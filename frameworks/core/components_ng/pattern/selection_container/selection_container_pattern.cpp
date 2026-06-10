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

#include "core/components_ng/pattern/selection_container/selection_container_pattern.h"

#include "adapter/ohos/capability/clipboard/clipboard_impl.h"
#include "base/geometry/ng/point_t.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/common/clipboard/clipboard_proxy.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/event/key_event.h"
#include "core/gestures/drag_constants.h"
#include "core/gestures/drag_event.h"
#include "core/text/html_utils.h"

namespace OHOS::Ace::NG {
namespace {
struct AllowedSelectionCopyItem {
    RefPtr<SelectionContainerChild> child;
    SelectionCopyPayload payload;
};

struct CollectedCopyData {
    std::vector<AllowedSelectionCopyItem> allowedChildren;
    std::u16string clipboardText;
    RefPtr<MutableSpanString> mergedSpanString;
    bool hasSpanString = false;
};

CollectedCopyData CollectAllowedCopyChildren(const std::vector<WeakPtr<SelectionContainerChild>>& childList,
    const std::u16string& separator)
{
    CollectedCopyData result;
    result.mergedSpanString = AceType::MakeRefPtr<MutableSpanString>(u"");
    bool isFirst = true;
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        auto copyPayload = child->GetSelectionCopyPayload();
        if (copyPayload.plainText.empty()) {
            continue;
        }
        if (!child->FireOnWillCopy(copyPayload.plainText)) {
            TAG_LOGI(AceLogTag::ACE_TEXT, "HandleOnCopy blocked once by child onWillCopy");
            continue;
        }
        result.allowedChildren.push_back({ .child = child, .payload = copyPayload });
        if (!isFirst && !separator.empty()) {
            result.clipboardText.append(separator);
            result.mergedSpanString->AppendSpanString(AceType::MakeRefPtr<SpanString>(separator));
        }
        result.clipboardText.append(copyPayload.plainText);
        if (copyPayload.spanString) {
            result.hasSpanString = true;
            result.mergedSpanString->AppendSpanString(copyPayload.spanString);
        } else {
            result.mergedSpanString->AppendSpanString(AceType::MakeRefPtr<SpanString>(copyPayload.plainText));
        }
        isFirst = false;
    }
    return result;
}
} // namespace


std::u16string SelectionContainerPattern::GetSelectionText()
{
    auto childList = GetChildList();
    std::u16string selectedText;
    bool isFirst = true;
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        auto childSelectedText = child->GetSelectionText();
        if (childSelectedText.empty()) {
            continue;
        }
        if (!isFirst) {
            auto separator = GetTextJoinSeparator();
            if (!separator.empty()) {
                selectedText.append(separator);
            }
        }
        selectedText.append(childSelectedText);
        isFirst = false;
    }
    return selectedText;
}

RefPtr<FrameNode> SelectionContainerPattern::GetHostNode() const
{
    return GetHost();
}

RefPtr<SelectionSelectOverlay> SelectionContainerPattern::GetOrCreateSelectionSelectOverlay()
{
    if (!selectionSelectOverlay_) {
        selectionSelectOverlay_ = AceType::MakeRefPtr<SelectionSelectOverlay>(
            WeakPtr<TextBase>(Claim(this)), WeakClaim(this));
    }
    return selectionSelectOverlay_;
}

void SelectionContainerPattern::CloseSelectOverlay(bool animation, CloseReason reason)
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    CHECK_NULL_VOID(overlay);
    overlay->CloseOverlay(animation, reason);
}

void SelectionContainerPattern::ProcessOverlay(const OverlayRequest& request)
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    CHECK_NULL_VOID(overlay);
    overlay->ProcessOverlay(request);
}

void SelectionContainerPattern::SwitchToOverlayMode()
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    CHECK_NULL_VOID(overlay);
    overlay->SwitchToOverlayMode();
}

void SelectionContainerPattern::ToggleMenu()
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    CHECK_NULL_VOID(overlay);
    overlay->ToggleMenu();
}

void SelectionContainerPattern::HideMenu(bool noAnimation, bool showSubMenu)
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    CHECK_NULL_VOID(overlay);
    overlay->HideMenu(noAnimation, showSubMenu);
}

void SelectionContainerPattern::DisableMenu()
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    CHECK_NULL_VOID(overlay);
    overlay->DisableMenu();
}

void SelectionContainerPattern::UpdateAISelectMenu()
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    CHECK_NULL_VOID(overlay);
    overlay->UpdateAISelectMenu();
}

bool SelectionContainerPattern::IsCurrentMenuVisibile()
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    CHECK_NULL_RETURN(overlay, false);
    return overlay->IsCurrentMenuVisibile();
}

