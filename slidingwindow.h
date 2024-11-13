
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

int lengthOfLongestSubstring(string s)
{
    unordered_map<char, int> hash; // num index
    int l = 0;
    int ans = 0;
    for (int r = 0; r < s.size(); r++)
    {
        char c = s[r];
        if (hash.count(c) && hash[c] >= l)
        {
            // 我们没有移除,只能hash[c]>=l
            l = hash[c] + 1;
        }
        hash[c] = r;
        ans = max(ans, r - l + 1);
    }
    return ans;
}

vector<int> findAnagrams(string s, string p)
{
    unordered_map<int, int> hash;
    unordered_map<int, int> need;
    vector<int> result;
    for (char c : p)
    {
        need[c]++;
    }

    int l = 0;
    int count = 0;
    int i = 0;
    while (i < s.size())
    {
        char c = s[i];
        i++;
        if (need.count(c))
        {
            // 有这个元素的话
            hash[c]++;
            if (hash[c] == need[c])
            {
                count++;
            }
        }

        while (i - l >= p.size())
        {
            if (count == need.size())
            {
                result.push_back(l);
            }

            char d = s[l];
            l++;
            if (need.count(d))
            {
                if (need[d] == hash[d])
                {
                    count--;
                }
                hash[d]--;
            }
        }
    }
    return result;
}