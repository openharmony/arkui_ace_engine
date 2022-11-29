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
#include "core/components_ng/pattern/radio/radio_paint_method.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/utils/utils.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint8_t ENABLED_ALPHA = 255;
constexpr uint8_t DISABLED_ALPHA = 102;
constexpr Dimension INNER_PADDING = 2.0_vp;
} // namespace

CanvasDrawFunction RadioPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    InitializeParam();
    auto paintProperty = DynamicCast<RadioPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(paintProperty, nullptr);
    bool checked = false;
    if (paintProperty->HasRadioCheck()) {
        checked = paintProperty->GetRadioCheckValue();
    } else {
        paintProperty->UpdateRadioCheck(false);
    }
    auto contentSize = paintWrapper->GetContentSize();
    auto offset = paintWrapper->GetContentOffset();
    auto paintFunc = [weak = WeakClaim(this), checked, contentSize, offset](RSCanvas& canvas) {
        auto radio = weak.Upgrade();
        if (radio) {
            radio->PaintRadio(canvas, checked, contentSize, offset);
        }
    };
    return paintFunc;
}

void RadioPaintMethod::InitializeParam()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    shadowWidth_ = radioTheme->GetShadowWidth().ConvertToPx();
    borderWidth_ = radioTheme->GetBorderWidth().ConvertToPx();
    activeColor_ = radioTheme->GetActiveColor();
    inactiveColor_ = radioTheme->GetInactiveColor();
    shadowColor_ = radioTheme->GetShadowColor();
    clickEffectColor_ = radioTheme->GetClickEffectColor();
    hoverColor_ = radioTheme->GetHoverColor();
    hotZoneHorizontalPadding_ = radioTheme->GetHotZoneHorizontalPadding();
}

void RadioPaintMethod::PaintRadio(
    RSCanvas& canvas, bool /* checked */, const SizeF& contentSize, const OffsetF& offset) const
{
    OffsetF paintOffset = offset;
    if (isTouch_ || isHover_) {
        paintOffset.SetX(offset.GetX() + hotZoneHorizontalPadding_.ConvertToPx());
        paintOffset.SetY(offset.GetY() + hotZoneHorizontalPadding_.ConvertToPx());
    }
    if (isTouch_) {
        DrawTouchBoard(canvas, contentSize, paintOffset);
    }
    if (isHover_) {
        DrawHoverBoard(canvas, contentSize, paintOffset);
    }

    float outCircleRadius = contentSize.Width() / 2 - INNER_PADDING.ConvertToPx();
    float centerX = outCircleRadius + paintOffset.GetX() + INNER_PADDING.ConvertToPx();
    float centerY = outCircleRadius + paintOffset.GetY() + INNER_PADDING.ConvertToPx();
    if (uiStatus_ == UIStatus::SELECTED) {
        // draw stroke border
        RSPen pen;
        RSBrush brush;
        brush.SetAntiAlias(true);
        brush.SetColor(ToRSColor(activeColor_));
        pen.SetAntiAlias(true);
        pen.SetColor(ToRSColor(activeColor_));
        if (!enabled_) {
            brush.SetColor(ToRSColor(activeColor_.BlendOpacity(float(DISABLED_ALPHA) / ENABLED_ALPHA)));
            pen.SetColor(ToRSColor(activeColor_.BlendOpacity(float(DISABLED_ALPHA) / ENABLED_ALPHA)));
        }
        canvas.AttachBrush(brush);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * totalScale_);
        canvas.AttachPen(pen);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * totalScale_);
        // draw shadow
        if (!NearZero(pointScale_) && !NearEqual(pointScale_, 1.0)) {
            brush.SetColor(ToRSColor(shadowColor_));
            canvas.AttachBrush(brush);
            canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * pointScale_ + shadowWidth_);
        }
        // draw inner circle
        brush.SetColor(ToRSColor(Color::WHITE));
        canvas.AttachBrush(brush);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * pointScale_);
        pen.SetColor(ToRSColor(Color::WHITE));
        canvas.AttachPen(pen);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * pointScale_);
    } else if (uiStatus_ == UIStatus::UNSELECTED) {
        RSPen pen;
        RSBrush brush;
        brush.SetColor(ToRSColor(Color::TRANSPARENT));
        brush.SetAntiAlias(true);
        canvas.AttachBrush(brush);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius - borderWidth_ / 2.0);
        // draw border with unselected color
        pen.SetAntiAlias(true);
        pen.SetColor(ToRSColor(inactiveColor_));
        if (!enabled_) {
            brush.SetColor(ToRSColor(inactiveColor_.BlendOpacity(float(DISABLED_ALPHA) / ENABLED_ALPHA)));
            pen.SetColor(ToRSColor(inactiveColor_.BlendOpacity(float(DISABLED_ALPHA) / ENABLED_ALPHA)));
        }
        pen.SetWidth(borderWidth_);
        canvas.AttachPen(pen);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius - borderWidth_ / 2.0);
    }
}

void RadioPaintMethod::DrawTouchBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const
{
    float outCircleRadius = contentSize.Width() / 2;
    float centerX = outCircleRadius + offset.GetX();
    float centerY = outCircleRadius + offset.GetY();
    RSBrush brush;
    brush.SetColor(ToRSColor(Color(clickEffectColor_)));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius + hotZoneHorizontalPadding_.ConvertToPx());
}

void RadioPaintMethod::DrawHoverBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const
{
    float outCircleRadius = contentSize.Width() / 2;
    float centerX = outCircleRadius + offset.GetX();
    float centerY = outCircleRadius + offset.GetY();
    RSBrush brush;
    brush.SetColor(ToRSColor(Color(hoverColor_)));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius + hotZoneHorizontalPadding_.ConvertToPx());
}

} // namespace OHOS::Ace::NG
