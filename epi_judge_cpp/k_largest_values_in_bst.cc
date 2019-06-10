#include <memory>
#include <vector>
#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

int get_n_largest(BstNode<int>* node, int n, std::vector<int>& result) {
    if (!node || !n)
        return n;

   n = get_n_largest(node->right.get(), n, result);
   if (n) {
       result.push_back(node->data);
       n--;
   }
   return get_n_largest(node->left.get(), n, result);
}

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
    std::vector<int> result;
    get_n_largest(tree.get(), k, result);
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         &UnorderedComparator<std::vector<int>>, param_names);
}
