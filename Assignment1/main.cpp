#include <regex>
#include "FileHandler.h"
#include "LineList.h"

/// Regex group legend
///
/// Group 1: Any match
///
/// Group 2: Single letter no number match
///
/// Group 3: Single letter single number match
/// Group 4: Letter from group 3
/// Group 5: Number from group 3
///
/// Group 6: Letter number number match
/// Group 7: Letter from group 6
/// Group 8: First number from group 6
/// Group 9: Second number from group 6
///
/// Regex:
/// ^(([IDVGLSEQ])|(([IDGLS]) (\d+))|(([DL]) (\d+) (\d+)))$
///
/// \return

int strToInt(std::string str) {
    std::stringstream ss;
    int rtnInt;
    ss << str.data();
    ss >> rtnInt;
    ss.clear();
    return rtnInt;
}

int main() {

    std::string inputPath;
    std::string outputPath;

    std::cout << "Enter input file path:" << std::endl;
    getline(std::cin, inputPath);
    std::cout << "Enter output file path:" << std::endl;
    getline(std::cin, outputPath);

    // F:\Users\jwill\data_structures\Assignment1\test.txt
    // F:\Users\jwill\data_structures\Assignment1\output.txt

    FileHandler fh (inputPath, outputPath);
    auto *lineList = new LineList();

    while(fh.hasLine()) {
        lineList->addLine(fh.getLine());
    }
    fh.closeInput();

    std::regex commandRegex ("^(([IDVGLSEQ])|(([IDGLS]) (\\d+))|(([DL]) (\\d+) (\\d+)))$");
    std::cmatch matches;

    std::string command;
    int loopCount;
    int matchNum;

    while(command != "E" && command != "Q") {
        std::cout << "Enter a command" << std::endl;
        getline(std::cin, command);
        command[0] = toupper(command[0]);
        if(std::regex_match(command.c_str(), matches, commandRegex)) {

            if(matches[2].matched) {
                matchNum = 2;
                loopCount = 1;
            } else if(matches[3].matched) {
                matchNum = 4;
                lineList->gotoLine(strToInt(matches[5].str()));
                loopCount = 1;
            } else if(matches[6].matched) {
                matchNum = 7;
                lineList->gotoLine(strToInt(matches[8].str()));
                loopCount = (strToInt(matches[9].str()) - lineList->getLineNum()) + 1;
            } else {
                std::cout << "Invalid command" << std::endl;
                continue;
            }

            for(int i = 0; i < loopCount; i++) {

                if(matches[matchNum] == 'L') {
                    std::cout << lineList->displayLine();
                    if(i + 1 < loopCount) {
                        lineList->gotoLine(lineList->getLineNum() + 1);
                    }
                } else if(matches[matchNum] == 'I') {
                    std::cout << "Enter text: " << std::endl;
                    getline(std::cin, command);
                    lineList->insertBefore(command);
                } else if(matches[matchNum] == 'V') {
                    std::cout << *lineList << std::endl;
                } else if(matches[matchNum] == 'D') {
                    lineList->deleteLine();
                } else if(matches[matchNum] == 'G') {
                    if(matchNum == 2) {
                        lineList->gotoLine(1);
                    }
                } else if(matches[matchNum] == 'S') {
                    std::cout << "Enter text: " << std::endl;
                    getline(std::cin, command);
                    lineList->subLine(command);
                    std::cout << *lineList << std::endl;
                } else if(matches[matchNum] == 'E') {
                    fh.writeToFile(lineList->toString());
                }
            }
        }
    }

    return 0;
}