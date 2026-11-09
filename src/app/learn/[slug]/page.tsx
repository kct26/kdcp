import Link from "next/link";
import type { Metadata } from "next";
import { order, monthOf } from "@/content/roadmap";
import { getTopic, neighbours } from "@/lib/content";
import { renderMarkdown } from "@/lib/markdown";
import { BackButton } from "@/components/BackButton";

type Props = { params: Promise<{ slug: string }> };

export const dynamicParams = false;
export function generateStaticParams() {
  return order.map((slug) => ({ slug }));
}

export async function generateMetadata({ params }: Props): Promise<Metadata> {
  const t = getTopic((await params).slug);
  return { title: t.title, description: t.summary };
}

const levelColor = { Easy: "bg-easy", Medium: "bg-medium", Hard: "bg-hard" } as const;

export default async function TopicPage({ params }: Props) {
  const { slug } = await params;
  const t = getTopic(slug);
  const month = monthOf(slug);
  const html = await renderMarkdown(t.body);
  const { prev, next } = neighbours(slug);

  return (
    <main>
      <BackButton />
      <p className="mt-8 font-mono text-xs text-muted">
        Month {String(month.n).padStart(2, "0")} · {month.title}
      </p>
      <h1 className="mt-2 text-3xl font-bold tracking-tight">{t.title}</h1>
      <p className="mt-2 text-muted">{t.summary}</p>

      <article className="prose mt-10" dangerouslySetInnerHTML={{ __html: html }} />

      {t.problems.length > 0 && (
        <section className="mt-14">
          <h2 className="mb-4 text-[1.05rem] font-medium tracking-tight">Problems</h2>
          <div className="overflow-hidden rounded-xl border border-line bg-card shadow-sm">
            <table className="w-full text-sm">
              <thead className="bg-head text-left text-[11px] uppercase tracking-wider text-head-fg">
                <tr>
                  <th className="w-10 py-2 pl-4 font-bold">#</th>
                  <th className="py-2 font-bold">Problem</th>
                  <th className="hidden py-2 font-bold sm:table-cell">Source</th>
                  <th className="py-2 pr-4 text-right font-bold">Level</th>
                </tr>
              </thead>
              <tbody className="divide-y divide-line">
                {t.problems.map((p, i) => (
                  <tr key={p.url} className="transition-colors hover:bg-soft">
                    <td className="py-2.5 pl-4 font-mono text-xs text-muted">{i + 1}</td>
                    <td className="py-2.5 pr-3">
                      <a href={p.url} target="_blank" rel="noreferrer" className="group inline-flex items-center gap-1.5">
                        <span className="text-link group-hover:underline group-hover:underline-offset-4">{p.name}</span>
                        <span className="text-muted opacity-0 transition-opacity group-hover:opacity-100">↗</span>
                      </a>
                      <span className="block text-xs text-muted sm:hidden">{p.judge}</span>
                    </td>
                    <td className="hidden py-2.5 text-muted sm:table-cell">{p.judge}</td>
                    <td className="py-2.5 pr-4 text-right">
                      <span className={`inline-block rounded-full px-2.5 py-0.5 text-[11px] font-medium text-white ${levelColor[p.level]}`}>
                        {p.level}
                      </span>
                    </td>
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        </section>
      )}

      <nav className="mt-16 grid gap-3 sm:grid-cols-2">
        {prev ? (
          <Link href={`/learn/${prev.slug}`} className="rounded-xl border border-line bg-card p-4 shadow-sm transition-shadow hover:shadow-md">
            <p className="text-xs text-muted">← Previous</p>
            <p className="mt-1 text-sm font-medium">{prev.title}</p>
          </Link>
        ) : (
          <span />
        )}
        {next && (
          <Link href={`/learn/${next.slug}`} className="rounded-xl border border-line bg-card p-4 text-right shadow-sm transition-shadow hover:shadow-md">
            <p className="text-xs text-muted">Next →</p>
            <p className="mt-1 text-sm font-medium">{next.title}</p>
          </Link>
        )}
      </nav>
    </main>
  );
}
