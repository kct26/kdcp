---
title: Closest Twins
session: 6
order: 3
lesson: map-multimap
---

For a list a₁ … aₙ, let D be the smallest distance j − i over all pairs i < j with aᵢ = aⱼ, or −1 if all values are different. Process q operations in order:

- `1 i x`: set aᵢ to x.
- `2`: print the current D.

## Input

The first line holds T. Each test case has a line with n and q, a line with a₁ … aₙ, then q operation lines.

## Output

For every operation of type 2, print D on its own line.

## Constraints

- 1 ≤ T ≤ 10
- 1 ≤ n, q ≤ 2·10⁵
- −10⁶ ≤ aᵢ, x ≤ 10⁶, and 1 ≤ i ≤ n

## Sample

```input
2
6 5
4 1 4 2 1 2
2
1 2 4
2
1 2 7
2
3 3
5 6 7
2
1 3 5
2
```

```output
2
1
2
-1
2
```

The closest equal pair is always two neighbouring occurrences of the same value. Keep a `set` of positions for each value (in a `map`) and a `multiset` of the gaps between neighbouring occurrences; an update removes one position and inserts another, changing at most three gaps each time.
