#include "conpyc.h"
#include "strfunc.h"

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