bool SelectionContainerPattern::GetIsHandleDragging()
{
    CHECK_NULL_RETURN(selectionSelectOverlay_, false);
    return selectionSelectOverlay_->GetIsHandleDragging();
}

bool SelectionContainerPattern::IsClickAtHandle(const GestureEvent& info)
{
    CHECK_NULL_RETURN(selectionSelectOverlay_, false);
    return selectionSelectOverlay_->IsClickAtHandle(info);
}

bool SelectionContainerPattern::IsTouchAtHandle(const TouchEventInfo& info)
{
    CHECK_NULL_RETURN(selectionSelectOverlay_, false);
    return selectionSelectOverlay_->IsTouchAtHandle(info);
}

void SelectionContainerPattern::UpdateAllHandlesOffset()
{
    CHECK_NULL_VOID(selectionSelectOverlay_);
    selectionSelectOverlay_->UpdateAllHandlesOffset();
}

void SelectionContainerPattern::UpdateViewPort()
{
    CHECK_NULL_VOID(selectionSelectOverlay_);
    selectionSelectOverlay_->UpdateViewPort();
}

void SelectionContainerPattern::MarkOverlayDirty()
{
    CHECK_NULL_VOID(selectionSelectOverlay_);
    selectionSelectOverlay_->MarkOverlayDirty();
}

bool SelectionContainerPattern::IsShowMouseMenu()
{
    CHECK_NULL_RETURN(selectionSelectOverlay_, false);
    return selectionSelectOverlay_->IsShowMouseMenu();
}

void SelectionContainerPattern::UpdateMenuOnWindowSizeChanged(WindowSizeChangeReason type)
{
    CHECK_NULL_VOID(selectionSelectOverlay_);
    selectionSelectOverlay_->UpdateMenuOnWindowSizeChanged(type);
}

void SelectionContainerPattern::SetMouseMenuOffset(const OffsetF& offset)
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    CHECK_NULL_VOID(overlay);
    overlay->SetMouseMenuOffset(offset);
}

bool SelectionContainerPattern::IsUsingMouse()
{
    return sourceType_ == SourceType::MOUSE;
}

void SelectionContainerPattern::OnSelectionMovingChildChange(const RefPtr<SelectionContainerChild>& child)
{
    UpdateScrollableParentByChild(child);
}

void SelectionContainerPattern::ResetScrollableParentOnScrollStop(bool isStopAutoScroll)
{
    if (!isStopAutoScroll) {
        return;
    }
    auto scrollablePattern = scrollableParent_.Upgrade();
    if (isTriggerParentToScroll_ && scrollablePattern) {
        auto notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
        scrollablePattern->HandleOnDragStatusCallback(DragEventType::DROP, notifyDragEvent);
    }
    scrollableParent_.Reset();
    scrollableParentIsInsideContainer_ = false;
    isTriggerParentToScroll_ = false;
}

void SelectionContainerPattern::UpdateScrollableParentByChild(const RefPtr<SelectionContainerChild>& child)
{
    CHECK_NULL_VOID(child);
    auto result = child->FindNearestScrollable();
    scrollableParent_ = result.scrollable;
    scrollableParentIsInsideContainer_ = result.isInsideContainer;
}

bool SelectionContainerPattern::IsPointInScrollableViewport(
    const RefPtr<ScrollablePattern>& scrollablePattern, const OffsetF& globalPoint)
{
    CHECK_NULL_RETURN(scrollablePattern, false);
    auto scrollableHost = scrollablePattern->GetHost();
    CHECK_NULL_RETURN(scrollableHost, false);
    auto scrollableFrameRect = scrollableHost->GetPaintRectWithTransform();
    return scrollableFrameRect.IsInRegion(PointF(globalPoint.GetX(), globalPoint.GetY()));
}

