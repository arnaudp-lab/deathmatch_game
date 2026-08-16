#pragma once

#include "layer.hpp"
#include "core/engine_parameters.hpp"

namespace vv
{

void run_application( const EngineParameters &params, Box<Layer> &&initial_layer);

} // namespace vv