//
// Created by jwill on 2018-02-08.
//

#include "Pathfinder.h"

Pathfinder::Pathfinder(Coord *currentPos, Coord *nextPos)
        :currentPos(currentPos), nextPos(nextPos) {
    path = new Stack<Coord>();
    path->Push(currentPos);
}

Pathfinder::Pathfinder(Coord *currentPos, Coord *nextPos, Stack<Coord> *path)
        :currentPos(currentPos), nextPos(nextPos) {
    this->path = new Stack<Coord>(*path);
}

void Pathfinder::MoveToNext() {
    currentPos = nextPos;
    nextPos = nullptr;
    path->Push(currentPos);
}

Pathfinder* Pathfinder::spawnNew(Coord *nextPos) {
    return new Pathfinder(currentPos, nextPos, path);
}

Stack<Coord>* Pathfinder::getPath() {
    return path;
}