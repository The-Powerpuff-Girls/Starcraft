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
      initializeViking(newShip);
    }
    else if (*terranFleetStr == 'b') {
      initializeBattleCruiser(newShip);
    }
    vectorPush(&(battleField->terranFleet), newShip);
  }
}

void generateProtossFleet(BattleField *battleField, const char *protossFleetStr) {
  vectorInit(&(battleField->protossFleet), strlen(protossFleetStr));

  for ( ; *protossFleetStr != '\0' ; protossFleetStr++) {
    ProtossShip *newShip = (ProtossShip*)malloc(sizeof(ProtossShip));
    if(*protossFleetStr == 'p') {
      initializePhoenix(newShip);
    } 
    else if (*protossFleetStr == 'c') {
      initializeCarrier(newShip);
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

