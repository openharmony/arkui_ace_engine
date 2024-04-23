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

#include "base/utils/utils.h"
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
    for (const auto& box : boxes) {
        if (box.Bottom() + textStartY >= contentRect.Bottom() && !hasResult) {
            result = box;
            hasResult = true;
            continue;
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
    auto data = CalculateTextDragData(hostPattern, dragNode);
    dragPattern->Initialize(hostPattern->GetDragParagraph(), data);
    dragPattern->SetLastLineHeight(data.lineHeight_);

    CalcSize size(NG::CalcLength(dragPattern->GetFrameWidth()), NG::CalcLength(dragPattern->GetFrameHeight()));
    dragNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(size);
    return dragNode;
}

TextDragData TextDragPattern::CalculateTextDragData(RefPtr<TextDragBase>& pattern, RefPtr<FrameNode>& dragNode,
    float selectedWidth)
{
    auto dragContext = dragNode->GetRenderContext();
    auto dragPattern = dragNode->GetPattern<TextDragPattern>();
    float textStartX = pattern->GetTextRect().GetX();
    float textStartY = pattern->IsTextArea() ? pattern->GetTextRect().GetY() : pattern->GetTextContentRect().GetY();
    auto contentRect = pattern->GetTextContentRect();
    float lineHeight = pattern->GetLineHeight();
    float bothOffset = TEXT_DRAG_OFFSET.ConvertToPx() * CONSTANT_HALF;
    auto boxes = pattern->GetTextBoxes();
    CHECK_NULL_RETURN(!boxes.empty(), {});
    auto boxFirst = GetFirstBoxRect(boxes, contentRect, textStartY);
    auto boxLast = GetLastBoxRect(boxes, contentRect, textStartY);
    float leftHandleX = boxFirst.Left() + textStartX;
    float leftHandleY = boxFirst.Top() + textStartY;
    float rightHandleX = boxLast.Right() + textStartX;
    float rightHandleY = boxLast.Top() + textStartY;
    bool oneLineSelected = (leftHandleY == rightHandleY);
    if (oneLineSelected) {
        leftHandleX = std::max(leftHandleX, contentRect.Left());
        rightHandleX = std::min(rightHandleX, contentRect.Right());
    }
    auto globalOffset = pattern->GetParentGlobalOffset();
    float width = rightHandleX - leftHandleX;
    float height = rightHandleY - leftHandleY + boxLast.Height();
    auto dragOffset = TEXT_DRAG_OFFSET.ConvertToPx();
    float globalX = leftHandleX + globalOffset.GetX() - dragOffset;
    float globalY = leftHandleY + globalOffset.GetY() - dragOffset;
    auto box = boxes.front();
    if (oneLineSelected) {
        float delta = 0.0f;
        if (rightHandleX - leftHandleX + bothOffset < TEXT_DRAG_MIN_WIDTH.ConvertToPx()) {
            delta = TEXT_DRAG_MIN_WIDTH.ConvertToPx() - (rightHandleX - leftHandleX + bothOffset);
            width += delta;
            globalX -= delta / CONSTANT_HALF;
        }

        dragPattern->SetContentOffset({box.Left() - dragOffset - delta / CONSTANT_HALF, box.Top() - dragOffset});
    } else {
        globalX = contentRect.Left() + globalOffset.GetX() - dragOffset;
        width = contentRect.Width();
        dragPattern->SetContentOffset({0 - dragOffset, box.Top() - dragOffset});
    }
    width = !NearZero(selectedWidth) ? selectedWidth : width;
    dragContext->UpdatePosition(OffsetT<Dimension>(Dimension(globalX), Dimension(globalY)));
    RectF rect(textStartX + globalOffset.GetX() - globalX, textStartY + globalOffset.GetY() - globalY, width, height);
    SelectPositionInfo info(leftHandleX + globalOffset.GetX() - globalX, leftHandleY + globalOffset.GetY() - globalY,
        rightHandleX + globalOffset.GetX() - globalX, rightHandleY + globalOffset.GetY() - globalY);
    info.InitGlobalInfo(globalX, globalY);
    TextDragData data(rect, width + bothOffset, height + bothOffset, lineHeight, info, oneLineSelected);
    return data;
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

std::shared_ptr<RSPath> TextDragPattern::GenerateBackgroundPath(float offset)
{
    std::shared_ptr<RSPath> path = std::make_shared<RSPath>();
    std::vector<TextPoint> points;
    GenerateBackgroundPoints(points, offset);
    CalculateLineAndArc(points, path);
    return path;
}

std::shared_ptr<RSPath> TextDragPattern::GenerateSelBackgroundPath(float offset)
{
    std::shared_ptr<RSPath> path = std::make_shared<RSPath>();
    std::vector<TextPoint> points;
    GenerateBackgroundPoints(points, offset, false);
    CalculateLine(points, path);
    return path;
}

void TextDragPattern::GenerateBackgroundPoints(std::vector<TextPoint>& points, float offset, bool needAdjust)
{
    auto radius = TEXT_DRAG_RADIUS.ConvertToPx();
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

void TextDragPattern::CalculateLineAndArc(std::vector<TextPoint>& points, std::shared_ptr<RSPath>& path)
{
    auto radius = TEXT_DRAG_RADIUS.ConvertToPx();
    path->MoveTo(points[0].x + radius, points[0].y);
    size_t step = 2;
    for (size_t i = 0; i + step < points.size(); i++) {
        auto firstPoint = points[i];
        auto crossPoint = points[i + 1];
        auto secondPoint = points[i + step];

        if (crossPoint.y == firstPoint.y) {
            int directionX = (crossPoint.x - firstPoint.x) > 0 ? 1 : -1;
            int directionY = (secondPoint.y - crossPoint.y) > 0 ? 1 : -1;
            auto direction =
                (directionX * directionY > 0) ? RSPathDirection::CW_DIRECTION : RSPathDirection::CCW_DIRECTION;
            path->LineTo(crossPoint.x - radius * directionX, crossPoint.y);
            path->ArcTo(radius, radius, 0.0f, direction, crossPoint.x, crossPoint.y + radius * directionY);
        } else {
            int directionX = (secondPoint.x - crossPoint.x) > 0 ? 1 : -1;
            int directionY = (crossPoint.y - firstPoint.y) > 0 ? 1 : -1;
            auto direction =
                (directionX * directionY < 0) ? RSPathDirection::CW_DIRECTION : RSPathDirection::CCW_DIRECTION;
            path->LineTo(crossPoint.x, crossPoint.y - radius * directionY);
            path->ArcTo(radius, radius, 0.0f, direction, crossPoint.x + radius * directionX, secondPoint.y);
        }
    }
}

void TextDragPattern::CalculateLine(std::vector<TextPoint>& points, std::shared_ptr<RSPath>& path)
{
    auto radius = TEXT_DRAG_RADIUS.ConvertToPx();
    path->MoveTo(points[0].x + radius, points[0].y);
    size_t step = 2;
    for (size_t i = 0; i + step < points.size(); i++) {
        auto crossPoint = points[i + 1];
        path->LineTo(crossPoint.x, crossPoint.y);
    }
}
} // namespace OHOS::Ace::NG
