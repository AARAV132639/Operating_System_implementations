# DeadLoc detection using RAG

## Goal:
Implement a Resource Allocation Graph (RAG) and detect deadlocks using cycle detection (DFS)

- One of the condition of deadlock is Cyclic Dependencies.
- Thus, if we are able to detect cycles we can avoid deadlocks

## Implementation:

1. Using DFS : Time Complexity is O(V+E) because it visits each node and edge once

- Limitation: A RAG detects deadlock only when *each resource type has a single instance*

- E.g. Printer(1) Scanner (1)

- It cannot correctly handle Printer = 5 copies|| GPU= 8 units || Memory Blocks = 32

- For multiple instances, os use *Wait-for Graph* (WFG) then run the same DFS cycle

## Application:

1. Operating System: Detect cycles, involving processes waiting for locks, devices or files

2. Database systems: Detect transcation deadlocks by building wait-for graphs between transcations

3. Distributed systems: Identify cylic waits among services competing for distributed locks.

4. Cloud orchestration: Detect dependency cycles among resource reservations

## Can we use Kahn's Algorithm?

- Yes, Kahn's algorithm detects cycles in a directed graph using *topological sorting*

- Algorithm:

o Compute indegree of every node

o Push all nodes with indegree 0 into a queue

o Remove them one by one

o Decrease indegrees of neighbours

o If some nodes remain unprocessed, a cycle exists

- time complexity: O(v+e) same as DFS

### Why is DFS taught more oftne?

- Because DFS is simpler to implement recursively for cycle detection

- DFS explicitly detects a *back edge*, which directly indicates a cycle

- Kahn's algorithm is more commonly used when you want a topological ordering such as:

                                                    o Task scheduling
                                                    o Course Scheduling
                                                    o Build systems
                                                    o Dependency resolution

- For deadlock detection, we only care whether a cycle exists, so DFS is the traditional choice

### Can we use DSU?

- No, DSU is designed for undirected graphs

- DSU ignores edge direction. It only knows that some components can belong to same connected component. It can't distinguish between the case of cycle and no cycle case

- Thus, DSU is not reliable for cycle detection

## Which algorithm is used in real systems?

1. Resource Allocation Graphs: DFS is the classical textbook approach because the graph is directed

2. Wait-for Graphs : DFS is also the most common implementation

3. Large dependency systems : Kahn's algorithm is often used because it naturally fits topological processing and can report which nodes remain in cycles

4. Network connectivity: Kruskal MST

5. Undirected Cycle detection: DSU is the standard tool

---
---