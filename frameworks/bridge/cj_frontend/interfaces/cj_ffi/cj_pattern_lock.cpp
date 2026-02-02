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

#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::Framework {
const std::vector<V2::PatternLockChallengeResult> CHALLENGE_RESULT = { V2::PatternLockChallengeResult::CORRECT,
    V2::PatternLockChallengeResult::WRONG };
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

void NativePatternLockController::SetChallengeResult(int64_t challengeResult)
{
    if (controller_) {
        controller_->SetChallengeResult(CHALLENGE_RESULT[challengeResult]);
    }
}

} // namespace OHOS::Ace::Framework

namespace OHOS::Ace {
// Should use CJUIModifier API later
NG::PatternLockModelNG* GetPatternLockModel()
{
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("PatternLock");
    if (module == nullptr) {
        LOGF("Can't find patternlock dynamic module");
        abort();
    }
    return reinterpret_cast<NG::PatternLockModelNG*>(module->GetModel());
}

}

extern "C" {
void FfiOHOSAceFrameworkPatternLockCreate(int64_t controllerId)
{
    auto patternLock = GetPatternLockModel()->Create();
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
    GetPatternLockModel()->SetPatternComplete(std::move(onPatternComplete));
}
void FfiOHOSAceFrameworkPatternLockonDotConnect(void (*callback)(int32_t idx))
{
    auto onDotConnect = [ffiCallback = CJLambda::Create(callback)](int64_t idx) { ffiCallback(idx); };
    GetPatternLockModel()->SetDotConnect(std::move(onDotConnect));
}
void FfiOHOSAceFrameworkPatternLockActivateCircleStyle(CJCircleStyleOptions options)
{
    GetPatternLockModel()->SetActiveCircleColor(Color(options.color));
    GetPatternLockModel()->SetActiveCircleRadius(
        Dimension(options.radius, static_cast<DimensionUnit>(options.radiusUnit)));
    GetPatternLockModel()->SetEnableWaveEffect(options.enableWaveEffect);
}
void FfiOHOSAceFrameworkPatternLockSelectedColor(uint32_t color)
{
    GetPatternLockModel()->SetSelectedColor(Color(color));
}
void FfiOHOSAceFrameworkPatternLockAutoReset(bool value)
{
    GetPatternLockModel()->SetAutoReset(value);
}
void FfiOHOSAceFrameworkPatternLockPathColor(uint32_t color)
{
    GetPatternLockModel()->SetPathColor(Color(color));
}
void FfiOHOSAceFrameworkPatternLockActiveColor(uint32_t color)
{
    GetPatternLockModel()->SetActiveColor(Color(color));
}
void FfiOHOSAceFrameworkPatternLockRegularColor(uint32_t color)
{
    GetPatternLockModel()->SetRegularColor(Color(color));
}
void FfiOHOSAceFrameworkPatternLockCircleRadius(double value, int32_t unit)
{
    GetPatternLockModel()->SetCircleRadius(Dimension(value, static_cast<DimensionUnit>(unit)));
}
void FfiOHOSAceFrameworkPatternLockSideLength(double value, int32_t unit)
{
    GetPatternLockModel()->SetSideLength(Dimension(value, static_cast<DimensionUnit>(unit)));
}
void FfiOHOSAceFrameworkPatternLockStrokeWidth(double value, int32_t unit)
{
    GetPatternLockModel()->SetStrokeWidth(Dimension(value, static_cast<DimensionUnit>(unit)));
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
void FfiOHOSAceFrameworkPatternLockControllerSetChallengeResult(int64_t selfID, int64_t challengeResult)
{
    auto self = FFIData::GetData<NativePatternLockController>(selfID);
    if (self) {
        self->SetChallengeResult(challengeResult);
    } else {
        LOGE("invalid pattern lock controller id");
    }
}
}
