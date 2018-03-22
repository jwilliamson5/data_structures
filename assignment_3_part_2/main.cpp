#include "Sorter.h"

int main() {
    ///Regex matches anything other then white space
    std::regex r ("[^\\s]+");
    std::smatch matches;
    ///Init result to a value that can;t be return from Sorter error enum
    int result = -1;
    std::string userInput;
    ///Array to hold column numbers given by user
    int givenCols [2];

    std::string inputPath;
    std::string outputPath;

    std::cout << "Enter path to input file:\n";
    while(getline(std::cin, inputPath)) {
        std::ifstream test (inputPath);
        ///Check if path is valid by attempting to open
        if(!test) {
            std::cerr << "Invalid path, please try again.\n";
            continue;
        }
        break;
    }

    std::cout << "Enter path to output file:\n";
    while(getline(std::cin, outputPath)) {
        std::ofstream test (outputPath, std::ios::app);
        ///Check if path is valid by attempting to open, use std::ios::app to avoid erasing file accidentally
        if(!test || outputPath == inputPath) {
            std::cerr << "Invalid path, please try again.\n";
            continue;
        }
        break;
    }

    ///Sorter assumes paths are valid, will now erase contents of given output file if it exists
    Sorter sorter (inputPath, outputPath);

    std::cout << "Please enter columns to sort by.\n"
              << "Leave blank to use first column,\n"
              << "or enter up to 2 number for primary and secondary\n"
              << "columns to sort by.\n";

    while(getline(std::cin, userInput)) {
        ///Empty input, sort by first column
        if(userInput.empty()) {
            result = sorter.setSortCols(1, 1);
            break;
        }

        bool invalidInput = false;
        std::stringstream ss;

        int i = 0;
        for(; i < 2; i++) {
            ///Input has something, so loop to split the input, break if no more input
            if(!std::regex_search(userInput, matches, r)) {
                break;
            }
            ss << matches[0];
            ss >> givenCols[i];
            ///Parse int, if fail then non-number was entered
            if(ss.fail()) {
                std::cerr << "Error: Invalid input, please check and try again.\n";
                invalidInput = true;
                break;
            }
            ss.clear();
            ///Matches.suffix() returns everything after current match
            userInput = matches.suffix();
        }
        ///If there was invalid input, error message was already displayed, loop back for more input
        if(invalidInput) {
            continue;
        }

        ///If more then 2 inputs were given, display error, loop back for more input
        if(std::regex_search(userInput, matches, r)) {
            std::cerr << "Error: Please only give up to 2 columns to sort by.\n";
            continue;
        }

        ///Iterate through given columns, make sure they are greater then 0
        for(int a = 0; a < i; a++) {
            if(givenCols[a] < 1) {
                std::cerr << "Error: All given columns must be greater than 0.\n";
                invalidInput = true;
                break;
            }
        }
        ///If a column is less then zero, loop back for more input
        if(invalidInput) {
            continue;
        }
        ///If only 1 input was given, set both array values to the first number.
        if(i == 1) {
            givenCols[1] = givenCols[0];
        }
        ///Sorter checks if given columns are equal on its own
        result = sorter.setSortCols(givenCols[0], givenCols[1]);

        ///Returned int from setSortCols is error enum, to make sure given values are within bounds
        switch (result) {
            case Sorter::first_out_of_bounds:
                std::cerr << "Error: First given column to sort by was to large. Please check your input and try again.\n";
                continue;
            case Sorter::second_out_of_bounds:
                std::cerr << "Error: Second given column to sort by was to large. Please check your input and try again.\n";
                continue;
            default:
                break;
        }
        ///If we got here, input is valid and sort columns are set, so we're good to go!
        break;
    }
    std::cout << "Starting sort...\n";
    ///Timed it just cause I was curious
    clock_t timer = clock();
    sorter.Sort();
    std::cout << "Sorting finished in " << double(clock() - timer) / CLOCKS_PER_SEC << " seconds.\n";
    return 0;
}