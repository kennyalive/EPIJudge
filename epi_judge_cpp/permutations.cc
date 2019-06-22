#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

// A).
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

void generate_permutations2(int k, vector<int>& a, vector<vector<int>>& result) {
    if (k == (int)a.size()-1) {
        result.push_back(a);
        return;
    }
    for (int i = k; i < (int)a.size(); i++) {
        std::swap(a[k], a[i]);
        generate_permutations2(k+1, a, result);
        std::swap(a[k], a[i]);
    }
}

vector<vector<int>> Permutations(vector<int> A) {
   // A).
   //return generate_permutation(A);

    // B).
    vector<vector<int>> result;
    generate_permutations2(0, A, result);
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "permutations.cc", "permutations.tsv", &Permutations,
      &UnorderedComparator<vector<vector<int>>>, param_names);
}
