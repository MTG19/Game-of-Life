# Game-of-Life
The Game of Life, created by mathematician John Horton Conway in 1970, is a zero-player game that simulates the evolution of a grid of cells based on simple rules of interaction. The game consists of a two-dimensional grid of cells, where each cell can either be alive or dead. The evolution of the grid is governed by a set of rules that determine whether a cell will live, die, or be born in the next generation. These rules are applied to each cell based on the state of its eight neighbors, which are the cells directly adjacent horizontally, vertically, and diagonally.

The Rules of the Game:
Underpopulation: Any live cell with fewer than two live neighbors dies.
Survival: Any live cell with two or three live neighbors remains alive.
Overpopulation: Any live cell with more than three live neighbors dies.
Reproduction: Any dead cell with exactly three live neighbors becomes alive.
Objective:
The main objective of the Game of Life is to observe the evolution of the cell grid over several generations, as the cells interact with their neighbors according to the rules. There is no direct player input; the game runs autonomously, simulating the behavior of the cells as they evolve.

Key Features of the Simulation:
Random Initialization: The grid can be randomly populated with a specified percentage of live cells.
Custom Patterns: Users can load predefined patterns from files, allowing them to experiment with different initial configurations.
Iteration Control: The user can control the number of generations to run, observing how the grid evolves over time.
Live Cell Representation: Alive cells are represented by an "A" character, and dead cells are represented by a "-" character.
Grid Display: The grid is printed on the console screen, and the state of the cells is updated on each iteration.
The Game of Life is a fascinating example of how simple rules can create complex, dynamic patterns over time. Despite the absence of a central controller, the interactions between cells can lead to interesting emergent behaviors, such as oscillators, gliders, and other self-sustaining structures.

How to Play:
Random Pattern: The user can choose to randomly populate the grid with live cells by specifying a percentage of live cells.
Load Pattern from File: Users can load custom patterns from a text file containing a grid of live and dead cells.
Iterations: The game runs for a specified number of generations, where each generation represents one "tick" of the game.
Exit: Users can choose to exit the game at any time.
