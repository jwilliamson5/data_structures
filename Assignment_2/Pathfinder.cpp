//
// Created by jwill on 2018-02-08.
//

#include "Pathfinder.h"

Pathfinder::Pathfinder(Coord *currentPos, Coord *nextPos)
        :currentPos(currentPos), nextPos(nextPos) {
    path = new Node<Coord>(currentPos, nullptr);
}

Pathfinder::Pathfinder(Coord *currentPos, Coord *nextPos, Node<Coord> *path)
        :currentPos(currentPos), nextPos(nextPos), path(path) {}

void Pathfinder::MoveToNext() {
    currentPos = nextPos;
    nextPos = nullptr;
    path = new Node<Coord>(currentPos, path);
}

Pathfinder* Pathfinder::spawnNew(Coord *nextPos) {
    return new Pathfinder(currentPos, nextPos, path);
}

Node<Coord>* Pathfinder::getPath() {
    return path;
}