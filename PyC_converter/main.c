#include <locale.h>
#include "strfunc.h"
#include "conpyc.h"

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
