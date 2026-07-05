# Dining Philosopher Problem

## Problem Statement:

- Five philosophers sit around a circular table

- Between every pair of philosophers is *one fork*

- Each philosopher repeatedly:

1. Thinks
2. Gets hungry
3. Picks up two forks
4. Eats
5. Puts down both forks

E.g. 5 Philosophers, 5 forks, Each philosopher needs *both* left and right forks to eat.

## Naive Solution [DeadLock_Prone]

- Each philosopher does:

o Pick left fork

o Pick right fork

o Eat

o Release right fork

o Release left fork

- Each fork protected by mutex

- DeadLock Condition: Suppose all philosophers become hungry simulatenously. In this case No body can continue. Hence DeadLock

## Four Coffman Conditions

1. **Mutual Exclusion** : Resources cannot be shared. Only one philosopher can hold it.

2. **Hold and Wait** : a philosopher holds one fork while waiting for another. Holding F0 waiting for F1

3. **No preemption** : A fork cannot be forcibly taken away. Only the philosopher holding it can release it.

4. **Circulat wait** : P0 --> F1 || P1-->F2....P4-->F0 forms a cycle.

## Deadlock prevention

- A deadlock can be prevented by breaking *at least one* Coffman Conditions

### Strategy 1 : Resource Ordering [Recommended]

- Always acquire the lower-numbered fork first:

`int left = id; int right = (id+1)%5;

if(left>right)
{
    int temp = left;
    left = right;
    right = temp;
}

pthread_mutex_lock(&forks[left]);
pthread_mutex_lock(&forks[right]);

printf("Philosopher %d is eating\n", id);

pthread_mutex_unlock(&forks[right]);
pthread_mutex_unlock(&forks[left]);`

*Reason* - No circular wait can form because all philosophers acquire resources in a consistent global order.

- This solution is preferred because it is easy to reason about and scales better. Buffer solution is safe but it has a cost

- In Buffer solution one philosopher is always waiting, even if the system could otherwise make progress. This introduces an extra semaphore operation and can reduce parallelism.

## Strategy 2 : Odd-Even Rule

- Even philosophers: Left Right

- Odd Philosophers: Right Left

`if(id%2==0)
{
    pthread_mutex_lock(&forks[id]);
    pthread_mutex_lock(&forks[(id+1)%5]);
}


else
{
    pthread_mutex_lock(&forks[(id+1)%5]);
    pthread_mutex_lock(&forks[id]);
}`

- This signinficantly reduces the chance of deadlock by breaking the circular waiting pattern

### Strategy 3: Butler(Waiter) Solution

- Introduce a semaphore that allows at most 4 philosophers to try to eat simulateously.

- Initalization:

` sem_t room;
sem_init(&room,0,4);`

- Philosopher:

`sem_wait(&room);
pthread_mutex_lock(&forks[id]);
pthread_mutex_lock(&forks[(id+1)%5]);

printf("Philosopher %d is eating \n",id);

pthread_mutex_unlock(&forks[(id+1)%5]);
pthread_mutex_unlock(&forks[id]);

sem_post(&room);`

- Sincle one philosopher is always outside the "room", at least one philosopher can obtain both forks and eventually release them, preventing a circular wait

## Real- world insights

1. *Operating System*: Kernel threads compete for locks protecting memory managers, schedulers, and file systems

2. *Database* : Transactions lock multiple tables or rows; consisten lock ordering prevents deadlocks

3. *Distributed AI training*; Multiple workers synchronize on GPUs, parameter servers and communication buffers. Poor lock ordering can halt training.

4. *Defense Systems*: Radar, sensor fusion, and weapon-control modules often share buses and hardware resources. Careful resource ordering and scheduling are critical to avoid deadlocks in real-time systems.