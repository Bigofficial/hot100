#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <climits>
using namespace std;
const int INT_MAX = 2147483647;
int uniquePaths(int m, int n)
{
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    dp[0][1] = 1;
    for (int i = 1; i < m + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m][n];
}

// 64 最小路径和
int minPathSum(vector<vector<int>> &grid)
{
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
    dp[0][1] = 0;
    for (int i = 1; i < m + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
        }
    }
    return dp[m][n];
}

//5 最长回文子串
string longestPalindrome(string s) {

    int n = s.size();
    int begin = 0, end = 0, result = 1;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        dp[i][i] = 1;
    }
    for(int i = n - 2; i >= 0; i--){
        for(int j = i + 1; j < n; j++){
            if(s[i] == s[j]){
                if(j == i + 1){
                    dp[i][j] = 2; //防止出现j小于i 这个相较于子序列 其实是一样的,但是下面要确保子串也是回文
                }else if(dp[i + 1][j - 1] > 0){
                    //里面的这个串也得是回文的
                    dp[i][j] = dp[i+1][j-1] + 2;
                }
            }
            if(dp[i][j] > result){
                result = dp[i][j];
                begin = i;
                end = j;
            }
        }
    }
    return s.substr(begin, end - begin + 1);
}

//1143 最长公共子序列
int longestCommonSubsequence(string text1, string text2){
    vector<vector<int>> dp(text1.size()+1, vector<int>(text2.size()+1, 0));
    for(int i = 1; i < text1.size() + 1; i++){
        for(int j = 1; j < text2.size() + 1; j++){
            if(text1[i - 1] == text2[j - 1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[text1.size()][text2.size()];
}

//72 编辑距离
int minDistance(string word1, string word2) {
    vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
    //dp[i][j]: 从0到下标i-1的,和0-下标j-1的子串的最近编辑距离
    //dp[0][j]: 就是j嘛,
    for(int i = 0; i <= word1.size(); i++){
        dp[i][0] = i;
    }
    for(int j = 0; j <= word2.size(); j++){
        dp[0][j] = j;
    }
    for(int i = 1; i <= word1.size(); i++){
        for(int j = 1; j <= word2.size(); j++){
            if(word1[i - 1] == word2[j - 1]){
                dp[i][j] = dp[i-1][j-1];
            }else{
                dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
            }
        }
    }
    return dp[word1.size()][word2.size()];
}
