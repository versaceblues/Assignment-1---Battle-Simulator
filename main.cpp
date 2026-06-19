#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// custom headers
#include "Player.h"
#include "Wizard.h"
#include "Knight.h"
#include "Enemy.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "========================================\n";
    cout << "      ENDLESS: BATTLE ARENA       \n";
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
                cout << "> Invalid choice! You hesitate and lose your turn.\n";
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
    cout << "========================================\n";
    cout << player->name << " has fallen...\n";
    cout << "Total Rooms Cleared: " << roomsCleared << "\n";
    cout << "========================================\n";

    delete player;
    return 0;
}