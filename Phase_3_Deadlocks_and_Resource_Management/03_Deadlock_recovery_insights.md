# Deadlock Recovery and Prevention

- Implementing at simulator level rather than real OS because actual kernels use far more complex heuristics

## Part 1 : Deadlock Prevention Simulator

- Instead of allowing a deadlock to occur, the simulator rejects any resource request that would violate the prevention policy

- Prevetion rule: Global Resources Ordering

                                            o Suppose resources are R0, R1, R2, R3

                                            o Every process must request R0-> R1-> R2-> R3

                                            o Hence an allocation function is used.

### Allocation function

` bool requestResource(Process &p, Resource resources[], int id)
{
    if(!p.resources.empty()&& id<p.resources.back())
    {
        cout<< "Denied \n";
        return false;
    }

    if(resources[id].allocated)
    {
        cout<< "Busy\n";
        return false;
    }

    resources[id].allocated = true;
    resources[id].owner = p.id;

    p.resources.push_back(id);

    return true;
}`

### Release

`void release(Process &p, Resource resources[])
{
    for(int r: p.resources[])
    {
        
            resources[r].allocated = false;
            resources[r].owner = -1;
        
    }
    p.resources.clear();
}

### Simulation

- P0 requests R0

- Granted

- P0 requests R2

- Granted

- P0 requests R1

- Denied

Reason: Violates resource order. Hence no deadlock can occur.

## Part 2: Deadlock Recovery

- Unlike prevention, Deadlock has already happened. Now we must recover.

### Recovery Strategy 1:

- Terminate every process

- Deadlock --> Kill everyone --> Restart

- Very simple and very expensive

` for(process &p: processes) p.resources.clear();`

- Not practical

### Recovery Strategy 2:

- Terminate One Victim

- Suppose P0 P1 P2 P3

- Choose one process: Kill P2

- It's resources become free

- Everyone else continues

### Recovery Stragety 3:

- Rollback

- Instead of termination restore process

- Checkpoint --> Rollback --> Retry

- This is used: Databases, Distributed Systems

### Recovery Strategy 4:

- Resource Preemption

- Take resources away. P0 owns printer --> Suspend P0 --> Give printer to P2

- Real OS rarely preempt arbitary resources because many cannot be safely taken away.

### Improving Victim selection

- Using "most resources held" is simple but not always the best strategy

- You can assign each process a cost:

`struct Process
{
    int id;
    int priority;
    int cpuTime;
    int resourcesHeld;
    bool checkpointAvailable;
}`

- Then compute a custom score

- Then choose the process with lowest importance/lowest recovery cost

- *This more closely resemebles how practical system choose victims.*

## Real OS

- Different systems use different strategies:

1. General purpose OS (LINUX, windows): Mostly avoid deadlocks through careful lock ordering, timeouts, and programming discipline rather than running a global deadlock recovery algorithm

2. Database Management Systems: Commonly detect deadlocks and abort(roll back) one transaction to break the cycle

3. Embedded and real-time systems: Emphasize prevention and avoidance because recovery may violate timing guarantees.

4. Distributed systems: Often combines timeouts, leases, checkpointing and roll back to recover from deadlocks or livelocks


- to do: Re read the code again for better understanding
---
---