#include <bits/stdc++.h>
#include <iostream>
#include <queue>

using namespace std;

void dfs(vector<vector<int> >& graph, int node, vector<bool>& visited) {
    visited[node] = true;

    for (int n : graph[node]) {
        if (!visited[n]) {
            dfs(graph, n, visited);
        }
    }
}

int main() {
    /*
    idea: brute force, but guaranteed to terminate in O((n+m)log n)
    observation: gcd(k, n) = 1 then adding edges between i and i+k mod n willf 
    connect all nodes, then smallest prime coprime with n must be in O(log n)
    
    */
    // also graph is not dense
    int N;
    cin >> N;
    for (int i =0; i < N; i++){
        int n, m;
        cin >> n >> m;
        vector<vector <int> > graph(n); 
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        for (int k = 2; k < n; k++){
            vector<vector<int> > newgraph = graph; // deep copy
            for (int i = 0; i < n; i++) {
                int u = i;
                int v = (i+k) % n;
                newgraph[u].push_back(v);
                newgraph[v].push_back(u);
            }

            // now do dfs from arbitrary node, if all visited then all connected
            vector<bool> visited(n, false);
            dfs(newgraph, 0, visited);

            bool flag = true;
            for (bool b : visited) {
                // cout << k << " visited? " << b << endl;
                if (!b) { flag = false; }
            }
            if (flag) { cout << k << endl; break; }
            else { continue; }
        }
    }
    return 0;
}