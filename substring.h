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

int subarraySum(vector<int> &nums, int k)
{
    unordered_map<int, int> hash = {{0, 1}};
    int ans = 0;
    int ps = 0;
    for (int num : nums)
    {
        ps += num;
        ans += hash[ps - k];
        hash[ps]++;
    }
    return ans;
}

// 239 滑动窗口最大值
class MyQueue
{
public:
    deque<int> que;

    void pop(int val)
    {
        if (!que.empty() && val == que.front())
        {
            que.pop_front();
        }
    }

    void push(int val)
    {
        while (!que.empty() && val > que.back())
        {
            que.pop_back();
        }
        que.push_back(val);
    }

    int front()
    {
        return que.front();
    }
};
vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
    vector<int> result;

    MyQueue myQue;
    for (int i = 0; i < k; i++)
    {
        myQue.push(nums[i]);
    }
    result.push_back(myQue.front());
    for (int i = k; i < nums.size(); i++)
    {
        myQue.push(nums[i]);
        myQue.pop(nums[i - k]);
        result.push_back(myQue.front());
    }
    return result;
}

// 76 最小覆盖子串
string minWindow(string s, string t)
{
    unordered_map<char, int> need;
    for (char c : t)
    {
        need[c]++;
    }
    unordered_map<char, int> hash;

    int l = 0, r = 0, count = 0;
    int start = 0;
    string result = "";
    int curLength, minLength = s.size() + 1;
    while (r < s.size())
    {
        char c = s[r];
        r++;
        if (need.count(c))
        {
            // 存在
            hash[c]++;
            if (hash[c] == need[c])
            {
                count++;
            }
        }

        // 收缩
        while (count == need.size())
        {

            // 收集结果
            curLength = r - l;
            if (curLength <= minLength)
            {
                minLength = curLength;
                start = l;
            }

            char lc = s[l];
            l++;

            if (hash.count(lc))
            {
                if (hash[lc] == need[lc])
                {
                    count--;
                }
                hash[lc]--;
            }
        }
    }
    return minLength == s.size() + 1 ? "" : s.substr(start, minLength);
}