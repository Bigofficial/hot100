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
// 35 搜索插入位置
// 这个位置的数肯定是比要找的数大一点,或者等于,这题其实就是找第一个大于等于target的位置
int searchInsert(vector<int> &nums, int target)
{
    int l = 0, r = nums.size() - 1;
    int ans = nums.size();
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] >= target) // 符合条件了,大于等于target的位置,但是我们不能break还要往前找第一个
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return ans;
}
// int startX = 0, startY = matrix[0].size();
// while(startX < matrix.size() && startY >= 0){
//     if(matrix[startX][startY] == target){
//         return true;
//     }else if(matrix[startX][startY] > target){
//         startY--;
//     }else{
//         startX++;
//     }
// }
// return false;

// 74 搜索二维矩阵
// 对于右上角元素 左边的都比他小,下边的都比他大
bool searchMatrix(vector<vector<int>> &matrix, int target)
{

    // 一次二分找到第一个小于等于target的行
    int m = matrix.size(), n = matrix[0].size();
    int rowL = 0, rowR = m - 1;
    int row = matrix.size();
    while (rowL <= rowR)
    {
        int mid = rowL + (rowR - rowL) / 2;
        if (matrix[mid][0] == target)
        {
            return true;
        }
        else if (matrix[mid][0] < target)
        {
            rowL = mid + 1;
        }
        else
        {
            row = mid;
            rowR = mid - 1;
        }
    }
    row--; // 此时row为大于的位置,我们要往前移动一位
    if (row == -1)
        return false;
    // 此时row这一行就是可能结果
    int colL = 0, colR = n - 1;
    int col = n;
    while (colL <= colR)
    {
        int mid = colL + (colR - colL) / 2;
        if (matrix[row][mid] == target)
        {
            return true;
        }
        else if (matrix[row][mid] < target)
        {
            colL = mid + 1;
        }
        else
        {
            colR = mid - 1;
        }
    }
    return false;
}

// 34 在排序数组中找第一个和最后一个
vector<int> searchRange(vector<int> &nums, int target)
{
    int l = 0, r = nums.size() - 1;
    int startIndex = -1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target)
        {
            startIndex = mid;
            r = mid - 1;
        }
        else if (nums[mid] < target)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    l = 0, r = nums.size() - 1;
    int endIndex = -1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target) // 等于了还要往前看
        {
            endIndex = mid;
            l = mid + 1;
        }
        else if (nums[mid] < target)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return {startIndex, endIndex};
}

// 33 搜索旋转排序数组
int search(vector<int> &nums, int target)
{
    int left = 0, right = nums.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[left] <= nums[mid])
        {
            // 在左边
            if (nums[left] <= target && target < nums[mid])
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        else
        {
            if (nums[mid] < target && target <= nums[right])
            {
                left = left + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
    }

    return -1;
}

// 153 旋转排序数组中的最小值
int findMin(vector<int> &nums)
{
    int left = 0, right = nums.size() - 1;
    int mid = 0;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (nums[left] <= nums[mid] && nums[mid] <= nums[right])
        {
            return nums[left];
        }

        if (nums[left] <= nums[mid]) // 左侧 等于也没事,我们+1肯定跳过这个
        {
            left = mid + 1;
        }
        else
        {
            right = mid; // 这里不能加1了,因为right可能就是结果,我们上面没有做 == 判断
        }
    }
    return -1;
}

int find(vector<int> &nums1, int i, vector<int> &nums2, int j, int k)
{
    if (nums1.size() - i > nums2.size() - j)
    {
        return find(nums2, j, nums1, i, k);
    }
    if (nums1.size() <= i)
    {
        return nums2[j + k - 1];
    }
    if (k == 1)
    {
        return min(nums1[i], nums2[j]);
    }

    int idx1 = min((int)nums1.size(), i + k / 2);
    int idx2 = j + k - k / 2;

    if(nums1[idx1 - 1] < nums2[idx2 - 1]){
        return find(nums1, idx1, nums2, j, k - (idx1 - i));
    }else{
        return find(nums1, i, nums2, idx2, k-(idx2 - j));
    }
}

double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
{
    int n = nums1.size() + nums2.size();
    if (n % 2 == 0)
    {
        int left = find(nums1, 0, nums2, 0, n / 2);
        int right = find(nums1, 0, nums2, 0, n / 2 + 1);
        return (left + right) / 2.0;
    }
    else
    {
        // 奇数
        return find(nums1, 0, nums2, 0, n / 2 + 1);
    }
}

// 1 3
// 2 4
// 2