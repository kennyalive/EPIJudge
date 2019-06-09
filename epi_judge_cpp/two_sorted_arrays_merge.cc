#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

void MergeTwoSortedArrays(vector<int>& A, int m, const vector<int>& B, int n) {
    for (int i = 0; i < m; i++)
        A[m+n-1-i] = A[m-1-i];

    auto a_iter = A.begin() + n;
    auto a_end = a_iter + m;
    auto b_iter = B.begin();
    auto b_end = B.begin() + n;

    auto a_cur = A.begin();

    while (a_iter != a_end && b_iter != b_end) {
        if (*a_iter < *b_iter)
            *a_cur++ = *a_iter++;
        else
            *a_cur++ = *b_iter++;
    }
    if (a_iter != a_end)
        std::copy(a_iter, a_end, a_cur);
    else
        std::copy(b_iter, b_end, a_cur);
}
vector<int> MergeTwoSortedArraysWrapper(vector<int> A, int m,
                                        const vector<int>& B, int n) {
  MergeTwoSortedArrays(A, m, B, n);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "m", "B", "n"};
  return GenericTestMain(
      args, "two_sorted_arrays_merge.cc", "two_sorted_arrays_merge.tsv",
      &MergeTwoSortedArraysWrapper, DefaultComparator{}, param_names);
}
