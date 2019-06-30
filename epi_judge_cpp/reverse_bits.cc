#include "test_framework/generic_test.h"
#include <vector>
using std::vector;

unsigned long long ReverseBits(unsigned long long x) {
    x = (x >> 32) | (x << 32);
    x = ((x & 0xffff0000ffff0000) >> 16) | ((x & 0x0000ffff0000ffff) << 16);
    x = ((x & 0xff00ff00ff00ff00) >> 8) |  ((x & 0x00ff00ff00ff00ff) << 8);
    x = ((x & 0xf0f0f0f0f0f0f0f0) >> 4) |  ((x & 0x0f0f0f0f0f0f0f0f) << 4);
    x = ((x & 0xcccccccccccccccc) >> 2) |  ((x & 0x3333333333333333) << 2);
    x = ((x & 0xaaaaaaaaaaaaaaaa) >> 1) |  ((x & 0x5555555555555555) << 1);
    return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
