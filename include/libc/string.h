#ifndef STRINGS_H
#define STRINGS_H

// convert a number into cstr
void int_to_ascii(int n, char* cstr);

// reverse a cstr
void str_reverse(char* cstr);

// get the cstr len
int str_len(const char* cstr);

// remove the last letter from cstr
void str_backspace(char* cstr);

// push a letter into cstr
void str_append(char* cstr, const char n);

/* 
 * compare two cstr
 * return: 
 * positive if cstr1 is bigger
 * negitive if cstr1 is lower
 * 0 if equal
 */
int str_cmp(const char* cstr1, const char* cstr2);

// return 1 if the two cstr are equals
int str_equ(const char* cstr1, const char* cstr2);

/* 
 * compare two cstr with buff overflow protection
 * return: 
 * positive if cstr1 is bigger
 * negitive if cstr1 is lower
 * 0 if equal
 */
int str_n_cmp(const char* cstr1, const char* cstr2, unsigned int n);

// return 1 if the two cstr are equals, with buff overflow protection
int str_n_equ(const char* cstr1, const char* cstr2, unsigned int n);

// count how many delimiter are in cstr
int str_count_c(const char* cstr, char delimiter);

// remove the leading zeros
void str_trim(char* cstr);

// copy the content from cstr1 into cstr2
void str_cpy(const char* cstr1, char* cstr2);

// copy n-1 amount letter from cstr1 into cstr2
void str_n_cpy(const char* cstr1, char* cstr2, unsigned int n);

// cut the cstr1 first word into cstr2 (trimmed)
void str_cut_word(char* cstr1, char* cstr2);

// cut the cstr1 first n-1 amount of letter into cstr2 until a space (trimmed)
void str_cut_word_n(char* cstr1, char* cstr2, unsigned int n);

#endif
