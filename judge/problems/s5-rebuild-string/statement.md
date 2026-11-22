---
title: Rebuild the Message
session: 5
order: 2
lesson: set-multiset
---

A lowercase message s was lost, but n clues survive. Each clue is a word t together with a list of starting positions: the word t appears in s starting at each of those positions (positions start at 1). Clues may overlap one another.

The clues never contradict each other, every position of s is covered by at least one clue, and the length of s equals the largest end position of any clue. So s is uniquely determined. Rebuild it.

## Input

The first line holds T. Each test case starts with a line containing n. Each of the next n lines describes a clue: the word t, a number k, then k starting positions in increasing order.

## Output

For each test case print the message s.

## Constraints

- 1 ≤ T ≤ 25
- 1 ≤ n ≤ 10⁵
- Every word is made of lowercase letters; in one test case the total length of all words is at most 10⁶, the total of all k is at most 10⁶, and |s| ≤ 10⁶
- 1 ≤ positions ≤ 10⁶

## Sample

```input
2
2
ab 2 1 4
bca 1 2
1
z 3 1 2 3
```

```output
abcab
zzz
```

Copying every clue letter by letter can take |t| · k steps, which is far too many. Each position of s needs to be written only once: keep the positions that are still empty in a `set` (or a "next empty position" jump array) and fill only those.
