#pragma once
#include <memory>
#include "model/model.h"

namespace ModelInitializator
{
std::unique_ptr<Model> ConstructModel();
};

