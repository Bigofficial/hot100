
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
void dfs(vector<vector<char>> &grid, int x, int y, int row, int col)
{
    if (grid.size() == 0)
    {
        return;
    }
    grid[x][y] = '0';
    // up
    if (x - 1 >= 0 && grid[x - 1][y] == '1')
    {
        dfs(grid, x - 1, y, row, col);
    }
    // right
    if (y + 1 < col && grid[x][y + 1] == '1')
    {
        dfs(grid, x, y + 1, row, col);
    }
    // down
    if (x + 1 < row && grid[x + 1][y] == '1')
    {
        dfs(grid, x + 1, y, row, col);
    }
    // left
    if (y - 1 >= 0 && grid[x][y - 1] == '1')
    {
        dfs(grid, x, y - 1, row, col);
    }
}
int numIslands(vector<vector<char>> &grid)
{
    int row = grid.size();
    int col = grid[0].size();
    int ans = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j] == '1')
            {
                ans++;
                dfs(grid, i, j, row, col);
            }
        }
    }
    return ans;
}

int numIslandsBFS(vector<vector<char>> &grid)
{
    int row = grid.size();
    int col = grid[0].size();
    int ans = 0;
    queue<pair<int, int>> que;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j] == '1')
            {
                ans++;
                grid[i][j] = '0';
                que.push({i, j});
                while (!que.empty())
                {
                    auto pos = que.front();
                    que.pop();
                    int x = pos.first, y = pos.second;
                    if (x - 1 >= 0 && grid[x - 1][y] == '1')
                    {
                        grid[x - 1][y] = '0';
                        que.push({x - 1, y});
                    }
                    if (y + 1 < col && grid[x][y + 1] == '1')
                    {
                        grid[x][y + 1] = '0';
                        que.push({x, y + 1});
                    }
                    if (x + 1 < row && grid[x + 1][y] == '1')
                    {
                        grid[x + 1][y] = '0';
                        que.push({x + 1, y});
                    }
                    if (y - 1 >= 0 && grid[x][y - 1] == '1')
                    {
                        grid[x][y - 1] = '0';
                        que.push({x, y - 1});
                    }
                }
            }
        }
    }
    return ans;
}

// 994 腐烂的橘子
int orangesRotting(vector<vector<int>> &grid)
{
    int row = grid.size(), col = grid[0].size();
    queue<pair<int, int>> q; // hoard the rot pos
    int freshCount = 0;
    int minutes = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j] == 1)
                freshCount++;
            else if (grid[i][j] == 2)
                q.push({i, j});
        }
    }

    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (!q.empty())
    {
        int n = q.size();
        bool rotten = false;
        for (int i = 0; i < n; i++)
        {
            auto pos = q.front();
            q.pop();
            for (auto cur : dirs)
            {
                int i = pos.first + cur.first;
                int j = pos.second + cur.second;
                if (i >= 0 && i < row && j >= 0 && j < col && grid[i][j] == 1)
                {
                    grid[i][j] = 2;
                    q.push({i, j});
                    freshCount--;
                    rotten = true;
                }
            }
        }
        if (rotten)
            minutes++;
    }
    return freshCount ? -1 : minutes;
}

//[a, b]  b->a
bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
{
    vector<int> ingree(numCourses, 0);         // indgree
    unordered_map<int, vector<int>> preCourse; // 先修课程 [课程, 后修课程]
    for (int i = 0; i < prerequisites.size(); i++)
    {
        // 0要学课程,1先修课程
        preCourse[prerequisites[i][1]].push_back(prerequisites[i][0]);
        ingree[prerequisites[i][0]]++; // 入度  [a, b]前面的课程入度增加
    }
    queue<int> q;
    int count = 0;
    for (int i = 0; i < numCourses; i++)
    {
        if (!ingree[i])
        {
            q.push(i);
            ++count;
        } // 放入入度为0节点
    }
    while (!q.empty())
    {
        int cur = q.front(); // 节点号
        q.pop();
        for (int i = 0; i < preCourse[cur].size(); i++)
        {
            --ingree[preCourse[cur][i]];
            if (!ingree[preCourse[cur][i]])
            {
                q.push(preCourse[cur][i]);
                ++count;
            }
        }
    }
    if (count == numCourses)
        return true;
    return false;
}

class Trie
{
private:
    bool isEnd;
    Trie *next[26];

public:
    Trie()
    {
        isEnd = false;
        memset(next, 0, sizeof(next));
    }

    void insert(string word)
    {
        Trie* node = this;
        for(char c : word){
            if(node->next[c - 'a'] == nullptr){
                node->next[c - 'a'] = new Trie();
            }
            node = node->next[c - 'a'];
        }
        node->isEnd = true;
    }

    bool search(string word)
    {
        Trie* node = this;
        for(char c : word){
            node = node->next[c - 'a'];
            if(node == nullptr){
                return false;
            }
        }
        return node->isEnd;
    }

    bool startsWith(string prefix)
    {
        Trie* node = this;
        for(char c : prefix){
            node = node->next[c - 'a'];
            if(node == nullptr){
                return false;
            }
        }
        return true;
    }
};