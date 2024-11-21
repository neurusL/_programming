#include <bits/stdc++.h>
#include <string>
#include <iostream>

// using namespace std;


std::string longestPalindrome(std::string s) {
        // idea: dp[i][j] -> bool to store str[i..j] is palindrome or not
        int str_len = s.size();
        if (str_len == 0) {
            return s;
        } else {
            int cnt = 1;
            int l_idx = 0; // [
            int r_idx = 1; // )

            int dp_len = str_len * (str_len - 1);
            bool dp[str_len+1][str_len+1];

            for (int i = 0; i < str_len; i++) {
                dp[i][i] = true;
            }
            for (int i = 0; i < str_len-1; i++) {
                dp[i][i+1] = true;
            }

            for (int k = 2; k < str_len + 1; k++) {
                for (int i = 0; i < str_len - k + 1; i++) {
                    if ((s[i] == s[i+k-1]) && dp[i+1][i+k-1]) {
                        dp[i][i+k] = true;
                        cnt = k;
                        l_idx = i;
                        r_idx = i+k;
                    } else {
                        // std::cout << i << endl;
                        // std::cout << k << endl;
                        dp[i][i+k] = false;
                    }
                }
            }
            return s.substr(l_idx, r_idx-l_idx);
        }
    }

int main() {
    std::string str;
    std::cin >> str;
    std::cout << longestPalindrome(str);
    return 0;
}

    

