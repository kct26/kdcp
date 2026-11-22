---
title: Silver Medals
session: 5
order: 3
lesson: set-multiset
---

You are given a permutation a₁ … aₙ of the numbers 1 to n. Every contiguous segment with at least two elements awards a silver medal to its **second largest** element. Find the sum of all silver medals, that is, the sum of the second largest value over all segments [l, r] with l < r.

## Input

The first line holds T. Each test case has a line with n, then a line with the permutation.

## Output

For each test case print the sum.

## Constraints

- 1 ≤ T ≤ 25
- 2 ≤ n ≤ 2·10⁵
- a is a permutation of 1 … n; the answer fits in a signed 64-bit integer

## Sample

```input
2
3
2 3 1
4
1 2 3 4
```

```output
5
14
```

In the first case the segments [2 3], [3 1] and [2 3 1] give 2 + 1 + 2.

Count, for each value, the segments in which it is second largest. Insert positions from the largest value down into a `set`: when value v is inserted, its nearest two larger positions on each side are its neighbours in the set.
