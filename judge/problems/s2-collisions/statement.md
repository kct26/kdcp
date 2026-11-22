---
title: Head-On Collisions
session: 2
order: 2
lesson: stack
---

A row holds n nonzero integers. A positive number moves right and a negative number moves left, at the same speed. Whenever a positive number stands **immediately to the left** of a negative number, they collide: the one with the smaller absolute value disappears, and if the absolute values are equal both disappear. Numbers moving in the same direction, or a negative number to the left of a positive one, never collide.

Collisions keep happening until none are possible. Print what is left, in order.

For example `[4, 1, -3]`: 1 meets −3 and disappears, leaving `[4, -3]`; then 4 meets −3 and −3 disappears, leaving `[4]`.

## Input

The first line holds T. Each test case has a line with n, then a line with a₁ … aₙ.

## Output

For each test case print the number k of remaining elements on one line. If k > 0, print the remaining elements on a second line.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 2·10⁵
- −10⁹ ≤ aᵢ ≤ 10⁹, aᵢ ≠ 0

## Sample

```input
3
4
3 -1 2 -5
3
-4 2 -2
2
6 -6
```

```output
1
-5
1
-4
0
```

Scan left to right with a stack of survivors. A new negative number fights the positive numbers on top of the stack until it dies or no positive is left.
