---
title: Widest Gap
session: 5
order: 1
lesson: set-multiset
---

A ruler has integer marks at positions 0, 1, …, n. At the start only the two ends, 0 and n, are painted. Each of q operations paints or erases one inner mark x (0 < x < n); the two ends always stay painted. After every operation, report the largest distance between two **consecutive** painted marks.

## Input

The first line holds T. Each test case starts with a line containing n and q, followed by q lines with t and x:

- `1 x`: paint mark x (it is currently unpainted),
- `2 x`: erase mark x (it is currently painted).

## Output

After each operation print the largest gap on its own line.

## Constraints

- 1 ≤ T ≤ 25
- 2 ≤ n ≤ 10⁹
- 1 ≤ q ≤ 2·10⁵
- 1 ≤ x < n, and every operation is valid

## Sample

```input
1
12 5
1 4
1 8
1 10
2 4
2 8
```

```output
8
4
4
8
10
```

Keep the painted marks in a `set` and all current gap lengths in a `multiset`. Painting x splits the gap between its neighbours in two; erasing merges two gaps back. The answer is the largest element of the multiset.
