import Link from "next/link";
import type { Metadata } from "next";
import { getExtras, getTopic } from "@/lib/content";
import { renderMarkdown } from "@/lib/markdown";
import { BackButton } from "@/components/BackButton";
import { Judge } from "@/components/Judge";

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

  return (
    <main>
      <BackButton />
      <p className="mt-8 font-mono text-xs text-muted">
        Session {e.session} extra ·{" "}
        <Link href={`/learn/${e.lesson}`} className="hover:text-fg hover:underline hover:underline-offset-4">
          {lesson.title}
        </Link>
      </p>
      <h1 className="mt-2 text-3xl font-bold tracking-tight">{e.title}</h1>

      <article className="prose mt-8" dangerouslySetInnerHTML={{ __html: html }} />

      <Judge id={e.id} />
      <p className="mt-3 text-xs text-muted">
        Prefer your own machine? Run <code className="font-mono">python3 judge/judge.py {e.id} my.cpp</code> from the
        project folder to test at full size.
      </p>
    </main>
  );
}
