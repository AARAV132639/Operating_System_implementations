# Synchronization Questions

## 1. What is a race condition?
A **race condition** occurs when two or more threads/processes access and modify shared data at the same time, and the final result depends on the order in which they execute. This can lead to unpredictable or incorrect results.

---

## 2. What is a critical section?
A **critical section** is a part of a program where shared resources (such as variables, files, or memory) are accessed or modified. Only one thread or process should execute the critical section at a time to avoid data inconsistency.

---

## 3. Why do we need synchronization?
Synchronization is needed to:
- Prevent race conditions.
- Ensure data consistency and correctness.
- Coordinate access to shared resources.
- Avoid conflicts when multiple threads/processes execute concurrently.

---

## 4. What is mutual exclusion?
**Mutual exclusion (Mutex)** is a synchronization technique that ensures only one thread or process can enter a critical section at any given time, preventing simultaneous access to shared resources.

---

## 5. How does a mutex work?
A mutex works by allowing only one thread to lock it at a time.
- A thread calls `pthread_mutex_lock()` before entering the critical section.
- If the mutex is already locked, other threads wait until it is unlocked.
- After finishing the critical section, the thread calls `pthread_mutex_unlock()` to release the mutex.

---

## 6. What is a semaphore?
A **semaphore** is a synchronization mechanism that controls access to shared resources using a counter.
- It allows multiple threads to access a resource depending on the semaphore's value.
- Semaphore operations include:
  - `sem_wait()` – Decrements the semaphore value and waits if it is zero.
  - `sem_post()` – Increments the semaphore value and signals waiting threads.

---

## 7. What is the difference between a binary semaphore and a counting semaphore?

| Binary Semaphore | Counting Semaphore |
|------------------|-------------------|
| Has only two values: 0 or 1. | Can have values greater than 1. |
| Allows only one thread to access the resource at a time. | Allows multiple threads to access a limited number of resources. |
| Similar to a mutex but without ownership. | Used to manage multiple identical resources. |

---

## 8. When should you use a mutex instead of a semaphore?
Use a **mutex** when:
- Only one thread should access a critical section.
- The same thread that locks the mutex should unlock it.
- Protecting shared data from concurrent access.

Use a **semaphore** when:
- Managing multiple instances of a resource.
- Signaling between threads or processes.
- Limiting the number of concurrent accesses.

---

## 9. What happens if `pthread_mutex_lock()` is omitted?
If `pthread_mutex_lock()` is omitted:
- Multiple threads may enter the critical section simultaneously.
- Race conditions can occur.
- Shared data may become corrupted or inconsistent.
- The program may produce incorrect or unpredictable results.

---

## 10. Why are `sem_wait()` and `sem_post()` used?

- **`sem_wait()`**
  - Decreases the semaphore value by 1.
  - If the semaphore value is 0, the thread waits until it becomes available.
  - Used before entering the critical section.

- **`sem_post()`**
  - Increases the semaphore value by 1.
  - Signals waiting threads that a resource has become available.
  - Used after leaving the critical section.
```