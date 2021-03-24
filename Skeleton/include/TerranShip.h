#include "Defines.h"

typedef struct {
  enum AirShipType type;
  int health;
  int damage;
} TerranShip;

TerranShip vikingPrototype = {
  .type = VIKING,
  .health = VIKING_HEALTH,
  .damage = VIKING_DAMAGE
};

TerranShip battleCruserPrototype = {
  .type = BATTLE_CRUSER,
  .health = BATTLE_CRUSER_HEALTH,
  .damage = BATTLE_CRUSER_DAMAGE
};
