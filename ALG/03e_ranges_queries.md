# Chapter
- range queries (prefix sum, diff, ...)

L1094
```python 
    def carPooling(self, trips: List[List[int]], capacity: int) -> bool:    
        """ using diff array """
        diffs = SortedDict() # at time, number of passenger changed

        for [num, s, t] in trips:
            diffs[s] = diffs.get(s, 0) + num
            diffs[t] = diffs.get(t, 0) - num
        
        # then scan diffs, for max of count at any given time
        max_cnt = 0
        cnt = 0
        for (time, num) in diffs.items():
            cnt += num
            max_cnt = max(max_cnt, cnt)

        return max_cnt <= capacity
```