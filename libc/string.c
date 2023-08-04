#include "string.h"
#include "stdlib.h"

void int_to_ascii(int n, char* cstr) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        cstr[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) cstr[i++] = '-';
    cstr[i] = '\0';

    reverse(cstr);
}

void reverse(char* cstr) {
    int c, i, j;
    for (i = 0, j = strlen(cstr)-1; i < j; i++, j--) {
        c = cstr[i];
        cstr[i] = cstr[j];
        cstr[j] = c;
    }
}

int strlen(const char* cstr) {
    int i = 0;
    while (cstr[i] != '\0') ++i;
    return i;
}

void append(char* cstr, const char n) {
    int len = strlen(cstr);
    cstr[len] = n;
    cstr[len+1] = '\0';
}

void backspace(char* cstr) {
    int len = strlen(cstr);
    cstr[len-1] = '\0';
}

int strcmp(const char* cstr1, const char* cstr2) {
    int i;
    for (i = 0; cstr1[i] == cstr2[i]; i++) {
        if (cstr1[i] == '\0') return 0;
    }
    return cstr1[i] - cstr2[i];
}

int strequ(const char* cstr1, const char* cstr2){
    int i = 0;
    while(cstr1[i]!='\0'&&cstr2[i]!='\0'&&cstr1[i]==cstr2[i]){
        ++i;
    }
    return cstr1[i]==cstr2[i];
}

int strncmp(const char* cstr1, const char* cstr2, int n){
    if(n<1)return 0;
    int i;
    for (i = 0; i<n-1 && cstr1[i] == cstr2[i]; i++) {
        if (cstr1[i] == '\0') return 0;
    }
    return cstr1[i] - cstr2[i];
}

int strnequ(const char* cstr1, const char* cstr2, int n){
    if(n<1)return 0;
    int i = 0;
    while(i<n-1&&cstr1[i]!='\0'&&cstr2[i]!='\0'&&cstr1[i]==cstr2[i]){
        ++i;
    }
    return cstr1[i]==cstr2[i];
}

int strcountc(const char* cstr, char c){
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

void strtrim(char* cstr){
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