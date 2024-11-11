#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <climits>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void inTraversal(TreeNode *root, vector<int> &result)
{
    if (root == nullptr)
        return;
    inTraversal(root->left, result);
    result.push_back(root->val);
    inTraversal(root->right, result);
}
vector<int> inorderTraversal1(TreeNode *root)
{
    vector<int> result;
    inTraversal(root, result);
    return result;
}

vector<int> inorderTraversal(TreeNode *root)
{
    // 先到最左边,直到左边没有了,那么我就可以打印了,我打印完再去右边
    vector<int> result;
    if (root == nullptr)
        return result;
    stack<TreeNode *> sta;
    TreeNode *cur = root;
    while (cur != nullptr || !sta.empty())
    {
        if (cur != nullptr)
        {
            sta.push(cur);
            cur = cur->left;
        }
        else
        {
            cur = sta.top();
            sta.pop();
            result.push_back(cur->val);
            cur = cur->right;
        }
    }
    return result;
}

void traversal1(TreeNode *node, vector<int> &ret)
{
    if (node == nullptr)
        return;
    ret.push_back(node->val);
    traversal1(node->left, ret);
    traversal1(node->right, ret);
}
// 迭代前序遍历
vector<int> iterPreorderTraversal(TreeNode *root)
{
    vector<int> ret;
    stack<TreeNode *> sta;
    if (root == nullptr)
    {
        return ret;
    }
    sta.push(root);
    while (!sta.empty())
    {
        TreeNode *temp = sta.top();
        ret.push_back(temp->val);
        sta.pop();
        if (temp->right)
            sta.push(temp->right);
        if (temp->left)
            sta.push(temp->left);
    }
    return ret;
}

int maxDepth(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

TreeNode *invertTree(TreeNode *root)
{
    if (root == nullptr)
        return root;
    TreeNode *left = invertTree(root->left);
    TreeNode *right = invertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
}

bool symTraversal(TreeNode *l, TreeNode *r)
{

    if (l == nullptr && r == nullptr)
        return true;
    if ((l != nullptr && r == nullptr) ||
        (l == nullptr && r != nullptr) ||
        (l->val != r->val))
    {
        return false;
    }
    bool outside = symTraversal(l->left, r->right);
    bool inside = symTraversal(l->right, r->left);
    return outside && inside;
}
bool isSymmetric(TreeNode *root)
{
    return symTraversal(root->left, root->right);
}

int result = -1;
int depthTraversal(TreeNode *root) // 求以root为节点的深度
{
    if (root == nullptr)
        return 0;
    int leftDepth = depthTraversal(root->left);
    int rightDepth = depthTraversal(root->right);
    result = max(result, leftDepth + rightDepth + 1);
    return max(leftDepth, rightDepth) + 1;
}
int diameterOfBinaryTree(TreeNode *root)
{
    depthTraversal(root);
    return result - 1;
}
// 层序遍历
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> result;
    queue<TreeNode *> que;
    if (root == nullptr)
    {
        return result;
    }
    que.push(root);
    while (!que.empty())
    {
        vector<int> level;
        int levelSize = que.size();
        for (int i = 0; i, i < levelSize; i++)
        {
            TreeNode *temp = que.front();
            level.push_back(que.front()->val);
            que.pop();
            if (temp->left)
                que.push(temp->left);
            if (temp->right)
                que.push(temp->right);
        }
        result.push_back(level);
    }
    return result;
}

#if 0

TreeNode* formBST(vector<int>& nums, int l, int r){
    if(l > r) return nullptr;
    int mid = l + (r - l) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = formBST(nums, l, mid - 1);
    root->right = formBST(nums, mid + 1, r);
    return root;
}
//108 有序数组转成二叉搜索树
TreeNode *sortedArrayToBST(vector<int> &nums)
{
    return formBST(nums, 0, nums.size() - 1);
}
#endif

#if 0
bool isValid(TreeNode *root, long long l, long long r)
{
    if (root == nullptr)
        return true;
    if (root->val < l || root->val > r)
        return false;
    bool left = isValid(root->left, l, root->val);
    bool right = isValid(root->right, root->val, r);
    return left && right;
}
// 98 验证二叉搜索树
bool isValidBST(TreeNode *root)
{
    return isValid(root, LONG_LONG_MIN, LONG_LONG_MAX);
}
#endif 

