#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

enum TokenType {
    NUMBER,
    IDENTIFIER,
    LET,
    PRINT,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    EQUAL,
    END
};

struct Token {
    TokenType type;
    string value;
};

class Lexer {

private:
    string source;
    int pos = 0;

public:

    Lexer(string src) {
        source = src;
    }

    vector<Token> tokenize() {

        vector<Token> tokens;

        while(pos < source.length()) {

            char current = source[pos];

            if(isspace(current)) {
                pos++;
                continue;
            }

            if(isdigit(current)) {

                string number;

                while(
                    pos < source.length() &&
                    isdigit(source[pos])
                ) {
                    number += source[pos];
                    pos++;
                }

                tokens.push_back({
                    NUMBER,
                    number
                });

                continue;
            }

            if(isalpha(current)) {

                string word;

                while(
                    pos < source.length() &&
                    isalnum(source[pos])
                ) {
                    word += source[pos];
                    pos++;
                }

                if(word == "let") {

                    tokens.push_back({
                        LET,
                        word
                    });
                }

                else if(word == "print") {

                    tokens.push_back({
                        PRINT,
                        word
                    });
                }

                else {

                    tokens.push_back({
                        IDENTIFIER,
                        word
                    });
                }

                continue;
            }

            switch(current) {

                case '+':

                    tokens.push_back({
                        PLUS,
                        "+"
                    });

                    break;

                case '-':

                    tokens.push_back({
                        MINUS,
                        "-"
                    });

                    break;

                case '*':

                    tokens.push_back({
                        STAR,
                        "*"
                    });

                    break;

                case '/':

                    tokens.push_back({
                        SLASH,
                        "/"
                    });

                    break;

                case '=':

                    tokens.push_back({
                        EQUAL,
                        "="
                    });

                    break;
            }

            pos++;
        }

        tokens.push_back({
            END,
            "END"
        });

        return tokens;
    }
};