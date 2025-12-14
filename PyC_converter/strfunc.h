#include <stdio.h>
#include "consts.h"

// find word in words array
wchar_t *find_word_a(wchar_t words[WORDS_SIZE][WORD_SIZE], wchar_t word[WORD_SIZE]);

// add (copy) word in words array at specific index
wchar_t *add_word_a(wchar_t words[WORDS_SIZE][WORD_SIZE], 
    wchar_t word[WORD_SIZE], size_t index);

// compare two words 
wchar_t *cmpnw(wchar_t *word1, wchar_t *word2, size_t n);

// checks if char is space-char 
_Bool wisspace(wchar_t wch);

// skip cpecific char 
size_t *skipwch(wchar_t buffer[BUFFER_SIZE], wchar_t ch, size_t *i);

// skip space-char 
size_t *skipwspace(wchar_t buffer[BUFFER_SIZE], size_t *i);

// skip before cpecific char 
size_t *skip_before_wch(wchar_t buffer[BUFFER_SIZE], wchar_t ch, size_t *i);

// skip space-char 
size_t *skip_before_wspace(wchar_t buffer[BUFFER_SIZE], size_t *i);

// put before cpecific char 
size_t *put_before_wch(wchar_t buffer[BUFFER_SIZE], wchar_t ch, size_t *i);

// put space-char 
size_t *put_before_wspace(wchar_t buffer[BUFFER_SIZE], size_t *i);

// insert wide-word to stdout
void winsw_out(wchar_t word[WORD_SIZE]);

// copy one wide-word to another
size_t wcpy(wchar_t src[WORD_SIZE], wchar_t dest[WORD_SIZE]);

// copy wide-word from stdin to another and store it 
size_t wcpy_wrd_buf(wchar_t buffer[BUFFER_SIZE], wchar_t word[WORD_SIZE], size_t *i);
