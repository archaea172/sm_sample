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


namespace sm_sample
{
// SMACC2 clases
struct StActive;

//STATES

//--------------------------------------------------------------------
//STATE_MACHINE
struct SmSample
: public smacc2::SmaccStateMachineBase<SmSample, StActive>
{
  using SmaccStateMachineBase::SmaccStateMachineBase;

  void onInitialize() override
  {
    // START: Example code - change or delete as needed

    // Use Blackboard to store global state-machine data - example - feel free to delete it.
    setGlobalSMData(
      "output_message_note", std::string("{I am very cool smacc2 SM called 'sm_sample'}"));
    // END: Example code - change or delete as needed
  }
};

}  // namespace sm_sample

//STATES
