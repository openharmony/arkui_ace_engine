/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_field/text_field_overlay_modifier.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/image_painter.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float MAGNIFIER_GAIN = 1.25f;
constexpr Dimension MAGNIFIER_WIDTH = 140.0_vp;
constexpr Dimension MAGNIFIER_HEIGHT = 48.0_vp;
constexpr Dimension MAGNIFIER_OFFSET_Y = 4.0_vp;
constexpr Dimension PIXEL_MAP_IMAGE_OFFSET = 4.0_vp;
constexpr Dimension CLOSE_MAGNIFIER_MAX_OFFSET_X = 70.0_vp;
constexpr Dimension MAGNIFIER_BOUNDRY_WIDTH = 1.0_vp;
constexpr Dimension DEFAULT_STATUS_BAR_HEIGHT = 48.0_vp;
} // namespace

TextFieldOverlayModifier::TextFieldOverlayModifier(
    const WeakPtr<OHOS::Ace::NG::Pattern>& pattern, WeakPtr<ScrollEdgeEffect>&& edgeEffect)
    : pattern_(pattern), edgeEffect_(edgeEffect)
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_VOID(theme);
    cursorColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color()));
    cursorWidth_ =
        AceType::MakeRefPtr<AnimatablePropertyFloat>(static_cast<float>(theme->GetCursorWidth().ConvertToPx()));
    selectedColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color()));
    cursorVisible_ = AceType::MakeRefPtr<PropertyBool>(false);
    showSelect_ = AceType::MakeRefPtr<PropertyBool>(false);
    contentSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    contentOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    cursorOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(textFieldPattern->GetCaretOffset());
    frameSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    currentOffset_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    underlineWidth_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    underlineColor_ = AceType::MakeRefPtr<PropertyColor>(Color());
    changeSelectedRects_ = AceType::MakeRefPtr<PropertyBool>(false);
    firstHandleOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    secondHandleOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());

    AttachProperty(cursorColor_);
    AttachProperty(cursorWidth_);
    AttachProperty(selectedColor_);
    AttachProperty(cursorVisible_);
    AttachProperty(showSelect_);
    AttachProperty(contentSize_);
    AttachProperty(contentOffset_);
    AttachProperty(cursorOffset_);
    AttachProperty(frameSize_);
    AttachProperty(currentOffset_);
    AttachProperty(underlineWidth_);
    AttachProperty(underlineColor_);
    AttachProperty(changeSelectedRects_);
    AttachProperty(firstHandleOffset_);
    AttachProperty(secondHandleOffset_);
}

void TextFieldOverlayModifier::SetFirstHandleOffset(const OffsetF& offset)
{
    firstHandleOffset_->Set(offset);
}

void TextFieldOverlayModifier::SetSecondHandleOffset(const OffsetF& offset)
{
    secondHandleOffset_->Set(offset);
}

void TextFieldOverlayModifier::onDraw(DrawingContext& context)
{
    auto& canvas = context.canvas;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        canvas.Save();
        RSRect clipRect;
        std::vector<RSPoint> clipRadius;
        GetFrameRectClip(clipRect, clipRadius);
        canvas.ClipRoundRect(clipRect, clipRadius, true);
    }
    PaintCursor(context);
    PaintSelection(context);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        canvas.Restore();
    }
    PaintScrollBar(context);
    PaintEdgeEffect(frameSize_->Get(), context.canvas);
    PaintUnderline(context.canvas);
    PaintMagnifier(context);
}

