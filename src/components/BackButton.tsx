"use client";
import { useRouter } from "next/navigation";

/** Goes back to the previous page on this site, or to the roadmap when opened directly. */
export function BackButton() {
  const router = useRouter();
  const goBack = () => {
    let sameSite = false;
    try {
      sameSite = !!document.referrer && new URL(document.referrer).origin === location.origin;
    } catch {}
    if (sameSite || window.history.length > 1) router.back();
    else router.push("/");
  };
  return (
    <button
      type="button"
      onClick={goBack}
      className="inline-flex items-center gap-1.5 rounded-lg border border-line bg-card px-3 py-1.5 text-sm text-muted transition-colors hover:text-fg"
    >
      <svg viewBox="0 0 16 16" className="size-3.5" fill="none" stroke="currentColor" strokeWidth="2" aria-hidden>
        <path d="M10 3L5 8l5 5" strokeLinecap="round" strokeLinejoin="round" />
      </svg>
      Back
    </button>
  );
}
