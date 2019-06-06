#include <memory>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {

    if (!tree)
        return {};
    vector<const BinaryTreeNode<int>*> nodes[2];
    int cur = 0;
    nodes[0].push_back(tree.get());

    std::vector<std::vector<int>> result;
    while (!nodes[cur].empty()) {
        std::vector<int> level;
        nodes[1-cur].resize(0);
        for (const auto& node : nodes[cur]) {
            level.push_back(node->data);
            if (node->left)
                nodes[1-cur].push_back(node->left.get());
            if (node->right)
                nodes[1-cur].push_back(node->right.get());
        }
        result.emplace_back(std::move(level));
        cur = 1-cur;
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
