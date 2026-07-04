# Producer - Consumer Problem

## Objective:

Implement a bounded buffer where:

1. *Producer* creates items and places them in a shared buffer.

2. *Consumer* removes items from the shared buffer

3. Producers must wait if the buffer is full.

4. Consumers must wait if the buffer is empty.

5. Only one thread can modify the buffer at a time.

## Step 1: The Shared Buffer

- For this we'll use a simple circular queue.

#define Buffer_SIZE 5
int buffer[BUFFER_SIZE];
int in=0; int out=0;

## Step 2: Synchornization Primitives

- we need three synchronization objects:

pthread_mutex_t mutex; sem_t empty; sem_t full;

### Purpose:

1. Mutex : 
            - Protects the critical section
            - Ensures only one thread accesses the buffer at a time

2. empty semaphore:
                    - Counts empty slots
                    - Initial value = buffer size

3. Full semaphore :
                    - Counts filled slots
                    - Initial value = 0

Initial state: Buffer size = 5 || empty = 5 || full = 0||

## Step 3 : Producer Algorithm

1. repeat forever

2. produce item

3. wait(empty)

4. lock(mutex)

5. insert item

6. unlock(mutex)

7. signal(full)

- Wait until there is an empty slot

- Lock the buffer

- Insert safely

- Unlock

- Inform consumers that a new item is available

## Step 4 : Consumer Algorithm

repeat forever

1. wait (full)

2. lock(mutex)

3. remove item

4. unlock(mutex)

5. signal (empty)

6. consume item

- Wait unitl an item exists

- Lock buffer

- Remove safely

- Unlock

- Inform producers that a slot is now free.

## Insights:

1. The exact order may vary because the producer and consumer run concurrently

2. Order of output might differ without *sleep()* because OS scheduler decides which thread runs next. 

3. Thread scheduling is nondeterministic

## How the semaphores change?

- Semaphores always reflect the current state of the buffer

- Suppose the buffer size is 5,

Initiall : empty = 5 || full = 0

- Producer inserts one item: empty = 4 || full =1

- Producer inserts another item : empty = 3 || full = 2

- consumer removes one : empty = 4 || full =1


## Why we need both  Mutex and Semaphore?

- Imagine remvoing the mutex

Two producers could execute: buffer[in] = item; in++;

at the same time, causing:

- Lost updates
- Overwritten items
- Corrupted queue indices

The mutex prevents simulatenous access to the shared buffer

Semaphores solve:

- *empty* prevents producing into a full buffer.

- *full* prevents consuming from an empty buffer.

They complement each other rather than replace each other

## Time complexity

- Produce operation : O(1)

- Consume Operation : O(1)

- Space complexity: O(Buffer_size)

## Read world applications:

1. Operating Systmes: Keyboard interrupts produce keystrokes; terminal drivers consume them

2. Networking : One thread receives packets while another processes them

3. AI/ML pipelines: A data-loading thread produces training batches while another thread or GPU consumes them for model training

4. Defense Systems: Sensor acquistion threads produce radar or camera data, and tracking or target-recognition threads consume it for analysis