//
//  contextProvider.h
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef contextProvider_hpp
#define contextProvider_hpp

#include <stdio.h>
#include <memory>
#include <sdl.h>

class MouseEventLogger;
class SDL_WindowWrapper;
class SDL_GLContextWrapper;
class MouseEventObservable;
class PointInSquare;


class ContextProvider
{
public:
  ContextProvider();
  ~ContextProvider();
  ContextProvider(const ContextProvider&) = delete;
  ContextProvider& operator=(const ContextProvider&) = delete;
  void notifyEvent(const SDL_Event& event) const;
  SDL_Window* getWindow() const;

private:
  std::unique_ptr<MouseEventObservable> mouseEventObservable_;
  std::unique_ptr<MouseEventLogger> mouseEventLogger_;
  std::unique_ptr<SDL_WindowWrapper> window_;
  std::unique_ptr<SDL_GLContextWrapper> context_;
  std::unique_ptr<PointInSquare> mainScene_;
};
  

#endif /* contextProvider_hpp */
