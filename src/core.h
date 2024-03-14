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
    unsigned int    c_scripts; //Number of scripts in the scripts array.
};

struct st_project {
    unsigned int    id;
    char**          name;
    bool            active;
    st_terminal**   terminal;
    unsigned int    s_terminal; //Terminal array size.
    unsigned int    c_terminal; //Number of terminal in the scripts array.
};

//New structure functions.
st_script*   new_script  (int id, char** name, char** path, bool active);
st_terminal* new_terminal(int id, char** name, bool active);

//Add/Remove scripts to/from terminal functions.
int add_script_into_terminal (st_terminal* terminal, st_script* script);
int add_scripts_into_terminal(st_terminal* terminal, st_script* scripts[]);

st_script* remove_script_from_terminal (st_terminal* terminal, int id);

int delete_terminal(st_terminal* terminal, bool include_children = false);
int delete_script(st_script* script);

char** new_string(char* str);
int delete_string(char**);