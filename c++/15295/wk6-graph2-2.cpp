#include <bits/stdc++.h>
#include <iostream>
#include <queue>

using namespace std;

bool dfs(vector<vector<int> >& graph, int parent, int node, vector<bool>& visited, vector<bool>& finished) {
    if (graph[node].size() > 2) {
        return false;
    }
    if (visited[node]) {
        if (!finished[node]) { return false; }  
        return true;
    }
    
    visited[node] = true;
    for (int n : graph[node]) {
        if (n != parent && !dfs(graph, node, n, visited, finished)) { return false; }
    }
    finished[node] = true;
    return true;
}

int main() {
    // idea: the graph can only be chains (all node deg <= 2 and no cycle)
    // int N, M;
    // cin >> N >> M;
    // vector<int> nodes(N, 0);

    // for (int i = 0; i < M; i++) {
    //     int ai, bi;
    //     cin >> ai >> bi;
    //     nodes[ai]++;
    //     nodes[bi]++;
    //     if (nodes[ai] > 2 || nodes[bi] > 2) {
    //         cout << "No";
    //         return 0;
    //     }
    // }
    // cout << "Yes";

    int N, M;
    cin >> N >> M;
    vector<vector<int> > graph(N+1);

    for (int i = 0; i < M; i++) {
        int ai, bi;
        cin >> ai >> bi;
        graph[ai].push_back(bi);
        graph[bi].push_back(ai);
    }
    
    vector<bool> visited(N+1, false);
    vector<bool> finished(N+1, false);

    for (int i = 1; i <= N; i++) {
        if (visited[i]) { continue; }
        else { 
            if (!dfs(graph, -1, i, visited, finished)) {
                // cout << i << endl;
                cout << "No";
                return 0;
            }
        }
    }
    cout << "Yes";
    return 0;
}