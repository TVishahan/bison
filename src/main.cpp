#include <ux/gui.h>
#include <bison/structures.h>

int main(){
    
    st_terminal* term = new_terminal(1, new_string("Hello Darkness My Old Friend "), true);
    printf(*term->name);
    add_script_into_terminal(term, new_script( 1, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script( 2, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script( 3, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script( 4, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script( 5, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script( 6, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script( 7, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script( 8, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script( 9, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script(10, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script(11, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script(12, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script(13, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script(14, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script(15, new_string("Hello Script"), new_string("Blues clues"), true));
    add_script_into_terminal(term, new_script(16, new_string("Hello Script"), new_string("Blues clues"), true));

    printf("%d\n", term->s_scripts);
    st_project* proj = new_project(1, new_string("Hello Project"));
    add_terminal_into_project(proj,term);


    delete_project(proj, true);
    auto func = add_script_into_terminal;
    
    //start_gui();
    return 0;
}