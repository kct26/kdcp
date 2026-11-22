---
title: One Seat Each
session: 4
order: 5
lesson: heap
---

There are n guests and seats numbered 1, 2, 3, …. Guest i accepts only a seat numbered from 1 to rᵢ, and seating them brings value wᵢ. Each seat holds at most one guest, and you may leave guests unseated.

Find the maximum total value of seated guests.

## Input

The first line holds T. Each test case has a line with n, a line with r₁ … rₙ, and a line with w₁ … wₙ.

## Output

For each test case print the maximum total value.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 2·10⁵, and the sum of n over all test cases is at most 7·10⁵
- 1 ≤ rᵢ, wᵢ ≤ 10⁹

## Sample

```input
2
5
1 1 2 3 3
4 6 5 2 1
3
1000000000 2 1
7 7 7
```

```output
13
21
```

In the first case seat 1 takes the guest worth 6, seat 2 the guest worth 5, and seat 3 the guest worth 2.

This is the deadline problem in disguise: sort by rᵢ, keep the seated values in a min-heap, and drop the smallest whenever more guests are seated than rᵢ allows.
