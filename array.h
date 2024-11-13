
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <climits>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int maxSubArray(vector<int> &nums)
{

    int result = INT_MIN, sum = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (sum > 0)
        {
            sum += nums[i];
        }
        else
        {
            sum = nums[i];
        }
        result = max(result, sum);
    }
    return result;
}

struct Comp
{
    bool operator()(vector<int> a, vector<int> b)
    {
        return a[0] < b[0];
    }
};
// 56 合并区间
vector<vector<int>>
merge(vector<vector<int>> &intervals)
{
    sort(intervals.begin(), intervals.end(), Comp());
    vector<vector<int>> result;
    result.push_back(intervals[0]);
    for (int i = 1; i < intervals.size(); i++)
    {
        if (intervals[i][0] > result.back()[1])
        {
            result.push_back(intervals[i]);
        }
        else
        {
            result.back()[1] = max(result.back()[1], intervals[i][1]);
        }
    }
    return result;
}

// 189 轮转数组
void rotate(vector<int> &nums, int k)
{
    int n = nums.size();
    k = k % n;
    if (k == 0)
        return;
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}

// 1 2 3 4
// 0 1 1 1
// 1 0 1 1
// 1 1 0 1
// 1 1 1 0

// 238 除自身以外的乘积
vector<int> productExceptSelf(vector<int> &nums)
{
    vector<int> ans(nums.size(), 1);
    for (int i = 1; i < nums.size(); i++)
    {
        ans[i] = ans[i - 1] * nums[i - 1];
    }
    int product = 1;
    for (int i = nums.size() - 2; i >= 0; i--)
    {
        product *= nums[i + 1];
        ans[i] = ans[i] * product;
    }
    return ans;
}

// 41 缺失的第一个正数
int firstMissingPositive(vector<int> &nums)
{
    // 0,1,2
    // 1,2,3
    for (int i = 0; i < nums.size(); i++)
    {
        //                                                  1    != nums[0] 
        while (nums[i] >= 1 && nums[i] <= nums.size() && nums[i] != nums[nums[i] - 1])
        {
            swap(nums[i], nums[nums[i] - 1]);
        }
    }
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] != i + 1)
        {
            return i + 1;
        }
    }
    return nums.size() + 1;
}