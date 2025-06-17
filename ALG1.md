# c++ basic algorithm cheatsheet -- sort, graph

## Two Pointer and Sliding Window
### two pointer
### scenario of use: remove elements satisfying property $$P$$ from array in place:
```python
def p(x: int) -> bool: # this can be generalized to any p
    return x == 0
    
def moveZeroes(self, nums: List[int]) -> None:
        """ remove 0 to the end of array
        method 1: (when we want to keep relative order)
            keep a pointer of next to write, and another iterator pointer
            when iterator pointer encounter a satisfying element, write 
            to the writer pointer
        method 2: (when there's no need to keep relative order, 
                   and target element is less frequent)
            keep a pointer starting from end pointint to a non-target
            another iterator pointer 
        """
        right = len(nums)-1  # to record right most idx where P is not true
        left = 0             # to record left most idx where P is true
        
        # both points to nowhere when initialized

        while left <= right:
            if p(nums[right]):
                right -= 1
            else:
                if p(nums[left]):
                    swap(nums[left], nums[right])
                left += 1

        return left
        # todo!("I hope there's a more generalizable and formal template for this")

```
Two types of sliding window;
```
left = 0; right = 0;
```
```
left = 0; right = vector.size();
```

## Binary Search
As one of the common scenes in algorithms, in Binary Search we exclude search space
(at least half of search space) each search:
```cpp
int binsearch(vector<int>& nums, int left, int right, int target) {
    int l = left;
    int r = right;
    while (l <= r) {
        int mid = (r - l) + l / 2;  // avoid overflow
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1; 
}
```


## Sort

```cpp
vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
// Sort in ascending order
sort(vec.begin(), vec.end());

// Sort based on first element
vector<pair<int, int>> vec = {{3, 40}, {1, 20}, {4, 50}, {2, 30}};
sort(vec.begin(), vec.end(), [](const pair<int, int>& a, const pair<int, int>& a) { 
    return a.first < b.first; })

// Sort index vector based on original vector
vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
vector<int> vec_idx(vec.size());
iota(vec_idx.begin(), vec_idx.end(), 0);

sort(vec_idx.begin(), vec_idx.end(), [&vec](int i, int j){ return vec[i] < vec[j]; })
```

### application: lower_bound / upper_bound in C++
```cpp
// input lower/upper_bound collection must be sorted
std::vector<int> v = {10, 20, 30, 40, 50};
auto it = std::lower_bound(v.begin(), v.end(), 30);
if (it != v.end()) {
    std::cout << "Lower bound of 30 is: " << *it << "\n";       // Output: 30
}
auto it = std::upper_bound(v.begin(), v.end(), 30);
if (it != v.end()) {
    std::cout << "Upper bound of 30 is: " << *it << "\n";       // Output: 40
}
```

### quickselect, quicksort

```cpp
    int partition(vector<int>& nums, int p, int l, int r) {
        // in place partition nums s.t. all lefts > nums[p]
        int pivot = nums[p];
        std::swap(nums[p], nums[r]);
        int idx = l;
        for (int i = l; i < r; i++) {
            if (nums[i] > pivot) {
                swap(nums[i], nums[idx]); // in place swap
                idx++;
            }
        }
        swap(nums[idx], nums[r]);
        return idx;
    }
    
    int quickSelect(vector<int>& nums, int left, int right, int k) {
        // the base case here is redundant, without it quickSelect is still proven
        // to be terminated with proper left, right
        if (left == right) return nums[left]; 

        // we rely on better randomness, this may not be a good one
        int p = rand() % (right - left + 1) + left;
        // assert(p >= left && p <= right);
        int pivotIndex = partition(nums, p, left, right);

        if (k == pivotIndex) return nums[k];
        else if (k < pivotIndex) return quickSelect(nums, left, pivotIndex - 1, k);
        else return quickSelect(nums, pivotIndex + 1, right, k);
    }

    int kthElement(vector<int>& nums, int k) {
        return quickSelect(nums, 0, nums.size()-1, k-1);
    }

```

### ```std::sort```

## DFS
implementation by recursion:
```cpp
void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {
    if(visited[node]) {
        // do stuff here
        return; 
    }

    // Mark the current node as visited
    visited[node] = true;
    // Visit all adjacent nodes
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) { // and other guards here
            dfs(neighbor, graph, visited);
        }
    }
}

void dfsall(graph){
    for (int i = 0; i < numNodes; i++) {
        if (!visited[i]) {
            dfs(i, graph, visited);
        }
    }
}
```
implementation by iteration, where stack store the next nodes to visit:
```cpp
void dfs(int node, vector<vector<int>>& graph) {
    vector<bool> visited(n, false);
    stack<int> stack;
    
    stack.push(node);
    visited[node] = true;
    while (!stack.empty()) {
        int curr = stack.top();
        stack.pop(); 

        for (auto n : graph[curr]) {
            if (!visited[n]) { 
                stack.push(n); 
                visited[node] = true;
            }
        }
        
    }
}

void dfsall(graph) { }
```

