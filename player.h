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
	double defense;
	int invCapacity;
	int itemCtr;
	Item* items;
}Player_default = {100.0,10.0,0,5,0,NULL};

typedef struct Player_s Player;

void getItemName(Player* p,int index){
	int i = 0;
	while(p->items[index].name[i] != '\0'){
		printf("%c",p->items[index].name[i++]);	
	}
	printf(" : %d",p->items[index].quantity);
	printf("\n");
}

void displayInventory(Player* p){
	int i = 0;
	for(i = 0;i<p->itemCtr;i++){
		getItemName(p,i);
	};
}

void updateStats(Player* p,Item itemToAdd){
	p->strength += MIN(10000,itemToAdd.strStat);
	p->defense  += MIN(10000,itemToAdd.defStat);
	p->invCapacity += MIN(10000,itemToAdd.invCapStat);
}
void deleteStats(Player* p,Item itemToAdd){
	p->strength -= MAX(0,itemToAdd.strStat);
	p->defense  -= MAX(0,itemToAdd.defStat);
	p->invCapacity -= MAX(0,itemToAdd.invCapStat);
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






