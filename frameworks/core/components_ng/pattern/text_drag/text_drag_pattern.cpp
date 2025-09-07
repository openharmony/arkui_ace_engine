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

#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"

#include <algorithm>

#include "base/utils/utils.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace {
// uncertainty range when comparing selectedTextBox to contentRect
constexpr float BOX_EPSILON = 0.2f;
constexpr float CONSTANT_HALF = 2.0f;
} // namespace

namespace OHOS::Ace::NG {
bool TextDragPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    return true;
}

const RectF GetFirstBoxRect(const std::vector<RectF>& boxes, const RectF& contentRect, const float textStartY)
{
    for (const auto& box : boxes) {
        if (box.Bottom() + textStartY > contentRect.Top() + BOX_EPSILON) {
            return box;
        }
    }
    return boxes.front();
} // Obtains the first line in the visible area of the text box, including the truncated part.

const RectF GetLastBoxRect(const std::vector<RectF>& boxes, const RectF& contentRect, const float textStartY)
{
    bool hasResult = false;
    RectF result;
    RectF preBox;
    auto deviceHeight = SystemProperties::GetDevicePhysicalHeight();
    auto container = Container::CurrentSafely();
    if (container && container->GetDisplayInfo()) {
        deviceHeight = container->GetDisplayInfo()->GetHeight();
    }
    auto maxBottom = contentRect.GetY() + deviceHeight;
    for (const auto& box : boxes) {
        auto caculateBottom = box.Bottom() + textStartY;
        bool isReachingBottom = (caculateBottom >= maxBottom) || (caculateBottom >= contentRect.Bottom());
        if (isReachingBottom && !hasResult) {
            result = box;
            hasResult = true;
            auto isBoxExceedContent = GreatOrEqual(result.Top() + textStartY, contentRect.Bottom()) &&
                LessNotEqual(preBox.Bottom() + textStartY, contentRect.Bottom());
            isBoxExceedContent = isBoxExceedContent || (GreatOrEqual(result.Top() + textStartY, maxBottom) &&
                LessNotEqual(preBox.Bottom() + textStartY, maxBottom));
            CHECK_NULL_RETURN(!isBoxExceedContent, preBox);
            continue;
        }
        if (!hasResult) {
            preBox = box;
        }
        if (hasResult && box.Bottom() == result.Bottom()) {
            result = box;
        } else if (hasResult && box.Bottom() != result.Bottom()) {
            return result;
        }
    }
    return boxes.back();
} // Obtains the last line in the visible area of the text box, including the truncated part.

RefPtr<FrameNode> TextDragPattern::CreateDragNode(const RefPtr<FrameNode>& hostNode)
{
    CHECK_NULL_RETURN(hostNode, nullptr);
    auto hostPattern = hostNode->GetPattern<TextDragBase>();
    const auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dragNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTDRAG_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextDragPattern>(); });
    auto dragContext = dragNode->GetRenderContext();
    auto hostContext = hostNode->GetRenderContext();
    if (hostContext->HasForegroundColor()) {
        dragContext->UpdateForegroundColor(hostContext->GetForegroundColor().value());
    }
    if (hostContext->HasForegroundColorStrategy()) {
        dragContext->UpdateForegroundColorStrategy(hostContext->GetForegroundColorStrategy().value());
    }
    auto dragPattern = dragNode->GetPattern<TextDragPattern>();
    auto data = CalculateTextDragData(hostPattern, dragNode, hostNode);
    TAG_LOGI(AceLogTag::ACE_TEXT, "CreateDragNode SelectPositionInfo startX = %{public}f, startY = %{public}f,\
             endX = %{public}f, endY = %{public}f, globalX = %{public}f, globalY = %{public}f",
             data.selectPosition_.startX_, data.selectPosition_.startY_,
             data.selectPosition_.endX_, data.selectPosition_.endY_,
             data.selectPosition_.globalX_, data.selectPosition_.globalY_);
    dragPattern->Initialize(hostPattern->GetDragParagraph(), data);
    dragPattern->SetLastLineHeight(data.lineHeight_);

    CalcSize size(NG::CalcLength(dragPattern->GetFrameWidth()), NG::CalcLength(dragPattern->GetFrameHeight()));
    dragNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(size);

    auto onDetachFromMainTreeCallback = [weak = WeakPtr<TextDragBase>(hostPattern)]() {
        auto textDragBasePattern = weak.Upgrade();
        CHECK_NULL_VOID(textDragBasePattern);
        textDragBasePattern->OnDragNodeDetachFromMainTree();
    };
    dragPattern->SetOnDetachFromMainTree(std::move(onDetachFromMainTreeCallback));
    return dragNode;
}

