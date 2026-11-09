---
title: Proof Techniques
summary: Invariants, extremal principle and pigeonhole for constructive problems.
---

Many Codeforces Div. 2 B–D problems are pure reasoning. A few tools carry most of the weight:

- **Invariants**: find a quantity (parity, sum mod k, XOR) that an operation never changes. If start and target disagree, the answer is impossible.
- **Monovariants**: a quantity that only moves one way; proves a process terminates.
- **Extremal principle**: look at the largest / smallest / leftmost element; it often has a forced role.
- **Pigeonhole**: n + 1 prefix sums modulo n → two are equal → some subarray sum is divisible by n.
- **Induction & constructions**: solve n = 1, 2, 3 by hand, find the pattern, then prove it extends.
- **Contradiction / exchange**: assume an optimal answer differs from yours and derive a contradiction.

Practical habit: brute-force tiny cases, print them, and look for the pattern before proving it.

## Problems
- [Raising Bacteria](https://codeforces.com/problemset/problem/579/A) Easy
- [Subarray Divisibility](https://cses.fi/problemset/task/1662) Medium
- [Two Sets](https://cses.fi/problemset/task/1092) Easy
- [Permutations](https://cses.fi/problemset/task/1070) Easy
- [Palindrome Reorder](https://cses.fi/problemset/task/1755) Easy
- [Gray Code](https://cses.fi/problemset/task/2205) Medium
