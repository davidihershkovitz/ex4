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
#define ASCII_SIZE 256

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




char board[MAX_SIZE][MAX_SIZE];    // Input board
char solution[MAX_SIZE][MAX_SIZE]; // Output solution board
int colOccupied[MAX_SIZE];         // Tracks if a column is occupied
int areaUsed[ASCII_SIZE];          // Tracks if an area is occupied
int diag1[2 * MAX_SIZE];           // Tracks diagonal from top-left to bottom-right
int diag2[2 * MAX_SIZE];           // Tracks diagonal from top-right to bottom-left
int N;                             // Board dimensions

// Function to initialize the global variables
void initialize() {
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

// Recursive function to place queens
int placeQueen(int row) {
    if (row == N) {
        return 1; // All queens successfully placed
    }

    for (int col = 0; col < N; col++) {
        char area = board[row][col];
        // Check if column and area are free
        if (!colOccupied[col] && !areaUsed[(int)area]) {
            // Check diagonals to ensure queens are not placed adjacent
            int diag1Index = row - col + N - 1;
            int diag2Index = row + col;

            // Allow placement if the diagonal is free or if the previous queen is at least 2 squares away
            if ((diag1[diag1Index] == -1) || (row - diag1[diag1Index] > 1)) {
                if ((diag2[diag2Index] == -1) || (row - diag2[diag2Index] > 1)) {
                    // Place queen
                    solution[row][col] = 'X';
                    colOccupied[col] = 1;
                    areaUsed[(int)area] = 1;
                    diag1[diag1Index] = row;
                    diag2[diag2Index] = row;

                    // Recursively place the next queen
                    if (placeQueen(row + 1)) {
                        return 1;
                    }

                    // Backtrack: Remove queen
                    solution[row][col] = '*';
                    colOccupied[col] = 0;
                    areaUsed[(int)area] = 0;
                    diag1[diag1Index] = -1;
                    diag2[diag2Index] = -1;
                }
            }
        }
    }

    return 0; // No valid placement for this row
}

// Main task function
void task4QueensBattle() {
    printf("Please enter the board dimensions:\n");
    scanf("%d", &N);

    printf("Please enter a %d*%d puzzle board:\n", N, N);
    for (int i = 0; i < N; i++) {
        scanf("%s", board[i]); // Read each row of the board
    }

    initialize(); // Initialize variables and solution

    if (placeQueen(0)) {
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

