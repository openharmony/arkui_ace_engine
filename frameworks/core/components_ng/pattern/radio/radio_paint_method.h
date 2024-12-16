/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RADIO_RADIO_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RADIO_RADIO_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/radio/radio_modifier.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class RadioPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(RadioPaintMethod, NodePaintMethod)

public:
    explicit RadioPaintMethod(const RefPtr<RadioModifier>& radioModifier) : radioModifier_(radioModifier) {}

    ~RadioPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* /* paintWrapper */) override
    {
        CHECK_NULL_RETURN(radioModifier_, nullptr);
        return radioModifier_;
    }

    void UpdateUIStatus(bool checked)
    {
        if (checked != radioModifier_->GetIsCheck()) {
            if (!enabled_ && !checked && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                radioModifier_->SetUIStatus(UIStatus::UNSELECTED);
            } else {
                radioModifier_->SetUIStatus(UIStatus::SELECTED);
            }
            if (!isFirstCreated_) {
                if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                    radioModifier_->UpdateIndicatorAnimation(checked);
                } else {
                    radioModifier_->UpdateIsOnAnimatableProperty(checked);
                }
            }
        } else if (!checked && isFirstCreated_) {
            radioModifier_->InitOpacityScale(checked);
        }
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(radioModifier_);
        auto paintProperty = DynamicCast<RadioPaintProperty>(paintWrapper->GetPaintProperty());
        CHECK_NULL_VOID(paintProperty);
        bool checked = false;
        if (paintProperty->HasRadioCheck()) {
            checked = paintProperty->GetRadioCheckValue();
        } else {
            paintProperty->UpdateRadioCheck(false);
        }

        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto radioTheme = pipeline->GetTheme<RadioTheme>();
        activeColor_ = paintProperty->GetRadioCheckedBackgroundColor().value_or(Color(radioTheme->GetActiveColor()));
        inactiveColor_ = paintProperty->GetRadioUncheckedBorderColor().value_or(Color(radioTheme->GetInactiveColor()));
        pointColor_ = paintProperty->GetRadioIndicatorColor().value_or(Color(radioTheme->GetPointColor()));

        auto size = paintWrapper->GetContentSize();
        auto offset = paintWrapper->GetContentOffset();
        radioModifier_->InitializeParam();
        radioModifier_->SetPointColor(pointColor_);
        radioModifier_->SetactiveColor(activeColor_);
        radioModifier_->SetinactiveColor(inactiveColor_);
        radioModifier_->SetSize(size);
        radioModifier_->SetOffset(offset);
        radioModifier_->SetIsOnAnimationFlag(isOnAnimationFlag_);
        radioModifier_->SetEnabled(enabled_);
        radioModifier_->SetTotalScale(totalScale_);
        radioModifier_->SetPointScale(pointScale_);
        radioModifier_->SetRingPointScale(ringPointScale_);
        UpdateUIStatus(checked);
        radioModifier_->SetShowHoverEffect(showHoverEffect_);
        radioModifier_->SetIsCheck(checked);
        radioModifier_->SetTouchHoverAnimationType(touchHoverType_);
        radioModifier_->UpdateAnimatableProperty();
        auto horizontalPadding = radioTheme->GetHotZoneHorizontalPadding().ConvertToPx();
        auto verticalPadding = radioTheme->GetHotZoneVerticalPadding().ConvertToPx();
        float boundsRectOriginX = offset.GetX() - horizontalPadding;
        float boundsRectOriginY = offset.GetY() - verticalPadding;
        float boundsRectWidth = size.Width() + 2 * horizontalPadding;
        float boundsRectHeight = size.Height() + 2 * verticalPadding;
        RectF boundsRect(boundsRectOriginX, boundsRectOriginY, boundsRectWidth, boundsRectHeight);
        radioModifier_->SetBoundsRect(boundsRect);
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

    void SetIsOnAnimationFlag(const bool isOnAnimationFlag)
    {
        isOnAnimationFlag_ = isOnAnimationFlag;
    }

    void SetIsFirstCreated(const bool isFirstCreated)
    {
        isFirstCreated_ = isFirstCreated;
    }

    void SetTotalScale(const float totalScale)
    {
        totalScale_ = totalScale;
    }

    void SetPointScale(const float pointScale)
    {
        pointScale_ = pointScale;
    }

    void SetRingPointScale(const float ringPointScale)
    {
        ringPointScale_ = ringPointScale;
    }

    void SetUIStatus(const UIStatus uiStatus)
    {
        uiStatus_ = uiStatus;
    }

    void SetTouchHoverAnimationType(const TouchHoverAnimationType touchHoverType)
    {
        touchHoverType_ = touchHoverType;
    }

    void SetShowHoverEffect(bool showHoverEffect)
    {
        showHoverEffect_ = showHoverEffect;
    }

private:
    Color pointColor_;
    Color activeColor_;
    Color inactiveColor_;
    bool enabled_ = true;
    bool isOnAnimationFlag_ = false;
    bool isFirstCreated_ = true;
    bool showHoverEffect_ = true;
    float totalScale_ = 1.0f;
    float pointScale_ = 0.5f;
    float ringPointScale_ = 0.0f;
    UIStatus uiStatus_ = UIStatus::UNSELECTED;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    TouchHoverAnimationType touchHoverType_ = TouchHoverAnimationType::NONE;

    RefPtr<RadioModifier> radioModifier_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RADIO_RADIO_PAINT_METHOD_H
