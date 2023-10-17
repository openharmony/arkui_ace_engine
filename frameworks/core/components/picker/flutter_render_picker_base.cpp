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

#include "core/components/picker/flutter_render_picker_base.h"

#include "include/effects/SkGradientShader.h"
#include "lib/ui/painting/rrect.h"

namespace OHOS::Ace {
namespace {

const uint32_t SEARCH_MAX_DEPTH = 16;
constexpr Dimension FOCUS_RADIUS = 8.0_vp;
constexpr Dimension FOCUS_BORDER_THICKNESS = 2.0_vp;
constexpr uint32_t FOCUS_BORDER_COLOR = 0xFF0A59F7;

} // namespace

RenderLayer FlutterRenderPickerBase::GetRenderLayer()
{
    if (!layer_) {
        layer_ = AceType::MakeRefPtr<Flutter::GradientLayer>();
    }

    // the alpha rate for disabled is 0.4. 255 * 0.4 = 102. 255 means no alpha.
    layer_->SetAlpha((disabled_ ? 102 : 255));
    return AceType::RawPtr(layer_);
}

Rect FlutterRenderPickerBase::GetOptionsRect(const Offset& offset, const RefPtr<RenderPickerColumn>& pickerColumn)
{
    // Calculate rect of all options.
    double top = offset.GetY() + pickerColumn->GetPosition().GetY();
    double left = offset.GetX() + pickerColumn->GetPosition().GetX() - pickerColumn->GetXOffset();

    // Get pickerColumn's relative position.
    auto parent = pickerColumn->GetParent().Upgrade();
    uint32_t depth = 0;
    while ((parent) && (AceType::RawPtr(parent) != this) && (depth < SEARCH_MAX_DEPTH)) {
        depth++;
        top += parent->GetPosition().GetY();
        left += parent->GetPosition().GetX();
        parent = parent->GetParent().Upgrade();
    }

    // Get first and last options relative position.
    auto bottom = top + pickerColumn->GetLayoutSize().Height();
    return Rect(left, top, columnParent_->GetLayoutSize().Width(), bottom - top);
}

void FlutterRenderPickerBase::Paint(RenderContext& context, const Offset& offset)
{
    if (layer_) {
        layer_->SetOffset(offset.GetX(), offset.GetY());
    }
    RenderNode::Paint(context, offset);
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    if (!data_) {
        return;
    }
    auto theme = data_->GetTheme();
    if (columns_.empty() || !theme || !box_ || !columnParent_) {
        return;
    }
    auto anchorColumn = GetTextDirection() == TextDirection::RTL ? columns_.back() : columns_.front();
    if (!anchorColumn) {
        return;
    }
    auto dividerThickness = NormalizeToPx(theme->GetDividerThickness());
    if (NearZero(dividerThickness) && NearZero(theme->GetGradientHeight().Value())) {
        // No divider and no gradient, directly return.
        return;
    }
    // Draw two dividers on both sides of selected option.
    flutter::Paint paint;
    flutter::PaintData paintData;
    paint.paint()->setColor(theme->GetDividerColor().GetValue());
    auto rect = GetOptionsRect(offset, anchorColumn);
    auto dividerSpacing = NormalizeToPx(theme->GetDividerSpacing());
    if (!NearZero(NormalizeToPx(data_->GetColumnHeight()))) {
        dividerSpacing = NormalizeToPx(data_->GetColumnHeight());
    }
    double upperLine = rect.Top() + rect.Height() / 2.0 - dividerSpacing / 2.0;
    double downLine = rect.Top() + rect.Height() / 2.0 + dividerSpacing / 2.0;
    double leftLine = rect.Left();
    double rightLine = rect.Right();
    if (!NearZero(dividerThickness) && !data_->GetSubsidiary()) {
        canvas->drawRect(leftLine, upperLine - dividerThickness, rightLine, upperLine, paint, paintData);
        canvas->drawRect(leftLine, downLine, rightLine, downLine + dividerThickness, paint, paintData);
    }
    // Paint gradient at top and bottom.
    PaintGradient(canvas, offset, rect, theme);

    // Need to use PipelineContext::ShowFocusAnimation
    PaintFocusOptionBorder(canvas);
}

void FlutterRenderPickerBase::PaintGradient(
    ScopedCanvas& canvas, const Offset& offset, const Rect& rect, const RefPtr<PickerTheme>& theme)
{
    if (data_ && data_->SubsidiaryShowed()) {
        return;
    }

    double gradientHeight = NormalizeToPx(theme->GetGradientHeight());
    if (NearZero(gradientHeight)) {
        return;
    }
    if (data_ && data_->GetIsDialog()) {
        // Paint gradient rect over the picker content.
        flutter::Paint paint;
        flutter::PaintData paintData;
        SkPoint beginPoint = SkPoint::Make(SkDoubleToScalar(rect.Left()), SkDoubleToScalar(rect.Top()));
        SkPoint endPoint = SkPoint::Make(SkDoubleToScalar(rect.Left()), SkDoubleToScalar(rect.Bottom()));
        SkPoint points[2] = { beginPoint, endPoint };
        auto backDecoration = theme->GetPopupDecoration(false);
        Color endColor = backDecoration ? backDecoration->GetBackgroundColor() : Color::WHITE;

        auto renderBox = GetBgColorBox();
        if (data_->GetHasBackgroundColor() && renderBox) {
            endColor = renderBox->GetColor();
        }

        Color middleColor = endColor.ChangeAlpha(0);
        SkColor colors[] = { endColor.GetValue(), middleColor.GetValue(), middleColor.GetValue(), endColor.GetValue() };
        const float stopPositions[] = { 0.0f, gradientHeight / rect.Height(),
            (rect.Height() - gradientHeight) / rect.Height(), 1.0f };

        paint.paint()->setShader(
            SkGradientShader::MakeLinear(points, colors, stopPositions, std::size(colors), SkTileMode::kClamp));
        canvas->drawRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), paint, paintData);
        return;
    }
    // Use layer to apply gradient effect.
    if (!layer_) {
        return;
    }
    layer_->SetGradientRect(rect);
    std::vector<Point> points { Point(0.0, 0.0), Point(0.0, gradientHeight), Point(0.0, rect.Height() - gradientHeight),
        Point(0.0, rect.Height()) };
    std::vector<Color> colors { Color(0x00000000), Color(0xff000000), Color(0xff000000), Color(0x00000000) };
    layer_->SetPoints(points);
    layer_->SetColors(colors);
}

