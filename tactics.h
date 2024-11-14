
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

int singleNumber(vector<int> &nums)
{
    int ans = 0;
    for (int num : nums)
    {
        ans ^= num;
    }
    return ans;
}

// 169 多数元素
int majorityElement(vector<int> &nums)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());
    return nums[n / 2];
}

// 75 颜色分类
void sortColors(vector<int> &nums)
{
    int redIndex = 0, blueIndex = nums.size() - 1;
    for (int i = 0; i <= blueIndex; i++)
    {
        if (nums[i] == 0)
        {
            swap(nums[redIndex++], nums[i]);
        }
        else if (nums[i] == 1)
        {
            continue;
        }
        else
        {
            swap(nums[blueIndex--], nums[i]);
            i--;
        }
    }
}

// 287 寻找重复数
int findDuplicate(vector<int> &nums)
{
    int n = nums.size();
    int left = 1, right = n - 1;
    int ans;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int count = 0;
        for (int num : nums)
        {
            if (num <= mid)
            {
                count++;
            }
        }
        if (count <= mid)
        {
            left = mid + 1;
        }
        else
        {
            ans = mid;
            right = mid - 1;
        }
    }
    return ans;
}

void nextPermutation(vector<int> &nums)
{
    int n = nums.size();
    int firstIndex = -1, secondIndex = -1;
    if (nums.size() == 0)
        return;
    for (int i = n - 2; i >= 0; i--)
    {
        if (nums[i] < nums[i + 1])
        {
            firstIndex = i;
            break;
        }
    }
    if (firstIndex == -1)
    {
        reverse(nums.begin(), nums.end());
        return;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (nums[i] > nums[firstIndex])
        {
            secondIndex = i;
            break;
        }
    }
    swap(nums[firstIndex], nums[secondIndex]);
    reverse(nums.begin() + firstIndex + 1, nums.end());
}