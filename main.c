#include "player.h"
#include "mob.h"
#include "room.h"
#include <stdio.h>
#include <time.h>

int main(){
	Player p1 = Player_default;
	Item i1 = {1,"firstItem",1};
	Item i2 = {2,"secondItem",1};
	Item i3 = {1};
	Item i4 = {3,"thirdItem",1};	
	
	srand(time(NULL));
	Mob m1 = Mob_default;
/*
	addItem(&p1,i1);	
	addItem(&p1,i2);
	addItem(&p1,i3);
	addItem(&p1,i4);
	displayInventory(&p1);
	removeItem(&p1,2,1);
	displayInventory(&p1);	
	printf("%lf",mobGetDamage(&m1,attack(&p1)));	
*/	
	Room r1 = roomGenerator(1);

	displayItem(r1.reward);

	
	
	return 0;
}

