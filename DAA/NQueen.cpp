#include <iostream>
#include <vector>
using namespace std;

void printSolution(const vector<vector<int>>& board) {
    int n = board.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j]) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;  // Add a blank line between solutions
}

bool isSafe(const vector<vector<int>>& board, int row, int col) {
    int n = board.size();
    int i, j;

    // Check row on the left side
    for (j = 0; j < col; j++) {
        if (board[row][j] == 1) return false;
    }

    // Check upper left diagonal
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) return false;
    }

    // Check lower left diagonal
    for (i = row, j = col; i < n && j >= 0; i++, j--) {
        if (board[i][j] == 1) return false;
    }

    // If no conflicts, it's safe
    return true;
}

void solveNQUtil(vector<vector<int>>& board, int col, vector<vector<vector<int>>>& solutions) {
    int n = board.size();

    // Base case: If all queens are placed, add the solution to the list
    if (col >= n) {
        solutions.push_back(board);
        return;
    }

    // Consider this column and try placing this queen in all rows one by one
    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col)) {
            // Place this queen
            board[i][col] = 1;

            // Recur to place the rest
            solveNQUtil(board, col + 1, solutions);

            // If placing queen in board[i][col] doesn't lead to a solution then
            // remove the queen (backtrack)
            board[i][col] = 0;
        }
    }
}

bool solveNQ(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<vector<vector<int>>> solutions;

    solveNQUtil(board, 0, solutions);

    if (solutions.empty()) {
        cout << "No solution exists" << endl;
        return false;
    }

    for (const auto& sol : solutions) {
        printSolution(sol);
    }
    return true;
}

int main() {
    int n;
    cout << "Enter size of chess board: ";
    cin >> n;

    solveNQ(n);

    return 0;
}
