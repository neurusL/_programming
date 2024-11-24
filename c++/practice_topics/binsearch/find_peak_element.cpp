// source: leetcode 162. Find Peak Element
/**
A peak element is an element that is strictly greater than its neighbors.
Given a integer array nums, find a peak element, and return its index. 
If the array contains multiple peaks, return the index to any of the peaks.

You may imagine that nums[-1] = nums[n] = -inf. In other words, an element 
is always considered to be strictly greater than a neighbor that is outside 
the array.
O(log n) solution. Hint: binary search
*/

/**
Solution:
It's not same as traditional binsearch, but since we are only asked to output
one possible solution, then we CAN reduce much search space each time, by
exploring the search space where there must be an solution.
A key observation: for index i under consideration, if i not a peak, then
- either nums[i+1] > nums[i] or nums[i-1] > nums[i]
- since we assume nums[-1] = nums[n] = -inf
- WLOG assume nums[i-1] > nums[i], then there must exist answer between 0..i-1 
*/

int findPeakElement(vector<int>& nums) {
    int n = nums.size();
    int l = 0;
    int r = n-1;
    auto gtl = [&](int i) -> bool {
        if (i == 0) return true;
        else return nums[i] > nums[i-1];
    };
    auto gtr = [&](int i) -> bool {
        if (i == n-1) return true;
        else return nums[i] > nums[i+1];
    };
    auto ok = [&](int i) -> bool {
        return gtl(i) && gtr(i);
    };

    while (l <= r) {
        int mid = (r-l)/2 + l;
        if (ok(mid)) return mid;
        else if (gtl(mid)) l = mid+1;
        else r = mid-1;
    }
    return -1;
}


// source leetcode 852. Peak Index in a Mountain Array
/**
You are given an integer mountain array arr of length n where the values 
increase to a peak element and then decrease.
Return the index of the peak element.
O(log n) solution. Hint: binary search
*/
/**
Solution: exactly the same code as above
*/