# Chapter 01: Search Space
- two pointer 
- sliding window
- binary search

## When search space can be pruned...

## 1. by two pointers
First, what is two pointer technique? Basically, each time we narrow down to two elements in search/memory space:
### scenario 1: remove elements satisfying property $P$ from array in place:
```python
def p(x: int) -> bool: # this can be generalized to any p
    return x == 0
    
def moveZeroes(self, nums: List[int]) -> None:
        """ remove 0 to the end of array
        method 1: (when we want to keep relative order)
            keep a pointer of next to write, and another iterator pointer
            when iterator pointer encounter a satisfying element, write 
            to the writer pointer
        method 2: (when there's no need to keep relative order, 
                   and target element is less frequent)
            keep a pointer starting from end pointint to a non-target
            another iterator pointer 
        """
        right = len(nums)-1  # to record right most idx where P is not true
        left = 0             # to record left most idx where P is true
        
        # both points to nowhere when initialized

        while left <= right:
            if p(nums[right]):
                right -= 1
            else:
                if p(nums[left]):
                    swap(nums[left], nums[right])
                left += 1

        return left
        # todo!("I hope there's a more generalizable and formal template for this")

```
### scenario 2.1: when input is sorted
- merge in merge sort

### scenario 2.2: when search space can be pruned to a sequence of range keep strictly decreasing
```python
    def twoSumLists(self, nums: List[int], start: int, end: int, target: int) -> List[List[int]]:
        res = []

        lo = start
        hi = end

        while lo < hi:
            x = nums[lo]
            y = nums[hi]
            if x + y == target:
                res.append([x, y])
                # ignore all same x's, since they won't contribute to new answer
                lo += 1
                while lo <= hi and nums[lo] == nums[lo-1]:
                    lo += 1
                # ignore all same y's ...
                hi -= 1
                while lo <= hi and nums[hi] == nums[hi+1]:
                    hi -= 1
            elif x + y < target:
                lo += 1
            else:
                hi -= 1

        return res

    def twoSumSmaller(self, nums: List[int], start: int, target: int) -> int:
        # assert the list is sorted
        # there's no need to sort the list each time we call twoSumSmaller
        # but rather main function sort the list, then
        # for each fixed number at idx i, run twoSumSmaller on nums[i:]
        # to avoid double count on different combinations

        left = start
        right = len(nums) - 1
        res = 0

        while left < right:
            sum = nums[left] + nums[right]

            if sum >= target:
                right -= 1
            else:
                # * a general technique of count result in different ways
                # all (left, right) are valid pairs whose sum < target
                res += (right - left)
                # consider next left
                left += 1
        
        return res

    def threeSumSmaller(self, nums: List[int], target: int) -> int:
        nums.sort()

        res = 0
        for i in range(len(nums) - 2):
            res += self.twoSumSmaller(nums, i + 1, target - nums[i])

        return res
```
exercise: L42, L923, L84
