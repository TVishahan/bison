#pragma once

#include <nlohmann/json.hpp>
#include <bison/enumerators.h>

#include <stdlib.h>
#include <stack>
#include <vector>



//Core Data Structures
//=======================================================================//
//  This holds structures for script project management and the terminals 
//  that they exist in.

//  Structure initialization
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

    //Script management functions.
    int         find_script(stScript* script);
    stScript*   find_script(int id);
    bool        add_script(stScript* script, int at=-1);
    stScript*   remove_script(int at);
    bool        move_script(int fr, int to);
};

//Project will also hold pointers to Scripts and Terminals for GC.
struct stProject {
    unsigned int Id;
    std::string Name;
    std::vector<stTerminal*> Terminals;

    //Terminal management functions.
    int         find_terminal(stTerminal* terminal);
    stTerminal* find_terminal(int id);
    bool        add_terminal(stTerminal* terminal, int at=-1);
    stTerminal* remove_terminal(int at);
    bool        move_terminal(int fr, int to);
};


//  Functions
//  -------------------------------------------------------------------  //

//  Initialization functions.
stScript*   new_script(unsigned int Id, std::string Name, std::string Path, bool Active=true);
stTerminal* new_terminal(unsigned int Id, std::string Name, enTermApp App, bool Active=true);
stProject*  new_project(unsigned int Id, std::string Name);

//  Create random ID that hasn't been init (By searching through the vector).
unsigned int make_id(enStType type = ST_TYPE_NONE);



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
void bison_audit();

//Delete all pointers at the end of the program.
void bison_end();