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
    // Only value provided, use current process
    pid = 0;  // Will be replaced with current pid in system call
    value = atoi(argv[1]);
  } else {
    // Both pid and value provided
    pid = atoi(argv[1]);
    value = atoi(argv[2]);
  }
  
  ret = nice(pid, value);
  if(ret < 0) {
    printf(2, "nice: failed to set priority\n");
    exit();
  }
  
  // Extract returned pid and old value
  int returned_pid = (ret >> 16) & 0xFFFF;
  int old_value = ret & 0xFFFF;
  
  printf(1, "%d %d\n", returned_pid, old_value);
  exit();
}