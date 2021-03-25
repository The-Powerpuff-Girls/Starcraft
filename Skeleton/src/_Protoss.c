#include "../include/ProtossShip.h"
#include "../include/TerranShip.h"

void initializePhoenix(ProtossShip *newShip) {
  newShip->type = PHOENIX;
  newShip->health = PHOENIX_HEALTH;
  newShip->shield = PHOENIX_SHIELD;
  newShip->damage = PHOENIX_DAMAGE;
}

void initializeCarrier(ProtossShip *newShip) {
  newShip->type = CARRIER;
  newShip->health = CARRIER_HEALTH;
  newShip->shield = CARRIER_SHIELD;
  newShip->damage = CARRIER_DAMAGE;
}

void phoenixAttack(TerranShip *enemy) {
  enemy->health -= PHOENIX_DAMAGE;
}

void carrierAttack(TerranShip *enemy) {
  enemy->health -= CARRIER_DAMAGE;
}

void protossRegen(ProtossShip *self) {
  if (self->type == PHOENIX) {
    self->shield += PHOENIX_SHIELD_REGENERATE_RATE;
    if (self->shield > PHOENIX_SHIELD) {
      self->shield = PHOENIX_SHIELD;
    }
  }
  
  if (self->type == CARRIER) {
    self->shield += CARRIER_SHIELD_REGENERATE_RATE;
    if (self->shield > CARRIER_SHIELD) {
      self->shield = CARRIER_SHIELD;
    }
  }
}