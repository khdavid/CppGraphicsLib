//
//  mouseEventLogger.hpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef mouseEventLogger_hpp
#define mouseEventLogger_hpp

#include <stdio.h>

#include "mouseEventListener.hpp"

class MouseEventLogger: public MouseEventListener
{
public:
  virtual void onMouseRelease() override;
  virtual void onMouseMove(int x, int y) override;
  virtual void onMouseClick() override;
  virtual void onMouseMovePassive(int x, int y) override;

};

#endif /* mouseEventLogger_hpp */