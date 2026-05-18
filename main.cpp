#include "vm.h"

#include <fstream>
#include <sstream>

using namespace std;

string opcodeToString(
    OpCode op
) {

    switch(op) {

        case PUSH:
            return "PUSH";

        case ADD:
            return "ADD";

        case SUB:
            return "SUB";

        case MUL:
            return "MUL";

        case DIV:
            return "DIV";

        case STORE:
            return "STORE";

        case LOAD:
            return "LOAD";

        case PRINT_OP:
            return "PRINT";
    }

    return "UNKNOWN";
}

int main() {

    ifstream file("script.cvm");

    if(!file.is_open()) {

        cout
            << "Failed to open script.cvm"
            << endl;

        return 1;
    }

    stringstream buffer;

    buffer << file.rdbuf();

    string source = buffer.str();

    Lexer lexer(source);

    vector<Token> tokens =
        lexer.tokenize();

    Parser parser(tokens);

    vector<Stmt*> program =
        parser.parse();

    Compiler compiler;

    for(
        Stmt* stmt :
        program
    ) {

        compiler.compileStatement(
            stmt
        );
    }

    cout
        << "BYTECODE:\n"
        << endl;

    for(
        Instruction instr :
        compiler.instructions
    ) {

        cout << opcodeToString(
                    instr.op
                );

        if(
            instr.op == PUSH
        ) {

            cout
                << " "
                << instr.value;
        }

        if(

            instr.op == STORE ||
            instr.op == LOAD

        ) {

            cout
                << " "
                << instr.name;
        }

        cout << endl;
    }

    cout << endl;

    VM vm;

    vm.execute(
        compiler.instructions
    );

    return 0;
}