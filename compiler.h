#pragma once

#include "parser.h"

using namespace std;

enum OpCode {

    PUSH,

    ADD,
    SUB,
    MUL,
    DIV,

    STORE,
    LOAD,

    PRINT_OP
};

struct Instruction {

    OpCode op;

    int value = 0;

    string name = "";
};

class Compiler {

public:

    vector<Instruction> instructions;

    void compile(Expr* expr) {

        if(
            dynamic_cast<NumberExpr*>(expr)
        ) {

            NumberExpr* num =
                dynamic_cast<NumberExpr*>(expr);

            instructions.push_back({

                PUSH,
                num->value,
                ""

            });
        }

        else if(
            dynamic_cast<VariableExpr*>(expr)
        ) {

            VariableExpr* var =
                dynamic_cast<VariableExpr*>(expr);

            instructions.push_back({

                LOAD,
                0,
                var->name

            });
        }

        else if(
            dynamic_cast<BinaryExpr*>(expr)
        ) {

            BinaryExpr* bin =
                dynamic_cast<BinaryExpr*>(expr);

            compile(bin->left);
            compile(bin->right);

            switch(bin->op.type) {

                case PLUS:

                    instructions.push_back({
                        ADD,
                        0,
                        ""
                    });

                    break;

                case MINUS:

                    instructions.push_back({
                        SUB,
                        0,
                        ""
                    });

                    break;

                case STAR:

                    instructions.push_back({
                        MUL,
                        0,
                        ""
                    });

                    break;

                case SLASH:

                    instructions.push_back({
                        DIV,
                        0,
                        ""
                    });

                    break;

                default:
                    break;
            }
        }
    }

    void compileStatement(Stmt* stmt) {

        if(
            dynamic_cast<LetStmt*>(stmt)
        ) {

            LetStmt* letStmt =
                dynamic_cast<LetStmt*>(stmt);

            compile(
                letStmt->value
            );

            instructions.push_back({

                STORE,
                0,
                letStmt->name

            });
        }

        else if(
            dynamic_cast<PrintStmt*>(stmt)
        ) {

            PrintStmt* printStmt =
                dynamic_cast<PrintStmt*>(stmt);

            compile(
                printStmt->value
            );

            instructions.push_back({

                PRINT_OP,
                0,
                ""

            });
        }
    }
};