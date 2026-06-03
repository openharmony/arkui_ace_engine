/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/text_selection_child.h"

#include <algorithm>

#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "base/utils/utf_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/select_content_overlay/select_overlay_holder.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
int32_t GetSelectableTextLength(const RefPtr<TextPattern>& pattern)
{
    CHECK_NULL_RETURN(pattern, 0);
    return static_cast<int32_t>(pattern->GetTextForDisplay().length()) + pattern->GetPlaceholderCount();
}

RectF ConvertRectToTargetNode(const RefPtr<FrameNode>& sourceNode, const RectF& rect,
    const RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_RETURN(sourceNode, {});
    CHECK_NULL_RETURN(targetNode, {});
    auto leftTop = sourceNode->ConvertPoint(rect.GetOffset(), targetNode);
    auto rightTop = sourceNode->ConvertPoint({ rect.Right(), rect.Top() }, targetNode);
    auto leftBottom = sourceNode->ConvertPoint({ rect.Left(), rect.Bottom() }, targetNode);
    auto rightBottom = sourceNode->ConvertPoint({ rect.Right(), rect.Bottom() }, targetNode);
    auto left = std::min({ leftTop.GetX(), rightTop.GetX(), leftBottom.GetX(), rightBottom.GetX() });
    auto right = std::max({ leftTop.GetX(), rightTop.GetX(), leftBottom.GetX(), rightBottom.GetX() });
    auto top = std::min({ leftTop.GetY(), rightTop.GetY(), leftBottom.GetY(), rightBottom.GetY() });
    auto bottom = std::max({ leftTop.GetY(), rightTop.GetY(), leftBottom.GetY(), rightBottom.GetY() });
    return { left, top, right - left, bottom - top };
}
} // namespace

TextSelectionChild::TextSelectionChild(const WeakPtr<TextPattern>& pattern) : pattern_(pattern) {}

std::u16string TextSelectionChild::GetSelectionText()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, u"");
    auto selector = pattern->GetTextSelector();
    if (selector.SelectNothing()) {
        return u"";
    }
    return pattern->GetSelectedText(selector.GetTextStart(), selector.GetTextEnd(),
        false, false, true);
}

RefPtr<FrameNode> TextSelectionChild::GetHostNode() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetHost();
}

std::optional<SelectHandleInfo> TextSelectionChild::GetFirstHandleInfo()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    CHECK_NULL_RETURN(pattern->selectOverlay_, std::nullopt);
    return pattern->selectOverlay_->GetFirstHandleInfo();
}

std::optional<SelectHandleInfo> TextSelectionChild::GetSecondHandleInfo()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    CHECK_NULL_RETURN(pattern->selectOverlay_, std::nullopt);
    return pattern->selectOverlay_->GetSecondHandleInfo();
}

RectF TextSelectionChild::GetSelectionArea(const RefPtr<FrameNode>& targetNode, SelectRectsType pos)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, {});
    CHECK_NULL_RETURN(targetNode, {});
    auto selector = pattern->GetTextSelector();
    if (selector.SelectNothing()) {
        return {};
    }
    auto boxes = pattern->GetTextBoxes();
    if (boxes.empty()) {
        return {};
    }

    if (pos == SelectRectsType::LEFT_TOP_POINT) {
        auto box = boxes.front();
        box.SetSize({ 0.0f, 0.0f });
        box.SetOffset(box.GetOffset() + pattern->GetTextRect().GetOffset());
        return ConvertRectToTargetNode(host, box, targetNode);
    }
    if (pos == SelectRectsType::RIGHT_BOTTOM_POINT) {
        auto box = boxes.back();
        box.SetRect({ box.Right(), box.Bottom() }, { 0.0f, 0.0f });
        box.SetOffset(box.GetOffset() + pattern->GetTextRect().GetOffset());
        return ConvertRectToTargetNode(host, box, targetNode);
    }

    RectF selectionArea;
    bool hasArea = false;
    auto textRect = pattern->GetTextRect();
    for (auto box : boxes) {
        if (box.IsEmpty()) {
            continue;
        }
        box.SetOffset(box.GetOffset() + textRect.GetOffset());
        auto areaInTarget = ConvertRectToTargetNode(host, box, targetNode);
        if (areaInTarget.IsEmpty()) {
            continue;
        }
        selectionArea = hasArea ? selectionArea.CombineRectT(areaInTarget) : areaInTarget;
        hasArea = true;
    }
    return hasArea ? selectionArea : RectF();
}

SelectionIndexRange TextSelectionChild::GetSelectionIndexes() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, SelectionIndexRange());
    auto selector = pattern->GetTextSelector();
    return { selector.baseOffset, selector.destinationOffset };
}

SelectionIndexRange TextSelectionChild::GetSelectionIndexesByPoints(
    const OffsetF& firstPoint, const OffsetF& secondPoint)
{
    return { GetSelectionIndexByPoint(firstPoint), GetSelectionIndexByPoint(secondPoint) };
}

