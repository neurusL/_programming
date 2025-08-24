Data Structure - record data wisely and economically

## Hashing based and improved data structure
HashMap provides average O(1) time read and write to key's value. But sometimes
we would like to keep more information:
### LinkedHashMap (OrderedDict/unordered_map/...)
- keep insertion order of (key, value) pairs (notice, usually iterating through a
hashmap(or hashset) is undeterministic)
```cpp
void put(Key k, Value v) {} // O(1)
Value get(Key k) {}         // O(1)
void delete(Key k) {}       // O(1)
Iterator<Pair<Key,Value>> iterate() {}   
```
Hint: a hashmap with double linked list
```python
class Node:
    def __init__(self, key: int, val: int):
        self.key = key
        self.value = val
        self.prev = None
        self.next = None

class LRUCache:

    def __init__(self, capacity: int):
        self.capacity = capacity

        # map from key to node 
        self.map = {}

        # double linked list for order(timestamp) of key, value pairs
        self.head = Node(-1, -1)  # dummy head 
        self.tail = Node(-1, -1)  # dummy tail
        self.head.next = self.tail
        self.tail.prev = self.head
    
    def add(self, node: Node):
        """append node to the end of double linked list"""
        last_node = self.tail.prev
        # between last node and node
        last_node.next = node
        node.prev = last_node
        # between node and tail dummy node
        node.next = self.tail
        self.tail.prev = node

    def remove(self, node: Node):
        node.prev.next = node.next # dummy head avoid casing on this
        node.next.prev = node.prev # dummy tail avoid casing on this
        # for a single direction linked list
        # only need dummy head

    def get(self, key: int) -> int:
        if key not in self.map:
            return -1
        
        node = self.map[key]
        self.remove(node)
        self.add(node)

        return node.value

    def put(self, key: int, value: int) -> None:
        if key in self.map:
            node = self.map[key]
            self.remove(node)
        
        new_node = Node(key, value)
        self.add(new_node)
        self.map[key] = new_node

        if len(self.map) > self.capacity:
            evict = self.head.next
            self.remove(evict)
            del self.map[evict.key]
```

### RandomizedSet

L380

## Tree (balanced) based data structure
### Tree Map (SortedDict/map/...)
Compared to hashmap, tree map is sorted by key (which requires keys are total ordered).
And tree is usually implemented by balanced tree algorithms: AVL/Red-Black/B/Splay tree
```cpp
void put(Key k, Value v) {} // O(log n)
Value get(Key k) {}         // O(log n)
void delete(Key k) {}       // O(log n)
auto range_query(Key k1, Key k2) {} // O(log n) + O(|k2 - k1|), see iterating a tree by stack
Iterator<Pair<Key,Value>> iterate() {}   
```