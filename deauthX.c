#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void clear_screen() {
    printf("\033[H\033[J");
}

void print_banner() {
    printf("\033[H"); 
    printf("\033[1;35m d \033[1;36m e \033[1;32m a \033[1;33m u \033[1;31m t \033[1;34m h \033[1;35m X \033[0m  \033[1;37m[V2.0]\033[0m\n");
    printf("\033[1;30m==============================\033[0m\n\n");
}

int main() {
    char keygen[50];
    char url[256];
    srand(time(NULL));

    if (getuid() != 0) {
        printf("Error: This tool must be run with sudo privileges.\n");
        return 1;
    }

    clear_screen();
    print_banner();

    for (int i = 0; i < 20; i++) {
        printf("%d%d", rand() % 2, rand() % 2);
        fflush(stdout);
        usleep(100000);
    }
    printf("\n\n");

    printf("Enter Activation Key: ");
    scanf("%49s", keygen);

    if (strcmp(keygen, "KEshy") != 0) {
        printf("\033[1;31mInvalid Keygen. Terminating...\033[0m\n");
        return 1;
    }

    printf("Target URL: ");
    scanf("%255s", url);

    int ip1 = rand() % 223 + 1;
    if (ip1 == 127 || ip1 == 192) ip1 = 172; 
    printf("\033[1;34mResolved source IP: %d.%d.%d.%d\033[0m\n", ip1, rand() % 255, rand() % 255, rand() % 255);

    printf("Synchronizing API... [");
    for (int i = 0; i <= 20; i++) {
        printf("\033[1;32m#\033[0m");
        fflush(stdout);
        usleep(150000);
    }
    printf("] 100%%\n");

    time_t end = time(NULL) + 5;
    while (time(NULL) < end) {
        printf("%x", rand());
        fflush(stdout);
        usleep(50000);
    }
    printf("\n\n");

    printf("\033[1;32mSUCCESS: OTP INTERCEPTED\033[0m\n");
    printf("OTP: %03d-%03d\n", rand() % 1000, rand() % 1000);

    return 0;
}
