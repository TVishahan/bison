#pragma once

#include <nlohmann/json.hpp>

#define ARRAY_SIZE_DEFAULT      10
#define ARRAY_SIZE_INCREMENT    10
#define ARRAY_SIZE_RANGE        3
#define STRING_SIZE_MAX         512


struct st_config {
    unsigned int    id;
    char**          path_scripts;
};

struct st_script {
    unsigned int    id;
    char**          name;
    bool            active;
    char**          path;
};

struct st_terminal {
    unsigned int    id;
    char**          name;
    bool            active;
    st_script**     scripts;
    unsigned int    s_scripts; //Scripts array size.
    unsigned int    c_scripts; //Number of scripts in the array.
};

struct st_project {
    unsigned int    id;
    char**          name;
    st_terminal**   terminals;
    unsigned int    s_terminals; //Terminal array size.
    unsigned int    c_terminals; //Number of terminals in the array.
};

//New structure functions.
st_script*   new_script   (int id, char** name, char** path, bool active);
st_terminal* new_terminal (int id, char** name, bool active);
st_project*  new_project  (int id, char** name);
char**       new_string   (char* str);

//Add/Remove scripts to/from a terminal.
int         add_script_into_terminal    (st_terminal* terminal, st_script* script);
st_script*  remove_script_from_terminal (st_terminal* terminal, int id);

//Add/Remove terminals to/from a project.
int          add_terminal_into_project    (st_project* project, st_terminal* terminal);
st_terminal* remove_terminal_from_project (st_project* project, int id);

//Delete GC functions.
int delete_script   (st_script* script);
int delete_terminal (st_terminal* terminal, bool include_children = false);
int delete_project  (st_project* project, bool include_children = false);
int delete_string   (char** string);