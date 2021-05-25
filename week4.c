#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

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
    int quantity;
}item;

item* createItem(item* i, const char* name, int p, int vm, int q) {
    i->name = name;
    i->price = p;
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
    int top;
}inventory;

inventory* createInventory(inventory* i, int mV) {
    i->index = 0;
    i->max = mV;
    i->volume = 0;
    i->maxVolume = mV;
    i->itemList = (item*)malloc(sizeof(item) * mV);
    i->total = 0;
    i->top = 5;
    return i;
}

typedef struct shop {
    const char* name;
    item* itemList;

}shop;

shop* createShop(shop* s, const char* n, item* itemList) {
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
    inventory* myChecklist;
    int level;
}human;

human* createHuman(human* user, wallet* w, inventory* i, inventory* cL) {
    user->health = 50;
    user->myWallet = w;
    user->myInventory = i;
    user->myChecklist = cL;
    user->level = 1;
    return user;
}

item* createCL(item* ilist, item* CheckList) {
    srand(time(NULL));

    for (int i = 0; i <= sizeof(CheckList); i++) {
        int r = rand() % 27;
        CheckList[i] = ilist[r];
        CheckList[i].quantity = rand() % 3 + 1;
        for (int j = 0; j < i; j++) {
            if (CheckList[i].name == CheckList[j].name) {
                i--;
                break;
            }
        }
    } 
    return CheckList;
}

void printCL(item* CL) {
    for (int i = 0; i <= sizeof(CL); i++) {
        printf("[%d]: %s, 가격: %d 개수: %d\n", i + 1, CL[i].name, CL[i].price, CL[i].quantity);
    }
}

void elevator(human* user) {
    int level;
    printf("엘레베이터를 이용합니다.\n");
    printf("현재 층: %d\n", user->level);
    printf("몇 층으로 가시겠습니까?1. 1층      2. 2층      3. 3층 1\->");
    fseek(stdin, 0, SEEK_END);
    scanf_s("%d", &level);
    if (level > 3) {
        printf("존재하지 않는 층입니다.\n다시 선택해주세요.\n");
        return;
    }
    printf("%d층으로 이동합니다...\n", level);
    user->level = level;
    printf("%d층으로 이동했습니다\n", level);

}

void escalator(human* user) {
    printf("에스컬레이터를 이용합니다.\n");
    printf("현재 층: %d\n", user->level);
    int up;
    if (user->level == 1) {
        printf("2층으로 올라갑니다...\n");
        user->level++;
    }
    else if (user->level == 2) {
        printf("1. 올라간다      2. 내려간다\n->");
        fseek(stdin, 0, SEEK_END);
        scanf_s("%d", &up);
        if (up == 1) {
            printf("3층으로 올라갑니다...\n");
            user->level++;
        }
        else {
            printf("1층으로 내려갑니다...\n");
            user->level--;
        }
    }
    else {
        printf("2층으로 내려갑니다...\n");
        user->level--;
    }
}

void printList(item* list) {
    for (int i = 0; i < sizeof(list)-1; i++) {
        printf("[%d]: %s, 가격: %d 개수: %d\n", i + 1, list[i].name, list[i].price, list[i].quantity);
    }
}

void printmyinventory(inventory* inven) {
    if (inven->index == 0) {
        printf("장바구니가 비어있습니다.\n");
    }
    for (int i = 0; i < inven->index; i++) {
        printf("[%d]: %s, 가격: %d 개수: %d\n", i + 1, inven->itemList[i].name, inven->itemList[i].price, inven->itemList[i].quantity);
    }
}
void myStatus(human* user) {
    printf("현재 층: %d", user->level);
}

void printshop(shop* sl) {
    for (int i = 0; i < sizeof(sl) - 1; i++) {
        printf("%d. %s    ", i + 1, sl[i].name);
    }
    printf("\n_______________________________________________\n");
}

