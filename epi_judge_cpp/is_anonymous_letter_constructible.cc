#include <string>
#include "test_framework/generic_test.h"
using std::string;

bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
    int letter_counts[256] = {};
    int magazine_counts[256] = {};

    for (auto c : letter_text)
        letter_counts[c]++;
    for (auto c : magazine_text)
        magazine_counts[c]++;

    for (int i = 0; i < 256; i++)
        if (letter_counts[i] > magazine_counts[i])
            return false;
    return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
