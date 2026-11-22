---
title: Overflowing Tanks
session: 4
order: 4
lesson: heap
---

You are given a limit K and n events. A set of tanks starts empty. Event i, given by three numbers (aᵢ, bᵢ, xᵢ), happens in this order:

1. A new tank with level aᵢ and **splash** bᵢ is added to the set.
2. Every tank in the set rises by xᵢ.
3. While some tank has level **at least K**, pick any such tank and remove it; every tank still in the set rises by the splash of the removed tank.

For each event, report how many tanks were removed during it. (The count does not depend on which tank you pick first: levels only ever go up, so a tank that reaches K stays at or above K until it is removed.)

## Input

The first line holds T. Each test case has a line with n and K, then n lines, the i-th containing aᵢ, bᵢ, xᵢ.

## Output

For each test case print n integers on one line: the number of tanks removed during each event.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 2·10⁵, and the sum of n over all test cases is at most 1.2·10⁶
- 1 ≤ K ≤ 10¹⁵
- 0 ≤ aᵢ, bᵢ, xᵢ ≤ 10⁹

## Sample

```input
1
4 10
3 5 2
6 1 1
2 0 3
1 1 1
```

```output
0 0 3 0
```

In event 3 the levels are 9, 10 and 5. Removing the 10 (splash 1) gives 10 and 6, removing that 10 (splash 5) gives 11, and that tank is removed too.

Since every rise applies to all tanks, store each tank's level minus a global offset. The tank with the highest level is always the first to reach K, so a max-heap is enough.
