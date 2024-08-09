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
#include "core/common/container.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/drawing_forward.h"

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
        if (useContentModifier_->Get()) {
            return;
        }
        RSCanvas& canvas = context.canvas;
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            PaintIndicator(canvas, isCheck_->Get(), size_->Get(), offset_->Get());
        } else {
            PaintRadio(canvas, isCheck_->Get(), size_->Get(), offset_->Get());
        }
    }

    void UpdateAnimatableProperty();
    void UpdateTotalScaleOnAnimatable(
        bool isCheck, const AnimationOption& delayOption, const AnimationOption& halfDurationOption);
    void UpdateIsOnAnimatableProperty(bool isCheck);
    void UpdateIndicatorAnimation(bool isCheck);
    void SetBoardColor(LinearColor color, int32_t duratuion, const RefPtr<CubicCurve>& curve);
    void InitializeParam();
    void PaintRadio(RSCanvas& canvas, bool checked, const SizeF& contentSize, const OffsetF& contentOffset) const;
    void PaintIndicator(RSCanvas& canvas, bool checked, const SizeF& contentSize, const OffsetF& contentOffset) const;
    void PaintUnselectedIndicator(RSCanvas& canvas, float outCircleRadius, float centerX, float centerY) const;
    void DrawTouchAndHoverBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& contentOffset) const;

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

    void SetEnabled(bool enabled)
    {
        if (enabled_) {
            enabled_->Set(enabled);
        }
    }

    void SetIsCheck(bool isCheck)
    {
        if (isCheck_) {
            isCheck_->Set(isCheck);
        }
    }

    bool GetIsCheck()
    {
        if (isCheck_) {
            return isCheck_->Get();
        }
        return false;
    }

    void SetIsOnAnimationFlag(bool isOnAnimationFlag)
    {
        if (isOnAnimationFlag_) {
            isOnAnimationFlag_->Set(isOnAnimationFlag);
        }
    }

    void SetTotalScale(const float totalScale)
    {
        if (totalScale_) {
            totalScale_->Set(totalScale);
        }
    }

    void InitOpacityScale(bool isCheck)
    {
        if (opacityScale_) {
            opacityScale_->Set(isCheck ? 1.0f : 0);
        }
        if (borderOpacityScale_) {
            borderOpacityScale_->Set(isCheck ? 0 : 1.0f);
        }
    }

    void SetPointScale(const float pointScale)
    {
        if (pointScale_) {
            pointScale_->Set(pointScale);
        }
    }

    void SetRingPointScale(const float ringPointScale)
    {
        if (ringPointScale_) {
            ringPointScale_->Set(ringPointScale);
        }
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

    void SetUIStatus(const UIStatus& uiStatus)
    {
        if (uiStatus_) {
            uiStatus_->Set(static_cast<int32_t>(uiStatus));
        }
    }

    void SetTouchHoverAnimationType(const TouchHoverAnimationType touchHoverType)
    {
        touchHoverType_ = touchHoverType;
    }

    void SetShowHoverEffect(bool showHoverEffect)
    {
        showHoverEffect_ = showHoverEffect;
    }

    void SetUseContentModifier(bool useContentModifier)
    {
        if (useContentModifier_) {
            useContentModifier_->Set(useContentModifier);
        }
    }

private:
    float shadowWidth_ = 1.5f;
    float borderWidth_ = 1.5f;
    Color inactivePointColor_;
    Color shadowColor_;
    Color clickEffectColor_;
    Color hoverColor_;
    Dimension hotZoneHorizontalPadding_;
    Dimension defaultPadding_;
    float hoverDuration_ = 0.0f;
    float hoverToTouchDuration_ = 0.0f;
    float touchDuration_ = 0.0f;
    bool showHoverEffect_ = true;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    RefPtr<PropertyBool> isOnAnimationFlag_;
    RefPtr<PropertyBool> enabled_;
    RefPtr<PropertyBool> isCheck_;
    RefPtr<PropertyInt> uiStatus_;
    RefPtr<PropertyBool> useContentModifier_;

    RefPtr<AnimatablePropertyColor> pointColor_;
    RefPtr<AnimatablePropertyColor> activeColor_;
    RefPtr<AnimatablePropertyColor> inactiveColor_;
    RefPtr<AnimatablePropertyOffsetF> offset_;
    RefPtr<AnimatablePropertySizeF> size_;
    RefPtr<RadioModifier> radioModifier_;
    RefPtr<AnimatablePropertyFloat> totalScale_;
    RefPtr<AnimatablePropertyFloat> opacityScale_;
    RefPtr<AnimatablePropertyFloat> borderOpacityScale_;
    RefPtr<AnimatablePropertyFloat> pointScale_;
    RefPtr<AnimatablePropertyFloat> ringPointScale_;
    RefPtr<AnimatablePropertyColor> animateTouchHoverColor_;
    TouchHoverAnimationType touchHoverType_ = TouchHoverAnimationType::NONE;

    ACE_DISALLOW_COPY_AND_MOVE(RadioModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_MODIFIER_H
