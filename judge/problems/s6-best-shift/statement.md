---
title: Best Shift
session: 6
order: 5
lesson: map-multimap
---

Two lists a and b each have n integers. For an integer x, let f(x) be the number of positions i with aᵢ + x = bᵢ, and let F be the largest f(x) over all integers x. Process q operations in order:

- `1 i x`: set aᵢ to x.
- `2 i x`: set bᵢ to x.
- `3`: print the current F.

## Input

The first line holds T. Each test case has a line with n and q, a line with a₁ … aₙ, a line with b₁ … bₙ, then q operation lines.

## Output

For every operation of type 3, print F on its own line.

## Constraints

- 1 ≤ T ≤ 10
- 1 ≤ n, q ≤ 2·10⁵
- −10⁶ ≤ aᵢ, bᵢ, x ≤ 10⁶, and 1 ≤ i ≤ n

## Sample

```input
1
3 5
1 5 2
4 8 6
3
2 3 5
3
1 1 0
3
```

```output
2
3
2
```

At first the differences bᵢ − aᵢ are 3, 3, 4, so x = 3 matches two positions.

F is the highest frequency among the differences dᵢ = bᵢ − aᵢ. Keep a count for each difference and a count of how many differences have each frequency; the maximum can only drop by one per update.
