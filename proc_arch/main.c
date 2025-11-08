#include <stdio.h>

void getl(char*s) {
  char ch;
  char *p = s;
  while ((ch=getchar()) != ' ' && ch!='\n' && ch!='\t' && ch!=EOF) *p++ = ch;
}

int main() {
  char s[255];
  getl(s);
  puts(s);
}
