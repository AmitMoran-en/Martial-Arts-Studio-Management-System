#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Person.h"
#include "General.h"
#include "FileHelper.h"

static const char* GenderTypeStr[eNofGenderType]
        = { "Male", "Female", "Other"};



void initPerson(Person* pPerson)
{
    initPersonNoID(pPerson);
    getPersonID(pPerson->id);
}

void initPersonNoID(Person* pPerson)
{
    char temp[MAX_STR_LEN];
    printf("Enter person name\n");
    myGets(temp, MAX_STR_LEN, stdin);
    pPerson->name = getDynStr(temp);
    printf("Enter person birth date:\n");
    getCorrectDate(&pPerson->dateOfBirth);
    pPerson->gender = getGenderType();
}

int isValidID(const char *id)
{
    //Algorithm for checking the correctness of an ID card in the world I have attached a link to the article- https://www.ynet.co.il/articles/0,7340,L-4483052,00.html
    int nDigits = (int)strlen(id);
    int sum = 0, isSecond = 0;

    if (nDigits != ID_LEN) return 0;

    for (int i = nDigits - 1; i >= 0; i--) {
        int digit = id[i] - '0';
        if (digit < 0 || digit > 9) return 0;

        if (isSecond) {
            digit = digit * 2;
            if (digit > 9) {
                digit -= 9;
            }
        }

        sum += digit;
        isSecond = !isSecond;
    }
    return (sum % 10 == 0);
}

void getPersonID(char* id)
{
    int res = 0;
    do
    {
        printf("Enter ID - valid number with %d digits: ", ID_LEN);
        scanf("%9s", id);
        id[ID_LEN] = '\0';
        if (!isValidID(id))
            printf("Invalid ID, please try again.\n");
        else
            res = 1;
    } while (!res);

}

eGenderType getGenderType(void)
{
    int option;
    printf("\n\n");
    do {
        printf("Please enter one of the following types\n");
        for (int i = 0; i < eNofGenderType; i++)
            printf("%d for %s\n", i, GenderTypeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= eNofGenderType);
    getchar();
    return (eGenderType)option;
}

const char* GetGenderTypeStr(int type)
{
    if (type < 0 || type >= eNofGenderType)
        return NULL;
    return GenderTypeStr[type];
}

void freePerson(void* pPerson)
{
    Person* fPerson = *(Person**)pPerson;
    free(fPerson->name);
}

int comparePersonByID(const void* pVoidPerson1, const void* pVoidPerson2)
{
    const Person* pPerson1 = (Person*)pVoidPerson1;
    const Person* pPerson2 = (Person*)pVoidPerson2;
    return strcmp(pPerson1->id, pPerson2->id);
}

void printPerson(void* pVoidPerson)
{
    const Person* pPerson = (const Person*)pVoidPerson;
    printf("Birth ");
    printDate(&pPerson->dateOfBirth);
    printf("Name: %-10s, ID: %-10s\n, Gender: %-10s", pPerson->name, pPerson->id, GenderTypeStr[pPerson->gender]);
}

//binary file
int writePersonToFile(const Person* pPer, FILE* fp)
{
    if (!writeStringToFile(pPer->name, fp, "Error write person name\n")
        || !writeCharsToFile(pPer->id, ID_LEN, fp, "Error write ID\n")
        || !writeDateToFile(fp, &pPer->dateOfBirth)
        || fwrite(&pPer->gender, sizeof(eGenderType), 1, fp) != 1)
        {
            return 0;
        }
    return 1;
}

//binary file
int readPersonFromFile(Person* pPer, FILE* fp)
{
    if (!pPer)
        return 0;
    pPer->name = readStringFromFile(fp, "Error read person name\n");
    if (!pPer->name)
        return 0;
    if (!readCharsFromFile(pPer->id, ID_LEN, fp, "Error read ID\n"))
    {
        FREE_PERSON_NAME
    }
       
    if (!readDateFromFile(fp, &pPer->dateOfBirth))
    {
        FREE_PERSON_NAME
    }
    if (fread(&pPer->gender, sizeof(eGenderType), 1, fp) != 1)
    {
        FREE_PERSON_NAME
    }
    pPer->id[ID_LEN] = '\0';
    return 1;
}

//text file
int savePersonText(Person* pPer, FILE* fp)
{
    if (!pPer)
        return 0;
    saveDateText(&pPer->dateOfBirth, fp);
    fprintf(fp, "%s\n", pPer->id);
    fprintf(fp, "%s\n", pPer->name);
    fprintf(fp, "%d\n", pPer->gender);
    return 1;

}

//text file
int loadPersonText(Person* pPer, FILE* fp)
{
    if (!pPer)
        return 0;
    loadDateText(&pPer->dateOfBirth, fp);
    myGets(pPer->id, ID_LEN +1, fp);
    char temp[MAX_STR_LEN];
    myGets(temp, MAX_STR_LEN, fp);
    pPer->name = getDynStr(temp);
   
    fscanf(fp, "%d", &pPer->gender);
    fgetc(fp);
    return 1;
    
}
