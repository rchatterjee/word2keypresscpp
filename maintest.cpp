#include<iostream>
// #include<cstring>
// #include<cstdlib>
#include "Keyboard.h"

std::string word2keyseq(std::string word) {
    bool caps_state = false;
    int sh_s=0, sh_e=0;
    std::string keyseq = "";
    for(int i=0; i<word.length(); i++) {
        
    }
}
    
int main() {
    std::string s = "ASSHole";
    Keyboard kb = Keyboard("US");
    Keypress kp(kb);
    kp.get_keypress(s);
    std::cout << s << " --> " << kp.str() << std::endl;
//    Key k = kb.char2key(ch);
//    std::cout << ch << " --> ";
//    std::cout << k.str()
//              << " --> " << kb.key2char(k) << std::endl;
    return 0;
}
