#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

int main(int argc, char *argv[]) {
  const int sz = PGSIZE * 1000;
  char *end = sbrk(sz);

  for (int off = 0; off < sz ; off++) {
    if (memcmp(end+off, "my very very very secret pw is:", 31) == 0) {
      fprintf(2, "OK: secret is '%s'\n", end+off+32);
    }
  }
  exit(0);
}
