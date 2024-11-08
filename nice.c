#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid, value;
  int ret;
  
  if(argc < 2 || argc > 3) {
    printf(2, "Usage: nice pid value OR nice value\n");
    exit();
  }
  
  if(argc == 2) {
    // Only value provided - use for current process
    value = atoi(argv[1]);
    ret = nice(0, value);  // 0 means current process
    if(ret < 0) {
      printf(2, "nice: failed to set priority - value must be between 1 and 5\n");
      exit();
    }
    printf(1, "%d %d\n", (ret >> 16) & 0xFFFF, ret & 0xFFFF);
  } else {
    // Both pid and value provided
    pid = atoi(argv[1]);
    value = atoi(argv[2]);
    ret = nice(pid, value);
    if(ret < 0) {
      printf(2, "nice: failed to set priority - process does not exist or invalid value\n");
      exit();
    }
    printf(1, "%d %d\n", (ret >> 16) & 0xFFFF, ret & 0xFFFF);
  }
  exit();
}