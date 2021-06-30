#include <stdexcept>
#include "Armory.h"


Armory::Armory(){
    arsenal.emplace(std::piecewise_construct,
                    std::forward_as_tuple(1),
                    std::forward_as_tuple(new Pistol()));

    arsenal.emplace(std::piecewise_construct,
                    std::forward_as_tuple(2),
                    std::forward_as_tuple(new Knife()));

    // precios originales del juego, ver https://www.cs2d.com/weapons.php
    // igualmente esto debe ser configurable
    prices.emplace(AK47, 2500);
    prices.emplace(M3, 1700);
    prices.emplace(AWP, 4750);

    currentWeapon = 2;
}


bool Armory::attack(const b2Vec2 &player, int16_t angle, const b2Vec2 &enemy){
    return arsenal[currentWeapon]->attack(player, angle, enemy);
}

std::shared_ptr<Weapon> Armory::hit(){
    return arsenal[currentWeapon];
}

bool Armory::tickCooldown(){
    return arsenal[currentWeapon]->tickCooldown();
}

void Armory::resetCooldown(){
    arsenal[currentWeapon]->resetCooldown();
}

int Armory::equipWeapon(int weaponType){
    // aca tiene que haber un chequeo para ver si es valida esa weapon
    // si no compro una primary, deberia devolver falso, o el codigo que sea
    if (arsenal.count(weaponType) != 0)
        currentWeapon = weaponType;
    else {
        return -1;
    }
    return arsenal.at(currentWeapon)->getWeaponCode();
}

bool Armory::tryBuying(uint8_t weaponCode, int& playerMoney) {
    int weaponPrice = prices.at(weaponCode);
    if (playerMoney >= weaponPrice){
        playerMoney -= weaponPrice;
        // aca hay que fijarse si ya tenia un arma primaria
        // en ese caso hay que dropear
        try {
            arsenal.emplace(0, Weapon::getArmoryWeapon(weaponCode));
        } catch(const std::invalid_argument& e){
            return false;
        }
        return true;
    }
    return false;
}
