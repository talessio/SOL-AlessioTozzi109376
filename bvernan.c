#include <stdio.h>
#include <stdlib.h>
#include "bvernan.h"

void handleEmptyKey(file key, file input, file output);

void applyXOR(file key, file input, file output);

/**
 * Returns size of file.
 * @param file The file whose size is needed
 * @return The int size
 */
int getSize(const char*file){
    int fileLength;
    FILE* f = fopen(file,"r");
    if(f == NULL) {
        perror("Error! Couldn't open file");
        return (-1);
    }
    fseek(f, 0, SEEK_END);
    fileLength = (int)ftell(f);
    fclose(f);
    return fileLength;
}

/**
 * Counts the blocks obtained by dividing input size by key size.
 * @param key The key used to encrypt or decrypt
 * @param input The file to be encrypted or decrypted
 * @return The int number of blocks
 */
int countBlocks(file key, file input) {
    int nBlocks;
    if ((input.size % key.size) == 0) {
        nBlocks = input.size / key.size;
    } else {
        nBlocks = (input.size / key.size) + 1;
    }
    // printf("key size = %d, input size = %d, number of blocks = %d\n", key.size, input.size, nBlocks);
    return nBlocks;
}

/**
 * Loads the key inside an array of char.
 * @param key The key used to encrypt or decrypt
 * @param keyArr The array of char values that will house the key
 * @return the array of char keyArr
 */
char* loadKey(file key, char* keyArr){
    for (int i = 0; i < key.size; ++i) {
        keyArr[i] = (char)fgetc(key.file);
    }
    return keyArr;
}

/**
 * Encrypts or decrypts the input file using XOR.
 * @param keyFile The key used to encrypt or decrypt
 * @param inputFile The file to be encrypted or decrypted
 * @param outputFile The encrypted or decrypted file
 */
void encryptDecrypt(const char*keyFile, const char*inputFile, const char*outputFile){
    file key = {(fopen(keyFile, "r")), getSize(keyFile)};
    file output = {(fopen(outputFile, "w")), getSize(outputFile)};
    file input = {(fopen(inputFile, "r")), getSize(inputFile)};
    if (key.size == 0){
        handleEmptyKey(key, input, output);
    }else if (getSize(keyFile) == -1 || getSize(inputFile) == -1 || getSize(outputFile) == -1){
        fclose(input.file);
        fclose(output.file);
        fclose(key.file);
        return;
    } else {
        applyXOR(key, input, output);
        printf("Done!\n");
    }
    fclose(input.file);
    fclose(output.file);
    fclose(key.file);
}

/**
 * Applies XOR encryption or decryption.
 * @param key The key used to encrypt or decrypt
 * @param input The file to be encrypted or decrypted
 * @param output The encrypted or decrypted file
 */
void applyXOR(file key, file input, file output) {
    int numberOfBlocks = countBlocks(key, input);
    char* keyArray = malloc(key.size);
    loadKey(key, keyArray);
    for (int i = 0; i<numberOfBlocks; i++) {
        for (int j = 0; j<key.size; j++) {
            int c = fgetc(input.file);
            if (c == EOF) {
                break;
            } else {
                int k;
                k = (i + j) % key.size;
                c = c ^ keyArray[k];
                fputc((c), output.file);
            }
        }
    }
    free(keyArray);
}

/**
 * Handles empty key by copying the input file into the output file.
 * @param key The key used to encrypt or decrypt
 * @param input The file to be encrypted or decrypted
 * @param output The encrypted or decrypted file
 */
void handleEmptyKey(file key, file input, file output) {
    printf("Given key is empty, output is the same as input.\n");
    int inputC;
    while ((inputC = fgetc(input.file)) != EOF){
        fputc(inputC, output.file);
    }
}
