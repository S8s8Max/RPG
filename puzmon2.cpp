/*=== puzmon0: source code ===*/
/*** include ***/

#include <bits/stdc++.h>

/*** enum ***/
typedef enum
{
    Fire,
    Water,
    Wind,
    Earth,
    Life,
    Empty,
} Element;

/*** global const ***/
#define ELEMENT_SYMBOLS = {'$', '~', '@', '#', '&', ' '};
#define ELEMENT_COLORS = {"\e[31m", "\e[34m", "\e[32m", "\e[33m", "\e[35m", "\e[30m"};
int num = 0;
/*** struct ***/
typedef struct
{
    char name[50];
    int type;
    int current_HP;
    int max_HP;
    int attack;
    int defense;
} Monster;

typedef struct
{
    Monster monsters[];
} Dungeon;

/*** prototype ***/

/*** function ***/
void printMonsterName(Monster monster);

void doBattle(char* monsterName)
{
    printf("\nA %s appeared!\n", monsterName);
    printf("You defeated %s!\n", monsterName);
}

void goDungeon(char* playerName)
{
    printf("\n%s has arrived at a dungeon.\n", playerName);
    Monster slime = {"Slime", 1, 100, 100, 10, 5};
    Monster goblin = {"Goblin", 3, 200, 200, 20, 15};
    Monster big_bat = {"Big Bat", 2, 300, 300, 30, 25};
    Monster wolf = {"Wolf", 2, 400, 400, 40, 30};
    Monster dragon = {"Dragon", 0, 800, 800, 50, 40};
    doBattle(slime.name); num++;
    doBattle(goblin.name); num++;
    doBattle(big_bat.name); num++;
    doBattle(wolf.name); num++;
    doBattle(dragon.name); num++;
}


int main(int argc, char** argv)
{
    printf("\n\e[3m*** Puzzele & Monsters ***\n");
    goDungeon(argv[1]);
    printf("\n*** Game Cleared! ***\n");
    printf("You beat %d monsters!!", num);
    return 0;
}

/*** utility ***/
void printMonsterName(Monster* monster)
{
    int type = (*monster).type;
    char t;
    switch (type){
    case Fire:
        t = ELEMENT_SYMBOLS[0];
        printf("\x1b[31m%c\x1b[31m%c\x1b[31m%c", t, monster->name, t);
    case Water:
        t = ELEMENT_SYMBOLS[1];
        printf("\x1b[31m%c\x1b[31m%c\x1b[31m%c", t, monster->name, t);
    case Wind:
        t = ELEMENT_SYMBOLS[2];
        printf("\x1b[31m%c\x1b[31m%c\x1b[31m%c", t, monster->name, t);
    case Earth:
        t = ELEMENT_SYMBOLS[3];
        printf("\x1b[31m%c\x1b[31m%c\x1b[31m%c", t, monster->name, t);
    case Life:
        t = ELEMENT_SYMBOLS[4];
        printf("\x1b[31m%c\x1b[31m%c\x1b[31m%c", t, monster->name, t);
    case Empty:
        t = ELEMENT_SYMBOLS[5];
        printf("\x1b[31m%c\x1b[31m%c\x1b[31m%c", t, monster->name, t);
    }
}

