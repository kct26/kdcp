import Link from "next/link";

type NavTopic = { slug: string; title: string };
type NavMonth = { n: number; title: string; topics: NavTopic[] };
type NavPhase = { name: string; range: string; months: NavMonth[] };

export function Roadmap({ phases }: { phases: NavPhase[] }) {
  return (
    <>
      {phases.map((phase, pi) => (
        <section key={phase.name} className="mt-14">
          <div className="mb-5 flex items-baseline justify-between border-b border-line pb-3">
            <h2 className="text-sm font-medium">
              <span className="mr-2 font-mono text-muted">0{pi + 1}</span>
              {phase.name}
            </h2>
            <span className="text-xs text-muted">{phase.range}</span>
          </div>

          <div className="grid gap-3 sm:grid-cols-2 lg:grid-cols-3">
            {phase.months.map((m) => (
              <article key={m.n} className="rounded-xl border border-line bg-card p-5 shadow-sm transition-shadow hover:shadow-md">
                <p className="font-mono text-xs text-muted">Month {String(m.n).padStart(2, "0")}</p>
                <h3 className="mt-2 font-medium tracking-tight">{m.title}</h3>
                <ol className="mt-4 space-y-0.5">
                  {m.topics.map((t) => (
                    <li key={t.slug}>
                      <Link
                        href={`/learn/${t.slug}`}
                        className="-mx-2 block rounded-md px-2 py-1.5 text-sm text-muted transition-colors hover:bg-soft hover:text-fg"
                      >
                        {t.title}
                      </Link>
                    </li>
                  ))}
                </ol>
              </article>
            ))}
          </div>
        </section>
      ))}
    </>
  );
}
