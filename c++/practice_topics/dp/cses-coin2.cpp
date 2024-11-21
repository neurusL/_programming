#include <bits/stdc++.h>
#include <iostream>
#include <queue>

#define P 1000000007

using namespace std;

int count_unique(int sum, int lb, vector<int>& coins, vector<vector<int> >& dp) {
    if (dp[sum][lb] != -1) { return dp[sum][lb]; }
    if (sum == 0) {
        dp[0][lb] = 1;
        return 1;
    }

    if (sum < lb) { 
        dp[sum][lb] = 0;
        return 0; 
    }
    else if (sum == coins[lb]) { 
        dp[sum][lb] = 1;
        return 1; 
    }
    else {
        int res = 0;
        for (int i = lb; i < coins.size(); i++) {
            res += count_unique(sum-coins[i], i, coins, dp);
        }
        dp[sum][lb] = res;
        return res;
    }
}

int main() {
    int n, sum;
    cin >> n >> sum;
    vector<int> coins(n);
    for (int i = 0; i < n; i++){
        int ci; cin >> ci;
        coins[i] = ci;
    }
    vector<vector<int> >dp(sum+1, vector<int>(n+1, -1));
    // dp[0] = vector<int>(n+1, 1);
    cout << count_unique(sum, 0, coins, dp);

    return 0;
}