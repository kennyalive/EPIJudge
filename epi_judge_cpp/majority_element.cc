#include <string>
#include <vector>
#include "test_framework/generic_test.h"
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

string MajoritySearch(vector<string>::const_iterator stream_begin,
                      const vector<string>::const_iterator stream_end) {
    // A)
    /*
    unordered_map<string, int> element_count;
    string result;
    int count= 0;
    for (; stream_begin != stream_end; stream_begin++) {
        const string& e = *stream_begin;
        int n = ++element_count[e];
        if (n > count) {
            count = n;
            result = e;
        }
    }
    return result;
    */
    // B)
    int count = 0;
    string candidate;
    while (stream_begin != stream_end) {
        if (count == 0)
            candidate = *stream_begin;

        if (candidate == *stream_begin)
            ++count;
        else
            --count;

        ++stream_begin;
    }
    return candidate;
}
string MajoritySearchWrapper(const vector<string>& stream) {
  return MajoritySearch(cbegin(stream), cend(stream));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream"};
  return GenericTestMain(args, "majority_element.cc", "majority_element.tsv",
                         &MajoritySearchWrapper, DefaultComparator{},
                         param_names);
}
