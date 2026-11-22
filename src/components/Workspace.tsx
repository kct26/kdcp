"use client";
import { useEffect, useRef, useState } from "react";
import { Judge } from "./Judge";

const KEY = "kdcp-split-left";

/** LeetCode-style workspace: description card on the left, code + tests on the right,
 *  with a draggable divider between them (desktop only; panels stack on small screens). */
export function Workspace({ id, left }: { id: string; left: React.ReactNode }) {
  const [leftPct, setLeftPct] = useState(45);
  const [dragging, setDragging] = useState(false);
  const box = useRef<HTMLDivElement>(null);

  useEffect(() => {
    try {
      const v = Number(localStorage.getItem(KEY));
      if (v >= 20 && v <= 80) setLeftPct(v);
    } catch {}
  }, []);

  const set = (v: number) => {
    const c = Math.max(20, Math.min(80, v));
    setLeftPct(c);
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
      style={{ "--left": `${leftPct}%` } as React.CSSProperties}
      className="flex flex-col gap-2 bg-[#f0f0f0] p-2 lg:h-[calc(100dvh-59px)] lg:flex-row lg:gap-0"
    >
      <section className="min-h-0 overflow-hidden rounded-lg border border-[#e5e5e5] bg-white lg:w-[var(--left)] lg:shrink-0">
        {left}
      </section>

      <div
        role="separator"
        aria-orientation="vertical"
        aria-label="Resize the description and code panels"
        tabIndex={0}
        onPointerDown={start}
        onDoubleClick={() => set(45)}
        onKeyDown={(e) => {
          if (e.key === "ArrowLeft" || e.key === "ArrowRight") {
            e.preventDefault();
            set(leftPct + (e.key === "ArrowLeft" ? -3 : 3));
          }
        }}
        title="Drag to resize · double-click to reset"
        className="group hidden w-2 shrink-0 cursor-col-resize touch-none justify-center outline-none lg:flex"
      >
        <span
          className={`my-1 w-[3px] rounded-full transition-colors group-hover:bg-[#1a90ff] group-focus-visible:bg-[#1a90ff] ${
            dragging ? "bg-[#1a90ff]" : "bg-transparent"
          }`}
        />
      </div>

      <div className="flex min-h-0 min-w-0 flex-1 flex-col">
        <Judge id={id} />
      </div>
    </main>
  );
}
