/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWITCH_SWITCH_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWITCH_SWITCH_MODIFIER_H

#include <algorithm>
#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "core/animation/spring_curve.h"
#include "core/common/container.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/radio/radio_modifier.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/paint_wrapper.h"
namespace OHOS::Ace::NG {
class SwitchModifier : public ContentModifier {
    DECLARE_ACE_TYPE(SwitchModifier, ContentModifier);

public:
    SwitchModifier(const SizeF& size, const OffsetF& offset, float pointOffset, bool isSelect,
        const Color& boardColor, const Color& pointColor, float dragOffsetX);
    ~SwitchModifier() override = default;

    void onDraw(DrawingContext& context) override
    {
        if (useContentModifier_->Get()) {
            return;
        }
        RSCanvas& canvas = context.canvas;
        PaintSwitch(canvas, offset_->Get(), size_->Get());
    }

    void UpdateAnimatableProperty()
    {
        SetSwitchBoardColor();
        if (!actualSize_.IsPositive()) {
            return;
        }
        bool isRtl = direction_ == TextDirection::AUTO ? AceApplicationInfo::GetInstance().IsRightToLeft()
                                                       : direction_ == TextDirection::RTL;
        auto offsetNotRtl = GreatOrEqual(actualSize_.Width(), actualSize_.Height())
                                ? (isSelect_->Get() ? actualSize_.Width() - actualSize_.Height() : 0.0f)
                                : (isSelect_->Get() ? actualSize_.Width() - actualTrackRadius_ : actualTrackRadius_);
        auto offsetIsRtl = GreatOrEqual(actualSize_.Width(), actualSize_.Height())
                               ? (isSelect_->Get() ? 0.0f : actualSize_.Width() - actualSize_.Height())
                               : (isSelect_->Get() ? actualTrackRadius_ : actualSize_.Width() - actualTrackRadius_);
        if (!isCancelAnimation_ || !isFocusOrBlur_) {
            AnimationOption colorOption = AnimationOption();
            colorOption.SetDuration(colorAnimationDuration_);
            colorOption.SetCurve(Curves::FAST_OUT_SLOW_IN);
            AnimationUtils::Animate(colorOption, [&]() {
                animatableBoardColor_->Set(isSelect_->Get() ?
                    LinearColor(userActiveColor_) : LinearColor(inactiveColor_));
            });
        }
        AnimationOption pointOption = AnimationOption();
        pointOption.SetDuration(pointAnimationDuration_);
        pointOption.SetCurve(Curves::FAST_OUT_SLOW_IN);
        float newPointOffset = 0.0f;
        if (!isDragEvent_) {
            if (isRtl) {
                newPointOffset = offsetIsRtl;
            } else {
                newPointOffset = offsetNotRtl;
            }
        } else {
            if (GreatOrEqual(actualSize_.Width(), actualSize_.Height())) {
                newPointOffset = std::clamp(
                    dragOffsetX_->Get() - offset_->Get().GetX(), 0.0f, actualSize_.Width() - actualSize_.Height());
            } else {
                newPointOffset = std::clamp(dragOffsetX_->Get() - offset_->Get().GetX(), actualTrackRadius_,
                    actualSize_.Width() - actualTrackRadius_);
            }
        }
        AnimationUtils::Animate(pointOption, [&]() { pointOffset_->Set(newPointOffset); });
    }

    void SetSwitchBoardColor()
    {
        switch (touchHoverType_) {
            case TouchHoverAnimationType::HOVER:
                SetBoardColor(LinearColor(hoverColor_), hoverDuration_, Curves::FRICTION);
                break;
            case TouchHoverAnimationType::PRESS_TO_HOVER:
                SetBoardColor(LinearColor(hoverColor_), hoverToTouchDuration_, Curves::SHARP);
                break;
            case TouchHoverAnimationType::NONE:
                SetBoardColor(LinearColor(hoverColor_.BlendOpacity(0)), hoverDuration_, Curves::FRICTION);
                break;
            case TouchHoverAnimationType::HOVER_TO_PRESS:
                SetBoardColor(LinearColor(clickEffectColor_), hoverToTouchDuration_, Curves::SHARP);
                break;
            case TouchHoverAnimationType::PRESS:
                SetBoardColor(LinearColor(clickEffectColor_), hoverDuration_, Curves::FRICTION);
                break;
            default:
                break;
        }
    }

    void SetBoardColor(LinearColor color, int32_t duratuion, const RefPtr<CubicCurve>& curve)
    {
        if (animateTouchHoverColor_) {
            AnimationOption option = AnimationOption();
            option.SetDuration(duratuion);
            option.SetCurve(curve);
            AnimationUtils::Animate(option, [&]() { animateTouchHoverColor_->Set(color); });
        }
    }

    void SetBoardColor(Color color)
    {
        if (animatableBoardColor_) {
            animatableBoardColor_->Set(LinearColor(color));
        }
    }

    void InitializeParam(int32_t themeScopeId);
    void PaintSwitch(RSCanvas& canvas, const OffsetF& contentOffset, const SizeF& contentSize);
    float GetSwitchWidth(const SizeF& contentSize) const;
    float CalcActualWidth(float width, float height, double actualGap, double defaultWidthGap);
    void DrawFocusBoard(RSCanvas& canvas, const OffsetF& offset);
    void DrawRectCircle(RSCanvas& canvas, const OffsetF& contentOffset,
        const SizeF& contentSize, const double& actualGap);

