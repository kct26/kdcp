"use client";
import { useEffect, useRef, useState } from "react";

const KEY = "kdcp-split-left";
const DEFAULT = 46; // % of the width given to the left panel

/** Two panels side by side with a draggable divider between them (desktop only;
 *  on small screens the panels stack). The chosen width is remembered in the browser. */
export function SplitView({ left, right }: { left: React.ReactNode; right: React.ReactNode }) {
  const [pct, setPct] = useState(DEFAULT);
  const [dragging, setDragging] = useState(false);
  const box = useRef<HTMLElement>(null);

  useEffect(() => {
    try {
      const v = Number(localStorage.getItem(KEY));
      if (v >= 20 && v <= 80) setPct(v);
    } catch {}
  }, []);

  const set = (v: number) => {
    const c = Math.max(20, Math.min(80, v));
    setPct(c);
    try {
      localStorage.setItem(KEY, String(c));
    } catch {}
  };

  const start = (e: React.PointerEvent) => {
    e.preventDefault();
    setDragging(true);
    const move = (ev: PointerEvent) => {
      const r = box.current!.getBoundingClientRect();
      set(((ev.clientX - r.left) / r.width) * 100);
    };
    const up = () => {
      setDragging(false);
      window.removeEventListener("pointermove", move);
      window.removeEventListener("pointerup", up);
      document.body.style.cursor = "";
      document.body.style.userSelect = "";
    };
    document.body.style.cursor = "col-resize";
    document.body.style.userSelect = "none";
    window.addEventListener("pointermove", move);
    window.addEventListener("pointerup", up);
  };

  return (
    <main
      ref={box}
      style={{ "--left": `${pct}%` } as React.CSSProperties}
      className="lg:flex lg:h-[calc(100dvh-59px)]"
    >
      <section className="min-h-0 overflow-y-auto bg-white lg:w-[var(--left)] lg:shrink-0">{left}</section>

      <div
        role="separator"
        aria-orientation="vertical"
        aria-label="Resize the problem and code panels"
        aria-valuenow={Math.round(pct)}
        aria-valuemin={20}
        aria-valuemax={80}
        tabIndex={0}
        onPointerDown={start}
        onDoubleClick={() => set(DEFAULT)}
        onKeyDown={(e) => {
          if (e.key === "ArrowLeft" || e.key === "ArrowRight") {
            e.preventDefault();
            set(pct + (e.key === "ArrowLeft" ? -3 : 3));
          }
        }}
        title="Drag to resize · double-click to reset"
        className={`group relative hidden w-1.5 shrink-0 cursor-col-resize touch-none items-center justify-center border-x border-line outline-none transition-colors hover:bg-[#e8eef6] focus-visible:bg-[#e8eef6] lg:flex ${
          dragging ? "bg-[#e8eef6]" : "bg-[#f3f5f7]"
        }`}
      >
        <span className={`h-10 w-1 rounded-full transition-colors group-hover:bg-[#1ba94c] ${dragging ? "bg-[#1ba94c]" : "bg-[#c2c7d0]"}`} />
      </div>

      <div className="flex min-h-0 min-w-0 flex-1 flex-col">{right}</div>
    </main>
  );
}
