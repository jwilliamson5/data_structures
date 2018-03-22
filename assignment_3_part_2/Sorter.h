//
// Created by jwill on 2018-03-21.
//

#include "Node.h"
#include <fstream>

#ifndef ASSIGNMENT_3_PART_2_SORTER_H
#define ASSIGNMENT_3_PART_2_SORTER_H


class Sorter {
private:
    std::string pathToFile;
    std::string pathToOutput;

    int colCount;
    int lineCount;

    int firstSortCol;
    int secondSortCol;

    void mergeSort(int first, int last);
    void merge(int first, int middle, int last);

    std::string getLine(int line);
    void writeLine(int lineNum, std::string line);
public:
    enum err_code {no_error, first_out_of_bounds, second_out_of_bounds};
    Sorter(std::string pathToFile, std::string pathToOutput);
    ~Sorter();
    void Sort();
    int setSortCols(int firstSortCol, int secondSortCol);
    std::string getOutputPath();
};


#endif //ASSIGNMENT_3_PART_2_SORTER_H
