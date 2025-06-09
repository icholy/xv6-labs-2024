#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

int main(int argc, char *argv[]) {
  const int sz = PGSIZE * 100;
  char *end = sbrk(sz);
  char *p;

  for (p = end; p < end+sz ; p++) {
    if (strcmp(p, "my very very very secret pw is:") == 0) {
      fprintf(2, "OK: secret is %s", p+32);
      exit(0);
    }
  }
  exit(0);
}
