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
#ifndef OHOS_ACE_FRAMEWORK_CJ_PATTERN_LOCK_H
#define OHOS_ACE_FRAMEWORK_CJ_PATTERN_LOCK_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/components_v2/pattern_lock/pattern_lock_component.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"
#include "ffi_remote_data.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT NativePatternLockController : public OHOS::FFI::FFIData {
    DECL_TYPE(NativePatternLockController, OHOS::FFI::FFIData)
public:
    NativePatternLockController();

    void Reset();
    void SetController(const RefPtr<V2::PatternLockController>& controller)
    {
        controller_ = controller;
    }
    void SetChallengeResult(int64_t challengeResult);

private:
    RefPtr<V2::PatternLockController> controller_;
};
} // namespace OHOS::Ace::Framework

extern "C" {
struct CJCircleStyleOptions {
    uint32_t color;
    double radius;
    int32_t radiusUnit;
    bool enableWaveEffect;
};

CJ_EXPORT void FfiOHOSAceFrameworkPatternLockCreate(int64_t controller);
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockOnPatternComplete(void (*callback)(VectorInt32Handle array));
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockSelectedColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockAutoReset(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockPathColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockActiveColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockRegularColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockCircleRadius(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockSideLength(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockStrokeWidth(double value, int32_t unit);
CJ_EXPORT int64_t FfiOHOSAceFrameworkPatternLockControllerCreate();
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockControllerReset(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockonDotConnect(void (*callback)(int32_t idx));
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockActivateCircleStyle(CJCircleStyleOptions options);
CJ_EXPORT void FfiOHOSAceFrameworkPatternLockControllerSetChallengeResult(int64_t selfID, int64_t challengeResult);
};

#endif // OHOS_ACE_FRAMEWORK_CJ_PATTERN_LOCK_H
