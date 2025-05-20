/******************
Name: Davidi Hershkovitz
ID: 214165417
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>
#define MAX_ROWS 5 // The max rows that can be in the pyramid
#define SIZE ((MAX_ROWS * (MAX_ROWS + 1)) / 2) // Total cheerleaders in a 5-level pyramid
#define MAX_SIZE 10 // Max size of the board
#define ASCII_SIZE 128 // receiving all kinds of chars
#define MAX_GRID 30 // Max size of grid
#define MAX_WORDS 100 // Max words in the dictionary
#define MAX_LENGTH 15 // Max length of word

// struct for the crosswords
typedef struct Slot
{
    int row;
    int col;
    int length;
    char direction; // H for horizontal, V for vertical
} Slot;
// All the functions that I used during the exe
int paths(int x, int y);
void task1RobotPaths();
float calculateWeight(int row, int col, const float weights[]);
void task2HumanPyramid();
int task3ParenthesisValidator(int first, int second, int third, int forth, int invalid, char lastChar);
void initialize(int colOccupied[], int areaUsed[], char solution[MAX_SIZE][MAX_SIZE], int N);
int is_neighbor_has_queen(int row, int col, int dr, int dc, char solution[MAX_SIZE][MAX_SIZE], int N);
int check_neighbors(int row, int col, char solution[MAX_SIZE][MAX_SIZE], int N, int d);
int checkSafe(int row, int col, char area, int colOccupied[], int areaUsed[], char solution[MAX_SIZE][MAX_SIZE], int N);
int placeQueen(int row, int col, char board[MAX_SIZE][MAX_SIZE], char solution[MAX_SIZE][MAX_SIZE],
               int colOccupied[MAX_SIZE], int areaUsed[ASCII_SIZE], int N);
void task4QueensBattle();


// Recursive func that will check how many ways there are to get to the destination
int paths(int x, int y)
{
    if (x == 0 && y == 0) // Base case - the robot is already at the des
    {
        return 1;
    }
    if (x > 0 && y > 0)
    {
        return paths(x - 1, y) + paths(x, y - 1); // Sum-up the ways from a curtain point
    }
    if (x == 0 && y > 0)
    {
        return paths(x, y - 1);
    }
    if (x > 0 && y == 0)
    {
        return paths(x - 1, y);
    }
    if (x < 0 || y < 0)
    {
        return 0;
    }
    return 0;
}

// Func to handle the recursive func
void task1RobotPaths()
{
    int x, y;
    printf("Please enter the coordinates of the robot (column, row): \n");
    scanf(" %d  %d", &x, &y);
    int totalPaths = paths(x, y);
    printf("The total number of paths the robot can take to reach home is: %d\n", totalPaths);
}


// Recursive function to calculate the total weight supported by a cheerleader
float calculateWeight(int row, int col, const float weights[])
{
    int index = (row * (row + 1)) / 2 + col;

    // Base case - Top cheerleader
    if (row == 0)
    {
        return weights[index];
    }

    // Calculate weight of the cheerleaders
    float left = (col > 0) ? 0.5 * calculateWeight(row - 1, col - 1, weights) : 0;
    float right = (col < row) ? 0.5 * calculateWeight(row - 1, col, weights) : 0;

    // Return the total weight
    return left + right + weights[index];
}

// Main function to handle the human pyramid calculation
void task2HumanPyramid()
{
    float weights[SIZE]; // Array for cheerleader weights

    printf("Please enter the weights of the cheerleaders: \n");
    for (int i = 0; i < SIZE; i++)
    {
        if (scanf("%f", &weights[i]) != 1 || weights[i] < 0)
        {
            printf("Negative weights are not supported.\n");
            return;
        }
    }

    printf("The total weight on each cheerleader is: \n");
    for (int row = 0, index = 0; row < MAX_ROWS; row++)
    {
        for (int col = 0; col <= row; col++, index++)
        {
            printf("%.2f ", calculateWeight(row, col, weights));
        }
        printf("\n");
    }
}

// Recursive function to validate parentheses
int task3ParenthesisValidator(int first, int second, int third, int forth, int invalid, char lastChar)
{
    char c;
    if (scanf("%c", &c) != 1 || c == '\n')
    {
        // Base case - End of input
        return (first == 0 && second == 0 && third == 0 && forth == 0 && invalid == 0) ? 1 : 0;
    }

    // Handle opening parentheses
    if (c == '<') return task3ParenthesisValidator(first + 1, second, third, forth, invalid, '<');
    if (c == '(') return task3ParenthesisValidator(first, second + 1, third, forth, invalid, '(');
    if (c == '[') return task3ParenthesisValidator(first, second, third + 1, forth, invalid, '[');
    if (c == '{') return task3ParenthesisValidator(first, second, third, forth + 1, invalid, '{');

    // Handle closing parentheses
    if (c == '>')
    {
        if (lastChar == '<' || lastChar == 0)
        {
            if (first > 0) return task3ParenthesisValidator(first - 1, second, third, forth, invalid, 0);
        }
        return task3ParenthesisValidator(first, second, third, forth, invalid + 1, lastChar);
    }
    if (c == ')')
    {
        if (lastChar == '(' || lastChar == 0)
        {
            if (second > 0) return task3ParenthesisValidator(first, second - 1, third, forth, invalid, 0);
        }
        return task3ParenthesisValidator(first, second, third, forth, invalid + 1, lastChar);
    }
    if (c == ']')
    {
        if (lastChar == '[' || lastChar == 0)
        {
            if (third > 0) return task3ParenthesisValidator(first, second, third - 1, forth, invalid, 0);
        }
        return task3ParenthesisValidator(first, second, third, forth, invalid + 1, lastChar);
    }
    if (c == '}')
    {
        if (lastChar == '{' || lastChar == 0)
        {
            if (forth > 0) return task3ParenthesisValidator(first, second, third, forth - 1, invalid, 0);
        }
        return task3ParenthesisValidator(first, second, third, forth, invalid + 1, lastChar);
    }

    // Ignore non-parenthesis characters
    return task3ParenthesisValidator(first, second, third, forth, invalid, lastChar);
}


// Function to initialize all necessary tracking arrays
void initialize(int colOccupied[], int areaUsed[], char solution[MAX_SIZE][MAX_SIZE], int N)
{
    for (int i = 0; i < N; i++)
    {
        colOccupied[i] = 0;
        for (int j = 0; j < N; j++)
            solution[i][j] = '*';
    }
    for (int i = 0; i < ASCII_SIZE; i++)
        areaUsed[i] = 0;
}

//help to check if the neighbor is a queen
int is_neighbor_has_queen(int row, int col, int dr, int dc, char solution[MAX_SIZE][MAX_SIZE], int N) {
    int nr = row + dr;
    int nc = col + dc;
    if (nr >= 0 && nr < N && nc >= 0 && nc < N)
        return solution[nr][nc] == 'X';
    return 0;
}
//check all adjacent neighbors
int check_neighbors(int row, int col, char solution[MAX_SIZE][MAX_SIZE], int N, int d) {
    int dr[8] = {-1,-1,-1,0,0,1,1,1};
    int dc[8] = {-1,0,1,-1,1,-1,0,1};
    if (d == 8)
        return 1;
    if (is_neighbor_has_queen(row, col, dr[d], dc[d], solution, N))
        return 0;
    return check_neighbors(row, col, solution, N, d+1);
}
//main func to check if the place is safe
int checkSafe(int row, int col, char area, int colOccupied[], int areaUsed[], char solution[MAX_SIZE][MAX_SIZE], int N)
{
    if (colOccupied[col] || areaUsed[(int)area])
        return 0;
    return check_neighbors(row, col, solution, N, 0);
}
//func that will place the queen
int placeQueen(int row, int col, char board[MAX_SIZE][MAX_SIZE], char solution[MAX_SIZE][MAX_SIZE],
               int colOccupied[MAX_SIZE], int areaUsed[ASCII_SIZE], int N)
{
    if (row == N)
        return 1;

    if (col == N)
        return 0;

    char area = board[row][col];
    if (checkSafe(row, col, area, colOccupied, areaUsed, solution, N))
    {
        solution[row][col] = 'X';
        colOccupied[col] = 1;
        areaUsed[(int)area] = 1;

        if (placeQueen(row + 1, 0, board, solution, colOccupied, areaUsed, N))
            return 1;

        solution[row][col] = '*';
        colOccupied[col] = 0;
        areaUsed[(int)area] = 0;
    }
    return placeQueen(row, col + 1, board, solution, colOccupied, areaUsed, N);
}
//func that will initiate all the recursion
void task4QueensBattle()
{
    int N;
    printf("Please enter the board dimensions:\n");
    scanf("%d", &N);

    char solution[MAX_SIZE][MAX_SIZE];
    int colOccupied[MAX_SIZE], areaUsed[ASCII_SIZE];
    initialize(colOccupied, areaUsed, solution, N);

    printf("Please enter a %d*%d puzzle board:\n", N, N);
    char board[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < N; i++)
    {
        scanf("%s", board[i]);
    }

    if (placeQueen(0, 0, board, solution, colOccupied, areaUsed, N))
    {
        printf("Solution:\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                printf("%c ", solution[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("This puzzle cannot be solved.\n");
    }
}

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
            "5. Exit\n");
// Each func is connected to the main
        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 5:
                printf("Goodbye!\n");
                break;
            case 1:
                task1RobotPaths();
                break;
            case 2:
                task2HumanPyramid();
                break;
            case 3:
                {
                    printf("Please enter a term for validation:\n"); // Getting input from the user
                    scanf(" ");
                    int isClosed = task3ParenthesisValidator(0, 0, 0, 0, 0, 0);
                    if (isClosed == 1) // Results of the validator
                    {
                        printf("The parentheses are balanced correctly.\n");
                    }
                    else
                    {
                        printf("The parentheses are not balanced correctly.\n");
                    }
                    break;
                }
            case 4:
                task4QueensBattle();
                break;
            default:
                printf("\nPlease choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }
    }
    while (task != 5);
}
