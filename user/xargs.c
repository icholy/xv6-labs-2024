#include "kernel/types.h"
#include "kernel/param.h"
#include "user.h"

int readline(int fd, char *buf) {
  int n;
  int sz = 0;
  buf[0] = 0;
  while (1) {
    n = read(fd, buf, 1);
    sz += n;
    if (n == 0) {
      buf++;
      *buf = 0;
      break;
    }
    if (n != 1) {
      return -1;
    }
    if (*buf == '\n') {
      *buf = 0;
      break;
    }
    buf++;
  }
  return sz;
}

int main(int argc, char *argv[]) {
  char line[512];
  while (readline(0, line) > 0) {
    if (fork() == 0) {
      char *xargv[MAXARG];
      memmove(xargv, argv, sizeof(char *) * argc);
      xargv[argc] = line;
      xargv[argc+1] = 0;
      exec(xargv[1], xargv + 1);
      fprintf(2, "xargs: failed to run command");
      exit(1);
    }
    wait(0);
  }
  exit(0);
}
