#include <string>
#include <vector>
#include "test_framework/generic_test.h"
#include <unordered_map>
using std::string;
using std::vector;

int FindNearestRepetition(const vector<string>& paragraph) {
    int min_dist = INT_MAX; 
    std::unordered_map<std::string, int> table;
    for (int i = 0; i < (int)paragraph.size(); i++) {
        const auto& s = paragraph[i];
        auto iter = table.find(s);
        if (iter == table.end())
            table.insert({s, i});
        else {
            min_dist = std::min(min_dist, i - iter->second);
            iter->second = i;
        }
    }
     return min_dist == INT_MAX ? -1 : min_dist;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
