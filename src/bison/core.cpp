#pragma once
#include <bison/core.h>

//Vector of pointers for garbage collection.
std::vector<stScript*>   _gc_ptrs_script;
std::vector<stTerminal*> _gc_ptrs_terminal;
std::vector<stProject*>  _gc_ptrs_project;

//Core Data Structures
//=======================================================================//
//  Initialization functions.
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



//Delta Undo/Redo - Command Pattern
//=======================================================================//


//Garbage Collection
//=======================================================================//
int bison_audit() {
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

    //TODO: Projects

    return 0;
}

int bison_end() {
    //Delete all projects.
    for(auto i=_gc_ptrs_project.begin();i!=_gc_ptrs_project.end();++i) delete *i;
    _gc_ptrs_project.clear();

    //Delete all terminals.
    for(auto i=_gc_ptrs_terminal.begin();i!=_gc_ptrs_terminal.end();++i) delete *i;
    _gc_ptrs_terminal.clear();

    //Delete all scripts.
    for(auto i=_gc_ptrs_script.begin();i!=_gc_ptrs_script.end();++i) delete *i;
    _gc_ptrs_script.clear();

    return 0;
}