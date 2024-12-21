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
    printf("Please enter the weights of the cheerleaders:\n");
    for (int i = 0; i < SIZE; i++) {
        scanf("%lf", &weights[i]);
        if (weights[i] < 0) { // check if any value is neg
            printf("Negative weights are not supported.\n");
            return; // return to the menu
        }
    }

    // calculate the weights with the recursive func
    printf("The total weight on each cheerleader is:\n");
    for (int row = 0, index = 0; row < 5; row++) {
        for (int col = 0; col <= row; col++, index++) {
            double totalWeight = calculateWeight(row, col, weights);
            printf("%.2f ", roundToTwoDecimal(totalWeight)); // round-up values
        }
        printf("\n");
    }
}


int isOpening(char c) {
    return c == '(' || c == '{' || c == '[' || c == '<';
}

int isClosing(char c) {
    return c == ')' || c == '}' || c == ']' || c == '>';
}

int isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']') ||
           (open == '<' && close == '>');
}

// The recursive function
int isBalanced(int stack[], int stackIndex) {
    char c;

    // Read character by character
    if (scanf("%c", &c) != 1 || c == '\n') { // Stops at newline or EOF
        return stackIndex == 0; // If the stack is empty, parentheses are balanced
    }

    if (isOpening(c)) {
        // Push the opening parenthesis onto the stack
        stack[stackIndex] = c;
        return isBalanced(stack, stackIndex + 1);
    }

    if (isClosing(c)) {
        // Check if it matches the last opening parenthesis
        if (stackIndex == 0 || !isMatching(stack[stackIndex - 1], c)) {
            return 0; // Unmatched closing parenthesis
        }
        return isBalanced(stack, stackIndex - 1); // Pop from the stack
    }

    // Ignore non-parenthesis characters
    return isBalanced(stack, stackIndex);
}

void task3ParenthesisValidator() {
    int stack[1000000]; // Buffer for the recursive function
    char c;

    // Clear any leftover characters from the menu selection
    while (scanf("%c", &c) == 1 && c != '\n'); // Clear leftover input after menu choice

    printf("Please enter a term for validation: \n");

    // Call the recursive function to validate the input
    if (isBalanced(stack, 0)) {
        printf("The parentheses are balanced correctly.\n");
    } else {
        printf("The parentheses are not balanced correctly.\n");
    }
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
            case 3:
                 task3ParenthesisValidator();
                 break;
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

