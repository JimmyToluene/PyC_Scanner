#include "scanner.h"
#include <iostream>

// Constructor for the linked list
List::List() : head(nullptr), tail(nullptr), size(0) {}

// Add a token to the linked list
void List::addToken(const Token& token) {
    Node* newNode = new Node{token, nullptr, nullptr};
    if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
    size++;
}

// Print all tokens with the specified format
void List::printTokens(const std::vector<std::string>& sourceLines) {
    Node* current = head;
    int lineNumber = 1;

    // Loop through all lines of the original source code
    for (const auto& line : sourceLines) {
        std::cout << "<--- " << lineNumber << ": " << line << " --->" << std::endl;

        // Print tokens for this line
        while (current && current->token.line == lineNumber) {
            if (current->token.type == ID ) {
                std::cout << "ID: " << current->token.info << std::endl;
            }else if(current->token.type == INTL) {
                std::cout << "INTL " << current->token.info << std::endl;
            }else if (current->token.type == FRACL) {
                std::cout << "FRACL " << current->token.info << std::endl;
            }else if (current->token.type == STRL) {
                std::cout << "STRL: " << current->token.info << std::endl;
            }else if (current->token.type == COMMENT) {
                std::cout << "COMMENT: " << current->token.info << std::endl;
            }else if (current->token.type == EOF_TOKEN) {
                std::cout << current->token.info << std::endl;
            }
            else {
                std::cout << tokenTypeToString(current->token.type) << std::endl;
            }
            current = current->next;
        }

        lineNumber++;
    }
}

// Convert TokenType enum to string representation
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MUL: return "MUL";
        case DIV: return "DIV";
        case MOD: return "MOD";
        case LT: return "LT";
        case GT: return "GT";
        case LTE: return "LTE";
        case GTE: return "GTE";
        case ASSIGN: return "ASSIGN";
        case EQ: return "EQ";
        case INT: return "INT";
        case FRAC: return "FRAC";
        case STR: return "STR";
        case ID: return "ID";
        case INTL: return "INTL";
        case FRACL: return "FRACL";
        case STRL: return "STRL";
        case LCUR: return "LCUR";
        case RCUR: return "RCUR";
        case LPAR: return "LPAR";
        case RPAR: return "RPAR";
        case LBRA: return "LBRA";
        case RBRA: return "RBRA";
        case NEWLINE: return "NEWLINE";
        case COLON: return "COLON";
        case SEMI: return "SEMI";
        case COMMA: return "COMMA";
        case INDENT: return "INDENT";
        case COMMENT: return "COMMENT";
        case DO: return "DO";
        case WHILE: return "WHILE";
        case FOR: return "FOR";
        case IF: return "IF";
        case ELSE: return "ELSE";
        case DEF: return "DEF";
        case ERROR: return "ERROR";
        case EOF_TOKEN: return "EOF_TOKEN";
        default: return "UNKNOWN";
    }
}
