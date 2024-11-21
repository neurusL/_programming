class Solution {
public:
    int endContainVowels(string& word, int start) {
        int c1 = 0;
        int c2 = 0;
        int c3 = 0;
        int c4 = 0;
        int c5 = 0;
        for (int i = start; i < word.size(); i++) {
            char c = word[i];
            if (c == 'a') { c1++; }
            else if (c == 'e') { c2++; }
            else if (c == 'i') { c3++; }
            else if (c == 'o') { c4++; }
            else if (c == 'u') { c5++; }
            if (c1 > 0 && c2 > 0 && c3 > 0 && c4 > 0 && c5 > 0) { return i; }
        }
        return -1;
    }
    bool isVow(char c) {
        return c == 'a' ||  c == 'e' ||  c == 'i' ||  c == 'o' || c == 'u';
    }
    int binsearch(vector<int>& nums, int low, int high, int x) {
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == x) { 
                int cnt = 1;
                int i = mid+1;
                while (i <= high) {
                    if (nums[i] == x) {cnt++;}
                    i++;
                }
                int j = mid-1;
                while (j >= low) {
                    if (nums[j] == x) {cnt++;}
                    j--;
                }
                return cnt;
             }
            else if (nums[mid] < x) { 
                low = mid + 1;
            } else { 
                high = mid - 1;
            }
        }
        return -1;
    }

    long long countOfSubstrings(string word, int k) {
        int N = word.size();

        // prefix sum
        vector<int> numk(N, 0);
        // vector<int> vowok(N, 0);
        int curr = 0;
        for (int i = 0; i < N; i++) {
            if (!isVow(word[i])) { curr++; }
            numk[i] = curr;
        }

        // calculate result
        long long res = 0;
        for (int i = 0; i < N; i++) {
            // calculate ending idx contain all vows
            int vowok = endContainVowels(word, i); //TIMEOUT
            // HINT: notice all vowel positions are sorted
            // USE: lower_bound
            if (vowok != -1) {
                // among numk[vowok[i]..N]
                // look for numk[i] + k 
                int cnt = binsearch(numk, vowok, N-1, i == 0 ? k : (numk[i-1]+k));
                if (cnt != -1) {
                    // cout << i << " " << cnt << endl;
                    res += cnt;
                }
            }
        }

        return res;
    }
};

// Solution from Ivan
// class Solution {
// public:
//     long long countOfSubstrings(string word, int k) {
//         int n = word.size();
//         vector<vector<int>> occ(5);
//         vector<int> pref(n + 1);
//         vector<char> con = {'a', 'e', 'i', 'o', 'u'};
//         for (int i = 0; i < n; i++) {
//             bool find = false;
//             for (int j = 0; j < 5; j++) {
//                 if (word[i] == con[j]) {
//                     find = true;
//                     occ[j].push_back(i);
//                     break;
//                 }
//             }
//             pref[i + 1] = pref[i] + (find == false);
//         }
//         long long ans = 0;
//         for (int i = 0; i < n; i++) {
//             int start = -1;
//             bool ok = true;
//             for (int j = 0; j < 5; j++) {
//                 auto iter = lower_bound(occ[j].begin(), occ[j].end(), i) - occ[j].begin();
//                 if (iter == occ[j].size()) {
//                     ok = false;
//                     break;
//                 }
//                 start = max(start, occ[j][iter]);
//             }
//             if (!ok) break;
//             int l = start - 1, r = n;
//             while (l + 1 < r) {
//                 int mid = (l + r) / 2;
//                 if (pref[mid + 1] - pref[i] >= k) r = mid;
//                 else l = mid;
//             }
//             int left = r;
//             l = start - 1, r = n;
//             while (l + 1 < r) {
//                 int mid = (l + r) / 2;
//                 if (pref[mid + 1] - pref[i] > k) r = mid;
//                 else l = mid;
//             }
//             int right = l;
//             ans += (long long)(right - left + 1);
//             // cout << i << ' ' << start << ' ' << left << ' ' << right << '\n';
//         }
//         return ans;
//     }
// };