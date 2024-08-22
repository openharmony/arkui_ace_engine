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
#include "node/node_model.h"

#include "base/error/error_code.h"
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

    for (int32_t i = 0; i < size; ++i) {
        //duration default 1000
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
    delete option;
}

int32_t OH_ArkUI_KeyframeAnimateOption_SetDelay(ArkUI_KeyframeAnimateOption* option, int32_t value)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    option->delay = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_KeyframeAnimateOption_SetIterations(ArkUI_KeyframeAnimateOption* option, int32_t value)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    //取值范围：[-1, +∞)
    if (value < -1) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->iterations = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_KeyframeAnimateOption_RegisterOnFinishCallback(
    ArkUI_KeyframeAnimateOption* option, void* userData, void (*onFinish)(void* userData))
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    option->onFinish = onFinish;
    option->userData = userData;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_KeyframeAnimateOption_SetDuration(ArkUI_KeyframeAnimateOption* option, int32_t value, int32_t index)
{
    if (option == nullptr || index < 0 || index >= static_cast<int32_t>(option->keyframes.size())) {
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
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!value || !value->curve) {
        option->keyframes[index].curve = nullptr;
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (value->type == ARKUI_CURVE_TYPE_SPRING_MOTION || value->type == ARKUI_CURVE_TYPE_RESPONSIVE_SPRING_MOTION ||
        value->type == ARKUI_CURVE_TYPE_INTERPOLATING_SPRING) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->keyframes[index].curve = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_KeyframeAnimateOption_RegisterOnEventCallback(
    ArkUI_KeyframeAnimateOption* option, void* userData, void (*event)(void* userData), int32_t index)
{
    if (option == nullptr || index < 0 || index >= static_cast<int32_t>(option->keyframes.size())) {
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
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (value < 0) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->duration = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetDelay(ArkUI_AnimatorOption* option, int32_t value)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    option->delay = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetIterations(ArkUI_AnimatorOption* option, int32_t value)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (value < -1) {
        value = 1;
    }
    option->iterations = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetFill(ArkUI_AnimatorOption* option, ArkUI_AnimationFillMode value)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (value > ARKUI_ANIMATION_FILL_MODE_BOTH || value < ARKUI_ANIMATION_FILL_MODE_NONE) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->fill = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetDirection(ArkUI_AnimatorOption* option, ArkUI_AnimationDirection value)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (value > ARKUI_ANIMATION_DIRECTION_ALTERNATE_REVERSE || value < ARKUI_ANIMATION_DIRECTION_NORMAL) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->direction = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (value) {
        if (value->type == ARKUI_CURVE_TYPE_SPRING || value->type == ARKUI_CURVE_TYPE_SPRING_MOTION ||
            value->type == ARKUI_CURVE_TYPE_RESPONSIVE_SPRING_MOTION ||
            value->type == ARKUI_CURVE_TYPE_INTERPOLATING_SPRING || value->type == ARKUI_CURVE_TYPE_CUSTOM) {
            option->easing = nullptr;
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
    }

    option->easing = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetBegin(ArkUI_AnimatorOption* option, float value)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (option->keyframes.size() > 0) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->begin = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetEnd(ArkUI_AnimatorOption* option, float value)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (option->keyframes.size() > 0) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->end = value;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetExpectedFrameRateRange(
    ArkUI_AnimatorOption* option, ArkUI_ExpectedFrameRateRange* value)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(value, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    option->expectedFrameRateRange = new ArkUI_ExpectedFrameRateRange { value->min, value->max, value->expected };
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_SetKeyframe(ArkUI_AnimatorOption* option, float time, float value, int32_t index)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (time < 0 || time > 1) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (index >= 0 && static_cast<size_t>(index) < option->keyframes.size()) {
        option->keyframes[index].keyTime = time;
        option->keyframes[index].keyValue = value;
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }
    return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
}

int32_t OH_ArkUI_AnimatorOption_SetKeyframeCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value, int32_t index)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (value) {
        if (value->type == ARKUI_CURVE_TYPE_SPRING || value->type == ARKUI_CURVE_TYPE_SPRING_MOTION ||
            value->type == ARKUI_CURVE_TYPE_RESPONSIVE_SPRING_MOTION ||
            value->type == ARKUI_CURVE_TYPE_INTERPOLATING_SPRING || value->type == ARKUI_CURVE_TYPE_CUSTOM) {
            option->keyframes[index].curve = nullptr;
            return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
        }
    }

    if (index >= 0 && static_cast<size_t>(index) < option->keyframes.size()) {
        option->keyframes[index].curve = value;
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }
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

int32_t OH_ArkUI_AnimatorOption_RegisterOnFrameCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorOnFrameEvent* event))
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !option || !callback) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->onFrame = callback;
    option->frameUserData = userData;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_RegisterOnFinishCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event))
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !option || !callback) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    option->onFinish = callback;
    option->finishUserData = userData;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_RegisterOnCancelCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event))
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !option || !callback) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    option->onCancel = callback;
    option->cancelUserData = userData;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_AnimatorOption_RegisterOnRepeatCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event))
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !option || !callback) {
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

#ifdef __cplusplus
};
#endif