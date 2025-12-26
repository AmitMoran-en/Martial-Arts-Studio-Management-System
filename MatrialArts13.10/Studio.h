#ifndef __STUDIO__
#define __STUDIO__

#include "RoomManager.h"
#include "Trainer.h"
#include "Trainee.h"
#include "Training.h"

typedef enum { eNone, eID, eSubscriptionPrice, eAge, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt] = {
	"None","ID", "SubscriptionPrice", "Age" };

typedef struct
{
	char*           name;
	char*           country;
	RoomManager*    roomManager;
	Trainer**       allTrainersArr;
	int             trainersCount; // also used as an SNequipment count
	Trainee**       allTraineesArr;
	int             traineesCount;
	int*			SNequipmentArr;
	Training*       allTrainingsArr;
	int             trainingsCount;	
	eSortOption	    traineeSortOpt;
}Studio;

int		    initStudio(Studio* pStudio);
int			addTraining(Studio* pStudio);
int		    addTrainee(Studio* pStudio);
int		    addTrainer(Studio* pStudio);
double		calculateAverageSeniority(const Studio* pStudio);
Trainer*    findMostSeniorTrainer(const Studio* pStudio);
void	    sortTrainees(Studio* pSt);
eSortOption showSortMenu();
void	    findTrainee(const Studio* pSt);
void	    printHighestSubscriptionTraineeDetails(const Studio* pStudio);
void	    printStudio(const void* pSt);
void	    printMostSeniorTrainerDetails(const Studio* pStudio);
void		printTrainings(const Studio* pStudio);
void        printTrainers(const Studio* pStudio);
void        printTrainees(const Studio* pStudio);
void		freeStudio(Studio* pStudio);

#endif
