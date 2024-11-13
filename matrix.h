

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

void setZeroes(vector<vector<int>> &matrix)
{
    int m = matrix.size(), n = matrix[0].size();
    vector<int> row(m), col(n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 0)
            {
                row[i] = 1;
                col[j] = 1;
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (row[i] == 1 || col[j] == 1)
            {
                matrix[i][j] = 0;
            }
        }
    }
}

vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    vector<int> ans;
    int m = matrix.size(), n = matrix[0].size();
    if (m == 1)
    {
        for (int i = 0; i < n; i++)
        {
            ans.push_back(matrix[0][i]);
        }
        return ans;
    }
    if (n == 1)
    {
        for (int i = 0; i < m; i++)
        {
            ans.push_back(matrix[i][0]);
        }
        return ans;
    }
    int minEdge = min(m, n);
    int round = minEdge / 2;
    int rowLen = m - 1;
    int colLen = n - 1;
    int startX = 0, startY = 0;
    while (round--)
    {
        // up
        for (int i = 0; i < colLen; i++)
        {
            ans.push_back(matrix[startX][startY + i]);
        }
        // right
        for (int i = 0; i < rowLen; i++)
        {
            ans.push_back(matrix[startX + i][startY + colLen]);
        }
        // down
        for (int i = 0; i < colLen; i++)
        {
            ans.push_back(matrix[startX + rowLen][startY + colLen - i]);
        }
        // left
        for (int i = 0; i < rowLen; i++)
        {
            ans.push_back(matrix[startX + rowLen - i][startY]);
        }
        startX += 1;
        startY += 1;
        rowLen -= 2;
        colLen -= 2;
    }

    if (minEdge % 2 == 1)
    {
        if (m <= n)
        {
            for (int i = 0; i < colLen + 1; i++)
            {
                ans.push_back(matrix[startX][startY + i]);
            }
        }
        else
        {
            for (int i = 0; i < rowLen + 1; i++)
            {
                ans.push_back(matrix[startX + i][startY]);
            }
        }
    }
    return ans;
}

void rotate(vector<vector<int>> &matrix)
{
    int m = matrix.size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < i; j++)
        {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m / 2; j++)
        {
            swap(matrix[i][j], matrix[i][m - j - 1]);
        }
    }
}

bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int m = matrix.size(), n = matrix[0].size();
    int startX = 0, startY = n - 1;
    while (startX < m && startY >= 0)
    {
        if (matrix[startX][startY] == target)
        {
            return true;
        }
        else if (matrix[startX][startY] > target)
        {
            startY--;
        }
        else
        {
            startX++;
        }
    }
    return false;
}