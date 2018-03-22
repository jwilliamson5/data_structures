//
// Created by jwill on 2018-03-21.
//

#include "Node.h"

/***
 * Automatically splits rows into columns using white space as delimiter.
 * Type of white space doesn't matter, regex is used
 * @param colCount Number of columns
 * @param row Row of data
 * @param firstSortCol Primary column to sort by
 * @param secondSortCol Secondary column to sort by
 */
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
/***
 * since std::toupper only does 1 char at a time, this method applies it to the entire string
 * @param str String to uppercase
 * @return Uppercased string
 */
std::string Node::toUpper(std::string str) const {
    std::string rtnStr;
    for (char i : str) {
        rtnStr += std::toupper(i);
    }
    return rtnStr;
}

///All comparisons are done keeping the data as a string. Raw numbers will not be sorted properly
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
