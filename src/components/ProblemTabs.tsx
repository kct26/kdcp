"use client";
import { useState } from "react";

/** "Problem" / "Solution" tabs for the left panel of a problem page. */
export function ProblemTabs({ problem, solution }: { problem: React.ReactNode; solution: React.ReactNode }) {
  const [tab, setTab] = useState<"problem" | "solution">("problem");
  const tabClass = (t: typeof tab) =>
    `border-b-2 pb-2 transition-colors ${tab === t ? "border-[#1ba94c] font-bold text-fg" : "border-transparent text-muted hover:text-fg"}`;
  return (
    <>
      <nav role="tablist" className="-mb-px mt-3 flex gap-6 px-6 text-sm">
        <button type="button" role="tab" aria-selected={tab === "problem"} onClick={() => setTab("problem")} className={tabClass("problem")}>
          Problem
        </button>
        <button type="button" role="tab" aria-selected={tab === "solution"} onClick={() => setTab("solution")} className={tabClass("solution")}>
          Solution
        </button>
      </nav>
      <div className="border-t border-line">{tab === "problem" ? problem : solution}</div>
    </>
  );
}
