#pragma once

#include <smacc2/smacc.hpp>
#include <boost/mpl/list.hpp>

namespace sm_sample
{

struct SmSample;
namespace mpl = boost::mpl;

//-----------------------------------------------
//  StTeleopActive （とりあえずログだけ）
//-----------------------------------------------
struct StTeleopActive
  : smacc2::SmaccState<StTeleopActive, SmSample>
{
  using Base = smacc2::SmaccState<StTeleopActive, SmSample>;
  using Base::SmaccState;

  using reactions = mpl::list<>;  // まだ遷移なし

  void onEntry()
  {
    RCLCPP_INFO(this->getLogger(), "StTeleopActive: entry (Joy connected)");
  }

  void onExit()
  {
    RCLCPP_INFO(this->getLogger(), "StTeleopActive: exit");
  }
};

}  // namespace sm_sample
