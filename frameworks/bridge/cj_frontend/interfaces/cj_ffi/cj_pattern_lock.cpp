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
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_pattern_lock.h"


#include "cj_lambda.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::Framework {
NativePatternLockController::NativePatternLockController() : FFIData()
{
    LOGI("Native NativePatternLockController constructed: %{public}" PRId64, GetID());
}

void NativePatternLockController::Reset()
{
    if (controller_) {
        controller_->Reset();
    }
}
} // namespace OHOS::Ace::Framework

extern "C" {
void FfiOHOSAceFrameworkPatternLockCreate(int64_t controllerId)
{
    auto patternLock = PatternLockModel::GetInstance()->Create();
    auto controller = FFIData::GetData<NativePatternLockController>(controllerId);
    if (controller) {
        controller->SetController(patternLock);
    } else {
        LOGE("patternLockControllerId is invalid");
    }
}
void FfiOHOSAceFrameworkPatternLockOnPatternComplete(void (*callback)(VectorInt32Handle array))
{
    auto onPatternComplete = [ffiCallback = CJLambda::Create(callback)](const BaseEventInfo* event) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<V2::PatternCompleteEvent>(event);
        if (!eventInfo) {
            return;
        }
        auto vectorC = eventInfo->GetInput();
        ffiCallback(&vectorC);
    };
    PatternLockModel::GetInstance()->SetPatternComplete(std::move(onPatternComplete));
}
void FfiOHOSAceFrameworkPatternLockSelectedColor(uint32_t color)
{
    PatternLockModel::GetInstance()->SetSelectedColor(Color(color));
}
void FfiOHOSAceFrameworkPatternLockAutoReset(bool value)
{
    PatternLockModel::GetInstance()->SetAutoReset(value);
}
void FfiOHOSAceFrameworkPatternLockPathColor(uint32_t color)
{
    PatternLockModel::GetInstance()->SetPathColor(Color(color));
}
void FfiOHOSAceFrameworkPatternLockActiveColor(uint32_t color)
{
    PatternLockModel::GetInstance()->SetActiveColor(Color(color));
}
void FfiOHOSAceFrameworkPatternLockRegularColor(uint32_t color)
{
    PatternLockModel::GetInstance()->SetRegularColor(Color(color));
}
void FfiOHOSAceFrameworkPatternLockCircleRadius(double value, int32_t unit)
{
    PatternLockModel::GetInstance()->SetCircleRadius(Dimension(value, static_cast<DimensionUnit>(unit)));
}
void FfiOHOSAceFrameworkPatternLockSideLength(double value, int32_t unit)
{
    PatternLockModel::GetInstance()->SetSideLength(Dimension(value, static_cast<DimensionUnit>(unit)));
}
void FfiOHOSAceFrameworkPatternLockStrokeWidth(double value, int32_t unit)
{
    PatternLockModel::GetInstance()->SetStrokeWidth(Dimension(value, static_cast<DimensionUnit>(unit)));
}
int64_t FfiOHOSAceFrameworkPatternLockControllerCreate()
{
    auto controller = FFIData::Create<NativePatternLockController>();
    return controller->GetID();
}
void FfiOHOSAceFrameworkPatternLockControllerReset(int64_t selfID)
{
    auto self = FFIData::GetData<NativePatternLockController>(selfID);
    if (self) {
        self->Reset();
    } else {
        LOGE("invalid pattern lock controller id");
    }
}
}