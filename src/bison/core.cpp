#pragma once
#include <bison/core.h>

//Vector of pointers for garbage collection.
std::vector<stScript*>   _gc_ptrs_script;
std::vector<stTerminal*> _gc_ptrs_terminal;
std::vector<stProject*>  _gc_ptrs_project;



//Core Data Structures
//=======================================================================//

//  Initialization functions
//  -------------------------------------------------------------------  //
stScript* new_script(unsigned int Id, std::string Name, std::string Path, bool Active) {
    stScript* o = new stScript;
    o->Id = Id;
    o->Name = Name;
    o->Path = Path;
    o->Active = Active;
    _gc_ptrs_script.push_back(o);
    return o;
}

stTerminal* new_terminal(unsigned int Id, std::string Name, enTermApp App, bool Active) {
    stTerminal* o = new stTerminal;
    o->Id = Id;
    o->Name = Name;
    o->Active = Active;
    _gc_ptrs_terminal.push_back(o);
    return o;
}

stProject* new_project(unsigned int Id, std::string Name) {
    stProject* o = new stProject;
    o->Id = Id;
    o->Name = Name;
    _gc_ptrs_project.push_back(o);
    return o;
}

//  stTerminal functions
//  -------------------------------------------------------------------  //

//Find the index of a script.
int stTerminal::find_script(stScript* script) {
    auto i=find(this->Scripts.begin(),this->Scripts.end(), script);
    if(i==this->Scripts.end()) return -1;
    return i-this->Scripts.end();
}

//Find a script by index.
stScript* stTerminal::find_script(int id) {
    return this->Scripts[id];
}

//Add a script to the back or at position. 
bool stTerminal::add_script(int at=-1) {

}

//Remove a script by value, returns the script.
stScript* stTerminal::remove_script(stScript* script) {

}

//Remove the script at index, returns the script.
stScript* stTerminal::remove_script(int at) {

}

//Move a script from index to index.
bool stTerminal::move_script(int fr, int to) {

}


//  stTerminal functions.
//  -------------------------------------------------------------------  //

//Find the index of a terminal.
int stProject::find_terminal(stTerminal* terminal) {
    auto i=find(this->Terminals.begin(),this->Terminals.end(), terminal);
    if(i==this->Terminals.end()) return -1;
    return i-this->Terminals.end();
}

//Find the terminal by index.
stTerminal* stProject::find_terminal(int id) {
    return this->Terminals[id];
}

//Add a terminal to the back or at position.
bool stProject::add_terminal(int at=-1) {

}
stTerminal* stProject::remove_terminal(stTerminal* terminal) {

}

stTerminal* stProject::remove_terminal(int at) {

}

bool stProject::move_terminal(int fr, int to) {

}


//Make a random id based on type.
unsigned int make_id(enStType type) {
    unsigned int o = 0;

    //Loop while id is not valid.
    bool valid = false;
    while(!valid) {
        //Assign random id.
        o = std::rand() * RAND_MAX;

        //Depending on type, search GC cache to find any existing instance of
        //the created id.
        bool found=false;
        switch(type) {
            case ST_TYPE_SCRIPT:
                //Search scripts for id and if none matching found, it's valid.
                if(_gc_ptrs_script.size()>0){
                    for(auto i=_gc_ptrs_script.begin();i!=_gc_ptrs_script.end();++i) {
                        if((*i)->Id==o) found=true;
                    }
                }
                if(!found)valid=true;
                break;

            case ST_TYPE_TERMINAL:
                //Search scripts for id and if none matching found, it's valid.
                if(_gc_ptrs_terminal.size()>0){
                    for(auto i=_gc_ptrs_terminal.begin();i!=_gc_ptrs_terminal.end();++i) {
                        if((*i)->Id==o) found=true;
                    }
                }
                if(!found)valid=true;
                break;

            case ST_TYPE_PROJECT:
                //Search scripts for id and if none matching found, it's valid.
                if(_gc_ptrs_project.size()>0){
                    for(auto i=_gc_ptrs_project.begin();i!=_gc_ptrs_project.end();++i) {
                        if((*i)->Id==o) found=true;
                    }
                }
                if(!found)valid=true;
                break;

            default:
                valid = true;
        }
    }
    return o;
}

//Delta Undo/Redo - Command Pattern
//=======================================================================//



//Garbage Collection
//=======================================================================//
void bison_audit() {
    //Remove if terminal not referenced anywhere.
    if(_gc_ptrs_terminal.size()>0){
        _gc_ptrs_terminal.erase(
            std::remove_if(_gc_ptrs_terminal.begin(),_gc_ptrs_terminal.end(), 
            [](const stTerminal*  o) {
                bool found=false;
                //Search for any references in the projects.
                for(auto i=_gc_ptrs_project.begin();i!=_gc_ptrs_project.end();++i) {
                    //Search terminals within projects to find a match.
                    for(auto j=(*i)->Terminals.begin();j!=(*i)->Terminals.end();++j) {
                        //Stop if found and unroll loop.
                        if(*j==o)found=true;
                        if(found)break;
                    }
                    if(found)break;
                }

                //TODO: Search Undo/Redo cache for any references.

                //If not found delete the pointer.
                if(!found) delete o;

                return !found;
            }), _gc_ptrs_terminal.end()
        );
    }

    //Remove if script not referenced anywhere.
    if(_gc_ptrs_script.size()>0) {
        _gc_ptrs_script.erase(
            std::remove_if(_gc_ptrs_script.begin(),_gc_ptrs_script.end(), 
            [](const stScript*  o) {
                bool found=false;
                //Search for any references in the terminals.
                for(auto i=_gc_ptrs_terminal.begin();i!=_gc_ptrs_terminal.end();++i) {
                    //Search scripts within terminals to find a match.
                    for(auto j=(*i)->Scripts.begin();j!=(*i)->Scripts.end();++j) {
                        //Stop if found and unroll loop.
                        if(*j==o)found=true;
                        if(found)break;
                    }
                    if(found)break;
                }

                //TODO: Search Undo/Redo cache for any references.

                //If not found delete the pointer.
                if(!found) delete o;

                return !found;
            }),  _gc_ptrs_script.end()
        );
    }

    return;
}

void bison_end() {
    //Delete all projects.
    for(auto i=_gc_ptrs_project.begin();i!=_gc_ptrs_project.end();++i) delete *i;
    _gc_ptrs_project.clear();

    //Delete all terminals.
    for(auto i=_gc_ptrs_terminal.begin();i!=_gc_ptrs_terminal.end();++i) delete *i;
    _gc_ptrs_terminal.clear();

    //Delete all scripts.
    for(auto i=_gc_ptrs_script.begin();i!=_gc_ptrs_script.end();++i) delete *i;
    _gc_ptrs_script.clear();

    return;
}


