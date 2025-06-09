#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/riscv.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  for (;;) {
    char *end = sbrk(PGSIZE);
    for (int off = 0; off < PGSIZE - 40; off++) {
      if (memcmp(end + off, "my very very very secret pw is:", 31) == 0) {
        fprintf(2, "OK: secret is '%s'\n", end + off + 32);
      }
    }
  }
  exit(0);
}