void TextFieldOverlayModifier::GetFrameRectClip(RSRect& clipRect, std::vector<RSPoint>& clipRadius)
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto textFrameRect = textFieldPattern->GetFrameRect();
    clipRect = RSRect(0.0f, 0.0f, textFrameRect.Width(), textFrameRect.Height());
    auto radius = renderContext->GetBorderRadius().value_or(BorderRadiusProperty());
    auto radiusTopLeft = RSPoint(static_cast<float>(radius.radiusTopLeft.value_or(0.0_vp).ConvertToPx()),
        static_cast<float>(radius.radiusTopLeft.value_or(0.0_vp).ConvertToPx()));
    clipRadius.emplace_back(radiusTopLeft);
    auto radiusTopRight = RSPoint(static_cast<float>(radius.radiusTopRight.value_or(0.0_vp).ConvertToPx()),
        static_cast<float>(radius.radiusTopRight.value_or(0.0_vp).ConvertToPx()));
    clipRadius.emplace_back(radiusTopRight);
    auto radiusBottomRight = RSPoint(static_cast<float>(radius.radiusBottomRight.value_or(0.0_vp).ConvertToPx()),
        static_cast<float>(radius.radiusBottomRight.value_or(0.0_vp).ConvertToPx()));
    clipRadius.emplace_back(radiusBottomRight);
    auto radiusBottomLeft = RSPoint(static_cast<float>(radius.radiusBottomLeft.value_or(0.0_vp).ConvertToPx()),
        static_cast<float>(radius.radiusBottomLeft.value_or(0.0_vp).ConvertToPx()));
    clipRadius.emplace_back(radiusBottomLeft);
}

void TextFieldOverlayModifier::PaintUnderline(RSCanvas& canvas) const
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!(layoutProperty->GetShowUnderlineValue(false) && textFieldPattern->IsUnspecifiedOrTextType())) {
        return;
    }
    if (textFieldPattern->IsNormalInlineState() && textFieldPattern->HasFocus()) {
        return;
    }
    auto contentRect = textFieldPattern->GetContentRect();
    auto textFrameRect = textFieldPattern->GetFrameRect();
    auto responseArea = textFieldPattern->GetResponseArea();
    Point leftPoint, rightPoint;
    if (layoutProperty->GetShowCounterValue(false)) {
        leftPoint.SetX(contentRect.Left());
        leftPoint.SetY(textFrameRect.Height());
        rightPoint.SetX(contentRect.Right());
        rightPoint.SetY(textFrameRect.Height());
    } else {
        auto responseAreaWidth = responseArea ? responseArea->GetAreaRect().Width() : 0.0f;
        leftPoint.SetX(contentRect.Left());
        leftPoint.SetY(textFrameRect.Height());
        rightPoint.SetX(contentRect.Right() + responseAreaWidth);
        rightPoint.SetY(textFrameRect.Height());
    }
    RSPen pen;
    pen.SetColor(ToRSColor(underlineColor_->Get()));
    pen.SetWidth(underlineWidth_->Get());
    pen.SetAntiAlias(true);
    canvas.AttachPen(pen);
    canvas.DrawLine(
        ToRSPoint(PointF(leftPoint.GetX(), leftPoint.GetY())), ToRSPoint(PointF(rightPoint.GetX(), rightPoint.GetY())));
    canvas.DetachPen();
}

void TextFieldOverlayModifier::PaintSelection(DrawingContext& context) const
{
    if (!showSelect_->Get() && !needPaintSelect_) {
        return;
    }
    auto& canvas = context.canvas;
    canvas.Save();
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<TextFieldTheme>();
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(selectedColor_->Get()));
    canvas.AttachBrush(brush);
    auto paintOffset = textFieldPattern->GetContentRect().GetOffset();
    auto textBoxes = textFieldPattern->GetTextBoxes();
    auto textRect = textFieldPattern->GetTextRect();
    bool isTextArea = textFieldPattern->IsTextArea();
    float clipRectHeight = 0.0f;
    clipRectHeight = paintOffset.GetY() + contentSize_->Get().Height();
    RSRect clipInnerRect;
    auto defaultStyle = !textFieldPattern->IsNormalInlineState() || isTextArea;
    if (defaultStyle) {
        clipInnerRect = RSRect(paintOffset.GetX(), paintOffset.GetY(),
            paintOffset.GetX() + contentSize_->Get().Width() + textFieldPattern->GetInlinePadding(), clipRectHeight);
        canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    } else {
        clipInnerRect = RSRect(paintOffset.GetX(), 0.0f, paintOffset.GetX() + contentSize_->Get().Width(),
            textFieldPattern->GetFrameRect().Height());
        canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    }
    // for default style, selection height is equal to the content height
    for (const auto& textBox : textBoxes) {
        canvas.DrawRect(RSRect(textBox.Left() + (isTextArea ? contentOffset_->Get().GetX() : textRect.GetX()),
            defaultStyle
                ? (textBox.Top() + (isTextArea ? textRect.GetY() : contentOffset_->Get().GetY()))
                : 0.0f,
            textBox.Right() + (isTextArea ? contentOffset_->Get().GetX() : textRect.GetX()),
            defaultStyle
                ? (textBox.Bottom() + (isTextArea ? textRect.GetY() : contentOffset_->Get().GetY()))
                         : textFieldPattern->GetFrameRect().Height()));
    }
    canvas.DetachBrush();
    canvas.Restore();
}

