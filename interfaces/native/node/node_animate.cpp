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

#include <cstring>
#include <securec.h>

#include "animate_impl.h"
#include "node/node_model.h"
#include "ui/animation/animation_constants.h"

#include "base/error/error_code.h"
#include "base/hiviewdfx/histogram_wrapper.h"
#include "interfaces/native/native_error_message_macros.h"
#include "interfaces/native/node/render_node.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"

namespace {
constexpr int32_t MIN_KEYFRAME_SIZE = 2;
constexpr int32_t BOUNDS_W_IDX = 2;
constexpr int32_t BOUNDS_H_IDX = 3;
constexpr int32_t VEC2_CNT = 2;
constexpr int32_t ROTATE_CNT = 3;
constexpr int32_t BOUNDS_CNT = 4;
} // namespace

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_AnimateOption* OH_ArkUI_AnimateOption_Create()
{
    ArkUI_AnimateOption* option = new ArkUI_AnimateOption;
    // duration default 1000
    option->duration = 1000;
    // tempo default 1.0
    option->tempo = 1.0f;
    option->curve = ArkUI_AnimationCurve::ARKUI_CURVE_EASE_IN_OUT;
    // delay default 0
    option->delay = 0;
    // iterations default 1
    option->iterations = 1;
    option->playMode = ArkUI_AnimationPlayMode::ARKUI_ANIMATION_PLAY_MODE_NORMAL;
    option->expectedFrameRateRange = nullptr;
    option->iCurve = nullptr;
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
    option->duration = static_cast<uint32_t>(value);
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
    // 取值范围：[-1, +∞)
    if (value < -1) {
        return;
    }
    if (value == OHOS::Ace::ANIMATION_REPEAT_INFINITE) {
        ACE_ENGINE_HISTOGRAM_BOOLEAN("OH_ArkUI_AnimateOption_SetIterations", 1);
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

void OH_ArkUI_AnimateOption_SetICurve(ArkUI_AnimateOption* option, ArkUI_CurveHandle value)
{
    CHECK_NULL_VOID(option);
    CHECK_NULL_VOID(value);
    option->iCurve = value;
}

ArkUI_CurveHandle OH_ArkUI_AnimateOption_GetICurve(ArkUI_AnimateOption* option)
{
    CHECK_NULL_RETURN(option, nullptr);
    return option->iCurve;
}

ArkUI_KeyframeAnimateOption* OH_ArkUI_KeyframeAnimateOption_Create(int32_t size)
{
    if (size < 0) {
        return nullptr;
    }

    ArkUI_KeyframeAnimateOption* animateOption = new ArkUI_KeyframeAnimateOption;
    animateOption->keyframes.resize(size);
    animateOption->delay = 0;
    animateOption->iterations = 1;
    animateOption->onFinish = nullptr;
    animateOption->userData = nullptr;
    animateOption->expectedFrameRateRange = nullptr;

    for (int32_t i = 0; i < size; ++i) {
        // duration default 1000
        animateOption->keyframes[i].duration = 1000;
        animateOption->keyframes[i].curve = nullptr;
        animateOption->keyframes[i].event = nullptr;
        animateOption->keyframes[i].userData = nullptr;
    }
    return animateOption;
}

void OH_ArkUI_KeyframeAnimateOption_Dispose(ArkUI_KeyframeAnimateOption* option)
{
    CHECK_NULL_VOID(option);
    if (option->expectedFrameRateRange) {
        delete option->expectedFrameRateRange;
        option->expectedFrameRateRange = nullptr;
    }
    delete option;
}

int32_t OH_ArkUI_KeyframeAnimateOption_SetDelay(ArkUI_KeyframeAnimateOption* option, int32_t value)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    option->delay = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_KeyframeAnimateOption_SetIterations(ArkUI_KeyframeAnimateOption* option, int32_t value)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    //取值范围：[-1, +∞)
    if (value < -1) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "value is less than -1");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (value == OHOS::Ace::ANIMATION_REPEAT_INFINITE) {
        ACE_ENGINE_HISTOGRAM_BOOLEAN("OH_ArkUI_KeyframeAnimateOption_SetIterations", 1);
    }
    option->iterations = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_KeyframeAnimateOption_RegisterOnFinishCallback(
    ArkUI_KeyframeAnimateOption* option, void* userData, void (*onFinish)(void* userData))
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    option->onFinish = onFinish;
    option->userData = userData;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_KeyframeAnimateOption_SetDuration(ArkUI_KeyframeAnimateOption* option, int32_t value, int32_t index)
{
    if (option == nullptr || index < 0 || index >= static_cast<int32_t>(option->keyframes.size())) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null or index is invalid");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (value < 0) {
        value = 0;
    }
    option->keyframes[index].duration = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_KeyframeAnimateOption_SetCurve(
    ArkUI_KeyframeAnimateOption* option, ArkUI_CurveHandle value, int32_t index)
{
    if (option == nullptr || index < 0 || index >= static_cast<int32_t>(option->keyframes.size())) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null or index is invalid");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!value || !value->curve) {
        option->keyframes[index].curve = nullptr;
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "value or value->curve is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (value->type == ARKUI_CURVE_TYPE_SPRING_MOTION || value->type == ARKUI_CURVE_TYPE_RESPONSIVE_SPRING_MOTION ||
        value->type == ARKUI_CURVE_TYPE_INTERPOLATING_SPRING) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "curve type is invalid");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->keyframes[index].curve = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_KeyframeAnimateOption_RegisterOnEventCallback(
    ArkUI_KeyframeAnimateOption* option, void* userData, void (*event)(void* userData), int32_t index)
{
    if (option == nullptr || index < 0 || index >= static_cast<int32_t>(option->keyframes.size())) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null or index is invalid");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->keyframes[index].event = event;
    option->keyframes[index].userData = userData;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_KeyframeAnimateOption_GetDelay(ArkUI_KeyframeAnimateOption* option)
{
    CHECK_NULL_RETURN(option, 0);
    return option->delay;
}

int32_t OH_ArkUI_KeyframeAnimateOption_GetIterations(ArkUI_KeyframeAnimateOption* option)
{
    CHECK_NULL_RETURN(option, 1);
    return option->iterations;
}

int32_t OH_ArkUI_KeyframeAnimateOption_GetDuration(ArkUI_KeyframeAnimateOption* option, int32_t index)
{
    if (option == nullptr || index < 0 || index >= static_cast<int32_t>(option->keyframes.size())) {
        return 0;
    }
    return option->keyframes[index].duration;
}

ArkUI_CurveHandle OH_ArkUI_KeyframeAnimateOption_GetCurve(ArkUI_KeyframeAnimateOption* option, int32_t index)
{
    if (option == nullptr || index < 0 || index >= static_cast<int32_t>(option->keyframes.size())) {
        return nullptr;
    }
    return option->keyframes[index].curve;
}

ArkUI_AnimatorOption* OH_ArkUI_AnimatorOption_Create(int32_t keyframeSize)
{
    if (keyframeSize < 0) {
        return nullptr;
    }

    ArkUI_AnimatorOption* option = new ArkUI_AnimatorOption;
    option->keyframes.resize(keyframeSize);
    for (int32_t i = 0; i < keyframeSize; i++) {
        option->keyframes[i].curve = nullptr;
    }
    option->duration = 0;
    option->delay = 0;
    option->iterations = 1;
    option->fill = ARKUI_ANIMATION_FILL_MODE_FORWARDS;
    option->direction = ARKUI_ANIMATION_DIRECTION_NORMAL;
    option->begin = 0.0f;
    option->end = 1.0f;
    option->easing = nullptr;
    option->onFrame = nullptr;
    option->frameUserData = nullptr;
    option->onFinish = nullptr;
    option->finishUserData = nullptr;
    option->onCancel = nullptr;
    option->cancelUserData = nullptr;
    option->onRepeat = nullptr;
    option->repeatUserData = nullptr;
    option->expectedFrameRateRange = nullptr;
    return option;
}

void OH_ArkUI_AnimatorOption_Dispose(ArkUI_AnimatorOption* option)
{
    CHECK_NULL_VOID(option);
    if (option->expectedFrameRateRange) {
        delete option->expectedFrameRateRange;
        option->expectedFrameRateRange = nullptr;
    }
    delete option;
}

int32_t OH_ArkUI_AnimatorOption_SetDuration(ArkUI_AnimatorOption* option, int32_t value)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    if (value < 0) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "value is negative");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (value == 0 && option->iterations == OHOS::Ace::ANIMATION_REPEAT_INFINITE) {
        ACE_ENGINE_HISTOGRAM_BOOLEAN("OH_ArkUI_AnimatorOption_SetDuration", 1);
    }
    option->duration = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetDelay(ArkUI_AnimatorOption* option, int32_t value)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    option->delay = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetIterations(ArkUI_AnimatorOption* option, int32_t value)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    if (value < -1) {
        value = 1;
    }
    if (value == OHOS::Ace::ANIMATION_REPEAT_INFINITE && option->duration == 0) {
        ACE_ENGINE_HISTOGRAM_BOOLEAN("OH_ArkUI_AnimatorOption_SetDuration", 1);
    }
    option->iterations = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetFill(ArkUI_AnimatorOption* option, ArkUI_AnimationFillMode value)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    if (value > ARKUI_ANIMATION_FILL_MODE_BOTH || value < ARKUI_ANIMATION_FILL_MODE_NONE) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "value is out of range");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->fill = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetDirection(ArkUI_AnimatorOption* option, ArkUI_AnimationDirection value)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    if (value > ARKUI_ANIMATION_DIRECTION_ALTERNATE_REVERSE || value < ARKUI_ANIMATION_DIRECTION_NORMAL) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "value is out of range");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->direction = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    if (value) {
        if (value->type == ARKUI_CURVE_TYPE_SPRING || value->type == ARKUI_CURVE_TYPE_SPRING_MOTION ||
            value->type == ARKUI_CURVE_TYPE_RESPONSIVE_SPRING_MOTION ||
            value->type == ARKUI_CURVE_TYPE_INTERPOLATING_SPRING || value->type == ARKUI_CURVE_TYPE_CUSTOM) {
            option->easing = nullptr;
            SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "curve type is invalid");
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
    }

    option->easing = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetBegin(ArkUI_AnimatorOption* option, float value)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    if (option->keyframes.size() > 0) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "keyframes exist, cannot set begin");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->begin = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetEnd(ArkUI_AnimatorOption* option, float value)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    if (option->keyframes.size() > 0) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "keyframes exist, cannot set end");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->end = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetExpectedFrameRateRange(
    ArkUI_AnimatorOption* option, ArkUI_ExpectedFrameRateRange* value)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(value, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "value is null");
    option->expectedFrameRateRange = new ArkUI_ExpectedFrameRateRange { value->min, value->max, value->expected };
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetKeyframe(ArkUI_AnimatorOption* option, float time, float value, int32_t index)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    if (time < 0 || time > 1) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "time is out of range");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (index >= 0 && static_cast<size_t>(index) < option->keyframes.size()) {
        option->keyframes[index].keyTime = time;
        option->keyframes[index].keyValue = value;
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }
    SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "index is invalid");
    return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
}

