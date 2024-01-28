# IFCC - Compilation Project
## About The Project
The goal of this project is to develop an end-to-end compiler of C language. This involves implementing a complete chain to analyze and transform a language.

### Build With
- C++11
- ANTLR 4.12.0

## Getting Started
Below are some instructions on setting up this project locally.
### Prerequisites
Install antlr using your distribution's  package manager, or run the provided shell script:   
```sh
./install-antlr.sh
```
### Installation 
1. Clone the repo
   ```sh
   git clone https://github.com/lamdang2k/ifcc-2023
   ```
2. Execute the script `*_runmake.sh`
3. Run the executable file `ifcc` in the folder `compiler/build`
### Test Execution
- Execute `run_test.sh` to run all the tests
- Enter `-h` option to see available commands
- Enter `-c` option to clean the tests results directory

## Usage
### Features Implemented
:heavy_check_mark: Variables  
:heavy_check_mark: Integer and character constants (with simple quote)  
:heavy_check_mark: Basic arithmetic operations: +,-, *  
:heavy_check_mark: bitwise logical operations: |, &,ˆ  
:heavy_check_mark: Comparison operations: ==, !=, <, >  
:heavy_check_mark: Unary operations: ! and -  
:heavy_check_mark: Declaration of variables anywhere  
:heavy_check_mark: Assignment (which, in C, also returns a value)  
:heavy_check_mark: Ability to initialise a variable when declaring it  
:heavy_check_mark: Use of the standard putchar and getchar functions for input/output  
:heavy_check_mark: Definition of functions with parameters, and return type int, char or void  
:heavy_check_mark: Check the consistency of function calls and their parameters  
:heavy_check_mark: Block structure using { and }  
:heavy_check_mark: Support for variable scoping and shadowing  
:heavy_check_mark: if, else, while control structures  
:heavy_check_mark: Support for return expression anywhere  
:heavy_check_mark: Check that a variable used in an expression has been declared  
:heavy_check_mark: Check that a variable is not declared more than once  
:heavy_check_mark: Check that a declared variable is used at least once  
:heavy_check_mark: Division and modulo  
:heavy_check_mark: Arrays (one-dimensional)  
### Features Currently Being Implemented
:pencil2: Basic data types char(32bits) and int(32bits) [char must change to 8 bits].  
:pencil2: Retargeting to several architectures: x86, MSP430, ARM [IR achieved].  
:pencil2: Character strings represented by arrays of char [no assignment of a character string with a string].  
:pencil2: Propagation of simple constants  
:pencil2: Propagation of constant variables (with data-flow analysis)  
### Features Not Supported
:x: Assignment operators +=, -= etc., increment ++ and decrement --.  
:x: Pointers  
:x: break and continue  
:x: switch...case  
:x: Lazy logical operators ||, &&  
:x: Propagation of simple constants  
:x: Propagation of constant variables (with data-flow analysis)  
:x: Global variables  
:x: Other control structures: for, do...while  
:x: Detailed support for all other arithmetic and logical operators: <=, >=, << and >> etc.  
:x: Other basic types such as inttypes.h, float, double, etc.  

## Source Files Information
- `ifcc.g4` contains the grammar in antlr4 format
- `main.cpp` contains the C++ code to call the antlr4-generated parser
  on the file name provided in the command line.
- `CodeGenVisitor.h` produces the actual assembly-language output
- `Makefile` contains  the actual build  logic.
  The  Makefile uses  3  variables (ANTLRJAR,  ANTLRINC and  ANTLRLIB)
  indicating the location of various parts of the Antlr suite. 
  You can (should)  change  those values to suit your installation, either
  by editing the  Makefile and/or on the command  line, as illustrated
  by the `*_runmake` scripts.
- `fedora_runmake.sh` is an example of such a script. it shows how
  makefile variables can be overriden from the command-line.

  <!-- LICENSE -->
## License
Distributed under the BSD 2-Clause "Simplified"  License.

<!-- CONTACT -->
## Authors
Thanh Lam DANG  
Maud ANDRUSZAK  
Jorge KORGUT  
Florian PAUTRAT  
Quoc Viet PHAM  
Mohamed Khalil LOUKHNATI  
Taha ISMAILI  
Anass AMMARI  
Contact us by email: firstname.lastname@insa-lyon.fr

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments
This project is a part of the Compilation course at INSA Lyon.

