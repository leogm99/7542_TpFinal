#include <tuple>
#include <iostream>
#include <algorithm>
#include "Animation.h"

Animation::Animation(SdlTexture &texture,
                     int numFrames,
                     int framesW,
                     int framesH,
                     int sizeW,
                     int sizeH,
                     bool center)
: texture(texture),
  currentFrame(0),
  numFrames(numFrames),
  sizeW(sizeW),
  sizeH(sizeH),
  numFramesH(framesH),
  numFramesW(framesW),
  frameOffset(0),
  center(center),
  ticksToChangeFrame(0){
    for (int i = 0; i < framesH; ++i){
        for (int j = 0; j < framesW; ++j){
            frames.push_back(SDL_Rect{j * sizeW, i * sizeH, sizeW, sizeH});
        }
    }
}

Animation::~Animation(){
}

Animation::Animation(SdlTexture &texture, int numFrames, int framesW, int framesH, int size, bool center)
: texture(texture),
  currentFrame(0),
  numFrames(numFrames),
  sizeW(size),
  sizeH(size),
  numFramesH(framesH),
  numFramesW(framesW),
  frameOffset(0),
  center(center),
  ticksToChangeFrame(0){
    for (int i = 0; i < framesH; ++i) {
        for (int j = 0; j < framesW; ++j) {
            frames.push_back(SDL_Rect{j * sizeW, i * sizeH, sizeW, sizeH});
        }
    }
}

void Animation::render(Camera &cam, float posX, float posY, float angle, size_t iteration) {
    auto frame = frames.at(iteration % numFrames);
    Area src(frame.x, frame.y, frame.w, frame.h);
    if (center){
        cam.renderAtCenter(texture, src, angle, sizeW, sizeH);
    } else if (cam.isVisible(posX, posY)){
        cam.renderInSight(texture, src, posX, posY, angle);
    }
    currentFrame = (iteration % numFrames);
    advanceFrame();
}

// seteo el frame desde el cual quiero renderizar
void Animation::renderFromFrame(int nFrame) {
    currentFrame = nFrame;
    frameOffset = nFrame;
}

void Animation::offsetRenderState(std::tuple<float, float, int16_t> offset) {
    modifiedState.push(std::move(offset));
}

// unique frame animation
// used for characters
std::tuple<float, float, int16_t> Animation::renderOne(Camera &camera,
                                                       float posX,
                                                       float posY,
                                                       int16_t angle) {
    float newPosX = posX;
    float newPosY = posY;
    int16_t newAngle = angle;
    auto frame = frames.at(currentFrame);
    if (!modifiedState.empty()){
        auto state = modifiedState.front();
        newPosX += std::get<0>(state);
        newPosY += std::get<1>(state);
        newAngle += std::get<2>(state);
        if (newAngle >= 360){
            newAngle -= 360;
        }
        modifiedState.pop();
    }

    Area src(frame.x, frame.y, frame.w, frame.h);
    if (center){
        camera.renderAtCenter(texture, src, newAngle, sizeW, sizeH);
    } else {
        if (camera.isVisible(newPosX, newPosY)){
            camera.renderInSight(texture, src, newPosX, newPosY, newAngle);
        }
    }

    return std::make_tuple(newPosX - posX, newPosY - posY, newAngle - angle);
}

bool Animation::renderOld(Camera &camera, int maxNumFrames) {
    auto it = oldRenders.begin();
    while (it != oldRenders.end()){
        Area src(std::get<3>(*it).x, std::get<3>(*it).y, std::get<3>(*it).w, std::get<3>(*it).h);
        camera.renderWithAlpha(texture,
                               src,
                               std::get<0>(*it),
                               std::get<1>(*it),
                           (maxNumFrames - std::get<2>(*it)));
        if (!(maxNumFrames - std::get<2>(*it))){
            it = oldRenders.erase(it);
        } else {
            ++std::get<2>(*it);
            ++it;
        }
    }
    return !oldRenders.empty();
}

void Animation::renderOneAndKeep(Camera &camera, float posX, float posY) {
    auto& rect = frames.at(currentFrame);
    Area src(rect.x, rect.y, rect.w, rect.h);
    camera.renderInSight(texture, src, posX, posY, 0);
    oldRenders.emplace_back(posX, posY, 0, rect);
}

void Animation::advanceFrame() {
    ++currentFrame;
    if (currentFrame == numFrames){
        currentFrame = frameOffset;
    }
}

void Animation::setCurrentFrame(uint8_t newFrame) {
    currentFrame = newFrame;
}

void Animation::renderFor(Camera &cam, float posX, float posY, int16_t angle, size_t iteration) {
    currentFrame = ((iteration - startingFrom) / ticksToChangeFrame) % numFrames;
    auto frame = frames.at(currentFrame);
    Area src(frame.x, frame.y, frame.w, frame.h);
    if (center){
        cam.renderAtCenter(texture, src, angle, sizeW, sizeH);
    } else if (cam.isVisible(posX, posY)){
        cam.renderInSight(texture, src, posX, posY, angle);
    } else {
        std::cout << "No visible\n";
    }
}

void Animation::setTicksToChange(size_t ticks) {
    ticksToChangeFrame = ticks;
}

void Animation::setStartingIteration(size_t iter) {
    startingFrom = iter;
}