int32_t OH_ArkUI_AnimatorOption_SetKeyframeCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value, int32_t index)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    if (value) {
        if (value->type == ARKUI_CURVE_TYPE_SPRING || value->type == ARKUI_CURVE_TYPE_SPRING_MOTION ||
            value->type == ARKUI_CURVE_TYPE_RESPONSIVE_SPRING_MOTION ||
            value->type == ARKUI_CURVE_TYPE_INTERPOLATING_SPRING || value->type == ARKUI_CURVE_TYPE_CUSTOM) {
            option->keyframes[index].curve = nullptr;
            SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "curve type is invalid");
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
    }

    if (index >= 0 && static_cast<size_t>(index) < option->keyframes.size()) {
        option->keyframes[index].curve = value;
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }
    SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "index is invalid");
    return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
}

int32_t OH_ArkUI_AnimatorOption_GetDuration(ArkUI_AnimatorOption* option)
{
    if (option != nullptr) {
        return option->duration;
    }
    return -1;
}

int32_t OH_ArkUI_AnimatorOption_GetDelay(ArkUI_AnimatorOption* option)
{
    if (option != nullptr) {
        return option->delay;
    }
    return -1;
}

int32_t OH_ArkUI_AnimatorOption_GetIterations(ArkUI_AnimatorOption* option)
{
    if (option != nullptr) {
        return option->iterations;
    }
    return -1;
}

ArkUI_AnimationFillMode OH_ArkUI_AnimatorOption_GetFill(ArkUI_AnimatorOption* option)
{
    if (option != nullptr) {
        return option->fill;
    }
    return static_cast<ArkUI_AnimationFillMode>(-1);
}

ArkUI_AnimationDirection OH_ArkUI_AnimatorOption_GetDirection(ArkUI_AnimatorOption* option)
{
    if (option != nullptr) {
        return option->direction;
    }
    return static_cast<ArkUI_AnimationDirection>(-1);
}

ArkUI_CurveHandle OH_ArkUI_AnimatorOption_GetCurve(ArkUI_AnimatorOption* option)
{
    if (option != nullptr) {
        return option->easing;
    }
    return nullptr;
}

float OH_ArkUI_AnimatorOption_GetBegin(ArkUI_AnimatorOption* option)
{
    if (option != nullptr) {
        return option->begin;
    }
    return 0.0f;
}

float OH_ArkUI_AnimatorOption_GetEnd(ArkUI_AnimatorOption* option)
{
    if (option != nullptr) {
        return option->end;
    }
    return 1.0f;
}

