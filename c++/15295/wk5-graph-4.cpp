#include <bits/stdc++.h>
#include <iostream>
#include <queue>

using namespace std;

// void dfs(vector<vector<int> >& tree, int node, 
//         vector<int>& min0, vector<int>& min1, vector<bool>& ons) {
//     int numchild = tree[node].size();
//     if (numchild == 0) {
//         if (ons[node]) {
//             min1[node] = 0;
//             min0[node] = 1;
//         } else {
//             min1[node] = 1;
//             min0[node] = 0;
//         }
//     } else if (numchild == 1) {
//         int child = tree[node][0];
//         dfs(tree, child, min0, min1, ons);
//         if (ons[node]) {
//             min1[node] = min1[child];
//             min0[node] = min1[child] + 1;
//         } else {
//             min1[node] = min0[child] + 1;
//             min0[node] = min0[child]; 
//         }
//     } else {
//         int child1 = tree[node][0];
//         int child2 = tree[node][1];
//         dfs(tree, child1, min0, min1, ons);
//         dfs(tree, child2, min0, min1, ons);
//         if (ons[node]) {
//             min1[node] = min1[child1]+min1[child2];
//             min0[node] = min1[child1]+min1[child2] + 1;
//         } else {
//             min1[node] = min0[child1]+min0[child2] + 1;
//             min0[node] = min0[child1]+min0[child2]; 
//         }
//     }
// }

// int main() {
//     // topo sort to identify root // actually root's parent is itself
//     int n, q;
//     cin >> n >> q;

//     vector<vector<int> > tree(n+1); // nodes 1..n
//     int root = 1;
//     for (int i = 2; i <= n; i++) {
//         int pi; 
//         cin >> pi;
//         tree[pi].push_back(i);
//     }

//     // observation: order of toggle doesn't matter, and each node will be toggled
//     // at most once, so let's simply test toggle or not
//     // backtrack starting at root, wisely by dp:
//     // for each node:
//         // min number to make subtree all 1, min1, similarly min0
//         // if node's val = 0
//         // min1 = left's min0 + right's min0 + 1
//         // min0 = left's min0 + right's min0
//         // if node's val = 1
//         // min1 = left's min1 + right's min1 
//         // min0 = left's min1 + right's min1 + 1
//     for (int i = 0; i < q; i++) {
//         vector<int> min0(n+1, INT_MAX);
//         vector<int> min1(n+1, INT_MAX);

//         vector<bool> ons(n+1, false);
//         int mi;
//         cin >> mi;
//         for (int i = 1; i <= mi; i++){
//             int vi;
//             cin >> vi;
//             ons[vi] = true;
//         }
//         dfs(tree, root, min0, min1, ons);
//         cout << min0[root] << endl;
//     }
    
//     return 0;
// }

// follow up:
// above solution is O(n * q)
// another key observation is: #nodes to flip = #nodes with color different from its parent

int main() {
    // topo sort to identify root // actually root's parent is itself
    int n, q;
    cin >> n >> q;

    vector<int> parents(n+1, -1);
    vector<int> child;
    parents[1] = 1;
    for (int i = 2; i <= n; i++) {
        int pi; cin >> pi;
        parents[i] = pi;
    }

    for (int i = 0; i < q; i++) {
        vector<bool> lights(n+1, 0);
        vector<int> ons;
        int mi;
        cin >> mi;
        for (int i = 1; i <= mi; i++){
            int vi; cin >> vi;
            lights[vi] = 1;
            ons.push_back(vi);
        }
        
        int cnt = 0;
        for (int vi : ons){
            if(vi == 1 || lights[parents[vi]] == 0 || ???) {
                cnt++;
            }
        }
        cout << cnt << endl;
    }
    
    return 0;
}