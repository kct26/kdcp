---
title: Beat the Deadlines
session: 4
order: 1
lesson: heap
---

There are n tasks. Each task takes exactly one day; task i earns wᵢ points if it is finished on day dᵢ or earlier (days are numbered from 1). You can work on at most one task per day, and each task is done at most once. Tasks you skip earn nothing.

Find the maximum total number of points.

## Input

The first line holds T. Each test case has a line with n, then n lines, the i-th containing dᵢ and wᵢ.

## Output

For each test case print the maximum total.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 2·10⁵
- 1 ≤ dᵢ ≤ n, 1 ≤ wᵢ ≤ 10⁹

## Sample

```input
2
3
1 5
1 9
2 3
4
2 10
2 20
2 30
4 1
```

```output
12
51
```

Process tasks by increasing deadline and keep the chosen ones in a min-heap. If the heap holds more tasks than the current deadline allows, drop the cheapest.
