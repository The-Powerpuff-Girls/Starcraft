#ifndef SHIPS_H_
#define SHIPS_H_

#include "ProtossShip.h"
#include "TerranShip.h"
#include "BattleField.h"
#include "Vector.h" /* ? */


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


#endif /* SHIPS_H_ */