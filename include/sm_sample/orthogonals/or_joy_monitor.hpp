#pragma once

#include <smacc2/smacc.hpp>
#include "sm_sample/components/cp_joy_monitor.hpp"

namespace sm_omni_teleop
{

struct OrJoyMonitor : smacc2::Orthogonal<OrJoyMonitor>
{
  void onInitialize() override
  {
    this->createComponent<CpJoyMonitor>();
  }
};

} // namespace sm_sample
