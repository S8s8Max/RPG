/*=== puzmon0: source code ===*/
/*** include ***/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

/*** enum ***/
typedef enum Element
{FIRE, WATER, WIND, EARTH, LIFE, EMPTY} Element;

/*** global const ***/

// (1) The symbols representing monsters' elements.
const char ELEMENT_SYMBOLS[EMPTY+1] = {'$', '~', '@', '#', '&', ' '};
// (2) The Color codes representing monsters' element.
const char ELEMENT_COLORS[EMPTY+1] = {1, 6, 2, 3, 5, 0};
// (3) The number of gems
enum {MAX_GEMS = 14};

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
typedef struct BATTLE_FIELD
{
    Party* pParty;
    Monster* pEnemy;
    Element gems[MAX_GEMS];
} BattleField;

/*** prototype declaration ***/
int goDungeon(Party* pParty, Dungeon* pDungeon);
int doBattle(Party* pParty, Monster* pEnemy);
Party organizeParty(char *playerName, Monster* monsters, int num_of_party_member);
void printParty(Party* pParty);
void onPlayerTurn(BattleField* pField);
void onEnemyTurn(BattleField* pField);
void doPlayerAttack(BattleField* pField);
void doEnemyAttack(BattleField* pField);
void printBattleField(BattleField* pField);
bool checkValidCommand(char* command);
void evaluateGems(BattleField* pField);

