#pragma once

#include <nlohmann/json.hpp>
#include <bison/enumerators.h>

#include <stdlib.h>
#include <stack>
#include <vector>
#include <typeindex>

//Core Data Structures
//=======================================================================//
//  This holds structures for script project management and the terminals 
//  that they exist in.

//  Structure initialization.
//  -------------------------------------------------------------------  //
struct stScript {
    unsigned int Id;
    std::string Name;
    std::string Path;
    bool Active;
};

struct stTerminal {
    unsigned int Id;
    std::string Name;
    enTermApp App;
    std::vector<stScript*> Scripts; 
    bool Active;
};

//Project will also hold pointers to Scripts and Terminals for GC.
struct stProject {
    unsigned int Id;
    std::string Name;
    std::vector<stScript*> Scripts;
    std::vector<stTerminal*> Terminals;
};


//  Functions
//  -------------------------------------------------------------------  //

//  Initialization functions.
stScript* new_script(unsigned int Id, std::string Name, std::string Path, bool Active=true);
stTerminal* new_terminal(unsigned int Id, std::string Name, enTermApp App, bool Active=true);
stProject* new_project (unsigned int Id, std::string Name);


//Delta Undo/Redo - Command Pattern
//=======================================================================//
//  Each command has a function it would use to go forward and a function
//  it would use to go backwards. Essentially making undos and redos delta
//  based and not state based.

//Garbage Collection
//=======================================================================//
//  A few funcions to be called during and at the end of the program to
//  free up dynamically allocated memory.

//To be run sparringly to make check if there are any dereferenced 
//instances and delete them. 
int bison_audit();

//Delete all pointers at the end of the program.
int bison_end();