#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>

// Define token types as an enumeration
enum TokenType {
    PLUS, MINUS, MUL, DIV, MOD,  // Operators
    LT, GT, LTE, GTE, ASSIGN, EQ,  // Comparison and assignment operators
    INT, FRAC, STR, CHAR,// Data types
    ID,// Identifier
    INTL, FRACL, STRL,  // Literals
    LCUR, RCUR, LPAR, RPAR, LBRA, RBRA,  // { } ( ) [ ]
    NEWLINE, COLON, SEMI, COMMA,  // \n : ; ,
    INDENT, COMMENT, DO, WHILE, FOR, IF, ELSE, DEF,  // Keywords
    ERROR, EOF_TOKEN  // Error and End of File tokens
};

// Token structure to store the token type, string value, and the line number
struct Token {
    TokenType type;      // Type of the token
    std::string info;    // Additional information (like the actual string of an identifier or literal)
    int line;            // Line number where the token appears
};

// Node structure for the linked list
struct Node {
    Token token;
    Node* prev;
    Node* next;
};

// Linked list structure for storing tokens
struct List {
    Node* head;
    Node* tail;
    int size;

    List();                                // Constructor for initializing the list
    void addToken(const Token& token);     // Add a token to the linked list
    void printTokens(const std::vector<std::string>& sourceLines); // Print tokens in formatted output
};

// Function to convert TokenType enum to a string representation
std::string tokenTypeToString(TokenType type);

void DFA(const std::string& input, List& tokenList);  // DFA function for lexical analysis

#endif