bool SelectionContainerPattern::CheckScrollableParentSize(const RefPtr<ScrollablePattern>& scrollablePattern)
{
    CHECK_NULL_RETURN(scrollablePattern, false);
    auto scrollAxis = scrollablePattern->GetAxis();
    auto scrollableHost = scrollablePattern->GetHost();
    CHECK_NULL_RETURN(scrollableHost, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto scrollableFrameRect = scrollableHost->GetPaintRectWithTransform();
    auto hostRect = host->GetPaintRectWithTransform();
    auto hostSize = scrollAxis == Axis::HORIZONTAL ? hostRect.Width() : hostRect.Height();
    auto scrollableParentSize = scrollAxis == Axis::HORIZONTAL ? scrollableFrameRect.Width() :
        scrollableFrameRect.Height();
    return GreatNotEqual(hostSize, scrollableParentSize);
}

bool SelectionContainerPattern::IsTriggerParentToScroll()
{
    return isTriggerParentToScroll_;
}

bool SelectionContainerPattern::HasScrollableParent()
{
    return scrollableParent_.Upgrade() != nullptr;
}

void SelectionContainerPattern::TriggerScrollableParentToScroll(const OffsetF& globalPoint, bool isStopAutoScroll)
{
    auto scrollablePattern = scrollableParent_.Upgrade();
    auto scrollableParentIsInsideContainer = scrollableParentIsInsideContainer_;
    if (!isStopAutoScroll && (!scrollablePattern || !IsPointInScrollableViewport(scrollablePattern, globalPoint))) {
        UpdateScrollableParentByChild(GetSelectionMovingChild());
        scrollablePattern = scrollableParent_.Upgrade();
        scrollableParentIsInsideContainer = scrollableParentIsInsideContainer_;
    }
    if (!scrollablePattern) {
        ResetScrollableParentOnScrollStop(isStopAutoScroll);
        return;
    }
    auto scrollAxis = scrollablePattern->GetAxis();
    if (!scrollablePattern->IsScrollable() || (scrollAxis != Axis::VERTICAL && scrollAxis != Axis::HORIZONTAL)) {
        ResetScrollableParentOnScrollStop(isStopAutoScroll);
        return;
    }
    if (!scrollableParentIsInsideContainer && !CheckScrollableParentSize(scrollablePattern)) {
        ResetScrollableParentOnScrollStop(isStopAutoScroll);
        return;
    }
    auto notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    notifyDragEvent->SetX(globalPoint.GetX());
    notifyDragEvent->SetY(globalPoint.GetY());
    scrollablePattern->HandleOnDragStatusCallback(
        isStopAutoScroll ? DragEventType::DROP : DragEventType::MOVE, notifyDragEvent);
    isTriggerParentToScroll_ = !isStopAutoScroll;
    ResetScrollableParentOnScrollStop(isStopAutoScroll);
}

void SelectionContainerPattern::EnableMouseLeftSelectionTracking(const OffsetF& globalPoint)
{
    if (!HasScrollableParent()) {
        return;
    }
    lastMouseLeftGlobalPoint_ = globalPoint;
    RegisterMouseLeftSelectionNodeChangeListener();
}

void SelectionContainerPattern::StopMouseLeftSelectionTracking()
{
    lastMouseLeftGlobalPoint_.reset();
    UnregisterMouseLeftSelectionNodeChangeListener();
}

void SelectionContainerPattern::RegisterMouseLeftSelectionNodeChangeListener()
{
    if (mouseLeftSelectionNodeChangeListenerRegistered_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RegisterNodeChangeListener();
    mouseLeftSelectionNodeChangeListenerRegistered_ = true;
}

void SelectionContainerPattern::UnregisterMouseLeftSelectionNodeChangeListener()
{
    if (!mouseLeftSelectionNodeChangeListenerRegistered_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->UnregisterNodeChangeListener();
    mouseLeftSelectionNodeChangeListenerRegistered_ = false;
}

void SelectionContainerPattern::RefreshMouseLeftSelectionOnFrameNodeChanged()
{
    CHECK_NULL_VOID(mouseLeftSelectionNodeChangeListenerRegistered_);
    CHECK_NULL_VOID(lastMouseLeftGlobalPoint_.has_value());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    NG::PointF localPoint(lastMouseLeftGlobalPoint_->GetX(), lastMouseLeftGlobalPoint_->GetY());
    NG::NGGestureRecognizer::Transform(localPoint, WeakClaim(Referenced::RawPtr(host)), true);
    HandleSelectionUpdate(OffsetF(localPoint.GetX(), localPoint.GetY()));
}

void SelectionContainerPattern::UpdateMovingChildForHandle(bool isFirstHandle)
{
    auto movingChild = isFirstHandle ? GetSelectionStartChild() : GetSelectionEndChild();
    if (!movingChild) {
        movingChild = GetSelectionMovingChild();
    }
    UpdateSelectionMovingChild(movingChild);
}

void SelectionContainerPattern::UpdateHandleColor()
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    CHECK_NULL_VOID(overlay);
    overlay->UpdateHandleColor();
}

bool SelectionContainerPattern::FireOnWillCopy(const std::u16string& text)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto eventHub = host->GetEventHub<SelectionContainerEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    return eventHub->FireOnWillCopy(text);
}

void SelectionContainerPattern::FireOnCopy(const std::u16string& text)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<SelectionContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnCopy(text);
}

void SelectionContainerPattern::OnSelectionRangeChanged(const std::vector<std::u16string>& selectedTexts,
    const std::vector<ChildSelectionInfo>& selectionState)
{
    if (selectionState == lastSelectionState_) {
        return;
    }
    lastSelectionState_ = selectionState;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<SelectionContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnTextSelectionChange(selectedTexts);
}

