#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Trainee.h"
#include "General.h"
#include "FileHelper.h"


int initTrainee(Trainee* pTrainee)
{
	pTrainee->person = (Person*)malloc(sizeof(Person));
	if (!pTrainee->person)
	{
		ERROR_ALLOCATION_GENERAL
	}
	initPerson(pTrainee->person);
	initTraineeNoPerson(pTrainee);
	return 1;
}

void initTraineeNoPerson(Trainee* pTrainee)
{
	getSubscriptionPrice(pTrainee);
}

void freeTrainee(void* pVoidTrainee)
{
	Trainee* pTrainee = *(Trainee**)pVoidTrainee;
	freePerson(&pTrainee->person);
	free(pTrainee->person);
}

void getSubscriptionPrice(Trainee* pTrainee)
{
	printf("Please enter the Subscription Price of the trainee:\n");
	scanf("%d", &pTrainee->subscriptionPrice);
}
int	 compareTraineeBySubscriptionPrice(const void* pVoidTrainee1, const void* pVoidTrainee2)
{
	Trainee* pTrainee1 = (Trainee*)pVoidTrainee1;
	Trainee* pTrainee2 = (Trainee*)pVoidTrainee2;
	return (pTrainee1->subscriptionPrice - pTrainee2->subscriptionPrice);
}
int  compareTraineeByID(const void* pVoidTrainee1, const void* pVoidTrainee2)
{
	Trainee* pTrainee1 = *(Trainee**)pVoidTrainee1;
	Trainee* pTrainee2 = *(Trainee**)pVoidTrainee2;
	return strcmp(pTrainee1->person->id, pTrainee2->person->id);
}
int  compareTraineeByAge(const void* pVoidTrainee1, const void* pVoidTrainee2)
{
	Trainee* pTrainee1 = *(Trainee**)pVoidTrainee1;
	Trainee* pTrainee2 = *(Trainee**)pVoidTrainee2;
	return compareDate(&pTrainee1->person->dateOfBirth, &pTrainee2->person->dateOfBirth);
}

void printTrainee(const void* pTrainee)
{
	Trainee* tTrainee = *(Trainee**)pTrainee;
	printf("Trainee details:\n");
	printPerson(tTrainee->person);
	printf("Subscription Price: % -20d\n", tTrainee->subscriptionPrice);
}

//binary file
int  writeTraineesToFile(const Trainee** traineeArr, const int count, FILE* fp)
{
	if (fwrite(&count, sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < count; i++)
	{
		if (!writeTraineeToFile(traineeArr[i], fp))
			return 0;
	}
	return 1;
}

//binary file
int  writeTraineeToFile(const Trainee* pTrainee, FILE* fp)
{
	if (writePersonToFile(pTrainee->person, fp) != 1 ||
		fwrite(&pTrainee->subscriptionPrice, sizeof(int), 1, fp) != 1)
		return 0;
	return 1;
}

//binary file
int readTraineesFromFile(Trainee** traineeArr, int count, FILE* fp)
{
	if (!traineeArr || !fp)
		return 0;
	Trainee* pTrainee;
	for (int i = 0; i < count; i++)
	{
		pTrainee = (Trainee*)calloc(1, sizeof(Trainee));
		if (!pTrainee)
		{
			ERROR_ALLOCATION_GENERAL
		}
		if (readTraineeFromFile(pTrainee, fp) != 1)
			return 0;
		traineeArr[i] = pTrainee;
	}
	return 1;
}
//binary file
int  readTraineeFromFile(Trainee* pTrainee, FILE* fp)
{
	if (!pTrainee || !fp)
		return 0;
	pTrainee->person = (Person*)malloc(sizeof(Person));
	if (!pTrainee->person)
	{
		ERROR_ALLOCATION_GENERAL
	}
	if (readPersonFromFile(pTrainee->person, fp) != 1)
	{
		free(pTrainee->person);
		return 0;
	}

	if (fread(&pTrainee->subscriptionPrice, sizeof(int), 1, fp) != 1)
	{
		free(pTrainee->person);
		return 0;
	}

	return 1;
}

//text file
int  saveTraineesText(const Trainee** TraineeArr, int count, FILE* fp)
{
    fprintf(fp, "%d\n", count);
    for (int i = 0; i < count; i++)
    {
        if (!saveTraineeText(TraineeArr[i], fp))
        {
            return 0;
        }
    }
    return 1;
}

//text file
int  saveTraineeText(const Trainee* pTrainee, FILE* fp)
{
	if (!pTrainee || !fp)
		return 0;

	if (savePersonText(pTrainee->person, fp) != 1)
		return 0;

	fprintf(fp, "%d\n", pTrainee->subscriptionPrice);
	return 1;
}

//text file
int  loadTraineesText(Trainee** traineeArr, int count, FILE* fp)
{
    Trainee* pTrainee;
    for (int i = 0; i < count; i++)
    {
        pTrainee = (Trainee*)calloc(1, sizeof(Trainee));
        if (!pTrainee)
        {
            ERROR_ALLOCATION_GENERAL
        }
        if (!loadTraineeText(pTrainee, fp))
        {
            printf("Error reading trainer\n");
            return 0;
        }
        traineeArr[i] = pTrainee;
    }
    return 1;
}

//text file
int  loadTraineeText(Trainee* pTrainee, FILE* fp)
{
	if (!pTrainee || !fp)
		return 0;
	pTrainee->person = (Person*)malloc(sizeof(Person));
	if (!pTrainee->person)
	{
		ERROR_ALLOCATION_GENERAL
	}
	if (loadPersonText(pTrainee->person, fp) != 1)
	{
		free(pTrainee->person);
		return 0;
	}

	fscanf(fp, "%d", &pTrainee->subscriptionPrice);
	fgetc(fp);
	return 1;
}


