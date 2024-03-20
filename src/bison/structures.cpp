#pragma once
#include <bison/structures.h>


//Core Data Structures
//-------------------------------------------------------------------------
//  This holds structures for script project management and the terminals 
//  that they exist in.

//New script initializer function.
st_script* new_script(int id, std::string name, std::string path, bool active) {
    st_script* o = new st_script();
    o->id = id;
    o->name = name;
    o->path = path;
    o->active = active;
    return o;
}

//New terminal initializer function.
st_terminal* new_terminal(int id, std::string name, bool active) {
    st_terminal* o = new st_terminal();
    o->id = id;
    o->name = name;
    o->active = active;
    o->scripts = new st_script*[ARRAY_SIZE_DEFAULT];
    o->s_scripts = ARRAY_SIZE_DEFAULT;
    o->c_scripts = 0;
    return o;
}

//New project initializer function.
st_project* new_project(int id, std::string name) {
    st_project* o = new st_project();
    o->id = id;
    o->name = name;
    o->terminals = new st_terminal*[ARRAY_SIZE_DEFAULT];
    o->s_terminals = ARRAY_SIZE_DEFAULT;
    o->c_terminals = 0;
    return o;
}


//Add script to terminal.
bool add_script_into_terminal(st_terminal* terminal, st_script* script) {
    //Check if adding a script will require an array resize.
    if(terminal->c_scripts + 1 + ARRAY_SIZE_RANGE > terminal->s_scripts) {
        //Create new array with larger size.
        st_script** n_arr = new st_script*[terminal->s_scripts + ARRAY_SIZE_INCREMENT];
        //Move old array elements to new array. 
        for(unsigned int i = 0; i < terminal->c_scripts; i++) {
            n_arr[i] = terminal->scripts[i];
        }
        //Delete old array and add new, larger, array.
        delete[] terminal->scripts;
        terminal->scripts = n_arr;
        terminal->s_scripts = terminal->s_scripts + ARRAY_SIZE_INCREMENT;
    }
    //Add the new script to the array.
    terminal->scripts[terminal->c_scripts] = script;
    terminal->c_scripts++;

    //Return number of scripts added.
    return true;
}

//Add terminal to project, functionality mirrors add_script_into_terminal.
bool add_terminal_into_project(st_project* project, st_terminal* terminal) {
    //Check if adding a terminal will require an array resize.
    if(project->c_terminals + 1 + ARRAY_SIZE_RANGE > project->s_terminals) {
        //Create new array with larger size.
        st_terminal** n_arr = new st_terminal*[project->s_terminals + ARRAY_SIZE_INCREMENT];
        //Move old array elements to new array. 
        for(unsigned int i = 0; i < project->s_terminals; i++) {
            n_arr[i] = project->terminals[i];
        }
        //Delete old array and add new, larger, array.
        delete[] project->terminals;
        project->terminals = n_arr;
        project->s_terminals = project->s_terminals + ARRAY_SIZE_INCREMENT;
    }
    //Add the new terminal to the array.
    project->terminals[project->c_terminals] = terminal;
    project->c_terminals++;

    //Return number of terminal added.
    return true;
}

//Remove a script from the terminal using the id of the script.
st_script* remove_script_from_terminal(st_terminal* terminal, st_script* script) {
    if(terminal->c_scripts==0) return nullptr;

    //Search scripts until id can be found. 
    unsigned int i;
    bool found = false;
    for(i = 0; i < terminal->c_scripts; i++) {
        if(!terminal->scripts[i]) {
            if(terminal->scripts[i] == script) {
                found = true;
                break;
            }
        }
    }

    //Return if not found.
    if(!found) return nullptr;

    //Pop out the script.
    st_script* o = terminal->scripts[i];
    terminal->scripts[i] = nullptr;

    //Move the rest of the scripts up a slot.
    for(/* i = i */; i < terminal->c_scripts - 1; i++) {
        terminal->scripts[i] = terminal->scripts[i + 1];
    }
    //Reduce counter.
    terminal->c_scripts = terminal->c_scripts--;

    //Check if removing a script will require an array resize.
    if(terminal->c_scripts - 1 - ARRAY_SIZE_RANGE <= terminal->s_scripts && 
    terminal->c_scripts - 1 - ARRAY_SIZE_RANGE > ARRAY_SIZE_DEFAULT) {
        //Create new array.
        st_script** n_arr = new st_script*[terminal->s_scripts - ARRAY_SIZE_INCREMENT];
        //Move old array elements to new array. 
        for(i = 0; i < terminal->c_scripts; i++) {
            n_arr[i] = terminal->scripts[i];
        }
        //Delete old array and add new, smaller, array.
        delete[] terminal->scripts;
        terminal->scripts = n_arr;
        terminal->s_scripts = terminal->s_scripts - ARRAY_SIZE_INCREMENT;
    }

    //Return removed script for garbage collection later.
    return o;
}

