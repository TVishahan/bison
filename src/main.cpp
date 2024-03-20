#include <ux/gui.h>
#include <bison/structures.h>

int main(){
    
    st_terminal* term = new_terminal(1, "Hello darkness my old friend", true);
    printf(term->name.c_str());
    add_script_into_terminal(term, new_script( 1, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script( 2, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script( 3, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script( 4, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script( 5, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script( 6, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script( 7, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script( 8, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script( 9, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script(10, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script(11, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script(12, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script(13, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script(14, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script(15, "Hello Script", "Blues clues", true));
    add_script_into_terminal(term, new_script(16, "Hello Script", "Blues clues", true));

    printf("%d\n", term->s_scripts);
    st_project* proj = new_project(1, "Hello Project");
    add_terminal_into_project(proj,term);


    delete_project(proj, true);
    auto func = add_script_into_terminal;
    
    //start_gui();
    return 0;
}