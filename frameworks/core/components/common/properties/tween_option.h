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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TWEEN_OPTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TWEEN_OPTION_H

#include <map>

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_offset.h"
#include "core/animation/animation.h"
#include "core/animation/animation_pub.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/animation/property_animatable.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"

namespace OHOS::Ace {

enum class TweenOperation {
    NONE,
    PLAY,
    FINISH,
    PAUSE,
    CANCEL,
    REVERSE,
};

class TweenOption final {
public:
    void SetCurve(const RefPtr<Curve>& curve)
    {
        if (!curve) {
            LOGE("set curve failed. curve is null.");
            return;
        }
        curve_ = curve;
    }

    const RefPtr<Curve>& GetCurve() const
    {
        return curve_;
    }

    void SetDelay(int32_t delay)
    {
        delay_ = delay;
    }

    int32_t GetDelay() const
    {
        return delay_;
    }

    void SetIteration(int32_t iteration)
    {
        iteration_ = iteration;
    }

    int32_t GetIteration() const
    {
        return iteration_;
    }

    void SetFillMode(FillMode fillMode)
    {
        fillMode_ = fillMode;
    }

    FillMode GetFillMode() const
    {
        return fillMode_;
    }

    void SetDuration(int32_t duration)
    {
        duration_ = duration;
        changeDuration_ = true;
    }

    // Duration in millisecond.
    int32_t GetDuration() const
    {
        return duration_;
    }

    void SetAnimationDirection(AnimationDirection direction)
    {
        direction_ = direction;
    }

    AnimationDirection GetAnimationDirection() const
    {
        return direction_;
    }

    void SetTransformOrigin(const Dimension& originX, const Dimension& originY)
    {
        originX_ = originX;
        originY_ = originY;
        SetTransformOriginChanged(true);
    }

    const Dimension& GetTransformOriginX() const
    {
        return originX_;
    }

    const Dimension& GetTransformOriginY() const
    {
        return originY_;
    }

    void SetIsBackground(bool isBackground)
    {
        isBackground_ = isBackground;
    }

    bool GetIsBackground() const
    {
        return isBackground_;
    }

    void SetTranslateAnimations(AnimationType type, const RefPtr<Animation<DimensionOffset>>& transformOffsetAnimation)
    {
        if (!transformOffsetAnimation) {
            LOGE("input translateAnimation is null.");
            return;
        }
        transformOffsetAnimations_[type] = transformOffsetAnimation;
    }

    const std::unordered_map<AnimationType, RefPtr<Animation<DimensionOffset>>>& GetTranslateAnimations() const
    {
        return transformOffsetAnimations_;
    }

    void SetTransformFloatAnimation(AnimationType type, const RefPtr<Animation<float>>& transformFloatAnimation)
    {
        if (!transformFloatAnimation) {
            LOGE("input transformFloatAnimation is null.");
            return;
        }
        transformFloatAnimations_[type] = transformFloatAnimation;
    }

    double GetMaxScaleXY()
    {
        return maxScaleXY_;
    }

    void SetMaxScaleXY(double maxScaleXY)
    {
        maxScaleXY_ = maxScaleXY;
    }

    const std::unordered_map<AnimationType, RefPtr<Animation<float>>>& GetTransformFloatAnimation() const
    {
        return transformFloatAnimations_;
    }

    void SetOpacityAnimation(const RefPtr<Animation<float>>& opacityAnimation)
    {
        if (!opacityAnimation) {
            LOGE("input opacityAnimation is null.");
            return;
        }
        opacityAnimation_ = opacityAnimation;
    }

    const RefPtr<Animation<float>>& GetOpacityAnimation() const
    {
        return opacityAnimation_;
    }

    void SetColorAnimation(const RefPtr<Animation<Color>>& colorAnimation)
    {
        if (!colorAnimation) {
            LOGE("input colorAnimation is null.");
            return;
        }
        colorAnimation_ = colorAnimation;
    }

    RefPtr<Animation<Color>>& GetColorAnimation()
    {
        return colorAnimation_;
    }

    void SetBackgroundPositionAnimation(const RefPtr<Animation<BackgroundImagePosition>>& backgroundPositionAnimation)
    {
        if (!backgroundPositionAnimation) {
            LOGE("input backgroundPositionAnimation is null.");
            return;
        }
        backgroundPositionAnimation_ = backgroundPositionAnimation;
    }