//Remove a terminal from the project using the id of the terminal.
st_terminal* remove_terminal_from_project(st_project* project, st_terminal* terminal) {
    if(project->c_terminals==0) return nullptr;

    //Search terminals until id can be found. 
    unsigned int i;
    bool found = false;
    for(i = 0; i < project->c_terminals; i++) {
        if(!project->terminals[i]) {
            if(project->terminals[i] == terminal) {
                found = true;
                break;
            }
        }
    }

    //Return if not found.
    if(!found) return nullptr;

    //Pop out the terminal.
    st_terminal* o = project->terminals[i];
    project->terminals[i] = nullptr;

    //Move the rest of the terminals up a slot.
    for(/* i = i */; i < project->c_terminals - 1; i++) {
        project->terminals[i] = project->terminals[i + 1];
    }
    //Reduce counter.
    project->c_terminals = project->c_terminals--;

    //Check if removing a terminal will require an array resize.
    if(project->c_terminals - 1 - ARRAY_SIZE_RANGE <= project->s_terminals && 
    project->c_terminals - 1 - ARRAY_SIZE_RANGE > ARRAY_SIZE_DEFAULT) {
        //Create new array.
        st_terminal** n_arr = new st_terminal*[project->s_terminals - ARRAY_SIZE_INCREMENT];
        //Move old array elements to new array. 
        for(i = 0; i < project->c_terminals; i++) {
            n_arr[i] = project->terminals[i];
        }
        //Delete old array and add new, smaller, array.
        delete[] project->terminals;
        project->terminals = n_arr;
        project->s_terminals = project->s_terminals - ARRAY_SIZE_INCREMENT;
    }

    //Return removed script for garbage collection later.
    return o;
}

//Shift a script in a terminal.
bool shift_script_in_terminal(st_terminal* terminal, st_script* script, int direction) {
    if(terminal->c_scripts==0) return false;
    
    //Search scripts until id can be found. 
    unsigned int i;
    bool found = false;
    for(i = 0; i < terminal->c_scripts; i++) {
        if(!terminal->scripts[i]) {
            if(terminal->scripts[i] == script) {
                found = true;
                break;
            }
        }
    }

    //Return if not found.
    if(!found) return false;

    //Return if out of bounds.
    if(0 >= i + direction && i + direction > terminal->c_scripts - 1) return false;
    
    //Swap the script with the one in the direction.
    st_script* temp = terminal->scripts[i];
    terminal->scripts[i] = terminal->scripts[i + direction];
    terminal->scripts[i + direction] = temp;

    return true;
}

//Shift a terminal in a project.
bool shift_terminal_in_project(st_project* project, st_terminal* terminal, int direction) {
    if(terminal->c_scripts==0) return false;
    
    //Search scripts until id can be found. 
    unsigned int i;
    bool found = false;
    for(i = 0; i < project->c_terminals; i++) {
        if(!project->terminals[i]) {
            if(project->terminals[i] == terminal) {
                found = true;
                break;
            }
        }
    }

    //Return if not found.
    if(!found) return false;

    //Return if out of bounds.
    if(0 >= i + direction && i + direction > terminal->c_scripts - 1) return false;
    
    //Swap the script with the one in the direction.
    st_terminal* temp = project->terminals[i];
    project->terminals[i] = project->terminals[i + direction];
    project->terminals[i + direction] = temp;

    return true;
}

//Deleting a script and it's contents.
bool delete_script(st_script* script) {
    delete script;
    return true;
}

//Delete a terminal and, optionally, all scripts under it.
bool delete_terminal(st_terminal* terminal, bool include_children) {
    //Dekete scripts if set to do so.
    if(include_children) {
        for(unsigned int i = 0; i < terminal->c_scripts; i++) {
            if(terminal->scripts[i] != nullptr) {
                delete_script(terminal->scripts[i]);
            }
        }
    }
    delete[] terminal->scripts;
    delete terminal;
    return true;
}

//Delete a terminal and, optionally, all scripts under it.
bool delete_project(st_project* project, bool include_children) {
    //Dekete scripts if set to do so.
    if(include_children) {
        for(unsigned int i = 0; i < project->c_terminals; i++) {
            if(project->terminals[i] != nullptr) {
                delete_terminal(project->terminals[i], include_children);
            }
        }
    }
    delete[] project->terminals;
    delete project;
    return true;
}


//-------------------------------------------------------------------------

//Delta Undo/Redo - Command Patern
//-------------------------------------------------------------------------
//  Each command has a function it would use to go forward and a function
//  it would use to go backwards. Essentially making undos and redos delta
//  based and not state based.

//Create a new command buffer.
st_cmdbuffer* new_cmdbuffer() {
    st_cmdbuffer* o = new st_cmdbuffer;
    o->s_buffer_forwards  = COMMAND_BUFFER_SIZE;
    o->s_buffer_backwards = COMMAND_BUFFER_SIZE;
    return o;
}

//Create a new command with optional data supplied.
st_command* new_command(es_func cf, es_func cb, 
    void* d1p, es_type d1t, void* d2p, es_type d2t, void* d3p, es_type d3t) {
    st_command* o = new st_command;
    o->cmd_forwards = cf;
    o->cmd_backwards = cb;
    o->d1_ptr = d1p;
    o->d1_type = d1t;
    o->d2_ptr = d2p;
    o->d2_type = d2t;
    o->d3_ptr = d3p;
    o->d3_type = d3t;
    return o;
}

//Delete a command buffer.
bool delete_cmdbuffer(st_cmdbuffer* buffer) {

    return true;
}

//Execute a command from the command buffer.
bool execute_command(st_command* command, int direction) {

    return true;
}

//-------------------------------------------------------------------------