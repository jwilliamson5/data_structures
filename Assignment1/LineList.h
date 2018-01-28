#ifndef ASSIGNMENT1_LINKEDLIST_H
#define ASSIGNMENT1_LINKEDLIST_H

#include <ostream>
#include "Node.h"

class LineList {
private:
    Node *first;
    int currentLine;
    bool firstIsNull(std::string data);
public:
    LineList();
    virtual ~LineList();
    void addLine(std::string data);
    void insertBefore(int lineNum, std::string data);
    void insertBeforeCurrent(std::string data);
    void deleteLine(int lineNum);
    void deleteMultiple(int start, int end);
    void deleteCurrent();
    std::string toString();
    friend std::ostream &operator<<(std::ostream &os, const LineList &list);
};


#endif //ASSIGNMENT1_LINKEDLIST_H
