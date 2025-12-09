#pragma once

#include <smacc2/smacc.hpp>
#include <lifecyclenode_client/lifecyclenode_client.hpp>

using cl_lifecyclenode::ClLifecycleNode;

struct ClJoy2Twist : public ClLifecycleNode
{
  using ClLifecycleNode::ClLifecycleNode;
};

struct ClCanBridge : public ClLifecycleNode
{
  using ClLifecycleNode::ClLifecycleNode;
};

struct OrLifecycleNodes : smacc2::Orthogonal<OrLifecycleNodes>
{
    void onInitialize() override
    {
        this->createClient<ClJoy2Twist>("joy_vel_converter");
        this->createClient<ClCanBridge>("test_canbridge");
    }
};
