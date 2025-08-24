Data Structure - record data wisely and economically
## Tree iteration

exercises:  
[L114](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/?envType=study-plan-v2&envId=top-interview-150)  
[L173](https://leetcode.com/problems/binary-search-tree-iterator/?envType=study-plan-v2&envId=top-interview-150)


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