#include "BattleField.h"
#include "ProtossShip.h"
#include "TerranShip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void generateTerranFleet(BattleField *battleField, const char *terranFleetStr) {
  vectorInit(&(battleField->terranFleet), strlen(terranFleetStr));

  for ( ; *terranFleetStr != '\0' ; terranFleetStr++) {
    TerranShip *newShip = (TerranShip*) malloc(sizeof(TerranShip));
    if (*terranFleetStr == 'v') {
      newShip->type = VIKING;
      newShip->health = VIKING_HEALTH;
      newShip->damage = VIKING_DAMAGE;
    }
    else if (*terranFleetStr == 'b') {
      newShip->type = BATTLE_CRUSER;
      newShip->health = BATTLE_CRUSER_HEALTH;
      newShip->damage = BATTLE_CRUSER_DAMAGE;
    }
    vectorPush(&(battleField->terranFleet), newShip);
  }
}

void generateProtossFleet(BattleField *battleField, const char *protossFleetStr){
  vectorInit(&(battleField->protossFleet), strlen(protossFleetStr));

  for ( ; *protossFleetStr != '\0' ; protossFleetStr++) {
    ProtossShip *newShip = (ProtossShip*)malloc(sizeof(ProtossShip));
    if(*protossFleetStr == 'p') {
      newShip->type = PHOENIX;
      newShip->health = PHOENIX_HEALTH;
      newShip->shield = PHOENIX_SHIELD;
      newShip->damage = PHOENIX_DAMAGE;      
      newShip->regenRate = PHOENIX_SHIELD_REGENERATE_RATE;
    } 
    else if (*protossFleetStr == 'c') {
      newShip->type = CARRIER;
      newShip->health = CARRIER_HEALTH;
      newShip->shield = CARRIER_SHIELD;
      newShip->damage = CARRIER_DAMAGE;
      newShip->regenRate = CARRIER_SHIELD_REGENERATE_RATE;
    }
    vectorPush(&(battleField->protossFleet), newShip);
  }
}

void startBattle(BattleField *battleField) {
  while (true) {
    if (processTerranTurn(battleField)) {
      printf("TERRAN has won!\n");
      break;
    }

    if (processProtossTurn(battleField)) {
      printf("PROTOSS has won!\n");
      break;
    }
  }
}

void deinit(BattleField *battleField) {
}

bool processTerranTurn(BattleField *battleField) {
  return false;
}

bool processProtossTurn(BattleField *battleField) {
  return false;
}

