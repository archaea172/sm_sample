// Copyright 2021 MyName/MyCompany Inc.
// Copyright 2021 RobosoftAI Inc. (template)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <memory>
#include <string>

#include "smacc2/smacc.hpp"

// ORTHOGONALS
#include "sm_sample/orthogonals/or_lifecycle_nodes.hpp"
#include "sm_sample/orthogonals/or_joy_monitor.hpp"

namespace sm_sample
{
// SMACC2 clases

//STATES
struct StActive;

//--------------------------------------------------------------------
//STATE_MACHINE
struct SmSample
: public smacc2::SmaccStateMachineBase<SmSample, StActive>
{
  	using SmaccStateMachineBase::SmaccStateMachineBase;

    void onInitialize() override
    {
		this->createOrthogonal<OrLifecycleNodes>();
		this->createOrthogonal<OrJoyMonitor>();
		
		setGlobalSMData(
			"output_message_note", std::string("{I am very cool smacc2 SM called 'sm_sample'}"));
    }
};

}  // namespace sm_sample

#include "sm_sample/states/st_active.hpp"