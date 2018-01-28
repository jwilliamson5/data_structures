#include <algorithm>
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
/// ^(([IDVGLSEQ])|(([IDGLS]) (\d+))|(([DS]) (\d+) (\d+)))$
///
/// \return

int main() {

//    FileHandler fh ("F:\\Users\\jwill\\data_structures\\Assignment1\\test.txt", "F:\\Users\\jwill\\data_structures\\Assignment1\\output.txt");
//    auto *lineList = new LineList();
//
//    while(fh.hasLine()) {
//        lineList->addLine(fh.getLine());
//    }
//    fh.closeInput();

    std::string command;
    std::cout << "Enter a command" << std::endl;
    while(command != "E" && command != "Q") {
        getline(std::cin, command);
        command[0] = toupper(command[0]);
        switch (command[0]) {


            default:
                break;
        }




        std::cout << command << std::endl;
    }

    return 0;
}