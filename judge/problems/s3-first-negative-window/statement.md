---
title: First Negative in Each Window
session: 3
order: 2
lesson: queue-deque
---

Slide a window of exactly k consecutive elements across a list of n integers, from the left end to the right end. For each of the n − k + 1 windows, report the **leftmost negative** number inside it, or `0` if the window has no negative number.

## Input

The first line holds T. Each test case has a line with n and k, then a line with a₁ … aₙ.

## Output

For each test case print n − k + 1 integers on one line, one per window from left to right.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ k ≤ n ≤ 2·10⁵
- −10⁹ ≤ aᵢ ≤ 10⁹

## Sample

```input
2
6 2
4 -1 -7 5 8 -3
3 3
2 0 6
```

```output
-1 -1 -7 0 -3
0
```

Keep a queue of the positions of negative numbers. Before answering a window, drop positions that have slid out on the left; the front is then the answer.
