export type Level = "Easy" | "Medium" | "Hard";

export interface Problem {
  name: string;
  url: string;
  level: Level;
  judge: string;
}

export interface Topic {
  slug: string;
  title: string;
  summary: string;
  /** Markdown body (without the Problems section). */
  body: string;
  problems: Problem[];
}

export interface Month {
  n: number;
  title: string;
  topics: string[];
}

export interface Phase {
  name: string;
  range: string;
  months: Month[];
}
