#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include "Pathfinder.h"

using namespace std;

int main() {
    ifstream mazeFile ("F:\\Users\\jwill\\data_structures\\Assignment_2\\maze.txt");
    int yLen = 0;
    string line;
    //Manually get first line so I can get the width
    getline(mazeFile, line);
    int xLen = line.length();
    yLen++;

    //Get height
    while(getline(mazeFile, line)) {
        yLen++;
    }

    //Move back to top of file
    mazeFile.clear();
    mazeFile.seekg(0, ios::beg);

    string maze [yLen];
    //Create the maze array
    for(int y = 0; y < yLen; y++) {
        getline(mazeFile, line);
        maze[y] = "";
        for(int x = 0; x < xLen; x++) {
            if(x >= line.length()) {
                maze[y] += " ";
            } else {
                maze[y] += line[x];
            }
        }
    }
    //Second array to keep track of visited cells
    bool *checked [yLen];
    for(int y = 0; y < yLen; y++) {
        checked[y] = new bool [xLen];
        for(int x = 0; x < xLen; x++) {
            checked[y][x] = false;
        }
    }
    //Always start in the same place, so the first 2 squares will always be the same,
    // and be marked as visited
    checked[1][0] = true;
    checked[1][1] = true;

    //Setup the initial values for the while loop
    auto *currentPf = new Pathfinder(new Coord(0,1), new Coord(1,1));
    auto *pfStack = new Stack<Pathfinder>();
    pfStack->Push(currentPf);
    auto *availablePaths = new Stack<Coord>();

    int nextx;
    int nexty;
    //Maze always ends in the same place, so use that to end the search
    int endx = xLen - 1;
    int endy = yLen - 2;

    int dirs [4] = {0, 1, 2, 3};
    int rIndex;
    int dirPlaceholder;
    srand (time(NULL));

    while(currentPf != nullptr) {
        //If the pathfinder isn't null, it will always have a next position.
        currentPf->MoveToNext();

        //Shuffle direction check order
        for(int i = 0; i < sizeof(dirs); i++) {
            rIndex = rand() % 3;
            dirPlaceholder = dirs[i];
            dirs[i] = dirs[rIndex];
            dirs[rIndex] = dirPlaceholder;
        }

        //Loop through all 4 directions in random order to search for available paths
        for(int i = 0; i < sizeof(dirs); i++) {

            nextx = currentPf->currentPos->x;
            nexty = currentPf->currentPos->y;

            switch(dirs[i]) {
                case (0):
                    nexty -= 1;
                    break;
                case (1):
                    nextx += 1;
                    break;
                case (2):
                    nexty += 1;
                    break;
                case (3):
                    nextx -= 1;
                    break;
            }
            //True if end of maze is found
            if(nextx == endx && nexty == endy) {
                cout << "Solution found." << endl;

                ofstream solvedMaze ("F:\\Users\\jwill\\data_structures\\Assignment_2\\solution.txt");
                //Draw the solution path to the maze array
                //Because it uses a stack, it draws backwards, not that it matters
                auto* path = currentPf->getPath();
                while(path->Peek() != nullptr) {
                    maze[path->Peek()->data->y][path->Peek()->data->x] = '#';
                    path->Pop();
                }
                //Write the maze with solution to solution file
                for(int a = 0; a < yLen; a++) {
                    solvedMaze << maze[a] << endl;
                }
                solvedMaze.close();

                //End program
                return 0;
            }

            if(checked[nexty][nextx]) {  //If cell has already been checked, skip
                continue;
            } else {
                checked[nexty][nextx] = true;  //Else, mark as checked
            }
            if(maze[nexty][nextx] == ' ') { //If cell is a blank space, add to available path stack
                availablePaths->Push(new Coord(nextx, nexty));
            }
        }

        //At least 1 path was found, add the first in the stack to the current Pathfinder
        if(availablePaths->Peek() != nullptr) {
            currentPf->nextPos = availablePaths->Peek()->data;
            availablePaths->Pop();
            //If more then 1 path was found, create additional pathfinders, and push them onto the stack
            while(availablePaths->Peek() != nullptr) {
                pfStack->Push(currentPf->spawnNew(availablePaths->Peek()->data));
                availablePaths->Pop();
            }
        } else { //If no path was found, pop the current pathfinder, because it has hit a dead end.
            pfStack->Pop();
        }
        //Grab the pathfinder on the top of the stack, and loop through again
        if(pfStack->Peek() != nullptr) {
            currentPf = pfStack->Peek()->data;
        }
    }
    //If the while loop is exited, then all the pathfinders hit dead ends, so no solution found.
    cout << "No solution found.\n";
    return 0;
}