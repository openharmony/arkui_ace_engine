/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_ANIMATABLE_DIMENSION_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_ANIMATABLE_DIMENSION_H

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "core/animation/evaluator.h"
#include "core/components/common/properties/animation_option.h"

namespace OHOS::Ace {

using RenderNodeAnimationCallback = std::function<void()>;

class Animator;

enum class AnimatorStatus {
    IDLE,    // when animation not start or been cancel.
    RUNNING, // play in reverse / forward direction.
    PAUSED,  // paused by call Pause API.
    STOPPED, // stopped by call Finish/Stop API or has played to the end.
};

/*
 * AnimatableDimension is a Dimension with AnimationOption and Animator.
 */
class ACE_FORCE_EXPORT AnimatableDimension : public CalcDimension {
public:
    AnimatableDimension();
    ~AnimatableDimension();

    explicit AnimatableDimension(
        double value, DimensionUnit unit = DimensionUnit::PX, const AnimationOption& option = AnimationOption());

    explicit AnimatableDimension(const std::string& value, DimensionUnit unit = DimensionUnit::CALC,
        const AnimationOption& option = AnimationOption());

    explicit AnimatableDimension(const Dimension& dimension, const AnimationOption& option = AnimationOption());

    explicit AnimatableDimension(const CalcDimension& dimension, const AnimationOption& option = AnimationOption());

    AnimatableDimension(const AnimatableDimension& other);
    void SetContextAndCallback(const WeakPtr<PipelineBase>& context, const RenderNodeAnimationCallback& callback)
    {
        context_ = context;
        animationCallback_ = callback;
    }

    void SetContextAndCallbackAfterFirstAssign(
        const WeakPtr<PipelineBase>& context, const RenderNodeAnimationCallback& callback)
    {
        context_ = context;
        animationCallback_ = callback;
        isFirstAssign_ = false;
    }

    const AnimationOption& GetAnimationOption() const
    {
        return animationOption_;
    }

    void SetAnimationOption(const AnimationOption& option)
    {
        animationOption_ = option;
    }

    void SetAnimationStopCallback(const RenderNodeAnimationCallback& callback)
    {
        stopCallback_ = callback;
    }

    AnimatorStatus GetAnimationStatus() const;

    void SetEvaluator(const RefPtr<Evaluator<double>>& evaluator)
    {
        evaluator_ = evaluator;
    }

    AnimatableDimension& operator=(const Dimension& newDimension);

    AnimatableDimension& operator=(const CalcDimension& newDimension);

    AnimatableDimension& operator=(const AnimatableDimension& newDimension);

    void MoveTo(double target);

private:
    void AnimateTo(double endValue);
    void ResetController();
    void OnAnimationCallback(double value);
    void ResetAnimatableDimension();

private:
    bool isFirstAssign_ = true;
    AnimationOption animationOption_;
    RefPtr<Animator> animationController_;
    WeakPtr<PipelineBase> context_;
    RenderNodeAnimationCallback animationCallback_;
    RenderNodeAnimationCallback stopCallback_;
    RefPtr<Evaluator<double>> evaluator_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_ANIMATABLE_DIMENSION_H
