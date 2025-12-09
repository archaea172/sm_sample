#pragma once

#include <smacc2/smacc.hpp>
#include <lifecyclenode_client/lifecyclenode_client.hpp>

using cl_lifecyclenode::ClLifecycleNode;

struct OrLifecycleNodes : smacc2::Orthogonal<OrLifecycleNodes>
{
    void onInitialize() override
    {
        this->createClient<ClLifecycleNode>("joy_vel_converter");
        this->createClient<ClLifecycleNode>("test_canbridge");
    }
};
