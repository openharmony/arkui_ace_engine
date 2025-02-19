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
#include <vector>

#include "native_animate.h"
#include "native_type.h"

#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

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
    ArkUI_CurveHandle iCurve;
};

typedef enum {
    ARKUI_CURVE_TYPE_BASE = 0,
    ARKUI_CURVE_TYPE_STEPS,
    ARKUI_CURVE_TYPE_CUBIC_BEZIER,
    ARKUI_CURVE_TYPE_SPRING,
    ARKUI_CURVE_TYPE_SPRING_MOTION,
    ARKUI_CURVE_TYPE_RESPONSIVE_SPRING_MOTION,
    ARKUI_CURVE_TYPE_INTERPOLATING_SPRING,
    ARKUI_CURVE_TYPE_CUSTOM,
} ArkUI_CurveType;

struct ArkUI_Curve {
    ArkUI_CurveType type;
    ArkUICurveHandle curve;
    ArkUI_AnimationCurve baseCurveType;
};

struct ArkUI_KeyframeState {
    int32_t duration;
    ArkUI_CurveHandle curve;
    void (*event)(void* userData);
    void* userData;
};

struct ArkUI_KeyframeAnimateOption {
    int32_t delay;
    int32_t iterations;
    void (*onFinish)(void* userData);
    void* userData;
    std::vector<ArkUI_KeyframeState> keyframes;
    ArkUI_ExpectedFrameRateRange* expectedFrameRateRange;
};

struct ArkUI_Keyframe {
    float keyTime;
    float keyValue;
    ArkUI_CurveHandle curve;
};
struct ArkUI_AnimatorOption {
    int32_t duration;
    int32_t delay;
    int32_t iterations;
    ArkUI_AnimationFillMode fill;
    ArkUI_AnimationDirection direction;
    float begin;
    float end;
    ArkUI_CurveHandle easing;
    ArkUI_ExpectedFrameRateRange* expectedFrameRateRange;
    std::vector<ArkUI_Keyframe> keyframes;
    void (*onFrame)(ArkUI_AnimatorOnFrameEvent* event);
    void* frameUserData;
    void (*onFinish)(ArkUI_AnimatorEvent* event);
    void* finishUserData;
    void (*onCancel)(ArkUI_AnimatorEvent* event);
    void* cancelUserData;
    void (*onRepeat)(ArkUI_AnimatorEvent* event);
    void* repeatUserData;
};

struct ArkUI_Animator {
    ArkUIAnimatorHandle animator;
    ArkUI_AnimatorOption* option;
    ArkUIAnimatorOption* animatorOption;
};
#ifdef __cplusplus
};
#endif

namespace OHOS::Ace::AnimateModel {

ArkUI_CurveHandle InitCurve(ArkUI_AnimationCurve animationCurve);
ArkUI_CurveHandle StepsCurve(int32_t count, bool end);
ArkUI_CurveHandle CubicBezierCurve(float x1, float y1, float x2, float y2);
ArkUI_CurveHandle SpringCurve(float velocity, float mass, float stiffness, float damping);
ArkUI_CurveHandle SpringMotion(float response, float dampingFraction, float overlapDuration);
ArkUI_CurveHandle ResponsiveSpringMotion(float response, float dampingFraction, float overlapDuration);
ArkUI_CurveHandle InterpolatingSpring(float velocity, float mass, float stiffness, float damping);
ArkUI_CurveHandle CustomCurve(void* userData, float (*interpolate)(float fraction, void* userdata));
void DisposeCurve(ArkUI_CurveHandle curveHandle);

int32_t AnimateTo(ArkUI_ContextHandle context, ArkUI_AnimateOption* option, ArkUI_ContextCallback* update,
    ArkUI_AnimateCompleteCallback* complete);

int32_t KeyframeAnimateTo(ArkUI_ContextHandle context, ArkUI_KeyframeAnimateOption* option);

ArkUI_AnimatorHandle CreateAnimator(ArkUI_ContextHandle context, ArkUI_AnimatorOption* option);
void DisposeAnimator(ArkUI_AnimatorHandle animatorHandle);

int32_t AnimatorReset(ArkUI_AnimatorHandle animatorHandle, ArkUI_AnimatorOption* option);
int32_t AnimatorPlay(ArkUI_AnimatorHandle animatorHandle);
int32_t AnimatorFinish(ArkUI_AnimatorHandle animatorHandle);
int32_t AnimatorPause(ArkUI_AnimatorHandle animatorHandle);
int32_t AnimatorCancel(ArkUI_AnimatorHandle animatorHandle);
int32_t AnimatorReverse(ArkUI_AnimatorHandle animatorHandle);
}; // namespace OHOS::Ace::AnimateModel
#endif