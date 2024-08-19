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

#include "node_transition.h"


#include "base/utils/utils.h"

namespace OHOS::Ace::TransitionModel {

ArkUITransitionEffectOption* CreateEffectOption()
{
    ArkUITransitionEffectOption* effectOption = new ArkUITransitionEffectOption;
    effectOption->appear = nullptr;
    effectOption->disappear = nullptr;
    effectOption->combine = nullptr;
    return effectOption;
}

ArkUITransitionEffectOption* ConvertToEffectOption(ArkUI_TransitionEffect* effectOption)
{
    CHECK_NULL_RETURN(effectOption, nullptr);
    auto* toEffectOption = CreateEffectOption();
    toEffectOption->type = effectOption->type;
    switch (effectOption->type) {
        case ARKUI_TRANSITION_EFFECT_OPACITY: {
            toEffectOption->opacity = effectOption->opacity;
            break;
        }
        case ARKUI_TRANSITION_EFFECT_TRANSLATE: {
            if (!effectOption->translate) {
                delete toEffectOption;
                toEffectOption = nullptr;
                return nullptr;
            }
            toEffectOption->translate.x = effectOption->translate->x;
            toEffectOption->translate.y = effectOption->translate->y;
            toEffectOption->translate.z = effectOption->translate->z;
            break;
        }
        case ARKUI_TRANSITION_EFFECT_SCALE: {
            if (!effectOption->scale) {
                delete toEffectOption;
                toEffectOption = nullptr;
                return nullptr;
            }
            toEffectOption->scale.x = effectOption->scale->x;
            toEffectOption->scale.y = effectOption->scale->y;
            toEffectOption->scale.z = effectOption->scale->z;
            toEffectOption->scale.centerX = effectOption->scale->centerX;
            toEffectOption->scale.centerY = effectOption->scale->centerY;
            break;
        }
        case ARKUI_TRANSITION_EFFECT_ROTATE: {
            if (!effectOption->rotate) {
                delete toEffectOption;
                toEffectOption = nullptr;
                return nullptr;
            }
            toEffectOption->rotate.x = effectOption->rotate->x;
            toEffectOption->rotate.y = effectOption->rotate->y;
            toEffectOption->rotate.z = effectOption->rotate->z;
            toEffectOption->rotate.angle = effectOption->rotate->angle;
            toEffectOption->rotate.centerX = effectOption->rotate->centerX;
            toEffectOption->rotate.centerY = effectOption->rotate->centerY;
            toEffectOption->rotate.centerZ = effectOption->rotate->centerZ;
            toEffectOption->rotate.perspective = effectOption->rotate->perspective;
            break;
        }
        case ARKUI_TRANSITION_EFFECT_MOVE: {
            toEffectOption->move = effectOption->move;
            break;
        }
        case ARKUI_TRANSITION_EFFECT_ASYMMETRIC: {
            if (effectOption->appear) {
                auto* appear = ConvertToEffectOption(effectOption->appear);
                toEffectOption->appear = appear;
            }
            if (effectOption->disappear) {
                auto* disappear = ConvertToEffectOption(effectOption->disappear);
                toEffectOption->disappear = disappear;
            }
            break;
        }
    }

    if (effectOption->animation) {
        toEffectOption->hasAnimation = true;
        toEffectOption->animation.duration = effectOption->animation->duration;
        toEffectOption->animation.tempo = effectOption->animation->tempo;
        toEffectOption->animation.curve = effectOption->animation->curve;
        if (effectOption->animation->iCurve) {
            toEffectOption->animation.iCurve = effectOption->animation->iCurve->curve;
            toEffectOption->animation.curveType = effectOption->animation->iCurve->type;
        } else {
            toEffectOption->animation.iCurve = nullptr;
        }
        toEffectOption->animation.delay = effectOption->animation->delay;
        toEffectOption->animation.iterations = effectOption->animation->iterations;
        toEffectOption->animation.playMode = effectOption->animation->playMode;
        if (effectOption->animation->expectedFrameRateRange) {
            toEffectOption->animation.expectedFrameRateRange =
                reinterpret_cast<ArkUIExpectedFrameRateRange*>(effectOption->animation->expectedFrameRateRange);
        } else {
            toEffectOption->animation.expectedFrameRateRange = nullptr;
        }
    } else {
        toEffectOption->hasAnimation = false;
    }

    if (effectOption->combine) {
        toEffectOption->combine = ConvertToEffectOption(effectOption->combine);
    }
    effectOption->toEffectOption = toEffectOption;
    return toEffectOption;
}
} // namespace OHOS::Ace::TransitionModel
