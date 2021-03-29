#ifndef BATTLEFIELD_H_
#define BATTLEFIELD_H_

#include <stdbool.h>
#include "Vector.h"
#include "Ships.h"

typedef struct {
  Vector terranFleet;
  Vector protossFleet;
} BattleField;

/* Allocates memory for each terran ship and initializes it from 'terranFleetStr' */
/* Initializes the terranFleet vector and pushes each ship */
void generateTerranFleet(BattleField *battleField, const char *terranFleetStr);

/* Allocates memory for each protoss ship and initializes it from 'protossFleetStr' */
/* Initializes the protossFleet vector and pushes each ship */
void generateProtossFleet(BattleField *battleField, const char *protossFleetStr);

/* Process each race's turn until one wins */
void startBattle(BattleField *battleField);

/* Iterates through the fleet; processes the attacks and destroyed enemy ships */
/* Returns true if no enemies are left */
bool processTerranTurn(BattleField *battleField);

/* Iterates through the fleet; processes the attacks, shield regen and destroyed enemy ships */
/* Returns true if no enemies are left */
bool processProtossTurn(BattleField *battleField);

/* If 'enemy' has been destroyed, free it and take the next enemy from 'fleet' */
void handleDestroyedShip(Ship **enemy, Vector *fleet, char *attackerString, int attackerID);

/* Frees the remaining ships. Deinitializes the fleet vectors */
void deinit(BattleField *battleField);

#endif /* BATTLEFIELD_H_ */
