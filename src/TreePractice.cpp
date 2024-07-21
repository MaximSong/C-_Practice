#include <__algorithm/max.h>
#include <vector>
class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
    static int Getdepth(TreeNode *root);
    static int KthNode(TreeNode *proot, int k);
    static TreeNode *Mirror(TreeNode *root);
};
int TreeNode::Getdepth(TreeNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int leftDepth = Getdepth(root->left);
    int rightDepth = Getdepth(root->right);
    return std::max(leftDepth, rightDepth) + 1;
}
// 找到第k小的数
void traverse(TreeNode *root, std::vector<int> &vec)
{
    if (root == nullptr)
    {
        return;
    }
    traverse(root->left, vec);
    vec.push_back(root->val);
    traverse(root->right, vec);
}
int TreeNode::KthNode(TreeNode *proot, int k)
{
    int count = 0;
    std::vector<int> temp;
    traverse(proot, temp);
    return temp[k - 1];
}
void MirrorTraverse(TreeNode *proot)
{
    if (proot == nullptr)
    {
        return;
    }
    TreeNode *temp = proot->left;
    proot->left = proot->right;
    proot->right = temp;
    MirrorTraverse(proot->left);
    MirrorTraverse(proot->right);
}
TreeNode *TreeNode::Mirror(TreeNode *proot)
{
    MirrorTraverse(proot);
    return proot;
}
