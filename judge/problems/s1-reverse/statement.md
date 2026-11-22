---
title: Back to Front
session: 1
order: 5
lesson: complexity-sorting
---

Print a list of n integers in reverse order: the last element first and the first element last.

## Input

The first line holds T. Each test case has a line with n, then a line with a₁ … aₙ.

## Output

For each test case print aₙ … a₁ on one line, separated by spaces.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 10⁵
- −10⁹ ≤ aᵢ ≤ 10⁹

## Sample

```input
2
4
10 -20 30 40
1
8
```

```output
40 30 -20 10
8
```

Store the values in a `vector`, then loop the index from n − 1 down to 0 (or call `reverse`).
