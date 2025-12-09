#pragma once

#include <smacc2/smacc.hpp>

namespace sm_sample
{
struct StWaitConnections;

struct StSystemStartup
  : smacc2::SmaccState<StSystemStartup, SmOmniTeleop>
{
  using SmaccState::SmaccState;

  using reactions = mpl::list<
    smacc2::Transition<smacc2::EvStateFinish<StSystemStartup>, StWaitConnections>
  >;

  void onEntry()
  {
    RCLCPP_INFO(getLogger(), "StSystemStartup: entry");
    // 必要ならここで lifecycle configure などを行う
    this->postEvent<smacc2::EvStateFinish<StSystemStartup>>();
  }
};

} // namespace sm_sample
