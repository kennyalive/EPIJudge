#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool is_subtree_balanced(const BinaryTreeNode<int>& node, int& height) {
    int left_height;
    bool is_left_balanced;
    if (node.left) {
        is_left_balanced = is_subtree_balanced(*node.left.get(), left_height);
    }
    else {
        is_left_balanced = true;
        left_height = 0;
    }

    int right_height;
    bool is_right_balanced;
    if (node.right) {
        is_right_balanced = is_subtree_balanced(*node.right.get(), right_height);
    }
    else {
        is_right_balanced = true;
        right_height = 0;
    }

    height = std::max(left_height, right_height) + 1;
    return is_left_balanced && is_right_balanced && std::abs(left_height - right_height) <= 1;
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
    if (!tree)
        return true;

    int height;
    return is_subtree_balanced(*tree.get(), height);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
