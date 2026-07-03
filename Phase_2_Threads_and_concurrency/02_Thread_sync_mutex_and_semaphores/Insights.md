# Insights: Synchornization using Mutex Lock(pthread_mutex) & Semaphores (POSIX_semaphores)

## Problem: Race Condition

o Suppose two threads execute counter++

o Initially it looks normal however under the hood its: Load counter --> Add 1 --> Store Counter

o But the output can vary in case multiple threads access the same memory leading to *Race Condition* because the result depends on the execution order


## Solution: Protect the shared resource

o Only one thread enters the critical section

o Two major methods : 1. Mutex      2. Semaphores


## Part 1 : Mutex

### Idea:

1. Thread A

2. Lock

3. Modify shared variable

4. Unlock

Thread B : waits until lock released

Incase of mutex only one thread executes the critical section.

- Purpose : Mutual exclusion

## Part 2: Semaphore

- Instead of locked & unlocked it stores a number

- E.g. Semaphore = 3 : three threads allowed simulatneosly.

- Purpose: Resource management & synchronization


## Usage:

### Mutex

Used when protecting: 

1. Shared Linked List
2. Shared Queue
3. Process table
4. File system metadata
5. Memory allocator

### Sempahore

Used when managing limited resources:

1. Printer pool
2. Database connections
3. Network sockets
4. Gpu execution slots
5. Producer- consumer buffer

## Defence & AI/ML perspective

### Edge AI on drones:
- Mulitple threads may handle sensor input, neural network inference, and flight control. 
- Mutexex protect shared state, while semaphores coordeinate data availability between threads

### Rada & signal processing:
- Producer threads acquire sensor data and consumer threads process it
- Semaphores efficiently synchronize these stages

### Deep learning frameworks:
- Libararies such as Pytorch and Tensorflow use mutexes and other syncronization mechansisms internally to safely manage shared memory, task queues and thread pools.

### Operating Systems:
- Kernels rely on synchronization primitives to protect process tables, schedulers, memory management strucutres and device drivers.



