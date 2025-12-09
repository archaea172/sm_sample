#pragma once

#include <smacc2/smacc.hpp>

#include <boost/mpl/list.hpp>

namespace sm_sample
{

struct SmSample;

namespace mpl = boost::mpl;

struct StCanError
  : smacc2::SmaccState<StCanError, SmSample>
{
  using Base = smacc2::SmaccState<StCanError, SmSample>;
  using Base::SmaccState;

  using reactions = mpl::list<>;

  void onEntry()
  {
    RCLCPP_ERROR(getLogger(), "StCanError: CAN error detected, teleop stopped");
  }
};

} // namespace sm_samples
