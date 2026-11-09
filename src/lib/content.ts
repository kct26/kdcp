import fs from "node:fs";
import path from "node:path";
import { months, order } from "@/content/roadmap";
import type { Level, Problem, Topic } from "@/content/types";

const DIR = path.join(process.cwd(), "src/content/topics");
const cache = new Map<string, Topic>();

function judgeOf(url: string): string {
  const host = new URL(url).hostname;
  if (host.includes("codeforces")) return "Codeforces";
  if (host.includes("cses")) return "CSES";
  if (host.includes("atcoder")) return "AtCoder";
  if (host.includes("kattis")) return "Kattis";
  return host.replace(/^www\./, "");
}

function parse(slug: string, raw: string): Topic {
  const fm = raw.match(/^---\n([\s\S]*?)\n---\n([\s\S]*)$/);
  if (!fm) throw new Error(`${slug}.md: missing front matter`);
  const meta: Record<string, string> = {};
  for (const line of fm[1].split("\n")) {
    const i = line.indexOf(":");
    if (i > 0) meta[line.slice(0, i).trim()] = line.slice(i + 1).trim();
  }
  const [body, list = ""] = fm[2].split(/^## Problems\s*$/m);
  const problems: Problem[] = [];
  for (const line of list.split("\n")) {
    const m = line.match(/^- \[(.+?)\]\((\S+?)\)\s+(Easy|Medium|Hard)\s*$/);
    if (m) problems.push({ name: m[1], url: m[2], level: m[3] as Level, judge: judgeOf(m[2]) });
    else if (line.trim()) throw new Error(`${slug}.md: bad problem line "${line}"`);
  }
  return { slug, title: meta.title, summary: meta.summary, body: body.trim(), problems };
}

export function getTopic(slug: string): Topic {
  let t = cache.get(slug);
  if (!t) {
    t = parse(slug, fs.readFileSync(path.join(DIR, `${slug}.md`), "utf8"));
    cache.set(slug, t);
  }
  return t;
}


export function neighbours(slug: string) {
  const i = order.indexOf(slug);
  const at = (j: number) => (j >= 0 && j < order.length ? { slug: order[j], title: getTopic(order[j]).title } : null);
  return { prev: at(i - 1), next: at(i + 1) };
}
