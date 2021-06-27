#ifndef WEAPON_H
#define WEAPON_H

#include <map>
#include "../sdlwrap/SdlTexture.h"
#include "../sdlwrap/Area.h"
#include "../Camera.h"
//#include "../anim/Character.h"
#define MAX_ROT_KNIFE 90.0f

// clase que representa a todas las armas
// pasamos un mapa de id de arma
// y sus texturas
// al cambiar de arma
// cambiamos la textura que utiliza

#define KNIFE 0
#define PISTOL 1
#define AK47 2
#define AWP 3
#define BOMB 4

class Character;

class Weapon {
private:
    std::map<uint8_t, SdlTexture>& weaponTextureMap;
    uint8_t currentWeapon;

    // usado para la rotacion del cuchillo
    // describe una parabola que va desde
    // un angulo 0, hasta un maximo
    // y de vuelta a 0
    int16_t parabolicMotion(int nFrame);
public:
    explicit Weapon(std::map<uint8_t, SdlTexture>& weaponTextureMap);

    Weapon(const Weapon& other) = delete;
    Weapon& operator=(const Weapon& other) = delete;

    Weapon(Weapon&& other) noexcept;
    Weapon& operator=(Weapon&& other) noexcept;

    void draw(float x, float y, float angle, Camera& cam);
    bool changeWeapon(uint8_t id);

    virtual ~Weapon();

    void animate(Character &character);
};


#endif