void TextFieldOverlayModifier::PaintCursor(DrawingContext& context) const
{
    auto& canvas = context.canvas;
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    if (textFieldPattern->GetShowMagnifier()) {
        cursorVisible_->Set(true);
    }
    if (!cursorVisible_->Get() || textFieldPattern->GetSelectMode() == SelectionMode::SELECT_ALL) {
        return;
    }
    canvas.Save();
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(cursorColor_->Get()));
    canvas.AttachBrush(brush);
    auto paintOffset = contentOffset_->Get();
    float clipRectHeight = 0.0f;
    clipRectHeight = paintOffset.GetY() + contentSize_->Get().Height();
    RSRect clipInnerRect(paintOffset.GetX(), paintOffset.GetY(),
        // add extra clip space for cases such as auto width
        paintOffset.GetX() + contentSize_->Get().Width() +
            (LessOrEqual(contentSize_->Get().Width(), 0.0) ? cursorWidth_->Get() : 0.0f),
        clipRectHeight);
    canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    auto caretRect = textFieldPattern->GetCaretRect();
    canvas.DrawRect(RSRect(caretRect.GetX(), caretRect.GetY(),
        caretRect.GetX() + (static_cast<float>(cursorWidth_->Get())), caretRect.GetY() + caretRect.Height()));
    canvas.DetachBrush();
    canvas.Restore();
}

void TextFieldOverlayModifier::PaintEdgeEffect(const SizeF& frameSize, RSCanvas& canvas)
{
    auto edgeEffect = edgeEffect_.Upgrade();
    CHECK_NULL_VOID(edgeEffect);
    edgeEffect->Paint(canvas, frameSize, { 0.0f, 0.0f });
}

void TextFieldOverlayModifier::PaintScrollBar(DrawingContext& context)
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    if (textFieldPattern->GetScrollBarVisible() && textFieldPattern->IsTextArea()) {
        ScrollBarOverlayModifier::onDraw(context);
    }
}

