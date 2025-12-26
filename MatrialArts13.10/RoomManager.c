#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "RoomManager.h"
#include "General.h"
#include "FileHelper.h"

int	initManager(RoomManager* pManager)
{
	if (!L_init(&pManager->RoomList))
		return 0;

	return 1;
}

int	addRoom(RoomManager* pManager)
{
	Room* pRoom = (Room*)calloc(1, sizeof(Room));
	if (!pRoom)
		return 0;

	if (!initNewRoom(pRoom, pManager))
		return 0;

	return insertNewRoomToList(&pManager->RoomList, pRoom);
}

int		insertNewRoomToList(LIST* pRoomList, Room* pRoom)
{
	NODE* tmp = &(pRoomList->head);

	while (tmp->next != NULL ) {
		if (strcmp(pRoom->entryCode, ((Room*)(tmp->next->key))->entryCode) < 0)
			break;
		tmp = tmp->next;
	}

    if (L_insert(tmp, pRoom) == NULL) {
            return 0;
    }
    return 1; 
}


int  initNewRoom(Room* pRoom, RoomManager* pManager)
{
	while (1)
	{
		getRoomEntryCode(pRoom->entryCode);
		if (checkUniqeEntryCode(pRoom->entryCode, pManager))
			break;

		printf("This ENTRY code already in use - enter a different number\n");
	}

	return initRoomNoCode(pRoom);
}

Room* findRoomByEntryCode(const RoomManager* pManager, const char* code)
{
	if (!pManager) 
		return NULL;

	NODE* currentNode = pManager->RoomList.head.next; // Start from the first node after the head
	while (currentNode != NULL)
	{
		// Ensure current node is not empty before accessing its key
		if (currentNode->key != NULL)
		{
			Room* currentRoom = (Room*)currentNode->key;
			if (isRoomCode(currentRoom, code))
				return currentRoom;
		}
		currentNode = currentNode->next; // Move to the next node
	}
	return NULL;
}

int checkUniqeEntryCode(const char* Code, const RoomManager* pManager)
{
	if (getRoomCount(pManager) != 0) {
		Room* pRoom = findRoomByEntryCode(pManager, Code);
		if (pRoom != NULL)
			return 0;
	}
	return 1;
}



int		getRoomCount(const RoomManager* pManager)
{
	int count = 0;
	const NODE* pN = &pManager->RoomList.head; //first Node

	while (pN->next != NULL)
	{
		count++;
		pN = pN->next;
	}
	return count;
}

void	printRooms(const RoomManager* pManager)
{
	printf("Number of rooms in the studio: %-20d\n", getRoomCount(pManager));
	L_print(&pManager->RoomList, printRoom);

}


//binary file
int writeManagerToFile(const RoomManager* pManager, FILE* fp)
{
	int len = getRoomCount(pManager);
	if (fwrite(&len, sizeof(int), 1, fp) != 1)
		return 0;
	NODE* pNode = pManager->RoomList.head.next;
	while (pNode != NULL)
	{
		if (!writeRoomToFile(((Room*)(pNode->key)), fp))
			return 0;
		pNode = pNode->next;
	}
	return 1;
}

//binary file
int readManagerToFile(RoomManager* pManager, FILE* fp)
{
	L_init(&pManager->RoomList);
    int count;
    Room* tRoom;
    NODE* pNode = &pManager->RoomList.head;
    if (fread(&count, sizeof(int), 1, fp) != 1)
    {
        printf("Failed to read the size of the list\n");
		free(pManager);
        return 0;
    }
    for (int i = 0; i < count; i++)
    {
		tRoom = (Room*)calloc(1, sizeof(Room));
		if (!tRoom)
		{
			free(pManager);
			ERROR_ALLOCATION_GENERAL
		}
        if (!readRoomFromFile(tRoom, fp))
        {
            printf("Unable to load the room list\n");
			freeManager(pManager);
			free(pManager);
            return 0;
        }
        L_insert(pNode, tRoom);
        pNode = pNode->next;
    }
    return 1;
    
}

//text file
int saveManagerToText(const RoomManager* pManager, FILE* fp)
{
    int count = getRoomCount(pManager);
    fprintf(fp, "%d\n", count);
    if (count > 0)
    {
        NODE* pNode = pManager->RoomList.head.next;
        Room* pTemp;

        while (pNode != NULL)
        {
            pTemp = (Room*)pNode->key;
            if (!saveRoomToText(pTemp, fp))
            {
                printf("Failed to write room\n");
                return 0;
            }
            pNode = pNode->next;
        }
    }
    return 1;
}

//text file
int loadManagerToText(RoomManager* pManager, FILE* fp)
{
    L_init(&pManager->RoomList);
    int count;
    fscanf(fp, "%d", &count);
    fgetc(fp);
    
    Room* pRoom;
    for (int i = 0; i < count; i++)
    {
        pRoom = (Room*)calloc(1, sizeof(Room));
        if (!pRoom)
		{
			freeManager(pManager);
			free(pManager);
			ERROR_ALLOCATION_GENERAL
		}
        if (!loadRoomFromText(pRoom, fp))
        {
            printf("Error loading room from file\n");
			free(pRoom);
            freeManager(pManager);
			free(pManager);
            return 0;
        }
        insertNewRoomToList(&pManager->RoomList, pRoom);
    }
    return 1;
}



void	freeManager(RoomManager* pManager)
{
	L_free(&pManager->RoomList, free);
}
