#ifndef CAMERA_H
#define CAMERA_H

#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"
#include "Renderizable.h"

// 32 pixeles (tamaño de tile) <-> 1 metro logico (server)
#define M_TO_P 32

class Camera{
private:
    SdlWindow& window;
    // center width and height
    // depends on screen resolution
    SDL_Point centerPix;

    float logicalCenterX;
    float logicalCenterY;

    int width;
    int height;


    // checks if the given logical coordinate pair
    // is in sight of the player
    // should render only if both shield true
    bool isVisibleInX(float x);
    bool isVisibleInY(float y);
public:
    explicit Camera(SdlWindow& window);

    // recibiria primero al player
    // luego al resto de las entidades
    void render(Renderizable &renderizable, size_t iteration);

    void setLogicalCenter(float x, float y);


    bool isVisible(float x, float y);

    // logical coordinates
    // only renders if visible to player
    void renderInSight(SdlTexture& texture, Area& src,
                       float posX,
                       float posY,
                       float angle);

    void renderWithAlpha(SdlTexture& texture,
                         Area& source,
                         float x,
                         float y,
                         uint8_t alpha);

    ~Camera();

    int16_t angleFromMouse();

    void renderWeapon(float playerX, float playerY, int16_t playerAngle, int sizeX, int sizeY, SdlTexture &texture);

    float calculateDistanceToCenter(float posX, float posY) const;
};

#endif
