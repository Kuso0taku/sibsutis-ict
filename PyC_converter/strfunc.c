#include "strfunc.h"

// find word in words array
wchar_t *find_word_a(wchar_t words[WORDS_SIZE][WORD_SIZE], wchar_t word[WORD_SIZE]) {
  for (size_t i=0; i<WORDS_SIZE; i++)
    for (size_t j=0; j<WORD_SIZE; j++) {
      if (*(*(words+i)+j) != *(word+j)) break;
      if (*(*(words+i)+j) == L'\0' && *(word+j) == L'\0') return *(words+i);
      if (*(*(words+i)+j) == L'\0') break;
    }
  return NULL;
}

// add (copy) word in words array at specific index
wchar_t *add_word_a(wchar_t words[WORDS_SIZE][WORD_SIZE], wchar_t word[WORD_SIZE], size_t index) {
  if (index >= WORDS_SIZE) return NULL;
  for (size_t i=0; i<WORD_SIZE; i++) {
    *(*(words+index)+i) = *(word+i);
    if (*(word+i) == '\0') break;
  }
  *(*(words+index)+WORD_SIZE-1) = L'\0';
  return *(words+index);
}

// compare two words 
wchar_t *cmpnw(wchar_t *word1, wchar_t *word2, size_t n) {
  if (!word1 || !word2) return NULL;
  for (size_t i=0; i<n; i++) {
    if (*(word1+i) != *(word2+i)) return NULL;
    if (*(word1+i) == L'\0' && *(word2+i) == L'\0') break;
    if (*(word1+i) == L'\0' || *(word2+i) == L'\0') return NULL;
  }
  return (wchar_t*)word1;
}

// checks if char is space-char 
_Bool wisspace(wchar_t wch) {
  if (wch == L'\n' || wch == L'\t' || wch == L' ' || wch == L'\r') return true;
  return false;
}

// skip cpecific char 
size_t *skipwch(wchar_t buffer[BUFFER_SIZE], wchar_t ch, size_t *i) {
  for (; (*i) < BUFFER_SIZE && 
    *(buffer+(*i)) == ch && *(buffer+(*i)) != L'\0'; (*i)++);
  return i;
}

// skip space-char 
size_t *skipwspace(wchar_t buffer[BUFFER_SIZE], size_t *i) {
  for (; (*i)<BUFFER_SIZE && wisspace(*(buffer+(*i))); (*i)++);
  return i;
}


// skip before cpecific char 
size_t *skip_before_wch(wchar_t buffer[BUFFER_SIZE], wchar_t ch, size_t *i) {
  for (; (*i) < BUFFER_SIZE && 
    *(buffer+(*i)) != ch && *(buffer+(*i)) != L'\0'; (*i)++);
  return i;
}

// skip space-char 
size_t *skip_before_wspace(wchar_t buffer[BUFFER_SIZE], size_t *i) {
  for (; (*i)<BUFFER_SIZE && !wisspace(*(buffer+(*i))); (*i)++);
  return i;
}

// put before cpecific char 
size_t *put_before_wch(wchar_t buffer[BUFFER_SIZE], wchar_t ch, size_t *i) {
  for (; (*i) < BUFFER_SIZE && 
    *(buffer+(*i)) != ch && *(buffer+(*i)) != L'\0'; (*i)++) 
    putwchar(*(buffer+(*i)));
  return i;
}

// put space-char 
size_t *put_before_wspace(wchar_t buffer[BUFFER_SIZE], size_t *i) {
  for (; (*i)<BUFFER_SIZE && !wisspace(*(buffer+(*i))); (*i)++) 
    putwchar(*(buffer+(*i)));
  return i;
}

// insert wide-word to stdout
void winsw_out(wchar_t word[WORD_SIZE]) {
  for (size_t i=0; i<WORD_SIZE && *(word+i) != L'\0'; i++) {
    putwchar(*(word+i));
  }
}

// copy one wide-word to another
size_t wcpy(wchar_t src[WORD_SIZE], wchar_t dest[WORD_SIZE]) {
  size_t cnt=0;
  for (size_t i=0; i<WORD_SIZE && *(src+i)!=L'\0'; i++) {
    *(dest+i) = *(src+i);
    cnt++;
  }
  if (cnt < WORD_SIZE) *(dest+cnt) = L'\0';
  return cnt;
}

// copy wide-word from stdin to another and store it 
size_t wcpy_wrd_buf(wchar_t buffer[BUFFER_SIZE], wchar_t word[WORD_SIZE], size_t *i) {
  size_t cnt=0; // counts chars
  wchar_t ch=0;
  // skip leading whitespaces
  skipwspace(buffer, i);

  // read word
  for (; (*i)<BUFFER_SIZE && cnt < WORD_SIZE-1; (*i)++) {
    ch = *(buffer+(*i));
    if (wisspace(ch) || ch==L':' || ch==L'(') {*(word+cnt)=L'\0'; return cnt;}
    *(word+cnt) = ch;
    cnt++;
  }
  
  // end word as string
  if (cnt < WORD_SIZE) *(word+cnt) = L'\0';

  return cnt;
}
