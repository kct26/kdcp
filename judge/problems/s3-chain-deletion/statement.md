---
title: Difference Erasure
session: 3
order: 5
lesson: queue-deque
---

A list holds n non-negative integers. It changes in rounds. In each round, look at every element that has a neighbour on **both** sides; if it equals the absolute difference of those two neighbours, it is marked. All marked elements are then removed **at the same time**, and the remaining elements close up while keeping their order. Marking always uses the list as it was at the start of the round.

The process stops after a round in which nothing is marked. For every original element, report the round in which it was removed (rounds are numbered from 1), or `-1` if it is never removed.

For example `8 3 2 5`: in round 1 only the 2 is marked, because 2 = |3 − 5|, leaving `8 3 5`. In round 2 the 3 is marked, because 3 = |8 − 5|, leaving `8 5`. The answer is `-1 2 1 -1`.

## Input

The first line holds T. Each test case has a line with n, then a line with a₁ … aₙ.

## Output

For each test case print n integers on one line: the removal round of each element in original order, or −1.

## Constraints

- 1 ≤ T ≤ 30
- 3 ≤ n ≤ 2·10⁵, and the sum of n over all test cases is at most 2·10⁵
- 0 ≤ aᵢ ≤ 10⁹

## Sample

```input
3
6
5 2 3 1 4 6
4
1 1 0 1
4
8 3 2 5
```

```output
-1 1 -1 1 -1 -1
-1 1 1 -1
-1 2 1 -1
```

Store the list as a doubly linked list. After a round, only the neighbours of removed elements can become removable, so the next round only needs to check those.