void TextFieldOverlayModifier::PaintMagnifier(DrawingContext& context)
{
    auto pattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    magnifierRect_ = pattern->GetMagnifierRect();
    if (!magnifierRect_.isChildNode) {
        return;
    }
    auto pixelMap = magnifierRect_.pixelMap;
    CHECK_NULL_VOID(pixelMap);
    auto& canvas = context.canvas;
    canvas.Save();

    auto cursorOffsetY = magnifierRect_.cursorOffset.GetY();
    auto localOffsetX = magnifierRect_.localOffset.GetX();
    if (!GetMagnifierRect(magnifierRect_.startX, magnifierRect_.startY, magnifierRect_.endX, magnifierRect_.endY,
        localOffsetX, cursorOffsetY)) {
        return;
    }

    RSBrush brush;
    brush.SetColor(RSColor::COLOR_WHITE);
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);

    std::vector<TextPoint> drawPathPoints =
        GetTextPoints(magnifierRect_.startX, magnifierRect_.startY, magnifierRect_.endX, magnifierRect_.endY, false);
    auto drawPath = GetPathByPoints(drawPathPoints);
    PaintShadow(*drawPath, ShadowConfig::DefaultShadowM, canvas);
    canvas.DrawPath(*drawPath);
    std::vector<TextPoint> clipPathPoints =
        GetTextPoints(magnifierRect_.startX, magnifierRect_.startY, magnifierRect_.endX, magnifierRect_.endY, false);
    auto clipPath = GetPathByPoints(clipPathPoints);
    canvas.ClipPath(*clipPath, RSClipOp::INTERSECT, true);

    auto magnifierGain = MAGNIFIER_GAIN;
    auto pixelMapImageOffset = PIXEL_MAP_IMAGE_OFFSET.ConvertToPx();

    PixelMapImage pixelMapImage(pixelMap);
    auto magnifierPaintConfig = pixelMapImage.GetPaintConfig();
    magnifierPaintConfig.scaleX_ = magnifierGain;
    magnifierPaintConfig.scaleY_ = magnifierGain;
    pixelMapImage.SetPaintConfig(magnifierPaintConfig);

    RectF dstRect;
    dstRect.SetRect(localOffsetX - localOffsetX * magnifierGain - pattern->GetTextPaintOffset().GetX() * magnifierGain,
        magnifierRect_.startY - pattern->GetTextPaintOffset().GetY() * magnifierGain - cursorOffsetY * magnifierGain +
            pixelMapImageOffset,
        pixelMap->GetWidth() * magnifierGain, pixelMap->GetHeight() * magnifierGain);
    pixelMapImage.DrawRect(canvas, ToRSRect(dstRect));

    canvas.DetachBrush();
    canvas.Restore();
}

bool TextFieldOverlayModifier::GetMagnifierRect(
    float& startX, float& startY, float& endX, float& endY, float& localOffsetX, float& cursorOffsetY)
{
    auto pattern = DynamicCast<TextFieldPattern>(magnifierRect_.parent.Upgrade());
    CHECK_NULL_RETURN(pattern, false);
    auto cursorOffsetX = magnifierRect_.cursorOffset.GetX();
    auto magnifierWidth = MAGNIFIER_WIDTH.ConvertToPx();
    auto magnifierHeight = MAGNIFIER_HEIGHT.ConvertToPx();
    auto magnifierOffsetY = MAGNIFIER_OFFSET_Y.ConvertToPx();
    auto closeMagnifierMaxOffsetX = CLOSE_MAGNIFIER_MAX_OFFSET_X.ConvertToPx();
    auto localOffsetY = magnifierRect_.localOffset.GetY();
    localOffsetX = std::max(localOffsetX, magnifierRect_.contentOffset.GetX());
    localOffsetX = std::min(localOffsetX, magnifierRect_.contentSize.Width() + magnifierRect_.contentOffset.GetX());
    auto textBoxesLeft = 0.0f;
    if (!pattern->GetTextBoxes().empty()) {
        textBoxesLeft = pattern->GetTextBoxes()[0].Left();
    }
    if (std::abs(localOffsetX - cursorOffsetX) > closeMagnifierMaxOffsetX &&
        std::abs(localOffsetX - textBoxesLeft) > closeMagnifierMaxOffsetX) {
        return false;
    }
    startX = localOffsetX - magnifierWidth / 2.0f;
    if (pattern->GetCaretIndex() == pattern->GetContentWideTextLength() && localOffsetX >= cursorOffsetX) {
        startX = cursorOffsetX - magnifierWidth / 2.0f;
        localOffsetX = cursorOffsetX;
    }
    auto firstHandleOffsetY = pattern->GetTextSelectController()->GetFirstHandleOffset().GetY();
    auto secondHandleOffsetY = pattern->GetTextSelectController()->GetSecondHandleOffset().GetY();
    if (pattern->IsSelected() && firstHandleOffsetY != secondHandleOffsetY &&
        localOffsetY < firstHandleOffsetY + pattern->GetLineHeight() &&
        localOffsetY < secondHandleOffsetY + pattern->GetLineHeight()) {
        if (firstHandleOffsetY < secondHandleOffsetY) {
            cursorOffsetY = firstHandleOffsetY;
        } else if (secondHandleOffsetY < firstHandleOffsetY) {
            cursorOffsetY = secondHandleOffsetY;
        }
    }
    startY = cursorOffsetY - magnifierHeight - magnifierOffsetY;
    if ((pattern->GetParentGlobalOffset().GetY() + startY) < DEFAULT_STATUS_BAR_HEIGHT.ConvertToPx()) {
        startY = cursorOffsetY + pattern->GetLineHeight() + magnifierHeight + magnifierOffsetY;
    }
    startX = std::max(startX, 0.0f);
    endX = startX + magnifierWidth;
    endY = startY;
    if (endX > magnifierRect_.contentSize.Width() + magnifierRect_.contentOffset.GetX() * 2.0f) {
        endX = magnifierRect_.contentSize.Width() + magnifierRect_.contentOffset.GetX() * 2.0f;
        startX = endX - magnifierWidth;
    }
    return true;
}

