//
//  contextBuilder.cpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include "contextProvider.hpp"
#include "contextBuilder.hpp"

ContextBuilder::ContextBuilder(ContextProvider& contextProvider):
  contextProvider_(contextProvider)
{
  mouseEventLogger_ = std::make_unique<MouseEventLogger>();
  contextProvider_.getMouseEventObservable_().addMouseListener(mouseEventLogger_.get());
}
