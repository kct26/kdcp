# KDCP

A 12-month competitive programming roadmap with notes, C++ reference code and curated problems (Codeforces, CSES, AtCoder, Kattis).

**Stack:** Next.js 16 (App Router, static export) · React 19 · TypeScript · Tailwind CSS v4 · Shiki

## Run locally

```bash
npm install
npm run dev        # http://localhost:3000
npm run build      # static site in ./out
```

## Add or edit a topic

Each topic is one Markdown file in `src/content/topics/<slug>.md`:

```md
---
title: Stack
summary: One line shown under the title.
---

Explanation in Markdown, with ```cpp code blocks.

## Problems
- [Problem name](https://cses.fi/problemset/task/1645) Easy
```

Levels are `Easy`, `Medium` or `Hard`. Topic order and months live in `src/content/roadmap.ts`.

## Extra practice judge

The extra problems (one set per session) have no online judge, so this repo includes one. Judge your C++ solution locally:

```bash
python3 judge/judge.py --list
python3 judge/judge.py s2-collisions my.cpp
```

See [judge/README.md](judge/README.md) for details and how to add problems.

## Deploy

- **GitHub Pages:** push to `main`, then in the repo go to *Settings → Pages → Source: GitHub Actions*. The workflow in `.github/workflows/deploy.yml` builds and publishes the site at `https://<user>.github.io/<repo>/`.
- **Vercel / Netlify:** import the repo; no configuration needed.
