#ifndef _PERSON_
#define _PERSON_

#include "Date.h"

#define ID_LEN 9
#define FREE_PERSON_NAME  free(pPer->name);return 0;

typedef enum {
    eMale, eFemale, eOther, eNofGenderType
} eGenderType;

static const char* GenderTypeStr[eNofGenderType];

typedef struct
{
    char*       name;
    char        id[ID_LEN + 1];
    Date        dateOfBirth;
    eGenderType gender;
}Person;

void        initPerson(Person* pPerson);
void        initPersonNoID(Person* pPerson);
int         isValidID(const char* id);
void        getPersonID(char* ID);
eGenderType getGenderType(void);
const char* GetGenderTypeStr(int type);
int         comparePersonByID(const void* pVoidPerson1, const void* pVoidPerson2);
void        printPerson(void* pVoidPerson);
void        freePerson(void* pPerson);

int         writePersonToFile(const Person* pPer, FILE* fp);
int         readPersonFromFile(Person* pPer, FILE* fp);
int         savePersonText(Person* pPer, FILE* fp);
int         loadPersonText(Person* pPer, FILE* fp);

#endif 
