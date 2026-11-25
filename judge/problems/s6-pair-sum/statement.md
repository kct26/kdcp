---
title: Pairs That Add Up
session: 6
order: 1
lesson: map-multimap
---

Given n integers a₁ … aₙ and a target M, count the index pairs (i, j) with i < j and aᵢ + aⱼ = M.

## Input

The first line holds T. Each test case has a line with n and M, then a line with a₁ … aₙ.

## Output

For each test case print the number of pairs.

## Constraints

- 1 ≤ T ≤ 20
- 1 ≤ n ≤ 2·10⁵
- −10¹² ≤ aᵢ ≤ 10¹², −2·10¹² ≤ M ≤ 2·10¹²

## Sample

```input
2
5 6
1 5 3 3 5
4 0
2 -2 -2 0
```

```output
3
2
```

In the first case the pairs are (1, 2), (1, 5) and (3, 4).

Walk left to right and keep a `map` from value to how many times it has appeared so far: each aᵢ pairs with every earlier M − aᵢ. Values need `long long`, and so does the count (up to about 2·10¹⁰).
