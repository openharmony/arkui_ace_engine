/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/badge/flutter_render_badge.h"

#include "core/components/common/properties/alignment.h"
#include "core/pipeline/base/flutter_render_context.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {
namespace {

constexpr Dimension CIRCLE_BADGE_SIZE = 6.0_vp;
constexpr Dimension NUMERICAL_BADGE_CIRCLE_SIZE = 16.0_vp;
constexpr Dimension NUMERICAL_BADGE_PADDING = 6.0_vp;

} // namespace

RefPtr<RenderNode> RenderBadge::Create()
{
    return AceType::MakeRefPtr<FlutterRenderBadge>();
}

void FlutterRenderBadge::Paint(RenderContext& context, const Offset& offset)
{
    auto badgeChild = GetChildren().front();
    if (!badgeChild) {
        return;
    }
    context.PaintChild(badgeChild, offset + badgeChildInitialOffset_);
    if (showMessage_) {
        DrawBadge(context, offset);
        if ((!textData_.empty() || messageCount_ > 0) && showMessage_ &&
            (LessOrEqual(textSize_.Height(), badgeHeight_))) {
            PaintText(offset + textInitialOffset_, context);
        }
    }
}

void FlutterRenderBadge::DrawCircleBadge(flutter::Canvas& canvas, const Offset& offset)
{
    flutter::Paint paint;
    paint.paint()->setColor(badgeColor_.GetValue());
    paint.paint()->setStyle(SkPaint::Style::kFill_Style);
    paint.paint()->setAntiAlias(true);
    flutter::RRect rRect;
    flutter::PaintData paintData;
    badgeCircleDiameter_ = badgeCircleSizeDefined_ ? (badgeCircleSize_.IsValid() ? NormalizeToPx(badgeCircleSize_) : 0)
                                                   : NormalizeToPx(CIRCLE_BADGE_SIZE);
    badgeCircleRadius_ = badgeCircleDiameter_ / 2;
    rRect.sk_rrect.setRectXY(
        SkRect::MakeIWH(badgeCircleDiameter_, badgeCircleDiameter_), badgeCircleRadius_, badgeCircleRadius_);
    if (badgePosition_ == BadgePosition::RIGHT_TOP) {
        rRect.sk_rrect.offset(offset.GetX() + width_ - badgeCircleDiameter_, offset.GetY());
    } else if (badgePosition_ == BadgePosition::RIGHT) {
        rRect.sk_rrect.offset(
            offset.GetX() + width_ - badgeCircleDiameter_, offset.GetY() + height_ / 2 - badgeCircleRadius_);
    } else {
        rRect.sk_rrect.offset(offset.GetX(), offset.GetY() + height_ / 2 - badgeCircleRadius_);
    }
    canvas.drawRRect(rRect, paint, paintData);
}

void FlutterRenderBadge::DrawNumericalBadge(flutter::Canvas& canvas, const Offset& offset)
{
    flutter::Paint paint;
    paint.paint()->setColor(badgeColor_.GetValue());
    paint.paint()->setStyle(SkPaint::Style::kFill_Style);
    paint.paint()->setAntiAlias(true);
    flutter::RRect rRect;
    flutter::PaintData paintData;
    textSize_ = CalculateTextSize(textData_, textStyle_, badgeRenderText_);
    badgeCircleDiameter_ = badgeCircleSizeDefined_ ? (badgeCircleSize_.IsValid() ? NormalizeToPx(badgeCircleSize_) : 0)
                                                   : NormalizeToPx(NUMERICAL_BADGE_CIRCLE_SIZE);
    badgeHeight_ = badgeCircleDiameter_;
    if (!textData_.empty() || messageCount_ > 0) {
        if ((textData_.size() <= 1 && textData_.size() > 0) ||
            ((messageCount_ < 10 && messageCount_ <= countLimit_) && textData_.empty())) {
            badgeCircleRadius_ = badgeCircleDiameter_ / 2;
            badgeWidth_ = badgeCircleDiameter_;
        } else if (textData_.size() > 1 || messageCount_ > countLimit_) {
            badgeWidth_ = textSize_.Width() + NormalizeToPx(NUMERICAL_BADGE_PADDING) * 2;
            badgeCircleRadius_ = badgeCircleDiameter_ / 2;
        }
    }
    rRect.sk_rrect.setRectXY(SkRect::MakeIWH(badgeWidth_, badgeHeight_), badgeCircleRadius_, badgeCircleRadius_);
    if (badgePosition_ == BadgePosition::RIGHT_TOP) {
        textInitialOffset_ = Offset(width_ - badgeCircleDiameter_ + NormalizeToPx(2.0_vp), 0 - NormalizeToPx(2.0_vp));
        rRect.sk_rrect.offset(offset.GetX() + textInitialOffset_.GetX(), offset.GetY() + textInitialOffset_.GetY());
    } else if (badgePosition_ == BadgePosition::RIGHT) {
        textInitialOffset_ = Offset(width_ - badgeCircleDiameter_, height_ / 2 - badgeCircleRadius_);
        rRect.sk_rrect.offset(offset.GetX() + textInitialOffset_.GetX(), offset.GetY() + textInitialOffset_.GetY());
    } else {
        textInitialOffset_ = Offset(0, height_ / 2 - badgeCircleRadius_);
        rRect.sk_rrect.offset(offset.GetX(), offset.GetY() + textInitialOffset_.GetY());
    }
    canvas.drawRRect(rRect, paint, paintData);
}

void FlutterRenderBadge::DrawBadge(RenderContext& context, const Offset& offset)
{
    flutter::Canvas* canvas = static_cast<FlutterRenderContext&>(context).GetCanvas();
    if (canvas == nullptr) {
        LOGE("Paint canvas is null");
        return;
    }
    if (!textData_.empty() || messageCount_ > 0) {
        DrawNumericalBadge(*canvas, offset);
    } else {
        DrawCircleBadge(*canvas, offset);
    }
}

void FlutterRenderBadge::PaintText(const Offset& textOffset, RenderContext& context) const
{
    auto textPos = Alignment::GetAlignPosition(Size(badgeWidth_, badgeHeight_), textSize_, Alignment::CENTER);
    if (!badgeRenderText_) {
        return;
    }
    badgeRenderText_->Paint(context, textOffset + textPos);
}

Size FlutterRenderBadge::CalculateTextSize(
    const std::string& text, const TextStyle& textStyle, RefPtr<RenderText>& renderText)
{
    if (!renderText) {
        LOGW("the render text is nullptr");
        return Size();
    }
    renderText->SetTextData(text);
    renderText->SetTextStyle(textStyle);
    renderText->PerformLayout();
    return renderText->GetLayoutSize();
}

} // namespace OHOS::Ace
