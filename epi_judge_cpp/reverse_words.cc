#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

void ReverseWords(string* s) {
    string& w = *s;
    
    int start = -1;
    for (int i = 0; i < (int)w.length(); i++) {
        if (isspace(w[i]) && start != -1) {
            std::reverse(w.begin() + start, w.begin()+i);
            start = -1;
        }
        else if (!isspace(w[i]) && start == -1) {
            start = i;
        }
    }
    if (start != -1)
        std::reverse(w.begin()+start, w.end());
    std::reverse(w.begin(), w.end());
}
string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}
