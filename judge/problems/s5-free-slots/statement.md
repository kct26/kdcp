---
title: Parking Spots
session: 5
order: 4
lesson: set-multiset
---

A street has n parking spots numbered 1 to n, all free at the start. Process q operations:

- `1 l r`: a car wants a spot between l and r inclusive. It takes the **smallest free** spot in that range; print the spot number, or `-1` if every spot in the range is taken (the car then leaves without parking).
- `2 x`: the car in spot x leaves, so spot x becomes free. Spot x is guaranteed to be taken.

## Input

The first line holds T. Each test case starts with a line containing n and q, followed by q operation lines.

## Output

For each operation of type 1, print the result on its own line.

## Constraints

- 1 ≤ T ≤ 25
- 1 ≤ n, q ≤ 2·10⁵
- 1 ≤ l ≤ r ≤ n, 1 ≤ x ≤ n, and every type 2 operation is valid

## Sample

```input
1
4 6
1 1 4
1 1 4
1 2 2
2 1
1 2 4
1 1 3
```

```output
1
2
-1
3
1
```

Keep the free spots in a `set`. `lower_bound(l)` gives the smallest free spot that is at least l; it is the answer if it is at most r.
