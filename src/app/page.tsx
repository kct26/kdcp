import { phases } from "@/content/roadmap";
import { getTopic } from "@/lib/content";
import { Roadmap } from "@/components/Roadmap";

export default function Home() {
  const data = phases.map((p) => ({
    name: p.name,
    range: p.range,
    months: p.months.map((m) => ({
      n: m.n,
      title: m.title,
      topics: m.topics.map((slug) => ({ slug, title: getTopic(slug).title })),
    })),
  }));

  return (
    <main className="mx-auto max-w-6xl px-4 pt-16 pb-24 sm:px-6 sm:pt-24">
      <h1 className="max-w-xl text-4xl font-bold tracking-tight text-balance sm:text-5xl">
        Competitive Programming Roadmap
      </h1>
      <Roadmap phases={data} />
    </main>
  );
}
