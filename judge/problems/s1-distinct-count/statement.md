---
title: Counting Distinct Values
session: 1
order: 3
lesson: complexity-sorting
---

How many different values appear in a list of n integers? A value that appears several times is counted once.

## Input

The first line holds T. Each test case has a line with n, then a line with a₁ … aₙ.

## Output

For each test case print the number of distinct values.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 2·10⁵
- −10⁹ ≤ aᵢ ≤ 10⁹

## Sample

```input
2
6
5 -3 5 0 -3 5
4
7 1 9 2
```

```output
3
4
```

After sorting, equal values sit next to each other, so count positions where a value differs from the one before it. `sort` + `unique` does exactly this.
