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
#ifndef NODE_TRANSITION_H
#define NODE_TRANSITION_H

#include "animate_impl.h"
#include "native_node.h"
#include "native_type.h"

#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ARKUI_TRANSITION_EFFECT_OPACITY = 0,
    ARKUI_TRANSITION_EFFECT_TRANSLATE,
    ARKUI_TRANSITION_EFFECT_SCALE,
    ARKUI_TRANSITION_EFFECT_ROTATE,
    ARKUI_TRANSITION_EFFECT_MOVE,
    ARKUI_TRANSITION_EFFECT_ASYMMETRIC,
} ArkUI_TransitionEffectType;

struct ArkUI_TransitionEffect {
    ArkUI_TransitionEffectType type;
    float opacity;
    ArkUI_TranslationOptions* translate;
    ArkUI_ScaleOptions* scale;
    ArkUI_RotationOptions* rotate;
    ArkUI_TransitionEdge move;
    ArkUI_TransitionEffect* appear;
    ArkUI_TransitionEffect* disappear;
    ArkUI_TransitionEffect* combine;
    ArkUI_AnimateOption* animation;
    ArkUITransitionEffectOption* toEffectOption;
};

#ifdef __cplusplus
};
#endif

namespace OHOS::Ace::TransitionModel {
ArkUITransitionEffectOption* ConvertToEffectOption(ArkUI_TransitionEffect* effectOption);
}; // namespace OHOS::Ace::TransitionModel

#endif