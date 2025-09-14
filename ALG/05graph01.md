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
