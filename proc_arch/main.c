#include <stdio.h>
#include <ctype.h> // isdigit
#include <math.h> // pow

void geti(int*num) {
  char s[21]; // max number of digits + 1 for int 64-bit
  char *p = s;
  char ch;
  int count=0; // counts numbers in input
  // reads only numbers
  while ((ch=getchar()) != ' ' && 
    ch!='\n' && ch!='\t' && ch!=EOF && isdigit(ch)) {*p++ = ch; count ++;}
  
  p = s; // point at start of input string
  // convert chars to number
  for (int i=pow(10, count-1); i>0; i/=10, p++) *num += (*p-'0')*i;
}

int main() {
  int n;
  geti(&n);
  printf("\n%d\n", n);
}
