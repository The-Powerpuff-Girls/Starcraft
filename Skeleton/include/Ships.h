#ifndef SHIPS_H_
#define SHIPS_H_

#include "Defines.h"

typedef struct {
  enum AirShipType type;
  int health;
  int shield;
} Ship;

void initializeViking(Ship *newShip);
void initializeBattleCruiser(Ship *newShip);
void initializePhoenix(Ship *newShip);
void initializeCarrier(Ship *newShip);

void vikingAttack(Ship *enemy);
void battleCruserAttack(Ship *enemy, int yamatoLoadingTurns);
void phoenixAttack(Ship *enemy);
void carrierAttack(Ship *enemy);
void protossRegen(Ship *self);

#endif /* SHIPS_H_ */