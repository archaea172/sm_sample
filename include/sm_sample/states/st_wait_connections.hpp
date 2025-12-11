#pragma once

#include <smacc2/smacc.hpp>
#include <boost/mpl/list.hpp>
#include <lifecyclenode_client/lifecyclenode_client.hpp>

#include "sm_sample/clients/cl_joy_monitor.hpp"
#include "sm_sample/orthogonals/or_lifecycle_nodes.hpp"

namespace sm_sample
{

struct SmSample;  // 親ステートマシン
struct StActive;

namespace mpl = boost::mpl;

using cl_lifecyclenode::ClLifecycleNode;

//-----------------------------------------------
//  StWaitConnections
//-----------------------------------------------
struct StWaitConnections
  : smacc2::SmaccState<StWaitConnections, SmSample>
{
  using Base = smacc2::SmaccState<StWaitConnections, SmSample>;
  using Base::SmaccState;

  // まだ遷移は何も定義しない（あとで足す）
  using reactions = mpl::list<
    smacc2::Transition<EvControllerConnected, StActive>
  >;

  void onEntry()
  {
    RCLCPP_INFO(this->getLogger(), "StWaitConnections: entry");
  }
};

}  // namespace sm_sample
