---
title: Balanced Columns
session: 6
order: 4
lesson: map-multimap
---

A grid has n rows and m columns of 0s and 1s. A block of consecutive rows l … r is **balanced** if, adding up only those rows, every column gets the same total. Count the balanced blocks.

## Input

The first line holds T. Each test case has a line with n and m, then n lines of m values each.

## Output

For each test case print the number of balanced blocks.

## Constraints

- 1 ≤ T ≤ 20
- 1 ≤ n ≤ 5·10⁴, 1 ≤ m ≤ 10
- every value is 0 or 1

## Sample

```input
2
3 2
1 0
0 1
1 1
4 1
1
0
1
1
```

```output
3
10
```

In the first case the balanced blocks are rows 1–2, row 3 alone, and rows 1–3. With one column every block is balanced.

Use prefix sums per column. Rows l … r are balanced exactly when the prefix vectors before l and at r have the same differences between column 1 and every other column. Count equal difference vectors with a `map` (start with the empty prefix).
