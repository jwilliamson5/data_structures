//
// Created by jwill on 2018-02-08.
//

#ifndef ASSIGNMENT_2_PATHFINDER_H
#define ASSIGNMENT_2_PATHFINDER_H

#include "Node.h"

struct Coord {
    Coord(int x, int y):x(x), y(y) {};
    int x;
    int y;
};


class Pathfinder {
private:
    Node<Coord> *path;
    Pathfinder(Coord *currentPos, Coord *nextPos, Node<Coord> *path);
public:
    Coord *currentPos;
    Coord *nextPos;
    Pathfinder(Coord *currentPos, Coord *nextPos);
    void MoveToNext();
    Pathfinder* spawnNew(Coord *nextPos);
    Node<Coord>* getPath();
};


#endif //ASSIGNMENT_2_PATHFINDER_H
