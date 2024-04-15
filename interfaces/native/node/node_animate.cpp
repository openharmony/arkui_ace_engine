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

#include "animate_impl.h"
#include "native_type.h"

#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_AnimateOption* OH_ArkUI_AnimateOption_Create()
{
    ArkUI_AnimateOption* option = new ArkUI_AnimateOption;
    //duration default 1000
    option->duration = 1000;
    //tempo default 1.0
    option->tempo = 1.0f;
    option->curve = ArkUI_AnimationCurve::ARKUI_CURVE_EASE_IN_OUT;
    //delay default 0
    option->delay = 0;
    //iterations default 1
    option->iterations = 1;
    option->playMode = ArkUI_AnimationPlayMode::ARKUI_ANIMATION_PLAY_MODE_NORMAL;
    option->expectedFrameRateRange = nullptr;
    return option;
}

void OH_ArkUI_AnimateOption_Dispose(ArkUI_AnimateOption* option)
{
    if (option == nullptr) {
        return;
    }
    if (option->expectedFrameRateRange != nullptr) {
        delete option->expectedFrameRateRange;
        option->expectedFrameRateRange = nullptr;
    }
    delete option;
}

uint32_t OH_ArkUI_AnimateOption_GetDuration(ArkUI_AnimateOption* option)
{
    CHECK_NULL_RETURN(option, 0);
    return option->duration;
}

float OH_ArkUI_AnimateOption_GetTempo(ArkUI_AnimateOption* option)
{
    CHECK_NULL_RETURN(option, 0.0f);
    return option->tempo;
}

ArkUI_AnimationCurve OH_ArkUI_AnimateOption_GetCurve(ArkUI_AnimateOption* option)
{
    CHECK_NULL_RETURN(option, static_cast<ArkUI_AnimationCurve>(-1));
    return option->curve;
}

int32_t OH_ArkUI_AnimateOption_GetDelay(ArkUI_AnimateOption* option)
{
    CHECK_NULL_RETURN(option, 0);
    return option->delay;
}

int32_t OH_ArkUI_AnimateOption_GetIterations(ArkUI_AnimateOption* option)
{
    CHECK_NULL_RETURN(option, 0);
    return option->iterations;
}

ArkUI_AnimationPlayMode OH_ArkUI_AnimateOption_GetPlayMode(ArkUI_AnimateOption* option)
{
    CHECK_NULL_RETURN(option, static_cast<ArkUI_AnimationPlayMode>(-1));
    return option->playMode;
}

ArkUI_ExpectedFrameRateRange* OH_ArkUI_AnimateOption_GetExpectedFrameRateRange(ArkUI_AnimateOption* option)
{
    CHECK_NULL_RETURN(option, nullptr);
    return option->expectedFrameRateRange;
}

void OH_ArkUI_AnimateOption_SetDuration(ArkUI_AnimateOption* option, int32_t value)
{
    CHECK_NULL_VOID(option);
    // 设置小于0的值时按0处理
    if (value < 0) {
        value = 0;
    }
    option->duration = value;
}

void OH_ArkUI_AnimateOption_SetTempo(ArkUI_AnimateOption* option, float value)
{
    CHECK_NULL_VOID(option);
    // 小于0的值时按值为1处理
    if (value < 0) {
        value = 1;
    }
    option->tempo = value;
}

void OH_ArkUI_AnimateOption_SetCurve(ArkUI_AnimateOption* option, ArkUI_AnimationCurve value)
{
    CHECK_NULL_VOID(option);
    if (value >= ARKUI_CURVE_LINEAR && value <= ARKUI_CURVE_FRICTION) {
        option->curve = value;
    }
}

void OH_ArkUI_AnimateOption_SetDelay(ArkUI_AnimateOption* option, int32_t value)
{
    CHECK_NULL_VOID(option);
    option->delay = value;
}

void OH_ArkUI_AnimateOption_SetIterations(ArkUI_AnimateOption* option, int32_t value)
{
    CHECK_NULL_VOID(option);
    //取值范围：[-1, +∞)
    if (value < -1) {
        return;
    }
    option->iterations = value;
}

void OH_ArkUI_AnimateOption_SetPlayMode(ArkUI_AnimateOption* option, ArkUI_AnimationPlayMode value)
{
    CHECK_NULL_VOID(option);
    if (value >= ARKUI_ANIMATION_PLAY_MODE_NORMAL && value <= ARKUI_ANIMATION_PLAY_MODE_ALTERNATE_REVERSE) {
        option->playMode = value;
    }
}

void OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(ArkUI_AnimateOption* option, ArkUI_ExpectedFrameRateRange* value)
{
    CHECK_NULL_VOID(option);
    CHECK_NULL_VOID(value);
    option->expectedFrameRateRange = new ArkUI_ExpectedFrameRateRange { value->min, value->max, value->expected };
}

#ifdef __cplusplus
};
#endif