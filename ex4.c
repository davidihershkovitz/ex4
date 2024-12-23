/******************
Name: Davidi Hershkovitz
ID: 214165417
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>
#define MAX_ROWS 5
#define SIZE ((MAX_ROWS * (MAX_ROWS + 1)) / 2) // Total cheerleaders in a 5-level pyramid
#define MAX_SIZE 10
#define ASCII_SIZE 128

int paths(int x, int y) {
    if(x == 0 && y == 0) {
        return 1;
    }
    if(x > 0 && y > 0) {
        return paths(x-1,y) + paths(x,y-1);
    }
    if(x == 0 && y > 0) {
        return paths(x,y-1);
    }
    if(x > 0 && y ==0) {
        return paths(x-1,y);
    }
    if(x < 0 || y < 0) {
        return 0;
    }
    return 0;
}
void task1RobotPaths() {
    int x, y;
    printf("Please enter the coordinates of the robot (column, row): \n");
    scanf("%d %d", &x, &y);
    int totalPaths =  paths(x,y);
    printf("The total number of paths the robot can take to reach home is: %d\n", totalPaths);
}


// Recursive function to calculate the total weight supported by a cheerleader
float calculateWeight(int row, int col, const float weights[]) {
    int index = (row * (row + 1)) / 2 + col;

    // Base case: Top cheerleader
    if (row == 0) {
        return weights[index];
    }

    // Calculate weight from left and right parents
    float left = (col > 0) ? 0.5 * calculateWeight(row - 1, col - 1, weights) : 0;
    float right = (col < row) ? 0.5 * calculateWeight(row - 1, col, weights) : 0;

    // Return the total weight
    return left + right + weights[index];
}

// Main function to handle the human pyramid calculation
void task2HumanPyramid() {
    float weights[SIZE]; // Array for cheerleader weights

    // Input weights
    printf("Please enter the weights of the cheerleaders: \n");
    for (int i = 0; i < SIZE; i++) {
        if (scanf("%f", &weights[i]) != 1 || weights[i] < 0) {
            printf("Negative weights are not supported.\n");
            return;
        }
    }

    // Output weights in pyramid format
    printf("The total weight on each cheerleader is: \n");
    for (int row = 0, index = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col <= row; col++, index++) {
            printf("%.2f ", calculateWeight(row, col, weights));
        }
        printf("\n");
    }
}

// Recursive function to validate parentheses
int task3ParenthesisValidator(int first, int second, int third, int forth, int invalid, char lastChar) {
    char c;
    if (scanf("%c", &c) != 1 || c == '\n') {
        // Base case: End of input
        return (first == 0 && second == 0 && third == 0 && forth == 0 && invalid == 0) ? 1 : 0;
    }

    // Handle opening parentheses
    if (c == '<') return task3ParenthesisValidator(first + 1, second, third, forth, invalid, '<');
    if (c == '(') return task3ParenthesisValidator(first, second + 1, third, forth, invalid, '(');
    if (c == '[') return task3ParenthesisValidator(first, second, third + 1, forth, invalid, '[');
    if (c == '{') return task3ParenthesisValidator(first, second, third, forth + 1, invalid, '{');

    // Handle closing parentheses
    if (c == '>') {
        if (lastChar == '<' || lastChar == 0) {
            if (first > 0) return task3ParenthesisValidator(first - 1, second, third, forth, invalid, 0);
        }
        return task3ParenthesisValidator(first, second, third, forth, invalid + 1, lastChar);
    }
    if (c == ')') {
        if (lastChar == '(' || lastChar == 0) {
            if (second > 0) return task3ParenthesisValidator(first, second - 1, third, forth, invalid, 0);
        }
        return task3ParenthesisValidator(first, second, third, forth, invalid + 1, lastChar);
    }
    if (c == ']') {
        if (lastChar == '[' || lastChar == 0) {
            if (third > 0) return task3ParenthesisValidator(first, second, third - 1, forth, invalid, 0);
        }
        return task3ParenthesisValidator(first, second, third, forth, invalid + 1, lastChar);
    }
    if (c == '}') {
        if (lastChar == '{' || lastChar == 0) {
            if (forth > 0) return task3ParenthesisValidator(first, second, third, forth - 1, invalid, 0);
        }
        return task3ParenthesisValidator(first, second, third, forth, invalid + 1, lastChar);
    }

    // Ignore non-parenthesis characters
    return task3ParenthesisValidator(first, second, third, forth, invalid, lastChar);
}



// Function to initialize all necessary tracking arrays
void initialize(int colOccupied[], int areaUsed[], int diag1[], int diag2[], char solution[MAX_SIZE][MAX_SIZE], int N) {
    for (int i = 0; i < N; i++) {
        colOccupied[i] = 0; // Mark columns as free
        for (int j = 0; j < N; j++) {
            solution[i][j] = '*'; // Set all cells to '*'
        }
    }
    for (int i = 0; i < ASCII_SIZE; i++) {
        areaUsed[i] = 0; // Mark areas as free
    }
    for (int i = 0; i < 2 * MAX_SIZE; i++) {
        diag1[i] = -1; // Initialize diagonals
        diag2[i] = -1;
    }
}

// Function to check if placing a queen is safe
int checkSafe(int row, int col, char area, int colOccupied[], int areaUsed[], int diag1[], int diag2[], int N) {
    int diag1Index = row - col + N - 1;
    int diag2Index = row + col;

    // Check if the column, area, or diagonals are already occupied
    if (colOccupied[col] || areaUsed[(int)area] ||
        (diag1[diag1Index] != -1 && row - diag1[diag1Index] <= 1) ||
        (diag2[diag2Index] != -1 && row - diag2[diag2Index] <= 1)) {
        return 0;
    }
    return 1;
}

// Recursive function to place queens in the solution board
int placeQueen(int row, int col, char board[MAX_SIZE][MAX_SIZE], char solution[MAX_SIZE][MAX_SIZE],
               int colOccupied[MAX_SIZE], int areaUsed[ASCII_SIZE], int diag1[2 * MAX_SIZE],
               int diag2[2 * MAX_SIZE], int N) {
    // If we have placed queens in all rows, return true
    if (row == N) {
        return 1;
    }

    // Try to place a queen in the current row (recursively try each column)
    if (col == N) {
        return 0; // All columns have been tried, backtrack to the previous row
    }

    char area = board[row][col];
    if (checkSafe(row, col, area, colOccupied, areaUsed, diag1, diag2, N)) {
        // Place the queen on the board
        solution[row][col] = 'X';
        colOccupied[col] = 1;
        areaUsed[(int)area] = 1;
        diag1[row - col + N - 1] = row;
        diag2[row + col] = row;

        // Recursively place the next queen in the next column
        if (placeQueen(row + 1, 0, board, solution, colOccupied, areaUsed, diag1, diag2, N)) {
            return 1; // Queen placed successfully
        }

        // Backtrack: remove the queen and try the next column
        solution[row][col] = '*';
        colOccupied[col] = 0;
        areaUsed[(int)area] = 0;
        diag1[row - col + N - 1] = -1;
        diag2[row + col] = -1;
    }

    // Recursively try the next column in the current row
    return placeQueen(row, col + 1, board, solution, colOccupied, areaUsed, diag1, diag2, N);
}

// Main task function
void task4QueensBattle() {
    int N;
    printf("Please enter the board dimensions:\n");
    scanf("%d", &N);

    printf("Please enter a %d*%d puzzle board:\n", N, N);
    char board[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < N; i++) {
        scanf("%s", board[i]); // Read each row of the board
    }

    char solution[MAX_SIZE][MAX_SIZE];
    int colOccupied[MAX_SIZE], areaUsed[ASCII_SIZE], diag1[2 * MAX_SIZE], diag2[2 * MAX_SIZE];
    initialize(colOccupied, areaUsed, diag1, diag2, solution, N); // Initialize variables and solution

    if (placeQueen(0, 0, board, solution, colOccupied, areaUsed, diag1, diag2, N)) {
        printf("Solution:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%c ", solution[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("This puzzle cannot be solved.\n");
    }
}


















// void task5CrosswordGenerator();

int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;
            case 1:
                task1RobotPaths();
                break;
            case 2:
                 task2HumanPyramid();
                break;
            case 3: {
                    printf("Please enter a term for validation:\n");
                    scanf(" ");
                    int isClosed=task3ParenthesisValidator(0,0,0,0,0, 0);
                    if (isClosed==1) {
                        printf("The parentheses are balanced correctly.\n");
                    } else {
                        printf("The parentheses are not balanced correctly.\n");
                    }
                    break;
            }
            case 4:
                 task4QueensBattle();
               break;
            // case 5:
            //     task5CrosswordGenerator();
            //     break;
            default:
                printf("\nPlease choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}

