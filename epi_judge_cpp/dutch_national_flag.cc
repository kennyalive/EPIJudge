#include <array>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
typedef enum { kRed, kWhite, kBlue } Color;

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
    auto& a = *A_ptr;
    Color pivot = a[pivot_index];

    // A) 
    /*
    int k = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] < pivot)
            std::swap(a[k++], a[i]);
    }
    for (int i = k; i < (int)a.size(); i++) {
        if (a[i] == pivot)
            std::swap(a[k++], a[i]);
    }
    */

    // B)
    int next_less = 0;
    int next_greater = static_cast<int>(a.size()) - 1;
   
    int i = 0;
    while (i <= next_greater) {
        if (a[i] < pivot) {
            std::swap(a[next_less++], a[i]);
            i++;
        }
        else if (a[i] > pivot) {
            std::swap(a[next_greater--], a[i]);
        }
        else {
            i++;
        }
    }
}

void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[colors[i]]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[colors[i]]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[colors[i]]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}