void SelectionContainerPattern::OnSelectionMenuOptionsUpdate(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
    const NG::OnMenuItemClickCallback&& onMenuItemClick, const NG::OnPrepareMenuCallback&& onPrepareMenuCallback)
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    CHECK_NULL_VOID(overlay);
    NG::OnMenuItemClickCallback onMenuItemClickCallback = std::move(onMenuItemClick);
    if (onMenuItemClickWithText_) {
        auto weak = AceType::WeakClaim(this);
        onMenuItemClickCallback = [weak](const MenuItemParam& menuItemParam) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, false);
            if (!pattern->onMenuItemClickWithText_) {
                return false;
            }
            return pattern->onMenuItemClickWithText_(menuItemParam, pattern->GetSelectionText());
        };
    }
    overlay->OnSelectionMenuOptionsUpdate(
        std::move(onCreateMenuCallback), std::move(onMenuItemClickCallback), std::move(onPrepareMenuCallback));
}

void SelectionContainerPattern::HandleOnCopy()
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    CHECK_NULL_VOID(overlay);
    auto selectedCopyOption = overlay->ResolveCopyOptionForSelectedText();
    CHECK_NULL_VOID(selectedCopyOption);
    auto copyOption = selectedCopyOption.value();

    auto data = CollectAllowedCopyChildren(GetChildList(), GetTextJoinSeparator());
    TAG_LOGI(AceLogTag::ACE_TEXT, "HandleOnCopy copyOption=%{public}d,allowedChildren=%{public}zu, textLen=%{public}zu",
        static_cast<int32_t>(copyOption), data.allowedChildren.size(), data.clipboardText.length());

    if (data.clipboardText.empty()) {
        overlay->HideMenu(true);
        return;
    }

    bool containerAllowed = FireOnWillCopy(data.clipboardText);
    if (!containerAllowed) {
        TAG_LOGI(AceLogTag::ACE_TEXT, "HandleOnCopy blocked by container onWillCopy");
        overlay->HideMenu(true);
        return;
    }

    WriteClipboard(data.clipboardText, data.mergedSpanString, data.hasSpanString, copyOption);
    overlay->HideMenu(true);

    for (const auto& item : data.allowedChildren) {
        item.child->FireOnCopy(item.payload.plainText);
    }
    FireOnCopy(data.clipboardText);
}

void SelectionContainerPattern::HandleOnCopyFromAI(const RefPtr<SelectionContainerChild>& child)
{
    CHECK_NULL_VOID(child);
    auto copyPayload = child->GetSelectionCopyPayload();
    if (copyPayload.plainText.empty()) {
        return;
    }
    auto copyOption = child->GetCopyOption();
    if (copyOption == CopyOptions::None) {
        return;
    }
    // 1. Child OnWillCopy
    if (!child->FireOnWillCopy(copyPayload.plainText)) {
        return;
    }
    // 2. Container OnWillCopy
    if (!FireOnWillCopy(copyPayload.plainText)) {
        return;
    }
    // 3. Write clipboard
    bool hasSpanString = copyPayload.spanString != nullptr;
    auto mergedSpanString = AceType::MakeRefPtr<MutableSpanString>(u"");
    if (hasSpanString) {
        mergedSpanString->AppendSpanString(copyPayload.spanString);
    } else {
        mergedSpanString->AppendSpanString(
            AceType::MakeRefPtr<SpanString>(copyPayload.plainText));
    }
    WriteClipboard(copyPayload.plainText, mergedSpanString, hasSpanString, copyOption);
    // 4. Child OnCopy + Container OnCopy
    child->FireOnCopy(copyPayload.plainText);
    FireOnCopy(copyPayload.plainText);
}

void SelectionContainerPattern::WriteClipboard(const std::u16string& clipboardText,
    const RefPtr<MutableSpanString>& mergedSpanString, bool hasSpanString, CopyOptions copyOption)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    if (!clipboard_) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    }
    CHECK_NULL_VOID(clipboard_);
    auto pasteData = UtfUtils::Str16DebugToStr8(clipboardText);
    if (hasSpanString) {
        HandleOnCopySpanString(mergedSpanString, copyOption);
    } else {
        HandleOnCopyWithoutSpanString(pasteData, copyOption);
    }
}

void SelectionContainerPattern::HandleOnCopySpanString(const RefPtr<SpanString>& spanString, CopyOptions copyOption)
{
    CHECK_NULL_VOID(spanString);
    CHECK_NULL_VOID(clipboard_);
#if defined(PREVIEW)
    clipboard_->SetData(spanString->GetString(), copyOption);
    return;
#endif
    AsyncHandleOnCopySpanStringHtml(spanString, copyOption);
}

