#include "test_framework/generic_test.h"
inline int parity_8_bit(uint8_t b) {
    // 0x0 0x1 0x2 0x3 0x4 0x5 0x6 0x7 0x8 0x9 0xa 0xb 0xc 0xd 0xe 0xf
    // 0   1   1   0   1   0   0   1   1   0   0   1   0   1   1   0
    // value = 0x6996

    // A)
    constexpr uint8_t hex_parities[16] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };
    return hex_parities[b >> 4] ^ hex_parities[b & 0xf];

    // B) 
    //return (0x6996 >> (b >> 4))&1 ^ (0x6996 >> (b & 0xf))&1;
}

inline int parity_16_bit(uint16_t k) {
    return parity_8_bit(k >> 8) ^ parity_8_bit(k & 0xff);
}

inline int parity_32_bit(uint32_t k) {
    return parity_16_bit(k >> 16) ^ parity_16_bit(k & 0xffff);
}

inline int parity_64_bit(uint64_t k) {
    return parity_32_bit(k >> 32) ^ parity_32_bit(k & 0xffffffff);
}

short Parity(unsigned long long x) {
    return parity_64_bit(x);
    /*
    static_assert(sizeof(x) == 8, "error");
    int num_ones = 0;
    while (x) {
        num_ones += x&1;
        x >>= 1;
    }
    return num_ones&1;
    */
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
