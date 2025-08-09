Data Structure - record data wisely and economically

## Heap and Priority Queue
When efficient (O(log n)) insertion and **only** delete min/max needed. (If there's
a need for arbitrary deletion, use OrderedMap)
### scenario 1: kth largest
 
### scenario 2: time scheduling
Usually, you are provided with a list of tasks [start_time, end_time], and some capacity constraining on number of intervals you can process. 
The general idea is simply modeling the processor ordered by starting time, where
you need a data structure maintaining tasks being processed. Upon new task coming in,
we **wrap up** with on-going tasks, then **enqueue** new task. The two operations
requires efficient deleting (based on order), and efficient add, where Heap is a natural fit.
```python
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:

        intervals.sort(key=(lambda x: x[0]))

        active_meetings = []
        heapify(active_meetings)

        max_mt = 0
        for [x, y] in intervals:
            # here we process pop first (wrapping up finished tasks in window)
            while len(active_meetings) > 0 and active_meetings[0] <= x:
                heappop(active_meetings)
            # avoid an instantaneous impossible state here by popping first
            # then push task to establish next state of window
            heappush(active_meetings, y)

            max_mt = max(max_mt, len(active_meetings))
        
        return max_mt

```
exercise: L253, L1094, L1834

L1834 (Simulation, Heap)
```python
    def getOrder(self, tasks: List[List[int]]) -> List[int]:
        """
        to model CPU's process, keep track of a current_time (initialized with 0)
        - process (increment current_time) tasks in heap, if there's any until >= t
        - if current_time do not reach t, i.e. no more tasks to process before time t
          we set t to be current time, since later tasks will increment time based on t
        - at time t (new tasks arrived at time t), push new tasks at time t into heap

        """
        tasks_idx = []
        for (i, [start, t]) in enumerate(tasks):
            tasks_idx.append((t, start, i))
        
        tasks_idx.sort(key=lambda x: x[1]) # sorted by starting time

        # tasks waited to be processed
        waiting = [] # (t, i)
        heapify(waiting)

        current_time = 0

        res = []

        j = 0
        while j < len(tasks_idx):
            (t, start, idx) = tasks_idx[j]

            while start > current_time and len(waiting) > 0:
                (next_t, next_i) = heappop(waiting)
                res.append(next_i)
                current_time += next_t
            
            current_time = max(current_time, start)

            while j < len(tasks_idx) and tasks_idx[j][1] == start:
                heappush(waiting, (tasks_idx[j][0], tasks_idx[j][2]))
                j += 1

        while len(waiting) > 0:
            (_, next_i) = heappop(waiting)
            res.append(next_i)

        return res

```