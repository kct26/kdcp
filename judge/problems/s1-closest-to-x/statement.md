---
title: Closest to X First
session: 1
order: 4
lesson: complexity-sorting
---

Reorder a list of n integers by how far each one is from a target value x: smaller distance |aᵢ − x| comes first. When two values are equally far from x, the smaller value comes first.

## Input

The first line holds T. Each test case has a line with n and x, then a line with a₁ … aₙ.

## Output

For each test case print the reordered list on one line, separated by spaces.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 10⁵
- −10⁹ ≤ x, aᵢ ≤ 10⁹

## Sample

```input
2
5 3
1 5 3 4 2
4 -1
-3 1 -1 0
```

```output
3 2 4 1 5
-1 0 -3 1
```

Use a custom comparator. |aᵢ − x| can reach 2·10⁹, so compute it in `long long`.
