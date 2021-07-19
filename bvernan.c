#include <stdio.h>
#include <stdlib.h>
#include "bvernan.h"

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
 * @param keyFile The key used to encrypt or decrypt
 * @param inputFile The file to be encrypted or decrypted
 * @return The int number of blocks
 */
int countBlocks(file_t keyFile, file_t inputFile) {
    int nBlocks = inputFile.size / keyFile.size;
    if ((inputFile.size % keyFile.size) != 0) {
        nBlocks += 1;
    }
    return nBlocks;
}

/**
 * Loads the key inside an array of char.
 * @param keyFile The key used to encrypt or decrypt
 * @param keyArr The array of char values that will house the key
 * @return the array of char
 */
char* loadKey(file_t keyFile, char* keyArr){
    for (int i = 0; i < keyFile.size; ++i) {
        keyArr[i] = (char)fgetc(keyFile.file);
    }
    return keyArr;
}

/**
 * Encrypts or decrypts the input file using XOR.
 * @param keyFilePath The path of the key file used to encrypt or decrypt
 * @param inputFilePath The path of the input file to be encrypted or decrypted
 * @param outputFilePath The path of the encrypted or decrypted output file
 */
void encryptDecrypt(const char*keyFilePath, const char*inputFilePath, const char*outputFilePath){
    // int keySize = getSize(keyFilePath);
    // int inputSize = getSize(inputFilePath);
    // int outputSize = getSize(outputFilePath);
    file_t keyFile = {fopen(keyFilePath, "r"), getSize(keyFilePath)};
    file_t outputFile = {fopen(outputFilePath, "w"), getSize(inputFilePath)};
    file_t inputFile = {fopen(inputFilePath, "r"), getSize(outputFilePath)};
    if (keyFile.size != -1 && inputFile.size != -1) {
        if (keyFile.size == 0) {
            handleEmptyKey(keyFile, inputFile, outputFile);
        } else {
            applyXOR(keyFile, inputFile, outputFile);
        }
        printf("Done!\n");
    } 
    fclose(inputFile.file);
    fclose(outputFile.file);
    fclose(keyFile.file);
}

/**
 * Applies XOR encryption or decryption.
 * @param keyFile The key used to encrypt or decrypt
 * @param inputFile The file to be encrypted or decrypted
 * @param outputFile The encrypted or decrypted file
 */
void applyXOR(file_t keyFile, file_t inputFile, file_t outputFile) {
    int numberOfBlocks = countBlocks(keyFile, inputFile);
    char* keyArray = malloc(keyFile.size);
    loadKey(keyFile, keyArray);
    for (int i = 0; i<numberOfBlocks; i++) {
        for (int j = 0; j<keyFile.size; j++) {
            int c = fgetc(inputFile.file);
            if (c == EOF) {
                break;
            } else {
                int k;
                k = (i + j) % keyFile.size;
                c = c ^ keyArray[k];
                fputc((c), outputFile.file);
            }
        }
    }
    free(keyArray);
}

/**
 * Handles empty key by copying the input file into the output file.
 * @param keyFile The key used to encrypt or decrypt
 * @param inputFile The file to be encrypted or decrypted
 * @param outputFile The encrypted or decrypted file
 */
void handleEmptyKey(file_t keyFile, file_t inputFile, file_t outputFile) {
    printf("Given key is empty, output is the same as input.\n");
    int inputC;
    while ((inputC = fgetc(inputFile.file)) != EOF){
        fputc(inputC, outputFile.file);
    }
}
