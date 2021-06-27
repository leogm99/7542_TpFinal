#ifndef TERRORIST_H
#define TERRORIST_H
#include "Renderizable.h"
#include "../weapons/Weapon.h"
#include "Animation.h"

class Character : public Renderizable {
private:
    bool player;
    bool bleeding;
    bool wasHit;
    Weapon weapon;
    // animacion de movimiento
    Animation movementAnimation;
    // animacion de sangrado
    Animation bloodAnimation;

    std::map<uint8_t, uint8_t> weaponCharacterFrameMap;
public:
	Character(SdlTexture& texture,
              float posX,
              float posY,
              bool player,
              std::map<uint8_t, SdlTexture>& weapons,
              SdlTexture& blood);

	Character(const Character& other) = delete;
    Character& operator=(const Character& other) = delete;

    Character(Character&& other) noexcept;
    Character& operator=(Character&& other) noexcept;

    void render(Camera &cam, uint8_t iteration) override;

	void changeWeapon(uint8_t weaponCode);

	void hit();
	void die();

	~Character() override;

    void attack();

    void pushPositionOffset(std::tuple<int, int, int> positionOffset);
};

#endif
