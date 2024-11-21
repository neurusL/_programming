#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int dp1[501][10001] = {-1};
int dp2[501][10001] = {-1};

// A Mistake! Notice target can be negative!
int oneClosest(vector<int>& nums, int idx, int target) {
    int len = nums.size();
    if (idx >= len) {
        return target;
    } else if (dp1[idx][target] != -1) {
        return dp1[idx][target];
    } else {
        int min = abs(target);
        for (int i = idx; i < len; i++) {
            int abs_val = abs(nums[i] - target);
            if (abs_val < min) {
                min = abs_val;
            }
        }
        dp1[idx][target] = min;
    }
    
}

int twoSumClosestI(vector<int>& nums, int idx, int target) {
    int len = nums.size();
    if (idx >= len) {
        return target;
    } else if (dp2[idx][target] != -1) {
        return dp2[idx][target];
    } else {
        int cI = oneClosest(nums, idx + 1, target - nums[idx]);
        int ncI = twoSumClosestI(nums, idx + 1, target);
        return cI < ncI ? cI : ncI;
    }
}

int threeSumClosestI(vector<int>& nums, int idx, int target) {
    int len = nums.size();
    if (idx >= len) {
        return target;
    } else {
        int cI = twoSumClosestI(nums, idx + 1, target - nums[idx]);
        int ncI = threeSumClosestI(nums, idx + 1, target);
        return cI < ncI ? cI : ncI;
    }
}

int threeSumClosest(vector<int>& nums, int target) {
    return threeSumClosestI(nums, 0, target);     
}