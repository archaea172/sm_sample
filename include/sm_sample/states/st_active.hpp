#pragma once

#include <smacc2/smacc.hpp>
#include <lifecyclenode_client/lifecyclenode_client.hpp>
#include "sm_sample/components/cp_joy_monitor.hpp"
#include "sm_sample/orthogonals/or_lifecycle_nodes.hpp"

#include <boost/mpl/list.hpp>

namespace sm_sample
{
namespace mpl = boost::mpl;

using cl_lifecyclenode::ClLifecycleNode;
using cl_lifecyclenode::EvTransitionOnDeactivateSuccess;

struct StWaitConnections;
struct StCanError;

struct StTeleopActive
  : smacc2::SmaccState<StTeleopActive, SmSample>
{
  using SmaccState::SmaccState;

  using EvCanDeactivated =
    EvTransitionOnDeactivateSuccess<ClLifecycleNode, OrLifecycleNodes>;

  using reactions = mpl::list<
    smacc2::Transition<EvControllerDisconnected, StWaitConnections>,
    smacc2::Transition<EvCanDeactivated, StCanError>
  >;

  void onEntry()
  {
    RCLCPP_INFO(getLogger(), "StTeleopActive: ENTRY (activate lifecycle nodes)");

    ClLifecycleNode * lcJoy2Twist;
    ClLifecycleNode * lcCan;
    this->requiresClient(lcJoy2Twist);
    this->requiresClient(lcCan);

    lcJoy2Twist->activate();
    lcCan->activate();
  }

  void onExit()
  {
    RCLCPP_INFO(getLogger(), "StTeleopActive: EXIT (deactivate joy2twist)");
    ClLifecycleNode * lcJoy2Twist;
    this->requiresClient(lcJoy2Twist);
    lcJoy2Twist->deactivate();
  }
};

} // namespace sm_sample