//*** utility function ***/
void printMonsterName(Monster* pEnemy);
void fillGems(Element* gems, bool emptyOnly);
void printGems(Element* gems);
void printGem(Element element);
void moveGem(Element* gems, int fromPos, int toPos);
void swapGem(Element* gems, int pos, int step);

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
        {"Seiryu", WIND, 150, 150, 15, 10},
        {"Byakko", EARTH, 150, 150, 20, 5},
        {"Genbu",  WATER, 150, 150, 20, 15},
        {"Suzaku", FIRE, 150, 150, 25, 10}
    };
    int size = sizeof(party_monsters)/sizeof(Monster);
    Party party = organizeParty(argv[1], party_monsters, size);

    // int party_size = sizeof(party_monsters)/sizeof(Monster);
    // int party_HP = calc_party_HP(party_size, party_monsters);
    // Party party = {argv[1], party_monsters, party_size, party_HP};

    // Set Monsters and Dungeon
    Monster dungeonMonsters[] = {
        {"Slime", WATER, 100, 100, 10, 5},
        {"Goblin", EARTH, 200, 200, 20, 15},
        {"Big Bat", WIND, 300, 300, 30, 25},
        {"Wolf", WIND, 400, 400, 40, 30},
        {"Dragon", FIRE, 800, 800, 50, 40}
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
    printf("   .\n");
    printf("   .\n");
    printf("   .\n");
    printMonsterName(pEnemy);
    printf(" appeared!\n");

    BattleField field = {pParty, pEnemy};
    fillGems(field.gems, false);

    // Battle
    while (true) {
        onPlayerTurn(&field);
        if (pEnemy->current_HP <= 0) {
            printMonsterName(pEnemy);
            printf(" was defeated.\n");
            return 1;
        }
        onEnemyTurn(&field);
        if (pParty->party_HP <= 0) {
            printf("%s was defeated...\n\n", pParty->playerName);
            return 0;
        }
    }
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
    printf("----------\n\n");
    for (int i = 0; i < pParty->num_of_party_member; ++i) {
        printMonsterName(&(pParty->monsters[i]));
        printf(" HP=%4d AT=%3d DF=%3d\n",
            pParty->monsters[i].max_HP,
            pParty->monsters[i].attack,
            pParty->monsters[i].defense
        );
    }
    printf("\n-------------------------------\n\n");
}
void onPlayerTurn(BattleField *pField)
{
    printf("\n [%s's turn]\n", pField->pParty->playerName);

    printBattleField(pField);

    // The detail of a battle.
    char command[3];
    do {
        printf(" Command ? >");
        scanf("%2s", command);
    } while (checkValidCommand(command) == false);

    moveGem(pField->gems, command[0] - 'A', command[1] - 'A');
    evaluateGems(pField);
}
void doPlayerAttack(BattleField *pField)
{
    pField->pEnemy->current_HP -= 80;
    printf("Atack! %d damages.\n\n", 80);
}
void onEnemyTurn(BattleField *pField)
{
    printf("\n [%s's turn]\n", pField->pEnemy->name);
    doEnemyAttack(pField);
}
void doEnemyAttack(BattleField *pField)
{
    pField->pParty->party_HP -= 20;
    printf("Attack! You got %d damages.\n", 20);
}
void printBattleField(BattleField* pField)
{
    printf("------------------------------\n\n");
    printf("          ");
    printMonsterName(pField->pEnemy);
    printf("\n        HP= %4d / %4d\n",
            pField->pEnemy->current_HP,
            pField->pEnemy->max_HP);
    printf("\n\n");
    for (int i = 0; i < pField->pParty->num_of_party_member; ++i) {
        printMonsterName(&(pField->pParty->monsters[i]));
        printf("  ");
    }
    printf("\n");
    printf("        HP= %4d / %4d\n",
            pField->pParty->party_HP,
            pField->pParty->party_max_HP);
    printf("------------------------------\n");
    printf(" ");
    for (int i = 0; i < MAX_GEMS; ++i) {
        printf("%c ", 'A' + i);
    }
    printf("\n");
    printGems(pField->gems);
    printf("\n------------------------------\n");
}
bool checkValidCommand(char* command)
{
    if (strlen(command) != 2) return false;
    if (command[0] == command[1]) return false;
    if (command[0] < 'A' || command[0] > 'A' + MAX_GEMS - 1) return false;
    if (command[1] < 'A' || command[1] > 'A' + MAX_GEMS - 1) return false;
    return true;
}
void evaluateGems(BattleField* pField)
{
    /* for (int i = 2; i < MAX_GEMS; ++i) {
        if (pField->gems[i-2] == pField->gems[i-1] == pField->gems[i]) {
            switch (i)
            {
            case FIRE:
                printf("\n Fire Bless! %3d Damage!", 100);
                pField->pEnemy->current_HP -= 100;
                break;
            case WATER:
                printf("\n Water Spear! %3d Damage!", 100);
                pField->pEnemy->current_HP -= 100;
                break;
            case WIND:
                printf("\n Wind Cutter! %3d Damage!", 100);
                pField->pEnemy->current_HP -= 100;
                break;
            case EARTH:
                printf("\n Gigant Rocks! %3d Damage!", 100);
                pField->pEnemy->current_HP -= 100;
                break;
            case LIFE:
                printf("\n Healing! %3d HP healed", 100);
                if (pField->pParty->party_HP < pField->pParty->party_max_HP) {
                    if (pField->pParty->party_max_HP - pField->pParty->party_HP < 100) {
                        int plus_life = pField->pParty->party_max_HP - pField->pParty->party_HP;
                        pField->pParty->party_HP += plus_life;
                        break;
                    } else {
                        pField->pParty->party_HP += 100;
                    }
                }
                break;
            case EMPTY:
                printf("\n Strong Attack! %3d Damage!", 100);
                pField->pEnemy->current_HP -= 100;
                break;
            }
            pField->gems[i] = (Element)(rand() % EMPTY);
            pField->gems[i-1] = (Element)(rand() % EMPTY);
            pField->gems[i-2] = (Element)(rand() % EMPTY);
            i += 2;
        }
    }
    */
    doPlayerAttack(pField);
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
void fillGems(Element* gems, bool emptyOnly)
{
    for (int i = 0; i < MAX_GEMS; ++i) {
        if (!emptyOnly || gems[i] == EMPTY) {
            gems[i] = (Element)(rand() % EMPTY);
        }
    }
}

void printGems(Element* gems)
{
    for (int i = 0; i < MAX_GEMS; ++i) {
        printf(" ");
        printGem(gems[i]);
    }
    printf("\n");
}
void printGem(Element gem)
{
    printf("\x1b[30m");                     // Black letters
    printf("\x1b[4%dm", ELEMENT_COLORS[gem]); // Background color of the element
    printf("%c", ELEMENT_SYMBOLS[gem]);
    printf("\x1b[0m");                      // Release the color identifier
}
void moveGem(Element* gems, int fromPos, int toPos)
{
    // Direction (1 = right, -1 = left)
    int step = (toPos > fromPos) ? 1 : -1;
    
    printGems(gems);
    for (int i = fromPos; i != toPos; i += step) {
        swapGem(gems, i, step);
        printGems(gems);
    }
}

// Swap the gem at gems["pos"] with the gem which is 
// "step" times far from the gem at gems["pos"].
void swapGem(Element* gems, int pos, int step)
{
    Element buf = gems[pos];
    gems[pos] = gems[pos + step];
    gems[pos + step] = buf;
}