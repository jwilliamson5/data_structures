//
// Created by jwill on 2018-03-21.
//

#include "Sorter.h"

Sorter::Sorter(std::string pathToFile, std::string pathToOutput)
        :pathToFile(pathToFile), pathToOutput(pathToOutput)
{
    std::ifstream inputFile(pathToFile);
    std::fstream outFile (pathToOutput, std::ios::out);

    std::string tmp;
    lineCount = 0;
    colCount = 0;

    std::regex r ("[\\s]+");
    ///Token iterator splits the given text using the regex. Regex acts as the delimiter in this case
    std::sregex_token_iterator iter(tmp.begin(), tmp.end(), r, -1);
    std::sregex_token_iterator end;

    ///Grab the first line now just to get the column count
    std::getline(inputFile, tmp);
    for(; iter != end; ++iter) colCount++;

    ///First line was already retrieved, so used do->while to avoid repeating code
    ///We need to have the original list to sort into, but can't modify the original,
    ///so copy the original into the output, and use that instead
    do {
        outFile << tmp;
        if(!inputFile.eof()) {
            outFile << "\n";
        }
        lineCount++;
    } while(std::getline(inputFile, tmp));

    ///Pretty sure I don't have to close the files, but things
    /// were acting weird, so I open and close manually as needed.
    outFile.close();
    inputFile.close();
}

/***
 * Deletes the temporary files created during sorting.
 */
Sorter::~Sorter() {
    remove("1.txt");
    remove("2.txt");
    remove("tmp");
}

/***
 * Sorts the data! Make sure SortCols are set before running.
 */
void Sorter::Sort() {
    mergeSort(0, lineCount - 1);
}

/***
 * Recursively splits and merge sorts the data
 * @param first Start of a chunk (inclusive)
 * @param last End of a chunk (inclusive)
 */
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
    ///n1 and n2 are number of lines that will be written to each file
    int n1 = middle - first + 1;
    int n2 = last - middle;

    std::fstream f1 ("1.txt", std::ios::out);
    std::fstream f2 ("2.txt", std::ios::out);

    ///Write the date that will be sorted to the temp files
    for(i = 0; i < n1; i++) {
        f1 << getLine(first + i) << "\n";
    }
    for(j = 0; j < n2; j++) {
        f2 << getLine(middle + 1 + j) << "\n";
    }

    ///Close to save lines and re-open as input files
    f1.close();
    f1.open("1.txt", std::ios::in);
    f2.close();
    f2.open("2.txt", std::ios::in);

    i = 0;
    j = 0;
    k = first;

    ///Node is a custom written model so I could use operator overloads
    ///Takes in a row of data as a string and splits on it's own
    ///Right now, everything is kept as a string, so raw numbers won't sort properly
    Node *row1, *row2;
    std::string r1, r2;

    ///Grab the first 2 lines from each file
    std::getline(f1, r1);
    std::getline(f2, r2);

    while(i < n1 && j < n2) {
        ///Create the Nodes for comparison
        row1 = new Node(colCount, r1, firstSortCol, secondSortCol);
        row2 = new Node(colCount, r2, firstSortCol, secondSortCol);
        ///Sort, write sorted data to proper line, get next line to sort and increment appropriate counter
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
    ///Append any left over data to the output file
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

/***
 * Gets the requested line number
 * @param line Line number
 * @return Line contents
 */
std::string Sorter::getLine(int line) {
    std::string tmp;
    int count = 0;

    std::fstream outFile (pathToOutput, std::ios::in);
    ///Was having weird output issues, this seemed to fix
    outFile.clear();
    outFile.seekg(0, std::ios::beg);
    ///Go to requested line and return
    while(std::getline(outFile, tmp)) {
        if(line == count++) {
            return tmp;
        }
    }
    outFile.close();
}

/***
 * Writes the given line to the given line number.
 * @param lineNum Number of the line
 * @param line Line contents
 */
void Sorter::writeLine(int lineNum, std::string line) {
    std::fstream outFile (pathToOutput, std::ios::in);
    std::fstream tmpFile ("tmp", std::ios::out);

    std::string tmp;
    int count = 0;
    ///Because you can't just insert lines into a file, we have to write to a tmp file,
    ///then overwrite the output file with the contents in the tmp
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
    ///Pretty sure this is never used, but if the requested line to write is greater
    ///then lines in the file, just add empty lines to fill
    if(count++ < lineNum) {
        while(count++ < lineNum) {
            tmpFile << "\n";
        }
        tmpFile << line;
    }
    tmpFile.close();

    ///Re-open the 2 files to write from tmp back to output
    outFile.open(pathToOutput, std::ios::out);
    tmpFile.open("tmp", std::ios::in);

    while(std::getline(tmpFile, tmp)) {
        outFile << tmp;
        ///Not sure if the rest of the program cares, but this prevents an empty line at the end of the file
        if(!tmpFile.eof()) {
            outFile << "\n";
        }
    }
    outFile.close();
    tmpFile.close();
}

/***
 * Verifies given params are in bounds and set properties of columns to sort by
 * @param firstSortCol Primary sort columns
 * @param secondSortCol Second sort column
 * @return Sorter::err_code enum, 0 = ok, 1 = first_out_of_bounds, 2 = second_out_of_bounds
 */
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

/***
 * Wrote this cause I thought I would use it but I didn't
 * @return Path to output file
 */
std::string Sorter::getOutputPath() {
    return pathToOutput;
}