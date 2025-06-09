#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

int main(int argc, char *argv[]) {
  const int sz = PGSIZE * 1000;
  char *end = sbrk(sz);

  for (char *addr = end+sz-100; ; addr--) {
    if (memcmp(addr, "my very very very secret pw is:", 31) == 0) {
      fprintf(2, "OK: secret is '%s'\n", addr+32);
    }
  }
  exit(0);
}
