import type { Phase } from "./types";

export const phases: Phase[] = [
  {
    name: "Foundations",
    range: "Months 1–6",
    months: [
      { n: 1, title: "Basic Data Structures", topics: ["complexity-sorting", "stack", "queue-deque", "heap", "set-multiset", "map-multimap", "bitset"] },
      { n: 2, title: "Core Techniques", topics: ["bit-manipulation", "two-pointers", "sieve", "binary-search", "ternary-search", "greedy", "recursion"] },
      { n: 3, title: "Dynamic Programming", topics: ["divide-and-conquer", "dp-intro", "dp-states", "dp-intervals", "dp-optimizations", "change-of-variables"] },
      { n: 4, title: "Graph Basics", topics: ["dfs", "topological-sort", "bridges-articulation", "scc", "bfs", "dijkstra", "dsu"] },
      { n: 5, title: "Math Basics", topics: ["combinatorics", "dp-counting", "probability", "expected-value", "game-theory", "proof-techniques"] },
      { n: 6, title: "Midterm Review", topics: ["midterm-practice"] },
    ],
  },
  {
    name: "Advanced",
    range: "Months 7–12",
    months: [
      { n: 7, title: "Advanced Data Structures", topics: ["segment-tree", "lazy-propagation", "fenwick-tree", "sparse-table", "trie", "suffix-array", "persistent-ds"] },
      { n: 8, title: "Advanced Techniques", topics: ["meet-in-the-middle", "sqrt-decomposition", "small-to-large", "kmp-hashing", "sweep-line", "convex-hull-trick", "randomization"] },
      { n: 9, title: "Advanced DP", topics: ["bitmask-dp", "sos-dp", "digit-dp", "matrix-exponentiation", "tree-dp", "bitset-dp", "dc-optimization"] },
      { n: 10, title: "Advanced Graphs", topics: ["max-flow-matching", "min-cut", "lca", "euler-tour", "hld", "centroid-decomposition", "two-sat"] },
      { n: 11, title: "Advanced Math", topics: ["geometry", "inclusion-exclusion-mobius", "euler-phi", "extended-euclid", "crt", "xor-basis", "numerical-methods"] },
      { n: 12, title: "Final Review", topics: ["final-practice"] },
    ],
  },
];

export const months = phases.flatMap((p) => p.months);
export const order = months.flatMap((m) => m.topics);
export const monthOf = (slug: string) => months.find((m) => m.topics.includes(slug))!;
