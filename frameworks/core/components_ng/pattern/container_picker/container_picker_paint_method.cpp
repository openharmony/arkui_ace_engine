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

#include "core/components_ng/pattern/container_picker/container_picker_paint_method.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/container_picker/container_picker_theme.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction ContainerPickerPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto painter = weak.Upgrade();
        CHECK_NULL_VOID(painter);
        painter->ClipPadding(paintWrapper, canvas);
        painter->PaintSelectionIndicatorBackground(paintWrapper, canvas);
    };

    return paintFunc;
}

CanvasDrawFunction ContainerPickerPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto painter = weak.Upgrade();
        CHECK_NULL_VOID(painter);
        painter->PaintSelectionIndicatorDivider(paintWrapper, canvas);
    };

    return paintFunc;
}

void ContainerPickerPaintMethod::ClipPadding(PaintWrapper* paintWrapper, RSCanvas& canvas) const
{
    CHECK_NULL_VOID(paintWrapper);
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetPaddingSize();
    frameSize.AddWidth(safeAreaPadding_.left.value_or(0.0f) + safeAreaPadding_.right.value_or(0.0f));
    OffsetF paddingOffset = geometryNode->GetPaddingOffset() - geometryNode->GetFrameOffset() -
                            OffsetF(safeAreaPadding_.left.value_or(0.0f), 0.0f);
    auto renderContext = paintWrapper->GetRenderContext();
    if (!renderContext || renderContext->GetClipEdge().value_or(true)) {
        auto clipRect = RSRect(paddingOffset.GetX(), paddingOffset.GetY(), frameSize.Width() + paddingOffset.GetX(),
            paddingOffset.GetY() + frameSize.Height());
        canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
    }
}

void ContainerPickerPaintMethod::PaintSelectionIndicatorBackground(PaintWrapper* paintWrapper, RSCanvas& canvas) const
{
    CHECK_NULL_VOID(paintWrapper);
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pickerNode = renderContext->GetHost();
    CHECK_NULL_VOID(pickerNode);
    auto pipelineContext = pickerNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ContainerPickerTheme>();
    CHECK_NULL_VOID(theme);
    auto layoutProperty = pickerNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (layoutProperty->GetIndicatorType() == static_cast<int32_t>(PickerIndicatorType::DIVIDER)) {
        return;
    }
    auto pickerGeometryNode = pickerNode->GetGeometryNode();
    CHECK_NULL_VOID(pickerGeometryNode);
    auto pickerRect = pickerGeometryNode->GetFrameRect();
    Color backgroundColor =
            layoutProperty->GetIndicatorBackgroundColor().value_or(theme->GetIndicatorBackgroundColor());
    BorderRadiusProperty borderRadius = layoutProperty->GetIndicatorBorderRadius().value_or(
        BorderRadiusProperty(theme->GetIndicatorBackgroundRadius()));
    SetDefaultIndicatorBackground(pickerNode, backgroundColor, borderRadius);

    float height = PICKER_ITEM_HEIGHT.ConvertToPx();
    float width = pickerRect.Width();
    float maxRadius = std::min(height, width) / 2;
    float left = 0.0f;
    float top = pickerRect.Height() / 2 - height / 2;
    auto topLeft = GreatNotEqual(borderRadius.radiusTopLeft->ConvertToPx(), maxRadius) ?
        maxRadius : borderRadius.radiusTopLeft->ConvertToPx();
    auto topRight = GreatNotEqual(borderRadius.radiusTopRight->ConvertToPx(), maxRadius) ?
        maxRadius : borderRadius.radiusTopRight->ConvertToPx();
    auto bottomLeft = GreatNotEqual(borderRadius.radiusBottomLeft->ConvertToPx(), maxRadius) ?
        maxRadius : borderRadius.radiusBottomLeft->ConvertToPx();
    auto bottomRight = GreatNotEqual(borderRadius.radiusBottomRight->ConvertToPx(), maxRadius) ?
        maxRadius : borderRadius.radiusBottomRight->ConvertToPx();

    canvas.Save();
    RSBrush brush;
    brush.SetColor(backgroundColor.GetValue());
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    std::vector<RSPoint> radiusXY = { RSPoint(topLeft, topLeft), RSPoint(topRight, topRight),
        RSPoint(bottomRight, bottomRight), RSPoint(bottomLeft, bottomLeft) };
    RSRoundRect result (RSRect(left, top, left + width, top + height), radiusXY);
    canvas.DrawRoundRect(result);
    canvas.DetachBrush();
    canvas.Restore();
}

