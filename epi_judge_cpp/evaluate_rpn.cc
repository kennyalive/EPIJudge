#include <string>
#include "test_framework/generic_test.h"
#include <stack>
using std::stack;
using std::string;
int Evaluate(const string& expression) {
    stack<int> values;
    auto it = expression.begin();
    while (it != expression.end()) {
        if ((*it == '+' || *it == '-' || *it == '*' || *it == '/') &&
                (it+1 == expression.end() || *(it+1) == ',')) {
            int arg1 = values.top();
            values.pop();
            int arg0 = values.top();
            values.pop();
            if (*it == '+')
                values.push(arg0 + arg1);
            else if (*it == '-')
                values.push(arg0 - arg1);
            else if (*it == '*')
                values.push(arg0 * arg1);
            else
                values.push(arg0 / arg1);
            ++it;
        }
        else if (*it == ',') {
            ++it;
        }
        else {
            int value = 0;
            bool sign = false;
            if (*it == '-') {
                sign = true;
                ++it;
            }
            while (it != expression.end() && isdigit(*it)) {
                value = value*10 + (*it - '0');
                ++it;
            }
            if (sign)
                value = -value;
            values.push(value);
        }
    }
    return values.top();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
