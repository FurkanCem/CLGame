#pragma once
#include "mob.h"
#include "item.h"
struct Room_s{
	int mobCtr;
	Mob* mobs;	
	Item reward;
	int roomType;
}Room_default = {1,0,0,0};

typedef struct Room_s Room;

Room roomGenerator(int diffuculty){
	Room room = Room_default;
	room.mobCtr += (diffuculty%5);
	room.mobs = mobGenerator(room.mobCtr,diffuculty);
	room.reward = itemGenerator(diffuculty);
	room.roomType = rand() % 3;
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
	}	
	printf("%s\n",roomDesc);
	printf("There are %d monsters here\n",r.mobCtr);
	int i = 0;
	for(i;i<r.mobCtr;i++){
		giveMobInfo(r.mobs[i],i+1);
	}
	printf("Reward of this room is : ");
	displayItem(r.reward);
}
