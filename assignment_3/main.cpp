#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>
#include "Sorter.h"

using namespace std;

string printArray(int* array, int arraySize) {
    string rtnStr;
    rtnStr += "[";
    for(int i = 0; i < arraySize - 1; i++) {
        rtnStr += to_string(array[i])+ ", ";
    }
    rtnStr +=  to_string(array[arraySize - 1]) + "]\n";
    return rtnStr;
}

void copyArray(int* original, int* target, int arraySize) {
    copy(original, original + arraySize, target);
}

int main() {
    string input;
    int arraySize;
    bool writeValidationFile;
    stringstream ss;

    smatch m;
    regex e ("^(\\d+)([Ww]?)$");
    smatch matches;

    cout << "Please enter the size for the array (greater than 1):\n";
    while(true) {
        ss.clear();
        getline(cin, input);

        if(!regex_search(input, matches, e)) {
            cerr << "Regex error: Input failed validation check. Please input a number, greater than 1: \n";
            continue;
        }

        ss << matches[1];

        while(ss >> arraySize || !ss.eof()) {
            if(ss.fail()) {
                cerr << "StringStream failed?\n";
                cerr << "User input: " << input << endl;
                cerr << "arraySize = " << arraySize << endl;
                return 0;
            }
        }

        if(arraySize <= 1) {
            cerr << "Size error: Please enter a number greater than 1: \n";
            ss.clear();
            string dummy;
            ss >> dummy;
            continue;
        }

        if(matches[2] == "W" || matches[2] == "w") {
            writeValidationFile = true;
        }

        break;
    }

    srand(time(NULL));
    int baseArray [arraySize];
    int arrayToSort [arraySize];

    for(int i = 0; i < arraySize; i++) {
        baseArray[i] = rand() % 32768;
    }

    Sorter sorter = Sorter();
    clock_t timer;
    double sort_time;

    ofstream timeFile;
    if(writeValidationFile) {
        timeFile.open("sort_validation.txt");
        timeFile << "Sort validation\n";
        timeFile << "Unsorted: " << printArray(baseArray, arraySize);
    } else {
        timeFile.open("times.txt", ios::app);
        timeFile << arraySize;
    }

    string sortTypeStrings [6] = {"Bubble sort", "Selection sort", "Insertion sort", "Shell sort", "Merge sort", "Quick sort"};

    for(int i = 0; i <= sorter.quick_sort; i++) {
        copyArray(baseArray, arrayToSort, arraySize);
        timer = clock();
        sorter.sort(arrayToSort, arraySize, Sorter::sortType(i));
        sort_time = double(clock() - timer) / CLOCKS_PER_SEC;

        if(writeValidationFile) {
            timeFile << sortTypeStrings[i] << ": " << printArray(arrayToSort, arraySize);
        } else {
            timeFile << " | " << sort_time;
        }
    }
    timeFile << endl;

    return 0;
}