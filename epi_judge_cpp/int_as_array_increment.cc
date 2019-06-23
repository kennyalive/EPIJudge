#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

void increment_arbitrary_integer(vector<int>& number) {
	reverse(number.begin(), number.end());
	bool carry = true;
	for (int i = 0; i < (int)number.size() && carry; i++) {
		if (++number[i] == 10)
			number[i] = 0;
		else
			carry = false;
    }
    if (carry)
        number.push_back(1);
    reverse(number.begin(), number.end());
}

vector<int> PlusOne(vector<int> A) {
    auto result = A;
    increment_arbitrary_integer(result);
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
