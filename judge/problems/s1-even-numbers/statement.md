---
title: Keep the Even Ones
session: 1
order: 1
lesson: complexity-sorting
---

You are given a list of n integers. Print only the even values, keeping the order in which they appear. If the list has no even value at all, print `-1`.

## Input

The first line holds T, the number of test cases. Each test case has two lines: the integer n, then the n integers a₁ … aₙ.

## Output

For each test case print one line: the even values separated by single spaces, or `-1`.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 10⁵
- −10⁹ ≤ aᵢ ≤ 10⁹

## Sample

```input
3
5
7 10 -4 3 0
2
9 -1
1
-6
```

```output
10 -4 0
-1
-6
```

Remember that 0 and negative numbers can be even too: test with `x % 2 == 0`, not `x % 2 == 1` for odd.
