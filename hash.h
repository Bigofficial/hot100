
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
vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> hash; // num index
    for (int i = 0; i < nums.size(); i++)
    {
        if (!hash.empty() && hash.find(nums[i]) != hash.end())
        {
            return {hash[nums[i]], i};
        }
        hash[target - nums[i]] = i;
    }
    return {-1, -1};
}

// 49 字母异位词分组
vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    unordered_map<string, vector<string>> hash;
    for (string s : strs)
    {
        string sortS = s;
        sort(sortS.begin(), sortS.end());
        hash[sortS].push_back(s);
    }
    vector<vector<string>> result;
    for (const pair<const string, vector<string>> &s : hash)
    {
        result.push_back(s.second);
    }
    return result;
}

// 128 最长连续序列
int longestConsecutive(vector<int> &nums)
{
    unordered_set<int> hash(nums.begin(), nums.end());
    int result = 0;
    for (int num : nums)
    {
        if (!hash.count(num - 1)) //不存在
        {
            // 还有前面的,这个就可以不管
            int curNum = num;
            int streak = 1;
            while (hash.count(curNum + 1))
            {
                streak++;
                curNum++;
            }
            result = max(result, streak);
        }
    }
    return result;
}