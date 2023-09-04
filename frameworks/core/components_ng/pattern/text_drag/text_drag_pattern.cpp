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
} // namespace

namespace OHOS::Ace::NG {
bool TextDragPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    return true;
}

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

RefPtr<FrameNode> TextDragPattern::CreateDragNode(
    const RefPtr<FrameNode>& hostNode, std::list<RefPtr<FrameNode>>& imageChildren)
{
    auto hostPattern = hostNode->GetPattern<TextDragBase>();
    auto dragNode = TextDragPattern::CreateDragNode(hostNode);
    auto dragPattern = dragNode->GetPattern<TextDragPattern>();
    auto textPattern = hostNode->GetPattern<TextPattern>();
    auto placeHolderIndex = textPattern->GetPlaceHolderIndex();
    auto rectsForPlaceholders = textPattern->GetRectsForPlaceholders();

    size_t index = 0;
    std::vector<Rect> realRectsForPlaceholders;
    std::list<RefPtr<FrameNode>> realImageChildren;
    auto boxes = hostPattern->GetTextBoxes();
    for (const auto& child : imageChildren) {
        auto imageIndex = placeHolderIndex[index];
        auto rect = rectsForPlaceholders.at(imageIndex);

        for (const auto& box : boxes) {
            if (LessOrEqual(box.rect_.GetLeft(), rect.Left()) &&
                GreatOrEqual(box.rect_.GetRight(), rect.Right()) &&
                LessOrEqual(box.rect_.GetTop(), rect.Top()) &&
                GreatOrEqual(box.rect_.GetBottom(), rect.Bottom())) {
                realImageChildren.emplace_back(child);
                realRectsForPlaceholders.emplace_back(rect);
            }
        }
        ++index;
    }
    dragPattern->SetLastLineHeight(boxes.back().rect_.GetHeight());
    dragPattern->InitSpanImageLayout(realImageChildren, realRectsForPlaceholders);
    return dragNode;
}

TextDragData TextDragPattern::CalculateTextDragData(RefPtr<TextDragBase>& hostPattern, RefPtr<FrameNode>& dragNode)
{
    auto dragContext = dragNode->GetRenderContext();
    auto dragPattern = dragNode->GetPattern<TextDragPattern>();
    float textStartX = hostPattern->GetTextRect().GetX();
    float textStartY =
        hostPattern->IsTextArea() ? hostPattern->GetTextRect().GetY() : hostPattern->GetTextContentRect().GetY();
    auto contentRect = hostPattern->GetTextContentRect();
    float lineHeight = hostPattern->GetLineHeight();
    float minWidth = TEXT_DRAG_MIN_WIDTH.ConvertToPx();
    float bothOffset = TEXT_DRAG_OFFSET.ConvertToPx() * 2; // 2 : double
    auto boxes = hostPattern->GetTextBoxes();
    CHECK_NULL_RETURN(!boxes.empty(), {});
    auto boxFirst = boxes.front();
    auto boxLast = boxes.back();
    float leftHandleX = boxFirst.rect_.GetLeft() + textStartX;
    float leftHandleY = boxFirst.rect_.GetTop() + textStartY;
    float rightHandleX = boxLast.rect_.GetRight() + textStartX;
    float rightHandleY = boxLast.rect_.GetTop() + textStartY;
    bool oneLineSelected = (leftHandleY == rightHandleY);
    if (oneLineSelected) {
        if (leftHandleX < contentRect.Left()) {
            leftHandleX = contentRect.Left();
        }
        if (rightHandleX > contentRect.Right()) {
            rightHandleX = contentRect.Right();
        }
    } else {
        if (leftHandleY < contentRect.Top() - BOX_EPSILON) {
            leftHandleX = contentRect.Left();
            leftHandleY = contentRect.Top();
        }
        if ((boxLast.rect_.GetBottom() + textStartY) > contentRect.Bottom()) {
            rightHandleX = contentRect.Right();
            rightHandleY = contentRect.Bottom() - lineHeight;
        }
    }
    auto hostGlobalOffset = hostPattern->GetParentGlobalOffset();
    float width = rightHandleX - leftHandleX;
    float height = rightHandleY - leftHandleY + lineHeight;
    float globalX = leftHandleX + hostGlobalOffset.GetX() - TEXT_DRAG_OFFSET.ConvertToPx();
    float globalY = leftHandleY + hostGlobalOffset.GetY() - TEXT_DRAG_OFFSET.ConvertToPx();
    if (oneLineSelected) {
        if (rightHandleX - leftHandleX + bothOffset < minWidth) {
            float delta = minWidth - (rightHandleX - leftHandleX + bothOffset);
            width += delta;
            globalX -= delta / 2; // 2 : half
        }
        dragPattern->SetContentOffset(OffsetF(boxes.front().rect_.GetLeft() - TEXT_DRAG_OFFSET.ConvertToPx(),
            boxes.front().rect_.GetTop() - TEXT_DRAG_OFFSET.ConvertToPx()));
    } else {
        globalX = contentRect.Left() + hostGlobalOffset.GetX() - TEXT_DRAG_OFFSET.ConvertToPx();
        width = contentRect.Width();
        dragPattern->SetContentOffset(
            OffsetF(0 - TEXT_DRAG_OFFSET.ConvertToPx(), boxes.front().rect_.GetTop() - TEXT_DRAG_OFFSET.ConvertToPx()));
    }
    dragContext->UpdatePosition(OffsetT<Dimension>(Dimension(globalX), Dimension(globalY)));
    RectF dragTextRect(
        textStartX + hostGlobalOffset.GetX() - globalX, textStartY + hostGlobalOffset.GetY() - globalY, width, height);
    SelectPositionInfo info(leftHandleX + hostGlobalOffset.GetX() - globalX,
        leftHandleY + hostGlobalOffset.GetY() - globalY, rightHandleX + hostGlobalOffset.GetX() - globalX,
        rightHandleY + hostGlobalOffset.GetY() - globalY);
    TextDragData data(dragTextRect, width + bothOffset, height + bothOffset, lineHeight, info, oneLineSelected);
    return data;
}

std::shared_ptr<RSPath> TextDragPattern::GenerateClipPath()
{
    std::shared_ptr<RSPath> path = std::make_shared<RSPath>();
    auto selectPosition = GetSelectPosition();
    float startX = selectPosition.startX_;
    float startY = selectPosition.startY_;
    float endX = selectPosition.endX_;
    float endY = selectPosition.endY_;
    float textStart = GetTextRect().GetX();
    float textEnd = textStart + GetTextRect().Width();
    auto lineHeight = GetLineHeight();
    if (OneLineSelected()) {
        path->MoveTo(startX, endY);
        path->LineTo(endX, endY);
        path->LineTo(endX, endY + lineHeight);
        path->LineTo(startX, endY + lineHeight);
        path->LineTo(startX, endY);
    } else {
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

void TextDragPattern::GenerateBackgroundPoints(std::vector<TextPoint>& points, float offset)
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
        if ((endX - startX) + bothOffset < minWidth) {
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
            points.push_back(TextPoint(textEnd + offset, endY + lineHeight + offset));
        } else {
            points.push_back(TextPoint(textEnd + offset, endY + offset));
            points.push_back(TextPoint(endX + offset, endY + offset));
            points.push_back(TextPoint(endX + offset, endY + lineHeight + offset));
        }
        points.push_back(TextPoint(textStart - offset, endY + lineHeight + offset));
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
} // namespace OHOS::Ace::NG
