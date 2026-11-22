import Link from "next/link";
import type { Metadata } from "next";
import { getExtras, getTopic } from "@/lib/content";
import { renderMarkdown } from "@/lib/markdown";
import { BackButton } from "@/components/BackButton";
import { Judge } from "@/components/Judge";
import { SplitView } from "@/components/SplitView";

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

  // Two panels like HackerRank: statement on the left, editor on the right, with a draggable
  // divider between them. On large screens both fill the window below the header and scroll separately.
  const statement = (
    <>
        <div className="border-b border-line px-6 pt-4">
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
          <nav className="mt-3 flex gap-6 text-sm">
            <span className="border-b-2 border-[#1ba94c] pb-2 font-bold">Problem</span>
          </nav>
        </div>
        <article className="prose px-6 py-6" dangerouslySetInnerHTML={{ __html: html }} />
        <p className="px-6 pb-8 text-xs text-muted">
          Prefer your own machine? Run <code className="font-mono">python3 judge/judge.py {e.id} my.cpp</code> from the
          project folder to test at full size.
        </p>
    </>
  );
  return <SplitView left={statement} right={<Judge id={e.id} />} />;
}
