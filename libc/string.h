#ifndef STRINGS_H
#define STRINGS_H

void int_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(const char s[]);
void backspace(char s[]);
void append(char s[], const char n);
int strcmp(const char* s1, const char* s2);
int strequ(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, int n);
int strnequ(const char* s1, const char* s2, int n);
int strcountc(const char* s, char delimiter);

#endif
