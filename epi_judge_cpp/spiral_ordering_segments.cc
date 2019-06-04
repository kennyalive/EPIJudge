#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
    if (square_matrix.empty())
        return std::vector<int>{};
    const int size = (int)square_matrix.size();
    std::vector<int> result(size*size);
    result[0] = square_matrix[0][0];
    int left = 0;
    int right = size-1;
    int top = 0;
    int bottom = size-1;
    int state = 0; // 0 -> horz right, 1 -> vert down, 2 - horz left, 3 - vert up
    int r = 0;
    int c = 0;

    for (int i = 0; i < size*size - 1; i++) {
        if (state == 0) {
            c++;
            if (c == right) {
                state = 1;
                top++;
            }
        }
        else if (state == 1) {
            r++;
            if (r == bottom) {
                state = 2;
                right--;
            }
        }
        else if (state == 2) {
            c--;
            if (c == left) {
                state = 3;
                bottom--;
            }
        }
        else {
            assert(state == 3);
            r--;
            if (r == top) {
                state = 0;
                left++;
            }
        }
        result[i+1] = square_matrix[r][c];
    }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering_segments.cc",
                         "spiral_ordering_segments.tsv", &MatrixInSpiralOrder,
                         DefaultComparator{}, param_names);
}
