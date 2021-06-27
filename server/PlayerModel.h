#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "../libs/box2d/include/box2d/box2d.h"
#include "weapons/Armory.h"

class PlayerModel{
    b2Body* model;
    b2Vec2 netForce;
    int16_t angle;

    int hp;
    int money;

    Armory armory;

    public:
        PlayerModel();
        PlayerModel(b2Body* body);

        PlayerModel(const PlayerModel& other) = delete;
        PlayerModel& operator=(const PlayerModel& other) = delete;

        PlayerModel(PlayerModel&& other) noexcept;
        PlayerModel& operator=(PlayerModel&& other) noexcept;

        void startMove(int dir);
        void stopMove(int dir);

        void reposition(float x, float y);

        bool attack(PlayerModel& enemy);
        Weapon& hit();
        bool gotHit(Weapon& weapon);

        int equipWeapon(int weaponType);

        bool tickCooldown();
        void resetCooldown();

        const b2Vec2& getPosition();

        void setAngle(int16_t newAngle);
        int16_t getAngle() const;

        void step();

};

#endif
