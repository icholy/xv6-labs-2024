#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

int main(int argc, char *argv[]) {
  const int sz = PGSIZE * 1000;
  char *end = sbrk(sz);

  for (int off = 0; off < sz ; off++) {
    if (strcmp(end+off, "my very very very secret pw is:") == 0) {
      fprintf(2, "OK: secret is %s", end+off+32);
      exit(0);
    }
  }
  exit(0);
}