void TextDragPattern::CalculateOverlayOffset(RefPtr<FrameNode>& dragNode, OffsetF& offset,
    const RefPtr<FrameNode>& hostNode)
{
    auto pipeline = dragNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    if (pipeline->CheckNodeOnContainerModalTitle(hostNode)) {
        rootNode = pipeline->GetContainerModalNode();
    }
    CHECK_NULL_VOID(rootNode);
    auto rootGeometryNode = AceType::DynamicCast<FrameNode>(rootNode)->GetGeometryNode();
    CHECK_NULL_VOID(rootGeometryNode);
    auto rootOffset = rootGeometryNode->GetFrameOffset();
    offset -= rootOffset;
}

void TextDragPattern::DropBlankLines(std::vector<RectF>& boxes)
{
    while (!boxes.empty() && NearZero(boxes.back().Width())) {
        boxes.pop_back();
    }
    while (!boxes.empty() && NearZero(boxes.front().Width())) {
        boxes.erase(boxes.begin());
    }
}

TextDragData TextDragPattern::CalculateTextDragData(RefPtr<TextDragBase>& pattern, RefPtr<FrameNode>& dragNode,
    const RefPtr<FrameNode>& hostNode)
{
    auto dragContext = dragNode->GetRenderContext();
    auto dragPattern = dragNode->GetPattern<TextDragPattern>();
    OffsetF textStartOffset = {pattern->GetTextRect().GetX(),
        pattern->IsTextArea() ? pattern->GetTextRect().GetY() : pattern->GetTextContentRect().GetY()};
    auto contentRect = pattern->GetTextContentRect(true);
    float bothOffset = TEXT_DRAG_OFFSET.ConvertToPx() * CONSTANT_HALF;
    auto boxes = pattern->GetTextBoxes();
    CHECK_NULL_RETURN(!boxes.empty(), {});
    DropBlankLines(boxes);
    auto globalOffset = pattern->GetParentGlobalOffset();
    CalculateOverlayOffset(dragNode, globalOffset, hostNode);
    RectF leftHandler = GetHandler(true, boxes, contentRect, globalOffset, textStartOffset);
    RectF rightHandler = GetHandler(false, boxes, contentRect, globalOffset, textStartOffset);
    AdjustHandlers(contentRect, leftHandler, rightHandler);
    float width = rightHandler.GetX() - leftHandler.GetX();
    float height = rightHandler.GetY() - leftHandler.GetY() + rightHandler.Height();
    auto dragOffset = TEXT_DRAG_OFFSET.ConvertToPx();
    float globalX = leftHandler.GetX() + globalOffset.GetX() - dragOffset;
    float globalY = leftHandler.GetY() + globalOffset.GetY() - dragOffset;
    auto box = boxes.front();
    float delta = 0.0f;
    float handlersDistance = width;
    if (leftHandler.GetY() == rightHandler.GetY()) {
        if (handlersDistance + bothOffset < TEXT_DRAG_MIN_WIDTH.ConvertToPx()) {
            delta = TEXT_DRAG_MIN_WIDTH.ConvertToPx() - (handlersDistance + bothOffset);
            width += delta;
            globalX -= delta / CONSTANT_HALF;
        }
    } else {
        globalX = contentRect.Left() + globalOffset.GetX() - dragOffset;
        dragPattern->AdjustMaxWidth(width, contentRect, boxes);
    }
    float contentX = (leftHandler.GetY() == rightHandler.GetY() ? box.Left() : 0) - dragOffset - delta / CONSTANT_HALF;
    dragPattern->SetContentOffset({contentX, box.Top() - dragOffset});
    dragContext->UpdatePosition(OffsetT<Dimension>(Dimension(globalX), Dimension(globalY)));
    auto offsetXValue = globalOffset.GetX() - globalX;
    auto offsetYValue = globalOffset.GetY() - globalY;
    RectF rect(textStartOffset.GetX() + offsetXValue, textStartOffset.GetY() + offsetYValue, width, height);
    SelectPositionInfo info(leftHandler.GetX() + offsetXValue, leftHandler.GetY() + offsetYValue,
        rightHandler.GetX() + offsetXValue, rightHandler.GetY() + offsetYValue);
    info.InitGlobalInfo(globalX, globalY);
    TextDragData data(rect, width + bothOffset, height + bothOffset, leftHandler.Height(), rightHandler.Height());
    data.initSelecitonInfo(info, leftHandler.GetY() == rightHandler.GetY());
    return data;
}

