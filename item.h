#pragma once

struct Item_s{
	int id;
	char* name;
	int quantity;
	int strStat;
	int defStat;
	int invCapStat;
	}Item_default = {0,"defaultItem",1,0,0,0};

typedef struct Item_s Item;
