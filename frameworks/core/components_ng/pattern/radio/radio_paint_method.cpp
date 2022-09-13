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

CanvasDrawFunction RadioPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    InitializeParam();

    auto paintProperty = DynamicCast<RadioPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(paintProperty, nullptr);
    auto checked = paintProperty->GetRadioCheckValue();
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetThemeManager()->GetTheme<RadioTheme>();
    shadowWidth_ = radioTheme->GetShadowWidth().ConvertToPx();
    borderWidth_ = radioTheme->GetBorderWidth().ConvertToPx();
    activeColor_ = radioTheme->GetActiveColor();
    inactiveColor_ = radioTheme->GetInactiveColor();
    shadowColor_ = radioTheme->GetShadowColor();
}

void RadioPaintMethod::PaintRadio(RSCanvas& canvas, bool checked, const SizeF& contentSize, const OffsetF& offset) const
{
    const float totalScale = 1.0f;
    const float pointScale = 0.5f;
    float outCircleRadius = contentSize.Width() / 2;

    float centerX = outCircleRadius + offset.GetX();
    float centerY = outCircleRadius + offset.GetY();

    if (checked) {
        // draw stroke border
        RSPen pen = RSPen();
        RSBrush brush = RSBrush();
        brush.SetAntiAlias(true);
        brush.SetColor(ToRSColor(activeColor_));
        pen.SetAntiAlias(true);
        pen.SetColor(ToRSColor(activeColor_));
        canvas.AttachBrush(brush);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * totalScale);
        canvas.AttachPen(pen);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * totalScale);
        // // draw shadow
        if (!NearZero(pointScale) && !NearEqual(pointScale, 1.0)) {
            brush.SetColor(ToRSColor(shadowColor_));
            canvas.AttachBrush(brush);
            canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * pointScale + shadowWidth_);
        }
        // draw inner circle
        brush.SetColor(ToRSColor(Color::WHITE));
        canvas.AttachBrush(brush);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * pointScale);
        pen.SetColor(ToRSColor(Color::WHITE));
        canvas.AttachPen(pen);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * pointScale);
    } else {
        // draw inner circle
        RSPen pen = RSPen();
        RSBrush brush = RSBrush();
        brush.SetAlpha(50);
        brush.SetColor(ToRSColor(Color::WHITE));
        brush.SetAntiAlias(true);
        canvas.AttachBrush(brush);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius - borderWidth_ / 2.0);
        // draw border with unselected color
        pen.SetAntiAlias(true);
        pen.SetColor(ToRSColor(inactiveColor_));
        pen.SetWidth(borderWidth_);
        canvas.AttachPen(pen);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius - borderWidth_ / 2.0);
    }
}

} // namespace OHOS::Ace::NG
