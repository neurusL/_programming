# c++ basic algorithm cheatsheet -- sort, graph

## Two Pointer and Sliding Window


## Binary Search
As one of the common scenes in algorithms, in Binary Search we exclude search space
(at least half of search space) each search:

Danny Sleator's ***best*** binary search template:

Problems that can be solved with binary search need to have the following property:

- Usually the space of binary search is canonical (i.e. integers)
- We can find a property (function) $f$ and some integer $N$ such that $\forall n >= N$ this property is true and $\forall n < N$ this property is false.

Therefore, in implementation we maintain two invariants:

- $l$​ is the right most point we know such that this property is true. (if such $l$​ doesn't exist define it to be left boundary - 1)
- $r$ is the left most point we know such that this property is false. (if such $r$ doesn't exist define it to be right boundary + 1)

Then just copy this template and customize this property function:

```cpp
int l = lb - 1, r = rb + 1;
while (l + 1 < r) {
  int mid = l + (r - l) / 2;
  function<bool(int)> ok = [&](int mid) -> bool {
    // Implement me
  }
  if (ok(mid)) l = mid;
  else r = mid;
}
```

Example: given a sorted vector $v$ in non-decreasing order, find the greatest index $x$ such that $v[x] < K$ or state it does not exist.

```cpp
// Suppose have v as vector
int l = -1, r = (int)v.size();
while (l + 1 < r) {
  int mid = l + (r - l) / 2;
  auto ok = [&](int mid) {
    return v[mid] < K;
  };
  if (ok(mid)) l = mid;
  else r = mid;
}
if (l == -1) std::cout << "Do not exist" << std::endl;
else std::cout << l << std::endl;
```

Special case: what if the binary search space is float? Do not use while loop in this case. Use for loop instead.

Example: find $x$ such that $x$ is no more then $10^{-6}$ away from $\sqrt3$.

```cpp
double l = 0, r = 2;
int iteration = 40; // The bigger this number the more accurate answer is
for (int i = 0; i < iteration; i++) {
double mid = (l + r) / 2;
auto ok = [&](double mid) {
    return mid * mid < (double)3;
};
if (ok(mid)) l = mid;
else r = mid;
}
std::cout << setprecision(10) << fixed << r << ' ' << sqrt(3) << std::endl;
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

## DFS
implementation by recursion:
```cpp
void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {
    // Mark the current node as visited
    visited[node] = true;

    // Visit all adjacent nodes
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
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

## DFS based algorithms 

DFS can be generalized to different algorithms, and idea behind is the DFS tree:
After DFS, a graph can be partitioned into three different types of edeges:
for (u, v), denote its visit and finish time for u to be u_s, u_t,
- (u, v) forward edge (in DFS tree) iff u_s < v_s < v_t < u_t
- (u, v) backward edge (DFS tree node pointing back to ancestor) iff v_s < u_s < u_t < v_t
- (u, v) cross edge iff no intersection between [u_s, u_t] and [v_s, v_t]

### Cycle Detection 
Observe that cycle exists iff there is backward edge after DFS.
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
// a note for undirected graph: check neighbor not to be parent, otherwise in
// adjacency list representation of undirected graph, there's always a cycle
```
### Topological Sort on DAG
Observe that for any u reach v, v finishes before u in any DFS:
a proof sketch is casing on the order we visit u, v: if first visit u, then before finishing u, we must visit and finish v; else, since in DAG v cannot reach u, then v finishes before we start visiting u.
Then toposort simply outputs nodes in reversed finishing time.

```cpp
void dfs(int v, vector<vector<int>>& graph, vector<bool>& visited, stack<int>& topoStack) {
    visited[v] = true;
    // Visit node v
    for (auto n : graph[v]) {
        if (!visited[n]) { dfs(neighbor, adj, visited, topoStack); }
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

