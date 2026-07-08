# Banker's Algortithm

## Idea

- Banker mentality before giving loan : "If I approve this request, can everyone still eventually finish?"

- Most Important deadlock *avoidance* algorithm

- Unlike deadlock detection, it prevents the system from entering an unsafe state.

## Data Structures:

1. Allocation Matrix: Current allocation

2. Max matrix : maximum demand

3. Need matrix : Max- allocation

## Time complexity

- P = number of processes
- R = number of resource types

- The safety algorithm may scan all processes multiple times. O(P^2xR)

## Resource Request Algorithm

- The previous implementation checks whether the current state is safe

- A Real OS also handles new resource requests

- When process Pi requests resources:

1. Verify *Request<= Need*
2. Verify *Request<= Available*
3. Temporarily allocate the resources
4. Run the safety algorithm
5. If the state remains safe : Keep allocation
6. Otherwise: Roll back temporary allocation. Make the process wait

- this "pretend allocation" followed by a safety check is what makes Banker's Algorithm an *avoidance algorithm*

## Detection VS Avoidance

1. RAG : Detect deadlock (single instance resources)

2. Wait-For-Graph : detect deadlock among processes

3. Banker's algorithm : Avoid deadlock before it happens

4. Lock ordering/ Dining philosopher's strategies : Prevent deadlock by design

## Real life perspective:

- Although general-purpose operating system rarely use Banker's algorithm because processes often cannot accurately declare their maximum future needs, the underlying idea is valuable ins systems where workloads and resources are predictable:

1. Embedded and real-time systems: Tasks often have known maximum resource requirements, making avoidance strategies practical

2. Defense Systems: Mission-critical resource schedulers can reject allocations that would jeopardize future task completion

3. AI clusters: Resource schedulers for GPUs, memory, and accelerators perfrom admission-control decisions inspired by the same principle- ensuring new jobs don't prevent existing job from completing.

---
---