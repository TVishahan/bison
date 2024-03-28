#include <ux/gui.h>
#include <bison/core.h>

int main(){
    stScript* s1 = new_script(1,"hello", "world", true);
    stScript* s2 = new_script(2,"hello", "world", true);
    stScript* s3 = new_script(3,"hello", "world", true);
    stScript* s4 = new_script(4,"hello", "world", true);
    stScript* s5 = new_script(5,"hello", "world", true);
    stScript* s6 = new_script(6,"hello", "world", true);
    stScript* s7 = new_script(7,"hello", "world", true);
    stTerminal* t1 = new_terminal(1,"hello world", TERM_CMD, true);
    stTerminal* t2 = new_terminal(2,"hello world", TERM_CMD, true);
    stProject* p1 = new_project(1,"Hello World");

    t1->Scripts.push_back(s2);
    p1->Terminals.push_back(t1);
    bison_audit();
    t1->Scripts.push_back(s2);
    
    std::cout <<  t1->Scripts.size() << std::endl;
    bison_end();
    return 0;
}