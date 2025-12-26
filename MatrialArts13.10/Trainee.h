#ifndef __TRAINEE__
#define __TRAINEE__

#include "Person.h"

typedef struct
{
	int     subscriptionPrice;
	Person* person;
}Trainee;

int  initTrainee(Trainee* pTrainee);
void initTraineeNoPerson(Trainee* pTrainee);
void freeTrainee(void* pVoidTrainee);
void getSubscriptionPrice(Trainee* pTrainee);
int	 compareTraineeBySubscriptionPrice(const void* pVoidTrainee1, const void* pVoidTrainee2);
int  compareTraineeByID(const void* pVoidTrainee1, const void* pVoidTrainee2);
int  compareTraineeByAge(const void* pVoidTrainee1, const void* pVoidTrainee2);
void printTrainee(const void* pTrainee);


int  writeTraineesToFile(const Trainee** traineeArr, const int count, FILE* fp);
int  writeTraineeToFile(const Trainee* pTrainee, FILE* fp);
int  readTraineesFromFile(Trainee** traineeArr, int count, FILE* fp);
int  readTraineeFromFile(Trainee* pTrainee, FILE* fp);
int  saveTraineesText(const Trainee** TraineeArr, int count, FILE* fp);
int  saveTraineeText(const Trainee* pTrainee, FILE* fp);
int  loadTraineesText(Trainee** traineeArr, int count, FILE* fp);
int  loadTraineeText(Trainee* pTrainee, FILE* fp);

#endif
