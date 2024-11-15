#include <iostream>
#include <climits>
#include <cstring>
using namespace std;

// Global constants and variables
const int N = 4;              // Number of cities
int final_path[N+1];          // Stores the minimum cost path
bool visited[N];              // Keeps track of visited cities
int final_res = INT_MAX;      // Stores the minimum cost of the tour

// Utility function to copy the current path to the final path
void copyToFinal(int curr_path[]) {
    for (int i = 0; i < N; i++) {
        final_path[i] = curr_path[i];
    }
    final_path[N] = curr_path[0];  // Complete the path by returning to the starting city
}

// Function to find the minimum edge cost for city `i`
int firstMin(int adj[N][N], int i) {
    int min = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (adj[i][j] < min && i != j) {  // Ignore self-loop edges
            min = adj[i][j];
        }
    }
    return min;
}

// Function to find the second minimum edge cost for city `i`
int secondMin(int adj[N][N], int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (i == j) continue;  // Ignore self-loop edges

        // Update first and second minimum costs
        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        } else if (adj[i][j] < second && adj[i][j] != first) {
            second = adj[i][j];
        }
    }
    return second;
}

// Recursive function that solves TSP using Branch and Bound
void TSPRec(int adj[N][N], int curr_bound, int curr_weight, int level, int curr_path[]) {
    // Base case: All cities are visited, complete the cycle by returning to start
    if (level == N) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {  // Check if there is an edge back to the starting city
            int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];

            // Update minimum result if the current result is better
            if (final_res > curr_res) {
                final_res = curr_res;
                copyToFinal(curr_path);
            }
        }
        return;
    }

    // Recursive case: Explore all cities as next steps in the path
    for (int i = 0; i < N; i++) {
        if (adj[curr_path[level - 1]][i] != 0 && !visited[i]) {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level - 1]][i];  // Add edge weight to current weight

            // Update the lower bound
            if (level == 1) {
                curr_bound -= (firstMin(adj, curr_path[level - 1]) + firstMin(adj, i)) / 2;
            } else {
                curr_bound -= (secondMin(adj, curr_path[level - 1]) + firstMin(adj, i)) / 2;
            }

            // If current bound + weight is promising, proceed to the next city
            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;

                // Recursively call for the next level
                TSPRec(adj, curr_bound, curr_weight, level + 1, curr_path);
            }

            // Backtrack: Undo the changes to weight and bound
            curr_weight -= adj[curr_path[level - 1]][i];
            curr_bound = temp; //reset curr bouund

            // Mark the current city as unvisited for the next iteration
            visited[i] = false;
        }
    }
}

// Main function to set up and start the TSP recursive process
void TSP(int adj[N][N]) {
    int curr_bound = 0;             // Initial lower bound of the root node
    int curr_path[N+1];             // To store the current path
    memset(curr_path, -1, sizeof(curr_path));
    memset(visited, false, sizeof(visited));

    visited[0] = true;              // Start the path from the first city
    curr_path[0] = 0;

    // Compute initial bound by summing first and second minimum costs for each city
    for (int i = 0; i < N; i++) {
        curr_bound += (firstMin(adj, i) + secondMin(adj, i)) / 2;
    }

    // Adjust curr_bound if it's odd (to ensure it's an integer)
    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    // Start recursive TSP search from the root city
    TSPRec(adj, curr_bound, 0, 1, curr_path);
}

int main() {
    // Adjacency matrix representing distances between cities
    int adj[N][N] = { {0, 10, 15, 20},
                      {10, 0, 35, 25},
                      {15, 35, 0, 30},
                      {20, 25, 30, 0} };

    // Call TSP function to calculate the minimum path
    TSP(adj);

    // Output the minimum cost and the optimal path
    cout << "Minimum cost : " << final_res << endl;
    cout << "Path Taken : ";
    for (int i = 0; i <= N; i++) {
        cout << final_path[i] << " ";
    }

    return 0;
}
