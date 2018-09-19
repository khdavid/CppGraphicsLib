//
//  mouseEventObservable.hpp
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef mouseEventObservable_hpp
#define mouseEventObservable_hpp

#include <sdl2/sdl.h>

#include <stdio.h>
#include <vector>
class MouseListener;


class MouseEventObservable
{
public:
  void addMouseListener(MouseListener* mouselistener);
  void removeMouseListener(MouseListener* mouselistener);
  void notifyMouseEvent(const SDL_Event& mouseEvent);
private:
  void processMouseButton_(const SDL_MouseButtonEvent& event);
  void processMouseMotion_(const SDL_MouseMotionEvent& event);

  std::vector<MouseListener*> mouseListeners_;
};

#endif /* mouseEventObservable_hpp */
