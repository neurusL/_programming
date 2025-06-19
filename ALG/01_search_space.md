# Chapter01: Search Space
- two pointer 
- sliding window
- binary search

## When search space can be pruned...

## 1. by two pointers
### scenario 1: remove elements satisfying property $$P$$ from array in place:
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
### scenario 2: when search space can be reduced to a sequence $$\{(i_t, j_t)\}$$, where $$ (i_t, j_t) < (i_{t+1}, j_{t+1}) $$
```python
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

## 2. by a "sliding window"
### scenario 1: when looking for consecutive sub-array with some property
1. search for string matching (Rabin Karp algorithm), or match up to permutation
2. search for shortest sub-string containing a multiset of chars
3. search for longest sub-string without duplicated chars
The problems can be solved by sliding window trick share the same property that:
- the solution space can be iterated thoroughly by maintain a window and slide over a larger search space
- lower boundary of the sliding window acts depending on the upper boundary of the window, which prevents the search on all potential combinations of lower and upper boundary, the key **challenge** is to come up with **invariant property of sliding window**
- after reaching the first sliding window with desired invariant, we will need to do next is shrink lower bound to break the invariant just right, followed by upper bound resume the invariant

Going back to the examples:
1. for string matching, window should only be size of string we match against,
2. window should cover all the chars in multiset, after that, 
3. window should never have duplicated chars in it, if there is, we pop lower side of the window until resume the invariant.

```python
    left = 0
    right = 0 
    window = {} # can be set, map, counters, array if keys are fixed, or 
    # other combined data structure
    # for instance in 3, you may maintain a hashmap together with a counter
    # of the number of char whose appearance is covered in the sliding window

    while right < len(iterable):
        window.add(iterable[right])
        right += 1

        while is_invariant(window): 
            # customized operation, e.g. update answer
            # ...

            # then shrink the window to break the invariant
            window.remove(iterable[left])
            left += 1
            # in next (serveral) iterations invariant will be resumed
```
