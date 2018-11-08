//
//  mouseListener.h
//  shaders
//
//  Created by David Khudaverdyan on 18/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef mouseListener_hpp
#define mouseListener_hpp

#include <stdio.h>

class MouseEventListener
{
public:
  virtual void onMouseClick(int x, int y);
  virtual void onMouseRelease(int x, int y);
  virtual void onMouseMove(int x, int y);
  virtual void onMouseMovePassive(int x, int y);
};

#endif /* mouseListener_hpp */
