#pragma once
#include <stdlib.h>
#include <string.h>
#include "item.h"

struct Mob_s{
	double health;
	double str;
	double defence;
	char* name;
}Mob_default = {5,5,0};

typedef struct Mob_s Mob;

double mobAttack(Mob* mob){
	return mob->str;
}
double mobGetDamage(Mob* mob,double val){
	mob->health -= val*(mob->defence < 100 ? (100-mob->defence)/100 : 1/100);
	return mob->health;
}
Mob* bossGenerator(int diffuculty){
	Mob* boss = malloc(sizeof(Mob));
	boss[0] = Mob_default;
	boss[0].health = (diffuculty*(rand()%2+2));
	boss[0].str = (diffuculty*(rand()%2+1));
	boss[0].defence = (diffuculty*(rand()%2+1));
	boss[0].name = generateRandomName();
	return boss;

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

void giveMobInfo(Mob m,int num){
	printf("Mob %d Health : %.0lf Str : %.0lf Def : %.0lf  ",num,m.health,m.str,m.defence);
	if(m.health <= 0)
		printf("Dead");
	printf("\n");
}
