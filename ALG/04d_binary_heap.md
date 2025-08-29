Data Structure - record data wisely and economically

## Heap and Priority Queue
When efficient (O(log n)) insertion and **only** delete min/max needed. (If there's
a need for arbitrary deletion, use OrderedMap).  
Notice most language has a default **min** heap.

### Basic usage
```python
heap1 = []
heapify(heap1)
elem1 = 1
heappush(heap2, 0-elem) # can transfer into max heap via negation
value = 0-heappop(heap2) # transfer back to original element

heap2 = []
heapify(heap2)
heappush(heap2, (1, "hallo")) # can customize priority by tuple
priority, value = heappop(heap2)
```
### scenario 1.1: kth largest element
```python
def findKthLargest(self, nums: List[int], k: int) -> int:
    largestk = []
    heapify(largestk)

    for nun in nums:
        heappush(largestk, num)
        if len(largestk) > k:
            heappop(largestk)
    
    return largestk[0] # smallest in largest k elements
```
### scenario 1.2: find median from data stream
```python
class MedianFinder:
    """
    maintain two partitions of accumulated data
    pq1: get and pop max when len(pq1) > (size + 1) // 2
    pq2: get and pop min when len(pq2) > size // 2
    invariant: 0 <= len(pq1) - len(pq2) <= 1
    """
    def __init__(self):
        self.max_heap = []
        self.min_heap = []
        heapify(self.max_heap)
        heapify(self.min_heap)
        

    def addNum(self, num: int) -> None:
        if len(self.max_heap) == 0:
            heappush(self.max_heap, -num)
            return None
        
        max_heap_top = -(self.max_heap[0])
        if num <= max_heap_top:
            heappush(self.max_heap, -num)
        else:
            heappush(self.min_heap, num)
        
        # rebalance between two heaps
        if len(self.max_heap) - len(self.min_heap) >= 2:
            heappush(self.min_heap, -heappop(self.max_heap))
        elif len(self.min_heap) - len(self.max_heap) >= 1:
            heappush(self.max_heap, -heappop(self.min_heap))
            
        

    def findMedian(self) -> float:
        assert 0 <= len(self.max_heap) - len(self.min_heap) <= 1

        if len(self.max_heap) - len(self.min_heap) == 1:
            return -self.max_heap[0]
        else:
            x = -self.max_heap[0]
            y = self.min_heap[0]
            return (x + y) / 2
```

### scenario 2.1: [greedy related] time scheduling
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