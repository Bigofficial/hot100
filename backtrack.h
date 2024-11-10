#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <climits>
#include <string>
using namespace std;

#if 0 
vector<vector<int>> results;
vector<int> result;
void backtrack(vector<int>& nums, vector<bool>& used){
    if(result.size() == nums.size()){
        results.push_back(result);
        return;
    }

    for(int i = 0; i < nums.size(); i++){
        if(used[i] == true){
            continue;
        }
        result.push_back(nums[i]);
        used[i] = true;
        backtrack(nums, used);
        used[i] = false;
        result.pop_back();
    }
}

vector<vector<int>> permute(vector<int> &nums)
{
    vector<bool> used(nums.size(), false);
    backtrack(nums, used);
    return results;
}
#endif

#if 0
vector<vector<int>> results;
vector<int> result;
void backtrack(vector<int>& nums, int start){
    
    results.push_back(result);

    for(int i = start; i < nums.size(); i++){
        result.push_back(nums[i]);
        backtrack(nums, i+1);
        result.pop_back();
    }
}
vector<vector<int>> subsets(vector<int> &nums)
{
    backtrack(nums, 0);
    return results;
}
#endif

#if 0
const string letterMap[10] = {
    "", //0
    "", //1
    "abc", //2
    "def", //3
    "ghi", //4
    "jkl", //5
    "mno", //6
    "pqrs", //7
    "tuv", //8
    "wxyz", //9
};

vector<string> results;
string result = "";
void backtrack(string digits, int index){
    if(result.size() == digits.size()){
        results.push_back(result);
        return;
    }
    int num = digits[index] - '0';
    string letter = letterMap[num];
    for(int i = 0; i < letter.size(); i++){//这一层也就是当前下标数字对应的字母集合
        result.push_back(letter[i]);
        backtrack(digits, index+1); // 往下一层 digits的index要移动
        result.pop_back();
    } 
}
vector<string> letterCombinations(string digits)
{
    if(digits.size() == 0) return results;
    backtrack(digits, 0);
    return results;
}

#endif

#if 0
vector<vector<int>> results;
vector<int> result;
int sum = 0;
void backtrack(vector<int>& candidates, int target, int index){
    if(sum > target){
        return;
    }
    if(sum == target){
        results.push_back(result);
        return;
    }
    for(int i = index; i < candidates.size(); i++){ 
        //剪枝,只有下一层可以重复使用,这一层不行,下标前面的把情况都考虑
        //如[2,3,7], 2要把223考虑,之后3不能选2了,不会出现322, 也不会出现232,只有223
        result.push_back(candidates[i]);
        sum+=candidates[i];
        backtrack(candidates, target, index);
        sum-=candidates[i];
        result.pop_back();
    }
}
//39 组合总数
vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    backtrack(candidates, target, 0);
    return results;
}
#endif

#if 0
vector<string> results;
string result;
void backtrack(int open, int close, int n){
    if(result.size() == n * 2){
        results.push_back(result);
        return;
    }

    if(open < n){
        result.push_back('(');
        backtrack(open + 1, close, n);
        result.pop_back();
    }
    if(close < open){
        result.push_back(')');
        backtrack(open, close + 1, n);
        result.pop_back();
    }
}
vector<string> generateParenthesis(int n)
{
    backtrack(0, 0, n);
    return results;
}
#endif

#if 0
vector<vector<bool>> isVisited;
string path;
bool result = false;
int direction[4][2] = {
    0, 1,   // 上
    1, 0,   // 右
    -1, 0,  // 左
    0, -1}; // 下

void backtrack(vector<vector<char>> &board, string word, int wordIndex, int curX, int curY)
{
    if (path.size() == word.size() )
    {
        result = true;
        return;
    }
    if (wordIndex > word.size())
        return;

    for (int i = 0; i < 4; i++)
    {
        // 每个节点看四个节点
        int nextX = curX + direction[i][0];
        int nextY = curY + direction[i][1];

        if (nextX < 0 || nextY < 0 || nextX >= board.size() || nextY >= board[0].size() || isVisited[nextX][nextY])
        {
            continue;
        }
        if (board[nextX][nextY] != word[wordIndex])
            continue;

        isVisited[nextX][nextY] = true;
        path += board[nextX][nextY];
        backtrack(board, word, wordIndex + 1, nextX, nextY);
        path.pop_back();
        isVisited[nextX][nextY] = false;
    }
}

bool exist(vector<vector<char>> &board, string word)
{
    int m = board.size(), n = board[0].size();
    isVisited.resize(m, vector<bool>(n, false));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        { // 起点的所有可能性
            if (board[i][j] == word[0])
            {
                isVisited[i][j] = true;
                path += board[i][j];
                backtrack(board, word, 0, i, j);
                path.pop_back();
                isVisited[i][j] = false;
            }
        }
    }
    return result;
}
#endif

#if 0
bool isPanlindrome(string &s, int start, int end)
{
    for (int i = start, j = end; i <= j; i++, j--)
    {
        if (s[i] != s[j])
        {
            return false;
        }
    }
    return true;
}
vector<vector<string>> results;
vector<string> result;
void backtrack(string s, int startIndex){
    if(startIndex >= s.size()){
        results.push_back(result);
        return;
    }

    for(int i = startIndex; i < s.size(); i++){ //同层表示划分位置, 下一层就是划分了.
        if(isPanlindrome(s, startIndex, i)){
            string str = s.substr(startIndex, i - startIndex + 1);
            result.push_back(str);
            backtrack(s, i + 1);
            result.pop_back();
        }
    }
}

vector<vector<string>> partition(string s)
{
    backtrack(s, 0);
    return results;
}

#endif

vector<vector<string>> results;

bool isValid(int x, int y, vector<string> &sol, int n)
{

    // 判断列
    for (int i = 0; i < n; i++)
    {
        if (sol[i][y] == 'Q')
        {
            return false;
        }
    }
    // 判断对角线 只需往前看
    for (int i = x - 1, j = y + 1; i >= 0 && j < n; i--, j++)
    {
        if (sol[i][j] == 'Q')
            return false;
    }

    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (sol[i][j] == 'Q')
            return false;
    }
    return true;
}

void backtrack(int row, int n, vector<string>& result){
    if(row == n){
        results.push_back(result);
        return;
    }

    for(int i = 0; i < n; i++){
        if(isValid(row, i, result, n)){
            result[row][i] = 'Q';
            backtrack(row + 1, n, result);
            result[row][i] = '.';
        }
    }
}
vector<vector<string>> solveNQueens(int n)
{
    vector<string> result(n, string(n, '.'));
    backtrack(0, n, result);
    return results;
}