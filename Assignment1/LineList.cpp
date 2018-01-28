#include "LineList.h"

LineList::LineList():first(nullptr), currentLine(1) {}

LineList::~LineList() {
    Node *node = first;
    while(node != nullptr) {
        Node *temp = node;
        node = node->next;
        delete temp;
    }
}

bool LineList::firstIsNull(std::string data) {
    if(first == nullptr) {
        first = new Node;
        first->data = std::move(data);
        return true;
    }
    return false;
}

void LineList::addLine(std::string data) {
    if(firstIsNull(data)) return;

    Node *node = first;
    while(node->next != nullptr) {
        node = node->next;
    }
    auto *newLine  = new Node;
    newLine->data = std::move(data);
    node->next = newLine;
}

void LineList::insertBefore(int lineNum, std::string data) {
    if(firstIsNull(data)) return;
    Node *node = first;
    if(lineNum <= 1) {
        auto *newFirst = new Node();
        newFirst->data = data;
        newFirst->next = node;
        first = newFirst;
        return;
    }
    currentLine = 0;
    while(node->next != nullptr) {
        currentLine += 1;
        if(currentLine == lineNum - 1) {
            break;
        }
        node = node->next;
    }
    auto *newNode = new Node();
    newNode->data = std::move(data);
    newNode->next = node->next;
    node->next = newNode;
    currentLine += 1;
}

void LineList::insertBeforeCurrent(std::string data) {
    insertBefore(currentLine, std::move(data));
}

void LineList::deleteLine(int lineNum) {
    if(lineNum <= 0) return;
    Node *node = first;
    if(lineNum == 1) {
        first = first->next;
        delete node;
        return;
    }
    currentLine = 0;
    while(node != nullptr) {
        currentLine += 1;
        if(currentLine + 1 == lineNum) {
            Node *temp = node->next;
            node->next = temp->next;
            delete temp;
            currentLine += 1;
            break;
        }
        node = node->next;
    }
}

void LineList::deleteMultiple(int start, int end) {
    for(int i = start; i <= end; i++) {
        deleteLine(start);
    }
}

void LineList::deleteCurrent() {
    deleteLine(currentLine);
}

std::string LineList::toString() {
    std::string text;
    Node *node = first;
    while(node != nullptr) {
        text += node->data;
        if(node->next != nullptr) {
            text += "\n";
        }
        node = node->next;
    }
    return text;
}

std::ostream &operator<<(std::ostream &os, const LineList &list) {
    Node *node = list.first;
    while(node != nullptr) {
        os << node->data << "\n";
        node = node->next;
    }
    return os;
}
