import Link from "next/link";
import { ThemeToggle } from "./ThemeToggle";

export function Header() {
  return (
    <header className="sticky top-0 z-20 border-b-[3px] border-brand bg-header">
      <div className="mx-auto flex h-14 max-w-6xl items-center justify-between px-4 sm:px-6">
        <Link
          href="/"
          aria-label="KDCP home"
          className="rounded-lg bg-brand px-2.5 py-1 text-[15px] font-bold tracking-wider text-[#1d1f21] transition-transform hover:scale-105"
        >
          KDCP
        </Link>
        <ThemeToggle />
      </div>
    </header>
  );
}