int32_t TextSelectionChild::GetSelectionIndexByPoint(const OffsetF& point)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, -1);
    CHECK_NULL_RETURN(pattern->pManager_, -1);
    return pattern->GetHandleIndex(GetMovingHandleReferenceOffset(point));
}

Offset TextSelectionChild::GetMovingHandleReferenceOffset(const OffsetF& point) const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, Offset(point.GetX(), point.GetY()));
    auto handlePoint = point;
    auto contentRect = pattern->contentRect_;
    if (GetRenderClipValue()) {
        handlePoint.SetX(std::clamp(handlePoint.GetX(), contentRect.Left(), contentRect.Right()));
        handlePoint.SetY(std::clamp(handlePoint.GetY(), contentRect.Top(), contentRect.Bottom()));
    }
    auto textPaintOffset = contentRect.GetOffset() - OffsetF(0.0f, std::min(pattern->baselineOffset_, 0.0f));
    return Offset(handlePoint.GetX() - textPaintOffset.GetX(), handlePoint.GetY() - textPaintOffset.GetY());
}

bool TextSelectionChild::GetRenderClipValue() const
{
    auto defaultClip = Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, defaultClip);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, defaultClip);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, defaultClip);
    return renderContext->GetClipEdge().value_or(defaultClip);
}

void TextSelectionChild::SelectTextByIndex(int32_t startIndex, int32_t endIndex)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->HandleSelectionChange(startIndex, endIndex);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextSelectionChild::SelectAll()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->HandleSelectionChange(0, GetSelectableTextLength(pattern));
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextSelectionChild::UpdateSelectionHandleInfo()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->selectOverlay_);
    CHECK_NULL_VOID(!pattern->GetTextSelector().SelectNothing());
    CHECK_NULL_VOID(pattern->HasContent());
    pattern->CalculateHandleOffsetAndShowOverlay();
}

bool TextSelectionChild::BetweenSelectedPosition(const Offset& globalOffset) const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->BetweenSelectedPosition(globalOffset);
}

bool TextSelectionChild::IsSelectAll() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsSelectAll();
}

bool TextSelectionChild::HasSelectableText() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return CanSelect() && GetSelectableTextLength(pattern) > 0;
}

bool TextSelectionChild::CanSelect() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsSelectableAndCopy();
}

CopyOptions TextSelectionChild::GetCopyOption() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, CopyOptions::None);
    return pattern->GetCopyOptions();
}

TextSpanType TextSelectionChild::GetSelectionSpanType() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, TextSpanType::NONE);
    return pattern->selectedType_.value_or(TextSpanType::TEXT);
}

bool TextSelectionChild::HandleOnAskCelia(const std::u16string& selectedContent)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto menuOptionAndActions = pattern->GetTextDetectResult().
                                menuOptionAndAction["askCelia"];
    if (menuOptionAndActions.empty()) {
        return false;
    }
    AISpan aiSpan{
        .content = UtfUtils::Str16DebugToStr8(selectedContent),
        .type = TextDataDetectType::ASK_CELIA
    };
    pattern->ClickAIMenuOptions(aiSpan, *menuOptionAndActions.begin());
    return true;
}

bool TextSelectionChild::IsAskCeliaSupported() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsAskCeliaSupported();
}

bool TextSelectionChild::FireOnWillCopy(const std::u16string& selectedContent)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    auto eventHub = host->GetEventHub<TextEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    return eventHub->FireOnWillCopy(selectedContent);
}

void TextSelectionChild::FireOnCopy(const std::u16string& selectedContent)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnCopy(selectedContent);
}

SelectionCopyPayload TextSelectionChild::GetSelectionCopyPayload()
{
    SelectionCopyPayload payload;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, payload);
    return pattern->GetSelectionCopyPayload();
}

RefPtr<SpanString> TextSelectionChild::GetSelectedSpanString()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetSelectedSpanString();
}

void TextSelectionChild::ResetOriginCaretPosition()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->ResetOriginCaretPosition();
}

void TextSelectionChild::ReportSelectionText()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->ReportSelectedText();
}

void TextSelectionChild::StartVibratorByIndexChange(int32_t currentIndex, int32_t preIndex)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->StartVibratorByIndexChange(currentIndex, preIndex);
}

void TextSelectionChild::OnContainerPropertyUpdate(uint32_t flags)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    if (flags & static_cast<uint32_t>(SelectionContainerPropertyChange::COPY_OPTION)) {
        pattern->OnContainerCopyOptionUpdate();
    }
    if (flags & static_cast<uint32_t>(SelectionContainerPropertyChange::ENABLE_HAPTIC_FEEDBACK)) {
        pattern->OnContainerEnableHapticFeedbackUpdate();
    }
    if (flags & static_cast<uint32_t>(SelectionContainerPropertyChange::SELECTED_BACKGROUND_COLOR)) {
        pattern->OnContainerSelectedBackgroundColorUpdate();
    }
}
} // namespace OHOS::Ace::NG