ArkUI_ExpectedFrameRateRange* OH_ArkUI_AnimatorOption_GetExpectedFrameRateRange(ArkUI_AnimatorOption* option)
{
    if (option != nullptr) {
        return option->expectedFrameRateRange;
    }
    return nullptr;
}

float OH_ArkUI_AnimatorOption_GetKeyframeTime(ArkUI_AnimatorOption* option, int32_t index)
{
    if (option != nullptr && index >= 0 && static_cast<size_t>(index) < option->keyframes.size()) {
        return option->keyframes[index].keyTime;
    }
    return -1.0f;
}

float OH_ArkUI_AnimatorOption_GetKeyframeValue(ArkUI_AnimatorOption* option, int32_t index)
{
    if (option != nullptr && index >= 0 && static_cast<size_t>(index) < option->keyframes.size()) {
        return option->keyframes[index].keyValue;
    }
    return -1.0f;
}

ArkUI_CurveHandle OH_ArkUI_AnimatorOption_GetKeyframeCurve(ArkUI_AnimatorOption* option, int32_t index)
{
    if (option != nullptr && index >= 0 && static_cast<size_t>(index) < option->keyframes.size()) {
        return option->keyframes[index].curve;
    }
    return nullptr;
}

void* OH_ArkUI_AnimatorEvent_GetUserData(ArkUI_AnimatorEvent* event)
{
    CHECK_NULL_RETURN(event, nullptr);
    return event->userData;
}

void* OH_ArkUI_AnimatorOnFrameEvent_GetUserData(ArkUI_AnimatorOnFrameEvent* event)
{
    CHECK_NULL_RETURN(event, nullptr);
    return event->userData;
}

float OH_ArkUI_AnimatorOnFrameEvent_GetValue(ArkUI_AnimatorOnFrameEvent* event)
{
    CHECK_NULL_RETURN(event, 0.0f);
    return event->progress;
}

int32_t OH_ArkUI_KeyframeAnimateOption_SetExpectedFrameRate(
    ArkUI_KeyframeAnimateOption* option, ArkUI_ExpectedFrameRateRange* frameRate)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(frameRate, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "frameRate is null");
    option->expectedFrameRateRange =
        new ArkUI_ExpectedFrameRateRange { frameRate->min, frameRate->max, frameRate->expected };
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

ArkUI_ExpectedFrameRateRange* OH_ArkUI_KeyframeAnimateOption_GetExpectedFrameRate(ArkUI_KeyframeAnimateOption* option)
{
    if (option != nullptr) {
        return option->expectedFrameRateRange;
    }
    return nullptr;
}

int32_t OH_ArkUI_AnimatorOption_RegisterOnFrameCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorOnFrameEvent* event))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Node model not initialized");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!option || !callback) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option or callback is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->onFrame = callback;
    option->frameUserData = userData;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_RegisterOnFinishCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Node model not initialized");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!option || !callback) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option or callback is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    option->onFinish = callback;
    option->finishUserData = userData;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_RegisterOnCancelCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Node model not initialized");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!option || !callback) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option or callback is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    option->onCancel = callback;
    option->cancelUserData = userData;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_RegisterOnRepeatCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Node model not initialized");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!option || !callback) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "option or callback is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    option->onRepeat = callback;
    option->repeatUserData = userData;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_Animator_ResetAnimatorOption(ArkUI_AnimatorHandle animator, ArkUI_AnimatorOption* option)
{
    return OHOS::Ace::AnimateModel::AnimatorReset(animator, option);
}

int32_t OH_ArkUI_Animator_Play(ArkUI_AnimatorHandle animator)
{
    return OHOS::Ace::AnimateModel::AnimatorPlay(animator);
}

int32_t OH_ArkUI_Animator_Finish(ArkUI_AnimatorHandle animator)
{
    return OHOS::Ace::AnimateModel::AnimatorFinish(animator);
}

int32_t OH_ArkUI_Animator_Pause(ArkUI_AnimatorHandle animator)
{
    return OHOS::Ace::AnimateModel::AnimatorPause(animator);
}

int32_t OH_ArkUI_Animator_Cancel(ArkUI_AnimatorHandle animator)
{
    return OHOS::Ace::AnimateModel::AnimatorCancel(animator);
}

int32_t OH_ArkUI_Animator_Reverse(ArkUI_AnimatorHandle animator)
{
    return OHOS::Ace::AnimateModel::AnimatorReverse(animator);
}

ArkUI_CurveHandle OH_ArkUI_Curve_CreateCurveByType(ArkUI_AnimationCurve curve)
{
    return OHOS::Ace::AnimateModel::InitCurve(curve);
}

ArkUI_CurveHandle OH_ArkUI_Curve_CreateStepsCurve(int32_t count, bool end)
{
    return OHOS::Ace::AnimateModel::StepsCurve(count, end);
}

ArkUI_CurveHandle OH_ArkUI_Curve_CreateCubicBezierCurve(float x1, float y1, float x2, float y2)
{
    return OHOS::Ace::AnimateModel::CubicBezierCurve(x1, y1, x2, y2);
}

ArkUI_CurveHandle OH_ArkUI_Curve_CreateSpringCurve(float velocity, float mass, float stiffness, float damping)
{
    return OHOS::Ace::AnimateModel::SpringCurve(velocity, mass, stiffness, damping);
}

ArkUI_CurveHandle OH_ArkUI_Curve_CreateSpringMotion(float response, float dampingFraction, float overlapDuration)
{
    return OHOS::Ace::AnimateModel::SpringMotion(response, dampingFraction, overlapDuration);
}

ArkUI_CurveHandle OH_ArkUI_Curve_CreateResponsiveSpringMotion(
    float response, float dampingFraction, float overlapDuration)
{
    return OHOS::Ace::AnimateModel::ResponsiveSpringMotion(response, dampingFraction, overlapDuration);
}

ArkUI_CurveHandle OH_ArkUI_Curve_CreateInterpolatingSpring(float velocity, float mass, float stiffness, float damping)
{
    return OHOS::Ace::AnimateModel::InterpolatingSpring(velocity, mass, stiffness, damping);
}

ArkUI_CurveHandle OH_ArkUI_Curve_CreateCustomCurve(void* userData, float (*interpolate)(float fraction, void* userdata))
{
    return OHOS::Ace::AnimateModel::CustomCurve(userData, interpolate);
}

void OH_ArkUI_Curve_DisposeCurve(ArkUI_CurveHandle curveHandle)
{
    return OHOS::Ace::AnimateModel::DisposeCurve(curveHandle);
}

ArkUI_MotionPathOptions* OH_ArkUI_MotionPathOptions_Create()
{
    ArkUI_MotionPathOptions* options = new ArkUI_MotionPathOptions;
    auto path = new char[1];
    path[0] = '\0';
    options->path = path;
    options->from = 0.0f;
    options->to = 1.0f;
    options->rotatable = false;
    return options;
}

