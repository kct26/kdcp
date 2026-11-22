---
title: Runner-Up Value
session: 1
order: 2
lesson: complexity-sorting
---

Among the n integers of a list, find the **second largest distinct value**: the largest value that is strictly smaller than the maximum. If every element is equal (so there is only one distinct value), print `-1`.

## Input

The first line holds T. Each test case has a line with n, then a line with a₁ … aₙ.

## Output

For each test case print the runner-up value, or `-1`.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 10⁵
- −10⁹ ≤ aᵢ ≤ 10⁹

## Sample

```input
3
5
4 8 8 1 6
3
-5 -5 -5
4
-2 -9 -2 -7
```

```output
6
-1
-7
```

Duplicates of the maximum do not count as the runner-up. Sorting works in O(n log n); a single pass that tracks the two best distinct values works in O(n).
