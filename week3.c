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
   const char* name;
   int price;
   int volume;
   int   quantity;
}item;

item* createItem(item* i, const char* name, int p, int vm, int q) {
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
   const char* name;
   item* itemList;

}shop;

shop* createShop(shop*s, const char* n, item* itemList) {
   s->name = n;
   s->itemList = (item*)malloc(sizeof(itemList));
   s->itemList = itemList;
   return s;
}

typedef struct level {
   const char* category;
   shop* shopList;
   int numOfShop;
}level;

level* createLevel(level* l, const char* cat, shop* shopList, int num) {
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

item* createCL(item* ilist) {
   item* cL;
   
   cL = (item*)malloc(sizeof(item)*rand() % 5);
   for (int i = 0; i < sizeof(cL); i++) {
      cL[i] = ilist[rand() % 27];
      cL[i].quantity = rand() % 3 + 1;
   }
   return cL;
}

void elevator(human* user, int num) {
   user->level = num;
}

void escalator(human* user, int num) {
   user->level += num;
}

void printList(item* list) {
   for (int i = 0; i <= sizeof(list); i++) {
      printf("[%d]: %c, 가격: %d 개수: %d\n", i + 1, list[i].name, list[i].price, list[i].quantity);
   }
}

void myStatus(human* user) {
   printf("현재 층: %d", user->level);
   }

void printshop(shop* sl) {
   for (int i = 0; i < sizeof(sl); i++) {
      printf("%d. %c    ", i+1 ,sl[i].name);
   }
}

int move() {
   int m = 0;
   printf("1. 1번 매장 가기   2. 2번 매장 가기   3. 3번 매장 가기");
   printf("\n4. 에스컬레이터   5. 엘레베이터      6. 장바구니 확인   7. 체크리스트 확인");
   printf("\n8. 계산하기\n->");

   scanf_s("%d", &m);
   return m;
}
void inventoryPush(human* user, item p, int c) {
   if (user->myInventory->index == user->myInventory->max) {
      printf("full!");
      return;
   }
   else {
      user->myInventory->itemList[user->myInventory->index] = p;
      user->myInventory->itemList[user->myInventory->index].quantity = c;
      user->myInventory->volume = user->myInventory->itemList[user->myInventory->index].volume * c;
      user->myInventory->index++;
   }
   }

void counter(human* user) {
   int total = 0;
   int change = 0;
   total = user->myInventory->total;
   printf("총액: %d 잔액: %d", total, user->myWallet->cash - total);
}
void selecter(shop* s, human* user) {
   int selecter;
   int counter;
   
   printf("%c 가는중...\n...\n...\n도착!",s->name);
   printf("%c 에는,,,\n",s->name);
   printList(s->itemList);
   printf("가 있다! 뭘 담을까?\n->");
   scanf_s("%d", &selecter);
   printf("몇 개를 담을까?\n->");
   scanf_s("%d", &counter);
   inventoryPush(user, s->itemList[selecter], counter);
}

int main() {
   int exit = 0;
   char shoppingBag = 0;
   printf("loading....\n");

   //1층
   item m1, m2, m3, v1, v2, v3, d1, d2, d3;
   shop x1, x2, x3;
   level f1;

   createItem(&m1, "chicken", 1000, 3, 5);
   createItem(&m2, "beef", 2000, 3, 5);
   createItem(&m3, "pork", 3000, 3, 5);
   item meatlist[3] = { m1, m2, m3 };

   createShop(&x1, "meat shop", meatlist);

   createItem(&v1, "onion", 1000, 3, 5);
   createItem(&v2, "garlic", 2000, 3, 5);
   createItem(&v3, "potato", 3000, 3, 5);
   item vlist[3] = { v1, v2, v3 };

   createShop(&x2, "vegetable shop", vlist);

   createItem(&d1, "milk", 1000, 3, 5);
   createItem(&d2, "yogurt", 2000, 3, 5);
   createItem(&d3, "cheese", 3000, 3, 5);
   item dlist[3] = { d1, d2, d3 };

   createShop(&x3, "dairyproduct shop", dlist);

   shop foodcorner[3] = { x1, x2, x3 };

   createLevel(&f1, "food", foodcorner, 3);

   //1층

   // 2층
   item l1, l2, l3, s1, s2, s3, a1, a2, a3;
   shop L, S, A;
   level f2;

   createItem(&l1, "LG", 30000, 3, 5);
   createItem(&l2, "ASUS", 10000, 3, 5);
   createItem(&l3, "Dell", 20000, 3, 5);

   createItem(&s1, "Apple", 10000, 3, 5);
   createItem(&s2, "Samsung", 10000, 3, 5);
   createItem(&s3, "Nokia", 5000, 3, 5);

   createItem(&a1, "Carrier", 50000, 3, 5);
   createItem(&a2, "Daewoo", 30000, 3, 5);
   createItem(&a3, "Dyson", 40000, 3, 5);

   item laptop[3] = { l1, l2, l3 };
   item smartphone[3] = { s1, s2, s3 };
   item appliance[3] = { a1, a2, a3 };
   createShop(&L, "Laptop", laptop);
   createShop(&S, "SmartPhone", smartphone);
   createShop(&A, "Apliances", appliance);

   shop ecorner[3] = { A,S,L };

   createLevel(&f2, "electronics", ecorner, 3);
   //2층

   //3층
   item h1, h2, h3, e1,e2,e3, n1, n2, n3;
   shop hm, sec, nike;
   level f3;

   createItem(&h1, "shirts", 3000, 5, 20);
   createItem(&h2, "pants", 2500, 5, 15);
   createItem(&h3, "shoes", 5000, 5, 10);
   createItem(&e1, "knit", 4000, 5, 15);
   createItem(&e2, "socks", 100, 5, 20);
   createItem(&e3, "cardigan", 3500, 5, 15);
   createItem(&n1, "blazer", 5000, 5, 10);
   createItem(&n2, "coat", 6000, 5, 5);
   createItem(&n3, "slacks", 2000, 5, 20);


   item itemlist1[3] = { h1, h2, h3 };
   item itemlist2[3] = { s1, s2, s3 };
   item itemlist3[3] = { n1, n2, n3 };

   createShop(&hm, "h&m", itemlist1);
   createShop(&sec, "8seconds", itemlist2);
   createShop(&nike, "nike", itemlist3);

   shop ccorner[3] = { hm,sec,nike};

   createLevel(&f3, "fashion", ccorner, 3);
   //3층
   //대 item 배열 만들기
   item itemlist[27] = {m1,m2,m3,v1,v2,v3,d1,d2,d3,l1,l2,l3,s1,s2,s3,a1,a2,a3,h1,h2,h3,e1,e2,e3,n1,n2,n3};
   //user 만들기
   human user;
   wallet w;
   w.creditCard = 30000000000000;
   inventory inventory;
   item* checklist;
   checklist = createCL(itemlist);
   
   printf("shopping mall 1.0\n 장을 보러 가자! 얼마를 챙길까? \n -> ");
   w.cash = 3000000;
   printf("%d원 챙겼다! ",w.cash);
   printf("뭘 사야하지?\n");
   //shopping list 출력
   printList(checklist);

   printf("장바구니를 챙길까? y/n \n->");
   //scanf_s("%c", &shoppingBag);
   //if (shoppingBag == 'y')
      createInventory(&inventory, 300);
   //else
   //   createInventory(&inventory, 30);
   
   printf("%d 만큼 챙길 수 있다!\n", inventory.maxVolume);

   createHuman(&user, &w, &inventory, checklist);

   printf("출발!\n가는중...\n");

   for (int i = 0; i < 9; i++) {
      printf("....\n");
   }

   printf("S-마트에 도착했다!\n");

   //루프 시작!
   int nextMove;
   char next;
   while (exit = 0) {
      if (user.level == 1) {
         printf("현재 층: %d: %c \n", user.level, f1.category);
         printshop(foodcorner);
         nextMove = move();
         while (nextMove == 1) {
            selecter(&x1,&user);
            printf("더 담을까? y/n \n->");
            scanf_s("%c", &next);
            if (next == 'n')
               nextMove = move();
         }
         while (nextMove == 2) {
            selecter(&x2, &user);
            printf("더 담을까? y/n \n->");
            scanf_s("%c", &next);
            if (next == 'n')
               nextMove = move();
         }
         while(nextMove == 3) {
            selecter(&x3, &user);
            printf("더 담을까? y/n \n->");
            scanf_s("%c", &next);
            if (next == 'n')
               nextMove = move();
         }
         while (nextMove == 4) {

         }
         while (nextMove == 5) {

         }
         while (nextMove == 6) {

         }
         while (nextMove == 7) {

         }
         while (nextMove == 8) {
            exit = 1;
         }
      }
      else if (user.level == 2) {

      }
      else {

      }
   }

   return 0;
}
