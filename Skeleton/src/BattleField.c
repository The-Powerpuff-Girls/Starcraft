#include "BattleField.h"
#include "Ships.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Allocates memory for each terran ship and initializes it from 'terranFleetStr' */
/* Initializes the terranFleet vector and pushes each ship */
void generateTerranFleet(BattleField *battleField, const char *terranFleetStr) {
  vectorInit(&(battleField->terranFleet), strlen(terranFleetStr));

  for (int i = 0; terranFleetStr[i] != '\0'; i++) {
    Ship *newShip = (Ship *) malloc(sizeof(Ship));

    if (terranFleetStr[i] == 'v') {
      initializeViking(newShip, i);
    } else if (terranFleetStr[i] == 'b') {
      initializeBattleCruiser(newShip, i);
    }

    vectorPush(&(battleField->terranFleet), newShip);
  }
}

/* Allocates memory for each protoss ship and initializes it from 'protossFleetStr' */
/* Initializes the protossFleet vector and pushes each ship */
void generateProtossFleet(BattleField *battleField, const char *protossFleetStr) {
  vectorInit(&(battleField->protossFleet), strlen(protossFleetStr));

  for (int i = 0; protossFleetStr[i] != '\0'; i++) {
    Ship *newShip = (Ship *) malloc(sizeof(Ship));
    
    if (protossFleetStr[i] == 'p') {
      initializePhoenix(newShip, i);
    } else if (protossFleetStr[i] == 'c') {
      initializeCarrier(newShip, i);
    }

    vectorPush(&(battleField->protossFleet), newShip);
  }
}

/* Process each race's turn until one wins */
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

/* Iterates through the fleet; processes the attacks and destroyed enemy ships */
/* Returns true if no enemies are left */
bool processTerranTurn(BattleField *battleField) {
  Vector *terFleet = &(battleField->terranFleet);
  Vector *protFleet = &(battleField->protossFleet);
  Ship *attacker;
  Ship *enemy = (Ship*) vectorBack(protFleet);

  static int cannonProgress = 1; /* Used by BattleCruser's special ability */

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

/* Iterates through the fleet; processes the attacks, shield regen and destroyed enemy ships */
/* Returns true if no enemies are left */
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
      /* Decide number of Carrier attacks based on health */
      int attacks;
      if (attacker->health == CARRIER_HEALTH) {
        attacks = MAX_INTERCEPTORS;
      } else {
        attacks = DAMAGED_STATUS_INTERCEPTORS;
      }
      /* Perform Carrier attacks */
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

/* If 'enemy' has been destroyed, free it and take the next enemy from 'fleet' */
void handleDestroyedShip(Ship **enemy, Vector *fleet, char *attackerString, int attackerID) {
  if ((*enemy)->health <= 0) {
    printf("%s with ID: %d killed enemy airship with ID: %d\n", attackerString, attackerID, (*enemy)->id);
    vectorPop(fleet);
    free(*enemy);
    *enemy = (Ship *) vectorBack(fleet);
  }
}

/* Frees the remaining ships. Deinitializes the fleet vectors */
void deinit(BattleField *battleField) {
  Ship *ship;

  /* Free terranFleet */
  while (!vectorIsEmpty(&(battleField->terranFleet))) {
    ship = (Ship *) vectorBack(&(battleField->terranFleet));
    vectorPop(&(battleField->terranFleet));
    free(ship);
  }

  /* Free protossFleet */
  while (!vectorIsEmpty(&(battleField->protossFleet))) {
    ship = (Ship *) vectorBack(&(battleField->protossFleet));
    vectorPop(&(battleField->protossFleet));
    free(ship);
  }

  vectorFree(&(battleField->terranFleet));
  vectorFree(&(battleField->protossFleet));
}
