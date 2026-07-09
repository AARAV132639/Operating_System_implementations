# Resource allocation and Process co ordination simulation

## Goal

Each process:

1. Start
2. Request resources
3. Wait if unavailable
4. Execute
5. Release resources
6. Exit

Synchronization done using: 
- pthread_mutex
- pthread_cond

- Condition variable is used beacuse continously checking is *busy waiting*, which wastes CPU.
- Instead blocked threads should sleep until notified

## Application Perspective

1. Coordinate processes competing for CPUs, memory, files and devices.

2. Allocate GPUs, model instances, and memory to concurrent requests

3. Co ordinate workers competing for shared accelerators and communication links

4. Schedule radar processing, sensor fusion and communication tasks while managing limited hardware resources.

---
---