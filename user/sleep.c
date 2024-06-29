#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  if(argc < 2){
    fprintf(2, "usage: sleep tick...\n");
    exit(1);
  }

  if (sleep(atoi(argv[1]))) {
    fprintf(2, "sleep: %d failed\n", atoi(argv[1]));
    exit(1);
  }
  exit(0);
}