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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/radio/radio_paint_method.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing_forward.h"

namespace OHOS::Ace::NG {
class CheckBoxGroupModifier : public ContentModifier {
    DECLARE_ACE_TYPE(CheckBoxGroupModifier, ContentModifier);

public:
    struct Parameters {
        float borderWidth;
        float borderRadius;
        float checkStroke;
        float checkMarkPaintSize;
        Color pointColor;
        Color activeColor;
        Color inactiveColor;
        Color shadowColor;
        Color clickEffectColor;
        Color hoverColor;
        Color inactivePointColor;
        Dimension hoverRadius;
        Dimension hotZoneHorizontalPadding;
        Dimension hotZoneVerticalPadding;
        Dimension shadowWidth;
        UIStatus uiStatus;
        CheckBoxGroupPaintProperty::SelectStatus status;
    };

    CheckBoxGroupModifier(const Parameters& parameters);
    ~CheckBoxGroupModifier() override = default;
    void onDraw(DrawingContext& context) override
    {
        PaintCheckBox(context, offset_->Get(), size_->Get());
    }

    void PaintCheckBox(DrawingContext& context, const OffsetF& paintOffset, const SizeF& contentSize) const;
    void PaintCheckBoxGroupPartStatus(RSCanvas& canvas, const OffsetF& paintOffset, RSBrush& brush,
        RSPen pen, const SizeF& paintSize) const;
    void DrawUnselected(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const;
    void DrawActiveBorder(RSCanvas& canvas, const OffsetF& paintOffset, RSBrush& brush, const SizeF& paintSize) const;
    void DrawUnselectedBorder(RSCanvas& canvas, const OffsetF& paintOffset,
        RSBrush& brush, const SizeF& paintSize) const;
    void DrawMark(RSCanvas& canvas, RSPath& path, RSPen& pen) const;
    void DrawPart(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const;
    void DrawTouchBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const;
    void DrawHoverBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const;
    void DrawAnimationOffToOn(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const;
    void DrawAnimationOnToOff(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const;

    void SetBorderWidth(float borderWidth)
    {
        borderWidth_ = borderWidth;
    }

    void SetBorderRadius(float borderRadius)
    {
        borderRadius_ = borderRadius;
    }

    void SetCheckStroke(float checkStroke)
    {
        checkStroke_->Set(checkStroke);
    }

    void SetCheckMarkPaintSize(float checkMarkPaintSize)
    {
        checkMarkPaintSize_->Set(checkMarkPaintSize);
    }
    
    void SetPointColor(Color pointColor)
    {
        pointColor_->Set(LinearColor(pointColor));
    }

    void SetActiveColor(Color activeColor)
    {
        activeColor_->Set(LinearColor(activeColor));
    }

    void SetInactiveColor(Color inactiveColor)
    {
        inactiveColor_->Set(LinearColor(inactiveColor));
    }

    void SetShadowColor(Color shadowColor)
    {
        shadowColor_ = shadowColor;
    }

    void SetClickEffectColor(Color clickEffectColor)
    {
        clickEffectColor_ = clickEffectColor;
    }

    void SetHoverColor(Color hoverColor)
    {
        hoverColor_ = hoverColor;
    }

    void SetInactivePointColor(Color inactivePointColor)
    {
        inactivePointColor_ = inactivePointColor;
    }

    void SetHoverRadius(Dimension hoverRadius)
    {
        hoverRadius_ = hoverRadius;
    }

    void SetHotZoneHorizontalPadding(Dimension hotZoneHorizontalPadding)
    {
        hotZoneHorizontalPadding_ = hotZoneHorizontalPadding;
    }

    void SetHotZoneVerticalPadding(Dimension hotZoneVerticalPadding)
    {
        hotZoneVerticalPadding_ = hotZoneVerticalPadding;
    }

    void SetShadowWidth(Dimension shadowWidth)
    {
        shadowWidth_ = shadowWidth;
    }

    void SetEnabled(bool value)
    {
        enabled_->Set(value);
    }

    void SetIsTouch(bool value)
    {
        isTouch_->Set(value);
    }

    void SetIsHover(bool value)
    {
        isHover_->Set(value);
    }

    void SetShapeScale(float value)
    {
        shapeScale_->Set(value);
    }

    void SetUiStatus(UIStatus uiStatus)
    {
        if (uiStatus_) {
            uiStatus_->Set(static_cast<int>(uiStatus));
        }
    }

    void SetSelectStatus(CheckBoxGroupPaintProperty::SelectStatus status)
    {
        if (status_) {
            status_->Set(static_cast<int>(status));
        }
    }

    float GetBorderWidth()
    {
        return borderWidth_;
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

private:
    RefPtr<AnimatablePropertyColor> activeColor_;
    RefPtr<AnimatablePropertyColor> pointColor_;
    RefPtr<AnimatablePropertyColor> inactiveColor_;
    RefPtr<AnimatablePropertyFloat> checkMarkPaintSize_;
    RefPtr<AnimatablePropertyFloat> checkStroke_;
    RefPtr<PropertyFloat> shapeScale_;
    RefPtr<PropertyBool> isTouch_;
    RefPtr<PropertyBool> isHover_;
    RefPtr<PropertyBool> enabled_;
    RefPtr<PropertyInt> uiStatus_;
    RefPtr<PropertyInt> status_;
    RefPtr<PropertyOffsetF> offset_;
    RefPtr<PropertySizeF> size_;
    float borderWidth_;
    float borderRadius_;
    Color shadowColor_;
    Color clickEffectColor_;
    Color hoverColor_;
    Color inactivePointColor_;
    Dimension hoverRadius_;
    Dimension hotZoneHorizontalPadding_;
    Dimension hotZoneVerticalPadding_;
    Dimension shadowWidth_;
    ACE_DISALLOW_COPY_AND_MOVE(CheckBoxGroupModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_MODIFIER_H
