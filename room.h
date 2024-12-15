#pragma once
#include "mob.h"
#include "item.h"
struct Room_s{
	int mobCtr;
	Mob* mobs;	
	Item reward;
	int roomType;
	bool isBossRoom;
}Room_default = {1,0,0,0};

typedef struct Room_s Room;

Room roomGenerator(int diffuculty,bool isBossRoom){
	Room room = Room_default;
	room.mobCtr += isBossRoom ? 1 : (diffuculty%5);
	room.mobs = isBossRoom ? bossGenerator(diffuculty) :  mobGenerator(room.mobCtr,diffuculty);
	room.reward = isBossRoom ? itemGenerator(diffuculty) : Item_default;
	room.roomType = isBossRoom ? 3 : rand() % 3;
	room.isBossRoom = isBossRoom;
	return room;
}

void giveRoomInformation(Room r){
       	char* roomDesc;
	switch(r.roomType){
		case 0:
			roomDesc = "Room desc 1";
			break;
		case 1:
			roomDesc = "Room desc 2";
			break;
		case 2:
			roomDesc = "Room desc 3";
			break;
		case 3:
			roomDesc = "Boss Room";

	}
	printf("%s\n",roomDesc);
	if(!r.isBossRoom){
		printf("There are %d monsters here\n",r.mobCtr);
		int i = 0;
		for(i;i<r.mobCtr;i++){
			giveMobInfo(r.mobs[i],i+1);
		}	
	}
	else{
		printf("Here lies legendary creature %s!",r.mobs[0].name);
		printf("Reward of %s is : \n",r.mobs[0].name);
		displayItem(r.reward);
	}

}
