#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

#include <unordered_map>

class LruCache {
 public:
  LruCache(size_t capacity) : capacity((int)capacity) {}
  int Lookup(int isbn) {
      auto iter = isbn_to_price.find(isbn);
      if (iter == isbn_to_price.end())
          return -1;

      if (iter->second != prices.begin())
        prices.splice(prices.begin(), prices, iter->second);

      return (*prices.begin()).price;
  }
  void Insert(int isbn, int price) {
      auto iter = isbn_to_price.find(isbn);
      if (iter != isbn_to_price.end()) {
          if (iter->second != prices.begin())
              prices.splice(prices.begin(), prices, iter->second);
          return;
      }
      if (prices.size() == capacity) {
          isbn_to_price.erase(prices.back().isbn);
          prices.erase(--prices.end());
      }
      prices.push_front({price, isbn});
      isbn_to_price.insert(std::make_pair(isbn, prices.begin()));
  }
  bool Erase(int isbn) {
      auto iter = isbn_to_price.find(isbn);
      if (iter == isbn_to_price.end())
          return false;

      prices.erase(iter->second);
      isbn_to_price.erase(isbn);
      return true;
  }
    struct List_Item {
        int price;
        int isbn;
    };
  int capacity;
  std::unordered_map<int, std::list<List_Item>::iterator> isbn_to_price;
  std::list<List_Item> prices;
};
struct Op {
  std::string code;
  int arg1;
  int arg2;
};

template <>
struct SerializationTraits<Op> : UserSerTraits<Op, std::string, int, int> {};

void RunTest(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &RunTest,
                         DefaultComparator{}, param_names);
}
