#ifndef __LL_BINARYSORTTREE_H__
#define __LL_BINARYSORTTREE_H__
template <class T>
struct TreeNode {
    T val;
    int bf; // balance factor
    TreeNode* lchild;
    TreeNode* rchild;
    TreeNode(const T& val) : val(val), lchild(nullptr), rchild(nullptr) {}
};
template <class T>
class BinarySortTree {
   private:
    TreeNode* root;

   public:
    bool helper(const int& val, TreeNode* node, bool is_insert) {
        if (node == nullptr){
            if(is_insert){
                auto tmp = new TreeNode(val);
                node = tmp;
                return true;
            }else{
                return false;
            }
        }
        else if (val = node->val){
            if)
        }
        else if (val < node->val)
            return search_aux(val, node->left);
        else
            return search_aux(val, node->right);
    }
    bool search(const int& val) {
        auto tmp = root;
        return helper(val, tmp, false);
    }
};
#endif