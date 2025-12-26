#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Equipment.h"
#include "Studio.h"
#include "General.h"
#include "FileHelper.h"


int	initStudio(Studio* pStudio)
{
	pStudio->name = getStrExactName("Please enter the studio name:\n");
	pStudio->country = getStrExactName("Please enter the studio country:\n");
	pStudio->roomManager = (RoomManager*)malloc(sizeof(RoomManager));
	if (!pStudio->roomManager)
	{
		ERROR_ALLOCATION_GENERAL
	}
	initManager(pStudio->roomManager);
	pStudio->trainersCount = 0;
	pStudio->traineesCount = 0;
	pStudio->allTrainersArr = NULL;
	pStudio->allTraineesArr = NULL;
	pStudio->SNequipmentArr = NULL;	
	pStudio->allTrainingsArr = NULL;
	pStudio->trainingsCount = 0;
	pStudio->traineeSortOpt = 0;

	return 1;
}	

int addTraining(Studio* pStudio)
{
	int check = getRoomCount(pStudio->roomManager);
	if (check == 0 || pStudio->trainersCount == 0)
	{
		printf("No rooms and trainers available.\n");
		return 0;
	}
	Training tr;
	int choose;
	initTrainingNameAndDate(&tr);
	initTrainingRoom(&tr, pStudio->roomManager);
	DROPPED_LINE
	printf("Please choose a trainer from the list below by the number of appearances in the list:\n");
	generalPrintArrFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), printTrainer);
	scanf("%d", &choose);
	initTrainingTrainer(&tr, pStudio->allTrainersArr[choose - 1]);
	pStudio->allTrainingsArr[pStudio->trainingsCount] = tr;
	pStudio->trainingsCount++;
	printf("The training have added succesfully.\n");
	return 1;
}

int addTrainer(Studio* pStudio)
{
	Trainer* tr = (Trainer*)malloc(sizeof(Trainer));
	if (!tr)
	{
		ERROR_ALLOCATION_GENERAL
	}
	if (!initTrainer(tr))
	{
		return 0;
	}
	pStudio->SNequipmentArr = addTrainerEquipmentSN(pStudio->SNequipmentArr, pStudio->trainersCount, tr);
	if (!pStudio->SNequipmentArr)
	{
		return 0;
	}
	int index = searchElementInArray(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), &tr, compareTrainerByID);
	if (index == -1)
	{
		pStudio->allTrainersArr = (Trainer**)realloc(pStudio->allTrainersArr,
			sizeof(Trainer*) * (size_t)(pStudio->trainersCount + 1));
		if (!pStudio->allTrainersArr)
		{
			freeTrainer(tr);
			free(tr);
			ERROR_ALLOCATION_GENERAL
		}
		pStudio->allTrainersArr[pStudio->trainersCount++] = tr;
		printf("The trainer have added succesfully.\n");
		return 1;
	}
	freeTrainer(tr);
	free(tr);
	printf("The trainer is already in the system.\n");
	return 0;
}

int addTrainee(Studio* pStudio)
{
	Trainee* trn = (Trainee*)malloc(sizeof(Trainee));
	if (!trn)
	{
		ERROR_ALLOCATION_GENERAL
	}
	if (!initTrainee(trn))
	{
		return 0;
	}
	int index = searchElementInArray(pStudio->allTraineesArr, pStudio->traineesCount, sizeof(Trainee*), &trn, compareTraineeByID);
	if (index == -1)
	{
		pStudio->allTraineesArr = (Trainee**)realloc(pStudio->allTraineesArr,
			sizeof(Trainee*) * (size_t)(pStudio->traineesCount + 1));
		if (!pStudio->allTraineesArr)
		{
			freeTrainee(trn);
			free(trn);
			ERROR_ALLOCATION_GENERAL
		}
		pStudio->allTraineesArr[pStudio->traineesCount++] = trn;
		printf("The trainee have added succesfully.\n");
		return 1;
	}
	printf("The trainee is already in the system.\n");
	freeTrainee(trn); 
	free(trn);
	return 0;
}



double calculateAverageSeniority(const Studio* pStudio) {
	if (pStudio == NULL || pStudio->trainersCount == 0 || pStudio->allTrainersArr == NULL) {
		return 0; // Return 0 if there are no trainers or the studio is not initialized
	}

	double totalSeniority = 0;
	for (int i = 0; i < pStudio->trainersCount; i++) {
		totalSeniority += pStudio->allTrainersArr[i]->seniority;
	}

	return totalSeniority / pStudio->trainersCount;
}

Trainer* findMostSeniorTrainer(const Studio* pStudio)
{
	if (pStudio == NULL || pStudio->trainersCount == 0 || pStudio->allTrainersArr == NULL) {
		return NULL;
	}

	Trainer* mostSeniorTrainer = pStudio->allTrainersArr[0];

	for (int i = 1; i < pStudio->trainersCount; i++) {
		if (pStudio->allTrainersArr[i]->seniority > mostSeniorTrainer->seniority) {
			mostSeniorTrainer = pStudio->allTrainersArr[i];
		}
	}

	return mostSeniorTrainer;
}


void sortTrainees(Studio* pSt)
{
	pSt->traineeSortOpt = showSortMenu();
	int(*compare)(const void* air1, const void* air2) = NULL;

	switch (pSt->traineeSortOpt)
	{
	case eID:
		compare = compareTraineeByID;
		break;
	case eSubscriptionPrice:
		compare = compareTraineeBySubscriptionPrice;
		break;
	case eAge:
		compare = compareTraineeByAge;
		break;
	
	}

	if (compare != NULL)
		qsort(pSt->allTraineesArr, pSt->traineesCount, sizeof(Trainee*), compare);
}

