#include <iostream>
#include <fstream>
#include "Cell.h"

//TODO delete this later
using namespace std;

int main() {
    ifstream mazeFile ("C:\\Users\\jwill\\Documents\\Repos\\data_structures\\Assignment_2\\maze.txt");
    int yLen = 0;
    string line;
    getline(mazeFile, line);
    int xLen = line.length();
    yLen++;

    while(getline(mazeFile, line)) {
        yLen++;
    }

    mazeFile.clear();
    mazeFile.seekg(0, ios::beg);

    string maze [yLen];

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

    for(int y = 0; y < yLen; y++) {
        for(int x = 0; x < xLen; x++) {
            cout << maze[y][x];
        }
        cout << endl;
    }

    auto *next = new Cell(0, 1, nullptr);
    Cell *current;
    int nextx;
    int nexty;

    int endx = xLen;
    int endy = yLen - 1;

    while(next != nullptr) {
        current = next;
        next = nullptr;

        for(int x = -1; x != 1; x += 2) {
            for(int y = -1; y != 1; y += 2) {
                nextx = current->x + x;
                nexty = current->y + y;
                if(nextx == endx && nexty == endy) {
                    cout << "End found\n";
                    return 0;
                }
                if(maze[nexty][nextx] == ' ') {
                    next = new Cell(nextx, nexty, next);
                }
            }
        }
    }
    cout << "End not found\n";
    return 0;
}