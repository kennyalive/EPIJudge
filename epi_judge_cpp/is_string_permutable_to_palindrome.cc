#include <string>
#include "test_framework/generic_test.h"
#include <unordered_map>
using std::unordered_map;
using std::string;

bool can_form_palindrome(const string& s) {
	unordered_map<char, int> count;
	for (char c : s)
		count[c]++;

	int odd_count = 0;
	for (const std::pair<char, int>& p : count) {
        if (p.second%2 != 0)
            odd_count++;
    }
    return odd_count <= 1;
}


bool CanFormPalindrome(const string& s) {
    return can_form_palindrome(s);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
