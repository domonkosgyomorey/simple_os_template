#include "string.h"
#include "stdlib.h"

void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int strlen(const char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char s[], const char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

int strcmp(const char* s1, const char* s2) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int strequ(const char* s1, const char* s2){
    int i = 0;
    while(s1[i]!='\0'&&s2[i]!='\0'&&s1[i]==s2[i]){
        ++i;
    }
    return s1[i]==s2[i];
}

int strncmp(const char* s1, const char* s2, int n){
    if(n<1)return 0;
    int i;
    for (i = 0; i<n-1 && s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int strnequ(const char* s1, const char* s2, int n){
    if(n<1)return 0;
    int i = 0;
    while(i<n-1&&s1[i]!='\0'&&s2[i]!='\0'&&s1[i]==s2[i]){
        ++i;
    }
    return s1[i]==s2[i];
}

int strcountc(const char* s, char c){
    int i=0;
    int cc=0;
    while(s[i]!='\0'){
        if(s[i]==c){
            ++cc;
        }
        ++i;
    }
    return cc;
}