## BFS 
BFS has similar implementation as stack based DFS, they are esstentially same except for the data structure which maintains next nodes to visit:
```cpp
void bfs(int node, vector<vector<int>>& graph) {
    vector<bool> visited(n, false);
    queue<int> queue;

    queue.push(node);
    while(!queue.empty()) {
        int curr = queue.pop();

        for (auto n : graph[curr]) {
            if (!visited[n]) { 
                queue.push(n); 
                visited[curr] = true;
            }
        }
    }
}
```
stack based DFS and queue based BFS are in general worklist algorithms, where worklist maintain a frontier of nodes we are exploring of the graph. Whatever in the worklist should be tag as visited. 
Exercise: think about why the following code fail, do we visit node only once?
```cpp
void bfs(int node, vector<vector<int>>& graph) {
    vector<bool> visited(n, false);
    queue<int> queue;

    queue.push(node);
    while(!queue.empty()) {
        int curr = queue.pop();
        visited[curr] = true; // <---- why not?

        for (auto n : graph[curr]) {
            if (!visited[n]) {
                queue.push(n);
            }
        }
    }
}

void dfs(int node, vector<vector<int>>& graph) {
    vector<bool> visited(n, false);
    stack<int> stack;

    stack.push(node);
    while(!stack.empty()) {
        int curr = stack.top();
        stack.pop();
        visited[curr] = true; // <---- why not?

        for (auto n : graph[curr]) {
            if (!visited[n]) {
                stack.push(n);
            }
        }
    }
}
```

## DFS based algorithms 

DFS can be generalized to different algorithms, and idea behind is the DFS tree:
After DFS, based on the DFS traversal tree, a graph can be partitioned into three different types of edeges:
for (u, v), denote its visit and finish time for u to be u_s, u_t,
- (u, v) forward edge (in DFS traversal tree) iff u_s < v_s < v_t < u_t
- (u, v) backward edge (DFS tree node pointing back to ancestor) iff v_s < u_s < u_t < v_t, where v is visited before u but v finished after u
- (u, v) cross edge iff no intersection between [u_s, u_t] and [v_s, v_t]

### Cycle Detection 
Observe that cycle exists iff there is backward edge after DFS. Alternatively, if there's an edge (u, v) where v is visited before u, but v hasn't finish it DFS call, then a cycle detected.
```cpp
bool hasCycle(vector<vector<int>>& graph, int c, vector<bool>& visited, vector<bool>& finished) {;
    if (visited[c]) {
        if (!finished[c]) {
            // backward edge
            return true;
        }
        // otherwise cross edge
        return false;
    } else {
        visited[c] = true;
        for (auto neigb : graph[c]) {
            if (hasCycle(graph, neigb, visited, finished)) {
                return true;
            }
        }
        finished[c] = true;
        return false;
    }
}
```
The same algorithm will output false positive of cycles in undirected graph, which represented by bidirected graph. Since each edge is a implicit cycle now, we need to first record the DFS traversal tree, say in some HashMap, to avoid detecting (u, v) and (v, u) as a cycle.

### Topological Sort on DAG
Observe that for any u reach v, v finishes before u in any DFS:
a proof sketch is casing on the order we visit u, v: if first visit u, then before finishing u, we must visit and finish v; else, since in DAG v cannot reach u, then v finishes before we start visiting u.
Then toposort simply outputs nodes in reversed finishing time.

```cpp
void dfs(int v, vector<vector<int>>& graph, vector<bool>& visited, stack<int>& topoStack) {
    visited[v] = true;
    // Visit node v
    for (auto n : graph[v]) {
        if (!visited[n]) { dfs(n, adj, visited, topoStack); }
    }
    // Finish node v
    topoStack.push(v);
}
void dfsall ...
// all essentially same as DFS but maintaining a topoStack!
```

### Strongly Connected Components and Tarjan's Index


## More Shortest Path
### Priority First Search
Actually BFS and DFS are special cases of priority first search, as well as the Dijkstra's algorithm to find shortes path for non-negative weighted graph, where it's priority is:
min_{y in frontier} p(y), where p(y) = min_{x in X}(p(s, x) + w(x, y)).
The rationale behind is, fix already searched set X, it's frontier Y, a shortest path from s in X to y in Y must pass through frontier, and for the y with minimum p(y), we know we already obtain the shortest path: AFSOC not shortest path, i.e. another path passing through different point y' in Y, then length(s, y') > length(s, y), contradicting with shortest path given all edges are positive.
### Dijkstra's Algorithm
```cpp
typedef pair<int, int> pii; // (node, weight)
void dijkstra(vector<vector<pii>>& graph, int start) {
    int n = graph.size();
    vector<int> p(n, INT_MAX);
    priority_queue< pii, vector<pii>, greater<pii> > pq;

    p[start] = 0;
    pq.push({0, start});

    while(!pq.empty()) {
        int curr = pq.top().first; // curr := min_{x in X}(p(s, x) + w(x, y))
        int u = pq.top().second;
        pq.pop();

        // if visited already, equivalently, we obtained shortest path already
        if (curr > p[u]) continue; 

        for (auto& nb : graph[u]) {// relax: only effects nodes neighboring u
            int v = nb.first;
            int w = nb.second;
            if (p[u] + w < p[v]) { // only add better results
                p[v] = p[u] + w;   
                pq.push({p[v], v});// add to pq
            }
        }
    }
}
```

### A*

## Dynamic Programming on graph
### Bellman-Ford

### Warshall-Floyd



## Minimal Spanning Tree 
### Prim's Algorithm

### Kruskal's Algorithm
Idea: sort edges' weights, based on which we add (u, v) to MST if either u or v not in MST yet.
We need wise data structure to maintain current MST
```cpp

int kruskal(vector<int, pair<int, int> >& edges) {

// union find for Kruskal
int n = graph.size();
vector<int> parents(n);
vector<int, pair<int, int> > graph;

function<int(int)> find = [&](int x) -> int {
    if ()
}



void union(int a, int b) {
    int p1 = find(a);
    int p2 = find(b);
    root[p1] = root[p2];
}


    int E = graph.size();
    int cost = 0;
    sort(graph.begin(), graph.end());
    for (int i = 0; i < E; i++) {
        int w = graph[i].first;
        int u = graph[i].second.first;
        int v = graph[i].second.second;
        if (find(u) != find(v)) {
            cost += w;
            union(u, v);
        }
    }
    return cost;
}

```

