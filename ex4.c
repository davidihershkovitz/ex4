/******************
Name: Davidi Hershkovitz
ID: 214165417
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>
#define SIZE 15 //The number of cheerleaders that we have in the pyramid for the arr

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


// func that will round-up values
double roundToTwoDecimal(double value) {
    return (int)(value * 100 + 0.5) / 100.0;
}

// recursive func that will calculate the weights
double calculateWeight(int row, int col, const double weights[]) {
    int index = (row * (row + 1)) / 2 + col;

    // base case; if the index belongs to the cheerleader at the top of the pyramid
    if (row == 0) {
        return weights[index];
    }

    // calculate the weight
    double leftParent = (col > 0) ? 0.5 * calculateWeight(row - 1, col - 1, weights) : 0;
    double rightParent = (col < row) ? 0.5 * calculateWeight(row - 1, col, weights) : 0;

    // return the total weight
    return weights[index] + leftParent + rightParent;
}

// func that will get the input and handle the task
void task2HumanPyramid() {
    double weights[SIZE]; // arr for the 15 cheerleader

    // getting the values from the user
    printf("Please enter the weights of the cheerleaders: \n");
    for (int i = 0; i < SIZE; i++) {
        scanf("%lf", &weights[i]);
        if (weights[i] < 0) { // check if any value is neg
            printf("Negative weights are not supported.\n");
            return; // return to the menu
        }
    }

    // calculate the weights with the recursive func
    printf("The total weight on each cheerleader is: \n");
    for (int row = 0, index = 0; row < 5; row++) {
        for (int col = 0; col <= row; col++, index++) {
            double totalWeight = calculateWeight(row, col, weights);
            printf("%.2f ", roundToTwoDecimal(totalWeight)); // round-up values
        }
        printf("\n");
    }
}



// Recursive function to validate parentheses
int task3ParenthesisValidator(int open1, int open2, int open3, int open4, int error, int last) {
    char c;
    if (scanf("%c", &c) != 1 || c == '\n') {
        // Base case: End of input
        return (open1 == 0 && open2 == 0 && open3 == 0 && open4 == 0 && error == 0) ? 1 : 0;
    }

    // Handle opening parentheses
    if (c == '<') return task3ParenthesisValidator(open1 + 1, open2, open3, open4, error, last);
    if (c == '(') return task3ParenthesisValidator(open1, open2 + 1, open3, open4, error, last);
    if (c == '[') return task3ParenthesisValidator(open1, open2, open3 + 1, open4, error, last);
    if (c == '{') return task3ParenthesisValidator(open1, open2, open3, open4 + 1, error, last);

    // Handle closing parentheses
    if (c == '>') {
        if (open1 > 0) return task3ParenthesisValidator(open1 - 1, open2, open3, open4, error, last);
        return task3ParenthesisValidator(open1, open2, open3, open4, error + 1, last);
    }
    if (c == ')') {
        if (open2 > 0) return task3ParenthesisValidator(open1, open2 - 1, open3, open4, error, last);
        return task3ParenthesisValidator(open1, open2, open3, open4, error + 1, last);
    }
    if (c == ']') {
        if (open3 > 0) return task3ParenthesisValidator(open1, open2, open3 - 1, open4, error, last);
        return task3ParenthesisValidator(open1, open2, open3, open4, error + 1, last);
    }
    if (c == '}') {
        if (open4 > 0) return task3ParenthesisValidator(open1, open2, open3, open4 - 1, error, last);
        return task3ParenthesisValidator(open1, open2, open3, open4, error + 1, last);
    }

    // Ignore non-parenthesis characters
    return task3ParenthesisValidator(open1, open2, open3, open4, error, last);
}






// void task4QueensBattle();
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
                    int isClosed=task3ParenthesisValidator(0,0,0,0,0,0);

                    if (isClosed==1) {
                        printf("The parentheses are balanced correctly.\n");
                    } else {
                        printf("The parentheses are not balanced correctly.\n");
                    }
                    break;
            }
            // case 4:
            //     task4QueensBattle();
            //     break;
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

