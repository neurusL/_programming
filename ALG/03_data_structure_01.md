Data Structure - record data wisely and economically

## Monotone stack and queue
The idea is to maintain monotone stack

A typical example is to look for next greater element
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
exercise: L503

- min/max stack:
```cpp
void push(int val) {} // O(1)
void pop() {}         // O(1)
int top() {}          // O(1)
int getMin/Max() {}   // O(1) amortized
```
Hint: implemented by two stacks, one maintaining the actual stack, another monotone stack maintaining current min/max value of all sub-stack above.
```
stack             max stack
( 2         )< || ( 2        )<
( 2 3       )< || ( 2 3      )<
( 2 3 1     )< || ( 2 3      )<
( 2 3 1 4   )< || ( 2 3 4    )<
( 2 3 1 4 0 )< || ( 2 3 4    )<
```

- min/max queue:
```cpp
void push(int val) {} // O(1)
void pop() {}         // O(1)
int top() {}          // O(1)
int getMin/Max() {}   // O(1) amortized
```
Hint: similar idea as above, one for actual queue, while another monotone queue keep track of current min/max value 
```
 queue              max queue
>( 2         )> || >( 2        )>
>( 3 2       )> || >( 3        )>
>( 1 3 2     )> || >( 1 3      )>
>( 4 1 3 2   )> || >( 4        )>  // 4 erase 1,3 since now until we pop 4, max must be 4
>( 0 4 1 3 2 )> || >( 0 4      )>  // 0 is stored since it is the max value after 4 pop
```

- min/max stack with O(log n) deletion of Min/Max value
```cpp
// extend interface of min/max stack with
void deleteMin/Max() {}
```