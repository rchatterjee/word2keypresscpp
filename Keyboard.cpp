/*
 * Created by rahul on 3/20/17.
 *
 * A module for converting word into keypress sequence,
 * and vice verse. Also, gives possible distance function,
 * and ways to compute all possible edit-1 typos.
 *
 * Unfortunately now, it only supports "qwerty" US keyboard.
 */


#include "Keyboard.h"
#include <string.h>
#include <vector>


/*
 * If the char written with shift, returns the without
 * shift, otherwise returns the character.
 */
Key Keyboard::char2key(char c) {
    // printf("c=%c (%d), %d\n", c, c, _is_initialized);
    if (c>128 || c<0) return Key();
    return keymap[c];
}

bool Keyboard::is_valid(Key& k) {
    if (k.sh < 0 || k.sh >= _num_shifts) return false;
    if (k.row < 0 || k.row >= _num_kb_rows) return false;
    return !(k.col < 0 || k.col >= strlen(_keys[k.sh][k.row]));
}
/*
 * Converts a key into it's char format
 */
char Keyboard::key2char(Key& k) {
    if (k.ch > 0)
        return k.ch;
    char ch = 0;
    if (!is_valid(k))
        return (char)0;
    return _keys[k.sh][k.row][k.col];
}

Keyboard::Keyboard(const std::string& _type) {
    type = _type;
    _is_initialized = true;
    for (int8_t sh = 0; sh < _num_shifts; sh++) {
        for (int8_t r = 0; r < _num_kb_rows; r++) {
            const char *key_row = _keys[sh][r];
            for (int8_t c = 0; c < strlen(key_row); c++) {
                keymap[key_row[c]] = {r, c, sh, key_row[c]};
            }
        }
    }
}

void Keyboard::addshift(Key& k) {
    if (k.is_shifted()){
        k.get_char();
    }
}

std::vector<Key> Keypress::get_keypress(std::string _word) {
    word = _word;
    keys.resize(word.size());
    for(int i=0; i<word.size(); i++)
        keys[i] = kb.char2key(word[i]);
    int s, e;
    s = e = 0;
    while (e < keys.size()) {
        while (s < keys.size() && !isupper(keys[s].get_char())) {
            s++;
        }
        e = s; if (s>0) s--;
        while (e < keys.size() && !islower(keys[e].get_char())) e++;
        if ((e-s)>2) {
            printf("Going to insert: %d, %d\n", s, e);
            keys.insert(keys.begin() + s, Key((char)CAPS));
            keys.insert(keys.begin() + e-1, Key((char)CAPS));
            s = e;
        }
    }
    return keys;
}

std::string Keypress::str() {
    std::ostringstream oss;
    for(auto s = keys.begin(); s != keys.end(); s++) {
        if (s->get_char()>20) {
            oss << s->str();
        } else {
            oss << (s->get_char() == CAPS?"<c>":"<s>");
        }
    }
    return oss.str();
}

//std::ostreambuf_iterator& operator<<(std::ostream& os, Key& k) {
//    char out[13];
//    snprintf(out, 12, "(%2d,%2d,%d,%c)",
//             k.get_row(), k.get_col(), k.is_shifted(), k.get_char());
//    return os << std::string(out);
//}

char Key::add_shift(char ch) {
    return 0;
}

char Key::remove_shift(char) {
    return 0;
}

