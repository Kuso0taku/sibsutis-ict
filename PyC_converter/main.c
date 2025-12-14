#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#define BUFFER_SIZE 1000 // max buffer size
#define WORD_SIZE 100 // max variable size
#define WORDS_SIZE 100 // max variables array size


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

// for loop condition (making brackets) processing 
void for_cond_proc(wchar_t buffer[BUFFER_SIZE], size_t *i) {
  fputws(L"for (int ", stdout); // start for loop

  wchar_t var[WORD_SIZE] = {L'\0'}; // local variable 
  wcpy_wrd_buf(buffer, var, i); // find local variable
  
  winsw_out(var);
  fputws(L"=0; ", stdout);
  winsw_out(var);
  putwchar(L'<');
  
  // find number
  skip_before_wch(buffer, L'(', i);
  
  // skip L'('
  (*i)++;

  // put number
  put_before_wch(buffer, L')', i);
  
  // skip L')'
  (*i)++;

  // skip L':'
  (*i)++;

  // close brackets
  fputws(L"; ", stdout);
  winsw_out(var);
  fputws(L"++)", stdout);
  if (*(buffer+(*i)) == L' ') putwchar(L' ');
  else fputws(L"\n\t", stdout);

}

// while loop and if condition (making brackets) processing 
void whif_cond_proc(wchar_t buffer[BUFFER_SIZE], size_t *i) {
  // start while/if
  fputws(L" (", stdout);
  
  // skip L' '
  (*i)++;

  // put condition 
  put_before_wch(buffer, L':', i);

  // skip L':'
  (*i)++;

  // close brackets
  putwchar(L')');
  if (*(buffer+(*i)) == L' ') putwchar(L' ');
  else fputws(L"\n\t", stdout);
}

// print processing
void print_proc(wchar_t buffer[BUFFER_SIZE], size_t *i) {
  // skip L"print" part
  skip_before_wch(buffer, L'(', i);

  // skip L'('
  (*i)++;

  // start printf func
  fputws(L"printf(\"%", stdout);

  // if string 
  if (*(buffer+(*i)) == L'"') putwchar(L's');
  else putwchar(L'd');
  fputws(L"\\n\", ", stdout);

  // end print
  put_before_wch(buffer, L')', i);
  (*i)++;
  fputws(L");\n\t", stdout);
}

// int(input()) processing 
void iinput_proc(wchar_t buffer[BUFFER_SIZE], wchar_t var[WORD_SIZE], size_t *i) {
  // just skip all L"int(input())"
  skip_before_wspace(buffer, i);

  // put scanf for int 
  fputws(L"scanf(\"%d\", &", stdout);
  winsw_out(var);
  fputws(L");\n\t", stdout);
}

// assignment processing
void asgn_proc(wchar_t buffer[BUFFER_SIZE], wchar_t vars[WORDS_SIZE][WORDS_SIZE], 
               wchar_t var[WORD_SIZE], _Bool new, wchar_t word[WORD_SIZE], 
               size_t *cntv, size_t *i) {
  // word copy to var
  wcpy(word, var);

  // skip spaces after variable
  skip_before_wch(buffer, L'=', i);

  // skip L'='
  if (*(buffer+(*i)) == L'=') (*i)++;
          
  // if variable isn't initialized
  if (new) {
    add_word_a(vars, var, *cntv);
    fputws(L"int ", stdout);
    (*cntv)++;
  }

  // print var and L'='
  winsw_out(var);
  fputws(L" = ", stdout);
  
  // read new word after L'='
  wcpy_wrd_buf(buffer, word, i);

  // int(input()), not input()!
  if (cmpnw(word, L"int", 3)) {
    if (new) {
      fputws(L"0;\n\t", stdout);
    }
    iinput_proc(buffer, var, i);
  } else {
    winsw_out(word); 
    put_before_wch(buffer, L'\n', i);
    fputws(L";\n\t", stdout);
  }
}

// end line 
void end_line(wchar_t ch) {
  if (ch==L'\n') {
    putwchar(L';');
    putwchar(ch);
    putwchar(L'\t');
  } else putwchar(ch);
}


int main() {
  setlocale(LC_ALL, "");

  wchar_t buffer[BUFFER_SIZE] = {L'\0'};
  wchar_t word[WORD_SIZE] = {L'\0'};
  wchar_t var[WORD_SIZE] = {L'\0'};
  wchar_t vars[WORDS_SIZE][WORD_SIZE] = {{L'\0'}};
  wint_t ch = 0; // character
  size_t cntv=0; // number of stored variables 
  size_t wlen=0; // word len
  size_t buf_len=0; // actualy buf size
  
  // read all input to buffer 
  for (; buf_len<BUFFER_SIZE-1; buf_len++) {
    ch = getwchar();
    if (ch == WEOF || ch == L'\0') break;
    *(buffer+buf_len)=ch;
  }
  *(buffer+buf_len)=L'\0';

  // start c-file
  fputws(L"#include <stdio.h>\n\nint main() {\n\t", stdout);

  for (size_t i=0; i<buf_len; i++) {
    // read buffer
    ch = *(buffer+i);
    if (ch==L'\0') break;

    // check end of word (or just space)
    if (wisspace(ch)) {
      putwchar(ch);
    } else {
      wlen = wcpy_wrd_buf(buffer, word, &i); // extract a word from input and cpy it to word
      if (wlen > 0) {
        // for loop
        if (cmpnw(word, L"for", 3)) for_cond_proc(buffer, &i);
        // if, while loopo
        else if (cmpnw(word, L"while", 5) || cmpnw(word, L"if", 2)) {
          winsw_out(word);
          whif_cond_proc(buffer, &i);
        // print
        } else if (cmpnw(word, L"print", 5)) {
          print_proc(buffer, &i);
        // assignment
        } else if (i+2<buf_len && *(buffer+i+1)==L'=' && *(buffer+i+2)!=L'=') {
          if (find_word_a(vars, word))
            asgn_proc(buffer, vars, var, 0, word, &cntv, &i);
          else asgn_proc(buffer, vars, var, 1, word, &cntv, &i);
        } else {
          winsw_out(word);
          end_line(ch);
        }
      }
    }
  }
  fputws(L"return 0;\n}", stdout);

  return 0;
}
