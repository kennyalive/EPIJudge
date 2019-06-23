#include <string>
#include "test_framework/generic_test.h"
using std::string;

bool IsPalindrome(const string& s) {
    if (s.empty())
        return true;

    int left = 0;
    while (left < s.length() && !isalnum(s[left]))
        left++;
    int right = (int)s.length()-1;
    while (right >= 0 && !isalnum(s[right]))
        right--;

    while (left < right) {
        if (tolower(s[left]) != tolower(s[right]))
            return false;
        left++;
        while (left < s.length() && !isalnum(s[left]))
            left++;
        right--;
        while (right >= 0 && !isalnum(s[right]))
            right--;
    }
    return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
