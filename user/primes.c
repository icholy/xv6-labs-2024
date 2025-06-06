#include "kernel/types.h"
#include "user/user.h"

int read_int(int fd) {
  char buf[sizeof(int)];
  int n = read(fd, buf, sizeof(int));
  if (n == 0) {
    // NOTE: this means read_int cannot read a zero.
    //       but we don't need it for this use-case.
    return 0;
  }
  // TODO: use multiple calls if we don't get enough in the first read
  if (n != sizeof(int)) {
    fprintf(2, "read_int: expected 4 bytes, got %d", n);
    exit(1);
  }
  int i = 0;
  memcpy(&i, buf, sizeof(int));
  return i;
}

void write_int(int fd, int i) {
  char buf[sizeof(int)];
  memcpy(buf, &i, sizeof(int));
  int n = write(fd, buf, sizeof(int));
  if (n != sizeof(int)) {
    printf("write_int: expected 4 bytes, got %d", n);
  }
}

/**
 * Read 4 byte int values from fd and print the primes.
 * The first value read from fd is guaranteed to be a prime.
 */
int primes(int fd) {
  int prime = read_int(fd);
  printf("prime %d\n", prime);

  int pid = 0; // child pid
  int n;
  int p[2];
  while ((n = read_int(fd)) != 0) {
    if (n % prime != 0) {
      if (pid == 0) {
        pipe(p);
        pid = fork();
        if (pid == -1) {
          printf("failed to fork");
          exit(1);
        }
        if (pid == 0) {
          close(fd);
          close(p[1]);
          primes(p[0]);
          close(p[0]);
          exit(0);
        }
        close(p[0]);
      }
      write_int(p[1], n);
    }
  }

  if (pid != 0) {
    close(p[1]);
    wait(0);
  }

  return 0;
}

int main(int argc, char *argv[]) {
  int p[2];
  pipe(p);
  if (fork() == 0) {
    close(p[1]);
    primes(p[0]);
    close(p[0]);
    exit(0);
  }
  close(p[0]);
  for (int i = 2; i <= 280; i++) {
    write_int(p[1], i);
  }
  close(p[1]);
  wait(0);
  exit(0);
}
