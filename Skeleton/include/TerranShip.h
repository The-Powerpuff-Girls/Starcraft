#include "Defines.h"

typedef struct {
  enum AirShipType type;
  int health;
  int damage;
} TerranShip;

void initializeViking(TerranShip *newShip);

void initializeBattleCruiser(TerranShip *newShip);
