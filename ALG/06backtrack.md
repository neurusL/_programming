
## Backtracking 
### combination sum
Let's first consider the classic combination sum problem, where given a list of candidates and a target, output combinations of candidates such that they sum up to be target number.  
Here's a typical backtracking solution (bruteforce)
- version [each element can be used unlimited times]
```python
def combinationSum(candidates: List[int], target: int) -> List[List[int]]:
    # candidates are distinct
    combinations = []
    def backtrack(acc: List[int], start: int, target: int):
        if target < 0:
            return
        if target == 0:
            combinations.append[acc[:]] # deep copy
        else:
            for i in range(start, len(candidates)):
                acc.append(candidates[i])
                backtrack(acc, i, target - candidates[i])
                acc.pop()
    
    backtrack([], 0, target)
    return combinations

``` 
- note: if ```candidates``` contain duplicate elements, but you only want to return
unique lists, here's a counter example: ```[1, 2, 3, 1, 1, 4, 5]```.
A small change of above solution is needed:
```python
+++         candidates.sort() #(*)
            ...
            for i in range(start, len(candidates)):
+++             # consider 1 once is okay, skip all the others
+++             # (*) allow us to skip consecutively
+++             for i != start and candidates[i] == candidates[i-1]:
+++                 continue
+++             # exercise: add a small optimization here
+++             # do we need to keep backtracking when candidates[i] > target?
+++             # given (*) we sort candidates ahead of time
                acc.append(candidates[i])
                backtrack(acc, i+1, target - candidates[i])
                acc.pop()
```
- note: each element can be used at most once
```python
+++             backtrack(acc, i+1, target - candidates[i])
``` 
