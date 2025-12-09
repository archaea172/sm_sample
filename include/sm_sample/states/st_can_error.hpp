#pragma once

#include <smacc2/smacc.hpp>

namespace sm_sample
{

struct StWaitConnections;

struct EvReset : sc::event<EvReset> {};

struct StCanError
  : smacc2::SmaccState<StCanError, SmSample>
{
  using SmaccState::SmaccState;

  using reactions = mpl::list<
    smacc2::Transition<EvReset, StWaitConnections>
  >;

  void onEntry()
  {
    RCLCPP_ERROR(getLogger(), "StCanError: CAN error detected, teleop stopped");
  }
};

} // namespace sm_samples
