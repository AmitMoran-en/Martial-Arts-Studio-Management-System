#ifndef __EQUIPMENT__
#define __EQUIPMENT__

#define SERIAL_LEN 3
#define SERIAL_MAX 999
#define SERIAL_MIN 0

typedef unsigned char BYTE;

typedef enum {
    eNew, eUsed,eOld, eDamaged, eNofConditionTypes
} eEquipmentCondition;

typedef enum {
	eKarate, eJudo, eBoxing, eMMA, eBJJ, eNofMartialArts
} eMartialArts;

typedef struct
{
	int                 serialNumber;
	eEquipmentCondition condition;
	eMartialArts		martialArtsType;
}Equipment;

void				initEquipmentNoSerialNumber(Equipment* pEquipment);
eMartialArts        getMartialArtsType();
eEquipmentCondition getEquipmentCondition();
const char*         getMartialArtsTypeStr(int type);
Equipment*          getEquipmentFromArr(Equipment* equipmentArr, int count);
void				getEquipmentSerialNumber(const int* SNequipmentArr, int equipmentCount, int* serialNumber);
Equipment*          findEquipmentBySerialNumber(Equipment* equipmentArr, int count, int serialNumber);
int					isSerialNumberUnique(const int* SNequipmentArr, int count, const int serialNumber);
void                printEquipment(const void* pEquipment);
void                genericPrintEquipment(void* pEquipment);

int                 writeEquipmentToFile(const Equipment* pEquipment, FILE* fp);
int                 readEquipmentFromFile(Equipment* pEquipment, FILE* fp);
int                 saveEquipmentText(const Equipment* pEquipment, FILE* fp);
int                 loadEquipmentText(Equipment* pEquipment, FILE* fp);

#endif
