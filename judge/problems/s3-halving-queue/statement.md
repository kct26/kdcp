---
title: Split Until One
session: 3
order: 3
lesson: queue-deque
---

A queue initially holds n cards. Card i shows the positive number aᵢ and carries the label i, and the cards stand in order 1, 2, …, n from front to back.

Repeat until the queue is empty: take the card at the front.

- If its number is 1, write its label at the end of a log.
- Otherwise, with number x > 1, split it into two cards with the same label: first one with ⌊x / 2⌋, then one with ⌈x / 2⌉. Both go to the back of the queue in that order.

Print the log.

For example, with numbers `3 2`: card 1 (3) splits into 1 and 2; card 2 (2) splits into 1 and 1; then the cards 1, 2, 1, 1, … reach the front, and the log reads `1 2 2 1 1`.

## Input

The first line holds T. Each test case has a line with n, then a line with a₁ … aₙ.

## Output

For each test case print the log on one line, labels separated by spaces.

## Constraints

- 1 ≤ T ≤ 30
- 1 ≤ n ≤ 2·10⁵
- aᵢ ≥ 1 and a₁ + … + aₙ ≤ 2·10⁵ in each test case

## Sample

```input
2
2
3 2
3
1 1 4
```

```output
1 2 2 1 1
1 2 3 3 3 3
```

A card with number x produces exactly x log entries and fewer than 2x cards in total, so simulating with a `queue` is fast enough.
