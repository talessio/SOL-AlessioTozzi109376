#ifdef VERNAN_VERNAN_H
#define VERNAN_VERNAN_H

#endif //VERNAN_VERNAN_H

typedef struct file {
    FILE* file;
    int size;
} file;

int getSize(const char*file);
int countBlocks(file key, file input);
char* loadKey(file key, char* keyArr);
void encryptDecrypt(const char*keyFile, const char*inputFile, const char*outputFile);