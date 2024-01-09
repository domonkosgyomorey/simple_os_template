#include "libc/string.h"
#include "libc/stdlib.h"

void int_to_ascii(int n, char* cstr) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        cstr[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) cstr[i++] = '-';
    cstr[i] = '\0';

    str_reverse(cstr);
}

void str_reverse(char* cstr) {
    int c, i, j;
    for (i = 0, j = str_len(cstr)-1; i < j; i++, j--) {
        c = cstr[i];
        cstr[i] = cstr[j];
        cstr[j] = c;
    }
}

int str_len(const char* cstr) {
    int i = 0;
    while (cstr[i] != '\0') ++i;
    return i;
}

void str_append(char* cstr, const char n) {
    int len = str_len(cstr);
    cstr[len] = n;
    cstr[len+1] = '\0';
}

void str_backspace(char* cstr) {
    int len = str_len(cstr);
    if(len!=0){
        cstr[len-1] = '\0';
    }
}
int str_cmp(const char* cstr1, const char* cstr2) {
    int i;
    for (i = 0; cstr1[i] == cstr2[i]; i++) {
        if (cstr1[i] == '\0') return 0;
    }
    return cstr1[i] - cstr2[i];
}

int str_equ(const char* cstr1, const char* cstr2){
    int i = 0;
    while(cstr1[i]!='\0'&&cstr2[i]!='\0'&&cstr1[i]==cstr2[i]){
        ++i;
    }
    return cstr1[i]==cstr2[i];
}

int str_n_cmp(const char* cstr1, const char* cstr2, unsigned int n){
    unsigned int i;
    for (i = 0; i<n-1 && cstr1[i] == cstr2[i]; i++) {
        if (cstr1[i] == '\0') return 0;
    }
    return cstr1[i] - cstr2[i];
}

int str_n_equ(const char* cstr1, const char* cstr2, unsigned int n){
    unsigned int i = 0;
    while(i<n-1&&cstr1[i]!='\0'&&cstr2[i]!='\0'&&cstr1[i]==cstr2[i]){
        ++i;
    }
    return cstr1[i]==cstr2[i];
}

int str_count_c(const char* cstr, char c){
    int i=0;
    int cc=0;
    while(cstr[i]!='\0'){
        if(cstr[i]==c){
            ++cc;
        }
        ++i;
    }
    return cc;
}

void str_trim(char* cstr){
    int i = 0;
    while(cstr[i]!='\0'&&cstr[i]==' '){
        ++i;
    }
    int j = 0;
    while(cstr[i]!='\0'){
        cstr[j++] = cstr[i];
        ++i;
    }
    cstr[j] = cstr[i];
}

void str_cpy(const char* cstr1, char* cstr2){
    int i = 0;
    while(cstr1[i]!='\0'){
        cstr2[i]=cstr1[i];
        ++i;
    }
    cstr2[i]='\0';
}

void str_n_cpy(const char* cstr1, char* cstr2, unsigned int n){
    unsigned int i = 0;
    while(cstr1[i]!='\0'&&i<n-1){
        cstr2[i]=cstr1[i];
        ++i;
    }
    cstr2[i]='\0';
}

void str_cut_word(char* cstr1, char* cstr2){
    str_trim(cstr1);
    int i = 0;
    while(cstr1[i]!='\0'&&cstr1[i]!=' '){
        cstr2[i] = cstr1[i];
        ++i;
    }
    str_cpy(cstr1+i, cstr1);
    cstr2[i] = '\0';
}

void str_cut_word_n(char* cstr1, char* cstr2, unsigned int n){
    str_trim(cstr1);
    unsigned int i = 0;
    while(cstr1[i]!='\0'&&cstr1[i]!=' '&&i<n-1){
        cstr2[i] = cstr1[i];
        ++i;
    }
    str_cpy(cstr1+i, cstr1);
    cstr2[i] = '\0';
}