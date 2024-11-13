
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
    unordered_map<char, int> hash; // char ,index
    int ans = 0;
    int l = 0, r = 0;
    while (r < s.size())
    {
        char c = s[r];
        if (hash.count(c) && hash[c] >= l)
        {
            l = hash[c] + 1;
        }
        hash[c] = r;
        r++;
        ans = max(ans, r - l);
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
        i++;
    }
    return result;
}