void ContainerPickerPaintMethod::PaintSelectionIndicatorDivider(PaintWrapper* paintWrapper, RSCanvas& canvas) const
{
    CHECK_NULL_VOID(paintWrapper);
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pickerNode = renderContext->GetHost();
    CHECK_NULL_VOID(pickerNode);
    auto pipelineContext = pickerNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ContainerPickerTheme>();
    CHECK_NULL_VOID(theme);
    auto layoutProperty = pickerNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (layoutProperty->GetIndicatorType() != static_cast<int32_t>(PickerIndicatorType::DIVIDER)) {
        return;
    }
    auto pickerGeometryNode = pickerNode->GetGeometryNode();
    CHECK_NULL_VOID(pickerGeometryNode);
    auto pickerRect = pickerGeometryNode->GetFrameRect();
    auto strokeWidth = layoutProperty->GetIndicatorDividerWidth().value_or(theme->GetStrokeWidth()).ConvertToPx();
    if (GreatNotEqual(strokeWidth, PICKER_ITEM_HEIGHT.ConvertToPx() / HALF)) {
        strokeWidth = theme->GetStrokeWidth().ConvertToPx();
    }
    auto dividerColor = layoutProperty->GetIndicatorDividerColor().value_or(theme->GetIndicatorDividerColor());
    auto startMargin = layoutProperty->GetIndicatorStartMargin().value_or(Dimension()).ConvertToPx();
    auto endMargin = layoutProperty->GetIndicatorEndMargin().value_or(Dimension()).ConvertToPx();
    SetDefaultIndicatorDivider(pickerNode, strokeWidth, dividerColor, startMargin, endMargin);

    PaddingPropertyF padding = layoutProperty->CreatePaddingAndBorder();
    RectF contentRect = { padding.left.value_or(0), padding.top.value_or(0),
        pickerRect.Width() - padding.Width(), pickerRect.Height() - padding.Height() };
    auto dividerLength = contentRect.Width();
    CheckMarginAndLength(dividerLength, startMargin, endMargin);
    if (GreatOrEqual(contentRect.Height(), PICKER_ITEM_HEIGHT.ConvertToPx()) && GreatNotEqual(strokeWidth, 0.0)) {
        PickerDividerPaintInfo dividerInfo;
        dividerInfo.dividerColor = dividerColor;
        dividerInfo.dividerLength = dividerLength;
        dividerInfo.strokeWidth = strokeWidth;
        double upperLine = (contentRect.Height() - PICKER_ITEM_HEIGHT.ConvertToPx()) / 2
                                + contentRect.GetY() - strokeWidth / 2;
        double downLine = (contentRect.Height() + PICKER_ITEM_HEIGHT.ConvertToPx()) / 2
                                + contentRect.GetY() - strokeWidth / 2;

        OffsetF upperOffset = OffsetF(contentRect.GetX() + startMargin, upperLine);
        PaintLine(upperOffset, dividerInfo, canvas);
        OffsetF downOffset = OffsetF(contentRect.GetX() + startMargin, downLine);
        PaintLine(downOffset, dividerInfo, canvas);
    }
}

void ContainerPickerPaintMethod::CheckMarginAndLength(float& length, double& startMargin, double& endMargin) const
{
    if (GreatNotEqual(startMargin + endMargin, length)) {
        startMargin = 0.0;
        endMargin = 0.0;
    }
    length = length - startMargin - endMargin;
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        std::swap(startMargin, endMargin);
    }
}

void ContainerPickerPaintMethod::SetDefaultIndicatorBackground(RefPtr<FrameNode> pickerNode,
    Color& backgroundColor, BorderRadiusProperty& borderRadius) const
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto pickerPattern = pickerNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    auto pipelineContext = pickerNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ContainerPickerTheme>();
    CHECK_NULL_VOID(theme);
    PickerIndicatorStyle style = pickerPattern->GetIndicatorStyleVal();
    if (style.isDefaultBackgroundColor) {
        backgroundColor = theme->GetIndicatorBackgroundColor();
    }
    if (style.isDefaultBorderRadius) {
        borderRadius = BorderRadiusProperty(theme->GetIndicatorBackgroundRadius());
    }
}

void ContainerPickerPaintMethod::SetDefaultIndicatorDivider(RefPtr<FrameNode> pickerNode, double& strokeWidth,
    Color& dividerColor, double& startMargin, double& endMargin) const
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto pickerPattern = pickerNode->GetPattern<ContainerPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    auto pipelineContext = pickerNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ContainerPickerTheme>();
    CHECK_NULL_VOID(theme);
    PickerIndicatorStyle style = pickerPattern->GetIndicatorStyleVal();
    if (style.isDefaultDividerWidth) {
        strokeWidth = theme->GetStrokeWidth().ConvertToPx();
    }
    if (style.isDefaultDividerColor) {
        dividerColor = theme->GetIndicatorDividerColor();
    }
    if (style.isDefaultStartMargin) {
        startMargin = Dimension().ConvertToPx();
    }
    if (style.isDefaultEndMargin) {
        endMargin = Dimension().ConvertToPx();
    }
}

void ContainerPickerPaintMethod::PaintLine(const OffsetF& offset, const PickerDividerPaintInfo &dividerInfo,
    RSCanvas& canvas) const
{
    canvas.Save();
    RSBrush brush;
    brush.SetColor(dividerInfo.dividerColor.GetValue());
    canvas.AttachBrush(brush);

    auto startPointX = offset.GetX();
    auto startPointY = offset.GetY();
    auto endPointX = offset.GetX() + dividerInfo.dividerLength;
    auto endPointY = offset.GetY() + dividerInfo.strokeWidth;

    canvas.DrawRect(RSRect(startPointX, startPointY, endPointX, endPointY));
    canvas.DetachBrush();
    canvas.Restore();
}

} // namespace OHOS::Ace::NG
