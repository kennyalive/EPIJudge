#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
     struct Deal_Info {
       int time;
       int array_index;
       int array_pos;
       bool operator<(const Deal_Info& other) const {
           return time > other.time;
       }
    };
     std::priority_queue<Deal_Info> heap;
     for (int i = 0; i < (int)sorted_arrays.size(); i++) {
         heap.push({sorted_arrays[i][0], i, 1});
     }
     std::vector<int> result;
     while (!heap.empty()) {
         Deal_Info info = heap.top();
         heap.pop();
         result.push_back(info.time);
         if (info.array_pos < (int)sorted_arrays[info.array_index].size()) {
             heap.push({sorted_arrays[info.array_index][info.array_pos], info.array_index, ++info.array_pos});
         }
     }
     return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
