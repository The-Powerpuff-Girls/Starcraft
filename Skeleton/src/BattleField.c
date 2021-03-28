#include "BattleField.h"
#include "Ships.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void generateTerranFleet(BattleField *battleField, const char *terranFleetStr) {
  vectorInit(&(battleField->terranFleet), strlen(terranFleetStr));

  for (int i = 0; terranFleetStr[i] != '\0'; i++) {
    Ship *newShip = (Ship *) malloc(sizeof(Ship));
    if (*terranFleetStr == 'v') {
      initializeViking(newShip, i);
    } else if (*terranFleetStr == 'b') {
      initializeBattleCruiser(newShip, i);
    }
    vectorPush(&(battleField->terranFleet), newShip);
  }
}

void generateProtossFleet(BattleField *battleField, const char *protossFleetStr) {
  vectorInit(&(battleField->protossFleet), strlen(protossFleetStr));

  for (int i = 0; protossFleetStr[i] != '\0'; i++) {
    Ship *newShip = (Ship *) malloc(sizeof(Ship));
    if (*protossFleetStr == 'p') {
      initializePhoenix(newShip, i);
    } else if (*protossFleetStr == 'c') {
      initializeCarrier(newShip, i);
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
  static int cannonProgress = 1; /* Needed for Yamato cannon */

  for (size_t i = 0; i < vectorGetSize(terFleet); i++) {
    attacker = (Ship *) vectorGet(terFleet, i);

    if (attacker->type == VIKING) {
      vikingAttack(enemy);
      handleDestroyedShip(&enemy, protFleet, "Viking", attacker->id);
    } else if (attacker->type == BATTLE_CRUSER) {
      battleCruserAttack(enemy, cannonProgress);
      handleDestroyedShip(&enemy, protFleet, "BattleCruser", attacker->id);
    }

    if (vectorIsEmpty(protFleet)) {
      return true;
    }
  }
  cannonProgress++;
  printf("Last Protoss AirShip with ID: %d has %d health and %d shield left\n", enemy->id, enemy->health, enemy->shield);
  return false;
}

bool processProtossTurn(BattleField *battleField) {
  Vector *terFleet = &(battleField->terranFleet);
  Vector *protFleet = &(battleField->protossFleet);
  Ship *attacker;
  Ship *enemy = (Ship*) vectorBack(terFleet);

  for (size_t i = 0; i < vectorGetSize(protFleet); i++) {
    attacker = (Ship*) vectorGet(protFleet, i);

    if (attacker->type == PHOENIX) {
      phoenixAttack(enemy);
      handleDestroyedShip(&enemy, terFleet, "Phoenix", attacker->id);
    } else if (attacker->type == CARRIER) {
      int attacks;
      if (attacker->health == CARRIER_HEALTH) {
        attacks = MAX_INTERCEPTORS;
      } else {
        attacks = DAMAGED_STATUS_INTERCEPTORS;
      }
      for (int j = 0; j < attacks; j++) {
        carrierAttack(enemy);
        handleDestroyedShip(&enemy, terFleet, "Carrier", attacker->id);
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
  printf("Last Terran AirShip with ID: %d has %d health left\n", enemy->id, enemy->health);
  return false;
}

void handleDestroyedShip(Ship **enemy, Vector *fleet, char *attackerString, int attackerID) {
  if ((*enemy)->health <= 0) {
    printf("%s with ID: %d killed enemy airship with ID: %d\n", attackerString, attackerID, (*enemy)->id);
    vectorPop(fleet);
    free(*enemy);
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

