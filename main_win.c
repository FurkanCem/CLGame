#include "player.h"
#include "mob.h"
#include "room.h"
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <io.h>

Player p1;
unsigned int roomNumber;
void gameLoop();
void mainMenu();
const char* files[] = {"SaveGame1","SaveGame2","SaveGame3"};
int saves[] = {0,0,0};


void startGame(){
	p1 = Player_default;
	srand(time(NULL));
	roomNumber = 1;
	gameLoop();
}

bool checkSaveFiles(){
	int fileCtr = sizeof(files)/sizeof(files[0]);
	bool saveExist = false;
	for(int i  = 0; i<fileCtr;i++){
		if(_access(files[i],F_OK) == 0){
			printf("[%d]%s\n",i+1,files[i]);
			saveExist = true;
			saves[i] = 1;
		}
		else{
			printf("[%d]Empty save!\n",i+1);
		}
	}
	return saveExist;
}

void saveGame(){
	FILE *fp;
	checkSaveFiles();	
	int selection;
	while(scanf("%d",&selection) != 1){
		printf("Enter numeric input\n");
		while(getchar() != '\n');
	}
	
	while(selection>3 || selection<1){
		printf("Enter a valid save location!\n");
		if(scanf("%d",&selection) != 1){
			printf("Enter numeric input\n");
			while(getchar() != '\n');
		}
	}
	fp = fopen(files[selection-1],"w");

	fwrite(&p1.health, sizeof(p1.health), 1, fp);
    	fwrite(&p1.strength, sizeof(p1.strength), 1, fp);
    	fwrite(&p1.defence, sizeof(p1.defence), 1, fp);
    	fwrite(&p1.invCapacity, sizeof(p1.invCapacity), 1, fp);
    	fwrite(&p1.itemCtr, sizeof(p1.itemCtr), 1, fp);
    	fwrite(&p1.hp, sizeof(p1.hp), 1, fp);
	int i = 0;
    	for (i; i < p1.itemCtr; i++) {
    		saveItem(p1.items[i],fp);	
	}
	fwrite(&roomNumber,sizeof(unsigned int),1,fp);
	fclose(fp);
}


void loadGame(){
	if(!checkSaveFiles()){
		printf("No save file is found!\n");
		Sleep(2000);
		mainMenu();
		return;
	}	
	
	FILE *fp;
	int selection;
	while(scanf("%d",&selection) != 1){
		printf("Enter numeric input\n");
		while(getchar() != '\n');
	}	
	while(!(selection < 4 && selection > 0 && saves[selection-1] == 1)){
		printf("Enter a valid save location!\n");
		if(scanf("%d",&selection) != 1){
			printf("Enter numeric input\n");
			while(getchar() != '\n');
		}	
	}
	fp = fopen(files[selection-1],"r");
	srand(time(NULL));

   	fread(&p1.health, sizeof(p1.health), 1, fp);
    	fread(&p1.strength, sizeof(p1.strength), 1, fp);
    	fread(&p1.defence, sizeof(p1.defence), 1, fp);
    	fread(&p1.invCapacity, sizeof(p1.invCapacity), 1, fp);
    	fread(&p1.itemCtr, sizeof(p1.itemCtr), 1, fp);
    	fread(&p1.hp, sizeof(p1.hp), 1, fp);
	
    	p1.items = malloc(p1.itemCtr * sizeof(Item));
	int i = 0;
	for (i; i < p1.itemCtr; i++) {
    	    p1.items[i] = loadItem(fp);
    	}
	fread(&roomNumber,sizeof(unsigned int),1,fp);	
	fclose(fp);
	gameLoop();
}

void deleteGame(){
	if(!checkSaveFiles()){
		printf("No save file is found!\n");
		Sleep(2000);
		mainMenu();
		return;
	}	
	
	int selection;
	while(scanf("%d",&selection) != 1){
		printf("Enter numeric input\n");
		while(getchar() != '\n');
	}	
	while(!(selection < 4 && selection > 0 && saves[selection-1] == 1)){
		printf("Enter a valid save location!\n");
		if(scanf("%d",&selection) != 1){
			printf("Enter numeric input\n");
			while(getchar() != '\n');
		}	
	}
	printf("Are you sure[y,N] : ");	
	char surety = 'n';
	while(scanf(" %c",&surety) != 1){
		printf("Enter a character!\n");
		while(getchar() != '\n');
	}
	if(!(surety == 'Y' || surety == 'y')){
		mainMenu();	
		return;
	}
	if(remove(files[selection-1]) == 0){
		printf("Save game %s file deleted!\n",files[selection-1]);	
	}
	else{
		printf("Error deleting file\n");
	}
	Sleep(2000);
	mainMenu();
}
void gameOver(){
	printf("Game Over!\n");
	Sleep(3000);
	mainMenu();
}
void exitGame(){
	printf("Goodbye!\n");
	Sleep(3000); 
	exit(0);
}

