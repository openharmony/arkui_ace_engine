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


#include "node/node_transition.h"

#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_TransitionEffect* OH_ArkUI_CreateOpacityTransitionEffect(float opacity)
{
    ArkUI_TransitionEffect* option = new ArkUI_TransitionEffect { ARKUI_TRANSITION_EFFECT_OPACITY };
    option->translate = nullptr;
    option->scale = nullptr;
    option->rotate = nullptr;
    option->appear = nullptr;
    option->disappear = nullptr;
    option->combine = nullptr;
    option->animation = nullptr;
    option->opacity = std::clamp(opacity, 0.0f, 1.0f);
    return option;
}

ArkUI_TransitionEffect* OH_ArkUI_CreateTranslationTransitionEffect(ArkUI_TranslationOptions* translate)
{
    CHECK_NULL_RETURN(translate, nullptr);
    ArkUI_TransitionEffect* option = new ArkUI_TransitionEffect { ARKUI_TRANSITION_EFFECT_TRANSLATE };
    option->scale = nullptr;
    option->rotate = nullptr;
    option->appear = nullptr;
    option->disappear = nullptr;
    option->combine = nullptr;
    option->animation = nullptr;
    option->translate = translate;
    return option;
}

ArkUI_TransitionEffect* OH_ArkUI_CreateScaleTransitionEffect(ArkUI_ScaleOptions* scale)
{
    CHECK_NULL_RETURN(scale, nullptr);
    ArkUI_TransitionEffect* option = new ArkUI_TransitionEffect { ARKUI_TRANSITION_EFFECT_SCALE };
    option->translate = nullptr;
    option->rotate = nullptr;
    option->appear = nullptr;
    option->disappear = nullptr;
    option->combine = nullptr;
    option->animation = nullptr;
    option->scale = scale;
    return option;
}

ArkUI_TransitionEffect* OH_ArkUI_CreateRotationTransitionEffect(ArkUI_RotationOptions* rotate)
{
    CHECK_NULL_RETURN(rotate, nullptr);
    ArkUI_TransitionEffect* option = new ArkUI_TransitionEffect { ARKUI_TRANSITION_EFFECT_ROTATE };
    option->translate = nullptr;
    option->scale = nullptr;
    option->appear = nullptr;
    option->disappear = nullptr;
    option->combine = nullptr;
    option->animation = nullptr;
    option->rotate = rotate;
    return option;
}

ArkUI_TransitionEffect* OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge move)
{
    if (move < ARKUI_TRANSITION_EDGE_TOP || move > ARKUI_TRANSITION_EDGE_END) {
        move = ARKUI_TRANSITION_EDGE_START;
    }
    ArkUI_TransitionEffect* option = new ArkUI_TransitionEffect { ARKUI_TRANSITION_EFFECT_MOVE };
    option->translate = nullptr;
    option->scale = nullptr;
    option->rotate = nullptr;
    option->appear = nullptr;
    option->disappear = nullptr;
    option->combine = nullptr;
    option->animation = nullptr;
    option->move = move;
    return option;
}

ArkUI_TransitionEffect* OH_ArkUI_CreateAsymmetricTransitionEffect(
    ArkUI_TransitionEffect* appear, ArkUI_TransitionEffect* disappear)
{
    if (!appear && !disappear) {
        return nullptr;
    }
    ArkUI_TransitionEffect* option = new ArkUI_TransitionEffect { ARKUI_TRANSITION_EFFECT_ASYMMETRIC };
    option->translate = nullptr;
    option->scale = nullptr;
    option->rotate = nullptr;
    option->combine = nullptr;
    option->animation = nullptr;
    option->appear = appear;
    option->disappear = disappear;
    return option;
}

void OH_ArkUI_TransitionEffect_Dispose(ArkUI_TransitionEffect* option)
{
    CHECK_NULL_VOID(option);
    if (option->toEffectOption) {
        delete option->toEffectOption;
        option->toEffectOption = nullptr;
    }
    delete option;
}

int32_t OH_ArkUI_TransitionEffect_Combine(ArkUI_TransitionEffect* option, ArkUI_TransitionEffect* combine)
{
    CHECK_NULL_RETURN(option, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto* currentOption = option;
    while (currentOption->combine) {
        currentOption = currentOption->combine;
    }
    currentOption->combine = combine;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_TransitionEffect_SetAnimation(ArkUI_TransitionEffect* option, ArkUI_AnimateOption* animation)
{
    CHECK_NULL_RETURN(option, ARKUI_ERROR_CODE_PARAM_INVALID);
    option->animation = animation;
    return ARKUI_ERROR_CODE_NO_ERROR;
}
#ifdef __cplusplus
};
#endif