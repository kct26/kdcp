"use client";
import { useEffect } from "react";

/** Handles every "Copy" button rendered inside markdown code blocks. */
export function CopyCode() {
  useEffect(() => {
    const onClick = async (e: MouseEvent) => {
      const btn = (e.target as HTMLElement).closest<HTMLButtonElement>("[data-copy]");
      if (!btn) return;
      const code = btn.parentElement?.querySelector("pre")?.innerText ?? "";
      try {
        await navigator.clipboard.writeText(code);
        btn.textContent = "Copied";
      } catch {
        btn.textContent = "Failed";
      }
      setTimeout(() => (btn.textContent = "Copy"), 1500);
    };
    document.addEventListener("click", onClick);
    return () => document.removeEventListener("click", onClick);
  }, []);
  return null;
}