std::vector<TextPoint> TextFieldOverlayModifier::GetTextPoints(
    float startX, float startY, float endX, float endY, bool haveOffset)
{
    std::vector<TextPoint> textPoints;
    auto lineHeight = MAGNIFIER_HEIGHT.ConvertToPx();
    auto offset = MAGNIFIER_BOUNDRY_WIDTH.ConvertToPx();
    if (haveOffset) {
        textPoints.emplace_back(TextPoint(startX - offset, startY - offset));
        textPoints.emplace_back(TextPoint(endX + offset, endY - offset));
        textPoints.emplace_back(TextPoint(endX + offset, endY + lineHeight + offset));
        textPoints.emplace_back(TextPoint(startX - offset, endY + lineHeight + offset));
        textPoints.emplace_back(TextPoint(startX - offset, endY - offset));
        textPoints.emplace_back(TextPoint(endX + offset, endY - offset));
        return textPoints;
    }
    textPoints.emplace_back(TextPoint(startX, startY));
    textPoints.emplace_back(TextPoint(endX, endY));
    textPoints.emplace_back(TextPoint(endX, endY + lineHeight));
    textPoints.emplace_back(TextPoint(startX, endY + lineHeight));
    textPoints.emplace_back(TextPoint(startX, endY));
    textPoints.emplace_back(TextPoint(endX, endY));
    return textPoints;
}

