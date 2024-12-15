#pragma once
#include "item.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


struct Player_s{
	double health;
	double strength;
	double defence;
	int invCapacity;
	int itemCtr;
	Item* items;
	int hp;
}Player_default = {100.0,10.0,0,5,0,NULL,3};

typedef struct Player_s Player;

void givePlayerInfo(Player* p){
	printf("Health : %.0lf Str : %.0lf Def : %.0lf HealthPotion : %d\n",p->health,p->strength,p->defence,p->hp);
}

void displayInventory(Player* p){
	printf("Inventory capacity : %d\n",p->invCapacity);
	if(p->itemCtr == 0){
		printf("You dont have any items!\n");
	}
	for(int i = 0;i<p->itemCtr;i++){
		printf("%s ",p->items[i].name);
		printf("Str : %d ,Def : %d ,InvCapacity : %d\n",p->items[i].strStat,p->items[i].defStat,p->items[i].invCapStat);
	}
}

void updateStats(Player* p,Item itemToAdd){
	p->strength += MIN(10000,itemToAdd.strStat);
	p->defence  += MIN(10000,itemToAdd.defStat);
	p->invCapacity += MIN(10000,itemToAdd.invCapStat);
}
void deleteStats(Player* p,Item itemToAdd){
	p->strength -= MAX(0,itemToAdd.strStat);
	p->defence  -= MAX(0,itemToAdd.defStat);
	p->invCapacity -= MAX(0,itemToAdd.invCapStat);
}


void addHealthPotion(Player* p,int quantity){
	p->hp = MIN(p->hp+quantity,10);
}

void addItem(Player* p,Item itemToAdd){
	int i = 0;
	for(i;i<p->itemCtr;i++){
		if(p->items[i].id == itemToAdd.id){
			p->items[i].quantity++;
			updateStats(p,itemToAdd);
			return;
		}
	}
	if(p->itemCtr == p->invCapacity){
		printf("Inventory is full!\n");
		return;
	}
	p->items = realloc(p->items,(p->itemCtr+2)*sizeof(Item));
	p->items[p->itemCtr++] = itemToAdd;
	updateStats(p,itemToAdd);
}

void removeItem(Player* p,int index,int quantity){
	if(index>p->itemCtr){
		printf("Invalid choice\n");
		return;
	}
	int i = 0;
	Item itemToRemove = p->items[index-1];
	bool found = false;
	for(i;i<p->itemCtr;i++){
		if(p->items[i].id == itemToRemove.id){
			found = true;
			break;
		}
	}
	if(!found){
		printf("No such item!\n");
		return;
	}
	if(p->items[i].quantity>quantity){
		p->items[i].quantity -= quantity;
		return;
	}
	for(i;i<p->itemCtr-1;i++){
		p->items[i] = p->items[i+1];
	}
	p->itemCtr = MAX(0,p->itemCtr-1);
	p->items = realloc(p->items,(p->itemCtr)*sizeof(Item));
	deleteStats(p,itemToRemove);
}

double attack(Player* p){
	return (p->strength)*((rand()%11)==3 ? 2 :1);
}

double getDamage(Player* p,double val){
	p->health -= val/(p->defence == 0 ? 1 : p->defence); 
	return p->health;
}
void getHeal(Player*p,double val){
	p->health += val;
	printf("You healed %.0lf hp!\n",val);
}






