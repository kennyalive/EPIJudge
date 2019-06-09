#include <memory>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool check_bst_node(const unique_ptr<BinaryTreeNode<int>>& node, int min, int max) {
    if (!node)
        return true;

    if (node->data < min || node->data > max)
        return false;

    return check_bst_node(node->left, min, node->data) &&
           check_bst_node(node->right, node->data, max);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
    return check_bst_node(tree, INT_MIN, INT_MAX);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
