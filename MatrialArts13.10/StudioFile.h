#ifndef __STUDIO_FILE__
#define __STUDIO_FILE__

#include "Studio.h"

#define CLOSE_FILE_RETURN_0		fclose(fp); return 0; 
#define CLOSE_FILE_FREE_NAME	free(pStudio->name); CLOSE_FILE_RETURN_0
#define CLOSE_FILE_FREE_COUNTRY free(pStudio->country); CLOSE_FILE_FREE_NAME
#define CLOSE_FILE_RETURN_1		fclose(fp); return 1;

int writeStudioToFile(const Studio* pStudio, const char* fileName);
int initStudiofromFile(Studio* pStudio, const char* fileName);
int loadStudioFromText(Studio* pStudio, const char* fileName);
int saveStudioToText(const Studio* pStudio, const char* fileName);

#endif
