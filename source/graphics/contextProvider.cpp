//
//  contextProvider.cpp
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include <sdl.h>
 
#include "listeners/inputEventLogger.h"
#include "wrappers/SDL_WindowWrapper.h"
#include "wrappers/SDL_GLContextWrapper.h"
#include "observables/inputEventObservable.h"
#include "sprites/spriteManager.h"
#include "pointInSquare.h"

#include "contextProvider.h"

ContextProvider::ContextProvider()
{
  inputEventObservable_ = std::make_unique<InputEventObservable>();
  window_ = std::make_unique<SDL_WindowWrapper>();
  context_ = std::make_unique<SDL_GLContextWrapper>(window_->getNative());
  inputEventLogger_ = std::make_unique<InputEventLogger>();
  pointInSquare_ = std::make_unique<PointInSquare>(*window_->getNative());
  spriteManager_ = std::make_unique<SpriteManager>(*window_->getNative());
  inputEventObservable_->addInputListener(inputEventLogger_.get());
  inputEventObservable_->addInputListener(spriteManager_.get());

}

void ContextProvider::notifyEvent(const SDL_Event& event) const
{
  inputEventObservable_->notifyMouseEvent(event);
}

SDL_Window* ContextProvider::getWindow() const
{
  return window_->getNative();
}



ContextProvider::~ContextProvider() = default;

