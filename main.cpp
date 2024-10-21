#include <iostream>
#include <fstream>  // For file handling
#include <string>
#include <vector>
#include "scanner.h"

// Function to check the file extension
bool hasValidExtension(const std::string& fileName) {
    size_t dotPosition = fileName.find_last_of(".");
    if (dotPosition == std::string::npos) return false;

    std::string extension = fileName.substr(dotPosition);
    return (extension == ".py" || extension == ".c" || extension == ".pc");
}

// Function to read the contents of the file
std::vector<std::string> readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    std::vector<std::string> sourceLines;
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            sourceLines.push_back(line);
        }
        file.close();
    } else {
        throw std::runtime_error("Unable to open file: " + fileName);
    }

    return sourceLines;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];

    // Check if the file has a valid extension
    if (!hasValidExtension(fileName)) {
        std::cerr << "Error: Unsupported file type. Please use .py, .c, or .PC files." << std::endl;
        return 1;
    }

    // Try to read the file
    std::vector<std::string> sourceLines;
    try {
        sourceLines = readFile(fileName);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Join the source lines into a single string for DFA processing
    std::string sourceCode = "";
    for (const auto& line : sourceLines) {
        sourceCode += line + "\n";
    }

    // Create a token list
    List tokenList;

    // Call DFA to analyze the source code
    DFA(sourceCode, tokenList);

    // Print the generated tokens in the desired format
    tokenList.printTokens(sourceLines);

    return 0;
}
