#ifndef __TRAINER__
#define __TRAINER__

#include "Person.h"
#include "Equipment.h"

typedef struct
{
	int         seniority;
	Equipment   equipment;
	Person*     person;
}Trainer;

int			initTrainer(Trainer* pTrainer); 
void		initTrainerNoPerson(Trainer* pTrainer);
int*		addTrainerEquipmentSN(int* SNequipmentArr, int count, Trainer* pTrainer);
int			compareTrainerByID(const void* pTrainer1, const void* pTrainer2);
Trainer*	getTrainerByID(Trainer** trainerArr, int count, char* id);
void		printTrainer(const void* pTrainer);
void		freeTrainer(void* pTrainer);

int			readTrainersFromFile(Trainer** trainerArr, int count, FILE* fp);
int			readTrainerFromFile(Trainer* pTrainer, FILE* fp);
int			writeTrainerToFile(const Trainer* pTrainer, FILE* fp);
int			writeTrainersToFile(const Trainer** TrainerArr, int count, FILE* fp);
int			saveTrainersText(const Trainer** TrainerArr, int count, FILE* fp);
int			saveTrainerText(const Trainer* pTrainer, FILE* fp);
int			loadTrainersText(Trainer** trainerArr, int count, FILE* fp);
int			loadTrainerText(Trainer* pTrainer, FILE* fp);

#endif
