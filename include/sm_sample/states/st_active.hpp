#pragma once

#include <smacc2/smacc.hpp>
#include <boost/mpl/list.hpp>
#include <lifecyclenode_client/lifecyclenode_client.hpp>

#include "sm_sample/clients/cl_joy_monitor.hpp"
#include "sm_sample/orthogonals/or_lifecycle_nodes.hpp"

namespace sm_sample
{

struct SmSample;
struct StWaitConnections;
struct StCanError;
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
    ClJoy2Twist * lcJoy2Twist;
    ClCanBridge * lcCan;
    this->requiresClient(lcJoy2Twist);
    this->requiresClient(lcCan);

    lcJoy2Twist->configure();
    // lcCan->configure();

    lcJoy2Twist->activate();
    // lcCan->activate();
    RCLCPP_INFO(this->getLogger(), "StActive: entry (activate lifecycle nodes)");
  }

  void onExit()
  {
    RCLCPP_INFO(this->getLogger(), "StActive: exit");
    ClJoy2Twist * lcJoy2Twist;
    ClCanBridge * lcCan;
    this->requiresClient(lcJoy2Twist);
    this->requiresClient(lcCan);

    lcJoy2Twist->deactivate();
    lcJoy2Twist->cleanup();
  }
};

}  // namespace sm_sample