int move() {
    int m = 0;
    printf("1. 1번 매장 가기   2. 2번 매장 가기   3. 3번 매장 가기      4. 에스컬레이터");
    printf("\n5. 엘레베이터      6. 장바구니 확인   7. 체크리스트 확인      8. 계산하기 ");
    printf("\n->");
    fseek(stdin, 0, SEEK_END);
    scanf_s("%d", &m);
    return m;
}
void inventoryPush(human* user, item* p, int c) {
    if (user->myInventory->index == user->myInventory->max) {
        printf("장바구니가 가득 찼습니다!\n");
        return;
    }
    else if (p->quantity == 0) {
        printf("재고가 없습니다!\n");
        return;
    }
    else {
        user->myInventory->itemList[user->myInventory->index].name = p->name;
        user->myInventory->itemList[user->myInventory->index].price = p->price;
        user->myInventory->total += p->price * c;
        user->myInventory->itemList[user->myInventory->index].quantity = c;
        user->myInventory->volume = user->myInventory->itemList[user->myInventory->index].volume * c;
        user->myInventory->index++;
        p->quantity = p->quantity - c;
        return;
    }
}

void compare(inventory) {

}

void counter(human* user) {
    int total = 0;
    int change = 0;
    total = user->myInventory->total;
    printf("바코드 찍는 중...\n...\n...\n");
    printmyinventory(user->myInventory);
    printf("__________________________________________________________\n총액은 %d원 입니다.\n ", total);
    printf("계산하는 중...\n");
    change = user->myWallet->cash - total;
    if (change < 0) {
        printf("잔액이 부족합니다.\n 쇼핑에 실패하였습니다!!\n");
    }
    else {
        printf("쇼핑에 성공하였습니다!\n 거스름돈: %d원\n", change);
    }
};
void selecter(shop* s, human* user) {
    int selecter;
    int counter;

    printf("%s 가는중...\n...\n...\n도착!\n", s->name);
    printf("%s 에는,,,\n", s->name);
    printList(s->itemList);
    printf("가 있다! 뭘 담을까?\n->");
    fseek(stdin, 0, SEEK_END);
    scanf_s("%d", &selecter);
    selecter--;
    printf("몇 개를 담을까?\n->");
    fseek(stdin, 0, SEEK_END);
    scanf_s("%d", &counter);
    inventoryPush(user, &s->itemList[selecter], counter);
}



