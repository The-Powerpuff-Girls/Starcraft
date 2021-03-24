#include "Defines.h"

typedef struct{
  enum AirShipType type;
  int health;
  int shield;
  int damage;
  int regenRate;
} ProtossShip;

ProtossShip const phoenixPrototype = {
  .type = PHOENIX,
  .health = PHOENIX_HEALTH,
  .shield = PHOENIX_SHIELD,
  .damage = PHOENIX_DAMAGE,
  .regenRate = PHOENIX_SHIELD_REGENERATE_RATE
};

ProtossShip const carrierPrototype = {
  .type = CARRIER,
  .health = CARRIER_HEALTH,
  .shield = CARRIER_SHIELD,
  .damage = CARRIER_DAMAGE,
  .regenRate = CARRIER_SHIELD_REGENERATE_RATE
};