void OH_ArkUI_MotionPathOptions_Dispose(ArkUI_MotionPathOptions* options)
{
    if (!options) {
        return;
    }
    if (options->path) {
        delete[] options->path;
        options->path = nullptr;
    }
    delete options;
}

ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetPath(ArkUI_MotionPathOptions* options, const char* svgPath)
{
    if (!options || !svgPath) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "options or svgPath is null");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (options->path != nullptr) {
        delete[] options->path;
        options->path = nullptr;
    }
    size_t len = strlen(svgPath) + 1;
    auto path = new char[len];
    if (strcpy_s(path, len, svgPath) != 0) {
        delete[] path;
        path = nullptr;
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_ANIMATION,
            "OH_ArkUI_MotionPathOptions_SetPath: strcpy_s copy svgPath failed, svgPath length: %zu", len);
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "strcpy_s copy svgPath failed");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    options->path = path;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetPath(
    const ArkUI_MotionPathOptions* options, char* svgPathBuffer, const int32_t bufferSize, int32_t* writeLength)
{
    if (!options || !options->path || !svgPathBuffer || bufferSize <= 0 || !writeLength) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__,
            "options, options->path, svgPathBuffer or writeLength is null, or bufferSize <= 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }

    const size_t bufferSizeU = static_cast<size_t>(bufferSize);
    const size_t srcLen = strlen(options->path);
    const size_t requiredSize = srcLen + 1;
    *writeLength = requiredSize;
    if (requiredSize > bufferSizeU) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR, __FUNCTION__, "buffer size is too small");
        return ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    if (strcpy_s(svgPathBuffer, bufferSizeU, options->path) != 0) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_ANIMATION,
            "OH_ArkUI_MotionPathOptions_GetPath: strcpy_s copy path failed, required size: %zu", requiredSize);
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "strcpy_s copy path failed");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetFrom(ArkUI_MotionPathOptions* options, const float from)
{
    if (!options) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "options is null");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (from < 0 || from > 1 || from > options->to) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE, __FUNCTION__, "from is out of range");
        return ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    options->from = from;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetFrom(const ArkUI_MotionPathOptions* options, float* from)
{
    if (!options || !from) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "options or from is null");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *from = options->from;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetTo(ArkUI_MotionPathOptions* options, const float to)
{
    if (!options) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "options is null");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (to < 0 || to > 1 || to < options->from) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE, __FUNCTION__, "to is out of range");
        return ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    options->to = to;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetTo(const ArkUI_MotionPathOptions* options, float* to)
{
    if (!options || !to) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "options or to is null");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *to = options->to;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_SetRotatable(ArkUI_MotionPathOptions* options, const bool rotatable)
{
    if (!options) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "options is null");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    options->rotatable = rotatable;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_MotionPathOptions_GetRotatable(const ArkUI_MotionPathOptions* options, bool* rotatable)
{
    if (!options || !rotatable) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "options or rotatable is null");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *rotatable = options->rotatable;
    return ARKUI_ERROR_CODE_NO_ERROR;
}
// =============================================================================
// Group Animation Helpers
// =============================================================================

static bool IsDurationIndependentCurveType(ArkUI_CurveType type)
{
    return type == ARKUI_CURVE_TYPE_SPRING_MOTION || type == ARKUI_CURVE_TYPE_RESPONSIVE_SPRING_MOTION ||
           type == ARKUI_CURVE_TYPE_INTERPOLATING_SPRING;
}

static int32_t GetPropertyValueSize(OH_ArkUI_AnimationPropertyType propertyType)
{
    switch (propertyType) {
        case OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION:
            return VEC2_CNT;
        case OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION_X:
        case OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION_Y:
        case OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION_Z:
        case OH_ARKUI_ANIMATION_PROPERTY_SCALE_X:
        case OH_ARKUI_ANIMATION_PROPERTY_SCALE_Y:
        case OH_ARKUI_ANIMATION_PROPERTY_ROTATION_X:
        case OH_ARKUI_ANIMATION_PROPERTY_ROTATION_Y:
        case OH_ARKUI_ANIMATION_PROPERTY_ROTATION_Z:
        case OH_ARKUI_ANIMATION_PROPERTY_OPACITY:
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_X:
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_Y:
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_WIDTH:
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_HEIGHT:
        case OH_ARKUI_ANIMATION_PROPERTY_BACKGROUND_COLOR:
            return 1;
        case OH_ARKUI_ANIMATION_PROPERTY_SCALE:
            return VEC2_CNT;
        case OH_ARKUI_ANIMATION_PROPERTY_ROTATION:
            return ROTATE_CNT;
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS:
            return BOUNDS_CNT;
        default:
            return -1;
    }
}

static bool ValidatePropertyValue(
    OH_ArkUI_AnimationPropertyType propertyType, const ArkUI_NumberValue* value, int32_t size)
{
    int32_t expectedSize = GetPropertyValueSize(propertyType);
    if (expectedSize < 0 || size != expectedSize) {
        return false;
    }
    if (value == nullptr) {
        return false;
    }
    if (propertyType == OH_ARKUI_ANIMATION_PROPERTY_OPACITY) {
        if (value[0].f32 < 0.0f || value[0].f32 > 1.0f) {
            return false;
        }
    } else if (propertyType == OH_ARKUI_ANIMATION_PROPERTY_BOUNDS) {
        if (value[BOUNDS_W_IDX].i32 < 0 || value[BOUNDS_H_IDX].i32 < 0) {
            return false;
        }
    } else if (propertyType == OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_WIDTH ||
               propertyType == OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_HEIGHT) {
        if (value[0].i32 < 0) {
            return false;
        }
    }
    return true;
}

// =============================================================================
// PropertyAnimation
// =============================================================================

OH_ArkUI_PropertyAnimationHandle OH_ArkUI_NativeModule_PropertyAnimation_Create(
    OH_ArkUI_AnimationPropertyType propertyType)
{
    if (propertyType < OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION ||
        propertyType > OH_ARKUI_ANIMATION_PROPERTY_BACKGROUND_COLOR) {
        return nullptr;
    }
    return new OH_ArkUI_PropertyAnimation { .propertyType = propertyType };
}

