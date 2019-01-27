#pragma once
#include "sprites/coloringSprite.h"
#include "listeners/mouseEventListener.h"
#include "tools/GLSLShaderToolBase.h"
#include "sprites/mondelbrotSprite.h"


class SDL_Window;

class SpriteManager : public MouseEventListener
{
public:
  SpriteManager(SDL_Window& window);
  virtual void onMouseMovePassive(int x, int y) override;
private:
  SDL_Window& window_;
  ColoringSprite sprite_;
  MondelbrotSprite mondSprite_;
};

