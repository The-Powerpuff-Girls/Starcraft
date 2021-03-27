<<<<<<< Updated upstream
#include "../include/TerranShip.h"
#include "../include/ProtossShip.h"

void initializeViking(TerranShip *newShip) {
=======
#include "Ships.h"

void initializeViking(Ship *newShip) {
>>>>>>> Stashed changes
  newShip->type = VIKING;
  newShip->health = VIKING_HEALTH;
}

void initializeBattleCruiser(Ship *newShip) {
  newShip->type = BATTLE_CRUSER;
  newShip->health = BATTLE_CRUSER_HEALTH;
}

void vikingAttack(Ship *enemy) {
  int damage = VIKING_DAMAGE;
  
  if (enemy->type == PHOENIX) {
    damage *= VIKING_VS_PHOENIX_BONUS;
  }

  if (damage > enemy->shield) {
    damage -= enemy->shield;
    enemy->shield = 0;
    enemy->health -= damage;
  } else {
    enemy->shield -= damage;
  }
}

void battleCruserAttack(Ship *enemy, int yamatoLoadingTurns) {
  int damage = BATTLE_CRUSER_DAMAGE;

  if (yamatoLoadingTurns % YAMATO_CANNON_LOADING_TURNS == 0) {
    damage *= YAMATO_CANNON_BONUS;
  }

  if (damage > enemy->shield) {
    damage -= enemy->shield;
    enemy->shield = 0;
    enemy->health -= damage;
  } else {
    enemy->shield -= damage;
  }
}