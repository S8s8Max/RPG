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

typedef struct Party
{
    char* playerName;
    Monster* monsters;
    int num_of_party_member;
    int party_HP;
} Party;


typedef struct DUNGEON
{
    Monster* monsters;
    const int num_of_monster;
} Dungeon;

/*** prototype declaration ***/
int goDungeon(Party* pParty, Dungeon* pDungeon);
int doBattle(char* playerName, Monster* pEnemy);
int calc_party_HP(int party_size, Monster* party_monsters);
//*** utility function ***/
void printMonsterName(Monster* pEnemy);
void printParty(Party* pParty);
/*** function -include main func- ***/

// (1)Game Start
int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Error : Type player name and start!\n");
        return 1;
    }

    printf("\n*** Puzzele & Monsters ***\n\n");

    // Set Party members
    Monster party_monsters[] = {
        {"Seiryu", Wind, 150, 150, 15, 10},
        {"Byakko", Earth, 150, 150, 20, 5},
        {"Genbu", Water, 150, 150, 20, 15},
        {"Suzaku", Fire, 150, 150, 25, 10}
    };
    int party_size = sizeof(party_monsters)/sizeof(Monster);
    int party_HP = calc_party_HP(party_size, party_monsters);
    Party party = {argv[1], party_monsters, party_size, party_HP};

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
    int winCount = goDungeon(&party, &dungeon);

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
int goDungeon(Party* pParty, Dungeon* dungeon)
{
    printf("%s's party (HP = %d) has arrived at Dungeon.\n\n", pParty->playerName, pParty->party_HP);
    printParty(pParty);
    int winCount = 0;
    for (int i = 0; i < dungeon->num_of_monster; ++i) {
        winCount += doBattle(pParty->playerName, &(dungeon->monsters[i]));
    }
    printf("\n%s conquered the Dungeon!\n", pParty->playerName);
    return winCount;
}

// (3) The flow from the beginning of the battle to the end
int doBattle(char* playerName, Monster* pEnemy)
{
    printMonsterName(pEnemy);
    printf(" appeared!\n");
    printf("You defeated ");
    printMonsterName(pEnemy);
    printf("\n%s goes forward...\n\n", playerName);
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

void printParty(Party* pParty)
{
    printf("< Party Members >");
    printf("--------------\n");
    for (int i = 0; i < pParty->num_of_party_member; ++i) {
        Monster* monster_name = &(pParty->monsters[i]);
        printMonsterName(monster_name);
        int HP = pParty->monsters[i].current_HP;
        int Attack = pParty->monsters[i].attack;
        int Defence = pParty->monsters[i].defense;
        printf(" HP= %3d AT= %2d DF= %2d\n", HP, Attack, Defence);
    }
    printf("-------------------------------\n");
}

int calc_party_HP(int party_size, Monster* party_monsters)
{
    int party_HP = 0;
    for (int i = 0; i < party_size; ++i) {
        party_HP += party_monsters[i].max_HP;
    }
    return party_HP;
}