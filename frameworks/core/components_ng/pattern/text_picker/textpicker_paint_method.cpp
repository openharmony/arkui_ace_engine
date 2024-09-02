/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_picker/textpicker_paint_method.h"

#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr uint8_t DOUBLE = 2;
const Dimension PICKER_DIALOG_DIVIDER_MARGIN = 24.0_vp;
} // namespace

CanvasDrawFunction TextPickerPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    auto frameRect = geometryNode->GetFrameRect();

    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto pickerNode = renderContext->GetHost();
    CHECK_NULL_RETURN(pickerNode, nullptr);
    auto layoutProperty = pickerNode->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);

    auto textPickerPattern = pickerNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, nullptr);
    auto fontScale = textPickerPattern->GetPaintDividerSpacing();

    return
        [weak = WeakClaim(this), layoutProperty, frameRect,
            fontScale, pattern = pattern_](RSCanvas& canvas) {
            auto picker = weak.Upgrade();
            CHECK_NULL_VOID(picker);
            auto textPickerPattern = DynamicCast<TextPickerPattern>(pattern.Upgrade());
            CHECK_NULL_VOID(textPickerPattern);

            PaddingPropertyF padding = layoutProperty->CreatePaddingAndBorder();
            RectF contentRect = { padding.left.value_or(0), padding.top.value_or(0),
                frameRect.Width() - padding.Width(), frameRect.Height() - padding.Height() };

            double dividerHeight = picker->defaultPickerItemHeight_ * fontScale;
            if (textPickerPattern->GetResizeFlag()) {
                dividerHeight = textPickerPattern->GetResizePickerItemHeight() * fontScale;
            }

            if (contentRect.Width() >= 0.0f && (contentRect.Height() >= dividerHeight)) {
                if (textPickerPattern->GetCustomDividerFlag()) {
                    auto divider = textPickerPattern->GetDivider();
                    auto textDirection = layoutProperty->GetNonAutoLayoutDirection();
                    divider.isRtl = (textDirection == TextDirection::RTL) ? true : false;
                    picker->PaintCustomDividerLines(canvas, contentRect, frameRect, divider, dividerHeight);
                } else {
                    picker->PaintDefaultDividerLines(canvas, contentRect, dividerHeight);
                }
            }
        };
}

void TextPickerPaintMethod::PaintCustomDividerLines(RSCanvas& canvas, const RectF &contentRect, const RectF &frameRect,
    const ItemDivider &divider, double dividerHeight)
{
    DividerInfo info;
    if (NeedPaintDividerLines(contentRect, divider, dividerHeight, info)) {
        PaintDividerLines(canvas, contentRect, info, false);
    }
}

void TextPickerPaintMethod::PaintDefaultDividerLines(RSCanvas& canvas, const RectF &contentRect,
    double dividerHeight)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto dividerColor = theme->GetDividerColor();
    auto dividerLineWidth = theme->GetDividerThickness().ConvertToPx();

    auto dividerLength = contentRect.Width();
    auto dividerMargin = contentRect.GetX();
    auto textPickerPattern = DynamicCast<TextPickerPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textPickerPattern);
    if (textPickerPattern->GetIsShowInDialog()) {
        dividerLength -= PICKER_DIALOG_DIVIDER_MARGIN.ConvertToPx() * DOUBLE;
        dividerMargin += PICKER_DIALOG_DIVIDER_MARGIN.ConvertToPx();
    }
    
    DividerInfo info;
    info.dividerColor = dividerColor;
    info.dividerWidth = dividerLineWidth;
    info.dividerLength = dividerLength;
    info.dividerMargin = dividerMargin;
    info.dividerHeight = dividerHeight;
    PaintDividerLines(canvas, contentRect, info);
}

