import Link from "next/link";

export default function NotFound() {
  return (
    <main className="mx-auto max-w-6xl px-6 py-32 text-center">
      <p className="font-mono text-sm text-muted">404</p>
      <Link href="/" className="mt-4 inline-block text-sm underline underline-offset-4">Back to roadmap</Link>
    </main>
  );
}
