//
//  mouseEventObservable.hpp
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef mouseEventObservable_hpp
#define mouseEventObservable_hpp

#include <stdio.h>
#include <vector>

class MouseEventListener;
class SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;
union SDL_Event;

class MouseEventObservable
{
public:
  MouseEventObservable(const MouseEventObservable&) = delete;
  MouseEventObservable() = default;
  void addMouseListener(MouseEventListener* mouselistener);
  void removeMouseListener(MouseEventListener* mouselistener);
  void notifyMouseEvent(const SDL_Event& mouseEvent) const;
private:
  void processMouseButton_(const SDL_MouseButtonEvent& event) const;
  void processMouseMotion_(const SDL_MouseMotionEvent& event) const;

  std::vector<MouseEventListener*> mouseEventListeners_;
};

#endif /* mouseEventObservable_hpp */
