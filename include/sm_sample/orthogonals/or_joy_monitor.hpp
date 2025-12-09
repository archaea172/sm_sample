#pragma once

#include <smacc2/smacc.hpp>
#include "sm_sample/clients/cl_joy_monitor.hpp"

namespace sm_sample
{

struct OrJoyMonitor : smacc2::Orthogonal<OrJoyMonitor>
{
  void onInitialize() override
  {
    this->createClient<ClJoyMonitor>();
  }
};

} // namespace sm_sample
