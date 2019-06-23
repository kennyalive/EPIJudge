#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

vector<int> sort_almost_sorted_array(
	vector<int>::const_iterator stream_begin,
	const vector<int>::const_iterator stream_end,
	int k)
{
	std::priority_queue<int, vector<int>, std::greater<int>> heap;
    vector<int> output;
	int n = 0;
	while (stream_begin != stream_end && n++ < k) {
		heap.push(*stream_begin++);
    }

    while (stream_begin != stream_end) {
        output.push_back(heap.top());
        heap.pop();
        heap.push(*stream_begin++);
    }

    while (!heap.empty()) {
        output.push_back(heap.top());
        heap.pop();
    }
    return output;
}


vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {
    return sort_almost_sorted_array(sequence_begin, sequence_end, k);
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
