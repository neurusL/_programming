## [Greedy Algorithm](https://usaco.guide/CPH.pdf#page=67)

Let's first walk through an example first: [Min Cost to Connect Sticks](https://leetcode.com/problems/minimum-cost-to-connect-sticks/description/)
```python
    def connectSticks(self, sticks: List[int]) -> int:
        """
        key greedy observation:
        - Choose two shortest stick to connect at any time
        - Intuitively, eariler we connect two sticks, more likely their weight
          is larger in final cost. So at early stage, let's choose shortest sticks
        """
        heapify(sticks)

        cost = 0
        while len(sticks) > 1:
            stick1 = heappop(sticks)
            stick2 = heappop(sticks)

            new_stick = stick1 + stick2
            cost += new_stick

            heappush(sticks, new_stick)

        return cost

```
A rigorous proof follows here: https://stackoverflow.com/questions/43715207/how-to-prove-this-greedy-algorithm-as-optimal-rod-connection 
The algorithm essentially brings the idea of Hoffman coding.


exercises:  
L45,  
L135,  
L435 (non-overlapping intervals, where we greedily remove interval with larger right boundary),  
L670,  

note: greedy algorithms are usually come with a data structure that supports retreiving the greedy choice efficiently (based on some order) -- heap.

note: while greedy algorithms require insightful observation and non-trivial proofs why local optimal choices lead to global optimal solution, it's relatively easy to 
recognize cases where your greedy algorithms won't work: *when problem need ***full search space exploration***, when local optimal choices ***effect later choices****.  
Interesting enough, coin system is a perfect example exploring the boundary between
a greedy solution and a full exploration solution (but can be optimized with dynamic programming). Check the post: https://stackoverflow.com/questions/63759434/greedy-algorithm-criteria-for-a-coin-system-to-be-canonical




exercise solution:
```python
# L670
    def maximumSwap(self, num: int) -> int:
        """
        idea1: look for first digit whose ranking is different than its position
        (the idea is partially correct, think about how to eliminate buggy idea at first place during an interview, before proceeding to implementation)
        idea2: look for first digit (from left to right, since significance of digit matters the most) that we can increase, then think about how to alter the digit:
        the solution becomes obvious: change first such digit with max digit right of it
        """
        # first process input
        digits = list(str(num))
        n = len(digits)
        right_max = [(-1, -1)] * n # (index, digit)
        right_max[n-1] = (n-1, int(digits[n-1]))

        # then calculate max number to the right of each digit, via suffix max
        for i in range(n-2, -1, -1):
            d = int(digits[i])
            if d <= right_max[i+1][1]: # second index matter!
                right_max[i] = right_max[i+1]
            else:
                right_max[i] = (i, d)
        
        # print(right_max)

        # look for first digit less than right max and swap it with right max
        for i in range(n):
            d = int(digits[i])
            if d < right_max[i][1]:
                j = right_max[i][0]
                # swap i, j
                digits[i], digits[j] = digits[j], digits[i]
                
                return int("".join(digits))

        return num
```