void SelectionContainerPattern::AsyncHandleOnCopySpanStringHtml(
    const RefPtr<SpanString>& spanString, CopyOptions copyOption)
{
    CHECK_NULL_VOID(spanString);
    CHECK_NULL_VOID(clipboard_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto multiTypeRecordImpl = AceType::MakeRefPtr<MultiTypeRecordImpl>();
    spanString->EncodeTlv(multiTypeRecordImpl->GetSpanStringBuffer());
    multiTypeRecordImpl->SetPlainText(spanString->GetString());
    taskExecutor->PostTask(
        [spanString, multiTypeRecordImpl, copyOption, weak = WeakClaim(this),
            task = WeakClaim(RawPtr(taskExecutor))]() {
            CHECK_NULL_VOID(multiTypeRecordImpl);
            multiTypeRecordImpl->SetHtmlText(HtmlUtils::ToHtml(RawPtr(spanString)));
            auto uiTaskExecutor = task.Upgrade();
            CHECK_NULL_VOID(uiTaskExecutor);
            uiTaskExecutor->PostTask(
                [weak, multiTypeRecordImpl, copyOption]() {
                    auto pattern = weak.Upgrade();
                    CHECK_NULL_VOID(pattern && pattern->clipboard_ && multiTypeRecordImpl);
                    RefPtr<PasteDataMix> pasteData = pattern->clipboard_->CreatePasteDataMix();
                    pattern->clipboard_->AddMultiTypeRecord(pasteData, multiTypeRecordImpl);
                    pattern->clipboard_->SetData(pasteData, copyOption);
                },
                TaskExecutor::TaskType::UI, "SelectionContainerCopySpanStringSetClipboardData");
        },
        TaskExecutor::TaskType::BACKGROUND, "SelectionContainerCopySpanStringHtml");
}

void SelectionContainerPattern::HandleOnCopyWithoutSpanString(const std::string& pasteData, CopyOptions copyOption)
{
    CHECK_NULL_VOID(clipboard_);
    clipboard_->SetData(pasteData, copyOption);
}

bool SelectionContainerPattern::SelectOverlayIsOn()
{
    CHECK_NULL_RETURN(selectionSelectOverlay_, false);
    return selectionSelectOverlay_->SelectOverlayIsOn();
}

void SelectionContainerPattern::RebuildSelectionSpanTypeByFullScan()
{
    childSelectionSummaryMap_.clear();
    selectedTextCount_ = 0;
    selectedImageCount_ = 0;
    selectedBuilderCount_ = 0;
    selectedMixedCount_ = 0;
    auto childList = GetChildList();
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        ChildSelectionSummary summary;
        summary.contributes = !child->GetSelectionText().empty();
        summary.type = child->GetSelectionSpanType();
        if (!summary.contributes) {
            continue;
        }
        auto childNode = child->GetHostNode();
        if (childNode) {
            childSelectionSummaryMap_[childNode->GetId()] = summary;
        }
        ApplySelectionSummaryDelta(summary, 1);
    }
    RecomputeSelectedTypeFromSummary();
}

void SelectionContainerPattern::OnChildSelectionSpanTypeChanged(
    int32_t childId, const ChildSelectionSummary& oldSummary, const ChildSelectionSummary& newSummary)
{
    ApplySelectionSummaryDelta(oldSummary, -1);
    ApplySelectionSummaryDelta(newSummary, 1);
    if (newSummary.contributes) {
        childSelectionSummaryMap_[childId] = newSummary;
    } else {
        childSelectionSummaryMap_.erase(childId);
    }
    RecomputeSelectedTypeFromSummary();
}

void SelectionContainerPattern::ApplySelectionSummaryDelta(const ChildSelectionSummary& summary, int32_t delta)
{
    if (!summary.contributes) {
        return;
    }
    if (summary.type == TextSpanType::IMAGE) {
        selectedImageCount_ = std::max(0, selectedImageCount_ + delta);
    } else if (summary.type == TextSpanType::TEXT || summary.type == TextSpanType::NONE) {
        selectedTextCount_ = std::max(0, selectedTextCount_ + delta);
    } else if (summary.type == TextSpanType::BUILDER) {
        selectedBuilderCount_ = std::max(0, selectedBuilderCount_ + delta);
    } else if (summary.type == TextSpanType::MIXED) {
        selectedMixedCount_ = std::max(0, selectedMixedCount_ + delta);
    }
}

