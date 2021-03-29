#ifndef SHIPS_H_
#define SHIPS_H_

#include "Defines.h"

typedef struct {
  enum AirShipType type;
  int id;
  int health;
  int shield;
} Ship;

void initializeViking(Ship *newShip, int id);
void initializeBattleCruiser(Ship *newShip, int id);

void initializePhoenix(Ship *newShip, int id);
void initializeCarrier(Ship *newShip, int id);

/* Attacks */

void vikingAttack(Ship *enemy);
void battleCruserAttack(Ship *enemy, int yamatoLoadingTurns);

void phoenixAttack(Ship *enemy);
void carrierAttack(Ship *enemy);
void protossRegen(Ship *self);

#endif /* SHIPS_H_ */