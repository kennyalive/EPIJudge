#include <algorithm>
#include <iterator>
#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

std::vector<std::vector<int>> get_valid_queen_placement(int column, int row_count) {
    if (column == 0) {
        std::vector<std::vector<int>> placements(row_count);
        for (int i = 0; i < row_count; i++)
            placements[i] = {i};
        return placements;
    }

    std::vector<std::vector<int>> result;

    auto placements = get_valid_queen_placement(column - 1, row_count);
    for (auto& placement : placements) {
        for (int r = 0; r < row_count; r++) {
            
            bool valid_placement = true;
            for (int placement_column = 0; placement_column < column; placement_column++) {
                int placement_row = placement[placement_column];
                if (placement_row == r || (column - placement_column == std::abs(r - placement_row))) {
                    valid_placement = false;
                    break;
                }
            }
            if (valid_placement) {
                result.push_back(placement);
                result.back().push_back(r);
            }
        }
    }
    return result;
}

vector<vector<int>> NQueens(int n) {
    return get_valid_queen_placement(n-1, n);
}

bool Comp(vector<vector<int>>& a, vector<vector<int>>& b) {
  std::sort(std::begin(a), std::end(a));
  std::sort(std::begin(b), std::end(b));
  return a == b;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens, &Comp,
                         param_names);
}
