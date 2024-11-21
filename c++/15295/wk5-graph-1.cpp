#include <bits/stdc++.h>
#include <iostream>
#include <queue>

using namespace std;

// void bfs(int node, vector<vector<int>>& graph) {
//     vector<bool> visited(n, false);
//     queue<int> queue;

//     queue.push(node);
//     while(!queue.empty()) {
//         int curr = queue.pop();
//         visited[curr] = true;

//         for (auto n : graph[curr]) {
//             if (!visited[n]) { queue.push(n); }
//         }
//     }
// }

int main() {
    // construct a graph (h * w) nodes
    // node(row, col) has tag (row * w + col)
    int h, w; 
    cin >> h >> w;

    queue<int> q;
    vector<bool> visited(h*w, false);
    vector<int> dist(h*w, -1);

    // starting bfs from # positions 
    for (int i = 0; i < h; i++) {
        string line;
        cin >> line;
        for (int j = 0; j < w; j++) {
            if (line[j] == '#') {
                q.push(i*w+j);
                dist[i*w+j] = 0;
                visited[i*w+j] = true;
            }
        }
    }

    while(!q.empty()) {
        // cout << "loop" << endl;
        int curr = q.front();
        int d = dist[curr];

        q.pop();

        int row = curr / w;
        int col = curr % w;

        bool up = row > 0;   bool down = row < h-1;
        bool left = col > 0; bool right = col < w-1;
        int iu = curr-w;     int id = curr+w;
        int ir = curr+1;     int il = curr-1;
        int iur = curr-w+1;
        int iul = curr-w-1;
        int idr = curr+w+1;
        int idl = curr+w-1;

        if (left && !visited[il]) {
            q.push(il); dist[il] = d+1; visited[il] = true;
        } 
        if (right && !visited[ir]) {
            q.push(ir); dist[ir] = d+1; visited[ir] = true;
        } 
        if (down && !visited[id]) {
            q.push(id); dist[id] = d+1; visited[id] = true;
        } 
        if (up && !visited[iu]) {
            q.push(iu); dist[iu] = d+1; visited[iu] = true;
        } 
        // if (up && right && !visited[iur]) {
        //     q.push(iur); dist[iur] = d+1; visited[iur] = true;
        // } 
        // if (up && left && !visited[iul]) {
        //     q.push(iul); dist[iul] = d+1; visited[iul] = true;
        // } 
        // if (down && right && !visited[idr]) {
        //     q.push(idr); dist[idr] = d+1; visited[idr] = true;
        // } 
        // if (down && left && !visited[idl]) {
        //     q.push(idl); dist[idl] = d+1; visited[idl] = true;
        // } 

    }
    
    int cmax = -1;
    for (int d : dist) {
        cmax = max(cmax, d);
        // cout << d << endl;
    }
    cout << cmax << endl;

    return 0;
}