void TextDragPattern::AdjustMaxWidth(float& width, const RectF& contentRect, const std::vector<RectF>& boxes)
{
    width = contentRect.Width();
    CHECK_NULL_VOID(!boxes.empty());
    float startX = boxes.front().Left();
    float endX = boxes.front().Right();
    for (const auto& box : boxes) {
        startX = std::min(startX, box.Left());
        endX = std::max(endX, box.Right());
    }
    startX = std::min(0.0f, startX);
    width = std::abs(startX - endX);
}

RectF TextDragPattern::GetHandler(const bool isLeftHandler, const std::vector<RectF> boxes, const RectF contentRect,
    const OffsetF globalOffset, const OffsetF textStartOffset)
{
    auto adjustedTextStartY = textStartOffset.GetY() + std::min(globalOffset.GetY(), 0.0f);
    auto box = isLeftHandler ? GetFirstBoxRect(boxes, contentRect, adjustedTextStartY) :
        GetLastBoxRect(boxes, contentRect, adjustedTextStartY);
    auto handlerX = (isLeftHandler ? box.Left() : box.Right()) + textStartOffset.GetX();
    return {handlerX, box.Top() + textStartOffset.GetY(), 0, box.Height()};
}

void TextDragPattern::AdjustHandlers(const RectF contentRect, RectF& leftHandler, RectF& rightHandler)
{
    if (leftHandler.GetY() != rightHandler.GetY()) {
        return;
    }
    leftHandler.SetLeft(std::max(leftHandler.GetX(), contentRect.Left()));
    rightHandler.SetLeft(std::min(rightHandler.GetX(), contentRect.Right()));
}

std::shared_ptr<RSPath> TextDragPattern::GenerateClipPath()
{
    std::shared_ptr<RSPath> path = std::make_shared<RSPath>();
    auto selectPosition = GetSelectPosition();
    float startX = selectPosition.startX_;
    float startY = selectPosition.startY_;
    float textStart = GetTextRect().GetX();
    float textEnd = textStart + GetTextRect().Width();
    float endX = selectPosition.endX_;
    float endY = selectPosition.endY_;
    auto lineHeight = GetLineHeight();
    if (OneLineSelected()) {
        path->MoveTo(startX, endY);
        path->LineTo(endX, endY);
        path->LineTo(endX, endY + lineHeight);
        path->LineTo(startX, endY + lineHeight);
        path->LineTo(startX, endY);
    } else {
        endX = std::min(selectPosition.endX_, textEnd);
        path->MoveTo(startX, startY);
        path->LineTo(textEnd, startY);
        path->LineTo(textEnd, endY);
        path->LineTo(endX, endY);
        path->LineTo(endX, endY + lastLineHeight_);
        path->LineTo(textStart, endY + lastLineHeight_);
        path->LineTo(textStart, startY + lineHeight);
        path->LineTo(startX, startY + lineHeight);
        path->LineTo(startX, startY);
    }
    return path;
}

