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

struct Comp
{
    bool operator()(int a, int b)
    {
        return a > b;
    }
};
// 215 数组中的第k个最大元素
int findKthLargest(vector<int> &nums, int k)
{
    priority_queue<int, vector<int>, Comp> pq; // 小顶堆
    for (int num : nums)
    {
        // 留存下来最大的k个
        pq.push(num);
        if (pq.size() > k)
        {
            pq.pop();
        }
    }
    return pq.top();
}

struct KComp
{
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        return a.second > b.second;
    }
};
// 347 前k个高频元素
vector<int>
topKFrequent(vector<int> &nums, int k)
{
    unordered_map<int, int> countMap; // num, freq
    vector<int> ans;
    for (int num : nums)
    {
        countMap[num]++;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, KComp> pq;
    for (auto it : countMap)
    {
        pq.push(it);
        if (pq.size() > k)
        {
            pq.pop();
        }
    }
    for (int i = 0; i < k; i++)
    {
        ans.push_back(pq.top().first);
        pq.pop();
    }
    return ans;
}

class minComp
{
    public:
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

class maxComp
{
    public:
    bool operator()(int a, int b)
    {
        return a < b;
    }
};
// 295 数据流的中位数
class MedianFinder
{
public:
    MedianFinder()
    {
    }

    void addNum(int num)
    { // maxHeap用于存放比中位数小的
        if (maxHeap.size() == 0 || num <= maxHeap.top())
        {
            maxHeap.push(num);
            if (maxHeap.size() - minHeap.size() > 1)
            {
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            }
        }
        else
        { // 存放比中位数大的
            minHeap.push(num);
            if (minHeap.size() > maxHeap.size())
            {
                maxHeap.push(minHeap.top());
                minHeap.pop();
            }
        }
    }

    double findMedian()
    {
        if ((maxHeap.size() + minHeap.size()) % 2 == 0)
        {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
        else
        {
            return maxHeap.top();
        }
    }

private:
    priority_queue<int, vector<int>, minComp> minHeap;
    priority_queue<int, vector<int>, maxComp> maxHeap;
};