#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool is_subtrees_symmetric(const BinaryTreeNode<int>* a, const BinaryTreeNode<int>* b) {
    if (a == nullptr && b == nullptr)
        return true;

    if (a == nullptr || b == nullptr || a->data != b->data)
        return false;

    return is_subtrees_symmetric(a->left.get(), b->right.get()) && is_subtrees_symmetric(a->right.get(), b->left.get());
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
    if (!tree)
        return true;

    return is_subtrees_symmetric(tree->left.get(), tree->right.get());
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
