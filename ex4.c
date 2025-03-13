/******************
Name: Omri Halfon
ID: 324209402
Assignment: ex4
*******************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define NUMBER_OF_ROWS_IN_PYRAMID 5 // Number of rows in the pyramid
#define SIZE 20 // General size for arrays
#define MAX_LETTERS 15 // Maximum number of letters per word
#define ROW 0
#define COLUMN 1
#define LENGTH 2
#define SLOTS 3

// Function declarations for tasks
void task1_robot_paths(); // Task 1: Calculate robot paths
void task2_human_pyramid(); // Task 2: Simulate human pyramid weights
void task3_parenthesis_validator(); // Task 3: Validate parentheses
void task4_queens_battle(); // Task 4: Solve the queens puzzle
void task5_crossword_generator(); // Task 5: Generate a crossword puzzle

// Helper function declarations

// Update weight in human pyramid
float update_weight(int row, int column, float weights[NUMBER_OF_ROWS_IN_PYRAMID][NUMBER_OF_ROWS_IN_PYRAMID]);
// Calculate number of paths for robot
int number_of_paths(int column, int row);
// Get valid parenthesis character
char getpernatesis(char c);
// Get matching closing parenthesis
char getopositesis(char c);
// Check if parentheses are valid
int validparenthesis(char open);
// Check if row is safe for a queen
int isRowQueen(char solve[SIZE][SIZE], int row, int col, int N);
// Check if column is safe for a queen
int isColQueen(char solve[SIZE][SIZE], int row, int col, int N);
// Check if diagonals are safe for a queen
int closeQueen(char solve[SIZE][SIZE], int row, int col, int N);
// Validate zones in queens puzzle
int zoneCheck(char solve[SIZE][SIZE], char board[SIZE][SIZE],
    char zone, int row, int col, int N);
// Perform all checks for queens
int checkAll(char solve[SIZE][SIZE], char board[SIZE][SIZE], int rowQ, int colQ, int N);
// Place all queens
int placeAllQueens(char solve[SIZE][SIZE], char board[SIZE][SIZE], int row, int col, int N);
// Count letters in a word
int count_letters(char words[SIZE][MAX_LETTERS], int specRow, int col);
// Place a word in the crossword grid
void place_word_by_position(char words[SIZE][MAX_LETTERS], char grid[SIZE][SIZE],
    int specRow, int colWord, int rowGrid, int colGrid, int length,char direction, int gridSize);
// Clean a grid section
void clean_grid(char grid[SIZE][SIZE], int row, int col, int length, char direction);
// Check word crossing validity
int check_crossing(char words[SIZE][MAX_LETTERS], char grid[SIZE][SIZE], int specRow, int wordCol,
    int wordRow, char direction, int length, int col, int row, int sizeGrid);
// Check all crossword constraints
int check_all(char words[SIZE][MAX_LETTERS], char grid[SIZE][SIZE], int specRow, int wordCol, int wordRow,
    char direction, int length, int col, int row, int sizeGrid);
// Place all words in the crossword grid
int place_all_words(char words[SIZE][MAX_LETTERS], char grid[SIZE][SIZE], int slots, int slot, char directions[],
    int place[][SLOTS], int wordIndex[], int wordToTry, int sizeGrid);
// Initialize solution board '*'
void initialize_board(char solve[SIZE][SIZE],int size,int row,int col);
// Initialize grid cells with '#'
void initialize_grid(char grid[SIZE][SIZE], int size, int row, int col);
float update_weight(int row, int column, float weights[NUMBER_OF_ROWS_IN_PYRAMID][NUMBER_OF_ROWS_IN_PYRAMID]) {
    // Top row
    if (row == 0) {
        return weights[row][0];
    }
    // Left edge
    if (column == 0) {
        return weights[row][column] + (update_weight(row - 1, column, weights) / 2);
    }
    // Right edge
    if (column == row) {
        return weights[row][column] + (update_weight(row - 1, column - 1, weights) / 2);
    }
    // Middle elements
    return weights[row][column] + (update_weight(row - 1, column, weights) / 2) +
        (update_weight(row - 1, column - 1, weights) / 2);
}
int number_of_paths(int column, int row) {
    // Base case: reached home
    if (column == 0 && row == 0) {
        return 1;
    }
    // Out of bounds
    if (column < 0 || row < 0) {
        return 0;
    }
    // Recursive case: sum of paths from left and above
    return number_of_paths(column, row - 1) + number_of_paths(column - 1, row);
}

char getopositesis(char c) {
    // Return the matching closing parenthesis for a given opening parenthesis
    switch (c) {
        case '(': return ')';
        case '[': return ']';
        case '<': return '>';
        case '{': return '}';
        default: return 0;
    }
}

char getpernatesis(char c) {
    // Return the valid parenthesis character
    switch (c) {
        case '(': return c;
        case ')': return ')';
        case '[': return '[';
        case ']': return ']';
        case '<': return '<';
        case '>': return '>';
        case '{': return '{';
        case '}': return '}';
        case '\n': return '\n';
        default: return 0;
    }
}

int validparenthesis(char open) {
    char current;
    if (scanf("%c", &current) != 1 || current == '\n') { // End of input
        if (open != '\0') {
            // Unmatched opening parenthesis
            return 1;
        }
        // Valid
        return 0;
    }
    // Ignore invalid characters
    if (getpernatesis(current) == 0) {
        return validparenthesis(open);
    }
    if (current == '(' || current == '[' || current == '{' || current == '<') {
        if (validparenthesis(current) == 1) {
            return 1; // Invalid
        }
        // Continue checking
        return validparenthesis(open);
    }

    if (current == ')' || current == ']' || current == '}' || current == '>') {
        if (open == '\0' || getopositesis(open) != current) {
            scanf("%*s");
            return 1; // Invalid
        }
        return 0; // Valid
    }

    return 1; // Invalid
}

int isRowQueen(char solve[SIZE][SIZE], int row, int col, int N) {
    // Checked all columns in the row
    if (col >= N)
        return 1;
    // Queen found
    if (solve[row][col] == 'X')
        return 0;
    // Check next column
    return isRowQueen(solve, row, col + 1, N);
}

int isColQueen(char solve[SIZE][SIZE], int row, int col, int N) {
    // Checked all rows in the column
    if (row >= N)
        return 1;
    // Queen found
    if (solve[row][col] == 'X')
        return 0;
    // Check next row
    return isColQueen(solve, row + 1, col, N);
}

int closeQueen(char solve[SIZE][SIZE], int row, int col, int N) {
    // Check if queens are too close diagonally
    if (row < N - 1 && col < N - 1 && solve[row + 1][col + 1] == 'X')
        return 0;
    if (row > 0 && col < N - 1 && solve[row - 1][col + 1] == 'X')
        return 0;
    if (row < N - 1 && col > 0 && solve[row + 1][col - 1] == 'X')
        return 0;
    if (row > 0 && col > 0 && solve[row - 1][col - 1] == 'X')
        return 0;
    return 1; // Safe
}

int zoneCheck(char solve[SIZE][SIZE], char board[SIZE][SIZE], char zone, int row, int col, int N) {
    // Checked all rows
    if (row >= N)
        return 1;
    // Checked all columns in the row
    if (col >= N)
        return zoneCheck(solve, board, zone, row + 1, 0, N);
    // Queen violates zone
    if (board[row][col] == zone && solve[row][col] == 'X')
        return 0;
    // Continue checking
    return zoneCheck(solve, board, zone, row, col + 1, N);
}

int checkAll(char solve[SIZE][SIZE], char board[SIZE][SIZE], int rowQ, int colQ, int N) {
    // Check all constraints for placing a queen
    return isRowQueen(solve, rowQ, 0, N) &&
           isColQueen(solve, 0, colQ, N) &&
           closeQueen(solve, rowQ, colQ, N) &&
           zoneCheck(solve, board, board[rowQ][colQ], 0, 0, N);
}

int placeAllQueens(char solve[SIZE][SIZE], char board[SIZE][SIZE], int row, int col, int N) {
    // All queens placed
    if (row >= N)
        return 1;
    // Out of bounds
    if (col >= N)
        return 0;
    // Check if position is valid
    if (checkAll(solve, board, row, col, N)) {
        // Place queen
        solve[row][col] = 'X';
        if (placeAllQueens(solve, board, row + 1, 0, N))
            return 1; // Successful placement
        solve[row][col] = '*'; // Backtrack
    }
    // Try next column
    return placeAllQueens(solve, board, row, col + 1, N);
}

int count_letters(char words[SIZE][MAX_LETTERS], int specRow, int col) {
    // Base case: reached the end of the word or exceeded max letters
    if (col >= MAX_LETTERS || words[specRow][col] == '\0') {
        return 0;
    }
    // Recursive case: count the current letter and move to the next
    return 1 + count_letters(words, specRow, col + 1);
}

int check_crossing(char words[SIZE][MAX_LETTERS], char grid[SIZE][SIZE], int specRow, int wordCol,
    int wordRow, char direction, int length, int col, int row, int sizeGrid) {
    // Base case: all letters placed
    if (length <= 0) {
        return 1;
    }
    // Check if the position is out of grid bounds
    if (col < 0 || col >= sizeGrid || row < 0 || row >= sizeGrid) {
        return 0;
    }
    // Check if the grid cell is already occupied by a different character
    if (grid[row][col] != '#' && grid[row][col] != words[specRow][wordCol]) {
        return 0;
    }
    // Recursive case for horizontal placement
    if (direction == 'H') {
        return check_crossing(words, grid, specRow, wordCol + 1,wordRow, direction, length - 1, col + 1,row,sizeGrid);
    // Recursive case for vertical placement
    } else if (direction == 'V') {
        return check_crossing(words, grid, specRow, wordCol+1, wordRow+1, direction,length-1, col, row + 1,sizeGrid);
    }
    // Invalid direction
    return 0;
}

int check_all(char words[SIZE][MAX_LETTERS], char grid[SIZE][SIZE], int specRow,
    int wordCol, int wordRow, char direction, int length, int col, int row, int sizeGrid) {
    // Ensure the word can be placed and the length matches the dictionary word
    return check_crossing(words, grid, specRow, wordCol, wordRow, direction, length, col, row, sizeGrid) &&
           (length == count_letters(words, specRow, 0));
}

void place_word_by_position(char words[SIZE][MAX_LETTERS], char grid[SIZE][SIZE], int specRow,
    int colWord, int rowGrid, int colGrid, int length, char direction, int gridSize) {
    // Base case: all letters placed
    if (length <= 0) {
        return;
    }
    // Place the letter in the current grid position
    if (direction == 'H') {
        // Place horizontally
        grid[rowGrid][colGrid] = words[specRow][colWord];
        place_word_by_position(words, grid, specRow, colWord + 1, rowGrid, colGrid + 1, length - 1,direction, gridSize);
    } else if (direction == 'V') {
        // Place vertically
        grid[rowGrid][colGrid] = words[specRow][colWord];
        place_word_by_position(words, grid, specRow, colWord + 1, rowGrid + 1, colGrid, length - 1,direction, gridSize);
    }
}

void clean_grid(char grid[SIZE][SIZE], int row, int col, int length, char direction) {
    // Base case: cleaned all positions
    if (length <= 0) {
        return;
    }
    // Check bounds to avoid invalid grid access
    if (row < 0 || col < 0 || row >= SIZE || col >= SIZE) {
        return;
    }
    // Reset the current grid position
    grid[row][col] = '#';
    // Recursive case: clean horizontally or vertically
    if (direction == 'H') {
        clean_grid(grid, row, col + 1, length - 1, direction);
    } else if (direction == 'V') {
        clean_grid(grid, row + 1, col, length - 1, direction);
    }
}

int place_all_words(char words[SIZE][MAX_LETTERS], char grid[SIZE][SIZE], int slots, int slot,
    char directions[], int place[][SLOTS], int wordIndex[], int wordToTry, int sizeGrid) {
    // Base case: all slots filled
    if (slot >= slots) {
        return 1;
    }
    // Base case: no more words to try
    if (wordToTry >= SIZE) {
        return 0;
    }

    // Get current slot details
    char direction = directions[slot];
    int row = place[slot][ROW];
    int col = place[slot][COLUMN];
    int length = place[slot][LENGTH];

    // Skip already used words
    if (wordIndex[wordToTry]) {
        return place_all_words(words, grid, slots, slot, directions, place, wordIndex, wordToTry + 1, sizeGrid);
    }

    // Check if the current word can fit in the slot
    if (check_all(words, grid, wordToTry, 0, row, direction, length, col, row, sizeGrid)) {
        place_word_by_position(words, grid, wordToTry,0,row,col, length,
            direction, sizeGrid); // Place the word
        wordIndex[wordToTry] = 1; // Mark word as used

        // Recursively place the next word
        if (place_all_words(words, grid, slots, slot + 1, directions, place, wordIndex, 0, sizeGrid)) {
            return 1;
        }

        // Backtrack if placing the word did not lead to a solution
        clean_grid(grid, row, col, length, direction);
        // Mark word as unused
        wordIndex[wordToTry] = 0;
    }

    // Try the next word in the dictionary
    return place_all_words(words, grid, slots, slot, directions, place, wordIndex, wordToTry + 1, sizeGrid);
}
void initialize_board(char solve[SIZE][SIZE],int size,int row,int col) {
    if(row >= size) {
        return;
    }
    solve[row][col] = '*';
    if(col >= size) {
        initialize_board(solve, size, row+1, 0);
    }
    else {
        initialize_board(solve, size, row, col+1);
    }
}
void initialize_grid(char grid[SIZE][SIZE],int size,int row,int col) {
    if(row >= size) {
        return;
    }
    grid[row][col] = '#';
    if(col >= size) {
        initialize_grid(grid, size, row+1, 0);
    }
    else {
        initialize_grid(grid, size, row, col+1);
    }
}




int main() {
    int task = -1; // Variable to store task choice
    do {
        // Display menu
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task)) { // Read user input
            switch (task) {
            case 6: {
                printf("Goodbye!\n");
                break; // Exit the loop
            }
            case 1: {
                task1_robot_paths();
                break; // Task 1: Robot paths
            }
            case 2:
                task2_human_pyramid();
                break; // Task 2: Human pyramid
            case 3:
                task3_parenthesis_validator();
                break; // Task 3: Parenthesis validation
            case 4:
                task4_queens_battle();
                break; // Task 4: Queens battle
            case 5:
                task5_crossword_generator();
                break; // Task 5: Crossword generator
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        } else {
            scanf("%*s"); // Ignore invalid input
        }
    } while (task != 6);
    return 0;
}

void task1_robot_paths()
{
    // Coordinates of the robot
    int column, row;
    printf("Please enter the coordinates of the robot (column, row):\n");
    // Input coordinates
    scanf("%d %d", &column, &row);
    // Check for invalid coordinates
    if (column < 0 || row < 0) {
        printf("The total number of paths the robot can take to reach home is: %d\n", 0);
    }
    else {
        // Calculate and print the number of paths
        printf("The total number of paths the robot can take to reach home is: %d\n",number_of_paths(column, row));
    }
}

void task2_human_pyramid()
{
    printf("Please enter the weights of the cheerleaders:\n");
    // Initialize weights array
    float weights[NUMBER_OF_ROWS_IN_PYRAMID][NUMBER_OF_ROWS_IN_PYRAMID] = {0};
    // Input weights row by row
    for (int i = 0; i < NUMBER_OF_ROWS_IN_PYRAMID; i++) {
        for (int j = 0; j <= i; j++) {
            // Input weight of a cheerleader
            scanf("%f", &weights[i][j]);
            if(weights[i][j] < 0 ) {
                printf("Negative weights are not supported.\n");
                return;
            }
        }
    }
    printf("The total weight on each cheerleader is:\n");
    for (int i = 0; i < NUMBER_OF_ROWS_IN_PYRAMID; i++) {
        for (int j = 0; j <= i; j++) {
            // Print updated weight
            printf("%.2f ", update_weight(i, j, weights));
        }
        // New line after each row
        printf("\n");
    }
}

void task3_parenthesis_validator() {
    printf("Please enter a term for validation:\n");
    getchar();
    // Check if parentheses are valid
    if (!validparenthesis('\0')) {
        printf("The parentheses are balanced correctly.\n");
    } else {
        printf("The parentheses are not balanced correctly.\n");
    }
}
void task4_queens_battle() {
    // Input board
    char board[SIZE][SIZE] = {0};
    // Solution board
    char boardSolve[SIZE][SIZE] = {0};
    int N; // Board size
    printf("Please enter the board dimensions:\n");
    // Input board size
    scanf("%d", &N);
    printf("Please enter a %d*%d puzzle board:\n", N, N);
    // Input board configuration
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Input board cell
            scanf(" %c", &board[i][j]);
        }
    }
    // Initialize solution board '*'
    initialize_board(boardSolve,N,0,0);
    // Solve the puzzle
    if (placeAllQueens(boardSolve, board, 0, 0, N)) {
        printf("Solution:\n");
        // Print the solution board
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%c ", boardSolve[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("This puzzle cannot be solved.\n");
    }
}

void task5_crossword_generator()
{
    // Number of words in the dictionary
    int numWords;
    // Size of the crossword grid
    int sizeGrid;
    // Number of slots in the crossword
    int slots;
    printf("Please enter the dimensions of the crossword grid:\n");
    // Input grid size
    scanf("%d", &sizeGrid);
    // Initialize crossword grid
    char grid[SIZE][SIZE];
    // Initialize grid cells with '#'
    initialize_grid(grid,sizeGrid,0,0);
    printf("Please enter the number of slots in the crossword:\n");
    // Input number of slots
    scanf("%d", &slots);
    // Slot details (row, column, length)
    int place[slots][SLOTS];
    // Slot directions (H/V)
    char directions[slots];
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int i = 0; i < slots; i++) {
        // Input slot details
        scanf("%d %d %d %c", &place[i][0], &place[i][1], &place[i][2], &directions[i]);
    }

    printf("Please enter the number of words in the dictionary:\n");
    // Input number of words
    scanf("%d", &numWords);
    // Ensure enough words for the slots
    while (numWords < slots) {
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", slots);
        // Input valid dictionary size
        scanf("%d", &numWords);
    }
    // Dictionary of words
    char words[numWords][MAX_LETTERS];
    printf("Please enter the words for the dictionary:\n");
    for (int i = 0; i < numWords; i++) {
        // Input words
        scanf("%s", words[i]);
    }
    // Array to track placed words
    int wordIndex[SIZE] = {0};
    // No solution possible
    if (!place_all_words(words, grid, slots, 0, directions, place, wordIndex, 0, sizeGrid)) {
        printf("This crossword cannot be solved.\n");
    } else {
        // Print the crossword grid
        for (int i = 0; i < sizeGrid; i++) {
            for (int j = 0; j < sizeGrid; j++) {
                printf("| %c ", grid[i][j]);
            }
            printf("|\n");
        }
    }
}
