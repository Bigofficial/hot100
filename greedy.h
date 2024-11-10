
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <climits>
#include <string>
#include <unordered_map>
using namespace std;

int maxProfit(vector<int> &prices)
{
    int result = 0;
    int buy = prices[0];
    for (int i = 1; i < prices.size(); i++)
    {
        result = max(result, prices[i] - buy);
        buy = min(buy, prices[i]);
    }
    return result;
}

bool canJump(vector<int> &nums)
{
    int range = 0; // 可以抵达的范围
    for (int i = 0; i < nums.size(); i++)
    {
        if (i > range)
        {
            return false;
        }
        else
        {
            range = max(range, i + nums[i]);
        }
        if (range >= nums.size() - 1)
            return true;
    }
    return false;
}

int jump(vector<int> &nums)
{
    int maxPos = 0, n = nums.size(), end = 0, step = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (maxPos >= i)
        {
            maxPos = max(maxPos, i + nums[i]);
            if (i == end)
            {
                end = maxPos;
                step++;
            }
        }
    }
    return step;
}

vector<int> partitionLabels(string s)
{
    vector<int> result;
    unordered_map<char, int> lastShowMap;
    for (int i = 0; i < s.size(); i++)
    {
        lastShowMap[s[i]] = i;
    }
    int start = 0, end = lastShowMap[s[0]];
    for (int i = 0; i < s.size(); i++)
    {
        end = max(end, lastShowMap[s[i]]);
        if (i == end)
        {
            result.push_back(end - start + 1);
            start = end + 1;
        }
    }
    return result;
}