#include "test_framework/generic_test.h"
#include <vector>
// A)
int F(int xcur, int ycur, int x, int y) {
	if (xcur == x || ycur == y)
		return 1;
	int n = 0;
	if (xcur < x)
		n += F(xcur+1, ycur, x, y);
	if (ycur < y)
		n += F(xcur, ycur+1, x, y);
	return n;
}



int NumberOfWays(int n, int m) {
    // A)
    // return F(1, 1, n, m);  

    // B)
    std::vector<int> A(m, 1);
    std::vector<int> B(m);

    for (int i = 0; i < n-1; i++) {
        B.back() = 1;
        for (int k = m-2; k >= 0; k--)
            B[k] = B[k+1] + A[k];
        std::swap(A, B);
    }
    return A[0];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
