#pragma once
#include "sprites/coloringSprite.h"
#include "listeners/inputEventListener.h"
#include "tools/GLSLShaderToolBase.h"
#include "sprites/mondelbrotSprite.h"


struct SDL_Window;

class SpriteManager : public InputEventListener
{
public:
  SpriteManager(SDL_Window& window);
  virtual void onMouseMovePassive(int x, int y) override;
  virtual void onKeyPress(SDL_Keycode keyCode) override;
  virtual void onWindowsResized(int, int) override;

private:
  SDL_Window& window_;
  ColoringSprite coloringSprite_;
  MondelbrotSprite mondSprite_;
  std::unique_ptr<SpriteBase> activeSprite_;
};

