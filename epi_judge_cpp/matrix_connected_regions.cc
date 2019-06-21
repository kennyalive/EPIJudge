#include <deque>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;

void do_paint(vector<deque<bool>>& m, int x, int y, bool expected_value) {
	if (x < 0 || y < 0 || x >= m.size() || y >= m[0].size() ||
        m[x][y] != expected_value)
    {
		return;
    }

    m[x][y] = !expected_value;

	do_paint(m, x-1, y, expected_value);
	do_paint(m, x+1, y, expected_value);
	do_paint(m, x, y-1, expected_value);
	do_paint(m, x, y+1,expected_value);
}

void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {
    do_paint(*image_ptr, x, y, (*image_ptr)[x][y]);
}
vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
