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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TRANSITIONEFFECT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TRANSITIONEFFECT_FFI_H

#include <cstdint>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "cj_transitioneffect.h"
#include "cj_animate_param_ffi.h"

namespace OHOS::Ace::Framework {
extern "C" {
    CJ_EXPORT int64_t FfiOHOSAceFrameworkTransitionEffectOpacity(double number);

    CJ_EXPORT int64_t FfiOHOSAceFrameworkTransitionEffectTranslate(CTranslateOptions translate);

    CJ_EXPORT int64_t FfiOHOSAceFrameworkTransitionEffectScale(CScaleOptions options);

    CJ_EXPORT int64_t FfiOHOSAceFrameworkTransitionEffectRotate(CRotateOptions options);

    CJ_EXPORT int64_t FfiOHOSAceFrameworkTransitionEffectMove(int32_t edge);

    CJ_EXPORT int64_t FfiOHOSAceFrameworkTransitionEffectAsymmetric(int64_t appearId, int64_t disappearId);

    CJ_EXPORT void FfiOHOSAceFrameworkTransitionEffectCombine(int64_t id, int64_t effectId);

    CJ_EXPORT void FfiOHOSAceFrameworkTransitionEffectAnimation(int64_t id, NativeAnimateParam param);

    CJ_EXPORT int64_t FfiOHOSAceFrameworkTransitionEffectIdentity();

    CJ_EXPORT int64_t FfiOHOSAceFrameworkTransitionEffectSlideSwitch();
};
}

#endif // OHOS_ACE_FRAMEWORK_CJ_TRANSITIONEFFECT_FFI_H