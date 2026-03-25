/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "base/geometry/animatable_dimension.h"
#include "core/animation/animator.h"
#include "core/animation/curve_animation.h"
#include "core/event/ace_event_helper.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {

AnimatableDimension::AnimatableDimension() = default;

AnimatableDimension::~AnimatableDimension() = default;

AnimatableDimension::AnimatableDimension(double value, DimensionUnit unit, const AnimationOption& option)
    : CalcDimension(value, unit), animationOption_(option)
{}

AnimatableDimension::AnimatableDimension(const std::string& value, DimensionUnit unit, const AnimationOption& option)
    : CalcDimension(value, unit), animationOption_(option)
{}

AnimatableDimension::AnimatableDimension(const Dimension& dimension, const AnimationOption& option)
    : CalcDimension(dimension), animationOption_(option)
{}

AnimatableDimension::AnimatableDimension(const CalcDimension& dimension, const AnimationOption& option)
    : CalcDimension(dimension), animationOption_(option)
{}

AnimatableDimension::AnimatableDimension(const AnimatableDimension& other) : CalcDimension(other.Value(), other.Unit())
{}

void AnimatableDimension::SetContextAndCallback(
    const WeakPtr<PipelineBase>& context, const RenderNodeAnimationCallback& callback)
{
    context_ = context;
    animationCallback_ = callback;
}

void AnimatableDimension::SetContextAndCallbackAfterFirstAssign(
    const WeakPtr<PipelineBase>& context, const RenderNodeAnimationCallback& callback)
{
    context_ = context;
    animationCallback_ = callback;
    isFirstAssign_ = false;
}

AnimatableDimension& AnimatableDimension::operator=(const Dimension& newDimension)
{
    ResetAnimatableDimension();
    Dimension& dimension = *this;
    dimension = newDimension;
    return *this;
}

AnimatableDimension& AnimatableDimension::operator=(const CalcDimension& newDimension)
{
    ResetAnimatableDimension();
    CalcDimension& dimension = *this;
    dimension = newDimension;
    return *this;
}

AnimatableDimension& AnimatableDimension::operator=(const AnimatableDimension& newDimension)
{
    return *this;
}

void AnimatableDimension::AnimateTo(double endValue) {}

void AnimatableDimension::ResetController() {}

void AnimatableDimension::OnAnimationCallback(double value) {}

void AnimatableDimension::MoveTo(double target) {}

void AnimatableDimension::ResetAnimatableDimension() {}

AnimatorStatus AnimatableDimension::GetAnimationStatus() const
{
    return AnimatorStatus::IDLE;
}
} // namespace OHOS::Ace
