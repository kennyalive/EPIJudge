#include <vector>
#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include <unordered_map>
using std::unordered_map;
using std::vector;

unique_ptr<BinaryTreeNode<int>> build_subtree(
    vector<int>::const_iterator pstart,
    vector<int>::const_iterator istart, vector<int>::const_iterator iend)
{
    auto root = std::make_unique<BinaryTreeNode<int>>(*pstart);
    auto inorder_root_it = std::find(istart, iend, root->data);

    int left_node_count = inorder_root_it - istart;
    if (left_node_count)
        root->left = build_subtree(pstart+1, istart, istart + left_node_count);

    int right_node_count = iend - inorder_root_it - 1;
    if (right_node_count)
        root->right = build_subtree(pstart + left_node_count + 1, istart + left_node_count + 1, iend);
    return root;
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
    if (preorder.empty())
        return nullptr;
   return build_subtree(preorder.begin(), inorder.begin(), inorder.end());
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
