#pragma once
//es = enum struct

//The following is mainly used for the command pattern and needs 
//to be manually filled out.
enum es_type {
    tNONE,
    tstring,
    tconfig,
    tscript,
    tterminal,
    tproject
};

enum es_func {
    fNONE,
    fnew_script,
    fnew_terminal,
    fnew_project,
    fnew_string,

    fadd_script_into_terminal,
    fremove_script_from_terminal,

    fadd_terminal_into_project,
    fremove_terminal_from_project,

    fdelete_script,
    fdelete_terminal,
    fdelete_project,
    fdelete_string
};