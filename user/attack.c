#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

int main(int argc, char *argv[]) {
  for (;;) {
    char *end = sbrk(PGSIZE);
    char *match = strstr(end, "my very very very secret pw is:");
    if (match) {
      fprintf(2, "OK: secret is %s", match+32);
      break;
    }
  }
  exit(0);
}
