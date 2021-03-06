#ifndef RIFLE_H
#define RIFLE_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

class Rifle: public Weapon {
    private:
        int bulletCount;
        double accuracy;
        int firerate;
    public:
        Rifle(int ammo, int range, int accuracy, int damage, int firerate, int bounty);
        ~Rifle() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool canShoot(bool isAttacking) override;
        void resetCooldown() override;
        int hit() override;


};

#endif
