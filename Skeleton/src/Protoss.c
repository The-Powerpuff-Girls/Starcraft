#include "Ships.h"

void initializePhoenix(Ship *newShip, int id) {
  newShip->type = PHOENIX;
  newShip->id = id;
  newShip->health = PHOENIX_HEALTH;
  newShip->shield = PHOENIX_SHIELD;
}

void initializeCarrier(Ship *newShip, int id) {
  newShip->type = CARRIER;
  newShip->id = id;
  newShip->health = CARRIER_HEALTH;
  newShip->shield = CARRIER_SHIELD;
}

void phoenixAttack(Ship *enemy) {
  enemy->health -= PHOENIX_DAMAGE;
}

void carrierAttack(Ship *enemy) {
  enemy->health -= CARRIER_DAMAGE;
}

void protossRegen(Ship *self) {
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