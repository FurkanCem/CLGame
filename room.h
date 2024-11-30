#pragma once
#include "mob.h"
#include "item.h"
struct Room_s{
	int mobCtr;
	Mob* mobs;	
	Item reward;
}Room_default = {1,0,0};

typedef struct Room_s Room;

Room roomGenerator(int diffuculty){
	Room room = Room_default;
	room.mobCtr += (diffuculty%5);
	room.mobs = mobGenerator(room.mobCtr,diffuculty);
	room.reward = itemGenerator(diffuculty);
	return room;
}
