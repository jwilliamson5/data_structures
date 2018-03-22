//
// Created by jwill on 2018-03-21.
//

#include "Sorter.h"

Sorter::Sorter(std::string pathToFile)
        :pathToFile(pathToFile)
{
    inputFile.open(pathToFile);
    std::string tmp;
    lineCount = 0;
    std::fstream outFile ("out.txt", std::ios::out);

    std::getline(inputFile, tmp);
    std::regex r ("[\\s]+");
    std::sregex_token_iterator iter(tmp.begin(), tmp.end(), r, -1);
    std::sregex_token_iterator end;
    colCount = 0;
    for(; iter != end; ++iter) colCount++;

    do {
        outFile << tmp;
        if(!inputFile.eof()) {
            outFile << "\n";
        }
        lineCount++;
    } while(std::getline(inputFile, tmp));

    outFile.close();
    inputFile.close();
}

Sorter::~Sorter() {
    remove("1.txt");
    remove("2.txt");
    remove("tmp");
    if(inputFile.is_open()) {
        inputFile.close();
    }
}

void Sorter::Sort() {
    mergeSort(0, lineCount - 1);
}

void Sorter::mergeSort(int first, int last) {
    if(first < last) {
        int middle = (first + (last - 1)) / 2;
        mergeSort(first, middle);
        mergeSort(middle + 1, last);
        merge(first, middle, last);
    }
}

void Sorter::merge(int first, int middle, int last) {
    int i, j, k;
    int n1 = middle - first + 1;
    int n2 = last - middle;

    std::fstream f1 ("1.txt", std::ios::out);
    std::fstream f2 ("2.txt", std::ios::out);

    for(i = 0; i < n1; i++) {
        f1 << getLine(first + i) << "\n";
    }
    for(j = 0; j < n2; j++) {
        f2 << getLine(middle + 1 + j) << "\n";
    }

    f1.close();
    f1.open("1.txt", std::ios::in);
    f2.close();
    f2.open("2.txt", std::ios::in);

    i = 0;
    j = 0;
    k = first;

    Node *row1, *row2;
    std::string r1, r2;

    std::getline(f1, r1);
    std::getline(f2, r2);

    while(i < n1 && j < n2) {
        row1 = new Node(colCount, r1, firstSortCol, secondSortCol);
        row2 = new Node(colCount, r2, firstSortCol, secondSortCol);
        if(*row1 <= *row2) {
            writeLine(k++, r1);
            std::getline(f1, r1);
            i++;
        } else {
            writeLine(k++, r2);
            std::getline(f2, r2);
            j++;
        }
    }

    while(i < n1) {
        writeLine(k++, r1);
        std::getline(f1, r1);
        i++;
    }

    while(j < n2) {
        writeLine(k++, r2);
        std::getline(f2, r2);
        j++;
    }
    f1.close();
    f2.close();
}

std::string Sorter::getLine(int line) {
    std::string tmp;
    int count = 0;
    std::fstream outFile ("out.txt", std::ios::in);
    outFile.clear();
    outFile.seekg(0, std::ios::beg);
    while(std::getline(outFile, tmp)) {
        if(line == count++) {
            return tmp;
        }
    }
    outFile.close();
}

void Sorter::writeLine(int lineNum, std::string line) {
    std::fstream outFile ("out.txt", std::ios::in);
    std::fstream tmpFile ("tmp", std::ios::out);

    std::string tmp;
    int count = 0;
    while(std::getline(outFile, tmp)) {
        if(lineNum == count++) {
            tmpFile << line;
            if(!outFile.eof()) {
                tmpFile << "\n";
            }
        } else {
            tmpFile << tmp;
            if(!outFile.eof()) {
                tmpFile << "\n";
            }
        }
    }
    outFile.close();
    if(count++ < lineNum) {
        while(count++ < lineNum) {
            tmpFile << "\n";
        }
        tmpFile << line;
    }
    tmpFile.close();

    outFile.open("out.txt", std::ios::out);
    tmpFile.open("tmp", std::ios::in);

    while(std::getline(tmpFile, tmp)) {
        outFile << tmp;
        if(!tmpFile.eof()) {
            outFile << "\n";
        }
    }
    outFile.close();
    tmpFile.close();
}

int Sorter::setSortCols(int firstSortCol, int secondSortCol) {
    if(--firstSortCol > colCount) {
        return first_out_of_bounds;
    }
    if(--secondSortCol > colCount) {
        return second_out_of_bounds;
    }
    this->firstSortCol = firstSortCol;
    this->secondSortCol = secondSortCol;
    return no_error;
}