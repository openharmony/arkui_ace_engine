/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_stepper_item_ffi.h"

#include "core/components_ng/pattern/stepper/stepper_item_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<std::string> ITEM_STATUS = { "normal", "disabled", "waiting", "skip" };
}

extern "C" {
void FfiOHOSAceFrameworkStepperItemCreate()
{
    StepperItemModel::GetInstance()->Create();
}

void FfiOHOSAceFrameworkStepperItemSetPrevLabel(const char* value)
{
    StepperItemModel::GetInstance()->SetPrevLabel(value);
}

void FfiOHOSAceFrameworkStepperItemSetNextLabel(const char* value)
{
    StepperItemModel::GetInstance()->SetNextLabel(value);
}

void FfiOHOSAceFrameworkStepperItemSetStatus(uint32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(ITEM_STATUS.size())) {
        return;
    }
    StepperItemModel::GetInstance()->SetStatus(ITEM_STATUS[value]);
}
}
