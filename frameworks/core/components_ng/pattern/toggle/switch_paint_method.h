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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_PAINT_METHOD_H

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/toggle/switch_modifier.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SWITCH_ERROR_RADIUS = -1.0f;
constexpr double NUM_TWO = 2.0;
} // namespace
class ACE_EXPORT SwitchPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(SwitchPaintMethod, NodePaintMethod)
public:
    SwitchPaintMethod() = default;

    ~SwitchPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        if (!switchModifier_) {
            auto paintProperty = DynamicCast<SwitchPaintProperty>(paintWrapper->GetPaintProperty());
            CHECK_NULL_RETURN(paintProperty, nullptr);
            auto size = paintWrapper->GetContentSize();
            auto offset = paintWrapper->GetContentOffset();
            bool isRtl = direction_ == TextDirection::AUTO ? AceApplicationInfo::GetInstance().IsRightToLeft()
                                                           : direction_ == TextDirection::RTL;
            auto pointOffset = isSelect_ ^ isRtl ? size.Width() - size.Height() : 0.0f;
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_RETURN(pipeline, nullptr);
            auto switchTheme = pipeline->GetTheme<SwitchTheme>();
            auto boardColor = isSelect_ ? paintProperty->GetSelectedColorValue(switchTheme->GetActiveColor())
                                        : switchTheme->GetInactivePointColor();
            switchModifier_ =
                AceType::MakeRefPtr<SwitchModifier>(size, offset, pointOffset, isSelect_, boardColor, dragOffsetX_);
            switchModifier_->InitializeParam();
        }
        return switchModifier_;
    }

    void UpdateBoundsRect(PaintWrapper* paintWrapper, float pointRadius, double actualTrackRadius)
    {
        CHECK_NULL_VOID(switchModifier_);
        auto size = paintWrapper->GetContentSize();
        auto offset = paintWrapper->GetContentOffset();
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto switchTheme = pipeline->GetTheme<SwitchTheme>();
        auto horizontalPadding = switchTheme->GetHotZoneHorizontalPadding().ConvertToPx();
        auto verticalPadding = switchTheme->GetHotZoneVerticalPadding().ConvertToPx();
        auto actualGap = radiusGap_.ConvertToPx() * size.Height() /
                        (switchTheme->GetHeight().ConvertToPx() - verticalPadding * 2);
        auto horizontalIncrement = 0.0;
        auto verticalIncrement = 0.0;
        auto actualPointRadius = pointRadius == SWITCH_ERROR_RADIUS ? size.Height() / NUM_TWO - actualGap : pointRadius;
        if (GreatOrEqual(size.Width(), size.Height())) {
            horizontalIncrement =
                (actualPointRadius * NUM_TWO > size.Height()) ? (actualPointRadius - size.Height() / NUM_TWO) : 0.0;
            verticalIncrement =
                (actualPointRadius * NUM_TWO > size.Height()) ? (actualPointRadius - size.Height() / NUM_TWO) : 0.0;
        } else {
            horizontalIncrement =
                (actualPointRadius > actualTrackRadius) ? (actualPointRadius - actualTrackRadius) : 0.0;
            verticalIncrement =
                (actualPointRadius * NUM_TWO > size.Height()) ? (actualPointRadius - size.Height() / NUM_TWO) : 0.0;
        }
        horizontalPadding += horizontalIncrement;
        verticalPadding += verticalIncrement;
        float boundsRectOriginX = offset.GetX() - horizontalPadding;
        float boundsRectOriginY = offset.GetY() - verticalPadding;
        float boundsRectWidth = size.Width() + 2 * horizontalPadding;
        float boundsRectHeight = size.Height() + 2 * verticalPadding;
        RectF boundsRect(boundsRectOriginX, boundsRectOriginY, boundsRectWidth, boundsRectHeight);
        switchModifier_->SetBoundsRect(boundsRect);
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(switchModifier_);
        auto paintProperty = DynamicCast<SwitchPaintProperty>(paintWrapper->GetPaintProperty());
        CHECK_NULL_VOID(paintProperty);
        switchModifier_->SetUseContentModifier(useContentModifier_);
        if (paintProperty->HasUnselectedColor()) {
            switchModifier_->SetInactiveColor(paintProperty->GetUnselectedColor().value());
        }
        if (paintProperty->HasSelectedColor()) {
            switchModifier_->SetUserActiveColor(paintProperty->GetSelectedColor().value());
        }
        if (paintProperty->HasSwitchPointColor()) {
            switchModifier_->SetPointColor(paintProperty->GetSwitchPointColor().value());
        }
        auto pointRadius = SWITCH_ERROR_RADIUS;
        if (paintProperty->HasPointRadius()) {
            pointRadius = paintProperty->GetPointRadius().value().ConvertToPx();
        }
        switchModifier_->SetPointRadius(pointRadius);
        auto trackRadius = SWITCH_ERROR_RADIUS;
        if (paintProperty->HasTrackBorderRadius()) {
            trackRadius = paintProperty->GetTrackBorderRadius().value().ConvertToPx();
        }
        switchModifier_->SetTrackRadius(trackRadius);
        auto size = paintWrapper->GetContentSize();
        auto offset = paintWrapper->GetContentOffset();
        switchModifier_->SetSize(size);
        switchModifier_->SetOffset(offset);
        switchModifier_->SetIsSelect(isSelect_);
        switchModifier_->SetDirection(direction_);
        switchModifier_->SetTouchHoverAnimationType(touchHoverType_);
        switchModifier_->SetDragOffsetX(dragOffsetX_);
        switchModifier_->SetIsDragEvent(isDragEvent_);
        switchModifier_->SetShowHoverEffect(showHoverEffect_);
        auto actualTrackRadius = 0.0;
        if (GreatOrEqual(trackRadius, 0.0) && LessOrEqual(trackRadius, std::min(size.Width(), size.Height()) / 2.0)) {
            // 2.0f is used to calculate half of the width.
            actualTrackRadius = trackRadius;
        } else {
            actualTrackRadius = size.Width() / 2.0; // 2.0f is used to calculate half of the width.
        }
        switchModifier_->SetActualTrackRadius(actualTrackRadius);
        switchModifier_->UpdateAnimatableProperty();
        UpdateBoundsRect(paintWrapper, pointRadius, actualTrackRadius);
        paintWrapper->FlushContentModifier();
    }

    void SetHotZoneOffset(OffsetF& hotZoneOffset)
    {
        hotZoneOffset_ = hotZoneOffset;
    }

    void SetHotZoneSize(SizeF& hotZoneSize)
    {
        hotZoneSize_ = hotZoneSize;
    }

    void SetHoverPercent(float hoverPercent)
    {
        hoverPercent_ = hoverPercent;
    }

    void SetDragOffsetX(float dragOffsetX)
    {
        dragOffsetX_ = dragOffsetX;
    }

    void SetIsSelect(bool isSelect)
    {
        isSelect_ = isSelect;
    }

    void SetIsHover(bool isHover)
    {
        isHover_ = isHover;
    }

    void SetTouchHoverAnimationType(const TouchHoverAnimationType touchHoverType)
    {
        touchHoverType_ = touchHoverType;
    }

    void SetIsDragEvent(bool isDragEvent)
    {
        isDragEvent_ = isDragEvent;
    }

    void SetShowHoverEffect(bool showHoverEffect)
    {
        showHoverEffect_ = showHoverEffect;
    }

    void SetDirection(TextDirection direction)
    {
        direction_ = direction;
    }

    void SetUseContentModifier(bool useContentModifier)
    {
        useContentModifier_ = useContentModifier;
    }

    RefPtr<SwitchModifier> GetSwitchModifier()
    {
        return switchModifier_;
    }

private:
    float dragOffsetX_ = 0.0f;
    float hoverPercent_ = 0.0f;
    const Dimension radiusGap_ = 2.0_vp;
    bool isSelect_ = true;
    Color clickEffectColor_ = Color::WHITE;
    Color hoverColor_ = Color::WHITE;
    Dimension hoverRadius_ = 8.0_vp;
    bool showHoverEffect_ = true;
    bool useContentModifier_ = false;

    bool isHover_ = false;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    TouchHoverAnimationType touchHoverType_ = TouchHoverAnimationType::NONE;
    TextDirection direction_ = TextDirection::AUTO;
    bool isDragEvent_ = false;

    RefPtr<SwitchModifier> switchModifier_;

    ACE_DISALLOW_COPY_AND_MOVE(SwitchPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_PAINT_METHOD_H