std::shared_ptr<RSPath> TextDragPattern::GenerateBackgroundPath(float offset, float radiusRatio)
{
    std::shared_ptr<RSPath> path = std::make_shared<RSPath>();
    std::vector<TextPoint> points;
    GenerateBackgroundPoints(points, offset);
    CalculateLineAndArc(points, path, radiusRatio);
    return path;
}

std::shared_ptr<RSPath> TextDragPattern::GenerateSelBackgroundPath(float offset)
{
    std::shared_ptr<RSPath> path = std::make_shared<RSPath>();
    std::vector<TextPoint> points;
    GenerateBackgroundPoints(points, offset);
    CalculateLine(points, path);
    return path;
}

void TextDragPattern::GenerateBackgroundPoints(std::vector<TextPoint>& points, float offset, bool needAdjust)
{
    auto radius = GetDragCornerRadius().ConvertToPx();
    auto bothOffset = offset * 2; // 2 : double
    auto minWidth = TEXT_DRAG_MIN_WIDTH.ConvertToPx();
    auto selectPosition = GetSelectPosition();
    float startX = selectPosition.startX_;
    float startY = selectPosition.startY_;
    float endX = selectPosition.endX_;
    float endY = selectPosition.endY_;
    float textStart = GetTextRect().GetX();
    float textEnd = textStart + GetTextRect().Width();
    auto lineHeight = GetLineHeight();
    if (OneLineSelected()) {
        if (needAdjust && (endX - startX) + bothOffset < minWidth) {
            float delta = minWidth - ((endX - startX) + bothOffset);
            startX -= delta / 2.0f; // 2 : half
            endX += delta / 2.0f;   // 2 : half
        }
        points.push_back(TextPoint(startX - offset, startY - offset));
        points.push_back(TextPoint(endX + offset, endY - offset));
        points.push_back(TextPoint(endX + offset, endY + lineHeight + offset));
        points.push_back(TextPoint(startX - offset, endY + lineHeight + offset));
        points.push_back(TextPoint(startX - offset, endY - offset));
        points.push_back(TextPoint(endX + offset, endY - offset));
    } else {
        points.push_back(TextPoint(startX - offset, startY - offset));
        points.push_back(TextPoint(textEnd + offset, startY - offset));
        if (textEnd - radius < endX + radius) {
            points.push_back(TextPoint(textEnd + offset, endY + lastLineHeight_ + offset));
        } else {
            points.push_back(TextPoint(textEnd + offset, endY + offset));
            points.push_back(TextPoint(endX + offset, endY + offset));
            points.push_back(TextPoint(endX + offset, endY + lastLineHeight_ + offset));
        }
        points.push_back(TextPoint(textStart - offset, endY + lastLineHeight_ + offset));
        if (startX - radius < textStart + radius) {
            points[0] = TextPoint(textStart - offset, startY - offset);
            points.push_back(TextPoint(textStart - offset, startY - offset));
        } else {
            points.push_back(TextPoint(textStart - offset, startY + lineHeight - offset));
            points.push_back(TextPoint(startX - offset, startY + lineHeight - offset));
            points.push_back(TextPoint(startX - offset, startY - offset));
        }
        points.push_back(TextPoint(textEnd + offset, startY - offset));
    }
}

