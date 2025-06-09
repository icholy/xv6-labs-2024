#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"


int
main(int argc, char *argv[])
{
  if(argc != 2){
    printf("Usage: secret the-secret\n");
    exit(1);
  }
  // grow heap by 32 pages
  char *end = sbrk(PGSIZE*32);
  // point 9 pages into the heap
  end = end + 9 * PGSIZE;
  // write secret into the page 9
  strcpy(end, "my very very very secret pw is:   ");
  strcpy(end+32, argv[1]);
  exit(0);
}

