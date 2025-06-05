#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  char buf[1];
  int p1[2]; // parent to child
  int p2[2]; // child to parent

  pipe(p1);
  pipe(p2);

  if (fork() == 0) {
    read(p1[0], buf, 1);
    printf("%d: received ping\n", getpid());
    write(p2[1], buf, 1);
    exit(0);
  }

  buf[0] = 'x';
  write(p1[1], buf, 1);
  read(p2[0], buf, 1);
  printf("%d: received pong\n", getpid());

  exit(0);
}
