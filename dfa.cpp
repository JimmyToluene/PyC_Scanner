#include "scanner.h"
#include <cctype>  // For isdigit, isalpha, etc.
#include <algorithm>  // For std::remove_if to clean comment strings

// Helper function to trim leading/trailing whitespace and remove comment symbols
std::string cleanComment(const std::string& comment) {
    std::string cleaned = comment;
    cleaned.erase(0, cleaned.find_first_not_of(" \t\n\r\f\v"));  // Trim leading whitespace
    cleaned.erase(cleaned.find_last_not_of(" \t\n\r\f\v") + 1);  // Trim trailing whitespace
    return cleaned;
}

// DFA function for lexical analysis
void DFA(const std::string& input, List& tokenList) {
    size_t currentPos = 0;
    std::string tokenString = "";
    TokenType currentState = ERROR;  // Initial state
    int currentLine = 1;  // Track the current line number
    bool atLineStart = true;  // Track whether we are at the start of a line
    int indentLevel = 0;  // Track indentation level

    while (currentPos < input.size()-1) {
        char currentChar = input[currentPos];

        if (atLineStart && isspace(currentChar) && currentChar != '\n') {
            // Handle spaces for indentation only at the start of the line
            indentLevel++;
            currentPos++;
            continue;
        }

        if (atLineStart && indentLevel > 0) {
            tokenList.addToken({INDENT, std::to_string(indentLevel) + " spaces", currentLine});
            indentLevel = 0;
            atLineStart = false;  // End of indentation
        }

        // Handle regular characters with a switch-case
        switch (currentChar) {
            case '+':
                tokenList.addToken({PLUS, "+", currentLine});
                atLineStart = false;
                break;
            case '-':
                // Handle negative numbers and negative fractions
                    if (currentPos + 1 < input.size() && isdigit(input[currentPos + 1])) {
                        tokenString = "-";
                        currentPos++;
                        while (currentPos < input.size() && isdigit(input[currentPos])) {
                            tokenString += input[currentPos++];
                        }
                        // Check if the next character is a colon (:) for a fraction
                        if (currentPos < input.size() && input[currentPos] == ':') {
                            tokenString += ":";  // Include the colon
                            currentPos++;
                            // Process the denominator (can also be negative)
                            std::string denominator = "";
                            if (currentPos < input.size() && input[currentPos] == '-') {
                                denominator += "-";  // Include the negative sign for the denominator
                                currentPos++;
                            }
                            while (currentPos < input.size() && isdigit(input[currentPos])) {
                                denominator += input[currentPos++];
                            }
                            tokenString += denominator;  // Add denominator to the fraction
                            tokenList.addToken({FRACL, tokenString, currentLine});
                        } else {
                            // If not a fraction, treat it as a negative integer literal
                            tokenList.addToken({INTL, tokenString, currentLine});
                        }
                        currentPos--;  // Adjust for loop increment
                    } else {
                        tokenList.addToken({MINUS, "-", currentLine});
                    }
                atLineStart = false;
                break;
            case '*':
                tokenList.addToken({MUL, "*", currentLine});
                atLineStart = false;
                break;
            case '/':
                if (currentPos + 1 < input.size() && input[currentPos + 1] == '*') {
                    // Handle multi-line comment /*...*/
                    std::string comment;
                    currentPos += 2;
                    while (currentPos + 1 < input.size() && !(input[currentPos] == '*' && input[currentPos + 1] == '/')) {
                        comment += input[currentPos++];
                    }
                    tokenList.addToken({COMMENT, cleanComment(comment), currentLine});
                    currentPos++;  // Skip over the closing '/';
                } else if (currentPos + 1 < input.size() && input[currentPos + 1] == '/') {
                    // Handle single-line comment starting with //
                    std::string comment;
                    currentPos += 2;
                    while (currentPos < input.size() && input[currentPos] != '\n') {
                        comment += input[currentPos++];
                    }
                    tokenList.addToken({COMMENT, cleanComment(comment), currentLine});
                    tokenList.addToken({NEWLINE, "\\n", currentLine});  // End the line after the comment
                    currentLine++;
                    atLineStart = true;  // Reset to the start of the next line
                } else {
                    tokenList.addToken({DIV, "/", currentLine});
                }
                atLineStart = false;
                break;
            case '\"':
                if(1) {
                    std::string comment;
                    currentPos += 1;
                    while (currentPos + 1 < input.size() && !(input[currentPos] == '\"')) {
                        comment += input[currentPos++];
                    }
                    tokenList.addToken({STRL, comment, currentLine});
                    currentPos++;  // Skip over the closing '/';
                }
                atLineStart = false;
                break;
            case '%':
                tokenList.addToken({MOD, "%", currentLine});
                atLineStart = false;
                break;
            case '=':
                if (currentPos + 1 < input.size() && input[currentPos + 1] == '=') {
                    // If the next character is also '=', treat it as an equality check (EQ)
                    tokenList.addToken({EQ, "==", currentLine});
                    currentPos++;  // Skip over the second '='
                } else {
                    // Otherwise, treat it as an assignment (ASSIGN)
                    tokenList.addToken({ASSIGN, "=", currentLine});
                }
                atLineStart = false;
                break;
            case '<':
                tokenList.addToken({LT, "<", currentLine});
                atLineStart = false;
                break;
            case '>':
                tokenList.addToken({GT, ">", currentLine});
                atLineStart = false;
                break;
            case ';':
                tokenList.addToken({SEMI, ";", currentLine});
                atLineStart = false;
                break;
            case '[':
                tokenList.addToken({LBRA, "[", currentLine});
                atLineStart = false;
                break;
            case ']':
                tokenList.addToken({RBRA, "]", currentLine});
                atLineStart = false;
                break;
            case '{':
                tokenList.addToken({LCUR, "{", currentLine});
            atLineStart = false;
            break;
            case '}':
                tokenList.addToken({RCUR, "}", currentLine});
            atLineStart = false;
            break;
            case '(':
                tokenList.addToken({LPAR, "(", currentLine});
            atLineStart = false;
            break;
            case ')':
                tokenList.addToken({RPAR, ")", currentLine});
            atLineStart = false;
            break;
            case ':':
                tokenList.addToken({COLON, ":", currentLine});
                atLineStart = false;
                break;
            case ',':
                tokenList.addToken({COMMA, ",", currentLine});
            atLineStart = false;
            break;
            case '\n':
                tokenList.addToken({NEWLINE, "\\n", currentLine});
                currentLine++;
                atLineStart = true;  // Start of a new line
                indentLevel = 0;  // Reset indentation for the new line
                break;
            case '#': {
                // Handle single-line comment starting with #
                std::string comment;
                currentPos++;
                while (currentPos < input.size() && input[currentPos] != '\n') {
                    comment += input[currentPos++];
                }
                tokenList.addToken({COMMENT, cleanComment(comment), currentLine});
                tokenList.addToken({NEWLINE, "\\n", currentLine});  // End the line after the comment
                currentLine++;
                atLineStart = true;  // Reset to the start of the next line
                break;
            }
            default:
                if (isdigit(currentChar)) {
                    // Handle integer literals and fractions like 1:9
                    tokenString = "";
                    while (currentPos < input.size() && isdigit(input[currentPos])) {
                        tokenString += input[currentPos++];
                    }
                    if (currentPos < input.size() && input[currentPos] == ':' && (input[currentPos + 1] == '-'||isdigit(input[currentPos + 1]))) {
                        // If it's a fraction, handle numerator and denominator, including negative numerators
                        tokenString += ":";  // Add the colon
                        currentPos++;

                        // Handle denominator (including negative)
                        std::string denominator = "";
                        if (currentPos < input.size() && input[currentPos] == '-') {
                            denominator += "-";  // Include the negative sign
                            currentPos++;
                        }
                        while (currentPos < input.size() && isdigit(input[currentPos])) {
                            denominator += input[currentPos++];
                        }

                        tokenString += denominator;  // Add denominator to the fraction string
                        tokenList.addToken({FRACL, tokenString, currentLine});
                        currentPos--;  // Adjust for loop increment
                    } else {
                        // Otherwise, it's just an integer literal
                        tokenList.addToken({INTL, tokenString, currentLine});
                        currentPos--;  // Adjust for loop increment
                    }
                    atLineStart = false;
                } else if (isalpha(currentChar)) {
                    // Handle identifiers and keywords
                    tokenString = "";
                    while (currentPos < input.size() && (isalnum(input[currentPos]) || input[currentPos] == '_')) {
                        tokenString += input[currentPos++];
                    }

                    // Check for specific keywords like int, char, str
                    if (tokenString == "int") {
                        tokenList.addToken({INT, tokenString, currentLine});
                    } else if (tokenString == "char") {
                        tokenList.addToken({CHAR, tokenString, currentLine});
                    } else if (tokenString == "fraction"||tokenString == "frac") {
                        tokenList.addToken({FRAC, tokenString, currentLine});
                    } else if (tokenString == "string"||tokenString == "str") {
                        tokenList.addToken({STR, tokenString, currentLine});
                    } else if (tokenString == "if"  || tokenString == "for" ) {
                        tokenList.addToken({IF, tokenString, currentLine});
                    } else if(tokenString == "else") {
                        tokenList.addToken({ELSE, tokenString, currentLine});
                    } else if(tokenString == "do") {
                        tokenList.addToken({DO, tokenString, currentLine});
                    } else if(tokenString == "while") {
                        tokenList.addToken({WHILE, tokenString, currentLine});
                    } else if(tokenString == "def") {
                        tokenList.addToken({DEF, tokenString, currentLine});
                    } else if(tokenString == "for") {
                       tokenList.addToken({FOR, tokenString, currentLine});
                    }
                    else {
                        // If not a keyword, treat it as an identifier
                        tokenList.addToken({ID, tokenString, currentLine});
                    }
                    currentPos--;  // Adjust for loop increment
                    atLineStart = false;
                } else if (!isspace(currentChar)) {
                    // Handle any unknown characters as errors
                    tokenList.addToken({ERROR, std::string(1, currentChar), currentLine});
                    atLineStart = false;
                }
                break;
        }

        currentPos++;  // Move to the next character
    }
    tokenList.addToken({EOF_TOKEN, "EOF", currentLine});
}
