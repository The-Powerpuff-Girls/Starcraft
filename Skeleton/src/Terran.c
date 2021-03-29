#include "Ships.h"

void initializeViking(Ship *newShip, int id) {
  newShip->type = VIKING;
  newShip->id = id;
  newShip->health = VIKING_HEALTH;
}

void initializeBattleCruiser(Ship *newShip, int id) {
  newShip->type = BATTLE_CRUSER;
  newShip->id = id;
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

/* Yamato Loading Turns is the current Terran turn, same for each battle cruiser */
void battleCruserAttack(Ship *enemy, int yamatoLoadingTurns) {
  int damage = BATTLE_CRUSER_DAMAGE;

  /* Bonus damage every X number of turns */
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