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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_MODIFIER_H

#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "core/animation/spring_curve.h"
#include "core/common/container.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/radio/radio_modifier.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paint_wrapper.h"
namespace OHOS::Ace::NG {
class CheckBoxModifier : public ContentModifier {
    DECLARE_ACE_TYPE(CheckBoxModifier, ContentModifier);

public:
    CheckBoxModifier(bool isSelect, const Color& boardColor, const Color& checkColor, const Color& borderColor,
        const Color& shadowColor);
    ~CheckBoxModifier() override = default;

    void onDraw(DrawingContext& context) override
    {
        RSCanvas canvas = context.canvas;
        PaintCheckBox(canvas, offset_, size_);
    }

    void UpdateAnimatableProperty()
    {
        AnimationOption option = AnimationOption();
        option.SetDuration(hoverDuration_);
        option.SetCurve(Curves::FRICTION);
        AnimationUtils::Animate(option, [&]() {
            animateHoverColor_->Set(isHover_->Get() ? LinearColor(hoverColor_) : LinearColor(Color::TRANSPARENT));
        });

        option.SetDuration(colorAnimationDuration_);
        option.SetCurve(Curves::FAST_OUT_SLOW_IN);
        AnimationUtils::Animate(option, [&]() {
            animatableBoardColor_->Set(
                isSelect_->Get() ? LinearColor(userActiveColor_) : LinearColor(inactivePointColor_));
            animatableCheckColor_->Set(
                isSelect_->Get() ? LinearColor(pointColor_) : LinearColor(pointColor_.BlendOpacity(0)));
            animatableBorderColor_->Set(
                isSelect_->Get() ? LinearColor(Color::TRANSPARENT) : LinearColor(inactiveColor_));
            animatableShadowColor_->Set(
                isSelect_->Get() ? LinearColor(shadowColor_) : LinearColor(shadowColor_.BlendOpacity(0)));
        });
    }

    void InitializeParam();
    void PaintCheckBox(RSCanvas& canvas, const OffsetF& paintOffset, const SizeF& paintSize) const;
    void DrawHoverBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const;

    void DrawBorder(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const;
    void DrawBackboard(RSCanvas& canvas, const OffsetF& origin, RSBrush& brush, const SizeF& paintSize) const;
    void DrawCheck(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, RSPen& shadowPen, const SizeF& paintSize) const;

    void SetUserActiveColor(const Color& color)
    {
        userActiveColor_ = color;
        animatableBoardColor_->Set(isSelect_->Get() ? LinearColor(userActiveColor_) : LinearColor(inactivePointColor_));
    }

    void SetInActiveColor(const Color& color)
    {
        inactiveColor_ = color;
        animatableBorderColor_->Set(isSelect_->Get() ? LinearColor(Color::TRANSPARENT) : LinearColor(inactiveColor_));
    }

    void SetPointColor(const Color& color)
    {
        pointColor_ = color;
        animatableCheckColor_->Set(isSelect_->Get() ? LinearColor(pointColor_) : LinearColor(Color::TRANSPARENT));
    }

    void SetEnabled(bool enabled)
    {
        enabled_ = enabled;
    }

    void SetIsTouch(bool isTouch)
    {
        isTouch_ = isTouch;
    }

    void SetIsSelect(bool isSelect)
    {
        if (!isSelect_ || (isSelect_->Get() == isSelect)) {
            return;
        }
        isSelect_->Set(isSelect);
        UpdateAnimatableProperty();
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
        offset_ = offset;
    }

    void SetSize(SizeF& size)
    {
        size_ = size;
    }

    void SetUIStatus(UIStatus& uiStatus)
    {
        uiStatus_ = uiStatus;
    }

    void SetIsHover(bool isHover)
    {
        if (isHover_) {
            isHover_->Set(isHover);
        }
    }

    void SetStrokeWidth(float value)
    {
        if (checkStroke_) {
            checkStroke_->Set(value);
        }
    }

    void SetStrokeSize(float value)
    {
        if (strokeSize_) {
            strokeSize_->Set(value);
        }
    }

private:
    float borderWidth_ = 0.0f;
    float borderRadius_ = 0.0f;
    Color pointColor_;
    Color activeColor_;
    Color inactiveColor_;
    Color shadowColor_;
    Color clickEffectColor_;
    Color hoverColor_;
    Color inactivePointColor_;
    Color userActiveColor_;
    Dimension hoverRadius_;
    Dimension hotZoneHorizontalPadding_;
    Dimension hotZoneVerticalPadding_;
    Dimension shadowWidth_;
    float hoverDuration_ = 0.0f;
    float hoverToTouchDuration_ = 0.0f;
    float touchDuration_ = 0.0f;
    float colorAnimationDuration_ = 0.0f;

    bool enabled_ = true;
    bool isTouch_ = false;
    UIStatus uiStatus_ = UIStatus::UNSELECTED;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    OffsetF offset_;
    SizeF size_;

    RefPtr<AnimatablePropertyColor> animatableBoardColor_;
    RefPtr<AnimatablePropertyColor> animatableCheckColor_;
    RefPtr<AnimatablePropertyColor> animatableBorderColor_;
    RefPtr<AnimatablePropertyColor> animatableShadowColor_;
    RefPtr<AnimatablePropertyColor> animateHoverColor_;
    RefPtr<AnimatablePropertyFloat> checkStroke_;
    RefPtr<AnimatablePropertyFloat> strokeSize_;
    RefPtr<PropertyBool> isSelect_;
    RefPtr<PropertyBool> isHover_;

    ACE_DISALLOW_COPY_AND_MOVE(CheckBoxModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_MODIFIER_H