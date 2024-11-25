
#include <iostream>
#include <vector>
#include <cstdlib>   // Includes functions for random number generation (rand), memory management, etc.
#include <ctime>     // Provides time-related functions, used here for setting the random seed (time(0))
#include <fstream>   // Provides functionality for file input and output (ifstream, ofstream)
#include <string>
#include <thread>    // Provides the ability to create and manage threads (for simulating delays in the game loop)
#include <chrono>    // Provides functionality for time durations and time-related calculations (for delays)


using namespace std;

class Universe {
private:
    int rows, cols; // Grid dimensions (rows x cols)
    vector<vector<int>> grid; // Main grid representing the state of the cells
    vector<vector<int>> tempGrid; // Temporary grid used for calculating the next generation

public:
    // Constructor to initialize the grid dimensions
    Universe(int r, int c) {
        rows = r; // Set number of rows
        cols = c; // Set number of columns
        grid = vector(rows, vector<int>(cols, 0)); // Initialize grid with all dead cells (0)
        tempGrid = vector(rows, vector<int>(cols, 0)); // Initialize temporary grid with dead cells (0)
    }

    // Randomly initialize the grid with a given percentage of alive cells
    void initialize(int alivePercentage) {
        srand(time(0)); // Initialize random seed using the current time
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Randomly decide whether the cell should be alive (1) or dead (0)
                grid[i][j] = (rand() % 100 < alivePercentage) ? 1 : 0;
            }
        }
    }

    // Reset all cells to dead (0)
    void reset() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                grid[i][j] = 0; // Set every cell in the grid to 0 (dead)
            }
        }
    }

    // Count the number of live neighbors around a given cell (x, y)
    int count_neighbors(int x, int y) {
        int count = 0; // Initialize the neighbor count to 0
        // Directions for neighbors: top-left, top, top-right, left, right, bottom-left, bottom, bottom-right
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int k = 0; k < 8; ++k) { // Loop through all 8 possible neighbors
            int nx = x + dx[k]; // Calculate the neighbor's row index
            int ny = y + dy[k]; // Calculate the neighbor's column index
            // Check if the neighbor is within bounds of the grid
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                count += grid[nx][ny]; // Increment count if the neighbor is alive
            }
        }
        return count; // Return the total number of alive neighbors
    }

    // Update the grid for the next generation based on Conway's rules
    void next_generation() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int liveNeighbors = count_neighbors(i, j); // Get the number of live neighbors for the current cell

                if (grid[i][j] == 1) { // Cell is currently alive
                    // A live cell survives if it has 2 or 3 live neighbors, otherwise it dies
                    tempGrid[i][j] = (liveNeighbors == 2 || liveNeighbors == 3) ? 1 : 0;
                } else { // Cell is currently dead
                    // A dead cell becomes alive if it has exactly 3 live neighbors
                    tempGrid[i][j] = (liveNeighbors == 3) ? 1 : 0;
                }
            }
        }
        grid = tempGrid; // Copy the temporary grid back to the main grid for the next generation
    }

    // Display the current state of the grid
    void display() {
        cout << string(1, '\n');  // Print 1 newline to simulate a "clear screen"
        // Loop through each row and column to display the grid
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Display 'A' for alive cells and '-' for dead cells
                cout << (grid[i][j] ? "A" : "-");
            }
            cout << endl; // Move to the next row
        }
        cout << "\n________________________________________________________________\n";
    }

    // Load a grid configuration from a file
    void load_from_file(const string& initialFilename = "") {
        ifstream file; // Input file stream
        string filename = initialFilename; // Create a non-const local copy of filename to allow modification

        // Keep asking for a valid filename until the file is successfully opened
        while (true) {
            if (filename.empty()) { // If no filename was passed initially, ask for user input
                cout << "Please enter the full path of the file without (' '): ";
                cin >> filename;
            }
            file.open(filename); // Try opening the file
            if (file.is_open()) { // If file was successfully opened
                break; // Exit the loop
            } else {
                cerr << "Could not open the file. Please try again.\n"; // Error message if file could not be opened
                file.clear(); // Reset file stream error state
                filename.clear(); // Clear the filename to prompt the user again
            }
        }

        // Read the dimensions of the grid (rows and columns) from the file
        file >> rows >> cols;
        // Resize the grid and temporary grid to match the new dimensions
        grid = vector(rows, vector(cols, 0));
        tempGrid = vector(rows, vector(cols, 0));

        // Read the grid pattern from the file
        for (int i = 0; i < rows; ++i) {
            string line; // String to store each line of the file
            file >> line; // Read the line representing a row of the grid
            for (int j = 0; j < cols && j < line.size(); ++j) {
                grid[i][j] = line[j] - '0'; // Convert character '0' or '1' to integer and assign to the grid
            }
        }
        file.close(); // Close the file after reading
    }

    // Run the game for a given number of generations
    void run(int iterations, int alivePercentage = 0) {
        if (alivePercentage > 0) {
            initialize(alivePercentage); // Initialize the grid randomly if not loading from a file
        }

        // Loop for the specified number of generations
        for (int i = 0; i < iterations; ++i) {
            display();          // Display the current grid state
            next_generation();  // Update the grid to the next generation
            // Pause for a short duration to simulate time between generations
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    }
};

