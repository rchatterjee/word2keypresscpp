//
// Created by rahul on 3/20/17.
//

#ifndef KEYBOARD_KEYBOARD_H
#define KEYBOARD_KEYBOARD_H

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>

#define CAPS 1
#define SHIFT 2

typedef struct key {
    int8_t row=-1, col=-1, sh=-1;  // Row, column, and shift state
    char ch=0; // The char that it will produce
} Key;

//class Key {
//private:
//    int8_t shift_state = -1; // shifted or not
//    int8_t row = -1; // Row index
//    int8_t col = -1; // column index
//    char ch = 0;  // actual char representation of char
//    char ch_key = 0;  // the character printed on the keyboard
//public:
//    Key(int8_t s, int8_t r, int8_t c, char _ch=0, char _ch_key=0):
//            shift_state(s), row(r), col(c), ch(_ch), ch_key(_ch_key){}
//    Key(char _ch=0): ch(_ch){}
//    int8_t get_row(){ return row;}
//    int8_t get_col(){ return col;}
//    char get_char() { return ch; }
//    void set_key(Key k);
//    void set_char(char _ch){ ch = _ch;}
//    char remove_shift(char);
//    char add_shift(char);
//
//    bool is_valid() {
//        return (((shift_state>=0) && (row>=0) && (col>=0)) || (ch>0));
//    }
//    std::string locstr() {
//        std::ostringstream ss;
//        ss << "(" << (int)row << ", " << (int)col << ", "
//           << (int)shift_state << ", " << ch << ")";
//        // snprintf(out, 12, "(%2d,%2d,%d,%c)", row, col, shift_state, ch);
//        // return out;
//        return ss.str();
//    }
//    std::string str(bool raw = false) {
//        std::ostringstream ss;
//        if (ch == CAPS){
//            if (raw) ss << CAPS;
//            else ss << "<c>";
//        } else {
//            if (shift_state>0) {
//                if (raw) ss << SHIFT;
//                else ss << "<s" << (int)shift_state << ">";
//            }
//            ss << ch_key;
//        }
//        return ss.str();
//    }
//
//    bool is_shifted() {
//        return (shift_state > 0);
//    };
//};


class Keyboard {
private:
    static const uint8_t _num_kb_rows = 4;
    static const uint8_t _num_shifts = 2;
    const char* _keys[_num_shifts][_num_kb_rows] = {{
            "`1234567890-=",
            " qwertyuiop[]\\",
            " asdfghjkl;'  ",
            " zxcvbnm,./   "
    }, {
            "~!@#$%^&*()_+",
            " QWERTYUIOP{}|",
            " ASDFGHJKL:\"  ",
            " ZXCVBNM<>?    "
    }};
    bool _is_initialized = false;
    std::string type = "US";
    Key keymap[128];  // char to its key version
    bool _keymap_initialized = false;
    // Does not check the bounds, make sure they are valid
    char char_at(int8_t sh, int8_t r, int8_t c){
        return _keys[sh][r][c];
    }
    bool is_valid(Key& key);
public:
    Keyboard(const std::string& _type = "US");
    // Keyboard() { printf("--> start: %d\n", _is_initialized); Keyboard("US");}
    Key char2key(char);
    char key2char(Key&);
    void unshift(Key&);
    void addshift(Key&);
};

class Keypress {
    Keyboard kb;
    std::vector<Key> keys;
    std::string word;
public:
    Keypress(Keyboard _kb): kb(_kb){}
    std::vector<Key> get_keypress(std::string word);
    std::string get_word();
    std::string str();
};
#endif //KEYBOARD_KEYBOARD_H
