#include <stdio.h>
#include <stdlib.h>

typedef struct wallet {
	int cash;
	int creditCard;
}wallet;

typedef struct item {
	char name;
	int price;
	int volume;
	int   quantity;
}item;

typedef struct inventory {
	item* itemList;
	int volume;
	int maxVolume;
	int total;
}inventory;

typedef struct checklist {
	item* itemList;
}checklist;

typedef struct shop {
	char name;
	item* itemList;
}shop;

typedef struct level {
	char* category;
	shop* shopList;
}level;

typedef struct human {
	int health;
	wallet* myWallet;
	inventory* myInventory;
	checklist* myChecklist;
	level* myFloor;
}human;


int main() {
	human user;
	wallet wallet;
	inventory basket;
	level first;
	shop shop1;
	item item1;
	item item2;
	item item3;

	user.health = 10;

	basket.maxVolume = 10;
	basket.volume = 0;
	basket.itemList = (item*)malloc(sizeof(item) * 3);
	basket.itemList = NULL;
	basket.total = 0;

	wallet.cash = 10;
	wallet.creditCard = 0;

	user.myInventory = &basket;
	user.myWallet = &wallet;

	item1.name = 'a';
	item2.name = 'b';
	item3.name = 'c';

	item1.price = 1;
	item2.price = 2;
	item3.price = 3;

	shop1.name = 'S';
	shop1.itemList = (item*)malloc(sizeof(item) * 3);

	shop1.itemList[0] = item1;
	shop1.itemList[1] = item2;
	shop1.itemList[2] = item3;

	first.shopList = (shop*)malloc(sizeof(shop));
	first.shopList[0] = shop1;

	user.myFloor = &first;


	return 0;
}