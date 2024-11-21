// https://leetcode.com/contest/weekly-contest-413/problems/k-th-nearest-obstacle-queries/description/

#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <set>
#include <queue>

using namespace std;

// naively using a vector
// vector<int> resultsArray(vector<vector<int>>& queries, int k) {
    
//     vector<int> ks;
//     vector<int> res;
//     int len = queries.size();

//     for (int i = 0; i < len; i++) {
//         int d = queries[i][1] + queries[i][2]; 

//         int idx = k;
//         for (int j = k-1; j >= 0; j--) {
//             if (d <= ks[j]) { idx = j; break; }
//         }

//         if (idx < k) {
//             for (int j = k-1; j >= idx+1; j--) {
//                 if (j == idx) { ks[j] = d; }
//                 else { ks[j] = ks[j-1]; }
//             }
//         }

//         if (i < k-1) { res.push_back(-1); }
//         else { res.push_back(ks[i]); }
//     }
// }

/*
using priority queue:
std::priority_queue<int> maxPQ;
std::priority_queue<int, std::vector<int>, std::greater<int>> minPQ;
*/

vector<int> resultsArray(vector<vector<int>>& queries, int k) {
        
        priority_queue<int> firstk;
        vector<int> res;
        int len = queries.size();
        int curr_k = -1;

        for (int i = 0; i < len; i++) {
            int d = abs(queries[i][0]) + abs(queries[i][1]); 

            if (i < k-1) {
                firstk.push(d);
                res.push_back(curr_k);
            } else if (i == k-1) {
                firstk.push(d);
                curr_k = firstk.top();
                res.push_back(curr_k);
            } else {
                if (d < curr_k) {
                    firstk.pop();
                    firstk.push(d);
                    curr_k = firstk.top(); 
                }
                res.push_back(curr_k);
            } 
        }

        return res;
    }

/*
using multiset:
std::priority_queue<int> maxPQ;
std::priority_queue<int, std::vector<int>, std::greater<int>> minPQ;
*/

vector<int> resultsArray(vector<vector<int>>& queries, int k) {
        
        multiset<int> firstk;
        vector<int> res;
        int len = queries.size();
        int curr_k = -1;

        for (int i = 0; i < len; i++) {
            int d = abs(queries[i][0]) + abs(queries[i][1]); 

            firstk.insert(d);
            if (firstk.size() > k) {
                firstk.erase(firstk.find(*firstk.rbegin()));
                // notice the behavior of multi set erase!
                // erase all values 
            }
            if (i < k-1) {
                res.push_back(-1);
            } else {
                res.push_back(*firstk.rbegin());
            }
        }

        return res;
    }