---
title: Fading Rewards
session: 4
order: 3
lesson: heap
---

There are n reward machines. Machine i pays bᵢ the first time you use it, and each use lowers its payout by dᵢ, but never below 0. So its j-th use pays max(0, bᵢ − (j − 1)·dᵢ).

You must make **exactly** k uses in total, spread across the machines any way you like (a machine can be used many times, or never). Find the maximum total payout.

## Input

The first line holds T. Each test case has a line with n and k, then n lines, the i-th containing bᵢ and dᵢ.

## Output

For each test case print the maximum total payout.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 2·10⁵
- 0 ≤ k ≤ 2·10⁵
- 0 ≤ bᵢ, dᵢ ≤ 10⁹

## Sample

```input
3
2 4
10 3
8 1
1 3
5 4
3 0
1 1
2 2
3 3
```

```output
32
6
0
```

In the first case the best uses pay 10, 8, 7 and 7.

Each machine's payouts never increase, so the k largest payouts overall are always reachable. Pop the best machine from a max-heap k times, then push it back with its next payout.
