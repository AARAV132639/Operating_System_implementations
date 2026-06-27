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

