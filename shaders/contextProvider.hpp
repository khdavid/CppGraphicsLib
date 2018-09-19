//
//  contextProvider.hpp
//  shaders
//
//  Created by David Khudaverdyan on 19/09/2018.
//  Copyright © 2018 David Khudaverdyan. All rights reserved.
//

#ifndef contextProvider_hpp
#define contextProvider_hpp

#include <stdio.h>

#include "observables/mouseEventObservable.hpp"

class ContextProvider
{
public:
  ContextProvider(const ContextProvider&) = delete;
  ContextProvider() = default;
  MouseEventObservable& getMouseEventObservable_();
  const MouseEventObservable& getMouseEventObservable_() const;

private:
  MouseEventObservable mouseEventObservable_;
};
  

#endif /* contextProvider_hpp */
