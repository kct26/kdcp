---
title: Smallest Ranks
session: 6
order: 2
lesson: map-multimap
---

Replace each of n integers a₁ … aₙ by a positive integer bᵢ so that the order is kept exactly: aᵢ < aⱼ gives bᵢ < bⱼ, equal values get equal numbers, and aᵢ > aⱼ gives bᵢ > bⱼ. Among all such choices, make the largest bᵢ as small as possible, and print b.

## Input

The first line holds T. Each test case has a line with n, then a line with a₁ … aₙ.

## Output

For each test case print b₁ … bₙ on one line.

## Constraints

- 1 ≤ T ≤ 20
- 1 ≤ n ≤ 2·10⁵
- −10¹² ≤ aᵢ ≤ 10¹²

## Sample

```input
2
5
30 -4 30 7 -4
3
1000000000000 -1000000000000 0
```

```output
3 1 3 2 1
3 1 2
```

The answer is each value's rank among the distinct values: sort, remove duplicates, then find each value's position with `lower_bound` (or store the ranks in a `map`).