eSortOption showSortMenu()
{
	int opt;
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 1; i < eNofSortOpt; i++)
			printf("Enter %d for %s\n", i, sortOptStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >= eNofSortOpt);

	return (eSortOption)opt;
}

//Function that finds Trainee based on user sort choice
void findTrainee(const Studio* pSt)
{
	int(*compare)(const void* trainee1, const void* trainee2) = NULL;
	Trainee e = { 0 };
	Person p = { 0 };
	e.person = &p;
	Trainee* pEmp = &e;

	switch (pSt->traineeSortOpt)
	{
	case eID:
		printf("%s\t", "ID:");
		getPersonID(e.person->id);
		compare = compareTraineeByID;
		break;

	case eAge:
		getCorrectDate(&e.person->dateOfBirth);
		compare = compareTraineeByAge;
		break;

	case eSubscriptionPrice:
		printf("%s\t", "Subscription price:");
		getSubscriptionPrice(pEmp);
		compare = compareTraineeBySubscriptionPrice;
		break;
	}
	if (compare != NULL)
	{
		Trainee* pE = bsearch(&pEmp, pSt->allTraineesArr, pSt->traineesCount, sizeof(Trainee*), compare);
		if (pE == NULL)
			printf("Trainee was not found\n");
		else {
			printf("Trainee found, ");
			printTrainee(pE);
		}
	}
	else {
		printf("The search cannot be performed, array not sorted\n");
	}
}
void printHighestSubscriptionTraineeDetails(const Studio* pStudio)
{
	if (pStudio == NULL || pStudio->traineesCount == 0 || pStudio->allTraineesArr == NULL) {
		printf("No trainees found in the studio.\n");
		return;
	}

	Trainee* highestSubscriptionTrainee = pStudio->allTraineesArr[0]; // Initialize with the first trainee
	int highestSubscriptionPrice = highestSubscriptionTrainee->subscriptionPrice;

	for (int i = 1; i < pStudio->traineesCount; i++) {
		// Iterate through the trainees array and update highestSubscriptionTrainee if found a trainee with higher subscription price
		if (pStudio->allTraineesArr[i]->subscriptionPrice > highestSubscriptionPrice) {
			highestSubscriptionTrainee = pStudio->allTraineesArr[i];
			highestSubscriptionPrice = highestSubscriptionTrainee->subscriptionPrice;
		}
	}

	printf("Highest Subscription Trainee Details:\n");
	printTrainee(&highestSubscriptionTrainee);
}
void printStudio(const void* pSt)
{
	const Studio* tStudio = (Studio*)pSt;
	printf("Studio name:%-20s ", tStudio->name);
	printf("in country: %-20s\n", tStudio->country);
	DROPPED_LINE
		DROPPED_LINE
		printTrainers(tStudio);
	DROPPED_LINE
		printTrainees(tStudio);
	DROPPED_LINE
		printTrainings(tStudio);
	DROPPED_LINE
		printRooms(tStudio->roomManager);
}

void printMostSeniorTrainerDetails(const Studio* pStudio)
{
	Trainer* mostSeniorTrainer = findMostSeniorTrainer(pStudio);
	if (mostSeniorTrainer != NULL) {
		printf("Most Senior Trainer Details:\n");
		printTrainer(&mostSeniorTrainer);

		double averageSeniority = calculateAverageSeniority(pStudio);
		double seniorityDifference = mostSeniorTrainer->seniority - averageSeniority;

		printf("Average seniority of all trainers: %.2f months\n", averageSeniority);
		printf("Difference between most senior trainer and average: %.2f months\n", seniorityDifference);
	}
	else {
		printf("No trainers found.\n");
	}
}

void    printTrainings(const Studio* pStudio)
{
	if (pStudio == NULL || pStudio->trainingsCount == 0) {
		printf("No trainings available.\n");
		return;
	}
	printf("Number of trainings in the studio: %-20d\n", pStudio->trainingsCount);
	DROPPED_LINE
		generalPrintArrFunction(pStudio->allTrainingsArr, pStudio->trainingsCount, sizeof(Training), printTraining);
}

void printTrainers(const Studio* pStudio) {
	if (pStudio == NULL || pStudio->trainersCount == 0) {
		printf("No trainers available.\n");
		return;
	}

	printf("Number of trainers in the studio: %-20d\n", pStudio->trainersCount);
	DROPPED_LINE
	generalPrintArrFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), printTrainer);
}


void    printTrainees(const Studio* pStudio)
{
	if (pStudio == NULL || pStudio->traineesCount == 0) {
		printf("No trainees available.\n");
		return;
	}

	printf("Number of trainees in the studio: %-20d\n", pStudio->traineesCount);
	DROPPED_LINE
	generalPrintArrFunction(pStudio->allTraineesArr, pStudio->traineesCount, sizeof(Trainee*), printTrainee);
}

void    freeStudio(Studio* pStudio)
{
	free(pStudio->name);
	free(pStudio->country);
	freeManager(pStudio->roomManager);
	free(pStudio->roomManager);
	//free Trainers
	generalArrayFunction(pStudio->allTrainersArr, pStudio->trainersCount, sizeof(Trainer*), freeTrainer);
	free(pStudio->allTrainersArr);
	//free Trainees
	generalArrayFunction(pStudio->allTraineesArr, pStudio->traineesCount, sizeof(Trainee*), freeTrainee);
	free(pStudio->allTraineesArr);
	//free SNequipments
	free(pStudio->SNequipmentArr);
	//free trainings
	generalArrayFunction(pStudio->allTrainingsArr, pStudio->trainingsCount, sizeof(Training), freeTraining);
	free(pStudio->allTrainingsArr);
}