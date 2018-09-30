//
//  mainScene.hpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef mainScene_hpp
#define mainScene_hpp

#include <stdio.h>

#include "listeners/mouseEventListener.hpp"
class SDL_Window;

class PointInSquare : public MouseEventListener
{
public:
  PointInSquare(SDL_Window& window);
  virtual void onMouseClick(int x, int y) override;
  virtual void onMouseRelease(int x, int y) override;
  virtual void onMouseMove(int x, int y) override;
  virtual void onMouseMovePassive(int x, int y) override;

private:
  SDL_Window& window_;
};

#endif /* mainScene_hpp */
