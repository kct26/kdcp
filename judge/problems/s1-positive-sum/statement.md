---
title: Sum of the Positives
session: 1
order: 6
lesson: complexity-sorting
---

Add up only the elements of the list that are strictly greater than 0. If there are none, the sum is 0.

## Input

The first line holds T. Each test case has a line with n, then a line with a₁ … aₙ.

## Output

For each test case print the sum of the positive elements.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 10⁵
- −10⁶ ≤ aᵢ ≤ 10⁶

## Sample

```input
3
5
3 -1 0 4 -8
3
-2 -2 0
2
1000000 1000000
```

```output
7
0
2000000
```

The total can reach 10¹¹, which does not fit in `int`: use `long long`.
