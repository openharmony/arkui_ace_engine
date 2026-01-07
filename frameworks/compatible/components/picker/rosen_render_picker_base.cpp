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

#include "compatible/components/picker/rosen_render_picker_base.h"

#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace {
namespace {

const uint32_t SEARCH_MAX_DEPTH = 16;
constexpr Dimension FOCUS_RADIUS = 8.0_vp;
constexpr Dimension FOCUS_BORDER_THICKNESS = 2.0_vp;
constexpr uint32_t FOCUS_BORDER_COLOR = 0xFF0A59F7;

} // namespace

Rect RosenRenderPickerBase::GetOptionsRect(const Offset& offset, const RefPtr<RenderPickerColumn>& pickerColumn)
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

void RosenRenderPickerBase::Paint(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
    if (!canvas || !rsNode) {
        LOGE("Paint canvas is null");
        return;
    }
    rsNode->SetPaintOrder(true);

#ifdef OHOS_PLATFORM
    LOGE("Drawing is not supported");
#endif

    RenderNode::Paint(context, offset);

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
    RSPen pen;
    pen.SetColor(theme->GetDividerColor().GetValue());
    auto rect = GetOptionsRect(offset, anchorColumn);
    auto dividerSpacing = NormalizeToPx(theme->GetDividerSpacing());
    if (data_->GetDefaultHeight()) {
        if (NormalizeToPx(data_->GetColumnHeight()) > 0) {
            if (data_->GetColumnHeight().Unit() == DimensionUnit::PERCENT) {
                dividerSpacing = data_->GetColumnHeight().Value() * dividerSpacing;
            } else {
                dividerSpacing = NormalizeToPx(data_->GetColumnHeight());
            }
        } else {
            dividerSpacing = 0;
        }
    }

    double upperLine = rect.Top() + rect.Height() / 2.0 - dividerSpacing / 2.0;
    double downLine = rect.Top() + rect.Height() / 2.0 + dividerSpacing / 2.0;
    double leftLine = rect.Left();
    double rightLine = rect.Right();

    if (!NearZero(dividerThickness) && !data_->GetSubsidiary()) {
        canvas->AttachPen(pen);
        canvas->DrawRect(RSRect(leftLine, upperLine - dividerThickness, rightLine, upperLine));
        canvas->DrawRect(RSRect(leftLine, downLine, rightLine, downLine + dividerThickness));
        canvas->DetachPen();
    }
    // Paint gradient at top and bottom.
    PaintGradient(canvas, offset, rect, theme);

    // Need to use PipelineContext::ShowFocusAnimation
    PaintFocusOptionBorder(canvas);
}

void RosenRenderPickerBase::PaintGradient(
    RSCanvas* canvas, const Offset& offset, const Rect& rect, const RefPtr<PickerTheme>& theme)
{
    if (data_ && data_->SubsidiaryShowed()) {
        return;
    }

    double gradientHeight = NormalizeToPx(theme->GetGradientHeight());
    if (NearZero(gradientHeight)) {
        return;
    }
    // Paint gradient rect over the picker content.
    RSPen pen;
    RSPoint beginPoint(static_cast<RSScalar>(rect.Left()), static_cast<RSScalar>(rect.Top()));
    RSPoint endPoint(static_cast<RSScalar>(rect.Left()), static_cast<RSScalar>(rect.Bottom()));
    std::vector<RSPoint> points = { beginPoint, endPoint };
    auto backDecoration = theme->GetPopupDecoration(false);
    Color endColor = backDecoration ? backDecoration->GetBackgroundColor() : Color::WHITE;

    auto renderBox = GetBgColorBox();
    if (data_ && data_->GetHasBackgroundColor() && renderBox) {
        endColor = renderBox->GetColor();
    }

    Color middleColor = endColor.ChangeAlpha(0);
    std::vector<RSColorQuad> colors = { endColor.GetValue(), middleColor.GetValue(), middleColor.GetValue(),
        endColor.GetValue() };
    const std::vector<RSScalar> stopPositions = { 0.0, static_cast<RSScalar>(gradientHeight / rect.Height()),
        static_cast<RSScalar>((rect.Height() - gradientHeight) / rect.Height()), 1.0f };
    pen.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(points.at(0), points.at(1), colors, stopPositions, RSTileMode::CLAMP));
    canvas->AttachPen(pen);
    canvas->DrawRect(RSRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom()));
    canvas->DetachPen();
}

void RosenRenderPickerBase::PaintFocusOptionBorder(RSCanvas* canvas)
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
        RSPen pen;
        pen.SetColor(FOCUS_BORDER_COLOR);
        pen.SetWidth(focusBorderThickness);
        pen.SetAntiAlias(true);
        RSRoundRect rRect(RSRect(0, 0, focusBorderWidth, focusBorderHeight), focusRadius, focusRadius);
        rRect.Offset(focusOffsetX, focusOffsetY);
        canvas->AttachPen(pen);
        canvas->DrawRoundRect(rRect);
        canvas->DetachPen();
        break;
    }
}

} // namespace OHOS::Ace