    void SetUserActiveColor(const Color& color)
    {
        userActiveColor_ = color;
        animatableBoardColor_->Set(isSelect_->Get() ? LinearColor(userActiveColor_) : LinearColor(inactiveColor_));
    }

    void SetPointColor(const Color& color)
    {
        hasPointColor_ = true;
        animatePointColor_->Set(LinearColor(color));
    }

    void SetIsHover(bool isHover)
    {
        if (isHover_) {
            isHover_->Set(isHover);
        }
    }

    void SetIsSelect(bool isSelect)
    {
        if (isSelect_) {
            isSelect_->Set(isSelect);
        }
    }

    void SetIsFocused(bool isFocused)
    {
        if (isFocused_) {
            isFocused_->Set(isFocused);
        }
    }

    void SetIsOn(bool isOn)
    {
        if (isOn_) {
            isOn_->Set(isOn);
        }
    }

    void SetFocusPointColor(Color color)
    {
        pointColor_ = color;
    }

    void SetHotZoneOffset(OffsetF& hotZoneOffset)
    {
        hotZoneOffset_ = hotZoneOffset;
    }

    void SetHotZoneSize(SizeF& hotZoneSize)
    {
        hotZoneSize_ = hotZoneSize;
    }

    void SetOffset(OffsetF& offset)
    {
        if (offset_) {
            offset_->Set(offset);
        }
    }

    void SetUseContentModifier(bool useContentModifier)
    {
        if (useContentModifier_) {
            useContentModifier_->Set(useContentModifier);
        }
    }

    void SetSize(SizeF& size)
    {
        actualSize_ = size;
        if (size_) {
            size_->Set(size);
        }
    }

    void SetDragOffsetX(float dragOffsetX)
    {
        if (dragOffsetX_) {
            dragOffsetX_->Set(dragOffsetX);
        }
    }

    void SetPointOffset(float pointOffset)
    {
        if (pointOffset_) {
            pointOffset_->Set(pointOffset);
        }
    }

    void SetTouchHoverAnimationType(const TouchHoverAnimationType touchHoverType)
    {
        touchHoverType_ = touchHoverType;
    }

    void SetIsDragEvent(bool isDragEvent)
    {
        isDragEvent_ = isDragEvent;
    }

    void SetShowHoverEffect(bool showHoverEffect)
    {
        showHoverEffect_ = showHoverEffect;
    }

    void SetDirection(TextDirection direction)
    {
        if (direction_ != direction) {
            direction_ = direction;
            isFirstCreated_ = true;
        }
    }

    void SetPointRadius(float pointRadius)
    {
        animatePointRadius_->Set(pointRadius);
    }

    float GetPointRadius()
    {
        return pointRadius_;
    }

    void SetInactiveColor(const Color& color)
    {
        inactiveColor_ = color;
    }

    void SetTrackRadius(float borderRadius)
    {
        animateTrackRadius_->Set(borderRadius);
    }

    float GetTrackRadius()
    {
        return actualTrackRadius_;
    }

    void SetActualTrackRadius(float borderRadius)
    {
        actualTrackRadius_ = borderRadius;
    }

    void SetIsFocusOrBlur(bool isFocusOrBlur)
    {
        isFocusOrBlur_ = isFocusOrBlur;
    }

private:
    float actualWidth_ = 0.0f;
    float actualHeight_ = 0.0f;
    float pointRadius_ = 0.0f;
    const Dimension radiusGap_ = 2.0_vp;
    Color clickEffectColor_;
    Color hoverColor_;
    Color activeColor_;
    Color inactiveColor_;
    Color userActiveColor_;
    Color pointColorUnchecked_;
    Color pointColor_;
    Color focusBoardColor_;
    Dimension hoverRadius_ = 8.0_vp;
    Dimension focusRadius_ = 8.0_vp;
    bool isUseDiffPointColor_ = false;
    bool isCancelAnimation_ = false;
    float hoverDuration_ = 0.0f;
    float hoverToTouchDuration_ = 0.0f;
    float touchDuration_ = 0.0f;
    float colorAnimationDuration_ = 0.0f;
    float pointAnimationDuration_ = 0.0f;
    bool isDragEvent_ = false;
    bool isFirstCreated_ = true;
    bool showHoverEffect_ = true;
    bool isFocusOrBlur_ = false;
    float actualTrackRadius_ = 0.0f;

    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    SizeF actualSize_;
    TouchHoverAnimationType touchHoverType_ = TouchHoverAnimationType::NONE;
    TextDirection direction_ = TextDirection::AUTO;

    RefPtr<AnimatablePropertyColor> animatableBoardColor_;
    RefPtr<AnimatablePropertyColor> animateTouchHoverColor_;
    RefPtr<AnimatablePropertyColor> animatePointColor_;
    RefPtr<AnimatablePropertyFloat> pointOffset_;
    RefPtr<PropertyFloat> dragOffsetX_;
    RefPtr<PropertyBool> isSelect_;
    RefPtr<PropertyBool> isHover_;
    RefPtr<PropertyBool> isFocused_;
    RefPtr<PropertyBool> isOn_;
    bool hasPointColor_ = false;
    RefPtr<AnimatablePropertyOffsetF> offset_;
    RefPtr<AnimatablePropertySizeF> size_;
    RefPtr<PropertyBool> useContentModifier_;
    RefPtr<PropertyFloat> animatePointRadius_;
    RefPtr<PropertyFloat> animateTrackRadius_;

    ACE_DISALLOW_COPY_AND_MOVE(SwitchModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWITCH_SWITCH_MODIFIER_H
