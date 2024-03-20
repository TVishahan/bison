#pragma once

#include <nlohmann/json.hpp>
#include <bison/enumerators.h>
#include <stack>
#include <string>

#define ARRAY_SIZE_DEFAULT      10
#define ARRAY_SIZE_INCREMENT    10
#define ARRAY_SIZE_RANGE        3
#define STRING_SIZE_MAX         512


//Core Data Structures
//-------------------------------------------------------------------------
//  This holds structures for script project management and the terminals 
//  that they exist in.
struct st_config {
    unsigned int    id;
    std::string     path_scripts;
};

struct st_script {
    unsigned int    id;
    std::string     name;
    bool            active;
    std::string     path;
};

struct st_terminal {
    unsigned int    id;
    std::string     name;
    bool            active;
    st_script**     scripts;
    unsigned int    s_scripts; //Scripts array size.
    unsigned int    c_scripts; //Number of scripts in the array.
};

struct st_project {
    unsigned int    id;
    std::string     name;
    st_terminal**   terminals;
    unsigned int    s_terminals; //Terminal array size.
    unsigned int    c_terminals; //Number of terminals in the array.
};

//New structure functions.
st_script*   new_script   (int id, std::string name, std::string path, bool active);
st_terminal* new_terminal (int id, std::string name, bool active);
st_project*  new_project  (int id, std::string name);

//Add/Remove/shift scripts to/from/in a terminal.
bool         add_script_into_terminal    (st_terminal* terminal, st_script* script);
st_script*   remove_script_from_terminal (st_terminal* terminal, st_script* script);
st_script*   find_script_id_in_terminal  (st_terminal* terminal, int id);
bool         shift_script_in_terminal    (st_terminal* terminal, st_script* script, int direction);

//Add/Remove/shift terminals to/from/in a project.
bool         add_terminal_into_project    (st_project* project, st_terminal* terminal);
st_terminal* remove_terminal_from_project (st_project* project, st_terminal* terminal);
st_terminal* find_terminal_id_in_project  (st_project* project, int id);
bool         shift_terminal_in_project    (st_project* project, st_terminal* terminal, int direction);

//Delete GC functions.
bool delete_script   (st_script* script);
bool delete_terminal (st_terminal* terminal, bool include_children = false);
bool delete_project  (st_project* project, bool include_children = false);
//-------------------------------------------------------------------------


//Delta Undo/Redo - Command Patern
//-------------------------------------------------------------------------
//  Each command has a function it would use to go forward and a function
//  it would use to go backwards. Essentially making undos and redos delta
//  based and not state based.

//The size of each buffer.
#define COMMAND_BUFFER_SIZE 15

//Command structure holds an identifier to go forwards/redo and one to 
//undo. This also has three data pointers and their types to pass over to
//the command runner. Not all data needs to be used.
struct st_command {
    es_func cmd_forwards;
    es_func cmd_backwards;

    void*   d1_ptr;
    es_type d1_type;

    void*   d2_ptr;
    es_type d2_type;

    void*   d3_ptr;
    es_type d3_type;
};

//Command buffer, holds two stacks, one for redo, and one for undo and it's 
//size forwards buffer should be purged when a new action is made.
struct st_cmdbuffer {
    int s_buffer_forwards;
    std::stack<st_command*> buffer_forwards;

    int s_buffer_backwards;
    std::stack<st_command*> buffer_backwards;
};

//Create a new command buffer.
st_cmdbuffer* new_cmdbuffer();

//Create a new command with optional data supplied.
st_command* new_command(
    es_func cmd_forward, es_func cmd_backward,
    void* d1_ptr = nullptr, es_type d1_type = es_type::tNONE,
    void* d2_ptr = nullptr, es_type d2_type = es_type::tNONE,
    void* d3_ptr = nullptr, es_type d3_type = es_type::tNONE);

//Delete a command buffer.
bool delete_cmdbuffer(st_cmdbuffer* buffer);

//Delete a command.
bool delete_command(st_command* command);

//Step through the command buffer.
st_command* step_command(int direction);

//Execute command based on the function type.
bool execute_command(st_command* command, int direction);

//-------------------------------------------------------------------------