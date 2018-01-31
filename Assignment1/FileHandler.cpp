#include "FileHandler.h"

FileHandler::FileHandler(std::string inputFilePath, std::string outputFilePath)
        :inputFilePath(inputFilePath), inputFile(inputFilePath), outputFilePath(outputFilePath), outputFile(outputFilePath) {}

FileHandler::~FileHandler() {
    if(inputFile.is_open()) {
        inputFile.close();
    }
    if(outputFile.is_open()) {
        outputFile.close();
    }
}

bool FileHandler::hasLine() {
    return (inputFile.peek() != EOF);
}

std::string FileHandler::getLine() {
    std::string line;
    getline(inputFile, line);
    return line;
}

bool FileHandler::writeToFile(std::string data) {
    if(outputFile.is_open()) {
        outputFile << data;
        closeOutput();
        return true;
    }
    return false;
}

void FileHandler::closeInput() {
    inputFile.close();
}

void FileHandler::closeOutput() {
    outputFile.close();
}

