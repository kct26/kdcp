import Link from "next/link";
import type { Metadata } from "next";
import { getExtras, getTopic } from "@/lib/content";
import { renderMarkdown } from "@/lib/markdown";
import { BackButton } from "@/components/BackButton";

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
  const judge = await renderMarkdown(
    "```bash\n" + `python3 judge/judge.py ${e.id} my.cpp` + "\n```",
  );

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

      <section className="mt-14 rounded-xl border border-line bg-card p-5 shadow-sm">
        <h2 className="text-[1.05rem] font-medium tracking-tight">Judge your solution</h2>
        <p className="mt-2 text-sm text-muted">
          From the project folder, run your C++ file against the sample and random tests, including tests at the
          maximum size. Output is compared token by token.
        </p>
        <div className="prose" dangerouslySetInnerHTML={{ __html: judge }} />
      </section>
    </main>
  );
}
