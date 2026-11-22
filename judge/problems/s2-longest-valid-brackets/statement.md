---
title: Longest Balanced Stretch
session: 2
order: 1
lesson: stack
---

A string of `(` and `)` is **balanced** when its brackets can be paired so that every `(` is closed by a later `)`. For example `(())()` is balanced, while `)(` and `(()` are not.

Given a bracket string s, find the length of the longest **contiguous** substring that is balanced. Print 0 if there is none.

## Input

The first line holds T. Each test case is one line containing s.

## Output

For each test case print the length of the longest balanced substring.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ |s| ≤ 2·10⁵, s contains only `(` and `)`

## Sample

```input
3
(()())(
))((
()(()
```

```output
6
0
2
```

Push indices onto a stack and keep the index of the last unmatched `)` at the bottom as a boundary: when a `)` matches, the balanced stretch ending here starts right after the index left on top.
