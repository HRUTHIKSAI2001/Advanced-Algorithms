#include <iostream>
#include <vector>
using namespace std;

// Function to find and print the longest common substring
string longestCommonSubstring(string s1, string s2) {
    int n = s1.length();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0)); // DP table
    int maxLength = 0, endIndex = 0;

    // Build DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i; // Store end index of LCS in s1
                }
            }
        }
    }

    // Print DP Table
    cout << "Dynamic Programming Table:\n";
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    // Extract the longest common substring
    return s1.substr(endIndex - maxLength, maxLength);
}

int main() {
    string str1, str2;
    
    // Take input
    cout << "Enter first string: ";
    cin >> str1;
    cout << "Enter second string: ";
    cin >> str2;

    // Ensure both strings are of equal length
    if (str1.length() != str2.length()) {
        cout << "Error: Strings must be of equal length." << endl;
        return 1;
    }

    // Compute and display the longest common substring
    string result = longestCommonSubstring(str1, str2);
    cout << "Longest Common Substring: " << result << endl;

    return 0;
}
