#include "Defines.h"

typedef struct{
  enum AirShipType type;
  int health;
  int shield;
  int damage;
  int regenRate;
} ProtossShip;

void initializePhoenix(ProtossShip *newShip);

void initializeCarrier(ProtossShip *newShip);



