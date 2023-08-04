#ifndef STRINGS_H
#define STRINGS_H

void int_to_ascii(int n, char* cstr);
void reverse(char* cstr);
int strlen(const char* cstr);
void backspace(char* cstr);
void append(char* cstr, const char n);
int strcmp(const char* cstr1, const char* cstr2);
int strequ(const char* cstr1, const char* cstr2);
int strncmp(const char* cstr1, const char* cstr2, int n);
int strnequ(const char* cstr1, const char* cstr2, int n);
int strcountc(const char* cstr, char delimiter);
void strtrim(char* cstr);

#endif
