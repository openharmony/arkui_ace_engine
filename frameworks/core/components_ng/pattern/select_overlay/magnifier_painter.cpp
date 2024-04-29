/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/select_overlay/magnifier_painter.h"
#include "core/components_ng/pattern/select_overlay/magnifier_controller.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/image_painter.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float MAGNIFIER_GAIN = 1.25f;
constexpr Dimension MAGNIFIER_WIDTH = 140.0_vp;
constexpr Dimension MAGNIFIER_HEIGHT = 48.0_vp;
constexpr Dimension MAGNIFIER_OFFSET_Y = 4.0_vp;
constexpr Dimension PIXEL_MAP_IMAGE_OFFSET = 4.0_vp;
constexpr Dimension MAGNIFIER_BOUNDRY_WIDTH = 1.0_vp;
constexpr Dimension DEFAULT_STATUS_BAR_HEIGHT = 48.0_vp;
} // namespace

// constructor
MagnifierPainter::MagnifierPainter(const WeakPtr<Pattern>& pattern) : pattern_(pattern) {}

void MagnifierPainter::PaintMagnifier(RSCanvas& canvas)
{
    auto pattern = DynamicCast<Magnifier>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto controller = pattern->GetMagnifierController();
    CHECK_NULL_VOID(controller);

    auto textBasePattern = DynamicCast<TextBase>(pattern_.Upgrade());
    CHECK_NULL_VOID(textBasePattern);

    magnifierRect_ = controller->GetMagnifierRect();
    auto parentPattern = DynamicCast<Magnifier>(magnifierRect_.parent.Upgrade());
    CHECK_NULL_VOID(parentPattern);
    auto parentController = parentPattern->GetMagnifierController();
    CHECK_NULL_VOID(parentController);

    if (!magnifierRect_.isChildNode || !parentController->GetShowMagnifier()) {
        return;
    }
    auto pixelMap = parentController->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);

    if (!GetMagnifierRect(magnifierRect_)) {
        return;
    }

    canvas.Save();
    RSBrush brush;
    brush.SetColor(RSColor::COLOR_WHITE);
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);

    std::vector<TextPoint> pathPoints = GetTextPoints(magnifierRect_, false);
    auto drawPath = GetPathByPoints(pathPoints);
    auto clipPath = GetPathByPoints(pathPoints);
    PaintShadow(*drawPath, ShadowConfig::DefaultShadowM, canvas);
    canvas.DrawPath(*drawPath);
    canvas.ClipPath(*clipPath, RSClipOp::INTERSECT, true);

    auto magnifierGain = MAGNIFIER_GAIN;
    auto pixelMapImageOffset = PIXEL_MAP_IMAGE_OFFSET.ConvertToPx();

    PixelMapImage pixelMapImage(pixelMap);
    auto magnifierPaintConfig = pixelMapImage.GetPaintConfig();
    magnifierPaintConfig.scaleX_ = magnifierGain;
    magnifierPaintConfig.scaleY_ = magnifierGain;
    pixelMapImage.SetPaintConfig(magnifierPaintConfig);

    auto cursorOffsetY = magnifierRect_.cursorOffset.GetY();
    auto localOffsetX = magnifierRect_.localOffset.GetX();
    auto textPaintOffset = textBasePattern->GetTextPaintOffset();
    RectF dstRect;
    dstRect.SetRect(localOffsetX - localOffsetX * magnifierGain - textPaintOffset.GetX() * magnifierGain,
        magnifierRect_.startY - textPaintOffset.GetY() * magnifierGain - cursorOffsetY * magnifierGain +
            pixelMapImageOffset,
        pixelMap->GetWidth() * magnifierGain, pixelMap->GetHeight() * magnifierGain);
    pixelMapImage.DrawRect(canvas, ToRSRect(dstRect));

    canvas.DetachBrush();
    canvas.Restore();
}

bool MagnifierPainter::GetMagnifierRect(MagnifierRect& rect)
{
    auto localOffsetX = magnifierRect_.localOffset.GetX();
    auto cursorOffsetY = magnifierRect_.cursorOffset.GetY();
    return GetMagnifierRect(rect.startX, rect.startY, rect.endX, rect.endY, localOffsetX, cursorOffsetY);
}

bool MagnifierPainter::GetMagnifierRect(
    float& startX, float& startY, float& endX, float& endY, float& localOffsetX, float& cursorOffsetY)
{
    auto textDragBasePattern = DynamicCast<TextDragBase>(magnifierRect_.parent.Upgrade());
    auto textBasePattern = DynamicCast<TextBase>(magnifierRect_.parent.Upgrade());
    CHECK_NULL_RETURN(textDragBasePattern, false);
    CHECK_NULL_RETURN(textBasePattern, false);

    auto cursorOffsetX = magnifierRect_.cursorOffset.GetX();
    auto magnifierWidth = MAGNIFIER_WIDTH.ConvertToPx();
    auto magnifierHeight = MAGNIFIER_HEIGHT.ConvertToPx();
    auto magnifierOffsetY = MAGNIFIER_OFFSET_Y.ConvertToPx();
    localOffsetX = std::max(localOffsetX, magnifierRect_.contentOffset.GetX());
    localOffsetX = std::min(localOffsetX, magnifierRect_.contentSize.Width() + magnifierRect_.contentOffset.GetX());
    auto textBoxesLeft = 0.0f;
    if (!textDragBasePattern->GetTextBoxes().empty()) {
        textBoxesLeft = textDragBasePattern->GetTextBoxes()[0].Left();
    }
    startY = cursorOffsetY - magnifierHeight - magnifierOffsetY;
    if ((textDragBasePattern->GetParentGlobalOffset().GetY() + startY) < DEFAULT_STATUS_BAR_HEIGHT.ConvertToPx()) {
        startY = cursorOffsetY + textDragBasePattern->GetLineHeight() + magnifierHeight + magnifierOffsetY;
    }
    startX = localOffsetX - magnifierWidth / 2.0f;
    if (((textBasePattern->GetCaretIndex() == textBasePattern->GetContentWideTextLength()
        && localOffsetX >= cursorOffsetX) || (textBasePattern->GetCaretIndex() == 0 && localOffsetX <= cursorOffsetX))
        && (cursorOffsetY == textBasePattern->GetCaretOffset().GetY())) {
        startX = cursorOffsetX - magnifierWidth / 2.0f;
        localOffsetX = cursorOffsetX;
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

std::vector<TextPoint> MagnifierPainter::GetTextPoints(const MagnifierRect& rect, bool haveOffset)
{
    return GetTextPoints(rect.startX, rect.startY, rect.endX, rect.endY, haveOffset);
}

std::vector<TextPoint> MagnifierPainter::GetTextPoints(
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

std::shared_ptr<RSPath> MagnifierPainter::GetPathByPoints(const std::vector<TextPoint>& points)
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

void MagnifierPainter::PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas& canvas)
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
} // namespace OHOS::Ace::NG