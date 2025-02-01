#include <iostream>
#include <vector>
#include <algorithm>

struct AllResults {
    int counter;
    std::vector<std::vector<std::vector<char>>> allResults;
    bool isCalculated;
    int n;
};

bool isQueenSafe(const std::vector<std::vector<char>>& board, int row, int col, int maxCol) {

    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
    }


    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }


    for (int j = col; j >= 0; j--) {
        if (board[row][j] == 'Q') return false;
    }


    for (int i = row, j = col; j >= 0 && i < maxCol; i++, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    return true;
}


void findQueenPlaces(
    std::vector<std::vector<char>>& board,
    int col,
    int maxCol,
    AllResults& results
) {

    if (col == maxCol) {
        if (std::find(results.allResults.begin(), results.allResults.end(), board) == results.allResults.end()) {
            results.counter++;
            results.allResults.push_back(board);
        }
        return;
    }


    for (int row = 0; row < maxCol; row++) {
        if (isQueenSafe(board, row, col, maxCol)) {
            board[row][col] = 'Q';
            findQueenPlaces(board, col + 1, maxCol, results);
            board[row][col] = '.';
        }
    }
}

void showSolutionResults(std::vector<std::vector<std::vector<char>>> res, int solCounter, int num) {
    for (int i = 0; i < solCounter;i++) {
        printf("solution %d\n\n", i);
        for (int j = 0;j < num;j++) {
            for (int w = 0; w < num;w++) {
                std::cout << res[i][j][w] << " ";
            }
            printf("\n");
        }
    }
    printf("solution founded : %d",solCounter);
}


void showMenu() {
    int options[] = { 1, 2, 3, 4 };
    std::cout << "\t\t\t ***** N-Queens Solver ***** \t\t\t\n";
    std::cout << "\t\t\t\t**** Menu ****\n";
    AllResults results{ 0, {}, false };

    while (true) {
        std::cout << "[1] - Find solution\n";
        std::cout << "[2] - Display Solution\n";
        std::cout << "[3] - Count Solutions for N between 2 and 8\n";
        std::cout << "[4] - Exit\n";
        std::cout << "Choose an option: ";

        int userOption;
        std::cin >> userOption;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printf("please write a valid intiger!\n");
            continue;
        }

        if (std::find(std::begin(options), std::end(options), userOption) == std::end(options)) {
            std::cout << "Invalid option! Please choose a valid option.\n\n";
            continue;
        }

        switch (userOption) {
        case 1: {

            do {
                std::cout << "Enter the value of N (must be greater than 2): ";
                std::cin >> results.n;
                if (results.n <= 2) {
                    std::cout << "N must be greater than 2. Try again.\n";
                }
            } while (results.n <= 2);

            std::vector<std::vector<char>> board(results.n, std::vector<char>(results.n, '.'));
            if (results.isCalculated) {
                printf("deletiing last calcs...");
                results.allResults = {};
                results.counter = 0;
                std::cout << "Finding solutions...\n";
                findQueenPlaces(board, 0, results.n, results);
                std::cout << "Solutions found: " << results.counter << "\n";
            }
            else {
                results.isCalculated = true;
                findQueenPlaces(board, 0, results.n, results);
                std::cout << "Solutions found: " << results.counter << "\n";

            }
            break;
        }
        case 2: {
            showSolutionResults(results.allResults, results.counter, results.n);
        }
        case 3: {

        }
        case 4: {
            return;
        }

        }


    }
}

int main() {
    showMenu();
    return 0;
}
