#include <stdlib.h>
#include <stdio.h>
#include "StudioFile.h"
#include "FileHelper.h"
#include "General.h"

int writeStudioToFile(const Studio* pStudio, const char* fileName)
{
    if (!pStudio)
        return 0;
    FILE* fp = fopen(fileName, "wb");
    if (!fp)
    {
        printf("Failed to open studio file for writing\n");
        return 0;
    }
    if (!writeStringToFile(pStudio->name, fp, "Error writing studio name\n"))
    {
        CLOSE_FILE_RETURN_0
    }
    if(!writeStringToFile(pStudio->country, fp, "Error write studio country\n"))
    {
        CLOSE_FILE_RETURN_0
    }
    if(!writeManagerToFile(pStudio->roomManager, fp))
    {
        CLOSE_FILE_RETURN_0
    }
    if(!writeTrainersToFile(pStudio->allTrainersArr, pStudio->trainersCount , fp))
    {
        CLOSE_FILE_RETURN_0
    }
    if(!writeTraineesToFile(pStudio->allTraineesArr, pStudio->traineesCount , fp))
    {
        CLOSE_FILE_RETURN_0
    }
    if(fwrite(pStudio->SNequipmentArr, sizeof(int), pStudio->trainersCount, fp) != pStudio->trainersCount)
    {
        CLOSE_FILE_RETURN_0
    }
    if(fwrite(&pStudio->traineeSortOpt, sizeof(int), 1, fp) != 1)
    {
        CLOSE_FILE_RETURN_0
    }
    if (!writeTrainingsToFile(pStudio->allTrainingsArr, pStudio->trainingsCount, fp))
    {
        CLOSE_FILE_RETURN_0
    }
    CLOSE_FILE_RETURN_1
}

