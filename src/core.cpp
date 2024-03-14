#pragma once
#include <core.h>

//New script initializer function.
st_script* new_script(int id, char** name, char** path, bool active) {
    st_script* o = new st_script();
    o->id = id;
    o->name = name;
    o->path = path;
    o->active = active;
    return o;
}

//New terminal initializer function.
st_terminal* new_terminal(int id, char** name, bool active) {
    st_terminal* o = new st_terminal();
    o->id = id;
    o->name = name;
    o->active = active;
    o->scripts = new st_script*[ARRAY_SIZE_DEFAULT];
    o->s_scripts = ARRAY_SIZE_DEFAULT;
    o->c_scripts = 0;
    return o;
}

//Used to create a new char array in the format we would need.
char** new_string(char* str)
{
    char** ptr = new char*[1];
    ptr[0] = new char[STRING_SIZE_MAX];
    strcpy(ptr[0], str);
    return ptr;
}

//Add/Remove scripts to/from terminal functions.
int add_script_into_terminal(st_terminal* terminal, st_script* script) {
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
    return 1;
}

//Delete a script from the terminal using the id of the script.
st_script* remove_script_from_terminal(st_terminal* terminal, int id) {
    if(terminal->c_scripts==0) return nullptr;

    //Search scripts until id can be found. 
    unsigned int i;
    bool found = false;
    for(i = 0; i < terminal->c_scripts; i++) {
        if(!terminal->scripts[i]) {
            if(terminal->scripts[i]->id == id) {
                found = true;
                break;
            }
        }
    }

    //Return if not found.
    if(!found) return nullptr;
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

int add_scripts_into_terminal(st_terminal* terminal, st_script* scripts[]);

//Delete a terminal and, optionally, all scripts under it.
int delete_terminal(st_terminal* terminal, bool include_strings) {
    delete_string(terminal->name);
    //Dekete scripts if set to do so.
    if(include_strings) {
        for(unsigned int i = 0; i < terminal->c_scripts; i++) {
            if(terminal->scripts[i] != nullptr) {
                delete_script(terminal->scripts[i]);
            }
        }
    }
    delete[] terminal->scripts;
    delete terminal;
    return 1;
}

//Deleting a script and it's contents.
int delete_script(st_script* script) {
    delete_string(script->name);
    delete_string(script->path);
    delete script;
    return 1;
}

//Deleting a char**.
int delete_string(char** string) {
    delete[] string[0];  // Delete the memory allocated for the string
    delete[] string;
    return 1;
}

