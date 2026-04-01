#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define KEYGEN "devil"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

void clear_screen() {
    printf("\e[1;1H\e[2J");
}

void print_banner() {
    printf("  _              _   _     __  __  __   __\n");
    printf(" | |            | | | |    \\ \\/ /  \\ \\ / /\n");
    printf(" | |__ ___  __ _| |_| |__   \\  /    \\ V / \n");
    printf(" | '_ ` _ \\/ _` | __| '_ \\  /  \\     > <  \n");
    printf(" | | |  __/ (_| | |_| | | |/_/\\_x   /_/ \\_\\\n");
    printf(" |_| |_\\___|\\__,_|\\__||_| |_|               V2.3\n\n");
}

int main(int argc, char *argv[]) {
    char input_key[50];
    char target_url[256];
    srand(time(NULL));

    if (getuid() != 0) {
        printf(RED "[!] ERROR: Permission denied. Use 'sudo ./deauthX'\n" RESET);
        return 1;
    }

    clear_screen();
    print_banner();

    // 1. KEYGEN CHALLENGE
    printf("[?] ENTER KEYGEN TO PROCEED: ");
    scanf("%49s", input_key);

    if (strcmp(input_key, KEYGEN) != 0) {
        printf(RED "[!] INVALID KEYGEN. TERMINATING SESSION...\n" RESET);
        return 1;
    }
    printf(GREEN "[+] AUTHENTICATION SUCCESSFUL.\n" RESET);
    sleep(1);

    // 2. TARGET URL
    printf("\n[?] ENTER TARGET URL: ");
    scanf("%255s", target_url);
    printf("[*] ATTACHING TO SOURCE...\n");
    sleep(1);

    // 3. SCAN URL FOR SOURCE IP
    printf("[*] SCANNING URL FOR SOURCE IP...\n");
    usleep(800000);
    printf(GREEN "[+] SOURCE IP IDENTIFIED: 192.168.%d.%d\n" RESET, rand()%255, rand()%255);
    sleep(1);

    // 4. TASKBAR / HEX STREAM
    printf("[*] INITIALIZING TASKBAR OVERLAY...\n");
    for(int i = 0; i < 6; i++) {
        printf("%04x %04x %04x %04x %04x %04x\n", 
               rand()%0xffff, rand()%0xffff, rand()%0xffff, 
               rand()%0xffff, rand()%0xffff, rand()%0xffff);
        usleep(300000);
    }

    // PROGRESS BAR
    printf("\n[");
    for(int i = 0; i < 40; i++) {
        printf("=");
        fflush(stdout);
        usleep(50000);
    }
    printf("] 100%%\n\n");

    // 5. GIVE OTP (NUMERIC ONLY)
    printf(GREEN "[+] OTP FOUND: %d-%d" RESET "\n", (rand()%900)+100, (rand()%900)+100);
    
    printf("\n[!] SESSION COMPLETED. PURGING BINARY...\n");
    sleep(1);

    // SELF DESTRUCT
    if (remove(argv[0]) == 0) {
        printf("[*] Binary " RED "deauthX" RESET " successfully purged.\n");
    }

    return 0;
}
