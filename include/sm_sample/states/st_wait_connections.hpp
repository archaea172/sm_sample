#pragma once

#include <smacc2/smacc.hpp>
#include <sr_all_events_go/sr_all_events_go.hpp>
#include <lifecyclenode_client/lifecyclenode_client.hpp>
#include "sm_sample/clients/cl_joy_monitor.hpp"

#include <boost/mpl/list.hpp>

namespace sm_sample
{

using smacc2::state_reactors::SrAllEventsGo;
using smacc2::state_reactors::EvAllGo;
using cl_lifecyclenode::ClLifecycleNode;
using cl_lifecyclenode::EvTransitionOnActivateSuccess;

struct StTeleopActive;

namespace mpl = boost::mpl;

struct StWaitConnections
  : smacc2::SmaccState<StWaitConnections, SmSample>
{
  using SmaccState::SmaccState;

  // CAN ノードが Active になったイベント型 alias
  using EvCanActivated =
    EvTransitionOnActivateSuccess<ClLifecycleNode, OrLifecycleNodes>;

  using reactions = mpl::list<
    smacc2::Transition<EvAllGo, StTeleopActive>
  >;

  void onEntry()
  {
    RCLCPP_INFO(getLogger(), "StWaitConnections: waiting for Joy & CAN");

    // Joy / CAN の両方が揃ったら EvAllGo を出す state reactor
    auto * sr = this->template createStateReactor<SrAllEventsGo>();

    sr->template addInputEvent<EvControllerConnected>();
    sr->template addInputEvent<EvCanActivated>();
  }
};

} // namespace sm_sample
