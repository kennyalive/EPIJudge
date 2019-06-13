#include <string>
#include <unordered_set>
#include "test_framework/generic_test.h"
using std::string;
using std::unordered_set;

#include <unordered_map>
using std::unordered_map;
#include <queue>
using std::queue;
using std::pair;

// Uses BFS to find the least steps of transformation.
int TransformString(unordered_set<string> D, const string& s, const string& t) {
    if (s == t)
        return 0;

    unordered_map<string, unordered_set<string>> graph;
    for (auto& word : D) {
        for (auto& word2 : D) {
            if (word != word2 && word.size() == word2.size()) {
                int diffs = 0;
                for (int i = 0; i < (int)word.size(); i++)
                    if (word[i] != word2[i])
                        diffs++;
                if (diffs == 1) {
                    graph[word].insert(word2);
                    graph[word2].insert(word);
                }
            }
        }
    }

    unordered_set<string> visited;
    queue<pair<string, int>> bfs_queue;
    bfs_queue.push({s, 0});
    visited.insert(s);

    while (!bfs_queue.empty()) {
        auto entry = bfs_queue.front();
        bfs_queue.pop();
        
        const auto& words = graph[entry.first]; 
        for (const auto& word : words) {
            if (visited.find(word) != visited.end())
                continue;
            if (word == t)
                return entry.second + 1;
            visited.insert(word);
            bfs_queue.push({word, entry.second + 1});
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"D", "s", "t"};
  return GenericTestMain(args, "string_transformability.cc",
                         "string_transformability.tsv", &TransformString,
                         DefaultComparator{}, param_names);
}
