#pragma once
//es = enum struct

//The following is mainly used for the command pattern and needs 
//to be manually filled out.
enum es_type {
    tNONE,
    string,
    config,
    script,
    terminal,
    project
};

enum es_func {
    fNONE,
    new_script,
    new_terminal,
    new_project,
    new_string,

    add_script_into_terminal,
    remove_script_from_terminal,

    add_terminal_into_project,
    remove_terminal_from_project,

    delete_script,
    delete_terminal,
    delete_project,
    delete_string
};