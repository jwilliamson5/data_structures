#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include "Pathfinder.h"

using namespace std;

void gotoxy( int x, int y )
{
    COORD p = { x, y };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}

void pause(float seconds) {
    clock_t t;
    t = clock();
    while((float) (clock() - t) / CLOCKS_PER_SEC < seconds) {
        continue;
    }
}

int main() {
    ifstream mazeFile ("F:\\Users\\jwill\\data_structures\\Assignment_2\\maze.txt");
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

    bool *checked [yLen];
    for(int y = 0; y < yLen; y++) {
        checked[y] = new bool [xLen];
        for(int x = 0; x < xLen; x++) {
            checked[y][x] = false;
        }
    }
    checked[1][0] = true;
    checked[1][1] = true;

    auto *startPos = new Coord(0,1);
    auto *nextPos = new Coord(1,1);
    auto *currentPf = new Pathfinder(startPos, nextPos);
    auto *finderQueue = new Node<Pathfinder>(currentPf, nullptr);
    Node<Coord> *availablePaths = nullptr;

    int nextx;
    int nexty;

    int endx = xLen - 1;
    int endy = yLen - 2;

    while(finderQueue != nullptr) {
        currentPf->MoveToNext();

        for(int y = -1; y < 2; y ++) {
            for(int x = -1; x < 2; x ++) {
                if(abs(x) == abs(y)) {
                    continue;
                }

                nextx = currentPf->currentPos->x + x;
                nexty = currentPf->currentPos->y + y;

                if(nextx == endx && nexty == endy) {

                    for(int a = 0; a < yLen; a++) {
                        cout << maze[a] << endl;
                    }

                    Node<Coord> *reversePath = nullptr;
                    Node<Coord> *path = currentPf->getPath();
                    while(path != nullptr) {
                        maze[path->data->y][path->data->x] = '#';
                        reversePath = new Node<Coord>(path->data, reversePath);
                        path = path->next;
                    }

                    ofstream solvedMaze ("F:\\Users\\jwill\\data_structures\\Assignment_2\\solution.txt");

                    for(int a = 0; a < yLen; a++) {
                        for(int b = 0; b < xLen; b++) {
                            solvedMaze << maze[a][b];
                        }
                        solvedMaze << endl;
                    }
                    solvedMaze.close();
                    cin.ignore();
                    while(reversePath != nullptr) {
                        gotoxy(reversePath->data->x, reversePath->data->y);
                        cout << "#";
                        reversePath = reversePath->next;
                        pause(0.0001);
                    }

                    cin.ignore();
                    return 0;
                }

                if(checked[nexty][nextx]) {
                    continue;
                } else {
                    checked[nexty][nextx] = true;
                }
                if(maze[nexty][nextx] == ' ') {
                    availablePaths = new Node<Coord>(new Coord(nextx, nexty), availablePaths);
                }
            }
        }

        if(availablePaths != nullptr) {
            currentPf->nextPos = availablePaths->data;
            availablePaths = availablePaths->next;

            while(availablePaths != nullptr) {
                finderQueue = new Node<Pathfinder>(currentPf->spawnNew(availablePaths->data), finderQueue);
                availablePaths = availablePaths->next;
            }
        } else {
            finderQueue = finderQueue->next;
        }

        if(finderQueue != nullptr) {
            currentPf = finderQueue->data;
        }
    }

    cout << "End not found\n";
    return 0;
}





























