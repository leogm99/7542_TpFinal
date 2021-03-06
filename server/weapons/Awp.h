#ifndef AWP_H
#define AWP_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

class Awp: public Weapon {
    private:
        double accuracy;
        int firerate;
    public:
        Awp(int ammo, int range, int accuracy, int damage, int firerate, int bounty);
        ~Awp() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool canShoot(bool isAttacking) override;
        void resetCooldown() override;
        int hit() override;
};

#endif
