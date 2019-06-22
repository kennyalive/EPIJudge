#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Event {
  int start, finish;
};

// A
int compute_max_event_concurency(const vector<Event>& events) {
	int latest = -1;
	for (const auto& e : events)
		if (e.finish > latest)
			latest = e.finish;

	vector<int> timeline(latest + 1, 0);
	for (const auto& e : events) {
		for (int k = e.start; k <= e.finish; k++)
			timeline[k]++;
    }
    return *std::max_element(timeline.begin(), timeline.end());
}


int FindMaxSimultaneousEvents(const vector<Event>& A) {
    // A)
    return compute_max_event_concurency(A);
  
}
template <>
struct SerializationTraits<Event> : UserSerTraits<Event, int, int> {};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}
