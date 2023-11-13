/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOX_CHECKBOX_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOX_CHECKBOX_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/pattern/checkbox/checkbox_modifier.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"
namespace OHOS::Ace::NG {
constexpr float CHECKBOX_MARK_STROKEWIDTH_LIMIT_RATIO = 0.25f;
class CheckBoxPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(CheckBoxPaintMethod, NodePaintMethod)

public:
    explicit CheckBoxPaintMethod(const RefPtr<CheckBoxModifier>& checkboxModifier) : checkboxModifier_(checkboxModifier)
    {}

    ~CheckBoxPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(checkboxModifier_, nullptr);
        return checkboxModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(checkboxModifier_);
        checkboxModifier_->InitializeParam();
        CHECK_NULL_VOID(paintWrapper);
        auto size = paintWrapper->GetContentSize();
        auto offset = paintWrapper->GetContentOffset();
        float strokePaintSize = size.Width();
        auto paintProperty = DynamicCast<CheckBoxPaintProperty>(paintWrapper->GetPaintProperty());
        if (paintProperty->GetCheckBoxSelect().has_value()) {
            checkboxModifier_->SetIsSelect(paintProperty->GetCheckBoxSelectValue());
        }
        if (paintProperty->HasCheckBoxSelectedColor()) {
            checkboxModifier_->SetUserActiveColor(paintProperty->GetCheckBoxSelectedColorValue());
        }
        if (paintProperty->HasCheckBoxSelectedStyle()) {
            checkboxModifier_->SetCheckboxStyle(paintProperty->GetCheckBoxSelectedStyleValue());
        }
        if (paintProperty->HasCheckBoxUnSelectedColor()) {
            checkboxModifier_->SetInActiveColor(paintProperty->GetCheckBoxUnSelectedColorValue());
        }
        if (paintProperty->HasCheckBoxCheckMarkColor()) {
            checkboxModifier_->SetPointColor(paintProperty->GetCheckBoxCheckMarkColorValue());
        }
        if (paintProperty->HasCheckBoxCheckMarkSize()) {
            if (paintProperty->GetCheckBoxCheckMarkSizeValue().ConvertToPx() >= 0) {
                strokePaintSize = paintProperty->GetCheckBoxCheckMarkSizeValue().ConvertToPx();
            }
            if (strokePaintSize > size.Width()) {
                strokePaintSize = size.Width();
            }
        }
        checkboxModifier_->SetStrokeSize(strokePaintSize);
        if (paintProperty->HasCheckBoxCheckMarkWidth()) {
            auto strokeWidth = paintProperty->GetCheckBoxCheckMarkWidthValue().ConvertToPx();
            auto strokeLimitByMarkSize = strokePaintSize * CHECKBOX_MARK_STROKEWIDTH_LIMIT_RATIO;
            if (strokeWidth > strokeLimitByMarkSize) {
                strokeWidth = strokeLimitByMarkSize;
            }
            checkboxModifier_->SetStrokeWidth(strokeWidth);
        }

        checkboxModifier_->SetSize(size);
        checkboxModifier_->SetOffset(offset);
        checkboxModifier_->SetEnabled(enabled_);
        checkboxModifier_->SetTouchHoverAnimationType(touchHoverType_);
        checkboxModifier_->UpdateAnimatableProperty();
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto checkboxTheme = pipeline->GetTheme<CheckboxTheme>();
        auto horizontalPadding = checkboxTheme->GetHotZoneHorizontalPadding().ConvertToPx();
        auto verticalPadding = checkboxTheme->GetHotZoneVerticalPadding().ConvertToPx();
        float boundsRectOriginX = offset.GetX() - horizontalPadding;
        float boundsRectOriginY = offset.GetY() - verticalPadding;
        float boundsRectWidth = size.Width() + 2 * horizontalPadding;
        float boundsRectHeight = size.Height() + 2 * verticalPadding;
        RectF boundsRect(boundsRectOriginX, boundsRectOriginY, boundsRectWidth, boundsRectHeight);
        checkboxModifier_->SetBoundsRect(boundsRect);
        SetHoverEffectType(paintProperty);
    }

    void SetHoverEffectType(const RefPtr<CheckBoxPaintProperty>& checkBoxPaintProperty)
    {
        auto host = checkBoxPaintProperty->GetHost();
        CHECK_NULL_VOID(host);
        auto eventHub = host->GetEventHub<EventHub>();
        CHECK_NULL_VOID(eventHub);
        auto inputEventHub = eventHub->GetInputEventHub();
        HoverEffectType hoverEffectType = HoverEffectType::AUTO;
        if (inputEventHub) {
            hoverEffectType = inputEventHub->GetHoverEffect();
            if (HoverEffectType::UNKNOWN == hoverEffectType || HoverEffectType::OPACITY == hoverEffectType) {
                hoverEffectType = HoverEffectType::AUTO;
            }
            if (checkboxModifier_) {
                checkboxModifier_->SetHoverEffectType(hoverEffectType);
            }
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

    void SetTouchHoverAnimationType(const TouchHoverAnimationType touchHoverType)
    {
        touchHoverType_ = touchHoverType;
    }

private:
    bool enabled_ = true;
    float totalScale_ = 1.0f;
    float pointScale_ = 0.5f;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    TouchHoverAnimationType touchHoverType_ = TouchHoverAnimationType::NONE;

    RefPtr<CheckBoxModifier> checkboxModifier_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOX_CHECKBOX_PAINT_METHOD_H
