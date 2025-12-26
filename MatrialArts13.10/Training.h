#ifndef __TRAINING__
#define __TRAINING__

#include "Trainer.h"
#include "RoomManager.h"

typedef struct
{
	Date        trainingDate;
	char*       name;
	Room*       room;
	Trainer*    trainer;
}Training;

int				initTraining(Training* pTraining, RoomManager* pRoomManager, Trainer* pTrainer);
void			initTrainingNameAndDate(Training* pTraining);
void			initTrainingTrainer(Training* pTraining, Trainer* pTrainer);
void			initTrainingRoom(Training* pTraining, RoomManager* pRoomManager);
int				compareTrainingByName(const void* pVoidTraining1, const void* pVoidTraining2);
int				compareTrainingByDate(const void* pVoidTraining1, const void* pVoidTraining2);
void			printTraining(const Training* pTraining);
void			freeTraining(Training* pTraining);

int				writeTrainingsToFile(const Training* trainingArr, int count, FILE* fp);
int				writeTrainingToFile(const Training* pTraining, FILE* fp);	
int				readTrainingsFromFile(Training* trainingArr, int countTraining, Trainer** allTrainersArr, int countTrainers, RoomManager* pManager, FILE* fp);
int				readTrainingFromFile(Training* pTraining, Trainer** allTrainersArr, int count, RoomManager* pManager, FILE* fp);
int				saveTrainingsText(const Training* trainingArr, int count, FILE* fp);
int				saveTrainingText(const Training* pTraining, FILE* fp);
int				loadTrainingsText(Training* trainingArr, int countTraining, Trainer** allTrainersArr, int countTrainers, RoomManager* pManager, FILE* fp);
int				loadTrainingText(Training* pTraining, Trainer** allTrainersArr, int count, RoomManager* pManager, FILE* fp);
#endif
