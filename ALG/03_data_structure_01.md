Data Structure - record data wisely and economically

## Stack
When requires Last In First Out pattern.
exercise: L946, L735, L301
## Queue


## Monotone data structures
### monotone stack

A typical example is to look for next strictly greater element
```python
res = [0] * n
monotone_stack = [] # stack invariant: monotonically decreasing

for i in range(len(nums) - 1, -1, -1):
    while len(monotone_stack) > 0 and nums[i] >= monotone_stack[-1]:
        monotone_stack.pop()
    
    if len(monotone_stack) == 0:
        res[i] = -1
    else:
        res[i] = monotone_stack[-1]
    
    monotone_stack.append(nums[i])
```
exercise: L503, L907, L42(requires a bit thought on breaking trap water down to each pop of the monotone stack)

### min/max queue
```cpp
void push(int val) {} // O(1)
void pop() {}         // O(1)
int top() {}          // O(1)
int getMin/Max() {}   // O(1) amortized
```
Hint: similar monotone stack in next greater element, when encounter a new element $$e$$,
we remove all element smaller than $$e$$ from monotone queue, since they can no
longer be max of the queue until we pop $$e$$. (Same idea as: when encounter a new
element $$e$$ in reversed order, all elements $$e' < e$$ cannot be next greater
value for all unvisited elements).
```
 queue              max queue
>( 2         )> || >( 2        )>
>( 3 2       )> || >( 3        )>
>( 1 3 2     )> || >( 1 3      )>
>( 4 1 3 2   )> || >( 4        )>  // 4 erase 1,3 since now until we pop 4, max must be 4
>( 0 4 1 3 2 )> || >( 0 4      )>  // 0 is stored since it is the max value after 4 pop
```
exercise: L239
solution:
```python
class MaxQueue:
    def __init__(self):
        self.queue = deque()
        self.max_queue = deque()

    def push(self, val: int) -> None:
        while len(self.max_queue) != 0 and self.max_queue[0] < val:
            self.max_queue.popleft()
        self.max_queue.appendleft(val)
        self.queue.appendleft(val)

    def pop(self) -> int:
        assert(len(self.queue) >= len(self.max_queue) > 0)
        if self.max_queue[-1] == self.queue[-1]:
            self.max_queue.pop()
        self.queue.pop()

    def get_max(self) -> int:
        assert(len(self.max_queue) > 0)
        return self.max_queue[-1]

class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        res = []
        left, right = 0, 0
        window = MaxQueue()

        while right < len(nums):
            window.push(nums[right])
            right += 1

            if right - left >= k:
                res.append(window.get_max())
                window.pop()
                left += 1

        return res
```

### min/max stack
min/max stack is simpler than monotone stack and min/max queue, there's no
cost analysis amortized by each element.
```cpp
void push(int val) {} // O(1)
void pop() {}         // O(1)
int top() {}          // O(1)
int getMin/Max() {}   // O(1)
```
Hint: implemented by two stacks, one maintaining the actual stack, another stack maintaining current min/max value of all sub-stack above. The 
For each new value $$e$$, we push into the S' iff $$e$$ change
the monotonic value (e.g. max, min). When we pop $$e'$$ from original stack, if 
$$e'$$ does not reside on top of S', then monotonic value is not 
effected; otherwise we also pop S' to obtain next monotonic value.
```
stack S           max stack S'
( 2           )< || ( 2        )<
( 2 3         )< || ( 2 3      )<
( 2 3 1       )< || ( 2 3      )<
( 2 3 3 1     )< || ( 2 3 3    )<
( 2 3 3 1 4   )< || ( 2 3 3 4  )<
( 2 3 3 1 4 0 )< || ( 2 3 3 4  )<
```

### min/max stack with O(log n) deletion of Min/Max value
```cpp
// extend interface of min/max stack with
void deleteMin/Max() {}
```
