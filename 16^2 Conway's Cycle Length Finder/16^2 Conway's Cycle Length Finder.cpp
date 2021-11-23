// 16^2 Conway's Cycle Length Finder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

int board[16][16];
int oldboard[16][16];
std::vector<std::vector<bool>> boardstorage;
int cyclelength;

void getboard()
{
    for (int y = 0; y <= 15; y++)
    {
        for (int x = 0; x <= 15; x++)
        {
            std::cin >> board[x][y];
        }
    }
    std::cout << std::endl;
}

void printboard()
{
    for (int y = 0; y <= 15; y++)
    {
        for (int x = 0; x <= 15; x++)
        {
            if (board[x][y] == 0)
            {
                std::cout << ". ";
            }
            else
            {
                std::cout << (char)254u << ' ';
            }
            //std::cout << board[x][y] << " ";  Legacy code that prints the 1's and 0's
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void saveboard() //saves board to oldboard for comparisons needed in the cycleboard function
{
    for (int y = 0; y <= 15; y++)
    {
        for (int x = 0; x <= 15; x++)
        {
            oldboard[x][y] = board[x][y];
        }
    }
}

int liveneighbors(int x, int y) //Adds all 8 cells surrounding the current cell in question
{
    int liveneighbors = 0;
    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            if (!(i == 0 && j == 0) && (15 >= x - i) && (x - i >= 0) && (15 >= y - j) && (y - j >= 0))
            {
                liveneighbors += oldboard[(x - i)][(y - j)];
            }
        }
    }
    return liveneighbors;
}

void cycleboard() //replaces board with the next step in conway's game of life
{
    saveboard(); //saves board to oldboard for comparisons needed in calculating the three rules
    for (int y = 0; y <= 15; y++)
    {
        for (int x = 0; x <= 15; x++)
        {
            if (oldboard[x][y] == 1)
            {
                if (liveneighbors(x, y) == 2 || liveneighbors(x, y) == 3) //Any live cell with two or three live neighbors survives
                {
                    board[x][y] = 1;
                }
                else
                {
                    board[x][y] = 0; //All other live cells die in the next generation
                }
            }
            else
            {
                if (liveneighbors(x, y) == 3) //Any dead cell with three live neighbors becomes a live cell
                {
                    board[x][y] = 1;
                }
                else
                {
                    board[x][y] = 0;
                }
            }
        }
    }
}

void testliveneighbors() //Liveneighbors broke so here's a test function for free
{
    saveboard();
    int x = 0;
    int y = 0;
    std::cout << "Input x and y to see how many live neighbors a square has\nx:";
    std::cin >> x;
    std::cout << "y:";
    std::cin >> y;
    int neighbors;
    neighbors = liveneighbors(x, y);
    std::cout << "Your selected square has " << neighbors << " live neighbors";
}

void storeboard() //stores the board in a giant global bool vector called boardstorage
{
    std::vector<bool> currentbackup;
    currentbackup.resize(256);
    int offset;
    for (int y = 0; y <= 15; y++)
    {
        for (int x = 0; x <= 15; x++)
        {
            offset = x + (y*16);
            if (board[x][y] == 1)
            {
                currentbackup[offset] = true;
            }
            else
            {
                currentbackup[offset] = false;
            }
        }
    }
    boardstorage.push_back(currentbackup);
}

bool compareallboards() //Compares all boards to look for any matching boardstates, returns true when a cycle is found
{
    int numberofboards = boardstorage.size();
    for (int i = 0; i < numberofboards; i++) //loop runs once for each saved board
    {
        for (int j = (i+1); j < numberofboards; j++)
        {
            if (boardstorage[i] == boardstorage[j])
            {
                cyclelength = j - i;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int boardnumber = 0;
    bool loop = false;

    getboard();
    storeboard();

    while (loop == false)
    {
        cycleboard();
        printboard();
        storeboard();
        loop = compareallboards();
        boardnumber++;
    }
    
    std::cout << "Loop found after " << boardnumber << " iterations, loop is " << cyclelength << " cycles long.";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