void SelectionContainerPattern::RecomputeSelectedTypeFromSummary()
{
    if (selectedMixedCount_ > 0) {
        selectedType_ = TextSpanType::MIXED;
        return;
    }
    auto selectedKindCount = 0;
    selectedKindCount += selectedTextCount_ > 0 ? 1 : 0;
    selectedKindCount += selectedImageCount_ > 0 ? 1 : 0;
    selectedKindCount += selectedBuilderCount_ > 0 ? 1 : 0;
    if (selectedKindCount > 1) {
        selectedType_ = TextSpanType::MIXED;
        return;
    }
    if (selectedImageCount_ > 0) {
        selectedType_ = TextSpanType::IMAGE;
    } else if (selectedTextCount_ > 0) {
        selectedType_ = TextSpanType::TEXT;
    } else if (selectedBuilderCount_ > 0) {
        selectedType_ = TextSpanType::BUILDER;
    } else {
        selectedType_ = TextSpanType::NONE;
    }
}

bool SelectionContainerPattern::IsSelectedTypeChange()
{
    return selectedType_.has_value() && oldSelectedType_ != selectedType_.value();
}

bool SelectionContainerPattern::CheckSelectedTypeChange()
{
    auto changed = IsSelectedTypeChange();
    if (changed) {
        oldSelectedType_ = selectedType_.value();
    }
    return changed;
}

void SelectionContainerPattern::SaveOldSelectedType()
{
    oldSelectedType_ = selectedType_.value_or(TextSpanType::NONE);
}

CopyOptions SelectionContainerPattern::GetCopyOption() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, CopyOptions::InApp);
    auto layoutProperty = host->GetLayoutProperty<SelectionContainerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, CopyOptions::InApp);
    return layoutProperty->GetCopyOptionValue(CopyOptions::InApp);
}

std::optional<Color> SelectionContainerPattern::GetSelectedBackgroundColor() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto layoutProperty = host->GetLayoutProperty<SelectionContainerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    return layoutProperty->GetSelectedBackgroundColor();
}

void SelectionContainerPattern::OnModifyDone()
{
    StackPattern::OnModifyDone();
    if (GetCopyOption() != CopyOptions::None || HasSelectableText()) {
        InitKeyEvent();
    }
    if (hasModifyDone_ && pendingContainerPropertyUpdateFlags_ != 0) {
        NotifyRegisteredChildrenPropertyUpdate(pendingContainerPropertyUpdateFlags_);
    }
    pendingContainerPropertyUpdateFlags_ = 0;
    hasModifyDone_ = true;
    if (selectionSelectOverlay_) {
        selectionSelectOverlay_->UpdateHandleColor();
    }
}

void SelectionContainerPattern::InitKeyEvent()
{
    CHECK_NULL_VOID(!keyEventInitialized_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    auto keyTask = [weak = WeakClaim(this)](const KeyEvent& keyEvent) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->HandleKeyEvent(keyEvent);
    };
    focusHub->SetOnKeyEventInternal(std::move(keyTask));
    keyEventInitialized_ = true;
}

bool SelectionContainerPattern::HandleKeyEvent(const KeyEvent& keyEvent)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    TAG_LOGI(AceLogTag::ACE_TEXT, "SelectionContainerPattern::HandleKeyEvent [action:%{public}d]", keyEvent.action);
    if (keyEvent.action != KeyAction::DOWN) {
        return false;
    }
    if (keyEvent.IsCtrlWith(KeyCode::KEY_C)) {
        HandleOnCopy();
        return true;
    }
    if (keyEvent.IsCtrlWith(KeyCode::KEY_A)) {
        HandleOnSelectAll();
        CloseSelectOverlay();
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        return true;
    }
    return false;
}

void SelectionContainerPattern::MarkContainerPropertyUpdate(uint32_t flags)
{
    pendingContainerPropertyUpdateFlags_ |= flags;
}

