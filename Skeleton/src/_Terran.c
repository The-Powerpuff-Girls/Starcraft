#include "../include/TerranShip.h"
#include "../include/ProtossShip.h"

void initializeViking(TerranShip *newShip) {
  newShip->type = VIKING;
  newShip->health = VIKING_HEALTH;
  newShip->damage = VIKING_DAMAGE;
}

void initializeBattleCruiser(TerranShip *newShip) {
  newShip->type = BATTLE_CRUSER;
  newShip->health = BATTLE_CRUSER_HEALTH;
  newShip->damage = BATTLE_CRUSER_DAMAGE;
}

void vikingAttack(ProtossShip *enemy) {
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

void battleCruserAttack(ProtossShip *enemy, int yamatoLoadingTurns) {
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