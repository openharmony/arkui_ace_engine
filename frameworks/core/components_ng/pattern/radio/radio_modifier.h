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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_MODIFIER_H

#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/animation/spring_curve.h"
#include "core/common/container.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/render/canvas.h"
namespace OHOS::Ace::NG {
enum class UIStatus {
    SELECTED = 0,
    UNSELECTED,
    FOCUS,
    ON_TO_OFF,
    OFF_TO_ON,
    PART,
    PART_TO_OFF,
    OFF_TO_PART,
    PART_TO_ON,
    ON_TO_PART,
};

enum class TouchHoverAnimationType {
    NONE = 0,
    HOVER,
    PRESS,
    HOVER_TO_PRESS,
    PRESS_TO_HOVER,
};

class RadioModifier : public ContentModifier {
    DECLARE_ACE_TYPE(RadioModifier, ContentModifier);

public:
    RadioModifier();
    ~RadioModifier() override = default;

    void onDraw(DrawingContext& context) override
    {
        PaintRadio(context);
    }

    void UpdateAnimatableProperty()
    {
        AnimationOption option = AnimationOption();
        option.SetDuration(hoverDuration_);
        option.SetCurve(Curves::FRICTION);
        AnimationUtils::Animate(option, [&]() {
            switch (touchHoverType_) {
                case TouchHoverAnimationType::HOVER:
                    animateTouchHoverColor_->Set(LinearColor(hoverColor_));
                    break;
                case TouchHoverAnimationType::NONE:
                    animateTouchHoverColor_->Set(LinearColor(Color::TRANSPARENT));
                    break;
                default:
                    break;
            }
        });
    }

    void InitializeParam();
    void PaintRadio(DrawingContext& context) const;
    void DrawTouchAndHoverBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const;

    void SetPointColor(const Color& pointColor)
    {
        pointColor_->Set(LinearColor(pointColor));
    }
    void SetactiveColor(const Color& activeColor)
    {
        activeColor_->Set(LinearColor(activeColor));
    }
    void SetinactiveColor(const Color& inactiveColor)
    {
        inactiveColor_->Set(LinearColor(inactiveColor));
    }
    void SetHotZoneOffset(const OffsetF& hotZoneOffset)
    {
        hotZoneOffset_ = hotZoneOffset;
    }

    void SetHotZoneSize(const SizeF& hotZoneSize)
    {
        hotZoneSize_ = hotZoneSize;
    }

    void SetEnabled(const bool enabled)
    {
        enabled_ = enabled;
    }

    void SetIsCheck(const bool isCheck)
    {
        isCheck_ = isCheck;
    }

    void SetTotalScale(const float totalScale)
    {
        if (totalScale_) {
            totalScale_->Set(totalScale);
        }
    }

    void SetPointScale(const float pointScale)
    {
        if (pointScale_) {
            pointScale_->Set(pointScale);
        }
    }

    void SetOffset(const OffsetF& offset)
    {
        offset_ = offset;
    }

    void SetSize(const SizeF& size)
    {
        size_ = size;
    }

    void SetUIStatus(const UIStatus uiStatus)
    {
        uiStatus_ = uiStatus;
    }

    void SetTouchHoverAnimationType(const TouchHoverAnimationType touchHoverType)
    {
        touchHoverType_ = touchHoverType;
    }

private:
    RefPtr<AnimatablePropertyColor> pointColor_;
    RefPtr<AnimatablePropertyColor> activeColor_;
    RefPtr<AnimatablePropertyColor> inactiveColor_;
    float shadowWidth_ = 1.5f;
    float borderWidth_ = 1.5f;
    Color inactivePointColor_;
    Color shadowColor_;
    Color clickEffectColor_;
    Color hoverColor_;
    Dimension hotZoneHorizontalPadding_;
    float hoverDuration_ = 0.0f;
    float hoverToTouchDuration_ = 0.0f;
    float touchDuration_ = 0.0f;

    bool enabled_ = true;
    bool isCheck_ = false;
    UIStatus uiStatus_ = UIStatus::UNSELECTED;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    OffsetF offset_;
    SizeF size_;
    RefPtr<RadioModifier> radioModifier_;
    RefPtr<PropertyFloat> totalScale_;
    RefPtr<PropertyFloat> pointScale_;
    RefPtr<AnimatablePropertyColor> animateTouchHoverColor_;
    TouchHoverAnimationType touchHoverType_;

    ACE_DISALLOW_COPY_AND_MOVE(RadioModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_MODIFIER_H