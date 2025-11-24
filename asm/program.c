int fac(int N) {
  int x=1;
  for (int i=1; i<=N; i++) x*=i;
  return x;
}

/* 
Пример вызова:
int main() {
  fac(10); // !10 = 3628800
}
*/
