#include <iostream>
#include <cstring>
#include <cmath>
#include <chrono>
using namespace std;

struct String{
    char *cstr;
    unsigned len;
    unsigned len_true;
};

String new_string(){
    String tmp;
    tmp.len = 0;
    tmp.len_true = 0;
    tmp.cstr = new char[1];
    tmp.cstr[0] = '\0';
    return tmp;
}

String new_string(char const *cstr_out){
    if (cstr_out != NULL){
        String tmp;
        tmp.len = strlen(cstr_out);
        tmp.len_true = 2*tmp.len;
        tmp.cstr = new char[2*tmp.len + 1];
        for (unsigned i = 0; i < tmp.len + 1; i++){
            tmp.cstr[i] = cstr_out[i];
        }
        return tmp;
    }
    else{
        return new_string();
    }
}

String new_string(String const &src){
    String tmp;
    tmp.len = src.len;
    tmp.len_true = 2*src.len;
    tmp.cstr = new char[2*tmp.len + 1];
    for (unsigned i = 0; i < tmp.len + 1; i++){
        tmp.cstr[i] = src.cstr[i];
    }
    return tmp;
}

void delete_string(String &str){
    str.len = 0;
    str.len_true = 0;
    delete[] str.cstr;
}

unsigned length(String const &str){
    return str.len;
}

String& copy(String &dst, String const &src){
    dst.len = src.len;
    dst.len_true = 2*dst.len;
    delete[] dst.cstr;
    dst.cstr = new char[2*dst.len + 1];
    for (unsigned i = 0; i < dst.len + 1; i++){
        dst.cstr[i] = src.cstr[i];
    }
    return dst;
}

char get_char_at(String const &str, unsigned pos){
    if (pos <= str.len){
        return str.cstr[pos];
    }
    else{
        return '\0';
    }
}

String& set_char_at(String &str, unsigned pos, char c){
    if (pos < str.len){
        str.cstr[pos] = c;
        return str;
    }
    else{
        return str;
    }
}

String& append(String &dst, char const *cstr_out) {
    if (strlen(cstr_out) > dst.len_true - dst.len){
        char *str_new = new char[2 * (dst.len + strlen(cstr_out)) + 1];
        for (unsigned i = 0; i < dst.len; i++){
            str_new[i] = dst.cstr[i];
        }
        for(unsigned i = dst.len; i < dst.len + strlen(cstr_out) + 1; i++){
            str_new[i] = cstr_out[i - dst.len];
        }
        delete[] dst.cstr;
        dst.cstr = str_new;
        dst.len += strlen(cstr_out);
        dst.len_true = 2 * dst.len;
        return dst;
    }
    else{
        for(unsigned i = dst.len; i < dst.len + strlen(cstr_out) + 1; i++){
            dst.cstr[i] = cstr_out[i - dst.len];
        }
        dst.len += strlen(cstr_out);
    }
}

String& append(String &dst, String const &src){
    if (src.len > dst.len){
        char *str_new = new char[2*(dst.len + src.len) + 1];
        for (unsigned i = 0; i < dst.len; i++){
            str_new[i] = dst.cstr[i];
        }
        for(unsigned i = dst.len; i < dst.len + src.len + 1; i++){
            str_new[i] = src.cstr[i - dst.len];
        }
        delete[] dst.cstr;
        dst.cstr = str_new;
        dst.len += src.len;
        return dst;
    }
    else{
        for(unsigned i = dst.len; i < dst.len + src.len + 1; i++){
            dst.cstr[i] = src.cstr[i - dst.len];
        }
        dst.len += src.len;
    }
}

void print(String const &str){
    for(unsigned i = 0; i < str.len + 1; i++){
        cout << str.cstr[i];
    }
}

int main() {
    for (int j = 0; j < 25; j++){
        for (double i = 0; i <= 8; i += 0.5){
            int limiter = pow(10, i);
            String str = new_string();
            char arr[] = {'a'};
            auto start = std::chrono::steady_clock::now();
            for (int counter = 0; counter < limiter; counter++) {
                str = append(str, arr);
            }
            auto stop = std::chrono::steady_clock::now();
            auto duration = stop - start;
            cout << limiter << ' ' << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() << ' ';
            delete_string(str);
        }
        cout << endl;
    }
    return 0;
}