bool TextPickerPaintMethod::SetStrokeWidth(const ItemDivider &divider, double dividerHeight, DividerInfo& info)
{
    if (divider.strokeWidth.ConvertToPx() > dividerHeight / DOUBLE) {
        auto pipeline = PipelineContext::GetCurrentContext();
        if (!pipeline) {
            return false;
        }
        auto theme = pipeline->GetTheme<PickerTheme>();
        if (theme) {
            info.dividerWidth = theme->GetDividerThickness().ConvertToPx();
        } else {
            info.dividerWidth = 0.0f;
        }
    } else {
        info.dividerWidth = divider.strokeWidth.ConvertToPx();
    }

    if (info.dividerWidth <= 0.0f) {
        return false;
    }
    return true;
}

bool TextPickerPaintMethod::NeedPaintDividerLines(const RectF &contentRect, const ItemDivider &divider,
    double dividerHeight, DividerInfo& info)
{
    if (!SetStrokeWidth(divider, dividerHeight, info)) {
        return false;
    }
    info.dividerHeight = dividerHeight;
    info.startMargin = std::max(0.0, divider.startMargin.ConvertToPx());
    info.endMargin = std::max(0.0, divider.endMargin.ConvertToPx());
    info.dividerColor = divider.color;

    auto dividerLength = contentRect.Width();
    auto dividerMargin = contentRect.GetX();
    auto textPickerPattern = DynamicCast<TextPickerPattern>(pattern_.Upgrade());
    if (!textPickerPattern) {
        return false;
    }
    if (textPickerPattern->GetIsShowInDialog()) {
        dividerLength -= PICKER_DIALOG_DIVIDER_MARGIN.ConvertToPx() * DOUBLE;
        dividerMargin += PICKER_DIALOG_DIVIDER_MARGIN.ConvertToPx();
    }

    float checkMargin = dividerLength - info.startMargin - info.endMargin;
    if (NearZero(checkMargin)) {
        return false;
    }
    if (LessNotEqual(checkMargin, 0.0f)) {
        LOGE("StartMagin and endMargin are set to 0, because the parameters are wrong");
        info.startMargin = 0.0f;
        info.endMargin = 0.0f;
    }
    if (divider.isRtl) {
        dividerMargin += info.endMargin;
    } else {
        dividerMargin += info.startMargin;
    }
    dividerLength = dividerLength - info.startMargin - info.endMargin;
    info.dividerMargin = dividerMargin;
    info.dividerLength = dividerLength;
    return true;
}

void TextPickerPaintMethod::PaintDividerLines(RSCanvas& canvas, const RectF& contentRect, const DividerInfo &info,
    bool isDefaultLine)
{
    double upperLine = 0.0f;
    double downLine = 0.0f;
    if (isDefaultLine) {
        upperLine = (contentRect.Height() - info.dividerHeight) / DOUBLE + contentRect.GetY();
        downLine = (contentRect.Height() + info.dividerHeight) / DOUBLE + contentRect.GetY();
    } else {
        upperLine = (contentRect.Height() - info.dividerHeight - info.dividerWidth) / DOUBLE + contentRect.GetY();
        downLine = (contentRect.Height() + info.dividerHeight  - info.dividerWidth) / DOUBLE + contentRect.GetY();
    }
    OffsetF offset = OffsetF(info.dividerMargin, upperLine);
    PaintLine(offset, info, canvas);
    OffsetF offsetY = OffsetF(info.dividerMargin, downLine);
    PaintLine(offsetY, info, canvas);
}

void TextPickerPaintMethod::PaintLine(const OffsetF& offset, const DividerInfo &info, RSCanvas& canvas)
{
    canvas.Save();
    RSBrush brush;
    brush.SetColor(info.dividerColor.GetValue());
    canvas.AttachBrush(brush);
    
    auto startPointX = offset.GetX();
    auto startPointY = offset.GetY();
    auto endPointX = offset.GetX() + info.dividerLength;
    auto endPointY = offset.GetY() + info.dividerWidth;

    canvas.DrawRect(RSRect(startPointX, startPointY, endPointX, endPointY));
    canvas.DetachBrush();
    canvas.Restore();
}

} // namespace OHOS::Ace::NG
