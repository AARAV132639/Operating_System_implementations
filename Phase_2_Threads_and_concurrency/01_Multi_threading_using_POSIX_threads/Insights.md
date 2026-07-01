# Insights File For this experimentation

## Functions Used

1. pthread_create() --> creates a new thread 

2. pthread_join() --> waits for a thread to finish

3. pthread_exit --> Terminates a thread

4. pthread_t --> thread identifier

## Fundamental questions

1. What is a thread?

- A Thread is the smallest unit of execution inside a process.
- A process can contain one or more threads that execute concurrently.

- Each thread has its own: Program Counter, Registers, Stack
- Threads within the same process share : Code Segment, Data Segment, Heap and Open files

E.g. A web browser has seperate threads for rendering the page, downloading fiels and responding to user input.

---

2. One line difference between Process and Thread

-  A process is an independent program, while a thread is a lightweight execution path within that program

- Proces uses IPC as communication while threads use Shared Memory

---

3. Why use Multi Threading?

- Multithreading is used to improve performance and responsiveness

o Executes multiple tasks simulatneously

o Better CPU utilization

o Faster exectuion on multi-core processors

o Keeps application responsive.

E.g. While downloading a file, you can still scroll through a browser because different threads handle different tasks.

---

4. What is pthread_create()?

- POSIX thread library fucntion used to create a new thread.

- syntax: pthread_create(&thread, NULL, function, argument);

o &thread --> stores the thread ID

o NULL --> default thread attributes

o function --> function executed by the thread

o argument --> data passed to the thread function.

Returns: 0 on success, Non-zero on error

---

5. Why we use pthread_join()?

-pthread_join() makes the calling thread (usually the main thread) wait until the specified thread finishes execution

- Ensures all threads complete before the program exits

- Allows retrieval of thread's return value

- Prevents premature termination of the process

---

6. Why is output order different every run?

- Threads are scheduled by the operating system scheduler.

- The scheduler decides:

o Which thread runs first

o When a thread is paused

o When another threaad gets CPU time.

Since scheduling depends on factors like CPU availability and system load, the execution order is *non-deterministic* so output can change each run.

---

## Other key insights:

1. exit(0) inside any thread ends the whole program while pthread_exit(NULL) inside a worker thread ends only that worker thread, while the remaining threads continue executing

2. There are majorly two types of threads: 1. User-Level Threads(ULT) 2. Kernel-level Threads(KLT)

3. An LLM server is highly multi-threaded. Different threads may handle: Tokenization, Request Scheduling, GPU data transfer, Logging etc

4. The actual neural network computation mainly runs on the GPU, but the CPU uses many threads to keep the GPU fed with work.

5. Reason OS matters in AI because CNNs & Transformers decide what to compute and the OS decides when computation runs and which resources it gets.

---
---