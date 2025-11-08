#include <stdio.h>
#include <ctype.h> // isdigit
#include <math.h> // pow
#include <string.h>

char memory[65536];

// reads first number from stdout
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

// prints number
void puti(int num) {
  char s[21];
  char *p = s;
  for (int i=1, n=num; n > 0; i++, n/=10) *p++ = ('0' + n%10);
  int len = strlen(s);
  for (int i=len-1; i>=0; i--) putchar(*(s+i));
  putchar('\n');
}

int main() {
  int N=0, sum=0;
  geti(&N);
  for (int i=1; i<=N; i++) {sum += i; memory[i%65536] = i%256;}
  puti(sum);
}
