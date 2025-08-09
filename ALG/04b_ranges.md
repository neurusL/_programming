


### Operations on non-overlapping intervals
Given an array of intervals where intervals[i] = [start_i, end_i], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
```python
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        """
        Takeaway: 
        think of the question inductively:
        - given the method work for k-1 length list
        - merge first two intervals into one
        - reduce the problem of size k-1
        """
        intervals.sort(key= lambda x: x[0])

        res = []
        for [x, y] in intervals:
            # after sorting by x, the only case two adjacent intervals overlap
            # (x1, y1), (x2, y2) where x2 < y1
            if len(res) == 0 or res[-1][1] < x:
                res.append([x, y])
            else:
                res[-1][1] = max(res[-1][1], y)
        
        return res
```

insert new interval in to sorted non-overlapped intervals:

```python
    def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
        n = len(intervals)
        if n == 0:
            return [newInterval]

        """
        Takeaway:
        instead of handling three cases in one while loop,
        it's easier to handle in separated loop (states)
        """
        res = []       
        i = 0
        # when newInterval's left greater than current interval'right
        while i < n and intervals[i][1] < newInterval[0]:
            res.append(intervals[i])
            i += 1
        
        # when newInterval overlap with current interval
        # (  ) ( [) (  ) ( ]) (  )
        while i < n and intervals[i][0] <= newInterval[1]:
            newInterval[0] = min(intervals[i][0], newInterval[0])
            newInterval[1] = max(intervals[i][1], newInterval[1])
            i += 1
        res.append(newInterval)

        # when newInterval's right less than current interval's left
        while i < n:
            res.append(intervals[i])
            i += 1

        return res

```

remove interval from sorted non-overlapped intervals:
```python
    def removeInterval(self, intervals: List[List[int]], toBeRemoved: List[int]) -> List[List[int]]:
        
        n = len(intervals)
        res = []

        i = 0
        while i < n and intervals[i][1] < toBeRemoved[0]:
            res.append(intervals[i])
            i += 1

        while i < n and intervals[i][0] <= toBeRemoved[1]:
            [x, y] = intervals[i]
            if x < toBeRemoved[0] and y > toBeRemoved[1]:
                res.append([x, toBeRemoved[0]])
                res.append([toBeRemoved[1], y])
            elif x < toBeRemoved[0] and y <= toBeRemoved[1]:
                res.append([x, toBeRemoved[0]])
            elif x >= toBeRemoved[0] and y > toBeRemoved[1]:
                res.append([toBeRemoved[1], y])

            i += 1

        while i < n:
            res.append(intervals[i])
            i += 1

        return res
```

### Scheduling tasks related problems

We can build interference graph from intervals, and such graph are "interval graph".
|-------|                    |-------|
      |-------|
             |-------|
                   |-------|
                        |-------|
For example, above intervals induce an interference graph P5, which is 2-colorable.

Calculating chromatic number of interval graphs (in general chordal graph, and more generally
perfect graph) has polynomial algorithms. Calculating chromatic number of arbitrary 
graph is NP-hard.
The ability to express interference by lineariable intervals guarantees a efficient algorithm
of calculating chromatic number. An interesting non-example is, register allocation:
|-- x --|                    |-- x --|
      |-- y --|
             |-- z --|
                   |-- w --|
                        |-- u --|
will build the graph C5 (3-colorable), which is neither a chordal nor a perfect graph. 
Such a graph cannot be build from simple intervals, e.g. in the meeting room problem,
since no two intervals there belongs to the same vertex in the graph.
A natural(but not trivial) solution is transfering program into a equivalent form
where we avoid splitting of variable's liveness---the form is call Static Single
Assignment(SSA) form. As the name suggested, we rename second ocurrence of x to
x', to ensure single assignment, concluding with intervals:
|-- x --|                    |-- x' --|
      |-- y --|
             |-- z --|
                   |-- w --|
                        |-- u --|
with corresponding graph P6(2-colorable), which is chordal and perfect graph.
It turns out SSAized program's interference graph are always chordal, in such case,
register allocation has efficient algorithm to solve.