#pragma once

#include "lexer.h"

using namespace std;

class Expr {
public:
    virtual ~Expr() {}
};

class NumberExpr : public Expr {

public:
    int value;

    NumberExpr(int val) {
        value = val;
    }
};

class VariableExpr : public Expr {

public:
    string name;

    VariableExpr(string n) {
        name = n;
    }
};

class BinaryExpr : public Expr {

public:
    Expr* left;
    Token op;
    Expr* right;

    BinaryExpr(
        Expr* l,
        Token oper,
        Expr* r
    ) {
        left = l;
        op = oper;
        right = r;
    }
};

class Stmt {
public:
    virtual ~Stmt() {}
};

class LetStmt : public Stmt {

public:
    string name;
    Expr* value;

    LetStmt(
        string n,
        Expr* val
    ) {
        name = n;
        value = val;
    }
};

class PrintStmt : public Stmt {

public:
    Expr* value;

    PrintStmt(Expr* val) {
        value = val;
    }
};

class Parser {

private:
    vector<Token> tokens;
    int pos = 0;

public:

    Parser(vector<Token> t) {
        tokens = t;
    }

    Token currentToken() {
        return tokens[pos];
    }

    void advance() {
        pos++;
    }

    vector<Stmt*> parse() {

        vector<Stmt*> statements;

        while(
            currentToken().type != END
        ) {
            statements.push_back(
                parseStatement()
            );
        }

        return statements;
    }

    Stmt* parseStatement() {

        if(
            currentToken().type == LET
        ) {

            advance();

            string name =
                currentToken().value;

            advance();
            advance();

            Expr* value =
                parseExpression();

            return new LetStmt(
                name,
                value
            );
        }

        if(
            currentToken().type == PRINT
        ) {

            advance();

            Expr* value =
                parseExpression();

            return new PrintStmt(
                value
            );
        }

        return nullptr;
    }

    Expr* parseExpression() {

        Expr* left =
            parseTerm();

        while(

            currentToken().type == PLUS ||
            currentToken().type == MINUS

        ) {

            Token op =
                currentToken();

            advance();

            Expr* right =
                parseTerm();

            left = new BinaryExpr(
                left,
                op,
                right
            );
        }

        return left;
    }

    Expr* parseTerm() {

        Expr* left =
            parsePrimary();

        while(

            currentToken().type == STAR ||
            currentToken().type == SLASH

        ) {

            Token op =
                currentToken();

            advance();

            Expr* right =
                parsePrimary();

            left = new BinaryExpr(
                left,
                op,
                right
            );
        }

        return left;
    }

    Expr* parsePrimary() {

        Token token =
            currentToken();

        if(
            token.type == NUMBER
        ) {

            advance();

            return new NumberExpr(
                stoi(token.value)
            );
        }

        if(
            token.type == IDENTIFIER
        ) {

            advance();

            return new VariableExpr(
                token.value
            );
        }

        return nullptr;
    }
};