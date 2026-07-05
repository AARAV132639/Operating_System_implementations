# Reader- writer synchronization problem

## Problem:

- Suppose several thread share a database:

o Readers only read data

o Writers modify data

- We want:

o Multiple readers can read simultaneously

o Only one writer can write at a time

o No reader should read while a writer is writing

## Synchronization primitives:

- pthread_mutex_t mutex
- sem_t wrt

- Shared variable: int readCount = 0

**Mutex** : protects readCount, only one thread can update it at a time

**wrt** : controls access to the shared resource. When a writer acquires it: Readers blocked, Other writers blocked

## Algorithm

### Reader:

- Lock mutex

- readCount++

- if first reader
        wait(wrt)

- Unlock mutex

- Read

- Lock mutex

- readCount--

- if last reader
        signal(wrt)

- Unlock mutex

### Writer: 

- wait(wrt)

- Write

- signal (wrt)

## Why this works?

Suppose three readers arrive.

- Initially : readCount = 0

- Reader 1 : readCount = 1 || first reader || locks wrt

- Reader 2 : readcount = 2

- readCount = 3

*They do not wait*

All three read simulatneously

- When they finish: Reader 3 (last one) : readCount = 0 || unlock wrt

- Now a writer may proceed

## Key points:

- Readers execute together

- Writers execute one at a time

- No reader reads while a writer is writing

- If mutex is removed, two readers could both increment or decrement readCount at the same time, leading to incorret counts and synchronization failures

- If semaphore is removed, writers could modify sharedData while readers were reading it, resulting in inconsistent data

## Limitations of this Solution :

1. This is a *reader-preference* solution. If readers keep arriving continously a writer may never get a chance to write. This is called *writer starvation*

## Variants of Reader-writer Problem:

1. Reader- preference:

o Maximizes reader concurrency

o Writers can starve

2. Writer - preference:

o Waiting writers are given priority.

o Prevents writer starvation.

o Readrs may wait longer.

3. Fair (FIFO) Reader-writer

o Threads are served roughly in arrival order

o Prevents starvation of both readers and writers

o Commonly used in production systems

## Real Life Applications:

1. *DataBases*: Many clients can read records simultaneously, but updates require exclusive access

2. *Operating System*: File systems and kernel data structures often allow concurrent reads while synchronizing writes

3. *AI/ML* : Multiple inferference requests can read the same model weights concurrently, while a model update or reload requires exclusive access

4. *Defense Systems*: Multiple analysis modules may read a shared radar or sensor state, while a fusion or tracking module periodically updates that state exclusively.

- Reader-writer basically teaches an important design principle:

*Synchronization should maximize safe concurrency rather than simply allowing only one thread at a time*