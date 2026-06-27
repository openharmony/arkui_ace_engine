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
#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"
#include "core/components_ng/pattern/text/text_event_hub.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/base_text_select_geometry_utils.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
namespace {
int32_t GetSelectableTextLength(const RefPtr<TextPattern>& pattern)
{
    CHECK_NULL_RETURN(pattern, 0);
    return static_cast<int32_t>(pattern->GetTextForDisplay().length()) + pattern->GetPlaceholderCount();
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

std::optional<RectF> TextSelectionChild::GetFirstHandleRect()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto selector = pattern->GetTextSelector();
    return selector.firstHandle;
}

std::optional<RectF> TextSelectionChild::GetSecondHandleRect()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto selector = pattern->GetTextSelector();
    return selector.secondHandle;
}

RectF TextSelectionChild::GetSelectionArea(SelectRectsType pos, SelectionAreaResultType& resultType)
{
    resultType = SelectionAreaResultType::NONE;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, {});
    auto selector = pattern->GetTextSelector();
    if (selector.SelectNothing()) {
        return {};
    }
    auto boxes = pattern->GetTextBoxes();
    if (boxes.empty()) {
        return {};
    }
    if (pos == SelectRectsType::LEFT_TOP_POINT) {
        boxes.erase(std::next(boxes.begin()), boxes.end());
        boxes.front().SetSize({ 0.0f, 0.0f });
    } else if (pos == SelectRectsType::RIGHT_BOTTOM_POINT) {
        boxes.erase(boxes.begin(), std::prev(boxes.end()));
        boxes.front().SetRect({ boxes.front().Right(), boxes.front().Bottom() }, { 0.0f, 0.0f });
    }

    auto textPaintOffset = GetChildPaintOffsetWithoutTransform();
    auto contentRect = pattern->GetTextContentRect();
    auto textRect = pattern->GetTextRect();
    auto textContentRect = pattern->GetTextContentRect(true);
    auto selectionArea = BaseTextSelectGeometryUtils::MergeSelectedBoxes(boxes, contentRect, textRect, textPaintOffset);
    RectF visibleContentRect;
    if (GetRenderClipValue() || LessOrEqual(textContentRect.Height(), contentRect.Height()) ||
        !GetClipHandleViewPortForChild(host, visibleContentRect)) {
        visibleContentRect = RectF(contentRect.GetOffset() + textPaintOffset, contentRect.GetSize());
        visibleContentRect = BaseTextSelectGeometryUtils::GetVisibleRect(host, visibleContentRect);
    }
    auto intersectRect = selectionArea.IntersectRectT(visibleContentRect);
    intersectRect.SetWidth(std::max(intersectRect.Width(), 0.0f));
    intersectRect.SetHeight(std::max(intersectRect.Height(), 0.0f));
    if (pos == SelectRectsType::ALL_LINES && intersectRect.IsEmpty()) {
        resultType = SelectionAreaResultType::CLIPPED_OUT;
        return {};
    }
    if (childHasTransform_) {
        intersectRect.SetOffset(intersectRect.GetOffset() - textPaintOffset);
        BaseTextSelectGeometryUtils::GetGlobalRectWithTransform(host, childHasTransform_, intersectRect);
    }
    resultType = SelectionAreaResultType::VISIBLE_AREA;
    return intersectRect;
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
    auto pattern = pattern_.Upgrade();
    auto defaultClip = Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    CHECK_NULL_RETURN(pattern, defaultClip);
    auto host = pattern->GetHost();
    return BaseTextSelectGeometryUtils::GetRenderClipValue(host, defaultClip);
}

bool TextSelectionChild::GetClipHandleViewPortForChild(const RefPtr<FrameNode>& host, RectF& rect)
{
    CHECK_NULL_RETURN(host, false);
    if (BaseTextSelectGeometryUtils::HasUnsupportedTransform(host, false)) {
        return false;
    }
    RectF contentRect;
    if (!BaseTextSelectGeometryUtils::GetFrameNodeContentRect(host, contentRect)) {
        return false;
    }
    contentRect.SetOffset(contentRect.GetOffset() + host->GetPaintRectWithTransform().GetOffset());
    CHECK_NULL_RETURN(BaseTextSelectGeometryUtils::CalculateClippedRect(host, contentRect), false);
    BaseTextSelectGeometryUtils::UpdateClipHandleViewPort(host, GetRenderClipValue(), contentRect);
    rect = contentRect;
    return true;
}

