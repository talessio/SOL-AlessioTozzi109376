#ifdef VERNAN_VERNAN_H
#define VERNAN_VERNAN_H

#endif //VERNAN_VERNAN_H

typedef struct {
    FILE* file;
    int size;
} file_t;

int getSize(const char*file);

int countBlocks(file_t keyFile, file_t inputFile);

char* loadKey(file_t keyFile, char* keyArr);

void encryptDecrypt(const char*keyFilePath, const char*inputFilePath, const char*outputFilePath);

void applyXOR(file_t keyFile, file_t inputFile, file_t outputFile);

void handleEmptyKey(file_t keyFile, file_t inputFile, file_t outputFile);