#ifndef __ROOM_MANAGER__
#define __ROOM_MANAGER__

#include "List.h"
#include "Room.h"

typedef struct {
    LIST RoomList;
} RoomManager;

int     initManager(RoomManager* pManager);
int     addRoom(RoomManager* pManager);
int     initNewRoom(Room* pRoom, RoomManager* pManager);
int     insertNewRoomToList(LIST* pList, Room* pRoom);
Room*   findRoomByEntryCode(const RoomManager* pManager, const char* code);
int     checkUniqeEntryCode(const char* Code, const RoomManager* pManager);
void    printRooms(const RoomManager* pManager);
int     getRoomCount(const RoomManager* pManager);
void    freeManager(RoomManager* pManager);

int     writeManagerToFile(const RoomManager* pManager, FILE* fp);
int     readManagerToFile(RoomManager* pManager, FILE* fp);
int     saveManagerToText(const RoomManager* pManager, FILE* fp);
int     loadManagerToText(RoomManager* pManager, FILE* fp);


#endif
