---
title: Best k Scores
session: 5
order: 5
lesson: set-multiset
---

A scoreboard holds n scores (scores may repeat) and a number k. Process q operations, and after each one print the **sum of the k largest scores** (counting repeated scores separately; the sum is 0 when k = 0):

- `1 x y`: one score equal to x is changed to y. A score equal to x is guaranteed to exist.
- `2 k`: k is set to a new value, which differs from the current k by at most 1.

## Input

The first line holds T. Each test case starts with a line containing n, q and the initial k, then a line with the n scores, then q operation lines.

## Output

After each operation print the sum on its own line.

## Constraints

- 1 ≤ T ≤ 25
- 1 ≤ n, q ≤ 2·10⁵
- 0 ≤ k ≤ n at all times
- −10⁹ ≤ scores, x, y ≤ 10⁹

## Sample

```input
1
5 4 2
3 -1 4 1 5
1 5 0
2 3
1 -1 9
2 2
```

```output
7
8
16
13
```

Split the scores into two multisets: `top` with the k largest and `rest` with the others, and keep the sum of `top`. After each change, move single elements across the border until `top` has size k again and its smallest element is at least the largest element of `rest`.
