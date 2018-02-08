//
// Created by jwill on 2018-02-08.
//

#ifndef ASSIGNMENT_2_CELL_H
#define ASSIGNMENT_2_CELL_H

class Cell {
public:
    Cell *next;
    const int x;
    const int y;
    Cell(int x, int y, Cell *next);
    virtual ~Cell();
};


#endif //ASSIGNMENT_2_CELL_H
