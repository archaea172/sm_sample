#pragma once

#include "rclcpp/rclcpp.hpp"
#include "smacc2/smacc.hpp"

using sm_sample::OrLifecycleNodes;

namespace sm_sample
{
// SMACC2 clases
using smacc2::Transition;
using smacc2::EvStateRequestFinish;
using smacc2::default_transition_tags::SUCCESS;

using sm_sample::OrLifecycleNodes;

struct Active : smacc2::SmaccState<Active, SmSample>
{
    using SmaccState::SmaccState;

};

}