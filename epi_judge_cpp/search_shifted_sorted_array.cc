#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int sorted_cyclic_array_min_index(const vector<int>& a) {
	int left = 0;
	int right = (int)a.size() - 1;
    while (a[left] > a[right]) {
        int middle = left + (right - left)/2;
        if (a[left] <= a[middle])
            left = middle+1;
        else
            right = middle;
    }
	return left;
}


int SearchSmallest(const vector<int>& A) {
    return sorted_cyclic_array_min_index(A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}
