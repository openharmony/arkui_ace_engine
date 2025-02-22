/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_PROPERTIES_ANIMATABLE_COLOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_PROPERTIES_ANIMATABLE_COLOR_H

#include "base/utils/macros.h"
#include "core/animation/animator.h"
#include "core/animation/curve_animation.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace {

class PipelineContext;

using RenderNodeAnimationCallback = std::function<void()>;

/*
 * AnimatableColor is a Color with AnimationOption and Animator.
 */
class AnimatableColor final : public Color {
public:
    ACE_FORCE_EXPORT AnimatableColor();
    explicit AnimatableColor(uint32_t value, const AnimationOption& option = AnimationOption());

    explicit AnimatableColor(const Color& color, const AnimationOption& option = AnimationOption());
    ACE_FORCE_EXPORT ~AnimatableColor();

    void SetContextAndCallback(const WeakPtr<PipelineContext>& context, const RenderNodeAnimationCallback& callback);

    const AnimationOption& GetAnimationOption() const
    {
        return animationOption_;
    }

    void SetAnimationOption(const AnimationOption& option)
    {
        animationOption_ = option;
    }

    AnimatableColor& operator=(const AnimatableColor& newColor);

private:
    void AnimateTo(uint32_t endValue);

    void ResetController();

    void OnAnimationCallback(const Color& color);

private:
    bool isFirstAssign_ = true;
    AnimationOption animationOption_;
    RefPtr<Animator> animationController_;
    WeakPtr<PipelineContext> context_;
    RenderNodeAnimationCallback animationCallback_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PROPERTIES_ANIMATABLE_COLOR_H
