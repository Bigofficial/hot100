
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

void moveZeroes(vector<int> &nums)
{
    if (nums.size() == 0)
    {
        return;
    }
    int j = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] != 0)
        {
            swap(nums[i], nums[j]);
            j++;
        }
    }
}

// 11 盛最多水的容器
int maxArea(vector<int> &height)
{
    int left = 0, right = height.size() - 1;
    int ans = (height.size() - 1) * min(height[left], height[right]);
    while (left < right)
    {
        if (height[left] < height[right])
        {
            left++;
        }
        else
        {
            right--;
        }
        int area = (right - left) * min(height[left], height[right]);
        ans = max(ans, area);
    }
    return ans;
}

vector<vector<int>> threeSum(vector<int> &nums)
{
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] > 0)
        {
            break;
        }

        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int left = i + 1;
        int right = nums.size() - 1;

        while (right > left)
        {
            if (nums[i] + nums[left] + nums[right] > 0)
                right--;
            else if (nums[i] + nums[left] + nums[right] < 0)
                left++;
            else
            {
                result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                while (right > left && nums[right] == nums[right - 1])
                    right--; // 出循环后right前面就不是这个数字了
                while (right > left && nums[left] == nums[left + 1])
                    left++;
                right--;
                left++;
            }
        }
    }
    return result;
}

int trap(vector<int> &height)
{
    int left = 0, right = height.size() - 1;
    int ans = 0;
    int leftMax = 0, rightMax = 0;
    while(left < right){
        leftMax = max(leftMax, height[left]);
        rightMax = max(rightMax, height[right]);
        if(leftMax < rightMax){
            ans += leftMax - height[left];
            left++;
        }else{
            ans += rightMax - height[right];
            right--;
        }
    }
    return ans;
}

int trap2(vector<int> &height)
{
    int n = height.size();
    int ans = 0;
    stack<int> stk;
    for(int i = 0; i < n; i++){
        while(stk.size() && height[i] > height[stk.top()]){
            int l = height[stk.top()];
            stk.pop();
            if(stk.size()){
                int h = min(height[i], height[stk.top()]);
                int capacity = (h - l ) * (i - stk.top() - 1);
                ans += capacity;
            }
        }
        stk.push(i);
    }
    return ans;
}