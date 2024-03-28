#include <ux/gui.h>
#include <bison/core.h>

int main(){
    stScript*   s1 = new_script  (make_id(ST_TYPE_SCRIPT),"hello", "world", true);
    stScript*   s2 = new_script  (make_id(ST_TYPE_SCRIPT),"hello", "world", true);
    stScript*   s3 = new_script  (make_id(ST_TYPE_SCRIPT),"hello", "world", true);
    stScript*   s4 = new_script  (make_id(ST_TYPE_SCRIPT),"hello", "world", true);
    stScript*   s5 = new_script  (make_id(ST_TYPE_SCRIPT),"hello", "world", true);
    stScript*   s6 = new_script  (make_id(ST_TYPE_SCRIPT),"hello", "world", true);
    stScript*   s7 = new_script  (make_id(ST_TYPE_SCRIPT),"hello", "world", true);
    stTerminal* t1 = new_terminal(make_id(ST_TYPE_TERMINAL),"hello world", TERM_CMD, true);
    stTerminal* t2 = new_terminal(make_id(ST_TYPE_TERMINAL),"hello world", TERM_CMD, true);
    stProject*  p1 = new_project (make_id(ST_TYPE_TERMINAL),"Hello World");

    t1->Scripts.push_back(s2);
    p1->Terminals.push_back(t1);
    
    std::cout << s1->Id << std::endl;
    std::cout << s2->Id << std::endl;
    std::cout << s3->Id << std::endl;
    std::cout << s4->Id << std::endl;
    std::cout << s5->Id << std::endl;
    std::cout << s6->Id << std::endl;
    std::cout << s7->Id << std::endl;
    std::cout << t1->Id << std::endl;
    std::cout << t2->Id << std::endl;
    std::cout << p1->Id << std::endl;
    
    bison_end();
    return 0;
}