#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Equipment.h"
#include "General.h"
#include "FileHelper.h"
#include "Studio.h"

static const char* equipmentConditionStr[eNofConditionTypes]
= { "New", "Used", "Old", "Damaged" };

static const char* MartialArtsTypeStr[eNofMartialArts]
= { "Karate", "Judo", "Boxing", "MMA", "BJJ" };

void initEquipmentNoSerialNumber(Equipment* pEquipment)
{
	pEquipment->martialArtsType = getMartialArtsType();
	pEquipment->condition = getEquipmentCondition();
}

eMartialArts getMartialArtsType()
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter the number of the martial art in which this equipment can be used\n");
		for (int i = 0; i < eNofMartialArts; i++)
			printf("%d for %s\n", i, MartialArtsTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofMartialArts);
	getchar();
	return (eMartialArts)option;
}

eEquipmentCondition getEquipmentCondition()
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter the number describing the condition of the equipment\n");
		for (int i = 0; i < eNofConditionTypes; i++)
			printf("%d for %s\n", i, equipmentConditionStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofConditionTypes);
	getchar();
	return (eEquipmentCondition)option;
}

const char* getMartialArtsTypeStr(int type)
{
	if (type < 0 || type >= eNofMartialArts)
		return NULL;
	return MartialArtsTypeStr[type];
}

void getEquipmentSerialNumber(const int* SNequipmentArr, int trainersCount, int* serialNumber)
{
	int res = 0;
	do
	{
		printf("Enter sirial number - valid number between %d to %d\t", SERIAL_MIN, SERIAL_MAX);
		scanf("%d", serialNumber);
		if (*serialNumber < SERIAL_MIN || *serialNumber > SERIAL_MAX)
			printf("The number inserted is out of range!\n");
		else if (!isSerialNumberUnique(SNequipmentArr, trainersCount, *serialNumber))
			printf("The serial number is already used by another equipment. Please choose a different one!\n");
		else
			res = 1;
	} while (!res);
}

int	isSerialNumberUnique(const int* SNequipmentArr, int count, const int serialNumber)
{
	for (int i = 0; i < count; i++)
	{
		if (SNequipmentArr[i] - serialNumber == 0)
			return 0;
	}
	return 1;
}

Equipment* findEquipmentBySerialNumber( Equipment* equipmentArr, int count, int sNumber)
{
	for (int i = 0; i < count; i++) 
	{
		if (equipmentArr[i].serialNumber - sNumber == 0)
			return &equipmentArr[i];
	}
	return NULL;
}

Equipment* getEquipmentFromArr(Equipment* equipmentArr, int count)
{
	int i = 0;
	if (count == 0)
	{
		printf("No equipment in the system\n");
		return NULL;
	}
	printf("All the equipment in the system:\n");
	for (int i = 0; i < count; i++)
	{
		printf("%d.  ", i + 1);
		printEquipment(&equipmentArr[i]);
	}
	do {
		printf("Please enter the number of the equipment:\n");
		scanf("%d", &i);
		if (i <= 0 || i > count)
		{
			printf("Plesae choose a number from 1 - %d\n", count);
			i = 0;
		}
	} while (!i);
	return &equipmentArr[i - 1];
}

void printEquipment(const void* pEquipment)
{
	Equipment* tEquipment = (Equipment*)pEquipment; 
	printf("serial number: %d, condition: %s, martial arts type: %s\n",
		tEquipment->serialNumber, equipmentConditionStr[tEquipment->condition], MartialArtsTypeStr[tEquipment->martialArtsType]);
}

void genericPrintEquipment(void* pPl)
{
	const Equipment* pEquipment = (const Equipment*)pPl;
	printEquipment(pEquipment);
}

int writeEquipmentToFile(const Equipment* pEquipment, FILE* fp)
{
    BYTE equipment[2];
    equipment[0] = (pEquipment->serialNumber >> 2) & 0xFF;  // Upper 8 bits of serial number
    equipment[1] = ((pEquipment->serialNumber & 0x03) << 6) // Remaining 2 bits of serial number shifted to the top of byte
                      | (pEquipment->condition << 3)            // Shift condition bits up by 3 positions
                      | (pEquipment->martialArtsType);          // Lowest 3 bits

    
    if (fwrite(equipment, sizeof(BYTE), 2, fp) != 2)
    {
        return 0;
    }
    return 1;

}

int readEquipmentFromFile(Equipment* pEquipment, FILE* fp)
{
    BYTE equipment[2];
    if (fread(equipment, sizeof(char), 2, fp) != 2)
        return 0;

    pEquipment->serialNumber = ((equipment[0] << 2) | (equipment[1] >> 6)) & 0x3FF;  // Extract 10 bits for serial number
    pEquipment->condition = (eEquipmentCondition)((equipment[1] >> 3) & 0x07);      // Extract 3 bits for condition
    pEquipment->martialArtsType = (eMartialArts)(equipment[1] & 0x07);               // Extract 3 bits for martial arts type
    return 1;
}

int saveEquipmentText(const Equipment* pEquipment, FILE* fp)
{
	if (!pEquipment)
		return 0;
	fprintf(fp, "%d\n", pEquipment->serialNumber);
	fprintf(fp, "%d\n", pEquipment->martialArtsType);
	fprintf(fp, "%d\n", pEquipment->condition);
	return 1;
}

int loadEquipmentText(Equipment* pEquipment, FILE* fp)
{
	if (!pEquipment)
		return 0;
	fscanf(fp, "%d", &pEquipment->serialNumber);
	fgetc(fp);
	fscanf(fp, "%d", &pEquipment->martialArtsType);
	fgetc(fp);
	fscanf(fp, "%d", &pEquipment->condition);
	fgetc(fp);
	return 1;
}
