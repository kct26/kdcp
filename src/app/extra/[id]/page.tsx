import Link from "next/link";
import type { Metadata } from "next";
import { getExtras, getTopic } from "@/lib/content";
import { renderMarkdown } from "@/lib/markdown";
import { BackButton } from "@/components/BackButton";
import { Workspace } from "@/components/Workspace";

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

  const description = (
    <div className="flex h-full flex-col">
      <div className="flex h-[41px] shrink-0 items-center gap-1.5 border-b border-[#eee] bg-[#fafafa] px-4 text-[13px] font-bold">
        <svg viewBox="0 0 16 16" className="size-4 text-[#1a90ff]" fill="none" stroke="currentColor" strokeWidth="1.6" strokeLinecap="round" aria-hidden>
          <rect x="3" y="2" width="10" height="12" rx="1.5" />
          <path d="M5.5 5.5h5M5.5 8h5M5.5 10.5h3" />
        </svg>
        Description
      </div>
      <div className="min-h-0 flex-1 overflow-y-auto px-5 py-4">
        <div className="flex items-center gap-3">
          <BackButton />
          <p className="truncate font-mono text-xs text-muted">
            Session {e.session} extra ·{" "}
            <Link href={`/learn/${e.lesson}`} className="hover:text-fg hover:underline hover:underline-offset-4">
              {lesson.title}
            </Link>
          </p>
        </div>
        <h1 className="mt-5 text-2xl font-bold tracking-tight">{e.title}</h1>
        <article className="prose mt-4" dangerouslySetInnerHTML={{ __html: html }} />
        <p className="mt-8 text-xs text-muted">
          Prefer your own machine? Run <code className="font-mono">python3 judge/judge.py {e.id} my.cpp</code> from the
          project folder to test at full size.
        </p>
      </div>
    </div>
  );

  // LeetCode-style workspace: description on the left, code and tests on the right.
  return <Workspace id={e.id} left={description} />;
}
