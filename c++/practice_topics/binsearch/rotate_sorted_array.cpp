// source leetcode 33. Search in Rotate Sorted Array
/**
There is an integer array nums sorted in ascending order (with distinct values).
Prior to being passed to your function, nums is possibly rotated at an unknown 
pivot index k (1 <= k < nums.length) such that the resulting array is 
[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). 
For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become 
[4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return 
the index of target if it is in nums, or -1 if it is not in nums.
O(log n) solution. Hint: binary search.
*/

int search(vector<int>& nums, int target) {
    // first find break point 
    int n = nums.size();
    int l = -1;
    int r = n;
    auto inleft = [&](int i) {
        return nums[i] >= nums[0];
    };

    while (l+1 < r) {
        int mid = (r-l)/2 + l;
        if (inleft(mid)) l = mid;
        else r = mid;
    }
    int pivot = l;
    cout << pivot << endl;

    // then sort in the right partition
    if (target >= nums[0]) {
        l = 0; r = pivot;
    } else {
        l = pivot+1; r = n-1;
    }
    while (l <= r) {
        int mid = (r-l)/2 + l;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) l = mid+1;
        else r = mid-1;
    }
    return -1;
}