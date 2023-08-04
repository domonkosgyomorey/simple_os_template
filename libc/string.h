#ifndef STRINGS_H
#define STRINGS_H

void int_to_ascii(int n, char* cstr);
void str_reverse(char* cstr);
int str_len(const char* cstr);
void str_backspace(char* cstr);
void str_append(char* cstr, const char n);
int str_cmp(const char* cstr1, const char* cstr2);
int str_equ(const char* cstr1, const char* cstr2);
int str_n_cmp(const char* cstr1, const char* cstr2, int n);
int str_n_equ(const char* cstr1, const char* cstr2, int n);
int str_count_c(const char* cstr, char delimiter);
void str_trim(char* cstr);

#endif
