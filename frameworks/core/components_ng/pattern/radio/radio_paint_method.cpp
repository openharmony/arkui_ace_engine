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
} // namespace

RadioModifier::RadioModifier()
{
    enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    isCheck_ = AceType::MakeRefPtr<PropertyBool>(false);
    uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(UIStatus::UNSELECTED));
    offset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    size_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    totalScale_ = AceType::MakeRefPtr<PropertyFloat>(1.0f);
    pointScale_ = AceType::MakeRefPtr<PropertyFloat>(0.5f);
    ringPointScale_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    animateTouchHoverColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));

    AttachProperty(enabled_);
    AttachProperty(isCheck_);
    AttachProperty(uiStatus_);
    AttachProperty(offset_);
    AttachProperty(size_);
    AttachProperty(totalScale_);
    AttachProperty(pointScale_);
    AttachProperty(ringPointScale_);
    AttachProperty(animateTouchHoverColor_);
}

void RadioModifier::InitializeParam()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    shadowWidth_ = radioTheme->GetShadowWidth().ConvertToPx();
    borderWidth_ = radioTheme->GetBorderWidth().ConvertToPx();
    pointColor_ = radioTheme->GetPointColor();
    activeColor_ = radioTheme->GetActiveColor();
    inactiveColor_ = radioTheme->GetInactiveColor();
    inactivePointColor_ = radioTheme->GetInactivePointColor();
    shadowColor_ = radioTheme->GetShadowColor();
    clickEffectColor_ = radioTheme->GetClickEffectColor();
    hoverColor_ = radioTheme->GetHoverColor();
    hotZoneHorizontalPadding_ = radioTheme->GetHotZoneHorizontalPadding();
    hoverDuration_ = radioTheme->GetHoverDuration();
    hoverToTouchDuration_ = radioTheme->GetHoverToTouchDuration();
    touchDuration_ = radioTheme->GetTouchDuration();
}

void RadioModifier::PaintRadio(
    RSCanvas& canvas, bool /* checked */, const SizeF& contentSize, const OffsetF& offset) const
{
    OffsetF paintOffset = offset;
    DrawTouchAndHoverBoard(canvas, contentSize, paintOffset);
    float outCircleRadius = contentSize.Width() / 2;
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
    if (uiStatus_->Get() == static_cast<int32_t>(UIStatus::SELECTED)) {
        if (!enabled_) {
            brush.SetColor(ToRSColor(pointColor_.BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        } else {
            brush.SetColor(ToRSColor(pointColor_));
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
            outPen.SetColor(ToRSColor(activeColor_.BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        } else {
            outPen.SetColor(ToRSColor(activeColor_));
        }
        auto outWidth = outCircleRadius * (totalScale_->Get() - pointScale_->Get() - ringPointScale_->Get());
        if (outWidth < borderWidth_) {
            outWidth = borderWidth_;
        }
        outPen.SetWidth(outWidth);
        canvas.AttachPen(outPen);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius * totalScale_->Get() - outWidth / 2);
    } else if (uiStatus_->Get() == static_cast<int32_t>(UIStatus::UNSELECTED)) {
        if (!enabled_->Get()) {
            brush.SetColor(
                ToRSColor(inactivePointColor_.BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
            pen.SetColor(ToRSColor(inactiveColor_.BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        } else {
            brush.SetColor(ToRSColor(inactivePointColor_));
            pen.SetColor(ToRSColor(inactiveColor_));
        }
        canvas.AttachBrush(brush);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius - borderWidth_);
        // draw border with unselected color
        canvas.AttachPen(pen);
        canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius - borderWidth_ / 2.0);
    }
}

void RadioModifier::DrawTouchAndHoverBoard(RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset) const
{
    float outCircleRadius = contentSize.Width() / 2;
    float centerX = outCircleRadius + offset.GetX();
    float centerY = outCircleRadius + offset.GetY();
    outCircleRadius += hotZoneHorizontalPadding_.ConvertToPx();
    RSBrush brush;
    brush.SetColor(ToRSColor(animateTouchHoverColor_->Get()));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawCircle(RSPoint(centerX, centerY), outCircleRadius);
}

} // namespace OHOS::Ace::NG
