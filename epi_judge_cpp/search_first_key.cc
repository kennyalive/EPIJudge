#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
    int begin = 0;
    int end = (int)A.size();
 
    while (begin < end) {
        int middle = (begin+end)/2;
        if (A[middle] == k) {
            if (middle == begin || A[middle-1] != k)
                return middle;
            else
                end = middle;
        }
        else if (A[middle] > k)
            end = middle;
        else
            begin = middle+1;
    }
    return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
