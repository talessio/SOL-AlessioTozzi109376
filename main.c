#include <stdio.h>
#include <string.h>
#include <time.h>
#include "bvernan.h"

void printInfo() {
    printf("bvernan keyfile inputfile outputfile\n");
}

int main(int argc, char **argv) {
    clock_t begin = clock();
    printf("Working on it...\n");
//    encryptDecrypt("k.txt", "input.txt", "output.txt");
    if (argc != 5) {
        printf("Wrong number of parameters, %d instead of 4!\n\n", argc);
        printInfo();
        return -1;
    }
    if (strcmp(argv[1], "bvernan")!=0) {
        printf("Wrong command!\n\n");
        printInfo();
        return -1;
    }
    if (argv[3] == NULL || argv[4] == NULL){
        perror("Error! Couldn't open file\n");
        return -1;
    }
    encryptDecrypt(argv[2], argv[3], argv[4]);
    clock_t end = clock();
    double tElapsed = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("It took me %lf seconds.\n", tElapsed);
    return 0;
}