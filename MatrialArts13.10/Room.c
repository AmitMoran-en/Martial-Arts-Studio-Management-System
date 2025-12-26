#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Room.h"
#include "General.h"
#include "FileHelper.h"

int		initRoomNoCode(Room* pRoom)
{
	printf("Enter room number (between %d and %d): ", MIN_ROOM_NUMBER, MAX_ROOM_NUMBER);
	int roomNum;
	scanf("%d", &roomNum);

	if (roomNum < MIN_ROOM_NUMBER || roomNum > MAX_ROOM_NUMBER) {
		printf("Invalid room number. Please enter a number between %d and %d.\n", MIN_ROOM_NUMBER, MAX_ROOM_NUMBER);
		return 0;
	}
	pRoom->number = roomNum;
	return 1;
}

int		isSameRoom(const Room* pRoom1, const Room* pRoom2) 
{
	if (!pRoom1 || !pRoom2)
		return 0;
	if (strcmp(pRoom1->entryCode, pRoom2->entryCode) == 0)
		return 1;

	return 0;
}

int		isRoomCode(const Room* pRoom1, const char* code)
{
	if (!pRoom1)
		return 0;
	if (strcmp(pRoom1->entryCode, code) == 0) {
		return 1;
	}
	return 0;
}

int   getRoomNum(Room* pRoom)
{
	if (pRoom == NULL) {
		return 0; 
	}
	return pRoom->number;
}

void getRoomEntryCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter room entry code  - %d letters\t", CODE_LEN);
		myGets(temp, MAX_STR_LEN, stdin);
		if (strlen(temp) != CODE_LEN)
		{
			printf("code should be %d letters\n", CODE_LEN);
			ok = 0;
		}
	} while (!ok);

	strcpy(code, temp);
}


void printRoom(const void* pVoidRoom)
{
    const Room* pRoom = (const Room*) pVoidRoom;

    if (pRoom == NULL) {
        printf("Error: Invalid room pointer\n");
        return;
    }

    printf("Room number:%-20d Entry code: %s\n", pRoom->number, pRoom->entryCode);
}


//binary file
int writeRoomToFile(const Room* pRoom, FILE* fp)
{
	if (!pRoom || !fp)
		return 0;

	if (!writeCharsToFile(pRoom->entryCode, CODE_LEN, fp, "Error writing entry code\n")
		|| fwrite(&(pRoom->number), sizeof(int), 1, fp) != 1)
		return 0;
	return 1;
}

//binary file
int readRoomFromFile(Room* pRoom, FILE* fp)
{
	if (!pRoom || !fp)
		return 0;

	if (!readCharsFromFile(pRoom->entryCode, CODE_LEN, fp, "Error read entry code\n")
		|| fread(&pRoom->number, sizeof(int), 1, fp) != 1)
		return 0;
	pRoom->entryCode[CODE_LEN] = '\0';
	return 1;
}

//text file
int		saveRoomToText(const Room* pRoom, FILE* fp)
{
	if (pRoom == NULL)
	{
		return 0;
	}
	fprintf(fp, "%d\n", pRoom->number);
	fprintf(fp, "%s\n", pRoom->entryCode);
	return 1;
}

//text file
int		loadRoomFromText(Room* pRoom, FILE* fp)
{
	if (!pRoom) {
		return 0;
	}
	fscanf(fp, "%d", &pRoom->number);
	fgetc(fp);
	myGets(pRoom->entryCode, CODE_LEN + 1 , fp);
	
	return 1;
}


