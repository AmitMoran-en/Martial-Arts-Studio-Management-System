#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255

#define ERROR_ALLOCATION_GENERAL printf("Memory allocation failed.\n"); return 0;
#define DROPPED_LINE printf("\n");

char*   getStrExactName(const char* msg);
char*   myGets(char* buffer, int size, FILE* source);
char*   getDynStr(char* str);
int     searchElementInArray(const void* arr, int count, int typeSize, const void* element, int(*compare)(const void* pVoid1, const void* pVoid2));
void    generalArrayFunction(void* arr, int size, int typeSize,void(*func)(void* element));// this function can also be used for printing but without numbering
void	generalPrintArrFunction(void* arr, int size, int typeSize, void(*func)(void* element));


#endif

