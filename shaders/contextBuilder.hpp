//
//  contextBuilder.hpp
//  shaders
//
//  Created by David Khudaverdyan on 20/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef contextBuilder_hpp
#define contextBuilder_hpp

#include <stdio.h>

#include "mouseEventLogger.hpp"

class ContextProvider;

class ContextBuilder
{
public:
  ContextBuilder(ContextProvider& contextProvider);
private:
  ContextProvider& contextProvider_;
  std::unique_ptr<MouseEventLogger> mouseEventLogger_;
  
};

#endif /* contextBuilder_hpp */
