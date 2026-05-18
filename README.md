CVM++

A simple stack based virtual machine and mini compiler made in C++.

This project takes a custom scripting language, converts it into tokens, parses it into an AST, generates bytecode instructions, and finally executes them using a stack-based virtual machine.



Features

- Lexer / Tokenizer
- Recursive Descent Parser
- Abstract Syntax Tree (AST)
- Bytecode Compiler
- Stack Based Virtual Machine
- Variable Assignment
- Arithmetic Operations
- Print Statements



Supported Operations

+   Addition
-   Subtraction
*   Multiplication
/   Division



Example Script

let x = 10
let y = 20
let z = x + y * 2
print z



Output

BYTECODE:

PUSH 10
STORE x
PUSH 20
STORE y
LOAD x
LOAD y
PUSH 2
MUL
ADD
STORE z
LOAD z
PRINT

PRINT: 50



Project Structure

main.cpp      -> Main execution flow
lexer.h       -> Tokenizer
parser.h      -> Parser + AST
compiler.h    -> Bytecode Compiler
vm.h          -> Virtual Machine
script.cvm    -> Input script



How To Run

Compile:

g++ main.cpp -o cvm

Run:

./cvm



Pipeline

Source Code
   ↓
Lexer
   ↓
Parser
   ↓
AST
   ↓
Compiler
   ↓
Bytecode
   ↓
Virtual Machine
   ↓
Output



Tech Used

- C++
- Stack Based Execution
- Bytecode Instructions
- Recursive Descent Parsing