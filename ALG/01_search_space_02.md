# Chapter 01: Search Space
- two pointer 
- sliding window
- binary search

## When search space can be pruned...

## 3. by reducing half of search space
### scenario 1: when the data structure is highly ordered, e.g. a sorted array, or a circular sorted array
The idea of Binary Search is straight forward: whenever you probe an element $$e$$ in a space which is highly ordered w.r.t property $$P$$, based on $$P(e)$$, we ignore all elements $$e'$$ s.t. $$e' < e$$ or $$e' > e$$.
The hairy details on boundaries require careful reasoning, see comments in between lines.

Here're some templates of binary search on 1d array:
1. search for an element in array
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
2. search for $$e$$'s lower bound (first element $$\geq e$$) and upper bound (first element $$>e$$)
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
- We can find a property (function) $P$ and some integer $N$ such that $\forall n \geq N$ this $$P(n)$$ is true and $\forall n < N$ this $$P(n)$$ is false. Based on the property, we ignore at least half of search space each time, which is crucial to binary search.

Therefore, in implementation we maintain two **invariants**:
- $l$​ is the **highest point** we know $$P$$ is true. (if such $l$​ doesn't exist define it to be left boundary - 1)
- $r$ is the **lowest point** we know $$P$$ is false. (if such $r$ doesn't exist define it to be right boundary + 1) 

With these invariants, it's trivial to prove the correctness of the template without hairy details on off by one. (coming up with these invariants isn't a trival thing!) Then just copy this template and customize this property function:
```cpp
int l = left_bound - 1, r = right_bound + 1; // (l,r) is an open interval
while (l + 1 < r) { 
  int mid = l + (r - l) / 2;
  function<bool(int)> ok = [&](int mid) -> bool {
    // Implement me
  }
  if (ok(mid)) l = mid;
  else r = mid;
}
```
example of uses (unified and clean!):
```python
    def lower_bd(nums: List[int], target: int) -> int:
        """
        lowest point >= target is true
        postcondition: bisect_left(nums, target, in [ 0, len(nums) ))
        """
        lo = -1 # highest point < target
        hi = len(nums) # lowest point >= target

        while lo + 1 < hi:
            mid = (hi-lo)//2 + lo
            if nums[mid] < target:
                lo = mid
            else:
                hi = mid
        
        return hi
    
    def upper_bd_inclusive(nums: List[int], target: int) -> int:
        """
        highest point <= target is true
        """
        lo = -1 # highest point <= target
        hi = len(nums) # lowest point > target

        while lo + 1 < hi:
            mid = (hi-lo)//2 + lo
            if nums[mid] <= target:
                lo = mid
            else:
                hi = mid
        
        return lo
    
    def upper_bd(nums: List[int], target: int) -> int:
        """
        lowest point > target is true
        postcondition: bisect_right(nums, target, in [ 0, len(nums) ))
        """
        lo = -1 # highest point <= target
        hi = len(nums) # lowest point > target

        while lo + 1 < hi:
            mid = (hi-lo)//2 + lo
            if nums[mid] <= target:
                lo = mid
            else:
                hi = mid
        
        return hi
```
exercise: L33, L4

### scenario 2: highly ordered search space can be implicit
For example, when the solution can only be integers with a bounded range, and we can eliminate at least half of answers each search, we can apply binary search with your customized ```ok``` there. When you have a feeling that answer can be tried oscillating around and converge to a final answer, then binary search is a good trial.
exercise: L875