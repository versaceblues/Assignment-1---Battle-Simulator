I wasn't able to implement this code into my final project. I ran out of time. 

std::cout << "=== BATTLE ARENA ===\n";
    enemy->TauntPlayer();      
    player->NormalAttack();    
    enemy->TauntPlayer();      
    player->SpecialAttack();   
    enemy->NormalAttack();    
    enemy->NormalAttack();     
    player->SpecialAttack();   
    enemy->TauntPlayer();      
    player->SpecialAttack();


ok so we need to do what we did in our lab except we need to create classes 
for the player and classes for the enemy. 

we need to create header files. we need to create a main file for enemy and player. 

we need to create a battle simulator. we can copy the code from lab 3  and edit it. 

remember to make a youtube video. 

here's the code i used before adding the header files, which was based on lab3:

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Player
class Player {
public:
    string name;
    int health;
    int maxHealth;
    int potions;
    int baseDamage;

    Player(string playerName, int hp, int pots, int dmg) {
        name = playerName;
        health = hp;
        maxHealth = hp; 
        potions = pots;
        baseDamage = dmg;
    }

    virtual ~Player() = default;

    void TakeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    void Heal() {
        if (potions > 0) {
            health += 40;
            if (health > maxHealth) health = maxHealth; 
            potions--;
            cout << "\nYou drink a potion. Health restored to " << health << "!\n";
            cout << "Potions remaining: " << potions << "\n";
        } else {
            cout << "\nYou are out of potions!\n";
        }
    }

    virtual int GetAttackDamage() {
        return baseDamage + (rand() % 10);   // Default random damage
    }
};

// Wizard
class Wizard : public Player {
public:
    Wizard(string playerName) : Player(playerName, 85, 5, 18) {}   // Less HP, more potions, stronger magic

    int GetAttackDamage() override {
        return baseDamage + (rand() % 16);   // Higher damage variance
    }
};

// Knight
class Knight : public Player {
public:
    Knight(string playerName) : Player(playerName, 120, 2, 15) {}  // Tankier, fewer potions

    int GetAttackDamage() override {
        return baseDamage + (rand() % 8);    // More consistent damage
    }
};

// Enemy
struct Enemy {
    string name;
    int health;
    int attackDamage;
};

Enemy SpawnRandomEnemy() {
    Enemy e;
    int roll = rand() % 3;

    if (roll == 0) {
        e.name = "Goblin";
        e.health = 35;
        e.attackDamage = 12;
    } else if (roll == 1) {
        e.name = "Skeleton";
        e.health = 50;
        e.attackDamage = 17;
    } else {
        e.name = "Ogre";
        e.health = 70;
        e.attackDamage = 23;
    }
    return e;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "========================================\n";
    cout << "      THE ENDLESS BATTLE ARENA       \n";
    cout << "========================================\n\n";

    int choice = 0;
    string pName;

    while (true) {
        cout << "Choose your class:\n";
        cout << "1. Wizard\n";
        cout << "2. Knight\n";
        cout << "Enter choice (1 or 2): ";

        if (!(cin >> choice)) {
            cout << "> Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice != 1 && choice != 2) {
            cout << "> Invalid choice! Please enter 1 or 2.\n";
            continue;
        }
        break;
    }

    cout << "Enter your hero's name: ";
    cin >> pName;

    Player* player = nullptr;

    if (choice == 1) {
        player = new Wizard(pName);
        cout << "\nA powerful Wizard " << pName << " enters the arena!\n";
    } else {
        player = new Knight(pName);
        cout << "\nA mighty Knight " << pName << " enters the arena!\n";
    }

    int roomsCleared = 0;

    while (player->health > 0) {
        cout << "\n========================================\n";
        cout << "ROOM " << roomsCleared + 1 << "\n";
        cout << "========================================\n";

        Enemy enemy = SpawnRandomEnemy();
        cout << "A wild " << enemy.name << " appears!\n\n";

        while (enemy.health > 0 && player->health > 0) {
            cout << player->name << " HP: " << player->health 
                 << "   |   " << enemy.name << " HP: " << enemy.health << "\n";
            
            cout << "1. Attack\n";
            cout << "2. Heal (" << player->potions << " potions)\n";
            cout << "Action: ";

            int action = 0;
            if (!(cin >> action)) {
                cout << "> Invalid input! You lose your turn.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                // Enemy still attacks
            } else if (action == 1) {
                int damage = player->GetAttackDamage();
                cout << "> You strike the " << enemy.name << " for " << damage << " damage!\n";
                enemy.health -= damage;
                if (enemy.health < 0) enemy.health = 0;
            } else if (action == 2) {
                player->Heal();
            } else {
                cout << "> Invalid choice! You lose your turn.\n";
            }

            // Enemy counter attack
            if (enemy.health > 0 && player->health > 0) {
                cout << "> The " << enemy.name << " hits you for " 
                     << enemy.attackDamage << " damage!\n";
                player->TakeDamage(enemy.attackDamage);
            }
        }

        if (player->health > 0) {
            cout << "\n*** You defeated the " << enemy.name << "! ***\n";
            roomsCleared++;

            if (rand() % 4 == 0) {   // 25% chance
                player->potions++;
                cout << "*** You found a potion! (+1) ***\n";
            }
        }
    }

    cout << "\n========================================\n";
    cout << "               GAME OVER\n";
    cout << player->name << " has fallen...\n";
    cout << "Total Rooms Cleared: " << roomsCleared << "\n";
    cout << "========================================\n";

    return 0;
}