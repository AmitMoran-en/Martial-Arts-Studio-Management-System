#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Trainer.h"
#include "General.h"
#include "FileHelper.h"

int initTrainer(Trainer* pTrainer)
{
    pTrainer->person = (Person*)malloc(sizeof(Person));
    if (!pTrainer->person)
    {
        ERROR_ALLOCATION_GENERAL
    }
	initPerson(pTrainer->person);
	initTrainerNoPerson(pTrainer);
    return 1;
}

void initTrainerNoPerson(Trainer* pTrainer)
{
    printf("Enter employee's Seniority in months\n");
    scanf("%d", &(pTrainer->seniority));
    printf("\n");
	printf("Enter the details of the trainer's personal equipment:\n");
	initEquipmentNoSerialNumber(&pTrainer->equipment);
}

int* addTrainerEquipmentSN(int* SNequipmentArr, int count, Trainer* pTrainer)
{
    int serialNumber;
    getEquipmentSerialNumber(SNequipmentArr, count, &serialNumber);
    pTrainer->equipment.serialNumber = serialNumber;
    SNequipmentArr = (int*)realloc(SNequipmentArr,
        sizeof(int) * (size_t)(count + 1));
    if (!SNequipmentArr)
    {
        freeTrainer(pTrainer);
        return NULL;
    }
    SNequipmentArr[count] = serialNumber;
    return SNequipmentArr;
}

int compareTrainerByID(const void* pVoidTrainer1, const void* pVoidTrainer2)
{
	Trainer* pTrainer1 = *(Trainer**)pVoidTrainer1;
	Trainer* pTrainer2 = *(Trainer**)pVoidTrainer2;
    return strcmp(pTrainer1->person->id, pTrainer2->person->id);
}

Trainer* getTrainerByID(Trainer** trainerArr, int count, char* id)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(trainerArr[i]->person->id, id) == 0)
            return trainerArr[i];
    }
    return NULL;
}


void printTrainer(const void* pTrainer)
{
    Trainer* tTrainer = *(Trainer**)pTrainer;
    printf("Trainer details:\n");
    printPerson(tTrainer->person);
    printEquipment(&(tTrainer->equipment));
    printf("Seniority in months: %d\n", tTrainer->seniority);
}

void freeTrainer(void* pVoidTrainer)
{
    Trainer* pTrainer = *(Trainer**)pVoidTrainer;
    freePerson(&pTrainer->person);
    free(pTrainer->person);
}

//binary file
int writeTrainerToFile(const Trainer* pTrainer, FILE* fp)
{
    if (writePersonToFile(pTrainer->person, fp) != 1 
        || fwrite(&pTrainer->seniority, sizeof(int), 1, fp) != 1
        || writeEquipmentToFile(&pTrainer->equipment, fp) != 1)
        return 0;
    return 1;
}

//binary file
int writeTrainersToFile(const Trainer** TrainerArr, int count, FILE* fp)
{
    if (fwrite(&count, sizeof(int), 1, fp) != 1)
        return 0;
    for (int i = 0; i < count; i++)
    {
        if (!writeTrainerToFile(TrainerArr[i], fp))
            return 0;
    }
    return 1;
}

//binary file
int readTrainerFromFile(Trainer* pTrainer, FILE* fp)
{
    if (!pTrainer || !fp)
        return 0;
    pTrainer->person = (Person*)malloc(sizeof(Person));
    if (!pTrainer->person)
    {
        ERROR_ALLOCATION_GENERAL
    }
    if (readPersonFromFile(pTrainer->person, fp) != 1)
    {
        free(pTrainer->person);
        return 0;
    }

    if (fread(&pTrainer->seniority, sizeof(int), 1, fp) != 1)
    {
        free(pTrainer->person);
        return 0;
    }

    if (readEquipmentFromFile(&pTrainer->equipment, fp) != 1)
    {
        free(pTrainer->person);
        return 0;
    }

    return 1;
}

//binary file
int readTrainersFromFile(Trainer** trainerArr, int count, FILE* fp)
{
    if (!trainerArr || !fp)
        return 0;
    Trainer* pTrainer;
    for (int i = 0; i < count; i++)
    {
        pTrainer = (Trainer*)calloc(1, sizeof(Trainer));
        if (!pTrainer)
        {
            ERROR_ALLOCATION_GENERAL
        }
        if (readTrainerFromFile(pTrainer, fp) != 1)
            return 0;
        trainerArr[i] = pTrainer;
    }
    return 1;
}

//text file
int saveTrainersText(const Trainer** TrainerArr, int count, FILE* fp)
{
    fprintf(fp, "%d\n", count);
    for (int i = 0; i < count; i++)
    {
        if (!saveTrainerText(TrainerArr[i], fp))
        {
            return 0;
        }
    }
    return 1;
}
    
//text file    
int saveTrainerText(const Trainer* pTrainer, FILE* fp)
{
    if (!pTrainer || !fp)
        return 0;
    
    if (savePersonText(pTrainer->person, fp) != 1)
        return 0;
    
    fprintf(fp, "%d\n", pTrainer->seniority);
    if (saveEquipmentText(&pTrainer->equipment, fp) != 1)
        return 0;
    return 1;
}

//text file
int  loadTrainersText(Trainer** trainerArr, int count, FILE* fp)
{
    if (!trainerArr)
        return 0;
    
    Trainer* pTrainer;
    for (int i = 0; i < count; i++)
    {
        pTrainer = (Trainer*)calloc(1, sizeof(Trainer));
        if (!pTrainer)
        {
            ERROR_ALLOCATION_GENERAL
        }
        if (!loadTrainerText(pTrainer, fp))
        {
            printf("Error reading trainer\n");
            return 0;
        }
        trainerArr[i] = pTrainer;
    }
    return 1;
}

//text file
int loadTrainerText(Trainer* pTrainer, FILE* fp)
{
    if (!pTrainer || !fp)
        return 0;
    pTrainer->person = (Person*)malloc(sizeof(Person));
    if (!pTrainer->person)
    {
        ERROR_ALLOCATION_GENERAL
    }
    if (loadPersonText(pTrainer->person, fp) != 1)
    {
        free(pTrainer->person);
        return 0;
    }
    
    fscanf(fp, "%d", &pTrainer->seniority);
    fgetc(fp);
    
    if (loadEquipmentText(&pTrainer->equipment, fp) != 1)
    {
        freePerson(pTrainer->person);
        free(pTrainer->person);
        return 0;
    }
    return 1;
}

