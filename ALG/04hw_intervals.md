A Case Study on Intervals

### Operations on non-overlapping intervals
For operations on interval, we need handle carefully for [x1, y1], [x2, y2] 
when ```not x2 > y1 and not y2 < x1```. In most cases, we first sort by x to only
consider the case ```x2 <= y1```
Union all intervals (L56)
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

        unions = []
        for [x, y] in intervals:
            # after sorting by x, the only case two adjacent intervals overlap
            # (x1, y1), (x2, y2) where x2 < y1
            if len(unions) == 0 or unions[-1][1] < x:
                unions.append([x, y])
            else:
                unions[-1][1] = max(unions[-1][1], y)
        
        return unions
```

Intersect all intervals (L452)
```python
    def findMinArrowShots(self, points: List[List[int]]) -> int:
        points.sort(key=lambda x: x[0])
        intersects = [] # reduce intervals to minimal intervals touching all points

        for point in points:
            if len(intersects) == 0 or \
                intersects[-1][1] < point[0]:
                # no overlap with last interval calculated
                intersects.append(point)
            else:
                # calculate a minimal interval touching both 
                # notice unlike merging intervals (union)
                # we are intersecting intervals, where only intersects[-1] is relevant
                [oldx, oldy] = intersects[-1]
                [newx, newy] = point
                intersects[-1] = [max(oldx, newx), min(oldy, newy)]

                # print(intersects[-1])
                assert intersects[-1][0] <= intersects[-1][1]
                
        return intersects
    """There's an alternative greedy solution of this problem"""
```

remove minimum number of intervals to make the rest non-overlap
```python
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        """
        greedy:
        - sort by x
        - whenever two adjacent intervals have overlap, choice the one with smaller y
        """

        intervals.sort(key=lambda x: x[0])

        res = []
        cnt = 0
        for [x, y] in intervals:
            if len(res) == 0 or res[-1][1] <= x:
                res.append([x, y])
            else:
                if res[-1][1] > y:
                    res[-1] = [x, y]
                cnt += 1

        return cnt
```

insert new interval in to sorted non-overlapped intervals (L57)
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
        unions = []       
        i = 0
        # when newInterval's left greater than current interval'right
        while i < n and intervals[i][1] < newInterval[0]:
            unions.append(intervals[i])
            i += 1
        
        # when newInterval overlap with current interval
        # (  ) ( [) (  ) ( ]) (  )
        while i < n and intervals[i][0] <= newInterval[1]:
            newInterval[0] = min(intervals[i][0], newInterval[0])
            newInterval[1] = max(intervals[i][1], newInterval[1])
            i += 1
        unions.append(newInterval)

        # when newInterval's right less than current interval's left
        while i < n:
            unions.append(intervals[i])
            i += 1

        return unions

```

remove one interval from sorted non-overlapped intervals:
```python
    def removeInterval(self, intervals: List[List[int]], toBeRemoved: List[int]) -> List[List[int]]:
        
        n = len(intervals)
        unions = []

        i = 0
        while i < n and intervals[i][1] < toBeRemoved[0]:
            unions.append(intervals[i])
            i += 1

        while i < n and intervals[i][0] <= toBeRemoved[1]:
            [x, y] = intervals[i]
            if x < toBeRemoved[0] and y > toBeRemoved[1]:
                unions.append([x, toBeRemoved[0]])
                unions.append([toBeRemoved[1], y])
            elif x < toBeRemoved[0] and y <= toBeRemoved[1]:
                unions.append([x, toBeRemoved[0]])
            elif x >= toBeRemoved[0] and y > toBeRemoved[1]:
                unions.append([toBeRemoved[1], y])

            i += 1

        while i < n:
            unions.append(intervals[i])
            i += 1

        return unions
```

### Scheduling tasks related problems

We can build interference graph from intervals, and such graph are "interval graph".
```ascii
|-------|                    |-------|
      |-------|
             |-------|
                   |-------|
                        |-------|
```
For example, above intervals induce an interference graph $$P_5$$, which is 2-colorable.

Calculating chromatic number of interval graphs (in general chordal graph, and more generally
perfect graph) has polynomial algorithms. Calculating chromatic number of arbitrary 
graph is NP-hard.
The ability to expunionss interference by lineariable intervals guarantees a efficient algorithm
of calculating chromatic number. An inteunionsting non-example is, register allocation:
```ascii
|-- x --|                    |-- x --|
      |-- y --|
             |-- z --|
                   |-- w --|
                        |-- u --|
```
will build the graph $$C_5$$ (3-colorable), which is neither a chordal nor a perfect graph. 
Such a graph cannot be build from simple intervals, e.g. in the meeting room problem,
since no two intervals there belongs to the same vertex in the graph.
A natural(but not trivial) solution is transfering program into a equivalent form
where we avoid splitting of variable's liveness---the form is call Static Single
Assignment(SSA) form. As the name suggested, we rename second ocurrence of x to
x', to ensure single assignment, concluding with intervals:
```ascii
|-- x --|                    |-- x' --|
      |-- y --|
             |-- z --|
                   |-- w --|
                        |-- u --|
```
with corunionsponding graph $$P_6$$ (2-colorable), which is chordal and perfect graph.
It turns out SSAized program's interference graph are always chordal, in such case,
register allocation has efficient algorithm to solve.