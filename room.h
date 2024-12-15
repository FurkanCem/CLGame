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
	room.mobCtr += isBossRoom ? 0 : (diffuculty/4);
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
			roomDesc = "A circular room of damp stone echoes every sound, distorting it into haunting whispers. A shallow pit of rippling, stagnant water lies at the center, while crude carvings of snarling faces watch from the walls.";
			break;
		case 1:
			roomDesc = "Smooth obsidian walls reflect the dim glow of ceiling crystals, casting jagged patterns of light. Chains dangle ominously, and a rune-etched iron chest sits on a dais, pulsing with an ominous red glow.";
			break;
		case 2:
			roomDesc = "This decaying corridor reeks of death, its walls lined with crumbling alcoves housing rotted coffins. A faint trail of footprints leads to a moss-covered stone door engraved with skeletal motifs.";
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
		printf("Here lies legendary creature %s!\n",r.mobs[0].name);
		giveMobInfo(r.mobs[0],-1);
		printf("Reward of %s is : \n",r.mobs[0].name);
		displayItem(r.reward);
	}

}
