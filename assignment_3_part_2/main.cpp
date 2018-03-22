#include "Sorter.h"

int main() {
    std::regex r ("\\d+");
    std::smatch matches;
    int result = -1;
    std::string userInput;

    Sorter sorter ("F:\\Users\\jwill\\data_structures\\assignment_3_part_2\\phonebook.txt");
    std::cout << "Please specify columns to sort by.\n"
              << "Leave blank to use first column,\n"
              << "or enter up to 2 number for primary and secondary\n"
              << "columns to sort by.\n";

    while(true) {
        getline(std::cin, userInput);

        if(userInput.empty()) {
            result = sorter.setSortCols(0, 0);
            break;
        }

        if(std::regex_search(userInput, matches, r)) {
            if(matches.length() > 2) {
                std::cerr << "Error: Please only give up to 2 columns to sort by.\n";
                continue;
            }
            std::stringstream ss;
            if(matches.length() == 1) {
                int num;
                ss << matches[0];
                while(ss >> num || !ss.eof()) {
                    if(ss.fail()) {
                        std::cerr << "StringStream failed?\n";
                        return 0;
                    }
                }
                result = sorter.setSortCols(num, num);
                if(result != 0) {
                    std::cerr << "Error: First given column to sort by was to large. Please check your input and try again.\n";
                    continue;
                }
                break;
            }

            int num1, num2;
            ss << matches[0];
            while(ss >> num1 || !ss.eof()) {
                if(ss.fail()) {
                    std::cerr << "StringStream failed?\n";
                    return 0;
                }
            }
            ss.clear();
            ss << matches[1];
            while(ss >> num2 || !ss.eof()) {
                if(ss.fail()) {
                    std::cerr << "StringStream failed?\n";
                    return 0;
                }
            }
            result = sorter.setSortCols(num1, num2);
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

        } else {
            std::cerr << "Error: Invalid input. Please check and try again.\n";
            continue;
        }
        break;
    }

    sorter.Sort();



    return 0;
}