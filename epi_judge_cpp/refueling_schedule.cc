#include <vector>
#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
const int kMPG = 20;

// gallons[i] is the amount of gas in city i, and distances[i] is the distance
// city i to the next city.
int FindAmpleCity(const vector<int>& gallons, const vector<int>& distances) {
    std::list<std::pair<int, int>> delta;
    for (int i = 0; i < (int)gallons.size(); i++)
        delta.push_back({i, gallons[i]*kMPG - distances[i]});

    auto iter = delta.begin();
    while ((int)delta.size() != 1) {
        auto next = iter;
        next++;
        if (next == delta.end())
            next = delta.begin();

        if (iter->second >= 0 || iter->second < 0 && next->second <= 0) {
            iter->second += next->second;
            delta.erase(next);
        }
        else {
            ++iter;
            if (iter == delta.end())
                iter = delta.begin();
        }
    }

    return delta.begin()->first;
}

void FindAmpleCityWrapper(TimedExecutor& executor, const vector<int>& gallons,
                          const vector<int>& distances) {
  int result = executor.Run([&] { return FindAmpleCity(gallons, distances); });
  const int num_cities = gallons.size();
  int tank = 0;
  for (int i = 0; i < num_cities; ++i) {
    int city = (result + i) % num_cities;
    tank += gallons[city] * kMPG - distances[city];
    if (tank < 0) {
      throw TestFailure(FmtStr("Out of gas on city {}", i));
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "gallons", "distances"};
  return GenericTestMain(args, "refueling_schedule.cc",
                         "refueling_schedule.tsv", &FindAmpleCityWrapper,
                         DefaultComparator{}, param_names);
}
