## Off by One
The note provides some common error of index off by one, and related functions.

### lower and upper bound
```i = bisect_left(arr, x)``` can be think of as the first insertion point in sorted ```arr```
for ```x``` to maintain sorted order, i.e. for all ```j < i```, ```arr[j] < x```;
and for all ```j >= i```, ```arr[j] >= x```.

```i = bisect_right(arr, x)``` can be think of as the last insertion point in sorted ```arr```
for ```x``` to maintain sorted order, i.e. for all ```j < i```, ```arr[j] <= x```;
and for all ```j >= i```, ```arr[j] > x```.

```python
arr = [1, 3, 3, 3, 3, 5, 7, 9]
#         ^[1,        ^5)  
print(bisect.bisect_left(arr, 2)) # idx = 1
print(bisect.bisect_right(arr, 2)) # idx = 1

print(bisect.bisect_left(arr, 3)) # idx = 1
print(bisect.bisect_right(arr, 3)) # idx = 5
```
So, when ```x not in  arr```, ```bisect_left``` and ```bisect_right``` return the 
same index, since there is only one place to insert the element.
When ```x in arr```, ```arr[[bisect_left, bisect_right)]``` are all ```x```. 

And some common uses:
| <!-- --> | <!-- --> |
| -- | -- |
| lowest point > x | ```bisect_right(arr, x)``` |
| lowest point >= x | ```bisect_left(arr, x)``` |
| highest point < x | ```bisect_left(arr, x) - 1``` |
| highest point <= x | ```bisect_right(arr, x) - 1``` |
***don't forget boundary check here***

exercise: L981, L1146
```python
class SnapshotArray:
    """Implement array-like data structure together with snapshot of versions"""
    """ approch 1: naively record whole array for each snapshot """
    # def __init__(self, length: int):
    #     self.arr = [0] * length
    #     self.next_snap_id = 0
    #     self.snaps = {}

    # def set(self, index: int, val: int) -> None:
    #     self.arr[index] = val

    # def snap(self) -> int:
    #     id = self.next_snap_id
    #     self.snaps[id] = self.arr[:] # make sure not aliasing
    #     self.next_snap_id += 1

    #     return id

    # def get(self, index: int, snap_id: int) -> int:
    #     if snap_id not in self.snaps:
    #         raise Exception("cannot find key")
    #     else:
    #         snapshot_arr = self.snaps[snap_id]
    #         return snapshot_arr[index]

    """ approach 2: for each index, record new value with it's earliest snapshot id """
    def __init__(self, length: int):
        self.arr = [0] * length
        self.next_snap_id = 0
        self.snaps = [[] for _ in range(length)] # to avoid aliasing

    def set(self, index: int, val: int) -> None:
        self.arr[index] = val
        self.snaps[index].append((self.next_snap_id, val))

    def snap(self) -> int:
        id = self.next_snap_id
        self.next_snap_id += 1

        return id


    def get(self, index: int, snap_id: int) -> int:
        # print(index)
        i_snap = self.snaps[index]
        i_snap_idx = bisect.bisect_right(i_snap, snap_id, key=lambda x: x[0]) - 1 # bisect off by one
        if i_snap_idx < 0:
            return 0
        else:
            return i_snap[i_snap_idx][1]
```