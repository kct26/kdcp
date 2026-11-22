---
title: Ticket Line
session: 3
order: 1
lesson: queue-deque
---

A ticket line starts empty. Process q operations in order:

- `1 x`: a person with number x joins the **back** of the line.
- `2`: the person at the **front** leaves (nothing happens if the line is empty).
- `3`: report the number of the person at the front, or `-1` if the line is empty.

## Input

The first line holds T. Each test case starts with a line containing q, followed by q lines, one operation each.

## Output

For every operation of type 3, print the reported value on its own line.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ q ≤ 2·10⁵
- −10⁹ ≤ x ≤ 10⁹

## Sample

```input
1
8
3
1 5
1 -2
3
2
3
2
3
```

```output
-1
5
-2
-1
```

`std::queue` does all three operations in O(1).