void TextDragPattern::CalculateLineAndArc(std::vector<TextPoint>& points, std::shared_ptr<RSPath>& path,
    float radiusRatio)
{
    auto originRadius = GetDragCornerRadius().ConvertToPx();
    auto radius = originRadius * radiusRatio;
    path->MoveTo(points[0].x + radius, points[0].y);
    auto frontPoint = points[0];
    size_t step = 2;
    for (size_t i = 0; i + step < points.size(); i++) {
        auto firstPoint = points[i];
        auto crossPoint = points[i + 1];
        auto secondPoint = points[i + step];
        float tempRadius = radius;
        if (crossPoint.y == firstPoint.y) {
            int directionX = (crossPoint.x - firstPoint.x) > 0 ? 1 : -1;
            int directionY = (secondPoint.y - crossPoint.y) > 0 ? 1 : -1;
            auto direction =
                (directionX * directionY > 0) ? RSPathDirection::CW_DIRECTION : RSPathDirection::CCW_DIRECTION;
            bool isInwardFoldingCorner = frontPoint.x == firstPoint.x && firstPoint.y == crossPoint.y &&
                secondPoint.x == crossPoint.x;
            isInwardFoldingCorner = isInwardFoldingCorner && (frontPoint.y - firstPoint.y) *
                (crossPoint.y - secondPoint.y) > 0;
            if (isInwardFoldingCorner) {
                radius = std::min(std::abs(secondPoint.y - crossPoint.y) / CONSTANT_HALF, tempRadius);
            }
            path->LineTo(crossPoint.x - radius * directionX, crossPoint.y);
            path->ArcTo(radius, radius, 0.0f, direction, crossPoint.x, crossPoint.y + radius * directionY);
        } else {
            int directionX = (secondPoint.x - crossPoint.x) > 0 ? 1 : -1;
            int directionY = (crossPoint.y - firstPoint.y) > 0 ? 1 : -1;
            auto direction =
                (directionX * directionY < 0) ? RSPathDirection::CW_DIRECTION : RSPathDirection::CCW_DIRECTION;
            bool isInwardFoldingCorner = frontPoint.y == firstPoint.y && firstPoint.x == crossPoint.x &&
                secondPoint.y == crossPoint.y;
            isInwardFoldingCorner = isInwardFoldingCorner && (frontPoint.x - firstPoint.x) *
                (crossPoint.x - secondPoint.x) > 0;
            if (isInwardFoldingCorner) {
                radius = std::min(std::abs(firstPoint.y - crossPoint.y) / CONSTANT_HALF, tempRadius);
            }
            path->LineTo(crossPoint.x, crossPoint.y - radius * directionY);
            path->ArcTo(radius, radius, 0.0f, direction, crossPoint.x + radius * directionX, secondPoint.y);
        }
        radius = tempRadius;
        frontPoint = firstPoint;
    }
    path->MoveTo(points[0].x + radius, points[0].y);
}

void TextDragPattern::CalculateLine(std::vector<TextPoint>& points, std::shared_ptr<RSPath>& path)
{
    auto radius = GetDragCornerRadius().ConvertToPx();
    path->MoveTo(points[0].x + radius, points[0].y);
    size_t step = 2;
    for (size_t i = 0; i + step < points.size(); i++) {
        auto crossPoint = points[i + 1];
        path->LineTo(crossPoint.x, crossPoint.y);
    }
}

Color TextDragPattern::GetDragBackgroundColor()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, Color(TEXT_DRAG_COLOR_BG));
    auto textTheme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(textTheme, Color(TEXT_DRAG_COLOR_BG));
    return textTheme->GetDragBackgroundColor();
}

Dimension TextDragPattern::GetDragCornerRadius()
{
    auto deviceType = SystemProperties::GetDeviceType();
    if (deviceType == DeviceType::TWO_IN_ONE) {
        return TEXT_DRAG_RADIUS_2IN1;
    }
    return TEXT_DRAG_RADIUS;
}

void TextDragPattern::OnDetachFromMainTree()
{
    ResetAnimatingParagraph();
    CHECK_NULL_VOID(onDetachFromMainTree_);
    onDetachFromMainTree_();
}
} // namespace OHOS::Ace::NG
