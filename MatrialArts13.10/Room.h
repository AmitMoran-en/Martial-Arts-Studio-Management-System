#ifndef __ROOM__
#define __ROOM__

#define MIN_ROOM_NUMBER 1
#define MAX_ROOM_NUMBER 999
#define CODE_LEN 4

typedef struct
{
	int  number;
	char entryCode[CODE_LEN +1];
}Room;

int  initRoomNoCode(Room* pRoom);
int  isSameRoom(const Room* pRoom1, const Room* pRoom2);
int  isRoomCode(const Room* pRoom1, const char* code);
int	 getRoomNum(Room* pRoom);
void getRoomEntryCode(char* code);
void printRoom(const void* pVoidRoom);

int  writeRoomToFile(const Room* pRoom, FILE* fp);
int  readRoomFromFile(Room* pRoom, FILE* fp);
int  saveRoomToText(const Room* pRoom, FILE* fp);
int  loadRoomFromText(Room* pRoom, FILE* fp);



#endif