void FlutterRenderPickerBase::PaintFocusOptionBorder(const ScopedCanvas& canvas)
{
    auto pipeline = context_.Upgrade();
    if (!pipeline || !pipeline->GetIsTabKeyPressed()) {
        return;
    }

    for (const auto& column : columns_) {
        if (!column->IsFocused()) {
            continue;
        }

        InitializeSelectedOption(column);
        double focusBorderThickness = NormalizeToPx(FOCUS_BORDER_THICKNESS);
        double focusOffsetX = focusBoxOffset_.GetX() - focusBorderThickness / 2.0;
        double focusOffsetY = focusBoxOffset_.GetY() - focusBorderThickness / 2.0;
        double focusBorderWidth = focusBoxSize_.Width() + focusBorderThickness;
        double focusBorderHeight = focusBoxSize_.Height() + focusBorderThickness;
        double focusRadius = NormalizeToPx(FOCUS_RADIUS);
        flutter::Paint paint;
        flutter::PaintData paintData;
        paint.paint()->setColor(FOCUS_BORDER_COLOR);
        paint.paint()->setStyle(SkPaint::Style::kStroke_Style);
        paint.paint()->setStrokeWidth(focusBorderThickness);
        paint.paint()->setAntiAlias(true);
        flutter::RRect rRect;
        SkRRect rect;
        rect.setRectXY(SkRect::MakeIWH(focusBorderWidth, focusBorderHeight), focusRadius, focusRadius);
        rect.offset(focusOffsetX, focusOffsetY);
        rRect.sk_rrect = rect;
        canvas->drawRRect(rRect, paint, paintData);
        break;
    }
}

} // namespace OHOS::Ace
