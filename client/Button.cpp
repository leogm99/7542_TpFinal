#include "Button.h"

Button::Button(int x, int y, int w, int h,
               SdlTexture &hudTex,
               SdlTexture &buttonTexture,
               SDL_Rect texSource,
               uint8_t buttonCode)
: box(x, y, w, h),
  hudTexture(hudTex),
  buttonTex(buttonTexture),
  textureSource((texSource)),
  code(buttonCode) {
}

void Button::show() {
    Area src(0, 0, box.width, box.height);
    Area dstGunTex(box.x + (box.width/2 - textureSource.w / 2),
                   box.y + (box.height/2 - textureSource.h / 2),
                   textureSource.w,
                   textureSource.h);
    hudTexture.render(src, box, SDL_FLIP_NONE);
    buttonTex.render(src, dstGunTex, SDL_FLIP_NONE);
}

Button::~Button() {

}

// se presiono si el mouse esta dentro de la caja
bool Button::checkPressed(int mouseX, int mouseY) {
    return (mouseX > box.x ) &&
           (mouseX < box.x + box.width) &&
           (mouseY > box.y ) &&
           (mouseY < box.y + box.height);
}

uint8_t Button::getCode() const {
    return code;
}

Button::Button(Button &&other)
: box(other.box),
  hudTexture(other.hudTexture),
  buttonTex(other.buttonTex),
  textureSource(other.textureSource),
  code(other.code) {
}

Button &Button::operator=(Button &&other) {
    if (this == &other) {
        return *this;
    }

    box = other.box;
    textureSource = other.textureSource;
    code = other.code;
    return *this;
}
