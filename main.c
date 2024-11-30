#include "player.h"
#include <stdio.h>
#include <time.h>

int main(){
	Player p1 = Player_default;
	Item i1 = {1,"firstItem",1};
	Item i2 = {2,"secondItem",1};
	Item i3 = {1};
	Item i4 = {3,"thirdItem",1};	
	
	srand(time(NULL));
	
	addItem(&p1,i1);	
	addItem(&p1,i2);
	addItem(&p1,i3);
	addItem(&p1,i4);
	displayInventory(&p1);
	removeItem(&p1,2,1);
	displayInventory(&p1);	
	
	return 0;
}

