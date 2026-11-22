---
title: Smaller Than the Next
session: 2
order: 5
lesson: stack
---

A list of n positive integers changes in rounds. In each round, **every** element that is strictly smaller than the element right after it is removed, all at the same time (the comparisons use the list as it was at the start of the round). The remaining elements then close up.

How many rounds remove at least one element?

For example `3 1 2 4 1`: round 1 removes 1 and 2 (each is smaller than its right neighbour), giving `3 4 1`; round 2 removes 3, giving `4 1`; nothing changes after that, so the answer is 2.

## Input

The first line holds T. Each test case has a line with n, then a line with a₁ … aₙ.

## Output

For each test case print the number of rounds.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 2·10⁵
- 1 ≤ aᵢ ≤ 10⁹

## Sample

```input
3
5
3 1 2 4 1
3
1 2 3
4
7 7 7 7
```

```output
2
1
0
```

Simulating round by round is too slow when the answer is large. Instead compute, for each element, the round in which it disappears, scanning from right to left with a monotonic stack.
