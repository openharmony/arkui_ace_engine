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
#include "core/components_ng/pattern/radio/radio_modifier.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint8_t ENABLED_ALPHA = 255;
constexpr uint8_t DISABLED_ALPHA = 102;
constexpr float CALC_RADIUS = 2.0f;
} // namespace

RadioModifier::RadioModifier()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();

    pointColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(radioTheme->GetPointColor()));
    AttachProperty(pointColor_);

    activeColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(radioTheme->GetActiveColor()));
    AttachProperty(activeColor_);

    inactiveColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(radioTheme->GetInactiveColor()));
    AttachProperty(inactiveColor_);
    totalScale_ = AceType::MakeRefPtr<PropertyFloat>(1.0f);
    pointScale_ = AceType::MakeRefPtr<PropertyFloat>(0.5f);
    ringPointScale_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    animateTouchHoverColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));

    AttachProperty(totalScale_);
    AttachProperty(pointScale_);
    AttachProperty(ringPointScale_);
    AttachProperty(animateTouchHoverColor_);

    InitializeParam();
}

void RadioModifier::InitializeParam()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    shadowWidth_ = radioTheme->GetShadowWidth().ConvertToPx();
    borderWidth_ = radioTheme->GetBorderWidth().ConvertToPx();
    inactivePointColor_ = radioTheme->GetInactivePointColor();
    shadowColor_ = radioTheme->GetShadowColor();
    clickEffectColor_ = radioTheme->GetClickEffectColor();
    hoverColor_ = radioTheme->GetHoverColor();
    hotZoneHorizontalPadding_ = radioTheme->GetHotZoneHorizontalPadding();
    hoverDuration_ = radioTheme->GetHoverDuration();
    hoverToTouchDuration_ = radioTheme->GetHoverToTouchDuration();
    touchDuration_ = radioTheme->GetTouchDuration();
}

void RadioModifier::PaintRadio(DrawingContext& context) const
{
    auto& canvas = context.canvas;
    auto contentSize = SizeF(context.width, context.height);
    OffsetF paintOffset;
    DrawTouchAndHoverBoard(canvas, contentSize, paintOffset);
    float outCircleRadius = contentSize.Width() / CALC_RADIUS;
    float centerX = paintOffset.GetX() + outCircleRadius;
    float centerY = paintOffset.GetY() + outCircleRadius;
    RSPen pen;
    RSPen outPen;
    RSBrush brush;
    RSBrush shadowBrush;
    pen.SetAntiAlias(true);
    pen.SetWidth(borderWidth_);
    outPen.SetAntiAlias(true);
    brush.SetAntiAlias(true);
    shadowBrush.SetAntiAlias(true);
    shadowBrush.SetColor(ToRSColor(shadowColor_));
    if (uiStatus_ == UIStatus::SELECTED) {
        if (!enabled_) {
            brush.SetColor(
                ToRSColor(pointColor_->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        } else {
            brush.SetColor(ToRSColor(pointColor_->Get()));
        }
        if (!NearZero(pointScale_->Get())) {
            // draw shadow
            canvas.AttachBrush(shadowBrush);
            canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * pointScale_->Get() + shadowWidth_);
            // draw inner circle
            canvas.AttachBrush(brush);
            canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * pointScale_->Get());
        }
        // draw ring circle
        if (!enabled_) {
            brush.SetColor(
                ToRSColor(inactivePointColor_.BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        } else {
            brush.SetColor(ToRSColor(inactivePointColor_));
        }
        if (!NearZero(ringPointScale_->Get())) {
            canvas.AttachBrush(brush);
            canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * ringPointScale_->Get());
        }
        // draw out circular ring
        if (!enabled_) {
            outPen.SetColor(
                ToRSColor(activeColor_->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        } else {
            outPen.SetColor(ToRSColor(activeColor_->Get()));
        }
        auto outWidth = outCircleRadius * (totalScale_->Get() - pointScale_->Get() - ringPointScale_->Get());
        if (outWidth < borderWidth_) {
            outWidth = borderWidth_;
        }
        outPen.SetWidth(outWidth);
        canvas.AttachPen(outPen);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * totalScale_->Get() - outWidth / CALC_RADIUS);
    } else if (uiStatus_ == UIStatus::UNSELECTED) {
        auto alphaCalculate = static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA;
        if (!enabled_) {
            brush.SetColor(ToRSColor(inactivePointColor_.BlendOpacity(alphaCalculate)));
            pen.SetColor(ToRSColor(inactiveColor_->Get().BlendOpacity(alphaCalculate)));
        } else {
            brush.SetColor(ToRSColor(inactivePointColor_));
            pen.SetColor(ToRSColor(inactiveColor_->Get()));
        }
        canvas.AttachBrush(brush);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius - borderWidth_);
        // draw border with unselected color
        canvas.AttachPen(pen);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius - borderWidth_ / CALC_RADIUS);
    }
}

void RadioModifier::DrawTouchAndHoverBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const
{
    float outCircleRadius = contentSize.Width() / CALC_RADIUS;
    float centerX = outCircleRadius + offset.GetX();
    float centerY = outCircleRadius + offset.GetY();
    outCircleRadius += hotZoneHorizontalPadding_.ConvertToPx();
    RSBrush brush;
    brush.SetColor(ToRSColor(Color(animateTouchHoverColor_->Get())));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius);
}

} // namespace OHOS::Ace::NG
