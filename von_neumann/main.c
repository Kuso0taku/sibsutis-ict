#include <stdio.h>

int main() {
  // keeps commands and data
  int program[] = {1, 37, 2, 81, 4, 6, 1, 0, 3, 5, 13, 5, 6, 0};
  size_t size = sizeof program / sizeof program[0];
  int pc=0; // command counter points to the current command
  int acc=0; // register-accumulator keeps the current result

  while (program[pc]) { // runs til 0
    printf("Выполняется команда %d, ", program[pc]);
    switch (program[pc]) {
      case 1: // LOAD
        acc = program[pc+1]; pc+=2;
        break;
      case 2: // ADD
        acc += program[pc+1]; pc+=2;
        break;
      case 3: // PRINT
        pc++;
        printf("%d, ", acc);
        break;
      case 4: // JUMP
        if (program[pc+1] >= size) {
          program[pc]=0; // stops program
          printf("переход за границы памяти! ");
        } else pc = program[pc+1];
        break;
      case 5: // JUMP IF ZERO
        if (acc==0) {
          if (program[pc+1] < size) pc = program[pc+1];
          else {
            program[pc]=0;
            printf("переход за границы памяти! ");
          }
        } else pc += 2;
        break;
      default:
        printf("неизвестная команда! ");
        program[pc]=0;
    }
    printf("acc = %d\n", acc);
  }
  printf("Программа завершена.\n");
  
  return 0;
}