#if 0
//230 二叉搜索树种的第k小元素
void traversalKSmall(TreeNode* root, vector<int>& vec){
    if(root == nullptr) return;
    traversalKSmall(root->left, vec);
    vec.push_back(root->val);
    traversalKSmall(root->right, vec);
}
int kthSmallest(TreeNode *root, int k)
{
    vector<int> vec;
    traversalKSmall(root, vec);
    return vec[k - 1];
}
#endif

#if 0
//199 二叉树的右视图
vector<int> rightSideView(TreeNode *root)
{
    vector<int> result;
    if(root == nullptr) return result;
    queue<TreeNode*> que;
    que.push(root);
    while(!que.empty()){
        int size = que.size();
        TreeNode* temp = nullptr;
        for(int i = 0; i < size; i++){
            temp = que.front();
            que.pop();
            if(temp->left) que.push(temp->left);
            if(temp->right) que.push(temp->right);
        }
        result.push_back(temp->val);
    }
    return result;
}
#endif

#if 0
TreeNode *listNext = nullptr;
void flatten(TreeNode *root)
{
    if(root == nullptr) return;
    flatten(root->right);
    flatten(root->left);
    root->left = nullptr;
    root->right = listNext;
    listNext = root;
}
// 114 二叉树展开为链表
void flatten(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    stack<TreeNode *> sta;
    sta.push(root);
    TreeNode *prev = nullptr;
    while (!sta.empty())
    {
        TreeNode *temp = sta.top();
        sta.pop();
        if (prev != nullptr)
        {
            prev->left = nullptr;
            prev->right = temp;
        }
        if(temp->right) sta.push(temp->right);
        if(temp->left) sta.push(temp->left);
        prev = temp;
    };
}
#endif

#if 0
TreeNode *buildTreeTraversal(vector<int> &preorder, vector<int> &inorder, int preStart, int preEnd, int inStart, int inEnd)
{
    if (preStart > preEnd || inStart > inEnd)
        return nullptr;
    TreeNode *root = new TreeNode(preorder[preStart]);
    int rootIndex = -1;
    for (int i = inStart; i <= inEnd; i++) //找到root在in中位置
    {
        if (inorder[i] == preorder[preStart])
            rootIndex = i;
    }
    int leftTreeSize = rootIndex - inStart;
    //左子树大小为rootIndex - inStart
    // 左子树
    root->left =  buildTreeTraversal(preorder, inorder, preStart + 1, preStart + 1 + leftTreeSize - 1, inStart, inStart + leftTreeSize - 1);
    root->right = buildTreeTraversal(preorder, inorder, preStart + 1 + leftTreeSize, preEnd, rootIndex + 1, inEnd); 
    return root;
}
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    return buildTreeTraversal(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
}
#endif

#if 0
//437路径之和
//cur - start = target
//cur - target = start
unordered_map<long long, int> prefix; //前面的数字和,与出现次数
int backtrack(TreeNode* root, long long cur, int targetSum){
    if(root == nullptr) return 0;
    int ret = 0;
    cur += root->val;

    if(prefix[cur - targetSum] > 0){
        ret += prefix[cur - targetSum];
    }

    prefix[cur]++;
    ret += backtrack(root->left, cur, targetSum);
    ret += backtrack(root->right, cur, targetSum);
    prefix[cur]--;
    return ret;
}
int pathSum(TreeNode *root, int targetSum)
{
    prefix[0] = 1;
    return backtrack(root, 0, targetSum);
}
#endif

// 236 二叉树的最近公共祖先
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (root == p || root == q || root == nullptr)
        return root;
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if (left && right)
        return root;
    else if (left && !right)
        return left;
    else if (!left && right)
        return right;
    else
        return nullptr;
}

int ans = INT_MIN;
int depth(TreeNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int l = depth(root->left);
    int r = depth(root->right);
    ans = max(ans, l + r + root->val);
    return max(0, max(l, r) + root->val);
}
// 124 二叉树中的最大路径
int maxPathSum(TreeNode *root)
{
    depth(root);
    return ans;
}