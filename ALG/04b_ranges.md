


### merge intervals
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