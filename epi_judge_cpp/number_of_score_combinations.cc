#include <vector>
#include "test_framework/generic_test.h"
#include <unordered_map>
using std::vector;

struct Pair_Hash {
    size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};
int compute_combinations(int final_score, const std::vector<int>& base_scores, int start_score, std::unordered_map<std::pair<int, int>, int, Pair_Hash>& final_score_cache) {
     if (final_score == 0)
        return 1;

   if (start_score == (int)base_scores.size())
        return 0;

   auto iter = final_score_cache.find({start_score, final_score});
   if (iter != final_score_cache.end())
       return iter->second;

    int count = 0;
    int i = 0;
    while (i * base_scores[start_score] <= final_score) {
        count += compute_combinations(final_score - i*base_scores[start_score], base_scores, start_score + 1, final_score_cache);
        i++;
    }
    final_score_cache[{start_score, final_score}] = count;
    return count;
}

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
   std::unordered_map<std::pair<int, int>, int, Pair_Hash> final_score_cache;
    return compute_combinations(final_score, individual_play_scores, 0, final_score_cache);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
