#pragma once

#include <smacc2/smacc.hpp>
#include <boost/mpl/list.hpp>
#include <lifecyclenode_client/lifecyclenode_client.hpp>

#include "sm_sample/clients/cl_joy_monitor.hpp"
#include "sm_sample/orthogonals/or_lifecycle_nodes.hpp"
#include "sm_sample/states/st_wait_connections.hpp"
#include "sm_sample/states/st_can_error.hpp"

namespace sm_sample
{

struct SmSample;
namespace mpl = boost::mpl;

using cl_lifecyclenode::ClLifecycleNode;
using cl_lifecyclenode::EvTransitionOnDeactivateSuccess;

using EvCanDeactivated =
  EvTransitionOnDeactivateSuccess<ClLifecycleNode, OrLifecycleNodes>;

struct StActive
  : smacc2::SmaccState<StActive, SmSample>
{
  using Base = smacc2::SmaccState<StActive, SmSample>;
  using Base::SmaccState;

  using reactions = mpl::list<
    smacc2::Transition<EvControllerDisconnected, StWaitConnections>,
    smacc2::Transition<EvCanDeactivated, StCanError>>;

  void onEntry()
  {
    RCLCPP_INFO(this->getLogger(), "StActive: entry (activate lifecycle nodes)");

    ClLifecycleNode * lcJoy2Twist;
    ClLifecycleNode * lcCan;
    this->requiresClient(lcJoy2Twist);
    this->requiresClient(lcCan);

    lcJoy2Twist->configure();
    lcCan->configure();

    lcJoy2Twist->activate();
    lcCan->activate();
  }

  void onExit()
  {
    RCLCPP_INFO(this->getLogger(), "StActive: exit");
    ClLifecycleNode * lcJoy2Twist;
    ClLifecycleNode * lcCan;
    this->requiresClient(lcJoy2Twist);
    this->requiresClient(lcCan);

    lcJoy2Twist->deactivate();
  }
};

}  // namespace sm_sample
