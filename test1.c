#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int pid;
  int ret;
  
  printf(1, "Starting nice value tests:\n\n");
  
  // Test 1: Change nice value of current process
  printf(1, "Test 1 - Current process:\n");
  ret = nice(0, 2);  // Change to 2 (higher priority than default)
  printf(1, "Expected: <current_pid> 3\n");  // Should show old value of 3
  printf(1, "Got: %d %d\n\n", (ret >> 16) & 0xFFFF, ret & 0xFFFF);
  
  // Test 2: Fork a child and change its nice value
  printf(1, "Test 2 - Child process:\n");
  if((pid = fork()) == 0) {
    // Child
    int child_pid = getpid();
    printf(1, "Child pid: %d\n", child_pid);
    ret = nice(child_pid, 4);  // Change to 4 (lower priority)
    printf(1, "Expected: %d 3\n", child_pid);  // Should show old value of 3
    printf(1, "Got: %d %d\n", (ret >> 16) & 0xFFFF, ret & 0xFFFF);
    exit();
  }
  wait();
  
  // Test 3: Invalid nice value (too high)
  printf(1, "\nTest 3 - Invalid nice value:\n");
  ret = nice(0, 6);  // Try to set value above 5
  printf(1, "Expected: -1 (error)\n");
  printf(1, "Got: %d\n\n", ret);
  
  // Test 4: Invalid pid
  printf(1, "Test 4 - Invalid pid:\n");
  ret = nice(99999, 2);
  printf(1, "Expected: -1 (error)\n");
  printf(1, "Got: %d\n", ret);
  
  // Test 5: Invalid nice value (too low)
  printf(1, "\nTest 5 - Below minimum nice value:\n");
  ret = nice(0, 0);  // Try to set value below 1
  printf(1, "Expected: -1 (error)\n");
  printf(1, "Got: %d\n", ret);

  exit();
}