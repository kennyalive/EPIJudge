#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

vector<vector<int>> generate_permutation(const vector<int>& a) {
	vector<vector<int>> result;
	for (int i = 0; i < (int)a.size(); i++) {
		auto a2 = a;
		a2.erase(a2.begin() + i);
		
        auto tail_perms = generate_permutation(a2);
        if (tail_perms.empty())
            result.push_back({a[i]});
        else {
            for (const auto& perm2 : tail_perms) {
                vector<int> perm;
                perm.push_back(a[i]);
                perm.insert(perm.end(), perm2.begin(), perm2.end());
                result.push_back(std::move(perm));
            }
       }
	}
	return result;
}

vector<vector<int>> Permutations(vector<int> A) {
    return generate_permutation(A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "permutations.cc", "permutations.tsv", &Permutations,
      &UnorderedComparator<vector<vector<int>>>, param_names);
}
