## Merge sort a linked list

As we mentioned in discussing merge sort, given sorted array-ish data $l1$ and $l2$, we can obtain a merged sorted array via
- constructing new array by picking elements from $l1$ or $l2$
- maintaining two pointers $p_1$ and $p_2$ pointing to next candidate to pick
- essentially, we narrow down the search space of next element to $O(1)$, by two pointers (see chapter 2)

### merge two sorted non-overlapping intervals
def intersectSortedIntervals(l1: List[List[int]], l2: List[List[int]]) -> List[int]:
    """
    requires: l1, l2 be sorted, non-overlapping intervals
    """
    if len(l1) == 0 or len(l2) == 0:
        return [] 
    
    p1, p2 = 0, 0
    res = []

    while p1 < len(l1) and p2 < len(l2):
        [x1, y1] = l1[p1]
        [x2, y2] = l2[p2]

        # consider next interval to append to res
        if y1 >= x2 and y2 >= x1:
            res.append([max(x1, x2), min(y1, y2)])

        # maintaint the two pointers (similar to merge in merge sort)
        if y1 < y2: 
            # then [x1, y1] can only be affected by [x2, y2], since next 
            # interval in l2 cannot overlap with [x1, y1]
            # we can safely move p1 by 1 since we already consider the effect of [x1, y1]
            p1 += 1
        else:
            p2 += 1
    
    return res

def unionSortedIntervals(l1: List[List[int]], l2: List[List[int]]) -> List[List[int]]:
    """
    requires: l1, l2 be sorted, non-overlapping intervals
    """
    if len(l1) == 0 or len(l2) == 0:
        return l1 + l2
    
    p1, p2 = 0, 0
    res = []
    l1, l2 = l1[:], l2[:] # we will mutate l1, l2 if not making deep copy

    while p1 < len(l1) and p2 < len(l2):
        [x1, y1] = l1[p1]
        [x2, y2] = l2[p2]

        # consider next interval to append to res
        if y1 < x2:
            res.append([x1, y1])
        elif y2 < x1:
            res.append([x2, y2])
        else:
            # in place merge happen
            merged_interval = [min(x1, x2), max(y1, y2)]
            l1[p1] = merged_interval
            l2[p2] = merged_interval
            

        # maintaint the two pointers
        if y1 < y2: 
            # then [x1, y1] can only be affected by [x2, y2], since next 
            # interval in l2 cannot overlap with [x1, y1]
            # we can safely move p1 by 1 since we already consider the effect of [x1, y1]
            p1 += 1
        else:
            p2 += 1
    
    while p1 < len(l1):
        res.append(l1[p1])
        p1 += 1
    
    while p2 < len(l2):
        res.append(l2[p2])
        p2 += 1
    
    return res

### merge two sorted linked lists
```python
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        """iterative approach
        - more efficient (avoid function call)
        - more complicated index tracking
        """
        dummy = ListNode(-1)
        
        p = dummy # step (pointer/index) on result linked list, i
        p1 = list1 # step (pointer/index) on first linked list, j
        p2 = list2 # second, k

        while p1 is not None and p2 is not None:
            if p1.val > p2.val:
                p.next = p2 # res.append(list2[k])
                p2 = p2.next # k += 1
            else:
                p.next = p1 # res.append(list1[j])
                p1 = p1.next # j += 1
            p = p.next # i += 1
        
        if p1:
            p.next = p1
        
        if p2:
            p.next = p2
        
        return dummy.next
```
```python
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        """recursive approach
        - more cost (function calls)
        - more straight forward and elegant
        """
        if list1 is None:
            return list2
        elif list2 is None:
            return list1
        else:
            if list1.val < list2.val:
                rest = self.mergeTwoLists(list1.next, list2)
                list1.next = rest
                return list1
            else:
                rest = self.mergeTwoLists(list1, list2.next)
                list2.next = rest
                return list2
```

### merge $k$ sorted linked list
approach 1: use ```mergeTwoList```
```python
def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        if len(lists) == 0:
            return None
        elif len(lists) == 1:
            return lists[0]
        else:
            """
            given N = n1 + n2 + .. + nk
            """
            """ 
            bruteforce merge:
            - k-1 times mergeTwoList, each with |l1| + |l2| cost
            - a super inbalanced tree
            - k layers, 
              cost = (n1 + (N - n1)) + (n2 + (N - n1 - n2)) + ...
                   = N + (N - n1) + (N - n1 - n2) + ...
            - in total O(N * k)
            """
            # last1 = lists.pop()
            # last2 = lists.pop()
            # last = self.mergeTwoLists(last1, last2)
            # lists.append(last)
            # return self.mergeKLists(lists)

            """
            divide and conquer merge:
            - k-1 times mergeTwoList, each with |l1| + |l2| cost
            - a balanced tree
            - log k layers
              cost = (n1 + n2 + .. + nk-1 + nk) 
                   + ((n1 + n2) + .. + (nk-1 + nk)) 
            - in total O(N * log k)
            """
            mid = len(lists) //2
            res1 = self.mergeKLists(lists[0:mid])
            res2 = self.mergeKLists(lists[mid:len(lists)])
            return self.mergeTwoLists(res1, res2)
```
approach 2: use heap
- the observation is similar to "two pointers" in merging two list, whereas here
we maintain "$k$ pointers" by heap, enabling us retreiving next minimal element
in $O(\log{k})$ time. Therefore, we acheive $O(N\log{k})$ same as divide and conquer.
```python
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        pointers = []
        heapify(pointers)
        for i, p in enumerate(lists):
            if p is not None:
                heappush(pointers, (p.val, i, p))
        
        dummy = ListNode(-1)
        p = dummy
        while len(pointers) > 0:
            (_, i, next_p) = heappop(pointers)
            if next_p.next is not None:
                heappush(pointers, (next_p.next.val, i, next_p.next))
            
            p.next = next_p
            p = p.next
        
        return dummy.next
```