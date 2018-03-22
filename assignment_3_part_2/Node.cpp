//
// Created by jwill on 2018-03-21.
//

#include "Node.h"

Node::Node(int colCount, std::string row, int firstSortCol, int secondSortCol)
        :colCount(colCount), firstSortCol(firstSortCol), secondSortCol(secondSortCol)
{
    columns = new std::string [this->colCount];
    std::regex r ("[\\s]+");
    std::sregex_token_iterator iter(row.begin(), row.end(), r, -1);
    std::sregex_token_iterator end;

    int counter = 0;
    for(; iter != end; ++iter) {
        columns[counter++] = *iter;
    }

}

Node::~Node() {
    delete (columns);
}

std::string Node::toUpper(std::string str) const {
    std::string rtnStr;
    for (char i : str) {
        rtnStr += std::toupper(i);
    }
    return rtnStr;
}

bool Node::operator<(const Node &rhs) const {
    std::string thisFirst = toUpper(columns[firstSortCol]),
    otherFirst = toUpper(rhs.columns[firstSortCol]),
    thisSecond = toUpper(columns[secondSortCol]),
    otherSecond = toUpper(rhs.columns[secondSortCol]);

    for(int a = 0; a < thisFirst.length(); a++) {
        if(thisFirst[a] < otherFirst[a]) {
            return true;
        }
    }

    for(int a = 0; a < thisFirst.length(); a++) {
        if(thisSecond[a] < otherSecond[a]) {
            return true;
        }
    }

    return false;

}

bool Node::operator>(const Node &rhs) const {
    return rhs < *this;
}

bool Node::operator<=(const Node &rhs) const {
    std::string thisFirst = toUpper(columns[firstSortCol]),
            otherFirst = toUpper(rhs.columns[firstSortCol]),
            thisSecond = toUpper(columns[secondSortCol]),
            otherSecond = toUpper(rhs.columns[secondSortCol]);

    for(int a = 0; a < thisFirst.length(); a++) {
        if(thisFirst[a] == otherFirst[a]) {
            continue;
        } else {
            return thisFirst[a] <= otherFirst[a];
        }
    }

    for(int a = 0; a < thisFirst.length(); a++) {
        if(thisSecond[a] == otherSecond[a]) {
            continue;
        } else {
            return thisSecond[a] <= otherSecond[a];
        }
    }

    return true;
}

bool Node::operator>=(const Node &rhs) const {
    return rhs <= *this;
}
