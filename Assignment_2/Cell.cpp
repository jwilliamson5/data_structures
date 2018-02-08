//
// Created by jwill on 2018-02-08.
//

#include "Cell.h"

Cell::Cell(int x, int y, Cell *next)
        :x(x), y(y), next(next) {}
Cell::~Cell() {
    if(next != nullptr) {
        delete next;
    }
};