int main() {
    int choice; // To store user's menu choice
    int rows = 0, cols = 0, iterations, alivePercentage; // Grid dimensions and other parameters
    string filename; // To store the filename for loading grid pattern

    cout << "\n___Welcome to Conway's Game of Life!___\n";
    cout << "_______________________________________\n\n";
    cout << "Please choose an option to enter the Pattern:\n";
    cout << "1. Random Pattern\n2. Load Pattern from File\n0. Exit\n";

    // Main loop for the program
    while (true) {
        cout << "\nEnter your choice: ";
        cin >> choice; // Get user input for menu choice

        if (cin.fail()) { // If the user enters an invalid value
            cout << "Invalid input. Please enter a valid number (1, 2 or 0).\n";
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            continue;
        }

        if (choice == 0) {
            cout << "Exiting the game. Goodbye!\n";
            break; // Exit the loop and terminate the game
        }

        if (choice == 1) {
            // For Random Pattern
            cout << "Enter grid dimensions (rows cols): ";
            cin >> rows >> cols;

            if (rows <= 0 || cols <= 0) {
                cout << "Invalid dimensions. Rows and columns must be positive integers.\n";
                continue;
            }

            Universe game(rows, cols); // Create Universe object with specified dimensions

            cout << "Enter percentage of live cells: ";
            cin >> alivePercentage;

            if (alivePercentage < 0 || alivePercentage > 100) {
                cout << "Invalid percentage. It must be between 0 and 100.\n";
                continue;
            }

            cout << "Enter number of generations: ";
            cin >> iterations;
            if (iterations <= 0) {
                cout << "Invalid number of generations. It must be a positive integer.\n";
                continue;
            }

            game.run(iterations, alivePercentage); // Run the game with random pattern

        } else if (choice == 2) {
            // For Load Pattern from File
            cout << "Please enter the full path of the file without (' '): ";
            cin >> filename;

            Universe game(0, 0); // Initialize an empty Universe, dimensions will be set by the file

            game.load_from_file(filename); // Load grid from the file

            cout << "Enter number of generations: ";
            cin >> iterations;
            if (iterations <= 0) {
                cout << "Invalid number of generations. It must be a positive integer.\n";
                continue;
            }

            game.run(iterations); // Run the game with the loaded pattern

        } else {
            cout << "Invalid choice. Please enter 1, 2, or 0.\n";
        }
        cout << "Nice game...Choose your pattern if you want to continue playing or Exit.\n\n1. Random Pattern\n2. Load Pattern from File\n0. Exit\n";
    }

    return 0;
}