int main() {

    printf("loading....\n");
    //초기화 작업
    // 
    //1층
    item m1, m2, m3, v1, v2, v3, d1, d2, d3;
    shop x1, x2, x3;
    level f1;

    createItem(&m1, "치킨", 1000, 3, 5);
    createItem(&m2, "소고기", 2000, 3, 5);
    createItem(&m3, "돼지고기", 3000, 3, 5);
    item meatlist[3] = { m1, m2, m3 };

    createShop(&x1, "정육점", meatlist);

    createItem(&v1, "양파", 1000, 3, 5);
    createItem(&v2, "마늘", 2000, 3, 5);
    createItem(&v3, "왕감자", 3000, 3, 5);
    item vlist[3] = { v1, v2, v3 };

    createShop(&x2, "싱싱코너", vlist);

    createItem(&d1, "우유", 1000, 3, 5);
    createItem(&d2, "요거트", 2000, 3, 5);
    createItem(&d3, "치즈", 3000, 3, 5);
    item dlist[3] = { d1, d2, d3 };

    createShop(&x3, "유제품코너", dlist);

    shop foodcorner[3] = { x1, x2, x3 };

    createLevel(&f1, "푸드코너", foodcorner, 3);

    //1층

    // 2층
    item l1, l2, l3, s1, s2, s3, a1, a2, a3;
    shop L, S, A;
    level f2;

    createItem(&l1, "LG 랩탑", 30000, 3, 5);
    createItem(&l2, "ASUS 랩탑", 10000, 3, 5);
    createItem(&l3, "Dell 랩탑", 20000, 3, 5);

    createItem(&s1, "아이폰", 10000, 3, 5);
    createItem(&s2, "갤럭시", 10000, 3, 5);
    createItem(&s3, "노키아", 5000, 3, 5);

    createItem(&a1, "캐리어 에어컨", 50000, 3, 5);
    createItem(&a2, "딤채 냉장고", 30000, 3, 5);
    createItem(&a3, "다이슨 청소기", 40000, 3, 5);

    item laptop[3] = { l1, l2, l3 };
    item smartphone[3] = { s1, s2, s3 };
    item appliance[3] = { a1, a2, a3 };
    createShop(&L, "랩탑", laptop);
    createShop(&S, "스마트폰", smartphone);
    createShop(&A, "가전제품", appliance);

    shop ecorner[3] = { A,S,L };

    createLevel(&f2, "전자제품", ecorner, 3);
    //2층

    //3층
    item h1, h2, h3, e1, e2, e3, n1, n2, n3;
    shop hm, sec, nike;
    level f3;

    createItem(&h1, "반팔", 3000, 5, 20);
    createItem(&h2, "바지", 2500, 5, 15);
    createItem(&h3, "신발", 5000, 5, 10);
    createItem(&e1, "니트", 4000, 5, 15);
    createItem(&e2, "양말", 100, 5, 20);
    createItem(&e3, "가디건", 3500, 5, 15);
    createItem(&n1, "블레이저", 5000, 5, 10);
    createItem(&n2, "코트", 6000, 5, 5);
    createItem(&n3, "슬랙스", 2000, 5, 20);


    item itemlist1[3] = { h1, h2, h3 };
    item itemlist2[3] = { e1, e2, e3 };
    item itemlist3[3] = { n1, n2, n3 };

    createShop(&hm, "나이키", itemlist1);
    createShop(&sec, "에잇세컨즈", itemlist2);
    createShop(&nike, "H&M", itemlist3);

    shop ccorner[3] = { hm,sec,nike };

    createLevel(&f3, "의류매장", ccorner, 3);
    //3층
    // 
    //      층 초기화 종룍
    //대 item 배열 만들기
    item itemlist[27] = { m1,m2,m3,v1,v2,v3,d1,d2,d3,l1,l2,l3,s1,s2,s3,a1,a2,a3,h1,h2,h3,e1,e2,e3,n1,n2,n3 };
    //user 만들기
    human user;
    wallet w;
    int cash;
    inventory inventory1;
    inventory  inventory2;
  

    item* checklist = (item*)malloc(sizeof(item)*5);
    checklist = createCL(itemlist, checklist);
    createInventory(&inventory2, 5);
    user.myChecklist = &inventory2;


    printf("shopping mall 1.0\n 장을 보러 가자! 얼마를 챙길까? \n -> ");
    scanf_s("%d", &cash);
    createWallet(&w, cash, 30);
    printf("%d원 챙겼다! ", w.cash);
    printf("뭘 사야하지?\n");
    //shopping list 출력
    printCL(checklist);

    int exit = 0;
    char shoppingBag;

    printf("장바구니를 챙길까? y/n \n->");
    fseek(stdin, 0, SEEK_END);
    shoppingBag = getchar();
    if (shoppingBag == 'y')
        createInventory(&inventory1, 10);
    else
        createInventory(&inventory1, 2);

    printf("%d가지 아이템을 담을 수 있다!\n", inventory1.maxVolume);

    createHuman(&user, &w, &inventory1, &inventory2);

    printf("출발!\n가는중...\n");

    for (int i = 0; i < 9; i++) {
        printf("....\n");
    }

    printf("S-마트에 도착했다!\n");
    printf("1층: 식품코너 2층:의류매장 3층: 가전제품\n");
    //사람 초기화 종료
    // 
    // 
    // 
    //루프 시작!
    int nextMove;
    char next;
    while (exit == 0) {
        if (user.level == 1) {
            printf("현재 층: %d: %s \n", user.level, f1.category);
            printshop(f1.shopList);
            nextMove = move();
            while (nextMove == 1) {
                selecter(&x1, &user);
                printf("더 담을까? y/n \n->");
                fseek(stdin, 0, SEEK_END);
                scanf_s("%c", &next);
                if (next == 'n')
                    nextMove = move();
            }
            while (nextMove == 2) {
                selecter(&x2, &user);
                fseek(stdin, 0, SEEK_END);
                printf("더 담을까? y/n \n->");
                scanf_s("%c", &next);
                if (next == 'n')
                    nextMove = move();
            }
            while (nextMove == 3) {
                selecter(&x3, &user);
                fseek(stdin, 0, SEEK_END);
                printf("더 담을까? y/n \n->");
                scanf_s("%c", &next);
                if (next == 'n')
                    nextMove = move();
            }
            while (nextMove == 4) {
                escalator(&user);
                break;
            }
            while (nextMove == 5) {
                elevator(&user);
                break;
            }
            while (nextMove == 6) {
                printf("장바구니를 확인합니다\n");
                printmyinventory(user.myInventory);
                break;
            }
            while (nextMove == 7) {
                printf("뭘 사야하지?\n");
                printCL(checklist);
                break;
            }
            while (nextMove == 8) {
                counter(&user);
                exit = 1;
                break;
            }
        }
        else if (user.level == 2) {
            printf("현재 층: %d: %s \n", user.level, f2.category);
            printshop(f2.shopList);
            nextMove = move();
            while (nextMove == 1) {
                selecter(&A, &user);
                printf("더 담을까? y/n \n->");
                fseek(stdin, 0, SEEK_END);
                scanf_s("%c", &next);
                if (next == 'n')
                    nextMove = move();
            }
            while (nextMove == 2) {
                selecter(&S, &user);
                fseek(stdin, 0, SEEK_END);
                printf("더 담을까? y/n \n->");
                scanf_s("%c", &next);
                if (next == 'n')
                    nextMove = move();
            }
            while (nextMove == 3) {
                selecter(&L, &user);
                fseek(stdin, 0, SEEK_END);
                printf("더 담을까? y/n \n->");
                scanf_s("%c", &next);
                if (next == 'n')
                    nextMove = move();
            }
            while (nextMove == 4) {
                escalator(&user);
                break;
            }
            while (nextMove == 5) {
                elevator(&user);
                break;
            }
            while (nextMove == 6) {
                printf("장바구니를 확인합니다\n");
                printmyinventory(user.myInventory);
                break;
            }
            while (nextMove == 7) {
                printf("뭘 사야하지?\n");
                printCL(checklist);
                break;
            }
            while (nextMove == 8) {
                counter(&user);
                exit = 1;
                break;
            }

        }
        else {
            printf("현재 층: %d: %s \n", user.level, f3.category);
            printshop(f3.shopList);
            nextMove = move();
            while (nextMove == 1) {
                selecter(&hm, &user);
                printf("더 담을까? y/n \n->");
                fseek(stdin, 0, SEEK_END);
                scanf_s("%c", &next);
                if (next == 'n')
                    nextMove = move();
            }
            while (nextMove == 2) {
                selecter(&sec, &user);
                fseek(stdin, 0, SEEK_END);
                printf("더 담을까? y/n \n->");
                scanf_s("%c", &next);
                if (next == 'n')
                    nextMove = move();
            }
            while (nextMove == 3) {
                selecter(&nike, &user);
                fseek(stdin, 0, SEEK_END);
                printf("더 담을까? y/n \n->");
                scanf_s("%c", &next);
                if (next == 'n')
                    nextMove = move();
            }
            while (nextMove == 4) {
                escalator(&user);
                break;
            }
            while (nextMove == 5) {
                elevator(&user);
                break;
            }
            while (nextMove == 6) {
                printf("장바구니를 확인합니다\n");
                printmyinventory(user.myInventory);
                break;
            }
            while (nextMove == 7) {
                printf("뭘 사야하지?\n");
                printCL(checklist);
                break;
            }
            while (nextMove == 8) {
                counter(&user);
                exit = 1;
                break;
            }

        }
    }

    return 0;
}
