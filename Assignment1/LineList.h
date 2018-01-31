#ifndef ASSIGNMENT1_LINKEDLIST_H
#define ASSIGNMENT1_LINKEDLIST_H

#include <ostream>
#include "Node.h"

class LineList {
private:
    Node *first;
    Node *currentNode;
    int currentLine;
    bool firstIsNull(std::string data);
public:
    LineList();
    virtual ~LineList();
    void addLine(std::string data);
    void insertBefore(std::string data);
    void deleteLine();
    std::string displayLine();
    void gotoLine(int line);
    int getLineNum();
    void subLine(std::string data);
    std::string toString();
    friend std::ostream &operator<<(std::ostream &os, const LineList &list);
};


#endif //ASSIGNMENT1_LINKEDLIST_H
