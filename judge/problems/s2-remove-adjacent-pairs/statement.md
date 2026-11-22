---
title: Cancel the Twins
session: 2
order: 3
lesson: stack
---

A string of lowercase letters shrinks by this rule: whenever two **equal letters stand next to each other**, both are removed and the two remaining parts join together. The rule is applied again and again until no two neighbouring letters are equal. Print the final string.

For example `xyyxz` → `xxz` (removing `yy`) → `z` (removing `xx`).

## Input

The first line holds T. Each test case is one line containing the string s.

## Output

For each test case print the final string, or `-` if nothing is left.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ |s| ≤ 2·10⁵, lowercase English letters only

## Sample

```input
3
xyyxz
abba
abc
```

```output
z
-
abc
```

The final string does not depend on the order of removals. Build the answer in a stack (a `string` works): push each letter, or pop when it equals the top.
