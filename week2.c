#include <stdio.h>
#include <stdlib.h>

typedef struct wallet {
   int cash;
   int creditCard;
}wallet;

wallet* createWallet(wallet* w, int money, int creditCard) {
   w->cash = money;
   w->creditCard = creditCard;
   return w;
}

typedef struct item {
   char name;
   int price;
   int volume;
   int   quantity;
}item;



item* createItem(item* i, char name, int p, int vm, int q) {
   i->name = name;
   i-> price = p;
   i->volume = vm;
   i->quantity = q;
   return i;
}

 
typedef struct inventory {
   item* itemList;
   int index;
   int max;
   int volume;
   int maxVolume;
   int total;
}inventory;

inventory* createInventory(inventory* i, int mV) {
   i->index = 0;
   i->max = 5;
   i->volume = 0;
   i->maxVolume = mV;
   i->itemList = (item*)malloc(sizeof(item) * mV);
   i->total = 0;
   return i;
}

typedef struct shop {
   char name;
   item* itemList;
}shop;

shop* createShop(shop*s, char n, item* itemList) {
   s->name = n;
   s->itemList = itemList;
   return s;
}

typedef struct level {
   char category;
   shop* shopList;
   int numOfShop;
}level;

level* createLevel(level* l, char cat, shop* shopList, int num) {
   l->category = cat;
   l->shopList = shopList;
   int numOfShop = num;
   return l;
}

typedef struct human {
   int health;
   wallet* myWallet;
   inventory* myInventory;
   item* myChecklist;
   int level;
}human;

human* createHuman(human* user, wallet* w, inventory* i, item* cL) {
   user->health = 50;
   user->myWallet = w;
   user->myInventory = i;
   user->myChecklist = cL;
   user->level = 1;
   return user;
}

void elevator(human* user, int num) {
   user->level = num;
}

void escalator(human* user, int num) {
   user->level += num;
}

void printList(item* list) {
   for (int i = 0; i <= sizeof(list); i++) {
      printf("[%d]: %c, price: %d quantity: %d\n", i + 1, list[i].name, list[i].price, list[i].quantity);
   }
}

void myStatus(human* user) {
   printf("현재 내 상태: \n health: %d\nmyWallet: %d\nmyFloor: %d\n", user->health, user->myWallet->cash,user->level);
   for (int i = 0; i <= sizeof(user->myChecklist); i++) {
      printf("[%d]: %c, price: %d quantity: %d\n", i + 1, user->myChecklist[i].name, user->myChecklist[i].price, user->myChecklist[i].quantity);
   }
}

void inventoryPush(human* user, item p) {
   if (user->myInventory->index == user->myInventory->max) {
      printf("full!");
      return;
   }
   else {
      user->myInventory->itemList[user->myInventory->index] = p;
      user->myInventory->index++;
   }
   }

void counter(human* user) {
   int total = 0;
   int change = 0;
   total = user->myInventory->total;
   printf("총액: %d 잔액: %d", total, user->myWallet->cash - total);
}

int main() {
   human user;
   wallet w;
   inventory i;
   item i1;
   item i2;
   item i3;
   
   createItem(&i1, 'a', 1000, 3, 5);
   createItem(&i2, 'b', 2000, 3, 5);
   createItem(&i3, 'c', 3000, 3, 5);
   item checklist[5] = { i1,i2,i3 };

   createWallet(&w, 5000, 99999999);
   createInventory(&i, 10);
   createHuman(&user,&w,&i,checklist);

   myStatus(&user);
   elevator(&user, 3);
   myStatus(&user);
   escalator(&user, -1);
   escalator(&user, -1);
   escalator(&user, 1);
   myStatus(&user);
   createItem(&i1, 'a', 1000, 3, 5);
   createItem(&i2, 'b', 2000, 3, 5);
   createItem(&i3, 'c', 3000, 3, 5);
   shop s;
   item item[3] = { i1,i2,i3 };
   createShop(&s, 'n', item);

   printf("상점 &c에 들어있는 item: \n");
   for (int i = 0; i < 3; i++) {
      printf("[%d]: %c, 가격: %d, 부피: %d, 수량: %d \n", i + 1, item[i].name, item[i].price, item[i].volume, item[i].quantity);
   }

   inventoryPush(&user, i3);
   inventoryPush(&user, i2);
   inventoryPush(&user, i1);
   
   printList(user.myInventory->itemList);

   return 0;
}
