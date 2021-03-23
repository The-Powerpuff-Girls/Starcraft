#ifndef SHIPS_H_
#define SHIPS_H_

#include "Defines.h"
#include "Vector.h" /* ? */

/* Added 'type' and made 'damage', 'regen' -> const (they should never change) */

typedef struct {
  AirShipType type;
  int health;
  const int damage;
} TerranShip;

typedef struct{
  AirShipType type;
  int health;
  int shield;
  const int damage;
  const int regen;
} ProtossShip;


/* Possible functions */

void vikingTurn(ProtossShip *enemy);
  /* if enemy->type is phoenix, do double damage */

void battleCruserTurn(ProtossShip *enemy);
  /* static variable turns? if (turns % LOADING_TURNS == 0) ??, do 5 times more damage */

void phoenixTurn(TerranShip *enemy, ProtossShip *self);
  /* use 'self' to regain shield */

void carrierTurn(Vector *enemyFleet, ProtossShip *self);
  /* if full health, MAX_INTERCEPTORS attacks
Only carriers need the fleet Vector - to attack more than one target */


/* Ship struct Examples */

TerranShip viking = {
  .type = VIKING,
  .health = VIKING_HEALTH,
  .damage = VIKING_DAMAGE
};

ProtossShip carrier = {
  .type = CARRIER,
  .health = CARRIER_HEALTH,
  .shield = CARRIER_SHIELD,
  .damage = CARRIER_DAMAGE,
  .regen = CARRIER_SHIELD_REGENERATE_RATE
};

#endif /* SHIPS_H_ */