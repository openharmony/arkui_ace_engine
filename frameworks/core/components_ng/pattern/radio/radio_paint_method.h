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
#include "base/utils/macros.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/radio/radio_modifier.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class RadioPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(RadioPaintMethod, NodePaintMethod)

public:
    explicit RadioPaintMethod(const RefPtr<RadioModifier>& radioModifier) : radioModifier_(radioModifier) {}

    ~RadioPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(radioModifier_, nullptr);
        return radioModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(radioModifier_);
        auto paintProperty = DynamicCast<RadioPaintProperty>(paintWrapper->GetPaintProperty());
        if (paintProperty->GetRadioCheck().has_value()) {
            radioModifier_->SetIsCheck(paintProperty->GetRadioCheckValue());
        }

        auto size = paintWrapper->GetContentSize();
        auto offset = paintWrapper->GetContentOffset();
        radioModifier_->InitializeParam();
        radioModifier_->SetSize(size);
        radioModifier_->SetOffset(offset);
        radioModifier_->SetEnabled(enabled_);
        radioModifier_->SetTotalScale(totalScale_);
        radioModifier_->SetPointScale(pointScale_);
        radioModifier_->SetRingPointScale(ringPointScale_);
        radioModifier_->SetUIStatus(uiStatus_);
        radioModifier_->SetTouchHoverAnimationType(touchHoverType_);
        radioModifier_->UpdateAnimatableProperty();
    }

    void SetHotZoneOffset(OffsetF& hotZoneOffset)
    {
        hotZoneOffset_ = hotZoneOffset;
    }

    void SetHotZoneSize(SizeF& hotZoneSize)
    {
        hotZoneSize_ = hotZoneSize;
    }

    void SetEnabled(bool enabled)
    {
        enabled_ = enabled;
    }

    void SetTotalScale(float totalScale)
    {
        totalScale_ = totalScale;
    }

    void SetPointScale(float pointScale)
    {
        pointScale_ = pointScale;
    }

    void SetRingPointScale(const float ringPointScale)
    {
        ringPointScale_ = ringPointScale;
    }

    void SetUIStatus(UIStatus& uiStatus)
    {
        uiStatus_ = uiStatus;
    }

    void SetTouchHoverAnimationType(TouchHoverAnimationType& touchHoverType)
    {
        touchHoverType_ = touchHoverType;
    }

private:
    bool enabled_ = true;
    float totalScale_ = 1.0f;
    float pointScale_ = 0.5f;
    float ringPointScale_ = 0.0f;
    UIStatus uiStatus_ = UIStatus::UNSELECTED;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    TouchHoverAnimationType touchHoverType_;

    RefPtr<RadioModifier> radioModifier_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RADIO_RADIO_PAINT_METHOD_H
