---
title: Mutually Visible Pairs
session: 2
order: 4
lesson: stack
---

Picture n towers of **distinct** heights a₁ … aₙ standing in a line. Two towers at positions l < r can **see each other** when every tower strictly between them is lower than both of them. Two neighbouring towers always see each other, since nothing stands between them.

Count the pairs (l, r) that can see each other.

## Input

The first line holds T. Each test case has a line with n, then a line with a₁ … aₙ (all different).

## Output

For each test case print the number of pairs.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 2·10⁵
- 1 ≤ aᵢ ≤ 10⁹, all aᵢ distinct

## Sample

```input
3
4
2 5 1 3
3
1 2 3
5
3 1 2 4 5
```

```output
4
2
6
```

In the first case the pairs are (2,5), (5,1), (1,3) and (5,3).

Keep a stack of heights that is decreasing from bottom to top. A new tower sees every tower it pops, plus the first taller one left on the stack.
