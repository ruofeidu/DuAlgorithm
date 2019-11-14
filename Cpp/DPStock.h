#pragma once
#include "common.h"

class StockProblems {
 public:
  // 121. Best Time to Buy and Sell Stock
  // Condition: Buy and sell once
  // Say you have an array for which the ith element is the price of a given
  // stock on day i. If you were only permitted to complete at most one
  // transaction(i.e., buy one and sell one share of the stock), design an
  // algorithm to find the maximum profit. Note that you cannot sell a stock
  // before you buy one.
  // Solution: scan the stocks, find the min_price up to now, update by cur -
  // min_price
  // Time: O(n)
  int maxProfit_once(vector<int>& prices) {
    int n = (int)prices.size();
    if (n == 0) return 0;
    int ans = 0;
    int min_price = prices[0];
    for (int i = 0; i < n; ++i) {
      min_price = min(min_price, prices[i]);
      ans = max(ans, prices[i] - min_price);
    }
    return ans;
  }

  // 122. Best Time to Buy and Sell Stock II
  // Condition: Buy and sell multiple times, can in the same day
  // Solution: as long as there is profit for consective two days, buy in
  // Time: O(n)
  // Say you have an array for which the ith element is the price of a given
  // stock on day i. Design an algorithm to find the maximum profit.You may
  // complete as many transactions as you like (i.e., buy one and sell one share
  // of the stock multiple times).
  int maxProfit_infinite_times(vector<int>& prices) {
    if (prices.size() < 2) return 0;
    int sum = 0;
    for (size_t i = 1; i < prices.size(); ++i) {
      int diff = prices[i] - prices[i - 1];
      if (diff > 0) sum += diff;
    }
    return sum;
  }

  // 123. Best Time to Buy and Sell Stock III
  // Condition: Buy and sell m times (m = 2)
  // Say you have an array for which the ith element is the price of a given
  // stock on day i. Design an algorithm to find the maximum profit.You may
  // complete at most two transactions. Note: You may not engage in multiple
  // transactions at the same time(i.e., you must sell the stock before you buy
  // again).
  // l[i][j] local indicates the i day, j transaction, all sold out, max profit
  // g[i][j] global indicates the maximum profit
  // l[i][j] = max(g[i-1][j-1] + max(diff, 0), local[i-1][j] + diff)
  int maxProfit_m_times(vector<int>& prices) {
    const int n = (int)prices.size();
    if (n == 0) return 0;
    const int m = 2;
    Grid g(n, Vector(m + 1)), l(n, vector<int>(m + 1));

    for (int i = 1; i < n; ++i) {
      int diff = prices[i] - prices[i - 1];
      for (int j = 1; j <= m; ++j) {
        l[i][j] = max(g[i - 1][j - 1] + max(diff, 0), l[i - 1][j] + diff);
        g[i][j] = max(l[i][j], g[i - 1][j]);
      }
    }
    return g[n - 1][2];
  }

  // Time: O(NM)
  // Space: O(M)
  int maxProfit_m_times_o1space(vector<int>& prices) {
    if (prices.empty()) return 0;
    const int m = 2;
    int g[m + 1] = {0};
    int l[m + 1] = {0};
    const int n = (int)prices.size();
    for (int i = 0; i < n - 1; ++i) {
      int diff = prices[i + 1] - prices[i];
      for (int j = 2; j >= 1; --j) {
        l[j] = max(g[j - 1] + max(diff, 0), l[j] + diff);
        g[j] = max(l[j], g[j]);
      }
    }
    return g[2];
  }

  // 188. Best Time to Buy and Sell Stock IV
  // Condition: buy and sell m times
  // Time: O(NM)
  // Space: O(M)
  int maxProfit(int k, vector<int>& prices) {
    if (prices.empty()) return 0;
    int n = (int)prices.size();
    if (k >= n) return maxProfit_infinite_times(prices);
    vector<int> g(k + 1), l(k + 1);
    for (int i = 0; i < n - 1; ++i) {
      int diff = prices[i + 1] - prices[i];
      for (int j = k; j >= 1; --j) {
        l[j] = max(g[j - 1] + max(diff, 0), l[j] + diff);
        g[j] = max(g[j], l[j]);
      }
    }
    return g[k];
  }

  /**
   * 309. Best Time to Buy and Sell Stock with 1 day Cooldown
   * prices = [1, 2, 3, 0, 2]
   * maxProfit = 3
   * transactions = [buy, sell, cooldown, buy, sell]
   **/
  // Time: O(N)
  int maxProfit_1d_cd(vector<int>& prices) {
    /**
    * buy[i]  = max(rest[i-1] - price, buy[i-1])
    * sell[i] = max(buy[i-1] + price, sell[i-1])
    * rest[i] = max(sell[i-1], buy[i-1], rest[i-1])
    */
    // rest[i] = sell[i-1]
    // buy[i]  = max(sell[i-2] - price, buy[i-1])
    // sell[i] = max(buy[i-1] + price, sell[i-1])
    int buy = INT_MIN, pre_buy = 0, sell = 0, pre_sell = 0;
    for (int price : prices) {
      pre_buy = buy;
      buy = max(pre_sell - price, pre_buy);
      pre_sell = sell;
      sell = max(pre_buy + price, pre_sell);
    }
    return sell;
  }
};
