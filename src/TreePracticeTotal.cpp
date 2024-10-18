#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
};
/*
题目的关键是要用额外的vector存储每个节点的指针，先更新vector再更新左右孩子
*/
TreeNode *buildTree(vector<int> &nums)
{

    if (nums.size() == 0)
    {
        return nullptr;
    }
    TreeNode *head = new TreeNode(nums[0]);
    vector<TreeNode *> node(nums.size());
    node[0] = head;

    for (int i = 0; i <= nums.size() - 1; i++)
    {
        if (2 * i + 1 < nums.size())
        {
            node[2 * i + 1] = new TreeNode(nums[2 * i + 1]);
            if (node[2 * i + 1]->val == -1)
            {
                node[2 * i + 1] = nullptr;
            }
            node[i]->left = node[2 * i + 1];
        }
        if (2 * i + 2 < nums.size())
        {
            node[2 * i + 2] = new TreeNode(nums[2 * i + 2]);
            if (node[2 * i + 2]->val == -1)
            {
                node[2 * i + 2] = nullptr;
            }
            node[i]->right = node[2 * i + 2];
        }
    }
    return head;
}
/*
后续遍历删除树，因为先删除根节点就找不到右节点了
*/
void deleteTree(TreeNode *head)
{
    if (head == nullptr)
    {
        return;
    }
    deleteTree(head->left);
    deleteTree(head->right);
    delete (head);
}
/*
用栈做前序遍历
*/
vector<int> PreOrderWithStack(TreeNode *head)
{
    vector<int> result;
    if (head == nullptr)
    {
        return result;
    }

    stack<TreeNode *> stk;
    stk.push(head);
    while (!stk.empty())
    {
        TreeNode *temp = stk.top();
        result.push_back(temp->val);
        stk.pop();
        if (temp->right != nullptr)
        {
            stk.push(temp->right);
        }
        if (temp->left != nullptr)
        {
            stk.push(temp->left);
        }
    }
    return result;
}
/*
后序遍历只需要根右左然后reverse即可
*/
/*
dfs中序遍历需要一直访问左子树然后再右子树
*/
vector<int> InorderWithStack(TreeNode *head)
{
    vector<int> result;
    if (head == nullptr)
    {
        return result;
    }
    stack<TreeNode *> stk;
    TreeNode *curr = head;
    while (!stk.empty() || curr != nullptr)
    {
        while (curr != nullptr)
        {
            stk.push(curr);
            curr = curr->left;
        }
        curr = stk.top();
        stk.pop();
        result.push_back(curr->val);
        curr = curr->right;
    }
    return result;
}

/*
Example:

        3
    5        1
  6  2     0  8
    7  4
Input: root = [3,5,1,6,2,0,8,null,null,7,4]
*/
int main()
{
    vector<int> nums = {3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4};
    TreeNode *head = buildTree(nums);

    return 0;
}