void SelectionContainerPattern::UpdatePropertyImpl(
    const std::string& key, RefPtr<PropertyValueBase> value)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutPropertyPtr<SelectionContainerLayoutProperty>();
    CHECK_NULL_VOID(property);
    CHECK_NULL_VOID(value);
    if (key == "SelectionContainerCaretColor") {
        if (auto realValue = std::get_if<Color>(&(value->GetValue()))) {
            property->UpdateCaretColor(*realValue);
        }
    } else if (key == "SelectionContainerSelectedBackgroundColor") {
        if (auto realValue = std::get_if<Color>(&(value->GetValue()))) {
            property->UpdateSelectedBackgroundColor(*realValue);
            MarkContainerPropertyUpdate(
                static_cast<uint32_t>(SelectionContainerPropertyChange::SELECTED_BACKGROUND_COLOR));
        }
    }
    if (frameNode->GetRerenderable()) {
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void SelectionContainerPattern::HandleOnSelectAll()
{
    auto childList = GetChildList();
    RefPtr<SelectionContainerChild> firstSelectedChild;
    RefPtr<SelectionContainerChild> lastSelectedChild;
    std::vector<std::u16string> selectedTexts;
    std::vector<ChildSelectionInfo> selectionState;
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (!child->HasSelectableText()) {
            child->SelectTextByIndex(-1, -1);
            continue;
        }
        child->SelectAll();
        auto childSelectionText = child->GetSelectionText();
        if (childSelectionText.empty()) {
            continue;
        }
        selectedTexts.push_back(std::move(childSelectionText));
        auto childHostNode = child->GetHostNode();
        if (childHostNode) {
            auto indexes = child->GetSelectionIndexes();
            selectionState.push_back({ childHostNode->GetId(), indexes.startIndex, indexes.endIndex });
        }

        if (!firstSelectedChild) {
            firstSelectedChild = child;
        }
        lastSelectedChild = child;
    }
    OnSelectionRangeChanged(selectedTexts, selectionState);
    selectionStartChild_ = firstSelectedChild;
    selectionEndChild_ = lastSelectedChild;
    if (firstSelectedChild) {
        firstSelectedChild->UpdateSelectionHandleInfo();
    }
    if (lastSelectedChild && lastSelectedChild != firstSelectedChild) {
        lastSelectedChild->UpdateSelectionHandleInfo();
    }
    CloseSelectOverlay(true);
    auto overlay = GetOrCreateSelectionSelectOverlay();
    if (IsUsingMouse()) {
        if (overlay && !GetSelectionText().empty()) {
            overlay->SetSelectionHoldCallback();
        }
    } else {
        ProcessOverlay({ .animation = true });
    }
    ReportSelectionText();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        child->ResetOriginCaretPosition();
    }
}

void SelectionContainerPattern::BindSelectionMenu(TextSpanType spanType, TextResponseType responseType,
    std::function<void()>& menuBuilder, const SelectMenuParam& menuParam)
{
    auto key = std::make_pair(spanType, responseType);
    auto it = selectionMenuMap_.find(key);
    if (it != selectionMenuMap_.end()) {
        if (menuBuilder == nullptr) {
            selectionMenuMap_.erase(it);
            return;
        }
        it->second->buildFunc = menuBuilder;
        it->second->onAppear = menuParam.onAppear;
        it->second->onDisappear = menuParam.onDisappear;
        it->second->onMenuShow = menuParam.onMenuShow;
        it->second->onMenuHide = menuParam.onMenuHide;
        it->second->onAppearWithText = menuParam.onAppearWithText;
        it->second->onMenuShowWithText = menuParam.onMenuShowWithText;
        it->second->onMenuHideWithText = menuParam.onMenuHideWithText;
        it->second->isValid = menuParam.isValid;
        return;
    }
    auto selectionMenuParams = std::make_shared<SelectionMenuParams>(
        spanType, menuBuilder, menuParam.onAppear, menuParam.onDisappear, responseType);
    selectionMenuParams->onMenuShow = menuParam.onMenuShow;
    selectionMenuParams->onMenuHide = menuParam.onMenuHide;
    selectionMenuParams->onAppearWithText = menuParam.onAppearWithText;
    selectionMenuParams->onMenuShowWithText = menuParam.onMenuShowWithText;
    selectionMenuParams->onMenuHideWithText = menuParam.onMenuHideWithText;
    selectionMenuParams->isValid = menuParam.isValid;
    selectionMenuMap_[key] = selectionMenuParams;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyWithOnProChange(PROPERTY_UPDATE_MEASURE_SELF);
}

std::shared_ptr<SelectionMenuParams> SelectionContainerPattern::GetMenuParams(
    TextSpanType spanType, TextResponseType responseType)
{
    std::vector<std::pair<TextSpanType, TextResponseType>> searchPairs = {
        { spanType, responseType },
        { spanType, TextResponseType::NONE },
    };
    if (spanType != TextSpanType::NONE) {
        searchPairs.push_back({ TextSpanType::NONE, responseType });
        searchPairs.push_back({ TextSpanType::NONE, TextResponseType::NONE });
    }
    for (const auto& key : searchPairs) {
        auto it = selectionMenuMap_.find(key);
        if (it != selectionMenuMap_.end()) {
            return it->second;
        }
    }
    return nullptr;
}

bool SelectionContainerPattern::IsSelectedBindSelectionMenu() const
{
    auto currentSpanType = selectedType_.value_or(TextSpanType::TEXT);
    return const_cast<SelectionContainerPattern*>(this)->GetMenuParams(
        currentSpanType, TextResponseType::SELECTED_BY_MOUSE) != nullptr;
}

void SelectionContainerPattern::SetSelectionHoldCallback()
{
    auto overlay = GetOrCreateSelectionSelectOverlay();
    if (overlay) {
        overlay->SetSelectionHoldCallback();
    }
}

