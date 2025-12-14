#include "consts.h"

// for loop condition (making brackets) processing 
void for_cond_proc(wchar_t buffer[BUFFER_SIZE], size_t *i);

// while loop and if condition (making brackets) processing 
void whif_cond_proc(wchar_t buffer[BUFFER_SIZE], size_t *i);

// print processing
void print_proc(wchar_t buffer[BUFFER_SIZE], size_t *i);

// int(input()) processing 
void iinput_proc(wchar_t buffer[BUFFER_SIZE], wchar_t var[WORD_SIZE], size_t *i);

// end line 
void end_line(wchar_t ch);

// assignment processing
void asgn_proc(wchar_t buffer[BUFFER_SIZE], wchar_t vars[WORDS_SIZE][WORDS_SIZE], 
               wchar_t var[WORD_SIZE], _Bool new, wchar_t word[WORD_SIZE], 
               size_t *cntv, size_t *i);
