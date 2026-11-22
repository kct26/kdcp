---
title: Meeting Point for Every Prefix
session: 4
order: 2
lesson: heap
---

Friends live at integer positions a₁, a₂, …, aₙ on a number line. For each i from 1 to n, the first i friends want to meet at a single integer point x so that the total walking distance |a₁ − x| + … + |aᵢ − x| is as small as possible. Print that smallest total for every i.

## Input

The first line holds T. Each test case has a line with n, then a line with a₁ … aₙ.

## Output

For each test case print n integers on one line: the answer for each prefix.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 2·10⁵
- −10⁹ ≤ aᵢ ≤ 10⁹

## Sample

```input
2
4
5 1 9 2
3
-3 -3 7
```

```output
0 4 8 11
0 0 10
```

The best meeting point is a median. Keep the lower half in a max-heap and the upper half in a min-heap, together with the sum of each half: the cost is (median · |lower| − sum(lower)) + (sum(upper) − median · |upper|).
