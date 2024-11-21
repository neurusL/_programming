#include <bits/stdc++.h>
#include <iostream>
#include <set>

using namespace std;

bool eq_nums1 (int x, int n) {
    multiset<int> a;
    int y = x;
    while (y > 0) {
        int l = y % 10;
        y = y / 10;
        a.insert(l);
    }
    int z = n * x;
    while (z > 0) {
        int l = z % 10;
        z = z / 10;
        auto it = a.find(l);
        if (it != a.end()) {
            a.erase(it);
        } else {
            return false;
        }
    }
    return a.empty();
}

bool eq_nums2 (int x, int n) {
    vector<int> a(10, 0);

    int y = x;
    while (y > 0) {
        int l = y % 10;
        y = y / 10;
        a[l]++;
    }

    int z = n * x;
    while (z > 0) {
        int l = z % 10;
        z = z / 10;
        a[l]--;
    }

    for (int i = 0; i < 10; i++) {
        if (a[i] != 0) {
            return false;
        }
    }
    return true;
}

// I misread the problem before ;(, it's actually asking 
// same digit with ALL 2x, 3x, ... nx

// int main() {
//     int n;
//     int curr = 1;
    
//     int i = 2;
//     cin >> n;
    
//     vector<int> leasts(n);
//     for (int i = 2; i <= n; i++) {
//         while (!eq_nums(curr, i)) {
//             if (curr > (i / n)) {
//                 curr = i;
//                 i *= 10;
//                 // cout << "shifting:" << endl;
//             } else {
//                 curr++;
//             }
//             curr++;
//             if (curr < 0) {
//                 cout << "warning:" << curr << endl;
//             }
//         }
//     }

//     cout << (int)curr;
//     return 0;
// }

int main() {
    int n;
    int curr = 1;
    
    int i = 2;
    cin >> n;
    
    while(i <= n) {
        while (!eq_nums2(curr, i)) {
            curr++;
        }

        int flag = 1;
        for (int j = 2; j < i; j++) {
            if (!eq_nums2(curr, j)) { 
                curr++; 
                flag = 0;
                break; 
            }
            // cout << curr << endl;
        }
        i += flag;
    }

    cout << (int)curr;
    return 0;
}