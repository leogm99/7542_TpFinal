#include "DroppedWeapons.h"
#include "../updates/WeaponDropUpdate.h"

DroppedWeapons::DroppedWeapons(Broadcaster &updates)
: uniquifier(0),
  broadcaster(updates){
}

void DroppedWeapons::dropWeapon(uint8_t weaponCode, const b2Vec2 &position) {
    auto pos = position;
    droppedWeapons.emplace_back(weaponCode, uniquifier, pos);
    broadcaster.pushAll(std::shared_ptr<Update>(new WeaponDropUpdate(weaponCode, uniquifier, pos.x, pos.y)));
    ++uniquifier;
}

int8_t DroppedWeapons::pickUpAnyIfClose(const b2Vec2 &playerPosition) {
    int8_t code = -1;
    auto weapon = droppedWeapons.begin();
    while (weapon != droppedWeapons.end()){
        if ((std::get<2>(*weapon) - playerPosition).LengthSquared() < 1){
            broadcaster.pushAll(std::shared_ptr<Update>(new WeaponDropUpdate(std::get<0>(*weapon),
                                                                             std::get<1>(*weapon),
                                                                             std::get<2>(*weapon).x,
                                                                             std::get<2>(*weapon).y,
                                                                             false)));
            code = std::get<0>(*weapon);
            droppedWeapons.erase(weapon);
            break;
        } else {
            ++weapon;
        }
    }
    return code;
}

DroppedWeapons::~DroppedWeapons() {
}

DroppedWeapons::DroppedWeapons(DroppedWeapons &&other) noexcept
: uniquifier(other.uniquifier),
  broadcaster(other.broadcaster),
  droppedWeapons(std::move(other.droppedWeapons)){
}

DroppedWeapons &DroppedWeapons::operator=(DroppedWeapons &&other) noexcept {
    if (this == &other){
        return *this;
    }

    return *this;
}