int initStudiofromFile(Studio* pStudio, const char* fileName)
{
    FILE* fp;
    fp = fopen(fileName, "rb");
    if (!fp)
    {
        printf("Error open studio file\n");
        return 0;
    }
    pStudio->name = readStringFromFile(fp, "Error reading studio name\n");
    if (!pStudio->name)
    {
        CLOSE_FILE_RETURN_0
    }
    pStudio->country = readStringFromFile(fp, "Error reading studio country\n");
    if (!pStudio->country)
    {
        CLOSE_FILE_FREE_NAME
    }
    pStudio->roomManager = (RoomManager*)malloc(sizeof(RoomManager));
    if (!pStudio->roomManager)
    {
        printf("Memory allocation failed\n");
        CLOSE_FILE_FREE_COUNTRY
    }
    if(!readManagerToFile(pStudio->roomManager, fp))
    {
        free(pStudio->roomManager);
        CLOSE_FILE_FREE_COUNTRY
    }
    if (fread(&pStudio->trainersCount, sizeof(int), 1, fp) != 1)
    {
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        CLOSE_FILE_FREE_COUNTRY
    }
    pStudio->allTrainersArr = (Trainer**)malloc(sizeof(Trainer*) * (pStudio->trainersCount));
    if (!pStudio->allTrainersArr)
    {
        printf("Memory allocation failed\n");
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        CLOSE_FILE_FREE_COUNTRY
    }

    if(!readTrainersFromFile(pStudio->allTrainersArr, pStudio->trainersCount , fp))
    {
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        free(pStudio->allTrainersArr);
        CLOSE_FILE_FREE_COUNTRY
    }
    
    if (fread(&pStudio->traineesCount, sizeof(int), 1, fp) != 1)
    {
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        CLOSE_FILE_FREE_COUNTRY
    }
    pStudio->allTraineesArr = (Trainee**)malloc(sizeof(Trainee*) * (pStudio->traineesCount));
    if (!pStudio->allTraineesArr)
    {
        printf("Memory allocation failed\n");
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        CLOSE_FILE_FREE_COUNTRY
    }
    if(!readTraineesFromFile(pStudio->allTraineesArr, pStudio->traineesCount , fp))
    {
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        //free Trainers
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        free(pStudio->allTraineesArr);
        CLOSE_FILE_FREE_COUNTRY
    }
    
    pStudio->SNequipmentArr = (int*)malloc(sizeof(int) * (pStudio->trainersCount));
    if (!pStudio->SNequipmentArr)
    {
        printf("Memory allocation failed\n");
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        //free Trainers
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        generalArrayFunction(pStudio->allTraineesArr, pStudio->traineesCount, sizeof(Trainee*), freeTrainee);
        free(pStudio->allTraineesArr);
        CLOSE_FILE_FREE_COUNTRY
    }

    if (fread(pStudio->SNequipmentArr, sizeof(int), pStudio->trainersCount, fp) != pStudio->trainersCount)
    {
        freeManager(pStudio->roomManager);
        //free Trainers
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        //free Trainees
        generalArrayFunction(pStudio->allTraineesArr, pStudio->traineesCount, sizeof(Trainee*), freeTrainee);
        free(pStudio->allTraineesArr);
        free(pStudio->SNequipmentArr);
        CLOSE_FILE_FREE_COUNTRY
    }
    if(fread(&pStudio->traineeSortOpt, sizeof(int), 1, fp) != 1)
    {
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        //free Trainers
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        //free Trainees
        generalArrayFunction(pStudio->allTraineesArr, pStudio->traineesCount, sizeof(Trainee*), freeTrainee);
        free(pStudio->allTraineesArr);
        //free equipment
        free(pStudio->SNequipmentArr);
        CLOSE_FILE_FREE_COUNTRY
    }

    if (fread(&pStudio->trainingsCount, sizeof(int), 1, fp) != 1)
    {
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        //free Trainers
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        //free Trainees
        generalArrayFunction(pStudio->allTraineesArr, pStudio->traineesCount, sizeof(Trainee*), freeTrainee);
        free(pStudio->allTraineesArr);
        //free equipment
        free(pStudio->SNequipmentArr);
        CLOSE_FILE_FREE_COUNTRY
    }
    pStudio->allTrainingsArr = (Training*)malloc(sizeof(Training) * (pStudio->trainingsCount));
    if (!pStudio->allTrainingsArr)
    {
        printf("Memory allocation failed\n");
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        //free Trainers
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        //free Trainees
        generalArrayFunction(pStudio->allTraineesArr, pStudio->traineesCount, sizeof(Trainee*), freeTrainee);
        free(pStudio->allTraineesArr);
        free(pStudio->SNequipmentArr);
        CLOSE_FILE_FREE_COUNTRY
    }

    if (!readTrainingsFromFile(pStudio->allTrainingsArr, pStudio->trainingsCount, pStudio->allTrainersArr, pStudio->trainersCount, pStudio->roomManager, fp))
    {
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        //free Trainers
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        //free Trainees
        generalArrayFunction(pStudio->allTraineesArr, pStudio->traineesCount, sizeof(Trainee*), freeTrainee);
        free(pStudio->allTraineesArr);
        free(pStudio->SNequipmentArr);
        free(pStudio->allTrainingsArr);
        CLOSE_FILE_FREE_COUNTRY
    }
    CLOSE_FILE_RETURN_1
}

