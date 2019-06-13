#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

bool HasThreeSum(vector<int> A, int t) {
    std::sort(A.begin(), A.end());
    for (int i : A) {
        int value_to_find = t - i;
        int left = 0;
        int right = (int)A.size() - 1;
        while (left <= right) {
            int sum = A[left] + A[right];
            if (sum == value_to_find)
                return true;
            if (sum > value_to_find)
                right--;
            else // sum < value_to_find
                left++;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
                         DefaultComparator{}, param_names);
}
