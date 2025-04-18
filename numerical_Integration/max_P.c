#include <limits.h>
#include <stdlib.h>

int maxProfit(int* prices, int pricesSize){
    if (pricesSize == 0) {
        return 0;
    }

    int min_price = INT_MAX;
    int max_profit = 0;

    for(int i = 0; i < pricesSize; ++i) {
        if(prices[i] < min_price){
            min_price = prices[i];
        }

        int potential_profit = prices[i] - min_price;

        if(potential_profit > max_profit) {
            max_profit = potential_profit;
        }
    }

    return max_profit;
}

