#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int compute_levenshtein_distance(const std::string& A, int a_idx, const std::string& B, int b_idx, std::vector<int>& distance_cache) {
    if (a_idx == (int)A.size())
        return (int)B.size() - b_idx;
    if (b_idx == (int)B.size())
        return (int)A.size() - a_idx;

    int cache_index = b_idx*(int)A.size() + a_idx;
    if (distance_cache[cache_index] != -1)
        return distance_cache[cache_index];

    if (A[a_idx] == B[b_idx])
        return compute_levenshtein_distance(A, a_idx+1, B, b_idx+1, distance_cache);

    int replace_current_char = compute_levenshtein_distance(A, a_idx+1, B, b_idx + 1, distance_cache);
    int delete_current_char = compute_levenshtein_distance(A, a_idx+1, B, b_idx, distance_cache);
    int insert_new_char = compute_levenshtein_distance(A, a_idx, B, b_idx+1, distance_cache);

    int distance = 1 + std::min(replace_current_char, std::min(delete_current_char, insert_new_char));
    distance_cache[cache_index] = distance;
    return distance;
}

int LevenshteinDistance(const string& A, const string& B) {
    std::vector<int> distance_cache(A.size()*B.size(), -1); 
    return compute_levenshtein_distance(A, 0, B, 0, distance_cache);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
