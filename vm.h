#pragma once

#include "compiler.h"
#include <unordered_map>

using namespace std;

class VM {

private:

    vector<int> stack;

    unordered_map<string, int> variables;

public:

    void execute(
        vector<Instruction> instructions
    ) {

        for(
            Instruction instr :
            instructions
        ) {

            switch(instr.op) {

                case PUSH: {

                    stack.push_back(
                        instr.value
                    );

                    break;
                }

                case ADD: {

                    int b = stack.back();
                    stack.pop_back();

                    int a = stack.back();
                    stack.pop_back();

                    stack.push_back(
                        a + b
                    );

                    break;
                }

                case SUB: {

                    int b = stack.back();
                    stack.pop_back();

                    int a = stack.back();
                    stack.pop_back();

                    stack.push_back(
                        a - b
                    );

                    break;
                }

                case MUL: {

                    int b = stack.back();
                    stack.pop_back();

                    int a = stack.back();
                    stack.pop_back();

                    stack.push_back(
                        a * b
                    );

                    break;
                }

                case DIV: {

                    int b = stack.back();
                    stack.pop_back();

                    int a = stack.back();
                    stack.pop_back();

                    stack.push_back(
                        a / b
                    );

                    break;
                }

                case STORE: {

                    int value =
                        stack.back();

                    stack.pop_back();

                    variables[
                        instr.name
                    ] = value;

                    break;
                }

                case LOAD: {

                    stack.push_back(

                        variables[
                            instr.name
                        ]

                    );

                    break;
                }

                case PRINT_OP: {

                    cout
                        << "PRINT: "
                        << stack.back()
                        << endl;

                    stack.pop_back();

                    break;
                }
            }
        }
    }
};