#include "kernel/types.h"
#include "user/user.h"

struct a {
  int foo;
};

struct b {
  struct a bar;
  long baz;
};

int main(int argc, char *argv[]) {
  printf("%ld\n", sizeof(struct b));
  exit(0);
}