std::optional<RectF> TextSelectionChild::GetAncestorNodeViewPortForChild()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, std::nullopt);
    if (CanClipHandleWithViewPort()) {
        RectF viewPort;
        if (GetClipHandleViewPortForChild(host, viewPort)) {
            return viewPort;
        }
    }

    auto parent = host->GetAncestorNodeOfFrame(true);
    while (parent) {
        auto scrollableContainer = parent->GetPattern<NestableScrollContainer>();
        if (scrollableContainer) {
            return parent->GetTransformRectRelativeToWindow();
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return std::nullopt;
}

std::vector<AncestorNodeViewPortInfo> TextSelectionChild::GetAncestorNodeViewPortInfos()
{
    std::vector<AncestorNodeViewPortInfo> infos;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, infos);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, infos);
    auto parent = host->GetAncestorNodeOfFrame(true);
    while (parent) {
        auto scrollableContainer = parent->GetPattern<NestableScrollContainer>();
        if (scrollableContainer) {
            auto viewPort = parent->GetTransformRectRelativeToWindow();
            AncestorNodeViewPortInfo info;
            info.ancestorNode = parent;
            info.viewPort = viewPort;
            infos.emplace_back(info);
        }
        auto renderContext = parent->GetRenderContext();
        if (renderContext && renderContext->GetClipEdge().value_or(false)) {
            RectF visibleRect;
            RectF frameRect;
            parent->GetVisibleRect(visibleRect, frameRect);
            AncestorNodeViewPortInfo info;
            info.ancestorNode = parent;
            info.viewPort = visibleRect;
            infos.emplace_back(info);
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return infos;
}

HandleVisibleContentResult TextSelectionChild::GetHandleVisibleContentRect(
    const RectF& paintRect, RectF& visibleContentRect, HandleLevelMode handleLevelMode)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, HandleVisibleContentResult::INVISIBLE);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, HandleVisibleContentResult::INVISIBLE);
    auto contentRect = pattern->GetTextContentRect();
    if (!GetRenderClipValue()) {
        if (handleLevelMode == HandleLevelMode::EMBED) {
            return HandleVisibleContentResult::VISIBLE;
        }
        auto localPaintRect = paintRect;
        localPaintRect.SetOffset(localPaintRect.GetOffset() - GetChildPaintOffsetWithoutTransform());
        localPaintRect.SetOffset(
            OffsetF(localPaintRect.GetX() + localPaintRect.Width() / 2.0f, localPaintRect.GetY()));
        visibleContentRect = contentRect.CombineRectT(localPaintRect);
        visibleContentRect.SetOffset(visibleContentRect.GetOffset() + pattern->GetTextPaintOffset());
        visibleContentRect = BaseTextSelectGeometryUtils::GetVisibleRect(host, visibleContentRect);
        return HandleVisibleContentResult::NEED_CHECK;
    }
    visibleContentRect = RectF(contentRect.GetOffset() + pattern->GetTextPaintOffset(), contentRect.GetSize());
    if (handleLevelMode == HandleLevelMode::OVERLAY) {
        visibleContentRect = BaseTextSelectGeometryUtils::GetVisibleRect(host, visibleContentRect);
    }
    return HandleVisibleContentResult::NEED_CHECK;
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
    CHECK_NULL_VOID(!pattern->GetTextSelector().SelectNothing());
    CHECK_NULL_VOID(pattern->HasContent());
    pattern->CalculateHandleOffsetAndShowOverlay();
}

bool TextSelectionChild::BetweenSelectedPosition(const Offset& globalOffset)
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

OffsetF TextSelectionChild::GetChildPaintOffsetWithoutTransform() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, {});
    if (!childHasTransform_) {
        return host->GetTransformRelativeOffset();
    }
    OffsetF offset;
    auto parent = host;
    while (parent) {
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, {});
        offset += renderContext->GetPaintRectWithoutTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return offset;
}

bool TextSelectionChild::CheckChildHasTransformAttr() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    return BaseTextSelectGeometryUtils::HasTransformAttr(host);
}

bool TextSelectionChild::HasOrUpdateRenderTransform()
{
    UpdateTransformFlag();
    return childHasTransform_;
}

bool TextSelectionChild::CanClipHandleWithViewPort()
{
    return !HasOrUpdateRenderTransform();
}

void TextSelectionChild::UpdateTransformFlag()
{
    childHasTransform_ = CheckChildHasTransformAttr();
}

void TextSelectionChild::UpdateChildHandleGlobalOffset()
{
    HasOrUpdateRenderTransform();
    handleGlobalOffset_ = GetChildPaintOffsetWithoutTransform();
}

OffsetF TextSelectionChild::GetChildHandleGlobalOffset() const
{
    return handleGlobalOffset_;
}

} // namespace OHOS::Ace::NG
