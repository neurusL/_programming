
int search(vector<int>& nums, int target) {
    // version 1 (traditional binary search)
    int l = 0;
    int r = nums.size()-1;
    while(l <= r) {
        int mid = (r - l)/2 + l;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) l = mid+1;
        else r = mid-1;
    }
    return -1;

    // // version 2 (general binary search)
    // // let l be the largest idx we know the property is true
    // // let r be the smallest idx we know the property is false
    // int l = -1;
    // int r = nums.size();
    // while(l+1 < r) {
    //     int mid = (r-l)/2 + l;
    //     auto ok = [&](int i) -> bool {
    //         return nums[i] <= target;
    //     };
    //     if (ok(mid)) l = mid;
    //     else r = mid;
    // }
    // return (l != -1 && nums[l] == target) ? l : -1;

    // // version 3
    // // use c++ build in function
    // auto it = lower_bound(nums.begin(), nums.end(), target);
    // if (it != nums.end() && *it == target) {
    //     return int(it - nums.begin());
    // } else {
    //     return -1;
    // }
}