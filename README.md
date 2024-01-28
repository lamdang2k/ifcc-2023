# PLD Compilateur
## Authors
Thanh Lam DANG  
Maud ANDRUSZAK  
Jorge KORGUT  
Florian PAUTRAT  
Quoc Viet PHAM  
Mohamed Khalil LOUKHNATI  
Taha ISMAILI  
Anass AMMARI  

## Compilation
- To run the compilation process, just execute the script `*_runmake.sh`
- Executable `ifcc` is inside the folder `compiler/build`

## Test execution
- To run all the tests, the script `run_test.sh` can be executed. 
- To see available commands `run_test.sh -h`.
- To clean the tests results directory `run_test.sh -c`

## Display gui
- Windows : On powershell type `powershell.exe -noprofile -executionpolicy bypass -file .\windows_tree.ps1 path/to/your/file.c`
- Ubuntu : `ubuntu_runmake.sh gui FILE=path/to/your/file.c`

## Features Implemented
:heavy_check_mark: Variables  
:heavy_check_mark: Constantes entières et caractère (avec simple quote)  
:heavy_check_mark: Opérations arithmétiques de base : +,-, *  
:heavy_check_mark: Opérations logiques bit-à-bit : |, &,ˆ  
:heavy_check_mark: Opérations de comparaison : ==, !=, <, >  
:heavy_check_mark: Opérations unaires : ! et -  
:heavy_check_mark: Déclaration de variables n’importe où  
:heavy_check_mark: Affectation (qui, en C, retourne aussi une valeur)  
:heavy_check_mark: Possibilité d’initialiser une variable lors de sa déclaration  
:heavy_check_mark: Utilisation des fonctions standard putchar et getchar pour les entrées-sorties  
:heavy_check_mark: Définition de fonctions avec paramètres, et type de retour int, char ou void  
:heavy_check_mark: Vérification de la cohérence des appels de fonctions et leurs paramètres  
:heavy_check_mark: Structure de blocs grâce à { et }  
:heavy_check_mark: Support des portées de variables et du shadowing  
:heavy_check_mark: Les structures de contrôle if, else, while  
:heavy_check_mark: Support du return expression n’importe où  
:heavy_check_mark: Vérification qu’une variable utilisée dans une expression a été déclarée  
:heavy_check_mark: Vérification qu’une variable n’est pas déclarée plusieurs fois  
:heavy_check_mark: Vérification qu’une variable déclarée est utilisée au moins une fois  
:heavy_check_mark: Division et modulo  
:heavy_check_mark: Tableaux (à une dimension)  

## Features In Course Of Implementation
:pencil2: Types de données de base char(32bits) et int(32bits) [char doit passer à 8 bits]  
:pencil2: Reciblage vers plusieurs architectures : x86, MSP430, ARM [IR réalisé]  
:pencil2: Les chaînes de caractères représentées par des tableaux de char [pas d'affectation d'une chaine de charactère avec une string]  
:pencil2: Propagation de constantes simple  
:pencil2: Propagation de variables constantes (avec analyse du data-flow)  

:x: Opérateurs d’affectation +=, -= etc., d’incrémentation ++ et décrémentation --  
:x: Pointeurs  
:x: break et continue  
:x: switch...case  
:x: Les opérateurs logiques paresseux ||, &&  
:x: Propagation de constantes simple  
:x: Propagation de variables constantes (avec analyse du data-flow)  
:x: Les variables globales  
:x: Les autres structures de contrôle : for, do...while  
:x: Le support dans les moindres détails de tous les autres opérateurs arithmétiques et logiques : <=, >=, << et >> etc.  
:x: Les autres types de base comme les types de inttypes.h, les float, double  

## Source Files
- `ifcc.g4` contains the grammar in antlr4 format
- `main.cpp` contains the C++ code to call the antlr4-generated parser
  on the file name provided in the command line.
- `CodeGenVisitor.h` produces the actual assembly-language output

## Prerequisites
- Before building your  compiler, you should install  antlr using your
  distribution's  package manager,  or by  running the  provided shell
  script:   `cd  .. ; ./install-antlr.sh`. 
    
## Compilation informations
- `Makefile` contains  the actual build  logic.
  The  Makefile uses  3  variables (ANTLRJAR,  ANTLRINC and  ANTLRLIB)
  indicating the location of various parts of the Antlr suite. 
  You can (should)  change  those values to suit your installation, either
  by editing the  Makefile and/or on the command  line, as illustrated
  by the `*_runmake` scripts.
- `fedora_runmake.sh` is an example of such a script. it shows how
  makefile variables can be overriden from the command-line.

