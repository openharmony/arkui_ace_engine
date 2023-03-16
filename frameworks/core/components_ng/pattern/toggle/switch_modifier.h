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
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paint_wrapper.h"
namespace OHOS::Ace::NG {
class SwitchModifier : public ContentModifier {
    DECLARE_ACE_TYPE(SwitchModifier, ContentModifier);

public:
    SwitchModifier(bool isSelect, const Color& boardColor, float mainDelta);
    ~SwitchModifier() override = default;

    void onDraw(DrawingContext& context) override
    {
        RSCanvas canvas = context.canvas;
        PaintSwitch(canvas, offset_->Get(), size_->Get());
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
            animatableBoardColor_->Set(isSelect_->Get() ? LinearColor(userActiveColor_) : LinearColor(inactiveColor_));
        });
    }

    void InitializeParam();
    void PaintSwitch(RSCanvas& canvas, const OffsetF& contentOffset, const SizeF& contentSize);
    void DrawHoverBoard(RSCanvas& canvas, const OffsetF& offset) const;
    float GetSwitchWidth(const SizeF& contentSize) const;

    void SetUserActiveColor(const Color& color)
    {
        userActiveColor_ = color;
    }

    void SetUserPointColor(const Color& color)
    {
        userPointColor_ = color;
    }

    void SetEnabled(bool enabled)
    {
        if (enabled_) {
            enabled_->Set(enabled);
        }
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

    void SetSize(SizeF& size)
    {
        if (size_) {
            size_->Set(size);
        }
    }

    void SetMainDelta(float mainDelta)
    {
        if (mainDelta_) {
            mainDelta_->Set(mainDelta);
        }
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
    Color pointColor_;
    Color userActiveColor_;
    Color userPointColor_;
    Dimension hoverRadius_ = 8.0_vp;
    float hoverDuration_ = 0.0f;
    float hoverToTouchDuration_ = 0.0f;
    float touchDuration_ = 0.0f;
    float colorAnimationDuration_ = 0.0f;

    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;

    RefPtr<AnimatablePropertyColor> animatableBoardColor_;
    RefPtr<AnimatablePropertyColor> animateHoverColor_;
    RefPtr<PropertyFloat> mainDelta_;
    RefPtr<PropertyBool> isSelect_;
    RefPtr<PropertyBool> isHover_;
    RefPtr<PropertyOffsetF> offset_;
    RefPtr<PropertySizeF> size_;
    RefPtr<PropertyBool> enabled_;

    ACE_DISALLOW_COPY_AND_MOVE(SwitchModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWITCH_SWITCH_MODIFIER_H
