#include "kernel/fs.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char *basename(char *path) {
  char *p;
  // find the first character after the last slach
  for (p = path + strlen(path); p > path && *p != '/'; p--)
    ;
  p++;
  return p;
}

int find(char *search, char *path) {
  int fd, len;
  struct stat st;
  struct dirent de;

  if ((fd = open(path, O_RDONLY)) < 0) {
    fprintf(2, "find: cannot open %s\n", path);
    return 1;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return 1;
  }

  switch (st.type) {
  case T_DEVICE:
  case T_FILE:
    if (strcmp(basename(path), search) == 0) {
      printf("%s\n", path);
    }
    break;
  case T_DIR:
    len = strlen(path);
    if (path[len-1] != '/') {
        path[len] = '/';
        path[len+1] = 0;
        len++;
    }
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
        continue;
      }
      memmove(path + len, de.name, DIRSIZ);
      if (find(search, path) < 0) {
        close(fd);
        return 1;
      }
    }
    break;
  }

  close(fd);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(2, "usage: find dir name");
    exit(1);
  }

  char path[512];
  strcpy(path, argv[1]);
  find(argv[2], path);
  exit(0);
}
