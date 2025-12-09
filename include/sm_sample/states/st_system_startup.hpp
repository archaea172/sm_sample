#pragma once

#include <smacc2/smacc.hpp>
#include <boost/mpl/list.hpp>
#include <lifecyclenode_client/lifecyclenode_client.hpp>

#include "sm_sample/orthogonals/or_lifecycle_nodes.hpp"

namespace sm_sample
{

// 親ステートマシン & 次の状態を前方宣言
struct SmSample;
struct StWaitConnections;

// Boost.MPL のエイリアス
namespace mpl = boost::mpl;

// 「スタートアップが終わった」ことを表す自前イベント
struct EvStartupDone : sc::event<EvStartupDone> {};

//-----------------------------------------------
//  StSystemStartup
//-----------------------------------------------
struct StSystemStartup
  : smacc2::SmaccState<StSystemStartup, SmSample>
{
  using Base = smacc2::SmaccState<StSystemStartup, SmSample>;
  using Base::SmaccState;

  // このステートが受け付けるイベントと遷移
  using reactions = mpl::list<
    smacc2::Transition<EvStartupDone, StWaitConnections>
  >;

  void onEntry()
  {
    RCLCPP_INFO(this->getLogger(), "StSystemStartup: entry");
    // すぐに次のステートへ進みたいので、自分でイベントをポスト
    this->postEvent<EvStartupDone>();
  }
};

}  // namespace sm_sample
