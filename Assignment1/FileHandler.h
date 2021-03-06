#ifndef ASSIGNMENT1_FILEHANDLER_H
#define ASSIGNMENT1_FILEHANDLER_H

#include <iostream>
#include <fstream>

class FileHandler {
private:
    std::string inputFilePath;
    std::string outputFilePath;
    std::ifstream inputFile;
    std::ofstream outputFile;
public:
    FileHandler(std::string inputFilePath, std::string outputFilePath);
    virtual ~FileHandler();
    bool hasLine();
    std::string getLine();
    bool writeToFile(std::string data);
    void closeInput();
    void closeOutput();
};


#endif //ASSIGNMENT1_FILEHANDLER_H
