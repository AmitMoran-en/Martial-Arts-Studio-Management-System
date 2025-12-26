#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Training.h"
#include "General.h"
#include "FileHelper.h"


int initTraining(Training* pTraining, RoomManager* pRoomManager, Trainer* pTrainer)
{
    initTrainingNameAndDate(pTraining);
    initTrainingTrainer(pTraining, pTrainer);
    initTrainingRoom(pTraining, pRoomManager);
    return 1;
}

void initTrainingNameAndDate(Training* pTraining) {
    char temp[MAX_STR_LEN];
    printf("Enter Training name\n");
    myGets(temp, MAX_STR_LEN, stdin);
    pTraining->name = getDynStr(temp);
    printf("Enter training date:\n");
    getCorrectDate(&pTraining->trainingDate);
}

void initTrainingTrainer(Training* pTraining, Trainer* pTainer) 
{
	if (pTainer == NULL) 
    {
		printf("Error: Invalid Trainer pointer.\n");
		return;
	}
    else
	{         
		pTraining->trainer = pTainer;   
	}   
}

void initTrainingRoom(Training* pTraining, RoomManager* pRoomManager) 
{
	if (pRoomManager == NULL) 
    {
		printf("Error: Invalid RoomManager pointer.\n");
		return;
	}

    printf("Please choose a room for training from the list below\n");
    printRooms(pRoomManager);
    char code[CODE_LEN + 1];
    printf("Enter the room entry code for the training: ");
    scanf("%s", code);

    Room* room = findRoomByEntryCode(pRoomManager, code);

    if (room != NULL) {
        pTraining->room = room;
        printf("Training room set to room number: %d, and the entry code: %s\n", room->number, room->entryCode);
    }
    else {
        printf("Error: Room with entry code %s not found.\n", code);
    }
}

int compareTrainingByName(const void* pVoidTraining1, const void* pVoidTraining2)
{
    const Training* pTraining1 = (const Training*)pVoidTraining1;
    const Training* pTraining2 = (const Training*)pVoidTraining2;
    return strcmp(pTraining1->name, pTraining2->name);
}

int compareTrainingByDate(const void* pVoidTraining1, const void* pVoidTraining2)
{
     const Training* pTraining1 = (const Training*)pVoidTraining1;
     const Training* pTraining2 = (const Training*)pVoidTraining2;
    return compareDate(&pTraining1->trainingDate, &pTraining2->trainingDate);
}

void printTraining(const Training* pTraining)
{
    printDate(&pTraining->trainingDate);
    printf("Training Name: %s\n", pTraining->name);
    printRoom(pTraining->room);
    printTrainer(&pTraining->trainer);
}

void freeTraining(Training* pTraining)
{
    free(pTraining->name);
}


//binary file
int writeTrainingsToFile(const Training* trainingArr, int count, FILE* fp)
{
    if (fwrite(&count, sizeof(int), 1, fp) != 1)
        return 0;
    for (int i = 0; i < count; i++)
    {
        if (!writeTrainingToFile(&trainingArr[i], fp))
            return 0;
    }
    return 1;
}

//binary file
int readTrainingsFromFile(Training* trainingArr, int countTraining, Trainer** allTrainersArr, int countTrainers, RoomManager* pManager, FILE* fp)
{
    if (!trainingArr || !fp)
        return 0;

    for (int i = 0; i < countTraining; i++)
    {
        if (readTrainingFromFile(&trainingArr[i], allTrainersArr, countTrainers, pManager, fp) != 1)
            return 0;
    }
    return 1;
}


//binary file
int readTrainingFromFile(Training* pTraining, Trainer** allTrainersArr, int count, RoomManager* pManager, FILE* fp)
{
    if (!pTraining || !fp)
        return 0;
    pTraining->name = readStringFromFile(fp, "Error read training name\n");
    if (!pTraining->name)
		return 0;

    char id[ID_LEN + 1];

    if (!readCharsFromFile(id, ID_LEN, fp, "Error read ID\n"))
        return 0;
    id[ID_LEN] = '\0';

    pTraining->trainer = getTrainerByID(allTrainersArr, count, id);
    if (!pTraining->trainer)
        return 0;
    
    if (!readDateFromFile(fp, &pTraining->trainingDate))
        return 0;

    char entryCode[CODE_LEN + 1];

    if (!readCharsFromFile(entryCode, CODE_LEN, fp, "Error read entry code\n"))
        return 0;
    entryCode[CODE_LEN] = '\0';

    pTraining->room = findRoomByEntryCode(pManager, entryCode);
    if (!pTraining->room)
        return 0;
    return 1;
}

//binary file
int writeTrainingToFile(const Training* pTraining, FILE* fp) 
{
    if (!writeStringToFile(pTraining->name, fp, "Error write training name\n")
        || !writeCharsToFile(pTraining->trainer->person->id, ID_LEN, fp, "Error write ID\n")
        || !writeDateToFile(fp, &pTraining->trainingDate)
        || !writeCharsToFile(pTraining->room->entryCode, CODE_LEN, fp, "Error writing entry code\n"))
        return 0;
    return 1;
}

//text file
int saveTrainingsText(const Training* trainingArr, int count, FILE* fp)
{
    fprintf(fp, "%d\n", count);
    for (int i = 0; i < count; i++)
    {
        if (!saveTrainingText(&trainingArr[i], fp))
        {
            return 0;
        }
    }
    return 1;
}


//text file
int saveTrainingText(const Training* pTraining, FILE* fp) {
    if (!pTraining)
        return 0;

    saveDateText(&pTraining->trainingDate, fp);
    fprintf(fp, "%s\n", pTraining->name);
    
    fprintf(fp, "%s\n", pTraining->trainer->person->id);

    fprintf(fp, "%s\n", pTraining->room->entryCode);
    return 1; 
}

//text file
int loadTrainingsText(Training* trainingArr, int countTraining, Trainer** allTrainersArr, int countTrainers, RoomManager* pManager, FILE* fp)
{
    for (int i = 0; i < countTraining; i++)
    {
        if (loadTrainingText(&trainingArr[i], allTrainersArr, countTrainers, pManager, fp) == 0)
        {
            printf("Error reading training\n");
            return 0;
        }
    }
    return 1;
}

//text file
int loadTrainingText(Training* pTraining, Trainer** allTrainersArr, int count, RoomManager* pManager, FILE* fp)
{ 
    loadDateText(&pTraining->trainingDate, fp);

    char temp[MAX_STR_LEN];
    myGets(temp, MAX_STR_LEN, fp);
    pTraining->name = getDynStr(temp);

    char id[ID_LEN + 1];
    myGets(id, ID_LEN + 1, fp);

    pTraining->trainer = getTrainerByID(allTrainersArr, count, id);
    if (!pTraining->trainer)
        return 0;

    char entryCode[CODE_LEN + 1];
    myGets(entryCode, CODE_LEN + 1, fp);
    
    pTraining->room = findRoomByEntryCode(pManager, entryCode);
    if (!pTraining->room)
        return 0;
    return 1;
}

