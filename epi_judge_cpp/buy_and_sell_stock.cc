#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
    int buy_index = 0;
    double profit = 0.0;

    for (int i = 1; i < (int)prices.size(); i++) {
        if (prices[i] - prices[buy_index] > profit) {
            profit = prices[i] - prices[buy_index];
        }
        else if (prices[i] < prices[buy_index]) {
            buy_index = i;
        }
    }
    return profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