    void SetPropertyAnimationFloat(PropertyAnimatableType property, const RefPtr<Animation<float>>& animation)
    {
        if (!animation) {
            LOGE("Set float property animation failed. animation is null. property: %{public}d", property);
            return;
        }
        LOGD("set float property animation. property: %{public}d", property);
        floatAnimationMap_[property] = animation;
    }

    PropertyAnimationFloatMap& GetFloatPropertyAnimation()
    {
        return floatAnimationMap_;
    }

    RefPtr<Animation<BackgroundImagePosition>>& GetBackgroundPositionAnimation()
    {
        return backgroundPositionAnimation_;
    }

    void SetTransformOriginChanged(bool change)
    {
        changeTransformOrigin_ = change;
    }

    bool HasTransformOriginChanged() const
    {
        return changeTransformOrigin_;
    }

    bool HasTransformOffsetChanged() const
    {
        return !transformOffsetAnimations_.empty();
    }

    bool HasTransformFloatChanged() const
    {
        return !transformFloatAnimations_.empty();
    }

    bool HasDurationChanged() const
    {
        return changeDuration_;
    }

    bool IsValid() const
    {
        return (opacityAnimation_ || colorAnimation_ || backgroundPositionAnimation_ || !floatAnimationMap_.empty() ||
                !transformFloatAnimations_.empty() || !transformOffsetAnimations_.empty());
    }

    void SkipAllPendingAnimation()
    {
        if (opacityAnimation_) {
            opacityAnimation_->SetSkipAnimation(true);
        }

        if (colorAnimation_) {
            colorAnimation_->SetSkipAnimation(true);
        }

        if (backgroundPositionAnimation_) {
            backgroundPositionAnimation_->SetSkipAnimation(true);
        }

        for (auto&& [type, animation] : floatAnimationMap_) {
            if (animation) {
                animation->SetSkipAnimation(true);
            }
        }
        for (auto&& [type, animation] : transformOffsetAnimations_) {
            if (animation) {
                animation->SetSkipAnimation(true);
            }
        }
        for (auto&& [type, animation] : transformFloatAnimations_) {
            if (animation) {
                animation->SetSkipAnimation(true);
            }
        }
    }

    void ClearListeners()
    {
        if (opacityAnimation_) {
            opacityAnimation_->ClearListeners();
        }
        if (colorAnimation_) {
            colorAnimation_->ClearListeners();
        }
        if (backgroundPositionAnimation_) {
            backgroundPositionAnimation_->ClearListeners();
        }

        ClearListeners(floatAnimationMap_);

        for (auto&& [type, animation] : transformOffsetAnimations_) {
            if (animation) {
                animation->ClearListeners();
            }
        }
        for (auto&& [type, animation] : transformFloatAnimations_) {
            if (animation) {
                animation->ClearListeners();
            }
        }
    }

private:
    template<class T, class U>
    void ClearListeners(const std::map<T, RefPtr<Animation<U>>>& animations)
    {
        for (auto&& [type, animation] : animations) {
            if (animation) {
                animation->ClearListeners();
            }
        }
    }

private:
    FillMode fillMode_ = FillMode::NONE;
    AnimationDirection direction_ = AnimationDirection::NORMAL;
    RefPtr<Curve> curve_; // use animation's curve as default.
    RefPtr<Animation<float>> opacityAnimation_;
    RefPtr<Animation<Color>> colorAnimation_;
    RefPtr<Animation<BackgroundImagePosition>> backgroundPositionAnimation_;
    PropertyAnimationFloatMap floatAnimationMap_;
    std::unordered_map<AnimationType, RefPtr<Animation<DimensionOffset>>> transformOffsetAnimations_;
    std::unordered_map<AnimationType, RefPtr<Animation<float>>> transformFloatAnimations_;

    int32_t duration_ = 0;
    int32_t delay_ = 0;
    int32_t iteration_ = 1;
    bool isBackground_ = true;
    bool changeTransformOrigin_ = false;
    bool changeDuration_ = false;
    double maxScaleXY_ = -1.0;
    Dimension originX_;
    Dimension originY_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_TWEEN_OPTION_H
