#include "LineList.h"

LineList::LineList():first(nullptr), currentNode(nullptr), currentLine(1) {}

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
        currentNode = first;
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

void LineList::insertBefore(std::string data) {
    if(currentLine == 1) {
        currentLine++;
        auto *newFirst = new Node();
        newFirst->data = data;
        newFirst->next = first;
        first = newFirst;
        currentNode = newFirst;
        return;
    }
    auto *newNode = new Node();
    newNode->data = std::move(data);
    newNode->next = currentNode->next;
    currentNode->next = newNode;
    currentNode = currentNode->next;
    currentLine++;
}

void LineList::deleteLine() {
    if(currentLine == 1) {
        first = first->next;
        currentNode = first;
        return;
    }
    Node *temp = currentNode->next;
    if(temp != nullptr) {
        currentNode->next = temp->next;
        delete temp;
    }
}

std::string LineList::displayLine() {
    if(currentLine == 1) {
        return currentNode->data + "\n";
    } else if(currentNode->next != nullptr) {
        return currentNode->next->data + "\n";
    } else {
        return "";
    }

}

void LineList::gotoLine(int line) {
    if(line == currentLine) {
        return;
    }
    currentNode = first;
    currentLine = 1;
    if(line <= currentLine) {
        return;
    }
    while(currentNode != nullptr) {
        if(currentNode->next == nullptr) {
            break;
        }
        currentLine++;
        if(currentLine == line) {
            break;
        }
        currentNode = currentNode->next;
    }
}

int LineList::getLineNum() {
    return currentLine;
}

void LineList::subLine(std::string data) {
    if(currentLine == 1) {
        currentNode->data = data;
        return;
    }
    currentNode->next->data = data;
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
