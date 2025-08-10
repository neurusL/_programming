
### [Jump Game I](https://leetcode.com/problems/jump-game/description/)
You are given an integer array nums. You are initially positioned at the array's 
first index, and each element in the array represents your maximum jump length 
at that position.
Return true if you can reach the last index, or false otherwise.
```
Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
```
```
Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
```

Solution:
A brute solution tries all possible jumps and test if there's one falls on the last index.
But notice there are unnecessary work done here:
- (Dynamic Programming) it doesn't matter how we reach a point in this problem, but
only whether we can reach the point. Sub-problem is whether from 0 can reach i or not,
and recurrence is $$P[n] = \lor_{0}^{n-1} (P[i] \land \text{from $i$ can jump to $n$})$$
```python
    def canJump(self, nums: List[int]) -> bool: # O(n^2)
        n = len(nums)
        dp = [False] * n
        dp[0] = True

        for (i, jump) in enumerate(nums):
            if dp[i]:
                for j in range(i, min(n, i+jump+1)):
                    dp[j] = True
        
        return dp[n-1]
```
- (Greedy) we don't but only care about the farest point we can jump to: as long
as we can jump to a point further than last index, we could reach last index (can 
be proven by induction on steps made to index). Then,
```python
    def canJump(self, nums: List[int]) -> bool: # O(n)
        n = len(nums)
        max_point = 0

        for (i, jump) in enumerate(nums):
            if i > max_point:
                continue
            else:
                max_point = max(max_point, i + jump)
                if max_point >= n-1:
                    return True

        return False
```
exercise: slightly modify this to solve [Jump Game II](https://leetcode.com/problems/jump-game-ii/description/).
```python
    def jump(self, nums: List[int]) -> int:
        INT_MAX = 2 ** 31 - 1
        n = len(nums)
        dp = [INT_MAX] * n

        dp[0] = 0

        for (i, jump) in enumerate(nums):
            if dp[i] != INT_MAX:
                for j in range(i, min(n, i+jump+1)):
                    dp[j] = min(dp[j], dp[i] + 1)
        
        return dp[n-1]
```
```python
        # The starting range of the first jump is [0, 0]
        answer, n = 0, len(nums)
        cur_end, cur_far = 0, 0

        for i in range(n - 1):
            # Update the farthest reachable index of this jump.
            cur_far = max(cur_far, i + nums[i])

            # If we finish the starting range of this jump,
            # Move on to the starting range of the next jump.
            if i == cur_end:
                answer += 1
                cur_end = cur_far

        return answer

```