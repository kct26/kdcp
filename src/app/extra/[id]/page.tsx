import Link from "next/link";
import type { Metadata } from "next";
import fs from "node:fs";
import path from "node:path";
import { getExtras, getTopic } from "@/lib/content";
import { renderMarkdown } from "@/lib/markdown";
import { BackButton } from "@/components/BackButton";
import { Judge } from "@/components/Judge";
import { SplitView } from "@/components/SplitView";
import { ProblemTabs } from "@/components/ProblemTabs";

type Props = { params: Promise<{ id: string }> };

export const dynamicParams = false;
export function generateStaticParams() {
  return getExtras().map((e) => ({ id: e.id }));
}

const find = (id: string) => getExtras().find((e) => e.id === id)!;

export async function generateMetadata({ params }: Props): Promise<Metadata> {
  return { title: find((await params).id).title };
}

export default async function ExtraPage({ params }: Props) {
  const { id } = await params;
  const e = find(id);
  const lesson = getTopic(e.lesson);
  const html = await renderMarkdown(e.body);
  const solutionFile = path.join(process.cwd(), "judge/problems", e.id, "solution.cpp");
  const solutionHtml = fs.existsSync(solutionFile)
    ? await renderMarkdown("```cpp\n" + fs.readFileSync(solutionFile, "utf8").trimEnd() + "\n```")
    : "";

  // Two panels like HackerRank: statement on the left, editor on the right, with a draggable
  // divider between them. On large screens both fill the window below the header and scroll separately.
  const problem = (
    <>
      <article className="prose px-6 py-6" dangerouslySetInnerHTML={{ __html: html }} />
      <p className="px-6 pb-8 text-xs text-muted">
        Prefer your own machine? Run <code className="font-mono">python3 judge/judge.py {e.id} my.cpp</code> from the
        project folder to test at full size.
      </p>
    </>
  );
  const solution = solutionHtml ? (
    <div className="px-6 py-6">
      <p className="text-sm text-muted">Try the problem yourself first. The full source code is hidden below.</p>
      <details className="group mt-4 overflow-hidden rounded-lg border border-line bg-white">
        <summary className="flex cursor-pointer list-none items-center justify-between gap-3 bg-[#f6f7f9] px-4 py-3 text-sm font-bold transition-colors hover:bg-[#eef1f5] [&::-webkit-details-marker]:hidden">
          <span className="flex items-center gap-2">
            <svg viewBox="0 0 16 16" className="size-4 text-[#1ba94c]" fill="none" stroke="currentColor" strokeWidth="1.8" strokeLinecap="round" strokeLinejoin="round" aria-hidden>
              <path d="M5.5 4.5L2 8l3.5 3.5M10.5 4.5L14 8l-3.5 3.5" />
            </svg>
            <span className="group-open:hidden">Show full solution</span>
            <span className="hidden group-open:inline">Hide full solution</span>
          </span>
          <svg viewBox="0 0 16 16" className="size-4 text-muted transition-transform group-open:rotate-180" fill="none" stroke="currentColor" strokeWidth="1.8" strokeLinecap="round" strokeLinejoin="round" aria-hidden>
            <path d="M4 6l4 4 4-4" />
          </svg>
        </summary>
        <div className="prose border-t border-line px-4 pb-4" dangerouslySetInnerHTML={{ __html: solutionHtml }} />
      </details>
    </div>
  ) : (
    <p className="px-6 py-6 text-sm text-muted">No solution yet.</p>
  );
  const statement = (
    <>
      <div className="px-6 pt-4">
        <div className="flex items-center gap-3">
          <BackButton />
          <p className="truncate font-mono text-xs text-muted">
            Session {e.session} extra ·{" "}
            <Link href={`/learn/${e.lesson}`} className="hover:text-fg hover:underline hover:underline-offset-4">
              {lesson.title}
            </Link>
          </p>
        </div>
        <h1 className="mt-4 text-2xl font-bold tracking-tight">{e.title}</h1>
      </div>
      <ProblemTabs problem={problem} solution={solution} />
    </>
  );
  return <SplitView left={statement} right={<Judge id={e.id} />} />;
}