void OH_ArkUI_NativeModule_PropertyAnimation_Destroy(OH_ArkUI_PropertyAnimationHandle animation)
{
    if (animation == nullptr) {
        return;
    }
    delete animation;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetFromValue(
    OH_ArkUI_PropertyAnimationHandle animation, const ArkUI_NumberValue* value, int32_t size)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (!ValidatePropertyValue(animation->propertyType, value, size)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->fromValue.assign(value, value + size);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetToValue(
    OH_ArkUI_PropertyAnimationHandle animation, const ArkUI_NumberValue* value, int32_t size)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (!ValidatePropertyValue(animation->propertyType, value, size)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->toValue.assign(value, value + size);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetFromValue(
    OH_ArkUI_PropertyAnimationHandle animation, ArkUI_NumberValue* value, int32_t size)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(value, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "value is null");
    if (animation->fromValue.empty()) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND, __FUNCTION__, "fromValue is not set");
        return ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND;
    }
    int32_t expectedSize = GetPropertyValueSize(animation->propertyType);
    if (size != expectedSize) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR, __FUNCTION__, "buffer size mismatch");
        return ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    for (int32_t i = 0; i < expectedSize; ++i) {
        value[i] = animation->fromValue[i];
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetToValue(
    OH_ArkUI_PropertyAnimationHandle animation, ArkUI_NumberValue* value, int32_t size)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(value, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "value is null");
    if (animation->toValue.empty()) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND, __FUNCTION__, "toValue is not set");
        return ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND;
    }
    int32_t expectedSize = GetPropertyValueSize(animation->propertyType);
    if (size != expectedSize) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR, __FUNCTION__, "buffer size mismatch");
        return ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    for (int32_t i = 0; i < expectedSize; ++i) {
        value[i] = animation->toValue[i];
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetDuration(
    OH_ArkUI_PropertyAnimationHandle animation, int32_t duration)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (duration <= 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duration must be greater than 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->duration = duration;
    animation->hasDuration = true;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetDuration(
    OH_ArkUI_PropertyAnimationHandle animation, int32_t* duration)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(duration, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duration is null");
    if (!animation->hasDuration) {
        return ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND;
    }
    *duration = animation->duration;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetDelay(
    OH_ArkUI_PropertyAnimationHandle animation, int32_t delay)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    animation->delay = delay;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetDelay(
    OH_ArkUI_PropertyAnimationHandle animation, int32_t* delay)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(delay, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "delay is null");
    *delay = animation->delay;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetCurve(
    OH_ArkUI_PropertyAnimationHandle animation, ArkUI_CurveHandle curve)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(curve, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "curve is null");
    animation->curve = curve;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetCurve(
    OH_ArkUI_PropertyAnimationHandle animation, ArkUI_CurveHandle* outBorrowedCurve)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        outBorrowedCurve, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "outBorrowedCurve is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        animation->curve, ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND, __FUNCTION__, "curve is not set");
    *outBorrowedCurve = animation->curve;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetTempo(
    OH_ArkUI_PropertyAnimationHandle animation, float tempo)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (tempo <= 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "tempo must be greater than 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->tempo = tempo;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetTempo(
    OH_ArkUI_PropertyAnimationHandle animation, float* tempo)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(tempo, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "tempo is null");
    *tempo = animation->tempo;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetAutoReverse(
    OH_ArkUI_PropertyAnimationHandle animation, bool autoReverse)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    animation->autoReverse = autoReverse;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetAutoReverse(
    OH_ArkUI_PropertyAnimationHandle animation, bool* autoReverse)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(autoReverse, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "autoReverse is null");
    *autoReverse = animation->autoReverse;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetTargetNode(
    OH_ArkUI_PropertyAnimationHandle animation, ArkUI_RenderNodeHandle targetNode)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    animation->targetNode = targetNode;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetTargetNode(
    OH_ArkUI_PropertyAnimationHandle animation, ArkUI_RenderNodeHandle* outBorrowedTargetNode)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        outBorrowedTargetNode, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "outBorrowedTargetNode is null");
    *outBorrowedTargetNode = animation->targetNode;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetIterations(
    OH_ArkUI_PropertyAnimationHandle animation, int32_t iterations)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (iterations < -1 || iterations == 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "iterations must be -1 or greater than 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->iterations = iterations;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetIterations(
    OH_ArkUI_PropertyAnimationHandle animation, int32_t* iterations)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(iterations, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "iterations is null");
    *iterations = animation->iterations;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

// =============================================================================
// KeyframeAnimation
// =============================================================================

OH_ArkUI_KeyframeAnimationHandle OH_ArkUI_NativeModule_KeyframeAnimation_Create(
    OH_ArkUI_AnimationPropertyType propertyType, int32_t size)
{
    if (propertyType < OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION ||
        propertyType > OH_ARKUI_ANIMATION_PROPERTY_BACKGROUND_COLOR) {
        return nullptr;
    }
    if (size < MIN_KEYFRAME_SIZE) {
        return nullptr;
    }
    auto* animation = new OH_ArkUI_KeyframeAnimation();
    animation->propertyType = propertyType;
    animation->keyframes.resize(size);
    float percent = 1.0f / (size - 1);
    for (int32_t i = 0; i < size - 1; ++i) {
        animation->keyframes[i].keyTime = percent * i;
    }
    animation->keyframes[size - 1].keyTime = 1.0f;
    return animation;
}

void OH_ArkUI_NativeModule_KeyframeAnimation_Destroy(OH_ArkUI_KeyframeAnimationHandle animation)
{
    if (animation == nullptr) {
        return;
    }
    delete animation;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetKeyTimes(
    OH_ArkUI_KeyframeAnimationHandle animation, const float* keyTimes, int32_t size)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(keyTimes, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "keyTimes is null");
    if (size != static_cast<int32_t>(animation->keyframes.size()) || size < MIN_KEYFRAME_SIZE) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (keyTimes[0] < 0.0f || keyTimes[0] > 1.0f) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    for (int32_t i = 1; i < size; ++i) {
        if (keyTimes[i] < 0.0f || keyTimes[i] > 1.0f || keyTimes[i] < keyTimes[i - 1]) {
            return ARKUI_ERROR_CODE_PARAM_INVALID;
        }
    }
    for (int32_t i = 0; i < size; ++i) {
        animation->keyframes[i].keyTime = keyTimes[i];
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetKeyTime(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t index, float* keyTime)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(keyTime, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "keyTime is null");
    if (index < 0 || index >= static_cast<int32_t>(animation->keyframes.size())) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *keyTime = animation->keyframes[index].keyTime;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetKeyTime(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t index, float keyTime)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    auto size = static_cast<int32_t>(animation->keyframes.size());
    if (index < 0 || index >= size) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (keyTime < 0.0f || keyTime > 1.0f) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->keyframes[index].keyTime = keyTime;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetValue(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t index, const ArkUI_NumberValue* value, int32_t size)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (index < 0 || index >= static_cast<int32_t>(animation->keyframes.size())) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (!ValidatePropertyValue(animation->propertyType, value, size)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->keyframes[index].values.assign(value, value + size);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetValues(
    OH_ArkUI_KeyframeAnimationHandle animation, const ArkUI_NumberValue* values, int32_t size)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(values, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "values is null");
    int32_t keyframeCount = static_cast<int32_t>(animation->keyframes.size());
    int32_t valuesPerKeyframe = GetPropertyValueSize(animation->propertyType);
    int32_t expectedSize = keyframeCount * valuesPerKeyframe;
    if (size != expectedSize || size < 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "values size mismatch");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    for (int32_t i = 0; i < keyframeCount; ++i) {
        const ArkUI_NumberValue* chunk = values + i * valuesPerKeyframe;
        if (!ValidatePropertyValue(animation->propertyType, chunk, valuesPerKeyframe)) {
            SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "invalid property value");
            return ARKUI_ERROR_CODE_PARAM_INVALID;
        }
    }
    for (int32_t i = 0; i < keyframeCount; ++i) {
        const ArkUI_NumberValue* chunk = values + i * valuesPerKeyframe;
        animation->keyframes[i].values.assign(chunk, chunk + valuesPerKeyframe);
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetValue(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t index, ArkUI_NumberValue* value, int32_t size)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(value, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "value is null");
    if (index < 0 || index >= static_cast<int32_t>(animation->keyframes.size())) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (animation->keyframes[index].values.empty()) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND, __FUNCTION__, "keyframe value is not set");
        return ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND;
    }
    int32_t expectedSize = GetPropertyValueSize(animation->propertyType);
    if (size != expectedSize) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR, __FUNCTION__, "buffer size mismatch");
        return ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    for (int32_t i = 0; i < expectedSize; ++i) {
        value[i] = animation->keyframes[index].values[i];
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetCurves(
    OH_ArkUI_KeyframeAnimationHandle animation, const ArkUI_CurveHandle* value, int32_t size)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(value, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "value is null");
    if (size != static_cast<int32_t>(animation->keyframes.size())) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    for (int32_t i = 0; i < size; ++i) {
        if (value[i] == nullptr || value[i]->type == ARKUI_CURVE_TYPE_SPRING_MOTION ||
            value[i]->type == ARKUI_CURVE_TYPE_RESPONSIVE_SPRING_MOTION ||
            value[i]->type == ARKUI_CURVE_TYPE_INTERPOLATING_SPRING) {
            return ARKUI_ERROR_CODE_PARAM_INVALID;
        }
    }
    for (int32_t i = 0; i < size; ++i) {
        animation->keyframes[i].curve = value[i];
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetCurve(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t index, ArkUI_CurveHandle curve)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(curve, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "curve is null");
    if (curve->type == ARKUI_CURVE_TYPE_SPRING_MOTION || curve->type == ARKUI_CURVE_TYPE_RESPONSIVE_SPRING_MOTION ||
        curve->type == ARKUI_CURVE_TYPE_INTERPOLATING_SPRING) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (index < 0 || index >= static_cast<int32_t>(animation->keyframes.size())) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->keyframes[index].curve = curve;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetCurve(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t index, ArkUI_CurveHandle* outBorrowedCurve)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        outBorrowedCurve, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "outBorrowedCurve is null");
    if (index < 0 || index >= static_cast<int32_t>(animation->keyframes.size())) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *outBorrowedCurve = animation->keyframes[index].curve;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetDuration(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t duration)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (duration <= 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duration must be greater than 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->duration = duration;
    animation->hasDuration = true;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetDuration(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t* duration)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(duration, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duration is null");
    if (!animation->hasDuration) {
        return ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND;
    }
    *duration = animation->duration;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetDelay(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t delay)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    animation->delay = delay;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetDelay(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t* delay)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(delay, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "delay is null");
    *delay = animation->delay;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetTempo(
    OH_ArkUI_KeyframeAnimationHandle animation, float tempo)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (tempo <= 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "tempo must be greater than 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->tempo = tempo;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetTempo(
    OH_ArkUI_KeyframeAnimationHandle animation, float* tempo)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(tempo, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "tempo is null");
    *tempo = animation->tempo;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetAutoReverse(
    OH_ArkUI_KeyframeAnimationHandle animation, bool autoReverse)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    animation->autoReverse = autoReverse;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetAutoReverse(
    OH_ArkUI_KeyframeAnimationHandle animation, bool* autoReverse)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(autoReverse, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "autoReverse is null");
    *autoReverse = animation->autoReverse;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetTargetNode(
    OH_ArkUI_KeyframeAnimationHandle animation, ArkUI_RenderNodeHandle targetNode)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    animation->targetNode = targetNode;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetTargetNode(
    OH_ArkUI_KeyframeAnimationHandle animation, ArkUI_RenderNodeHandle* outBorrowedTargetNode)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        outBorrowedTargetNode, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "outBorrowedTargetNode is null");
    *outBorrowedTargetNode = animation->targetNode;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetIterations(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t iterations)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (iterations < -1 || iterations == 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "iterations must be -1 or greater than 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->iterations = iterations;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetIterations(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t* iterations)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(iterations, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "iterations is null");
    *iterations = animation->iterations;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

// =============================================================================
// PathAnimation
// =============================================================================

OH_ArkUI_PathAnimationHandle OH_ArkUI_NativeModule_PathAnimation_Create(const char* path)
{
    if (path == nullptr) {
        return nullptr;
    }
    if (path[0] == '\0') {
        return nullptr;
    }
    if (strstr(path, "start") != nullptr || strstr(path, "end") != nullptr) {
        return nullptr;
    }
    auto* animation = new OH_ArkUI_PathAnimation();
    size_t len = strlen(path) + 1;
    animation->path = new char[len];
    if (strcpy_s(animation->path, len, path) != 0) {
        delete[] animation->path;
        animation->path = nullptr;
        delete animation;
        return nullptr;
    }
    return animation;
}

void OH_ArkUI_NativeModule_PathAnimation_Destroy(OH_ArkUI_PathAnimationHandle animation)
{
    if (animation == nullptr) {
        return;
    }
    if (animation->path != nullptr) {
        delete[] animation->path;
        animation->path = nullptr;
    }
    delete animation;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetDuration(
    OH_ArkUI_PathAnimationHandle animation, int32_t duration)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (duration <= 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duration must be greater than 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->duration = duration;
    animation->hasDuration = true;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetDuration(
    OH_ArkUI_PathAnimationHandle animation, int32_t* duration)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(duration, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duration is null");
    if (!animation->hasDuration) {
        return ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND;
    }
    *duration = animation->duration;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetDelay(OH_ArkUI_PathAnimationHandle animation, int32_t delay)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    animation->delay = delay;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetDelay(OH_ArkUI_PathAnimationHandle animation, int32_t* delay)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(delay, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "delay is null");
    *delay = animation->delay;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetCurve(
    OH_ArkUI_PathAnimationHandle animation, ArkUI_CurveHandle curve)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(curve, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "curve is null");
    if (IsDurationIndependentCurveType(curve->type)) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duration-independent curve is not allowed");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->curve = curve;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetCurve(
    OH_ArkUI_PathAnimationHandle animation, ArkUI_CurveHandle* outBorrowedCurve)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        outBorrowedCurve, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "outBorrowedCurve is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        animation->curve, ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND, __FUNCTION__, "curve is not set");
    *outBorrowedCurve = animation->curve;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetTempo(OH_ArkUI_PathAnimationHandle animation, float tempo)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (tempo <= 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "tempo must be greater than 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->tempo = tempo;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetTempo(OH_ArkUI_PathAnimationHandle animation, float* tempo)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(tempo, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "tempo is null");
    *tempo = animation->tempo;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetAutoReverse(
    OH_ArkUI_PathAnimationHandle animation, bool autoReverse)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    animation->autoReverse = autoReverse;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetAutoReverse(
    OH_ArkUI_PathAnimationHandle animation, bool* autoReverse)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(autoReverse, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "autoReverse is null");
    *autoReverse = animation->autoReverse;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetTargetNode(
    OH_ArkUI_PathAnimationHandle animation, ArkUI_RenderNodeHandle targetNode)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    animation->targetNode = targetNode;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetTargetNode(
    OH_ArkUI_PathAnimationHandle animation, ArkUI_RenderNodeHandle* outBorrowedTargetNode)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        outBorrowedTargetNode, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "outBorrowedTargetNode is null");
    *outBorrowedTargetNode = animation->targetNode;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetIterations(
    OH_ArkUI_PathAnimationHandle animation, int32_t iterations)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (iterations < -1 || iterations == 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "iterations must be -1 or greater than 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    animation->iterations = iterations;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetIterations(
    OH_ArkUI_PathAnimationHandle animation, int32_t* iterations)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(iterations, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "iterations is null");
    *iterations = animation->iterations;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetAutoRotation(
    OH_ArkUI_PathAnimationHandle animation, bool autoRotation)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    animation->autoRotation = autoRotation;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetAutoRotation(
    OH_ArkUI_PathAnimationHandle animation, bool* autoRotation)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(autoRotation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "autoRotation is null");
    *autoRotation = animation->autoRotation;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

// =============================================================================
// AnimationGroup
// =============================================================================

OH_ArkUI_AnimationGroupHandle OH_ArkUI_NativeModule_AnimationGroup_Create()
{
    return new OH_ArkUI_AnimationGroup();
}

void OH_ArkUI_NativeModule_AnimationGroup_Destroy(OH_ArkUI_AnimationGroupHandle group)
{
    if (group == nullptr) {
        return;
    }
    if (group->expectedFrameRateRange != nullptr) {
        delete group->expectedFrameRateRange;
        group->expectedFrameRateRange = nullptr;
    }
    delete group;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetDuration(OH_ArkUI_AnimationGroupHandle group, int32_t duration)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    if (duration <= 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duration must be greater than 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    group->duration = duration;
    group->hasDuration = true;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetDuration(OH_ArkUI_AnimationGroupHandle group, int32_t* duration)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(duration, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duration is null");
    if (!group->hasDuration) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND, __FUNCTION__, "duration is not set");
        return ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND;
    }
    *duration = group->duration;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetDelay(OH_ArkUI_AnimationGroupHandle group, int32_t delay)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    if (delay < 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "delay must be greater than or equal to 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    group->delay = delay;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetDelay(OH_ArkUI_AnimationGroupHandle group, int32_t* delay)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(delay, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "delay is null");
    *delay = group->delay;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetCurve(
    OH_ArkUI_AnimationGroupHandle group, ArkUI_CurveHandle curve)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(curve, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "curve is null");
    if (IsDurationIndependentCurveType(curve->type)) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duration-independent curve is not allowed");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    group->curve = curve;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetCurve(
    OH_ArkUI_AnimationGroupHandle group, ArkUI_CurveHandle* outBorrowedCurve)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        outBorrowedCurve, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "outBorrowedCurve is null");
    if (group->curve == nullptr) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND, __FUNCTION__, "curve is not set");
        return ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND;
    }
    *outBorrowedCurve = group->curve;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetTempo(OH_ArkUI_AnimationGroupHandle group, float tempo)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    if (tempo <= 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "tempo must be greater than 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    group->tempo = tempo;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetTempo(OH_ArkUI_AnimationGroupHandle group, float* tempo)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(tempo, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "tempo is null");
    *tempo = group->tempo;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetAutoReverse(
    OH_ArkUI_AnimationGroupHandle group, bool autoReverse)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    group->autoReverse = autoReverse;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetAutoReverse(
    OH_ArkUI_AnimationGroupHandle group, bool* autoReverse)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(autoReverse, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "autoReverse is null");
    *autoReverse = group->autoReverse;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetTargetNode(
    OH_ArkUI_AnimationGroupHandle group, ArkUI_RenderNodeHandle targetNode)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    group->targetNode = targetNode;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetTargetNode(
    OH_ArkUI_AnimationGroupHandle group, ArkUI_RenderNodeHandle* outBorrowedTargetNode)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        outBorrowedTargetNode, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "outBorrowedTargetNode is null");
    *outBorrowedTargetNode = group->targetNode;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetIterations(
    OH_ArkUI_AnimationGroupHandle group, int32_t iterations)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    if (iterations < -1 || iterations == 0) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "iterations must be -1 or greater than 0");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    group->iterations = iterations;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetIterations(
    OH_ArkUI_AnimationGroupHandle group, int32_t* iterations)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(iterations, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "iterations is null");
    *iterations = group->iterations;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetExpectedFrameRateRange(
    OH_ArkUI_AnimationGroupHandle group, const ArkUI_ExpectedFrameRateRange* frameRate)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(frameRate, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "frameRate is null");
    if (frameRate->min > frameRate->expected || frameRate->expected > frameRate->max) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (group->expectedFrameRateRange != nullptr) {
        *(group->expectedFrameRateRange) = *frameRate;
    } else {
        group->expectedFrameRateRange =
            new ArkUI_ExpectedFrameRateRange { frameRate->min, frameRate->max, frameRate->expected };
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetExpectedFrameRateRange(
    OH_ArkUI_AnimationGroupHandle group, ArkUI_ExpectedFrameRateRange* frameRate)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(frameRate, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "frameRate is null");
    if (group->expectedFrameRateRange == nullptr) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND, __FUNCTION__, "expectedFrameRateRange is not set");
        return ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND;
    }
    *frameRate = *group->expectedFrameRateRange;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_RegisterOnFinishCallback(
    OH_ArkUI_AnimationGroupHandle group, void* userData, void (*callback)(void* userData))
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(callback, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "callback is null");
    group->onFinish = callback;
    group->userData = userData;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_AddPropertyAnimation(
    OH_ArkUI_AnimationGroupHandle group, OH_ArkUI_PropertyAnimationHandle animation)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (animation->propertyType < OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION ||
        animation->propertyType > OH_ARKUI_ANIMATION_PROPERTY_BACKGROUND_COLOR) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID, __FUNCTION__, "propertyType out of range");
        return ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID;
    }
    if (animation->toValue.empty()) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID, __FUNCTION__, "toValue is empty");
        return ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID;
    }
    for (const auto& child : group->childAnimations) {
        if (const auto* prop = std::get_if<OH_ArkUI_PropertyAnimationHandle>(&child)) {
            if (*prop == animation) {
                SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duplicate property animation");
                return ARKUI_ERROR_CODE_PARAM_INVALID;
            }
        }
    }
    group->childAnimations.push_back(animation);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_AddKeyframeAnimation(
    OH_ArkUI_AnimationGroupHandle group, OH_ArkUI_KeyframeAnimationHandle animation)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (animation->propertyType < OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION ||
        animation->propertyType > OH_ARKUI_ANIMATION_PROPERTY_BACKGROUND_COLOR) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID, __FUNCTION__, "propertyType out of range");
        return ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID;
    }
    if (animation->keyframes.empty()) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID, __FUNCTION__, "keyframes is empty");
        return ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID;
    }
    int32_t expectedValueSize = GetPropertyValueSize(animation->propertyType);
    float prevKeyTime = -1.0f;
    for (const auto& kf : animation->keyframes) {
        if (kf.keyTime < prevKeyTime) {
            SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID, __FUNCTION__, "keyTime is not non-decreasing");
            return ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID;
        }
        if (static_cast<int32_t>(kf.values.size()) != expectedValueSize) {
            SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID, __FUNCTION__, "keyframe values size mismatch");
            return ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID;
        }
        if (kf.curve && IsDurationIndependentCurveType(kf.curve->type)) {
            SET_ERROR_MESSAGE(
                ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID, __FUNCTION__, "duration-independent curve is not allowed");
            return ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID;
        }
        prevKeyTime = kf.keyTime;
    }
    for (const auto& child : group->childAnimations) {
        if (const auto* kf = std::get_if<OH_ArkUI_KeyframeAnimationHandle>(&child)) {
            if (*kf == animation) {
                SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duplicate keyframe animation");
                return ARKUI_ERROR_CODE_PARAM_INVALID;
            }
        }
    }
    group->childAnimations.push_back(animation);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_AddPathAnimation(
    OH_ArkUI_AnimationGroupHandle group, OH_ArkUI_PathAnimationHandle animation)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(animation, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "animation is null");
    if (animation->path == nullptr) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID, __FUNCTION__, "path is null");
        return ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID;
    }
    if (animation->curve && IsDurationIndependentCurveType(animation->curve->type)) {
        SET_ERROR_MESSAGE(
            ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID, __FUNCTION__, "duration-independent curve is not allowed");
        return ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID;
    }
    for (const auto& child : group->childAnimations) {
        if (const auto* path = std::get_if<OH_ArkUI_PathAnimationHandle>(&child)) {
            if (*path == animation) {
                SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "duplicate path animation");
                return ARKUI_ERROR_CODE_PARAM_INVALID;
            }
        }
    }
    group->childAnimations.push_back(animation);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_AddAnimationGroup(
    ArkUI_ContextHandle context, OH_ArkUI_AnimationGroupHandle group, const char* key)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(context, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "context is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(group, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "group is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(key, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "key is null");
    if (group->childAnimations.empty()) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID, __FUNCTION__, "group has no child animations");
        return ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID;
    }
    std::vector<ArkUIRenderNodeHandle> resolvedTargets;
    resolvedTargets.reserve(group->childAnimations.size());
    for (const auto& child : group->childAnimations) {
        ArkUI_RenderNodeHandle resolved = nullptr;
        if (const auto* prop = std::get_if<OH_ArkUI_PropertyAnimationHandle>(&child)) {
            resolved = (*prop)->targetNode ? (*prop)->targetNode : group->targetNode;
        } else if (const auto* kf = std::get_if<OH_ArkUI_KeyframeAnimationHandle>(&child)) {
            resolved = (*kf)->targetNode ? (*kf)->targetNode : group->targetNode;
        } else if (const auto* path = std::get_if<OH_ArkUI_PathAnimationHandle>(&child)) {
            resolved = (*path)->targetNode ? (*path)->targetNode : group->targetNode;
        }
        if (resolved == nullptr) {
            SET_ERROR_MESSAGE(
                ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID, __FUNCTION__, "child has no resolvable target node");
            return ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID;
        }
        resolvedTargets.push_back(resolved->renderNodeHandle);
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(impl, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "impl is null");
    return static_cast<ArkUI_ErrorCode>(
        impl->getAnimation()->addAnimationGroup(reinterpret_cast<ArkUIContext*>(context), group, resolvedTargets.data(),
            static_cast<ArkUI_Uint32>(resolvedTargets.size()), key));
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_RemoveAnimationGroup(ArkUI_ContextHandle context, const char* key)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(context, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "context is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(key, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "key is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(impl, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "impl is null");
    return static_cast<ArkUI_ErrorCode>(
        impl->getAnimation()->removeAnimationGroup(reinterpret_cast<ArkUIContext*>(context), key));
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_GetAnimationGroupState(
    ArkUI_ContextHandle context, const char* key, OH_ArkUI_AnimationGroupState* state)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(context, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "context is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(key, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "key is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(state, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "state is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(impl, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "impl is null");
    return static_cast<ArkUI_ErrorCode>(impl->getAnimation()->getAnimationGroupState(
        reinterpret_cast<ArkUIContext*>(context), key, reinterpret_cast<ArkUI_Int32*>(state)));
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_HasAnimationGroup(ArkUI_ContextHandle context, const char* key, bool* exists)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(context, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "context is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(key, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "key is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(exists, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "exists is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(impl, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "impl is null");
    return static_cast<ArkUI_ErrorCode>(
        impl->getAnimation()->hasAnimationGroup(reinterpret_cast<ArkUIContext*>(context), key, exists));
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_PauseAnimationGroup(ArkUI_ContextHandle context, const char* key)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(context, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "context is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(key, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "key is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(impl, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "impl is null");
    return static_cast<ArkUI_ErrorCode>(
        impl->getAnimation()->pauseAnimationGroup(reinterpret_cast<ArkUIContext*>(context), key));
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_ResumeAnimationGroup(ArkUI_ContextHandle context, const char* key)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(context, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "context is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(key, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "key is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(impl, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "impl is null");
    return static_cast<ArkUI_ErrorCode>(
        impl->getAnimation()->resumeAnimationGroup(reinterpret_cast<ArkUIContext*>(context), key));
}

ArkUI_ErrorCode OH_ArkUI_NativeModule_FinishAnimationGroup(
    ArkUI_ContextHandle context, const char* key, OH_ArkUI_AnimationFinishMode mode)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(context, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "context is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(key, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "key is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(impl, ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__, "impl is null");
    return static_cast<ArkUI_ErrorCode>(impl->getAnimation()->finishAnimationGroup(
        reinterpret_cast<ArkUIContext*>(context), key, static_cast<ArkUI_Int32>(mode)));
}
#ifdef __cplusplus
};
#endif