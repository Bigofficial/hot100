#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <climits>
using namespace std;
const int INT_MAX = 2147483647;
// 70 爬楼梯
int climbStairs(int n)
{
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}
// 118 杨辉三角
vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> result(numRows);
    result[0].push_back(1);
    if (numRows > 1)
    {
        result[1].push_back(1);
        result[1].push_back(1);
    }
    for (int i = 2; i < numRows; i++)
    {
        result[i].push_back(1);
        for (int j = 1; j < i; j++)
        {
            result[i].push_back(result[i - 1][j - 1] + result[i - 1][j]);
        }
        result[i].push_back(1);
    }
    return result;
}
// 198 打家劫舍
int rob(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n, 0);
    // dp[i] : 以i下标为结尾的房屋盗窃的最大值
    dp[0] = nums[0];
    if (n > 1)
    {
        dp[1] = max(nums[0], nums[1]);
    }
    for (int i = 2; i < n; i++)
    {
        dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
    }
    return dp[n - 1];
}
// 279 完全平方数
int numSquares(int n)
{
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    // dp[i] : i 最少由几个完全平方数构成
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j * j <= i; j++)
        {
            dp[i] = min(dp[i], dp[i - j * j] + 1);
        }
    }
    return dp[n];
}
// 322 零钱兑换
int coinChange(vector<int> &coins, int amount)
{
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 0; i < coins.size(); i++)
    {
        for (int j = coins[i]; j < amount + 1; j++)
        {
            if (dp[j - coins[i]] != INT_MAX)
            {
                dp[j] = min(dp[j], dp[j - coins[i]] + 1);
            }
        }
    }
    if (dp[amount] == INT_MAX)
        return -1;
    return dp[amount];
}

// 139 单词拆分
bool wordBreak(string s, vector<string> &wordDict)
{
    int n = s.size();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 0; j < wordDict.size(); j++)
        {
            if (wordDict[j].size() <= i)
            {
                // 找出这个单词
                string word = s.substr(i - wordDict[j].size(), wordDict[j].size());
                if (word == wordDict[j] && dp[i - wordDict[j].size()])
                {
                    dp[i] = true;
                }
            }
        }
    }
    return dp[n];
}

// 300 最长递增子序列
int lengthOfLIS(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n, 1);
    int result = 1;
    // dp[i]:以i为下标的最长递增子序列长度
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (nums[i] > nums[j])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
            result = max(result, dp[i]);
        }
    }
    return dp[n];
}

// 152 乘积最大子数组
int maxProduct(vector<int> &nums)
{
    int n = nums.size();
    long maxF = nums[0], minF = nums[0];
    long result = nums[0];
    for (int i = 1; i < n; i++)
    {
        int mx = maxF, mn = minF;
        maxF = max(mx * nums[i], max(mn * nums[i], nums[i]));
        minF = min(mx * nums[i], min(mn * nums[i], nums[i]));
        result = max(result, maxF);
    }
    return result;
}

// 416 分割等和子集
bool canPartition(vector<int> &nums)
{
    int n = nums.size();
    int sum = 0;
    for (int num : nums)
    {
        sum += num;
    }
    if (sum % 2 != 0)
    {
        return false;
    }
    int target = sum / 2;
    // 背包就是target,物品为nums, 非完全背包,要从大到小遍历
    vector<int> dp(target + 1, 0);
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = target; j >= nums[i]; j--)
        {
            if (j >= nums[i])
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
        }
    }
    if (dp[target] == target)
        return true;
    return false;
}

// 32 最长有效括号
int longestValidParentheses(string s)
{
    int n = s.size();
    vector<int> dp(n, 0);
    int ans = 0;
    // dp[i] : s以下标i为结尾的子串最长子串
    for (int i = 1; i < n; i++)
    {
        if (s[i] == ')')
        {
            if (s[i] == '(')
            {
                //() or ()()
                dp[i] = (i - 2) > 0 ? 2 : dp[i - 2] + 2;
            }
            else if (s[i] == ')')
            {
                // ()) (())
                // 如果找到前面匹配完的前一个如())就是找到-1, 如果前面匹配玩的前一个是,那么我们自己就匹配上了
                if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(')
                { // (())
                    dp[i] = 2 + dp[i - 1] + (i - dp[i - 1] - 2 >= 0 ? dp[i - dp[i - 1] - 2] : 0);
                }
            }
            ans = max(ans, dp[i]);
        }
    }
    return ans;
}