#ifndef _FILEHELPER_
#define _FILEHELPER_
#include <stdio.h>

int   writeStringToFile(const char* str, FILE* fp, const char* msg);
int   writeCharsToFile(const char* arr, int size, FILE* fp, const char* msg);
int   writeIntToFile(int val, FILE* fp, const char* msg);
char* readStringFromFile(FILE* fp, const char* msg);
int   readCharsFromFile(char* arr, int length, FILE* fp, const char* msg);
int   readIntFromFile(int* pVal, FILE* fp, const char* msg);


#endif
