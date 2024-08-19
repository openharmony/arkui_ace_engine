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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_stepper_ffi.h"

#include "cj_lambda.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "core/components_ng/pattern/stepper/stepper_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkStepperCreate(uint32_t value)
{
    StepperModel::GetInstance()->Create(value);
}

void FfiOHOSAceFrameworkStepperOnFinish(void (*callback)())
{
    StepperModel::GetInstance()->SetOnFinish(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkStepperOnSkip(void (*callback)())
{
    StepperModel::GetInstance()->SetOnSkip(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkStepperOnChange(void (*callback)(int32_t prevIndex, int32_t index))
{
    StepperModel::GetInstance()->SetOnChange(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkStepperOnNext(void (*callback)(int32_t index, int32_t pendingIndex))
{
    StepperModel::GetInstance()->SetOnNext(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkStepperOnPrevious(void (*callback)(int32_t index, int32_t pendingIndex))
{
    StepperModel::GetInstance()->SetOnPrevious(CJLambda::Create(callback));
}
}