std::shared_ptr<RSPath> TextFieldOverlayModifier::GetPathByPoints(std::vector<TextPoint> points)
{
    std::shared_ptr<RSPath> path = std::make_shared<RSPath>();
    auto radius = MAGNIFIER_HEIGHT.ConvertToPx() / 2.0f;
    path->MoveTo(points[0].x + radius, points[0].y);
    size_t step = 2;
    for (size_t i = 0; i + step < points.size(); i++) {
        auto firstPoint = points[i];
        auto crossPoint = points[i + 1];
        auto secondPoint = points[i + step];

        if (crossPoint.y == firstPoint.y) {
            int32_t directionX = (crossPoint.x - firstPoint.x) > 0 ? 1 : -1;
            int32_t directionY = (secondPoint.y - crossPoint.y) > 0 ? 1 : -1;
            auto direction =
                (directionX * directionY > 0) ? RSPathDirection::CW_DIRECTION : RSPathDirection::CCW_DIRECTION;
            path->LineTo(crossPoint.x - radius * directionX, crossPoint.y);
            path->ArcTo(radius, radius, 0.0f, direction, crossPoint.x, crossPoint.y + radius * directionY);
        } else {
            int32_t directionX = (secondPoint.x - crossPoint.x) > 0 ? 1 : -1;
            int32_t directionY = (crossPoint.y - firstPoint.y) > 0 ? 1 : -1;
            auto direction =
                (directionX * directionY < 0) ? RSPathDirection::CW_DIRECTION : RSPathDirection::CCW_DIRECTION;
            path->LineTo(crossPoint.x, crossPoint.y - radius * directionY);
            path->ArcTo(radius, radius, 0.0f, direction, crossPoint.x + radius * directionX, secondPoint.y);
        }
    }
    return path;
}
void TextFieldOverlayModifier::PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas& canvas)
{
    canvas.Save();
#ifndef USE_ROSEN_DRAWING
    RSPath rsPath = path;
#else
    RSRecordingPath rsPath;
    rsPath.AddPath(path);
#endif
    rsPath.Offset(shadow.GetOffset().GetX(), shadow.GetOffset().GetY());
    RSColor spotColor = ToRSColor(shadow.GetColor());
    RSPoint3 planeParams = { 0.0f, 0.0f, shadow.GetElevation() };
#ifndef USE_ROSEN_DRAWING
    RSPoint3 lightPos = { rsPath.GetBounds().GetLeft() / 2 + rsPath.GetBounds().GetRight(),
        rsPath.GetBounds().GetTop() / 2.0 + rsPath.GetBounds().GetBottom() / 2.0, shadow.GetLightHeight() };
#else
    auto bounds = rsPath.GetBounds();
    RSPoint3 lightPos = { bounds.GetLeft() / 2.0 + bounds.GetRight() / 2.0,
        bounds.GetTop() / 2.0 + bounds.GetBottom() / 2.0, shadow.GetLightHeight() };
#endif
    RSColor ambientColor = RSColor(0, 0, 0, 0);
    canvas.DrawShadow(rsPath, planeParams, lightPos, shadow.GetLightRadius(), ambientColor, spotColor,
        RSShadowFlags::TRANSPARENT_OCCLUDER);
    canvas.Restore();
}

void TextFieldOverlayModifier::SetCursorColor(Color& value)
{
    cursorColor_->Set(LinearColor(value));
}

void TextFieldOverlayModifier::SetCursorWidth(float value)
{
    cursorWidth_->Set(value);
}

void TextFieldOverlayModifier::SetSelectedBackGroundColor(Color& value)
{
    selectedColor_->Set(LinearColor(value));
}

void TextFieldOverlayModifier::SetCursorVisible(bool value)
{
    cursorVisible_->Set(value);
}

void TextFieldOverlayModifier::SetContentSize(SizeF& value)
{
    contentSize_->Set(value);
}

void TextFieldOverlayModifier::SetContentOffset(OffsetF& value)
{
    contentOffset_->Set(value);
}

void TextFieldOverlayModifier::SetCursorOffset(const OffsetF& value)
{
    cursorOffset_->Set(value);
}

void TextFieldOverlayModifier::SetInputStyle(InputStyle& value)
{
    inputStyle_ = value;
}

void TextFieldOverlayModifier::SetFrameSize(const SizeF& value)
{
    frameSize_->Set(value);
}

void TextFieldOverlayModifier::SetCurrentOffset(float value)
{
    currentOffset_->Set(value);
}

void TextFieldOverlayModifier::SetUnderlineWidth(float value)
{
    underlineWidth_->Set(value);
}

void TextFieldOverlayModifier::SetUnderlineColor(const Color& value)
{
    underlineColor_->Set(value);
}

void TextFieldOverlayModifier::SetScrollBar(const RefPtr<ScrollBar>& scrollBar)
{
    scrollBar_ = scrollBar;
}

void TextFieldOverlayModifier::SetChangeSelectedRects(bool value)
{
    if (value) {
        changeSelectedRects_->Set(!changeSelectedRects_->Get());
    }
    needPaintSelect_ = value;
}

void TextFieldOverlayModifier::SetShowSelect(bool value)
{
    showSelect_->Set(value);
}
} // namespace OHOS::Ace::NG
