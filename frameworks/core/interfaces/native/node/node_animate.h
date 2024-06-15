/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NODE_ANIMATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NODE_ANIMATE_H

#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/node_utils.h"

namespace OHOS::Ace::NG::ViewAnimate {

void AnimateToInner(AnimationOption& option, const std::function<void()>& animateToFunc,
    const std::function<void()>& onFinishFunc, bool immediately);

void AnimateTo(ArkUIContext* context, ArkUIAnimateOption option, void (*event)(void* userData), void* user);

void KeyframeAnimateTo(ArkUIContext* context, ArkUIKeyframeAnimateOption* animateOption);
ArkUIAnimatorHandle CreateAnimator(ArkUIContext* context, ArkUIAnimatorOption* option);
void DisposeAnimator(ArkUIAnimatorHandle animatorHandle);

int32_t AnimatorReset(ArkUIAnimatorHandle animatorHandle, ArkUIAnimatorOption* option);
int32_t AnimatorPlay(ArkUIAnimatorHandle animatorHandle);
int32_t AnimatorFinish(ArkUIAnimatorHandle animatorHandle);
int32_t AnimatorPause(ArkUIAnimatorHandle animatorHandle);
int32_t AnimatorCancel(ArkUIAnimatorHandle animatorHandle);
int32_t AnimatorReverse(ArkUIAnimatorHandle animatorHandle);

ArkUICurveHandle CreateCurve(ArkUI_Int32 curve);
ArkUICurveHandle CreateStepsCurve(ArkUI_Int32 count, ArkUI_Bool end);
ArkUICurveHandle CreateCubicBezierCurve(ArkUI_Float32 x1, ArkUI_Float32 y1, ArkUI_Float32 x2, ArkUI_Float32 y2);
ArkUICurveHandle CreateSpringCurve(
    ArkUI_Float32 velocity, ArkUI_Float32 mass, ArkUI_Float32 stiffness, ArkUI_Float32 damping);
ArkUICurveHandle CreateSpringMotion(
    ArkUI_Float32 response, ArkUI_Float32 dampingFraction, ArkUI_Float32 overlapDuration);
ArkUICurveHandle CreateResponsiveSpringMotion(
    ArkUI_Float32 response, ArkUI_Float32 dampingFraction, ArkUI_Float32 overlapDuration);
ArkUICurveHandle CreateInterpolatingSpring(
    ArkUI_Float32 velocity, ArkUI_Float32 mass, ArkUI_Float32 stiffness, ArkUI_Float32 damping);
ArkUICurveHandle CreateCustomCurve(
    ArkUI_Float32 (*interpolate)(ArkUI_Float32 fraction, void* userData), void* userData);
void DisposeCurve(ArkUICurveHandle curve);
} // namespace OHOS::Ace::NG::ViewAnimate

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NODE_ANIMATE_H
