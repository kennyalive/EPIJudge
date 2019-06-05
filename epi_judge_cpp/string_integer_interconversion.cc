#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
    bool negative = x < 0;
    std::string s;
    do {
        s.push_back(std::abs(x%10) + '0');
        x /= 10;
    } while (x);
    if (negative)
        s.push_back('-');
    std::reverse(s.begin(), s.end());
    return s;
}

int StringToInt(const string& s) {
    int x = 0;
    for (int i = (s[0]=='-' ? 1 : 0); i < (int)s.length(); i++) {
        x = x*10 + (s[0] == '-' ? -1 : 1) * (s[i] - '0');
    }
   return x;
}
void Wrapper(int x, const string& s) {
  if (IntToString(x) != s) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
