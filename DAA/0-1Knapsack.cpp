#include <iostream>
using namespace std;

// Recursive function to solve the Knapsack problem with memoization
// `w[]` - array of weights
// `v[]` - array of values
// `W` - remaining weight capacity of knapsack
// `dp` - memoization table
// `index` - current index of item being considered
int knapsacRev(int w[], int v[], int W, int** dp, int index) {
    // Base case: If no items are left, or knapsack capacity is exhausted, return 0
    if (index < 0) return 0;

    // If the value for the current state is already computed, return it from the dp table.
    if (dp[index][W] != -1) {
        return dp[index][W];
    }

    // If the weight of the current item is more than the remaining capacity `W`,
    // skip this item and proceed to the next item
    if (w[index] > W) {
        dp[index][W] = knapsacRev(w, v, W, dp, index - 1);
        return dp[index][W];
    } else {
        // Consider two choices:
        // 1. Include the current item and add its value, reduce remaining capacity by its weight
        // 2. Exclude the current item and move to the next item
        // Take the maximum of both choices
        dp[index][W] = max(v[index] + knapsacRev(w, v, W - w[index], dp, index - 1),
                           knapsacRev(w, v, W, dp, index - 1));
        return dp[index][W];
    }
}

// Initializes the dp table and calls the recursive knapsack function
int knapSack(int w[], int v[], int W, int n) {
    // Create a 2D dp array with size `n x (W + 1)`
    int** dp;
    dp = new int*[n];
    for (int i = 0; i < n; i++) {
        dp[i] = new int[W + 1];
    }

    // Initialize the dp table with -1 to indicate uncomputed states
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < W + 1; j++) {
            dp[i][j] = -1;
        }
    }

    // Call the recursive function starting with the last item and the full capacity `W`
    return knapsacRev(w, v, W, dp, n - 1);
}

int main() {
    // Example weights and values
    int w[] = {10, 20, 30};  // weights of items
    int v[] = {60, 100, 120}; // values of items

    int W = 50; // Knapsack capacity
    int n = 3;  // Number of items

    // Output the maximum profit that can be obtained
    cout << "Max Profit: " << knapSack(w, v, W, n);

    return 0;
}