void SelectionContainerPattern::OnHandleSelectionMenuCallback(
    SelectionMenuCalblackId callbackId, std::shared_ptr<SelectionMenuParams> menuParams)
{
    auto selectedText = GetSelectionText();
    switch (callbackId) {
        case SelectionMenuCalblackId::MENU_SHOW:
            if (menuParams->onMenuShowWithText) {
                menuParams->onMenuShowWithText(selectedText);
                return;
            }
            break;
        case SelectionMenuCalblackId::MENU_HIDE:
            if (menuParams->onMenuHideWithText) {
                menuParams->onMenuHideWithText(selectedText);
                return;
            }
            break;
        case SelectionMenuCalblackId::MENU_APPEAR:
            if (menuParams->onAppearWithText) {
                menuParams->onAppearWithText(selectedText);
                return;
            }
            break;
        default:
            break;
    }
    std::function<void(int32_t, int32_t)> callback;
    switch (callbackId) {
        case SelectionMenuCalblackId::MENU_SHOW:
            callback = menuParams->onMenuShow;
            break;
        case SelectionMenuCalblackId::MENU_HIDE:
            callback = menuParams->onMenuHide;
            break;
        case SelectionMenuCalblackId::MENU_APPEAR:
            callback = menuParams->onAppear;
            break;
        default:
            callback = nullptr;
    }
    CHECK_NULL_VOID(callback);
    callback(-1, -1);
}

void SelectionContainerPattern::SetSelectionMenuItemClickWithTextCallback(
    std::function<bool(const MenuItemParam&, const std::u16string&)>&& onMenuItemClickWithText)
{
    onMenuItemClickWithText_ = std::move(onMenuItemClickWithText);
}

void SelectionContainerPattern::CopySelectionMenuParams(SelectOverlayInfo& selectInfo)
{
    auto currentSpanType = selectedType_.value_or(TextSpanType::NONE);
    auto menuParams = GetMenuParams(currentSpanType, textResponseType_);
    if (menuParams == nullptr || !menuParams->isValid) {
        return;
    }
    selectInfo.menuInfo.menuBuilder = menuParams->buildFunc;
    auto weak = AceType::WeakClaim(this);
    selectInfo.menuCallback.onAppear = [weak, menuParams]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHandleSelectionMenuCallback(SelectionMenuCalblackId::MENU_APPEAR, menuParams);
    };
    selectInfo.menuCallback.onDisappear = menuParams->onDisappear;
    selectInfo.menuCallback.onMenuShow = [weak, menuParams]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHandleSelectionMenuCallback(SelectionMenuCalblackId::MENU_SHOW, menuParams);
    };
    selectInfo.menuCallback.onMenuHide = [weak, menuParams]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHandleSelectionMenuCallback(SelectionMenuCalblackId::MENU_HIDE, menuParams);
    };
}

FrameNodeChangeInfoFlag SelectionContainerPattern::CollectDescendantChangeFlags()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, FRAME_NODE_CHANGE_INFO_NONE);
    auto hostId = host->GetId();
    for (const auto& weakChild : GetChildList()) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        auto childHost = child->GetHostNode();
        CHECK_NULL_CONTINUE(childHost);
        auto flag = CollectFlagsFromChildToHost(childHost, hostId);
        if (flag != FRAME_NODE_CHANGE_INFO_NONE) {
            return flag;
        }
    }
    return FRAME_NODE_CHANGE_INFO_NONE;
}

FrameNodeChangeInfoFlag SelectionContainerPattern::CollectFlagsFromChildToHost(
    const RefPtr<FrameNode>& childHost, int32_t containerId)
{
    auto flag = childHost->GetChangeInfoFlag();
    auto current = childHost->GetAncestorNodeOfFrame(true);
    while (current) {
        if (current->GetId() == containerId) {
            break;
        }
        flag |= current->GetChangeInfoFlag();
        if (flag == FRAME_NODE_CHANGE_ALL) {
            return flag;
        }
        current = current->GetAncestorNodeOfFrame(true);
    }
    return flag;
}

OffsetF SelectionContainerPattern::GetContainerPaintOffsetWithTransform() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, {});
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    return host->GetPaintRectOffsetNG(false, true) - rootOffset;
}

void SelectionContainerPattern::OnFrameNodeChanged(FrameNodeChangeInfoFlag flag)
{
    if (selectionSelectOverlay_ && selectionSelectOverlay_->SelectOverlayIsOn()) {
        selectionSelectOverlay_->OnAncestorNodeChanged(flag);
    }
    RefreshMouseLeftSelectionOnFrameNodeChanged();
}

} // namespace OHOS::Ace::NG
