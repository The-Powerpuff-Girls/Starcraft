#include "Defines.h"

typedef struct{
  enum AirShipType type;
  int health;
  int shield;
  int damage;
} ProtossShip;

void initializePhoenix(ProtossShip *newShip);
void initializeCarrier(ProtossShip *newShip);

void phoenixAttack(TerranShip *enemy);
void carrierAttack(TerranShip *enemy);
void protossRegen(ProtossShip *self);