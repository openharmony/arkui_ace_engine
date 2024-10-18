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

#include "core/components_ng/pattern/text/text_base.h"
#include <cstdint>

namespace OHOS::Ace::NG {

void TextBase::SetSelectionNode(const SelectedByMouseInfo& info)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto selectOverlayManager = pipeline->GetSelectOverlayManager();
    selectOverlayManager->SetSelectedNodeByMouse(info);
}

int32_t TextBase::GetGraphemeClusterLength(
    const std::wstring& text, int32_t extend, bool checkPrev)
{
    char16_t aroundChar = 0;
    if (checkPrev) {
        if (static_cast<size_t>(extend) <= text.length()) {
            aroundChar = text[std::max(0, extend - 1)];
        }
    } else {
        if (static_cast<size_t>(extend) <= (text.length())) {
            aroundChar = text[std::min(text.length() ? static_cast<int32_t>(text.length()) - 1 : 0, extend)];
        }
    }
    return StringUtils::NotInUtf16Bmp(aroundChar) ? 2 : 1;
}

void TextBase::CalculateSelectedRect(std::vector<RectF>& selectedRect, float longestLine, TextDirection direction)
{
    if (selectedRect.size() <= 1 || direction == TextDirection::RTL) {
        return;
    }
    std::map<float, RectF> lineGroup;
    for (const auto& localRect : selectedRect) {
        if (NearZero(localRect.Width()) && NearZero(localRect.Height())) {
            continue;
        }
        auto it = lineGroup.find(localRect.GetY());
        if (it == lineGroup.end()) {
            lineGroup.emplace(localRect.GetY(), localRect);
        } else {
            auto lineRect = it->second;
            it->second = lineRect.CombineRectT(localRect);
        }
    }
    selectedRect.clear();
    auto firstRect = lineGroup.begin()->second;
    float lastLineBottom = firstRect.Top();
    auto end = *(lineGroup.rbegin());
    for (const auto& line : lineGroup) {
        if (line == end) {
            break;
        }
        auto rect = RectF(line.second.Left(), lastLineBottom, longestLine - line.second.Left(),
                line.second.Bottom() - lastLineBottom);
        selectedRect.emplace_back(rect);
        lastLineBottom = line.second.Bottom();
    }
    selectedRect.emplace_back(RectF(end.second.Left(), lastLineBottom, end.second.Width(), end.second.Height()));
}

void TextBase::RevertLocalPointWithTransform(const RefPtr<FrameNode>& targetNode, OffsetF& point)
{
    auto pattern = targetNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    auto parent = pattern->GetHost();
    CHECK_NULL_VOID(parent);
    std::stack<RefPtr<FrameNode>> nodeStack;
    while (parent) {
        nodeStack.push(parent);
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    CHECK_NULL_VOID(!nodeStack.empty());
    PointF localPoint(point.GetX(), point.GetY());
    while (!nodeStack.empty()) {
        parent = nodeStack.top();
        CHECK_NULL_VOID(parent);
        nodeStack.pop();
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->GetPointWithRevert(localPoint);
        auto rectOffset = renderContext->GetPaintRectWithoutTransform().GetOffset();
        localPoint = localPoint - rectOffset;
    }
    point.SetX(localPoint.GetX());
    point.SetY(localPoint.GetY());
}

bool TextBase::HasRenderTransform(const RefPtr<FrameNode>& targetNode)
{
    auto pattern = targetNode->GetPattern<Pattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    auto hasTransform = false;
    while (host) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        if (host->GetTag() == V2::WINDOW_SCENE_ETS_TAG) {
            break;
        }
        if (!hasTransform) {
            auto noTransformRect = renderContext->GetPaintRectWithoutTransform();
            auto transformRect = renderContext->GetPaintRectWithTransform();
            hasTransform = noTransformRect != transformRect;
        } else {
            break;
        }
        host = host->GetAncestorNodeOfFrame(true);
    }
    return hasTransform;
}

void TextGestureSelector::DoGestureSelection(const TouchEventInfo& info)
{
    if (info.GetTouches().empty()) {
        return;
    }
    auto touchType = info.GetTouches().front().GetTouchType();
    switch (touchType) {
        case TouchType::UP:
            EndGestureSelection();
            break;
        case TouchType::MOVE:
            DoTextSelectionTouchMove(info);
            break;
        case TouchType::CANCEL:
            DoTextSelectionTouchCancel();
            break;
        default:
            break;
    }
}

void TextGestureSelector::DoTextSelectionTouchMove(const TouchEventInfo& info)
{
    if (!isStarted_ || info.GetTouches().empty()) {
        return;
    }
    auto localOffset = info.GetTouches().front().GetLocalLocation();
    if (!isSelecting_ && LessOrEqual((localOffset - startOffset_).GetDistance(), minMoveDistance_.ConvertToPx())) {
        return;
    }
    isSelecting_ = true;
    auto index = GetTouchIndex({ localOffset.GetX(), localOffset.GetY() });
    auto start = std::min(index, start_);
    auto end = std::max(index, end_);
    OnTextGestureSelectionUpdate(start, end, info);
}
}