#include "Bomb.h"

Bomb::Bomb(int range, int spread, int damage, int firerate):
 Weapon(BOMB, 0, range, damage),
 firerate(firerate),
 spread(spread){
}

Bomb::~Bomb(){
}

bool Bomb::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    double dist = static_cast<double>((player - enemy).Length());
    if (dist < range) {
        int res = static_cast<int>(atan2(enemy.y - player.y, enemy.x - player.x));
        int enemyAngle = res * 180/3.14 + 90;
        if (enemyAngle < 0){
            enemyAngle += 360;
        }
        int start = (angle) - spread;
        int end = (angle) + spread;
        if (start < end){
            return (start < enemyAngle && enemyAngle < end);
        } else {
            if (start < enemyAngle) return true;
            if (end > enemyAngle) return true;
        }
    }
    return false;
}


int Bomb::hit(){
    return damage;
}

bool Bomb::canShoot(){
    if (cooldown == 0) {
        cooldown = firerate;
        return true;
    } else {
        return false;
    }
}

void Bomb::resetCooldown(){
    cooldown = 0;
}

