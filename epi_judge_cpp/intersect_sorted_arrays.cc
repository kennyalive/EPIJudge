#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
    // A)
    /*
    auto a_iter = A.begin();
    auto b_iter = B.begin();
    std::vector<int> result;
    while (a_iter != A.end() && b_iter != B.end()) {
        if (*b_iter < *a_iter) {
            ++b_iter;
        }
        else if (*a_iter < *b_iter) {
            ++a_iter;
        }
        else {
            int value = *a_iter;
            result.push_back(value);
            while (a_iter != A.end() && *a_iter == value)
                ++a_iter;
            while (b_iter != B.end() && *b_iter == value)
                ++b_iter;
        }
    }
    return result;
    */

    // B)
    const auto& a = A.size() <= B.size() ? A : B;
    const auto& b = A.size() > B.size() ? A : B;
    auto b_iter = b.begin();
    std::vector<int> result;
    for (int i = 0; i < (int)a.size() && b_iter != b.end(); i++) {
        if (i == 0 || a[i-1] != a[i]) {
            b_iter = std::lower_bound(b_iter, b.end(), a[i]);
            if (b_iter != b.end() && *b_iter == a[i])
                result.push_back(a[i]);
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
