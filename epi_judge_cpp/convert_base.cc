#include <string>
#include "test_framework/generic_test.h"
using std::string;

string ConvertBase(const string& num_as_string, int b1, int b2) {
    bool negative = num_as_string[0] == '-';
    int x1 = 0;
    for (int i = (num_as_string[0] == '-' ? 1 : 0); i < (int)num_as_string.length(); i++) {
        char c = num_as_string[i];
        x1 = x1*b1 + (c >= 'A' ? c - 'A' + 10 : c - '0');
    }
    string result;
    do {
        int k = x1 % b2;
        result += k >= 10 ? (k - 10 + 'A') : (k + '0');
        x1 /= b2;
    } while (x1);
    if (negative)
        result += '-';
    std::reverse(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
