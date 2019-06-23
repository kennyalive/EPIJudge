#include "test_framework/generic_test.h"
long long Reverse(int x) {
    bool sign = x < 0;
    long long k = x;
    if (sign)
        k = -k;

    long long reversed = 0;
    while (k) {
        reversed = reversed*10 + k%10;
        k /= 10;
    }
    if (sign)
        reversed = -reversed;
    return reversed;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
