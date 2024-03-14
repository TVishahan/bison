#include <gui.h>
#include <core.h>
int main(){
    
    st_terminal* term = new_terminal(1, new_string("Hello Darkness My Old Friend"), true);
    printf(*term->name);
    delete_terminal(term, true);
    //start_gui();
    return 0;
}