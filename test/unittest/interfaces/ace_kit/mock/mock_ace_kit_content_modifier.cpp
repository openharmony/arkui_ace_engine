/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_content_modifier.h"

#include <memory>

#include "2d_graphics/include/draw/brush.h"
#include "2d_graphics/include/draw/canvas.h"
#include "2d_graphics/include/draw/color.h"
#include "2d_graphics/include/draw/pen.h"
#include "render_service_client/core/modifier/rs_property.h"
#include "ui/animation/animation_option.h"
#include "ui/animation/animation_utils.h"
#include "ui/animation/curves.h"
#include "ui/base/geometry/dimension.h"
#include "ui/base/utils/utils.h"
#include "ui/properties/linear_color.h"

namespace OHOS::Ace::Kit {
namespace {
constexpr int32_t DEFAULT_PEN_WIDTH = 5;
constexpr int32_t DEFAULT_DURATION = 300;
} // namespace
using RSPen = Rosen::Drawing::Pen;
using RSCanvas = Rosen::Drawing::Canvas;
using RSColor = Rosen::Drawing::Color;
using RSBrush = Rosen::Drawing::Brush;

RSColor ToRSColor(const Ace::LinearColor& color)
{
    return RSColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}

MockAceKitContentModifier::MockAceKitContentModifier()
{
    ringWidth_ = std::make_shared<Rosen::RSProperty<float>>();
    fillColor_ = std::make_shared<Rosen::RSAnimatableProperty<Ace::LinearColor>>();
}

void MockAceKitContentModifier::OnDraw(const Ace::Kit::DrawingContext& context)
{
    RSCanvas* canvas = context.canvas;
    RSPen pen;
    pen.SetWidth(ringWidth_ ? ringWidth_->Get() : DEFAULT_PEN_WIDTH);
    pen.SetColor(RSColor::COLOR_CYAN);
    RSBrush brush;
    if (fillColor_ && attached_) {
        brush.SetColor(ToRSColor(fillColor_->Get()));
    }
    canvas->AttachPen(pen);
    canvas->AttachBrush(brush);
    canvas->DrawRect({ 0, 0, context.width, context.height });
    canvas->DetachPen();
    canvas->DetachBrush();
}

void MockAceKitContentModifier::OnAttached()
{
    if (!attached_) {
        AttachRSProperty(ringWidth_);
        AttachRSProperty(fillColor_);
        fillColor_->Set(Ace::LinearColor(initialColor_));
        attached_ = true;
    }
}

void MockAceKitContentModifier::SetFillColor(const Ace::Color& color)
{
    if (!attached_) {
        initialColor_ = color;
    } else {
        Ace::AnimationOption option;
        option.SetDuration(DEFAULT_DURATION);
        option.SetIteration(1);
        option.SetCurve(Ace::Curves::EASE_IN);
        Ace::Kit::AnimationUtils::Animate(
            option, [fillColor = fillColor_, color]() { fillColor->Set(Ace::LinearColor(color)); });
    }
}

void MockAceKitContentModifier::SetRingWidth(const Ace::Dimension& width)
{
    ringWidth_->Set(width.ConvertToPx());
}

} // namespace OHOS::Ace::Kit
