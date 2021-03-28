#include "BattleField.h"
#include "Ships.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void generateTerranFleet(BattleField *battleField, const char *terranFleetStr) {
  vectorInit(&(battleField->terranFleet), strlen(terranFleetStr));

  for ( ; *terranFleetStr != '\0'; terranFleetStr++) {
    Ship *newShip = (Ship *) malloc(sizeof(Ship));
    if (*terranFleetStr == 'v') {
      initializeViking(newShip);
    } else if (*terranFleetStr == 'b') {
      initializeBattleCruiser(newShip);
    }
    vectorPush(&(battleField->terranFleet), newShip);
  }
}

void generateProtossFleet(BattleField *battleField, const char *protossFleetStr) {
  vectorInit(&(battleField->protossFleet), strlen(protossFleetStr));

  for ( ; *protossFleetStr != '\0'; protossFleetStr++) {
    Ship *newShip = (Ship *) malloc(sizeof(Ship));
    if (*protossFleetStr == 'p') {
      initializePhoenix(newShip);
    } else if (*protossFleetStr == 'c') {
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

bool processTerranTurn(BattleField *battleField) {
  Vector *terFleet = &(battleField->terranFleet);
  Vector *protFleet = &(battleField->protossFleet);
  Ship *attacker;
  Ship *enemy = (Ship*) vectorBack(protFleet);
  int enemyID = vectorGetSize(protFleet) - 1;
  static int cannonProgress = 1; /* Needed for Yamato cannon */

  for (size_t i = 0; i < vectorGetSize(terFleet); i++) {
    attacker = (Ship *) vectorGet(terFleet, i);

    if (attacker->type == VIKING) {
      vikingAttack(enemy);
      handleDestroyedShip(&enemy, protFleet, &enemyID, "Viking", (int) i);
    } else if (attacker->type == BATTLE_CRUSER) {
      battleCruserAttack(enemy, cannonProgress);
      handleDestroyedShip(&enemy, protFleet, &enemyID, "BattleCruser", (int) i);
    }

    if (vectorIsEmpty(protFleet)) {
      return true;
    }
  }
  cannonProgress++;
  printf("Last Protoss AirShip with ID: %d has %d health and %d shield left\n", enemyID, enemy->health, enemy->shield);
  return false;
}

bool processProtossTurn(BattleField *battleField) {
  Vector *terFleet = &(battleField->terranFleet);
  Vector *protFleet = &(battleField->protossFleet);
  Ship *attacker;
  Ship *enemy = (Ship*) vectorBack(terFleet);
  int enemyID = vectorGetSize(terFleet) - 1;

  for (size_t i = 0; i < vectorGetSize(protFleet); i++) {
    attacker = (Ship*) vectorGet(protFleet, i);

    if (attacker->type == PHOENIX) {
      phoenixAttack(enemy);
      handleDestroyedShip(&enemy, terFleet, &enemyID, "Phoenix", (int) i);
    } else if (attacker->type == CARRIER) {
      int attacks;
      if (attacker->health == CARRIER_HEALTH) {
        attacks = MAX_INTERCEPTORS;
      } else {
        attacks = DAMAGED_STATUS_INTERCEPTORS;
      }
      for (int j = 0; j < attacks; j++) {
        carrierAttack(enemy);
        handleDestroyedShip(&enemy, terFleet, &enemyID, "Carrier", (int) i);
        if (vectorIsEmpty(terFleet)) {
          return true;
        }
      }
    }

    if (vectorIsEmpty(terFleet)) {
      return true;
    }
    protossRegen(attacker);
  }
  printf("Last Terran AirShip with ID: %d has %d health left\n", enemyID, enemy->health);
  return false;
}

void handleDestroyedShip(Ship **enemy, Vector *fleet, int *enemyID, char *attackerString, int attackerID) {
  if ((*enemy)->health <= 0) {
    printf("%s with ID: %d killed enemy airship with ID: %d\n", attackerString, attackerID, *enemyID);
    vectorPop(fleet);
    free(*enemy);
    (*enemyID)--;
    *enemy = (Ship *) vectorBack(fleet);
  }
}

void deinit(BattleField *battleField) {
  Ship *ship;

  /* free terranFleet */
  while (!vectorIsEmpty(&(battleField->terranFleet))) {
    ship = (Ship *) vectorBack(&(battleField->terranFleet));
    vectorPop(&(battleField->terranFleet));
    free(ship);
  }

  /* free protossFleet */
  while (!vectorIsEmpty(&(battleField->protossFleet))) {
    ship = (Ship *) vectorBack(&(battleField->protossFleet));
    vectorPop(&(battleField->protossFleet));
    free(ship);
  }

  vectorFree(&(battleField->terranFleet));
  vectorFree(&(battleField->protossFleet));
}
