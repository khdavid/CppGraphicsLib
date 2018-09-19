//
//  mainLoop.hpp
//  shaders
//
//  Created by David Khudaverdyan on 17/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef mainLoop_hpp
#define mainLoop_hpp

#include <stdio.h>
#include <vector>

class
  MouseListener;

class MainLoop
{
public:
  bool run();
  void addMouseListener(MouseListener* mouselistener);
  void removeMouseListener(MouseListener* mouselistener);

private:
  void processMouseButton_(const SDL_MouseButtonEvent& event);
  void processMouseMotion_(const SDL_MouseMotionEvent& event);

  std::vector<MouseListener*> mouseListeners_;
};



#endif /* mainLoop_hpp */
