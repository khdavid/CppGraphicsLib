//
//  contextProvider.cpp
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#include "contextProvider.hpp"

MouseEventObservable& ContextProvider::getMouseEventObservable_()
{
  return mouseEventObservable_;
}

const MouseEventObservable& ContextProvider::getMouseEventObservable_() const
{
  return mouseEventObservable_;
}

