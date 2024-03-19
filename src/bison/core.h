#pragma once
#include <bison/enumerators.h>
#include <bison/structures.h>
#include <stack>


//Command Pattern - For undo and redo support.
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