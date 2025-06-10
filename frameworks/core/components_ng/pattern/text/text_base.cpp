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
constexpr size_t UTF16_SURROGATE_PAIR_LENGTH = 2;
constexpr size_t UTF16_SINGLE_CHAR_LENGTH = 1;
}; // namespace

void TextBase::SetSelectionNode(const SelectedByMouseInfo& info)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto selectOverlayManager = pipeline->GetSelectOverlayManager();
    selectOverlayManager->SetSelectedNodeByMouse(info);
}

int32_t TextBase::GetGraphemeClusterLength(
    const std::u16string& text, int32_t extend, bool checkPrev)
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
        auto width = (line == end) ? line.second.Width() : longestLine - line.second.Left();
        auto rect = RectF(line.second.Left(), lastLineBottom, width, line.second.Bottom() - lastLineBottom);
        selectedRect.emplace_back(rect);
        lastLineBottom = line.second.Bottom();
    }
}

float TextBase::GetSelectedBlankLineWidth()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, static_cast<float>(SELECTED_BLANK_LINE_WIDTH.ConvertToPx()));
    auto blankWidth = pipeline->NormalizeToPx(SELECTED_BLANK_LINE_WIDTH);
    return static_cast<float>(blankWidth);
}

void TextBase::CalculateSelectedRectEx(std::vector<RectF>& selectedRects, float lastLineBottom,
    const std::optional<TextDirection>& direction)
{
    if (selectedRects.empty()) {
        return;
    }
    std::map<float, std::pair<RectF, std::vector<RectF>>> lineGroup;
    SelectedRectsToLineGroup(selectedRects, lineGroup);
    selectedRects.clear();
    if (lineGroup.empty()) {
        return;
    }
    lastLineBottom = LessNotEqual(lastLineBottom, 0.0f) ? lineGroup.begin()->second.first.Top() : lastLineBottom;
    for (const auto& line : lineGroup) {
        const auto& lineRect = line.second.first;
        const auto& lineRects = line.second.second;
        for (const auto& lineItem : lineRects) {
            RectF rect = RectF(lineItem.Left(), lastLineBottom, lineItem.Width(), lineRect.Bottom() - lastLineBottom);
            selectedRects.emplace_back(rect);
        }
        lastLineBottom = line.second.first.Bottom();
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

void TextBase::SelectedRectsToLineGroup(const std::vector<RectF>& selectedRect,
    std::map<float, std::pair<RectF, std::vector<RectF>>>& lineGroup)
{
    for (const auto& localRect : selectedRect) {
        if (NearZero(localRect.Width()) && NearZero(localRect.Height())) {
            continue;
        }
        auto it = lineGroup.find(localRect.GetY());
        if (it == lineGroup.end()) {
            std::vector<RectF> rects = { localRect };
            lineGroup.emplace(localRect.GetY(), std::make_pair(localRect, rects));
            continue;
        }
        auto lineRect = it->second.first;
        it->second.first = lineRect.CombineRectT(localRect);
        if (it->second.second.empty()) {
            it->second.second.emplace_back(localRect);
            continue;
        }
        auto backRect = it->second.second.back();
        if (NearEqual(backRect.Left(), localRect.Right()) || NearEqual(backRect.Right(), localRect.Left())) {
            it->second.second.back() = backRect.CombineRectT(localRect);
        } else {
            it->second.second.emplace_back(localRect);
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

std::u16string TextBase::TruncateText(const std::u16string& text, const size_t& length) const
{
    const size_t maxLength = length;
    size_t charCount = 0;
    size_t byteIndex = 0;

    while (byteIndex < text.size() && charCount < maxLength) {
        charCount++;
        byteIndex += (text[byteIndex] >= 0xD800 && text[byteIndex] <= 0xDBFF) ?
            UTF16_SURROGATE_PAIR_LENGTH : UTF16_SINGLE_CHAR_LENGTH;
    }

    if (charCount >= maxLength) {
        return text.substr(0, byteIndex);
    }
    return text;
}

size_t TextBase::CountUtf16Chars(const std::u16string& s)
{
    size_t charCount = 0;
    size_t i = 0;
    while (i < s.size()) {
        charCount++;
        i += (s[i] >= 0xD800 && s[i] <= 0xDBFF) ? UTF16_SURROGATE_PAIR_LENGTH : UTF16_SINGLE_CHAR_LENGTH;
    }
    return charCount;
}

LayoutCalPolicy TextBase::GetLayoutCalPolicy(LayoutWrapper* layoutWrapper, bool isHorizontal)
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, LayoutCalPolicy::NO_MATCH);
    auto layoutPolicyProperty = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_RETURN(layoutPolicyProperty, LayoutCalPolicy::NO_MATCH);
    if (isHorizontal) {
        CHECK_NULL_RETURN(layoutPolicyProperty->widthLayoutPolicy_, LayoutCalPolicy::NO_MATCH);
        return layoutPolicyProperty->widthLayoutPolicy_.value();
    }
    CHECK_NULL_RETURN(layoutPolicyProperty->heightLayoutPolicy_, LayoutCalPolicy::NO_MATCH);
    return layoutPolicyProperty->heightLayoutPolicy_.value();
}

float TextBase::GetConstraintMaxLength(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& constraint, bool isHorizontal)
{
    auto layoutCalPolicy = GetLayoutCalPolicy(layoutWrapper, isHorizontal);
    if (layoutCalPolicy == LayoutCalPolicy::MATCH_PARENT) {
        return isHorizontal ? constraint.parentIdealSize.Width().value_or(0.0f)
                            : constraint.parentIdealSize.Height().value_or(0.0f);
    }
    return isHorizontal ? constraint.maxSize.Width() : constraint.maxSize.Height();
}

void TextGestureSelector::DoGestureSelection(const TouchEventInfo& info)
{
    if (!isStarted_ || info.GetChangedTouches().empty()) {
        return;
    }
    auto locationInfo = info.GetChangedTouches().front();
    auto touchType = locationInfo.GetTouchType();
    switch (touchType) {
        case TouchType::UP:
            EndGestureSelection(locationInfo);
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
    auto locationInfo = info.GetChangedTouches().front();
    auto localOffset = locationInfo.GetLocalLocation();
    if (!isSelecting_) {
        if (LessOrEqual((localOffset - startOffset_).GetDistance(), minMoveDistance_.ConvertToPx())) {
            return;
        }
        isSelecting_ = true;
        selectingFingerId_ = locationInfo.GetFingerId();
    }
    auto index = GetTouchIndex({ localOffset.GetX(), localOffset.GetY() });
    auto start = std::min(index, start_);
    auto end = std::max(index, end_);
    OnTextGestureSelectionUpdate(start, end, info);
}

std::pair<std::string, std::string> TextBase::DetectTextDiff(const std::string& latestContent)
{
    const std::string& beforeText = textCache_;
    std::string addedText;
    std::string removedText;
    size_t prefixLen = 0;
    size_t minLength = std::min(beforeText.length(), latestContent.length());
    while (prefixLen < minLength && beforeText[prefixLen] == latestContent[prefixLen]) {
        prefixLen++;
    }
    while (prefixLen > 0 && ((beforeText[prefixLen] & 0xC0) == 0x80)) {
        prefixLen--;
    }
    size_t suffixLen = 0;
    size_t remainBefore = beforeText.length() - prefixLen;
    size_t remainAfter = latestContent.length() - prefixLen;
    size_t minSuffix = std::min(remainBefore, remainAfter);
    while (suffixLen < minSuffix &&
        beforeText[beforeText.length() - 1 - suffixLen] == latestContent[latestContent.length() - 1 - suffixLen]) {
        suffixLen++;
    }
    while (suffixLen > 0 && ((beforeText[beforeText.size() - suffixLen] & 0xC0) == 0x80)) {
        suffixLen--;
    }
    size_t removeStart = prefixLen;
    size_t removeEnd = beforeText.length() - suffixLen;
    if (removeEnd > removeStart) {
        removedText = beforeText.substr(removeStart, removeEnd - removeStart);
    }
    size_t addStart = prefixLen;
    size_t addEnd = latestContent.length() - suffixLen;
    if (addEnd > addStart) {
        addedText = latestContent.substr(addStart, addEnd - addStart);
    }
    return {std::move(addedText), std::move(removedText)};
}
}