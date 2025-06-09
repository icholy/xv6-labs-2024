#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/riscv.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  for (;;) {
    char *end = sbrk(PGSIZE);
    for (int off = 0; off < PGSIZE - 40; off++) {
      if (memcmp(end + off, "secret pw is:", 12) == 0) {
        fprintf(2, "%s", end + off + 14);
        exit(0);
      }
    }
  }
  exit(0);
}
