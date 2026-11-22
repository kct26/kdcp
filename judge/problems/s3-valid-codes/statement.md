---
title: The k-th Code
session: 3
order: 4
lesson: queue-deque
---

A **code** is a non-empty string over the digits `1`, `2`, `3` in which no two neighbouring digits are equal. Codes are listed shortest first, and codes of the same length in dictionary order:

`1, 2, 3, 12, 13, 21, 23, 31, 32, 121, 123, 131, …`

Given k, print the k-th code in this list (counting from 1).

## Input

The first line holds T. Each test case is one line with k.

## Output

For each test case print the k-th code.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ k ≤ 2·10⁵

## Sample

```input
3
4
9
13
```

```output
12
32
132
```

Generate codes with a queue: start from `1`, `2`, `3`; each time you take a code from the front, append the digits that differ from its last digit, in increasing order, and push the results to the back. Codes come out in exactly the required order.
