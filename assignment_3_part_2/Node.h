//
// Created by jwill on 2018-03-21.
//
#include <iostream>
#include <regex>

#ifndef ASSIGNMENT_3_PART_2_NODE_H
#define ASSIGNMENT_3_PART_2_NODE_H


class Node {
public:
    int colCount;
    int firstSortCol = 0;
    int secondSortCol = 0;
    std::string* columns;

    Node(int colCount, std::string row, int firstSortCol, int secondSortCol);
    ~Node();

    std::string toUpper(std::string str) const;

    bool operator<(const Node &rhs) const;
    bool operator>(const Node &rhs) const;
    bool operator<=(const Node &rhs) const;
    bool operator>=(const Node &rhs) const;
};


#endif //ASSIGNMENT_3_PART_2_NODE_H
