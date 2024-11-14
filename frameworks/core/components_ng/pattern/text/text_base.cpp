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
#include "core/text/text_emoji_processor.h"
#include <cstdint>

namespace OHOS::Ace::NG {
namespace {
const Dimension SELECTED_BLANK_LINE_WIDTH = 2.0_vp;
}; // namespace

void TextBase::SetSelectionNode(const SelectedByMouseInfo& info)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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

float TextBase::GetSelectedBlankLineWidth()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, static_cast<float>(SELECTED_BLANK_LINE_WIDTH.ConvertToPx()));
    auto blankWidth = pipeline->NormalizeToPx(SELECTED_BLANK_LINE_WIDTH);
    return static_cast<float>(blankWidth);
}

void TextBase::CalculateSelectedRectEx(std::vector<RectF>& selectedRects, float lastLineBottom)
{
    if (selectedRects.empty()) {
        return;
    }
    std::map<float, RectF> lineGroup;
    SelectedRectsToLineGroup(selectedRects, lineGroup);
    selectedRects.clear();
    lastLineBottom = LessNotEqual(lastLineBottom, 0.0f) ? lineGroup.begin()->second.Top() : lastLineBottom;
    for (const auto& line : lineGroup) {
        auto& lineRect = line.second;
        RectF rect = RectF(lineRect.Left(), lastLineBottom, lineRect.Width(), lineRect.Bottom() - lastLineBottom);
        selectedRects.emplace_back(rect);
        lastLineBottom = line.second.Bottom();
    }
}

bool TextBase::UpdateSelectedBlankLineRect(RectF& rect, float blankWidth, TextAlign textAlign, float longestLine)
{
    CHECK_EQUAL_RETURN(NearZero(rect.Width()), false, false);
    switch (textAlign) {
        case TextAlign::JUSTIFY:
        case TextAlign::START: {
            if (GreatNotEqual(longestLine, 0.0f) && GreatNotEqual(rect.Left() + blankWidth, longestLine)) {
                rect.SetLeft(longestLine - blankWidth);
            }
            break;
        }
        case TextAlign::CENTER:
            rect.SetLeft(rect.Left() - (blankWidth / 2.0f));
            break;
        case TextAlign::END: {
            auto left = rect.Left() - blankWidth;
            if (GreatOrEqual(left, 0.0f)) {
                rect.SetLeft(left);
            }
            break;
        }
        default:
            return false;
    }
    rect.SetWidth(blankWidth);
    return true;
}

void TextBase::SelectedRectsToLineGroup(const std::vector<RectF>& selectedRect, std::map<float, RectF>& lineGroup)
{
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
}

TextAlign TextBase::CheckTextAlignByDirection(TextAlign textAlign, TextDirection direction)
{
    if (direction == TextDirection::RTL) {
        if (textAlign == TextAlign::START) {
            return TextAlign::END;
        } else if (textAlign == TextAlign::END) {
            return TextAlign::START;
        }
    }
    return textAlign;
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

std::u16string TextBase::ConvertStr8toStr16(const std::string& value)
{
    auto content = value;
    std::u16string result = StringUtils::Str8ToStr16(content);
    if (result.length() == 0 && value.length() != 0) {
        content = TextEmojiProcessor::ConvertU8stringUnpairedSurrogates(value);
        result = StringUtils::Str8ToStr16(content);
    }
    return result;
}

void TextGestureSelector::DoGestureSelection(const TouchEventInfo& info)
{
    if (!isStarted_ || info.GetTouches().empty()) {
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
            CancelGestureSelection();
            break;
        default:
            break;
    }
}

void TextGestureSelector::DoTextSelectionTouchMove(const TouchEventInfo& info)
{
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