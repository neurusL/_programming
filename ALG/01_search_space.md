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
1. search for string matching (Rabin Karp algorithm, where each check for window is built incrementally), or match up to permutation
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
    left, right = 0, 0 # window boundary [left, right)
    window = {} # can be int, set, map, counters, array if keys are fixed, or 
    # other combined data structure
    # for instance in 3, you may maintain a hashmap together with a counter
    # of the number of char whose appearance is covered in the sliding window

    while right < len(iterable):
        window.add(iterable[right])
        right += 1

        while is_invariant(window): # sometimes worth additional check of left < right
            # customized operation, e.g. update answer
            # ...
            # it can be trick to wisely update information here (*)

            # then shrink the window to break the invariant
            window.remove(iterable[left])
            left += 1
            # in next (serveral) iterations invariant will be resumed
```
exercise: L76, L3297
here's an example how to break the final answer into partitions with bijection to each valid sliding window:
```python
    def validSubstringCount(self, word1: str, word2: str) -> int:
        # first step if find all matching of word2 in word1 up to permutation
        # the step is same as L76
        # second step is accumulate the counts based on each sliding window

         
        target_char_cnt = 0
        target = [0] * 26 # hardcode the window info here, since a fixed alphabet
        for s in word2:
            w = ord(s) - ord('a')
            target[w] += 1

        for i in range(26):
            if target[i] > 0:
                target_char_cnt += 1

        char_cnt = 0   # +1 if c in word2 and window[c] >= target[c]
        window = [0] * 26

        left, right = 0, 0

        res = 0 # total number count of desired substring

        while right < len(word1):
            w = ord(word1[right]) - ord('a')
            if target[w] > 0:
                window[w] += 1
                if window[w] == target[w]:
                    char_cnt += 1

            right += 1

            while char_cnt == target_char_cnt:
                print(left, right)
                res += len(word1) - right + 1   # this step is crucial (*)
                w2 = ord(word1[left]) - ord('a')
                if target[w2] > 0:
                    window[w2] -= 1
                    if window[w2] < target[w2]:
                        char_cnt -= 1
                left += 1

        return res
```
let's conclude with an extended discussion: when do not use sliding window? Namely, when you cannot narrow down the search space to a collection of windows that share an invariant, such that the growth of upper boundary doesn't "drag" the lower boundary to move forward. In this scenario, try to think about other optimization techniques, like reusing calculated results (e.g. dynamic programming).

## 3. by reducing half of search space
### scenario 1: when the data structure is highly ordered, e.g. a sorted array, or a circular sorted array
The idea of Binary Search is straight forward: whenever you probe an element $$e$$ in a space which is highly ordered w.r.t property $$P$$, based on $$P(e)$$, we ignore all elements $$e'$$ s.t. $$e' < e$$ or $$e' > e$$.
The hairy details on boundaries require careful reasoning, see comments in between lines.

Here're some templates of binary search on 1d array:
1. search for element in array
```python
    def binary_search(self, nums: List[int], target: int) -> int:
        # requires(is_sorted(nums))
        # we search on range [lo, hi)
        lo = 0
        hi = len(nums)

        while lo < hi: # while search range is not empty
            mid = (hi - lo) // 2 + lo # avoid overflow
            if nums[mid] == target:
                return mid
            elif nums[mid] > target:
                hi = mid # new `open` upper bd
            else:
                lo = mid + 1 
                # mid is excluded from search space, so lower bd = mid + 1
                # if lo = mid, then range not necessarily shink
                # cause infinite loop

        return -1
```
2. search for $$e$$'s lower bound (first element $$>= e$$) and upper bound (first element $$>e$$)
You may notice in the implementation of binary search above, ```lo``` stands for highest point that $$e = target$$ might be true, and ```hi``` for lowest point we know $$e > target$$. A small adjustment lead to implementation of ```lower_bound``` and ```upper_bound```
```python
    def lower_bound_include(self, nums: List[int], target: int) -> int:
        lo, hi = 0, len(nums)

        # hi: lowest point >= target (the result)
        # lo: given highest point < target, +1 to obtain new lower bound
        while lo < hi: 
            mid = (hi - lo) // 2 + lo
            if nums[mid] >= target:
                hi = mid
            else:
                lo = mid + 1
        return hi
```
```python
    def upper_bound_exclude(self, nums: List[int], target: int) -> int:
        lo, hi = 0, len(nums)

        # hi: lowest point > target (the result)
        # lo: given highest point <= target, +1 to obtain new lower bound
        while lo < hi: 
            mid = (hi - lo) // 2 + lo
            if nums[mid] > target:
                hi = mid
            else:
                lo = mid + 1
        return hi
```
```python
    def upper_bound_include(self, nums: List[int], target: int) -> int:
        upper_bound_exclude(nums,target) - 1
```
3. a unified template (thanks to @IvanLenn, and according to this post https://codeforces.com/blog/entry/9901)
- Usually the space of binary search is canonical (i.e. integers)
- We can find a property (function) $P$ and some integer $N$ such that $\forall n >= N$ this $$P(n)$$ is true and $\forall n < N$ this $$P(n)$$ is false. Based on the property, we ignore at least half of search space each time, which is crucial to binary search.

Therefore, in implementation we maintain two invariants:
- $l$​ is the **highest point** we know $$P$$ is true. (if such $l$​ doesn't exist define it to be left boundary - 1)
- $r$ is the **lowest point** we know $$P$$ is false. (if such $r$ doesn't exist define it to be right boundary + 1)

Then just copy this template and customize this property function:
```cpp
int l = lb - 1, r = rb + 1;
while (l + 1 < r) {
  int mid = l + (r - l) / 2;
  function<bool(int)> ok = [&](int mid) -> bool {
    // Implement me
  }
  if (ok(mid)) l = mid;
  else r = mid;
}
```