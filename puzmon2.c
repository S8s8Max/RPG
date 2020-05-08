/*=== puzmon0: source code ===*/
/*** include ***/

#include <bits/stdc++.h>

/*** enum ***/
typedef enum Element
{
    Fire,
    Water,
    Wind,
    Earth,
    Life,
    Empty,
} Element;

/*** global const ***/
const char ELEMENT_SYMBOLS[] = {'$', '~', '@', '#', '&', ' '};
const char ELEMENT_COLORS[] = {"\e[31m", "\e[34m", "\e[32m", "\e[33m", "\e[35m", "\e[30m"};
int num = 0;
/*** struct ***/
typedef struct Monster
{
    char name[25];
    int type;
    int current_HP;
    int max_HP;
    int attack;
    int defense;
} Monster;

typedef struct Dungeon
{
    Monster monsters[20];
} Dungeon;

/*** prototype ***/

/*** function ***/
void printMonsterName(Monster monster);

void doBattle(Monster monster)
{
    printMonsterName(monster);
    num++;
}

void goDungeon(char* playerName)
{
    printf("\n%s has arrived at a dungeon.\n", playerName);
    Monster slime = {"Slime", Water, 100, 100, 10, 5};
    Monster goblin = {"Goblin", Earth, 200, 200, 20, 15};
    Monster big_bat = {"Big Bat", Wind, 300, 300, 30, 25};
    Monster wolf = {"Wolf", Wind, 400, 400, 40, 30};
    Monster dragon = {"Dragon", Fire, 800, 800, 50, 40};
    doBattle(slime);
    doBattle(goblin);
    doBattle(big_bat);
    doBattle(wolf);
    doBattle(dragon);
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
void printMonsterName(Monster monster)
{
    char symbol, color;
    switch (monster.type)
    {
    case Fire:
        symbol = ELEMENT_SYMBOLS[Fire];
        color = ELEMENT_COLORS[Fire];
        printf("color%ccolor%scolor%c", symbol, monster.name, symbol);
        return;
    case Water:
        symbol = ELEMENT_SYMBOLS[Fire];
        color = ELEMENT_COLORS[Fire];
        printf("color%ccolor%scolor%c", symbol, monster.name, symbol);
        return;
    case Wind:
        symbol = ELEMENT_SYMBOLS[Fire];
        color = ELEMENT_COLORS[Fire];
        printf("color%ccolor%scolor%c", symbol, monster.name, symbol);
        return;
    case Earth:
        symbol = ELEMENT_SYMBOLS[Fire];
        color = ELEMENT_COLORS[Fire];
        printf("color%ccolor%scolor%c", symbol, monster.name, symbol);
        return;
    case Empty:
        symbol = ELEMENT_SYMBOLS[Fire];
        color = ELEMENT_COLORS[Fire];
        printf("color%ccolor%scolor%c", symbol, monster.name, symbol);
        return;
    }
    printf(" appeared!\n");
    printf("You defeated %s!\n", monster.name);
}

