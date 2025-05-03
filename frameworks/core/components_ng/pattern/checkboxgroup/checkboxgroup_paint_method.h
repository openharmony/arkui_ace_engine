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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOXGROUP_CHECKBOXGROUP_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOXGROUP_CHECKBOXGROUP_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_modifier.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {
constexpr float CHECKBOXGROUP_MARK_STROKEWIDTH_LIMIT_RATIO = 0.25f;

class CheckBoxGroupPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(CheckBoxGroupPaintMethod, NodePaintMethod)

public:
    explicit CheckBoxGroupPaintMethod(const RefPtr<CheckBoxGroupModifier>& checkboxGroupModifier)
        : checkboxGroupModifier_(checkboxGroupModifier) {};

    ~CheckBoxGroupPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* /*paintWrapper*/) override
    {
        CHECK_NULL_RETURN(checkboxGroupModifier_, nullptr);
        return checkboxGroupModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(checkboxGroupModifier_);
        CHECK_NULL_VOID(paintWrapper);
        auto paintProperty = DynamicCast<CheckBoxGroupPaintProperty>(paintWrapper->GetPaintProperty());
        CHECK_NULL_VOID(paintProperty);
        auto size = paintWrapper->GetContentSize();
        auto offset = paintWrapper->GetContentOffset();
        float strokePaintSize = size.Width();
        SetModifierContentType(paintProperty);
        if (paintProperty->GetCheckBoxGroupCheckMarkSize().has_value()) {
            if (paintProperty->GetCheckBoxGroupCheckMarkSizeValue().ConvertToPx() >= 0) {
                strokePaintSize = paintProperty->GetCheckBoxGroupCheckMarkSizeValue().ConvertToPx();
            }
            if (strokePaintSize > size.Width()) {
                strokePaintSize = size.Width();
            }
        }
        checkboxGroupModifier_->SetCheckMarkPaintSize(strokePaintSize);
        if (paintProperty->GetCheckBoxGroupCheckMarkWidth().has_value()) {
            auto strokeWidth = paintProperty->GetCheckBoxGroupCheckMarkWidthValue().ConvertToPx();
            auto strokeLimitByMarkSize = strokePaintSize * CHECKBOXGROUP_MARK_STROKEWIDTH_LIMIT_RATIO;
            if (strokeWidth > strokeLimitByMarkSize) {
                strokeWidth = strokeLimitByMarkSize;
            }
            checkboxGroupModifier_->SetCheckStroke(strokeWidth);
        }
        auto selectStatus = paintProperty->GetSelectStatus();

        checkboxGroupModifier_->SetEnabled(enabled_);
        checkboxGroupModifier_->SetUiStatus(uiStatus_);
        checkboxGroupModifier_->SetSelectStatus(selectStatus);
        checkboxGroupModifier_->SetOffset(offset);
        checkboxGroupModifier_->SetSize(size);
        checkboxGroupModifier_->SetTouchHoverAnimationType(touchHoverType_);
        checkboxGroupModifier_->UpdateAnimatableProperty();
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto host = paintWrapper->GetRenderContext() ? paintWrapper->GetRenderContext()->GetHost() : nullptr;
        auto checkboxTheme = pipeline->GetTheme<CheckboxTheme>(host ? host->GetThemeScopeId() : 0);
        CHECK_NULL_VOID(checkboxTheme);
        auto horizontalPadding = checkboxTheme->GetHotZoneHorizontalPadding().ConvertToPx();
        auto verticalPadding = checkboxTheme->GetHotZoneVerticalPadding().ConvertToPx();
        float boundsRectOriginX = offset.GetX() - horizontalPadding;
        float boundsRectOriginY = offset.GetY() - verticalPadding;
        float boundsRectWidth = size.Width() + 2 * horizontalPadding;
        float boundsRectHeight = size.Height() + 2 * verticalPadding;
        RectF boundsRect(boundsRectOriginX, boundsRectOriginY, boundsRectWidth, boundsRectHeight);
        checkboxGroupModifier_->SetBoundsRect(boundsRect);
        SetHoverEffectType(paintProperty);
        checkboxGroupModifier_->SetInactivePointColor(checkboxTheme->GetInactivePointColor());
    }

    void SetModifierContentType(const RefPtr<CheckBoxGroupPaintProperty>& paintProperty)
    {
        CHECK_NULL_VOID(paintProperty);
        if (paintProperty->GetCheckBoxGroupSelectedColor().has_value()) {
            checkboxGroupModifier_->SetActiveColor(paintProperty->GetCheckBoxGroupSelectedColor().value());
        }
        if (paintProperty->GetCheckBoxGroupUnSelectedColor().has_value()) {
            checkboxGroupModifier_->SetInactiveColor(paintProperty->GetCheckBoxGroupUnSelectedColor().value());
        }
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            if (paintProperty->HasCheckBoxGroupSelectedStyle()) {
                checkboxGroupModifier_->SetCheckboxGroupStyle(paintProperty->GetCheckBoxGroupSelectedStyleValue());
            }
        }
        if (paintProperty->GetCheckBoxGroupCheckMarkColor().has_value()) {
            checkboxGroupModifier_->SetPointColor(paintProperty->GetCheckBoxGroupCheckMarkColor().value());
        }
    }

    void SetHoverEffectType(const RefPtr<CheckBoxGroupPaintProperty>& checkBoxgroupPaintProperty)
    {
        auto host = checkBoxgroupPaintProperty->GetHost();
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
            if (checkboxGroupModifier_) {
                checkboxGroupModifier_->SetHoverEffectType(hoverEffectType);
            }
        }
    }

    void SetEnabled(bool enabled)
    {
        enabled_ = enabled;
    }

    void SetUiStatus(const UIStatus uiStatus)
    {
        uiStatus_ = uiStatus;
    }

    void SetTouchHoverAnimationType(const TouchHoverAnimationType touchHoverType)
    {
        touchHoverType_ = touchHoverType;
    }

    void SetHotZoneOffset(OffsetF& hotZoneOffset)
    {
        hotZoneOffset_ = hotZoneOffset;
    }

    void SetHotZoneSize(SizeF& hotZoneSize)
    {
        hotZoneSize_ = hotZoneSize;
    }

private:
    bool enabled_ = true;
    UIStatus uiStatus_ = UIStatus::UNSELECTED;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    TouchHoverAnimationType touchHoverType_ = TouchHoverAnimationType::NONE;
    RefPtr<CheckBoxGroupModifier> checkboxGroupModifier_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOXGROUP_CHECKBOXGROUP_PAINT_METHOD_H
