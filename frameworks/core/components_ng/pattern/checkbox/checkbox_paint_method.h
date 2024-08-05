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
    CheckBoxPaintMethod() = default;

    ~CheckBoxPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        if (!checkboxModifier_) {
            auto size = paintWrapper->GetContentSize();
            auto offset = paintWrapper->GetContentOffset();
            auto pipeline = PipelineBase::GetCurrentContextSafely();
            CHECK_NULL_RETURN(pipeline, nullptr);
            auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
            CHECK_NULL_RETURN(checkBoxTheme, nullptr);
            auto paintProperty = DynamicCast<CheckBoxPaintProperty>(paintWrapper->GetPaintProperty());
            auto isSelect = paintProperty->GetCheckBoxSelectValue(false);
            auto boardColor = isSelect ? paintProperty->GetCheckBoxSelectedColorValue(checkBoxTheme->GetActiveColor())
                                       : checkBoxTheme->GetInactivePointColor();
            auto checkColor = isSelect ? checkBoxTheme->GetPointColor() : Color::TRANSPARENT;
            auto borderColor = isSelect ? Color::TRANSPARENT : checkBoxTheme->GetInactiveColor();
            auto shadowColor = isSelect ? checkBoxTheme->GetShadowColor() : Color::TRANSPARENT;
            float strokePaintSize = size.Width();
            auto checkStroke = static_cast<float>(checkBoxTheme->GetCheckStroke().ConvertToPx());
            if (paintProperty->HasCheckBoxCheckMarkWidth()) {
                checkStroke = static_cast<float>(paintProperty->GetCheckBoxCheckMarkWidthValue().ConvertToPx());
                auto strokeLimitByMarkSize = strokePaintSize * CHECKBOX_MARK_STROKEWIDTH_LIMIT_RATIO;
                if (checkStroke > strokeLimitByMarkSize) {
                    checkStroke = strokeLimitByMarkSize;
                }
            }
            auto strokeSize = size.Width();
            if (paintProperty->HasCheckBoxCheckMarkSize()) {
                if (paintProperty->GetCheckBoxCheckMarkSizeValue().ConvertToPx() >= 0) {
                    strokePaintSize = paintProperty->GetCheckBoxCheckMarkSizeValue().ConvertToPx();
                }
                if (strokePaintSize > size.Width()) {
                    strokePaintSize = size.Width();
                }
            }
            checkboxModifier_ = AceType::MakeRefPtr<CheckBoxModifier>(
                isSelect, boardColor, checkColor, borderColor, shadowColor, size, offset, checkStroke, strokeSize);
        }
        return checkboxModifier_;
    }

    void UpdateCheckboxColors(const RefPtr<CheckBoxPaintProperty>& paintProperty)
    {
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
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(checkboxModifier_);
        checkboxModifier_->InitializeParam();
        CHECK_NULL_VOID(paintWrapper);
        auto size = paintWrapper->GetContentSize();
        float strokePaintSize = size.Width();
        auto paintProperty = DynamicCast<CheckBoxPaintProperty>(paintWrapper->GetPaintProperty());
        if (paintProperty->GetCheckBoxSelect().has_value()) {
            checkboxModifier_->SetIsSelect(paintProperty->GetCheckBoxSelectValue());
        }
        UpdateCheckboxColors(paintProperty);
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
        auto offset = paintWrapper->GetContentOffset();
        checkboxModifier_->SetOffset(offset);
        checkboxModifier_->SetEnabled(enabled_);
        checkboxModifier_->SetTouchHoverAnimationType(touchHoverType_);
        checkboxModifier_->UpdateAnimatableProperty();

        SetHoverEffectType(paintProperty);
        SetModifierBoundsRect(size, offset);
    }

    void SetModifierBoundsRect(const SizeF& size, const OffsetF& offset)
    {
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

    void SetCheckboxStyle(CheckBoxStyle checkBoxStyle)
    {
        checkBoxStyle_ = checkBoxStyle;
    }

    void SetUseContentModifier(bool useContentModifier)
    {
        useContentModifier_ = useContentModifier;
    }

    void SetHasBuilder(bool hasBuilder)
    {
        hasBuilder_ = hasBuilder;
    }

    RefPtr<CheckBoxModifier> GetCheckBoxModifier()
    {
        return checkboxModifier_;
    }

private:
    bool enabled_ = true;
    float totalScale_ = 1.0f;
    float pointScale_ = 0.5f;
    bool hasBuilder_ = false;
    bool useContentModifier_ = false;
    CheckBoxStyle checkBoxStyle_ = CheckBoxStyle::CIRCULAR_STYLE;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    TouchHoverAnimationType touchHoverType_ = TouchHoverAnimationType::NONE;

    RefPtr<CheckBoxModifier> checkboxModifier_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOX_CHECKBOX_PAINT_METHOD_H
