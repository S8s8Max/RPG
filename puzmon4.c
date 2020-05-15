/*=== puzmon0: source code ===*/
/*** include ***/

#include <stdio.h>
#include <stdbool.h>

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
    char* name;
    Element element;
    int current_HP;
    int max_HP;
    int attack;
    int defense;
} Monster;

typedef struct PARTY
{
    char* playerName;
    Monster* monsters;
    const int num_of_party_member;
    const int party_max_HP;
    int party_HP;
    const int defense;
} Party;

typedef struct DUNGEON
{
    Monster* monsters;
    const int num_of_monster;
} Dungeon;

/*** prototype declaration ***/
int goDungeon(Party* pParty, Dungeon* pDungeon);
int doBattle(Party* pParty, Monster* pEnemy);
Party organizeParty(char *playerName, Monster* monsters, int num_of_party_member);
void printParty(Party* pParty);
void onPlayerTurn(Party* pParty, Monster* pEnemy);
void onEnemyTurn(Party* pParty, Monster* pEnemy);
void doPlayerAttack(Monster* pEnemy);
void doEnemyAttack(Party* pParty);
//*** utility function ***/
void printMonsterName(Monster* pEnemy);
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
        {"Genbu",  Water, 150, 150, 20, 15},
        {"Suzaku", Fire, 150, 150, 25, 10}
    };
    int size = sizeof(party_monsters)/sizeof(Monster);
    Party party = organizeParty(argv[1], party_monsters, size);

    // int party_size = sizeof(party_monsters)/sizeof(Monster);
    // int party_HP = calc_party_HP(party_size, party_monsters);
    // Party party = {argv[1], party_monsters, party_size, party_HP};

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
        winCount += doBattle(pParty, &(dungeon->monsters[i]));
        if (pParty->party_HP <= 0) {
            printf("%s ran away from the dungeon...", pParty->playerName);
            printf("===================================\n\n");
        }
    }
    
    printf("\n%s conquered the Dungeon!\n", pParty->playerName);
    return winCount;
}

// (3) The flow from the beginning of the battle to the end
int doBattle(Party* pParty, Monster* pEnemy)
{
    // Encount
    printMonsterName(pEnemy);
    printf(" appeared!\n");

    // Battle
    while (true) {
        onPlayerTurn(pParty, pEnemy);
        if (pEnemy->current_HP <= 0) {
            printMonsterName(pEnemy);
            printf(" was defeated.\n");
            return 1;
        }
        onEnemyTurn(pParty, pEnemy);
        if (pParty->party_HP <= 0) {
            printf("%s was defeated...\n\n", pParty->playerName);
            return 0;
        }
    }
}

void onPlayerTurn(Party* pParty, Monster* pEnemy)
{
    printf("\n [%s's turn]\n", pParty->playerName);
    doPlayerAttack(pEnemy);
}
void doPlayerAttack(Monster* pEnemy)
{
    pEnemy->current_HP -= 80;
    printf("Atack! %d damages.\n\n", 80);
}
void onEnemyTurn(Party* pParty, Monster* pEnemy)
{
    printf("\n [%s's turn]\n", pEnemy->name);
    doEnemyAttack(pParty);
}
void doEnemyAttack(Party* pParty)
{
    pParty->party_HP -= 20;
    printf("Attack! You got %d damages.\n", 20);
    return;
}

Party organizeParty(char* playerName, Monster* party_monsters, int num_of_party_member)
{
    int party_HP = 0;
    int defense = 0;
    for (int i = 0; i < num_of_party_member; ++i) {
        party_HP += party_monsters[i].max_HP;
        defense += party_monsters[i].defense;
    }
    int average_defense = defense / num_of_party_member;

    Party party = {playerName,
                   party_monsters,
                   num_of_party_member,
                   party_HP,
                   party_HP,
                   defense};
    return party;
}

void printParty(Party* pParty)
{
    printf("< Party Information >");
    printf("--------------\n");
    for (int i = 0; i < pParty->num_of_party_member; ++i) {
        printMonsterName(&(pParty->monsters[i]));
        printf(" HP=%4d AT=%3d DF=%3d\n",
            pParty->monsters[i].max_HP,
            pParty->monsters[i].attack,
            pParty->monsters[i].defense
        );
    }
    printf("-------------------------------\n");
}

/*** utility function ***/
void printMonsterName(Monster* pMonster)
{
    char symbol = ELEMENT_SYMBOLS[pMonster->element];
    int color = ELEMENT_COLORS[pMonster->element];
    printf("\x1b[3%dm", color);
    printf("%c%s%c", symbol, pMonster->name, symbol);
    printf("\x1b[0m");
}