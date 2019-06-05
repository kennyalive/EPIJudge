#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
    if (x == INT_MIN)
        return "-2147483648";
    if (x == 0) 
        return "0";
    
    std::string s;
    if (x < 0) {
        s.push_back('-');
        x = -x;
    }
   while (x) {
        s.push_back(x%10 + '0');
        x /= 10;
    }
    std::reverse(s[0] == '-' ? s.begin() + 1 : s.begin(), s.end());
    return s;
}

int StringToInt(const string& s) {
    int x = 0;
    int base = s[0] == '-' ? -1 : 1;
    for (int i = (int)s.length() - 1; i >= (s[0] == '-' ? 1 : 0); i--) {
        x += base * (s[i] - '0');
        base *= 10;
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
