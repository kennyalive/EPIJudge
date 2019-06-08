#include <vector>
#include "test_framework/generic_test.h"
#include <random>
using std::vector;

int partition_relative_to_pivot(std::vector<int>& a, int begin /*incl*/, int end /*incl*/, int pivot_index) {
    int pivot = a[pivot_index];
    std::swap(a[pivot_index], a[end]);

    int middle = begin;
    for (int i = begin; i <= end; i++) {
        if (a[i] >= pivot)
            std::swap(a[i], a[middle++]);
    }
    return middle-1;
}

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
    // A)
    /*
    auto a = *A_ptr;
    std::partial_sort(a.begin(), a.begin() + k, a.end(), [](int a, int b) { return a > b; });
    return a[k-1];
    */

    // B)
    auto a = *A_ptr;
    std::default_random_engine random_engine(std::random_device{}());

    int begin = 0;
    int end = (int)a.size()-1;

    while (true) {
        int pivot_index = std::uniform_int_distribution<>(begin, end)(random_engine);
        int middle = partition_relative_to_pivot(a, begin, end, pivot_index);

        if (middle == k-1)
            return a[middle];
        else if (middle > k-1)
            end = middle-1;
        else // middle < k-1
            begin = middle+1;
    }
}

int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
