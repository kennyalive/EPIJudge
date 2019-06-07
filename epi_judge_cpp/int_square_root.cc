#include "test_framework/generic_test.h"

int SquareRoot(int k) {
    int L = 0;
    int U = std::min(k, 46340);

    int R;
    while (L <= U) {
        int M = L + (U - L)/2;
        if (M*M < k) {
            L = M + 1;
            R = M;
        }
        else if (M*M == k) {
            return M;
        }
        else { // M*M > k
            U = M - 1;
        }
    }
    return R;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