void mainMenu(){

	system("cls"); 
	printf("\tWelcome to the Game!\n");
	printf("[1] New Game\n");
	printf("[2] Load Game\n");
	printf("[3] Delete Game\n");
	printf("[4] Exit\n");
	int selection;
	while(true){
		if(scanf("%d",&selection) != 1){
			printf("Enter numeric input!\n");
			while(getchar()!= '\n');
			continue;
		}
		switch(selection){
			case 1:
				startGame();	
				break;
			case 2:
				loadGame();
				break;
			case 3:
				deleteGame();
				break;
			case 4:
				exitGame();
			default:
				printf("Please enter a valid selection!");
		}
	}
}

void actionSelection(){
	printf("[1] Attack\n");
	printf("[2] Heal\n");
	printf("[3] Inventory\n");
	printf("[4] Save Game\n");
	printf("[5] Return to Main Menu\n");
}

void gameLoop(){
	int actionSelected = 0;
	Room room = roomGenerator(roomNumber,0 == roomNumber % 5);
	int mobTargetIndex = 0;
	bool toTheNewRoom = false;
	while(!toTheNewRoom){
		bool validChoice = false;
		bool checkedInventory = false;
		while(true){
			system("cls"); 
			printf("Room : %d\n",roomNumber);
			givePlayerInfo(&p1);
			giveRoomInformation(room);
			actionSelection();
			if(scanf("%d",&actionSelected) != 1){
				printf("Enter numeric input!\n");
				while(getchar() != '\n');
				Sleep(2000);
				continue;
			}
			if(actionSelected > 0 || actionSelected < 4)		
				break;
			printf("Enter a valid choice\n");	
		}
		
		Mob* targetedMob = &room.mobs[mobTargetIndex];
		switch(actionSelected){
			case 1:{
				int damage = (int)attack(&p1);
				printf("You deal %d damage!\n",damage);
				int remainingHealth = mobGetDamage(targetedMob,damage);
				if(remainingHealth <=0 ){
					printf("Creature is dead!\n");
					mobTargetIndex++;
					targetedMob = &room.mobs[mobTargetIndex];
					if(mobTargetIndex >= room.mobCtr)
						toTheNewRoom = true;
				}
				break;}
			case 2: 
				if(p1.hp>0){
					getHeal(&p1,40);
					p1.hp--;
				}	
				else{
					printf("You dont have any health potion!\n");
				}
				break;
			case 3:
				displayInventory(&p1);
				checkedInventory = true;
				Sleep(3000);
				break;
			case 4:
				saveGame();	
				checkedInventory = true;
				break;
			case 5:
				mainMenu();
				break;
			default:
				printf("Enter a valid choice!\n");
				Sleep(2000);
				checkedInventory = true;
				break;
		}
		if(checkedInventory)
			continue;
		int i = mobTargetIndex;
		int sumDmg = 0;
		for(i;i<room.mobCtr;i++){
			int receivedDmg = mobAttack(&room.mobs[i]);
			if(0 != roomNumber % 5){
				printf("Mob %d deals %d damage!\n",i+1,receivedDmg);
			}
			else
				printf("Boss deals %d damage!\n",receivedDmg);
			sumDmg += receivedDmg;
		}
		int remainingHealth = getDamage(&p1,sumDmg);
		if(remainingHealth <= 0){
			gameOver();
		}
		Sleep(3000);
	}
	if(roomNumber %5 == 0){
		printf("You won %s and 2 heath potion!\n",room.reward.name); 
		addItem(&p1,room.reward);
		getHeal(&p1,50.0);
	}
	else{
		printf("You won 2 heath potion!\n");
		getHeal(&p1,20.0);
	}
	addHealthPotion(&p1,2);
	Sleep(2000);
	roomNumber++;
	gameLoop();
}

int main(){
	mainMenu();
	return 0;
}

