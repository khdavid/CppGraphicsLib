//
//  contextProvider.cpp
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include <sdl.h>
 
#include "listeners/mouseEventLogger.h"
#include "wrappers/SDL_WindowWrapper.h"
#include "wrappers/SDL_GLContextWrapper.h"
#include "observables/mouseEventObservable.h"
#include "sprites/spriteManager.h"
#include "pointInSquare.h"

#include "contextProvider.h"

ContextProvider::ContextProvider()
{
  mouseEventObservable_ = std::make_unique<MouseEventObservable>();
  window_ = std::make_unique<SDL_WindowWrapper>();
  context_ = std::make_unique<SDL_GLContextWrapper>(window_->getNative());
  mouseEventLogger_ = std::make_unique<MouseEventLogger>();
  pointInSquare_ = std::make_unique<PointInSquare>(*window_->getNative());
  spriteManager_ = std::make_unique<SpriteManager>(*window_->getNative());
  mouseEventObservable_->addMouseListener(mouseEventLogger_.get());
  //mouseEventObservable_->addMouseListener(pointInSquare_.get());
  mouseEventObservable_->addMouseListener(spriteManager_.get());

}

void ContextProvider::notifyEvent(const SDL_Event& event) const
{
  mouseEventObservable_->notifyMouseEvent(event);
}

SDL_Window* ContextProvider::getWindow() const
{
  return window_->getNative();
}



ContextProvider::~ContextProvider() = default;

