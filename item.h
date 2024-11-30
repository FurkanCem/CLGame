#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Item_s{
	int id;
	char* name;
	int quantity;
	int strStat;
	int defStat;
	int invCapStat;
	}Item_default = {0,"defaultItem",1,0,0,0};

typedef struct Item_s Item;
char* generateRandomName() {
    	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    	int length = rand() % 8 + 3;  
    	char* firstName = (char*)malloc(length + 1);  
    	if (!firstName) {
        	return NULL;  
    	}

    	for (int i = 0; i < length; i++) {
        	firstName[i] = charset[rand() % (sizeof(charset) - 1)];
    	}
    	firstName[length] = '\0';  
   	 return firstName;  
}

Item itemGenerator(int diffuculty){
	Item item = Item_default;
	item.name = generateRandomName();
	item.strStat += ((1+(rand() % 5))*diffuculty);
	item.defStat += ((1+(rand() % 5))*diffuculty);
	item.invCapStat += ((1+(rand() % 5))*(diffuculty%10));
	return item;
}


void displayItem(Item item){
	printf("%s\n",item.name);
	printf("Str : %d ,Def : %d ,InvCapacity : %d\n",item.strStat,item.defStat,item.invCapStat);	
}

Item loadItem(FILE *fp) {
    Item item = Item_default;

    fread(&item.id, sizeof(item.id), 1, fp);
    fread(&item.quantity, sizeof(item.quantity), 1, fp);
    fread(&item.strStat, sizeof(item.strStat), 1, fp);
    fread(&item.defStat, sizeof(item.defStat), 1, fp);
    fread(&item.invCapStat, sizeof(item.invCapStat), 1, fp);

    int nameLength;
    fread(&nameLength, sizeof(int), 1, fp);
    item.name = malloc(nameLength * sizeof(char)); 
    fread(item.name, sizeof(char), nameLength, fp); 

    return item; 
}



void saveItem(Item item, FILE *fp) {
    fwrite(&item.id, sizeof(item.id), 1, fp);
    fwrite(&item.quantity, sizeof(item.quantity), 1, fp);
    fwrite(&item.strStat, sizeof(item.strStat), 1, fp);
    fwrite(&item.defStat, sizeof(item.defStat), 1, fp);
    fwrite(&item.invCapStat, sizeof(item.invCapStat), 1, fp);
    
    int nameLength = strlen(item.name) + 1; 
    fwrite(&nameLength, sizeof(int), 1, fp);
    fwrite(item.name, sizeof(char), nameLength, fp); 
}

