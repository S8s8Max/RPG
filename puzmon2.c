/*=== puzmon0: source code ===*/
/*** include ***/

#include <stdio.h>

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
const char ELEMENT_COLORS[] = {1, 6, 2, 3, 5, 0};
/*** struct ***/
typedef struct MONSTER
{
    char name[25];
    int type;
    int current_HP;
    int max_HP;
    int attack;
    int defense;
} Monster;

typedef struct DUNGEON
{
    Monster* monsters;
    const int num_of_monster;
} Dungeon;

/*** prototype declaration ***/
int goDungeon(char* playerName, Dungeon* pDungeon);
int doBattle(char* playerName, Monster* pEnemy);
//*** utility function ***/
void printMonsterName(Monster* pEnemy);

/*** function -include main func- ***/

// (1)Game Start
int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Error : Type player name and start.");
        return 1;
    }

    printf("\n*** Puzzele & Monsters ***\n\n");

    // Set Monsters and Dungeon
    Monster dungeonMonsters[] = {
        {"Slime", Water, 100, 100, 10, 5},
        {"Goblin", Earth, 200, 200, 20, 15},
        {"Big Bat", Wind, 300, 300, 30, 25},
        {"Wolf", Wind, 400, 400, 40, 30},
        {"Dragon", Fire, 800, 800, 50, 40}
    };
    int number_of_monster = sizeof(dungeonMonsters)/sizeof(Monster);
    Dungeon dungeon = {dungeonMonsters, number_of_monster};
    
    // Into the Adventure
    int winCount = goDungeon(argv[1], &dungeon);

    // After the adventure
    if (winCount == dungeon.num_of_monster) {
        printf("\n*** GAME CLEAR! ***\n");
    } else {
        printf("\n*** GAME OVER ***\n");
    }
    printf("You beat %d monsters!!\n", winCount);
    return 0;
}

// (2) The flow from the beginning of a dungeon to the end
int goDungeon(char* playerName, Dungeon* dungeon)
{
    printf("%s has arrived at Dungeon.\n\n", playerName);

    int winCount = 0;
    for (int i = 0; i < dungeon->num_of_monster; ++i) {
        winCount += doBattle(playerName, &(dungeon->monsters[i]));
    }
    printf("\n%s conquered the Dungeon!\n", playerName);
    return winCount;
}

// (3) The flow from the beginning of the battle to the end
int doBattle(char* playerName, Monster* pEnemy)
{
    printMonsterName(pEnemy);
    printf(" appeared!\n");
    printf("You defeated ");
    printMonsterName(pEnemy);
    printf("\n\n");
    return 1;
}

/*** utility function ***/
void printMonsterName(Monster* pEnemy)
{
    char symbol = ELEMENT_SYMBOLS[pEnemy->type];
    int color = ELEMENT_COLORS[pEnemy->type];
    printf("\x1b[3%dm", color);
    printf("%c%s%c", symbol, pEnemy->name, symbol);
    printf("\x1b[0m");
}