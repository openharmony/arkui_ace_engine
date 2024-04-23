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
#ifndef ARKUI_NATIVE_ANIMATE_IMPL_H
#define ARKUI_NATIVE_ANIMATE_IMPL_H

#include <cstdint>

#include "native_animate.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ArkUI_AnimateOption {
    uint32_t duration;
    float tempo;
    ArkUI_AnimationCurve curve;
    int32_t delay;
    int32_t iterations;
    ArkUI_AnimationPlayMode playMode;
    ArkUI_ExpectedFrameRateRange* expectedFrameRateRange;
};

#ifdef __cplusplus
};
#endif

namespace OHOS::Ace::AnimateModel {

int32_t AnimateTo(ArkUI_ContextHandle context, ArkUI_AnimateOption* option, ArkUI_ContextCallback* update,
    ArkUI_AnimateCompleteCallback* complete);
}; // namespace OHOS::Ace::AnimateModel
#endif