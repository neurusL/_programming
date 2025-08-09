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