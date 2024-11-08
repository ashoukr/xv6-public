#include "types.h"
#include "stat.h"
#include "user.h"

int isPrime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void primeCalculator(void) {
    int count = 0;
    int num = 2;
    while(count < 1000) {
        if(isPrime(num)) {
            count++;
        }
        num++;
        sleep(1);
    }
}

int
main(void)
{
    // Create 27 children
    for(int i = 0; i < 27; i++) {
        int pid = fork();
        if(pid < 0) {
            printf(1, "Fork failed!\n");
            exit();
        }
        if(pid == 0) {  // Child process
            printf(1, "Started process: %d\n", getpid());
            primeCalculator();
            exit();
        }
        // Parent continues loop
    }

    // Parent waits for all children
    while(wait() != -1);  // Wait for all children to finish

    exit();
}