int loadStudioFromText(Studio* pStudio, const char* fileName)
{
    FILE* fp;

    fp = fopen(fileName, "r");
    if (!fp)
    {
        printf("Error open studio file\n");
        return 0;
    }
    char temp[MAX_STR_LEN];

    myGets(temp, MAX_STR_LEN, fp);
    pStudio->name = getDynStr(temp);
    if (!pStudio->name)
    {
        
        CLOSE_FILE_RETURN_0
    }

    myGets(temp, MAX_STR_LEN, fp);
    pStudio->country = getDynStr(temp);
    if (!pStudio->country)
    {
        CLOSE_FILE_FREE_NAME
    }
    pStudio->roomManager = (RoomManager*)malloc(sizeof(RoomManager));
    if (!pStudio->roomManager)
    {
        printf("Memory allocation failed\n");
        CLOSE_FILE_FREE_COUNTRY
    }
    if(!loadManagerToText(pStudio->roomManager, fp))
    {
        free(pStudio->roomManager);
        CLOSE_FILE_FREE_COUNTRY
    }

    fscanf(fp, "%d", &pStudio->trainersCount);
    fgetc(fp);
    pStudio->allTrainersArr = (Trainer**)malloc(sizeof(Trainer*) * (pStudio->trainersCount));
    if (!pStudio->allTrainersArr)
    {
        printf("Memory allocation failed\n");
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        CLOSE_FILE_FREE_COUNTRY
    }

    if (!loadTrainersText(pStudio->allTrainersArr, pStudio->trainersCount, fp))
    {
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        free(pStudio->allTrainersArr);
        CLOSE_FILE_FREE_COUNTRY
    }

    fscanf(fp, "%d", &pStudio->traineesCount);
    fgetc(fp);
    pStudio->allTraineesArr = (Trainee**)malloc(sizeof(Trainee*) * (pStudio->traineesCount));
    if (!pStudio->allTraineesArr)
    {
        printf("Memory allocation failed\n");
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        CLOSE_FILE_FREE_COUNTRY
    }

    if(!loadTraineesText(pStudio->allTraineesArr, pStudio->traineesCount, fp))
    {
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        //free Trainers
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        free(pStudio->allTraineesArr);
        CLOSE_FILE_FREE_COUNTRY
    }

    pStudio->SNequipmentArr = (int*)malloc(sizeof(int) * (pStudio->trainersCount));
    if (!pStudio->SNequipmentArr)
    {
        printf("Memory allocation failed\n");
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        //free Trainers
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        generalArrayFunction(pStudio->allTraineesArr, pStudio->traineesCount, sizeof(Trainee*), freeTrainee);
        free(pStudio->allTraineesArr);
        CLOSE_FILE_FREE_COUNTRY
    }

    for (int i = 0; i < pStudio->trainersCount; i++)
	{
		fscanf(fp, "%d", &pStudio->SNequipmentArr[i]);
		fgetc(fp);
	}

    fscanf(fp, "%d", &pStudio->traineeSortOpt);
    fgetc(fp);

    fscanf(fp, "%d", &pStudio->trainingsCount);
    fgetc(fp);

    pStudio->allTrainingsArr = (Training*)malloc(sizeof(Training) * (pStudio->trainingsCount));
    if (!pStudio->allTrainingsArr)
    {
        printf("Memory allocation failed\n");
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        //free Trainers
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        //free Trainees
        generalArrayFunction(pStudio->allTraineesArr, pStudio->traineesCount, sizeof(Trainee*), freeTrainee);
        free(pStudio->allTraineesArr);
        free(pStudio->SNequipmentArr);
        CLOSE_FILE_FREE_COUNTRY
    }

    if (!loadTrainingsText(pStudio->allTrainingsArr, pStudio->trainingsCount, pStudio->allTrainersArr, pStudio->trainersCount, pStudio->roomManager, fp))
    {
        freeManager(pStudio->roomManager);
        free(pStudio->roomManager);
        //free Trainers
        generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
        free(pStudio->allTrainersArr);
        //free Trainees
        generalArrayFunction(pStudio->allTraineesArr, pStudio->traineesCount, sizeof(Trainee*), freeTrainee);
        free(pStudio->allTraineesArr);
        free(pStudio->SNequipmentArr);
        free(pStudio->allTrainingsArr);
        CLOSE_FILE_FREE_COUNTRY
    }
    CLOSE_FILE_RETURN_1
}

int saveStudioToText(const Studio* pStudio, const char* fileName)
{
    FILE* fp;

    fp = fopen(fileName, "w");
    if (!fp)
    {
        printf("Unable to open studio file for writing\n");
        return 0;
    }

    fprintf(fp, "%s\n", pStudio->name);
    fprintf(fp, "%s\n", pStudio->country);
    if (!saveManagerToText(pStudio->roomManager, fp))
    {
        printf("Failed to write room manager data\n");
        CLOSE_FILE_RETURN_0
    }
    if (!saveTrainersText(pStudio->allTrainersArr, pStudio->trainersCount, fp))
    {
        printf("Failed to write trainers data\n");
        CLOSE_FILE_RETURN_0
    }
    if (!saveTraineesText(pStudio->allTraineesArr, pStudio->traineesCount, fp))
    {
        printf("Failed to write trainees data\n");
        CLOSE_FILE_RETURN_0
    }

    for (int i = 0; i < pStudio->trainersCount; i++) 
    {
        fprintf(fp, "%d\n", pStudio->SNequipmentArr[i]);
    }
    
    fprintf(fp, "%d\n", pStudio->traineeSortOpt);

    if (!saveTrainingsText(pStudio->allTrainingsArr, pStudio->trainingsCount, fp))
    {
        printf("Failed to write trainings data\n");
        CLOSE_FILE_RETURN_0
    }
    CLOSE_FILE_RETURN_1
}
