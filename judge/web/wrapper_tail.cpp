
// ---- KDCP judge wrapper (appended to your code on large tests) ----
// The online runner returns at most 32 KB of output, so for large tests the program's
// output goes through a pipe to a reader thread that hashes it (FNV-1a 64 over the tokens
// joined by single spaces); only "KDCP <token count> <hash>" is printed. main() is left
// untouched: setup runs before main, and the result is printed when the program exits.
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
namespace kdcp_judge {
int real_stdout = -1, pipe_read = -1;
pthread_t reader;
bool started = false;
unsigned long long count = 0, hash = 1469598103934665603ULL;
void* read_all(void*) {
    static char buf[1 << 16];
    bool inTok = false;
    for (ssize_t n; (n = read(pipe_read, buf, sizeof buf)) > 0;)
        for (ssize_t i = 0; i < n; i++) {
            unsigned char c = buf[i];
            if (c == ' ' || c == '\n' || c == '\r' || c == '\t') { inTok = false; continue; }
            if (!inTok) {
                if (count++) { hash ^= ' '; hash *= 1099511628211ULL; }
                inTok = true;
            }
            hash ^= c; hash *= 1099511628211ULL;
        }
    close(pipe_read);
    return nullptr;
}
void finish() {
    std::cout.flush(); std::fflush(stdout);
    if (started) {
        dup2(real_stdout, 1);                     // closes the pipe's write end: the reader sees EOF
        pthread_join(reader, nullptr);
    }
    std::printf("KDCP %llu %016llx\n", count, hash);
    std::fflush(stdout);
}
__attribute__((constructor)) void setup() {
    int p[2];
    if (pipe(p) != 0) return;
    real_stdout = dup(1);
    pipe_read = p[0];
    dup2(p[1], 1); close(p[1]);
    started = pthread_create(&reader, nullptr, read_all, nullptr) == 0;
    std::atexit(finish);
}
}  // namespace kdcp_judge
