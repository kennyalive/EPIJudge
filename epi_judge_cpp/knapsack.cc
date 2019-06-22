#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Item {
  int weight, value;
};

int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
    if (items.empty())
        return 0;

    vector<int> A(capacity + 1);
    vector<int> B(capacity + 1);

    for (int i = 0; i < (int)A.size(); i++)
        A[i] = items[0].weight <= i ? items[0].value : 0;

    for (int k = 1; k < (int)items.size(); k++) {
        for (int i = 0; i < (int)A.size(); i++)
            B[i] = std::max(A[i], items[k].weight <= i ? items[k].value + A[i-items[k].weight] : 0);
        std::swap(A, B);
    }
    return A.back();
}
template <>
struct SerializationTraits<Item> : UserSerTraits<Item, int, int> {};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"items", "capacity"};
  return GenericTestMain(args, "knapsack.cc", "knapsack.tsv",
                         &OptimumSubjectToCapacity, DefaultComparator{},
                         param_names);
}
