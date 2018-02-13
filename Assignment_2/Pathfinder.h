//
// Created by jwill on 2018-02-08.
//

#ifndef ASSIGNMENT_2_PATHFINDER_H
#define ASSIGNMENT_2_PATHFINDER_H

#include "Stack.h"

struct Coord {
    Coord(int x, int y):x(x), y(y) {};
    int x;
    int y;
};


class Pathfinder {
private:
    //Path taken through maze
    Stack<Coord> *path;
    //Private constructor used for in spawnNew method
    Pathfinder(Coord *currentPos, Coord *nextPos, Stack<Coord> *path);
public:
    Coord *currentPos;
    Coord *nextPos;
    Pathfinder(Coord *currentPos, Coord *nextPos);
    void MoveToNext();
    //Spawns a clone of this to travel down a different path
    Pathfinder* spawnNew(Coord *nextPos);
    Stack<Coord>* getPath();
};


#endif //ASSIGNMENT_2_PATHFINDER_H
