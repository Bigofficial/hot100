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

// 20 有效括号
bool isValid(string s)
{
    int n = s.size();
    if (n % 2 != 0)
        return false;
    unordered_map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}};
    stack<char> sta;
    for (char c : s)
    {
        if (pairs.count(c))
        { // 键存在
            if (sta.empty() || sta.top() != pairs[c])
            {
                return false;
            }
            sta.pop();
        }
        else
        {
            sta.push(c);
        }
    }
    return sta.empty();
}

// 155 最小栈
class MinStack
{
public:
    MinStack()
    {
    }

    void push(int val)
    {
        if (minSta.empty() || val < minSta.top())
        {
            minSta.push(val);
        }
        else
        {
            minSta.push(getMin());
        }
        sta.push(val);
    }

    void pop()
    {
        sta.pop();
        minSta.pop();
    }

    int top()
    {
        return sta.top();
    }

    int getMin()
    {
        return minSta.top();
    }

private:
    stack<int> sta;
    stack<int> minSta;
};

// 394 字符串解码
string decodeString(string s)
{
    stack<char> sta;
    string ans = "";
    for (char c : s)
    {
        if (c == ']')
        {
            // 取出字符
            string temp = "";
            while (!sta.empty() && sta.top() != '[')
            {
                temp = sta.top() + temp;
                sta.pop();
            }
            sta.pop(); // 弹出[
            string num = "";
            while (!sta.empty() && isdigit(sta.top()))
            {
                num = sta.top() + num;
                sta.pop();
            }
            int rep = stoi(num);
            string repTemp = "";
            while (rep--)
            {
                repTemp += temp;
            }

            // 放回
            for (char r : repTemp)
            {
                sta.push(r);
            }
        }
        else
        {
            sta.push(c);
        }
    }
    while (!sta.empty())
    {
        ans = sta.top() + ans;
        sta.pop();
    }
    return ans;
}

// 739 每日温度
vector<int> dailyTemperatures(vector<int> &temperatures)
{
    stack<int> sta; // 栈从大到小排序
    vector<int> ans(temperatures.size(), 0);
    for (int i = 0; i < temperatures.size(); i++)
    {
        // 栈是有的,我们得比较
        while (!sta.empty() && temperatures[i] > temperatures[sta.top()])
        {
            // 当前温度高于栈顶温度
            ans[sta.top()] = i - sta.top();
            sta.pop();
        }
        sta.push(i);
    }
    return ans;
}

// 84 柱状图中最大的矩形
//算出以每个柱子为高的各个矩形面积
int largestRectangleArea(vector<int> &heights)
{
    //递增单调栈,当要放入元素小于栈顶元素出栈,可以以栈顶元素作为高了
    stack<int> sta;
    int ans = 0;
    heights.push_back(-1); //确保所有元素都算
    for(int i = 0; i < heights.size(); i++){
        while(!sta.empty() && heights[i] < heights[sta.top()]){
            int idx = sta.top();
            sta.pop();
            int left = sta.empty() ? -1 : sta.top();
            ans = max(ans, heights[idx] * (i - left - 1));
        }
        sta.push(i);
    }
    return ans;
}