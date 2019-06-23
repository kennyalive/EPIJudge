#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
bool is_valid_sudoku(const vector<vector<int>>& assignment) {
	vector<int> has_value(10);

	// rows
	for (int i = 0; i < 9; i++) {
		fill(has_value.begin(), has_value.end(), 0);
		for (int k = 0; k < 9; k++) {
            int v = assignment[i][k]; 
			if (v) {
				if (has_value[v]) return false;
				has_value[v] = 1;
			}
		}
	}

	// columns
	for (int i = 0; i < 9; i++) {
		fill(has_value.begin(), has_value.end(), 0);
		for (int k = 0; k < 9; k++) {
            int v = assignment[k][i]; 
			if (v) {
				if (has_value[v]) return false;
				has_value[v] = 1;
			}
		}
	}

	// grid squares
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			fill(has_value.begin(), has_value.end(), 0);
			for (int x = 0; x < 3; x++)
				for (int y = 0; y < 3; y++)
				{
					int r = i*3 + x;
					int c = j*3 + y;
                    int v = assignment[r][c]; 
					if (v) {
						if (has_value[v]) return false;
						has_value[v] = 1;
					}
				}
        }
	return true;
}


// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
    return is_valid_sudoku(partial_assignment);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
