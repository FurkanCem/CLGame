#pragma once
#include <stdlib.h>

struct Mob_s{
	double health;
	double str;
	double defence;
}Mob_default = {10,10,0};

typedef struct Mob_s Mob;

double mobAttack(Mob* mob){
	return mob->str;
}
double mobGetDamage(Mob* mob,double val){
	mob->health -= val*(mob->defence < 100 ? (100-mob->defence)/100 : 1/100);
	return mob->health;
}

Mob* mobGenerator(int number,int diffuculty){
	Mob* mobs = malloc(number*sizeof(Mob));
	int i = 0;
	for(i;i<number;i++){
		mobs[i] = Mob_default;
		mobs[i].health += (rand()%11 == 2 ? diffuculty*2 : diffuculty);
		mobs[i].str += (rand()%11 == 2 ? diffuculty*1.5 : diffuculty);
		mobs[i].defence += (rand()%11 == 2 ? diffuculty*1.5 : diffuculty);
	}
	return mobs;
}
