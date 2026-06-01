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

#include "core/components_ng/manager/select_content_overlay/selection_container_child.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/select_content_overlay/selection_container.h"
#include "core/components_ng/manager/select_content_overlay/selection_container_manager.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text/base_text_select_overlay.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<SelectionContainerManager> GetSelectionContainerManagerFromNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto pipeline = node->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto selectOverlayManager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_RETURN(selectOverlayManager, nullptr);
    return selectOverlayManager->GetSelectionContainerManager();
}

RefPtr<SelectionContainer> GetSelectionContainerFromNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto selectionContainerId = node->GetSelectionContainerId();
    if (selectionContainerId <= 0) {
        return nullptr;
    }
    auto selectionContainerManager = GetSelectionContainerManagerFromNode(node);
    CHECK_NULL_RETURN(selectionContainerManager, nullptr);
    return selectionContainerManager->GetSelectionContainer(selectionContainerId);
}
} // namespace

SelectionCopyPayload::SelectionCopyPayload() = default;
SelectionCopyPayload::SelectionCopyPayload(const SelectionCopyPayload& other) = default;
SelectionCopyPayload::SelectionCopyPayload(SelectionCopyPayload&& other) noexcept = default;
SelectionCopyPayload& SelectionCopyPayload::operator=(const SelectionCopyPayload& other) = default;
SelectionCopyPayload& SelectionCopyPayload::operator=(SelectionCopyPayload&& other) noexcept = default;
SelectionCopyPayload::~SelectionCopyPayload() = default;

SelectionCopyPayload SelectionContainerChild::GetSelectionCopyPayload()
{
    SelectionCopyPayload payload;
    payload.plainText = GetSelectionText();
    payload.spanString = GetSelectedSpanString();
    return payload;
}

ScrollableParentResult SelectionContainerChild::FindNearestScrollable() const
{
    auto node = GetHostNode();
    CHECK_NULL_RETURN(node, {});
    auto selectionContainer = GetSelectionContainer();
    if (!selectionContainer) {
        selectionContainer = GetSelectionContainerFromNode(node);
    }
    auto containerNode = selectionContainer ? selectionContainer->GetHostNode() : nullptr;
    auto parent = node->GetAncestorNodeOfFrame(true);
    bool passedContainer = false;
    while (parent) {
        if (containerNode && parent == containerNode) {
            passedContainer = true;
            parent = parent->GetAncestorNodeOfFrame(true);
            continue;
        }
        auto scrollablePattern = parent->GetPattern<ScrollablePattern>();
        if (scrollablePattern && scrollablePattern->IsScrollable()) {
            return { scrollablePattern, !passedContainer };
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return {};
}

void SelectionContainerChild::RegisterChild()
{
    auto node = GetHostNode();
    CHECK_NULL_VOID(node);
    auto selectionContainerId = node->GetSelectionContainerId();
    if (selectionContainerId <= 0) {
        return;
    }
    auto selectionContainerManager = GetSelectionContainerManagerFromNode(node);
    CHECK_NULL_VOID(selectionContainerManager);
    auto child = AceType::DynamicCast<SelectionContainerChild>(WeakClaim(this).Upgrade());
    CHECK_NULL_VOID(child);
    selectionContainerManager->RegisterChild(selectionContainerId, child);
}

void SelectionContainerChild::UnregisterChild()
{
    NotifyContainerSelectionSpanTypeChanged({});
    auto node = GetHostNode();
    CHECK_NULL_VOID(node);
    auto selectionContainerId = node->GetSelectionContainerId();
    if (selectionContainerId <= 0) {
        return;
    }
    auto selectionContainerManager = GetSelectionContainerManagerFromNode(node);
    CHECK_NULL_VOID(selectionContainerManager);
    selectionContainerManager->UnregisterChild(selectionContainerId, node->GetId());
}

bool SelectionContainerChild::HandleSelectionStart(const Offset& localPoint, int32_t startIndex, int32_t endIndex)
{
    auto node = GetHostNode();
    CHECK_NULL_RETURN(node, false);
    auto selectionContainerId = node->GetSelectionContainerId();
    if (selectionContainerId <= 0) {
        return false;
    }

    SelectionStartEventInfo eventInfo;
    eventInfo.child = WeakClaim(this);
    eventInfo.localPoint = OffsetF(localPoint.GetX(), localPoint.GetY());
    eventInfo.startIndex = startIndex;
    eventInfo.endIndex = endIndex;

    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->HandleSelectionStart(eventInfo);
    }

    auto selectionContainerManager = GetSelectionContainerManagerFromNode(node);
    CHECK_NULL_RETURN(selectionContainerManager, false);
    return selectionContainerManager->HandleSelectionStart(selectionContainerId, eventInfo);
}

bool SelectionContainerChild::HandleSelectionUpdate(const Offset& localPoint)
{
    auto node = GetHostNode();
    CHECK_NULL_RETURN(node, false);
    auto selectionContainerId = node->GetSelectionContainerId();
    if (selectionContainerId <= 0) {
        return false;
    }

    SelectionEndEventInfo eventInfo;
    eventInfo.child = Claim(this);
    eventInfo.localPoint = OffsetF(localPoint.GetX(), localPoint.GetY());

    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->HandleSelectionUpdate(eventInfo);
    }

    auto selectionContainerManager = GetSelectionContainerManagerFromNode(node);
    CHECK_NULL_RETURN(selectionContainerManager, false);
    return selectionContainerManager->HandleSelectionUpdate(selectionContainerId, eventInfo);
}

bool SelectionContainerChild::ProcessGestureSelectionUpdate(const Offset& localPoint, const OffsetF& globalPoint)
{
    auto node = GetHostNode();
    CHECK_NULL_RETURN(node, false);
    auto selectionContainerId = node->GetSelectionContainerId();
    if (selectionContainerId <= 0) {
        return false;
    }

    SelectionEndEventInfo eventInfo;
    eventInfo.child = Claim(this);
    eventInfo.localPoint = OffsetF(localPoint.GetX(), localPoint.GetY());

    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->ProcessGestureSelectionUpdate(eventInfo, globalPoint);
    }

    auto selectionContainerManager = GetSelectionContainerManagerFromNode(node);
    CHECK_NULL_RETURN(selectionContainerManager, false);
    auto container = selectionContainerManager->GetSelectionContainer(selectionContainerId);
    CHECK_NULL_RETURN(container, false);
    return container->ProcessGestureSelectionUpdate(eventInfo, globalPoint);
}

bool SelectionContainerChild::ProcessGestureSelectionEnd(const Offset& localPoint, const OffsetF& globalPoint)
{
    auto node = GetHostNode();
    CHECK_NULL_RETURN(node, false);
    auto selectionContainerId = node->GetSelectionContainerId();
    if (selectionContainerId <= 0) {
        return false;
    }

    SelectionEndEventInfo eventInfo;
    eventInfo.child = Claim(this);
    eventInfo.localPoint = OffsetF(localPoint.GetX(), localPoint.GetY());

    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->ProcessGestureSelectionEnd(eventInfo, globalPoint);
    }

    auto selectionContainerManager = GetSelectionContainerManagerFromNode(node);
    CHECK_NULL_RETURN(selectionContainerManager, false);
    auto container = selectionContainerManager->GetSelectionContainer(selectionContainerId);
    CHECK_NULL_RETURN(container, false);
    return container->ProcessGestureSelectionEnd(eventInfo, globalPoint);
}


bool SelectionContainerChild::ProcessMouseLeftRelease(const Offset& localPoint)
{
    auto node = GetHostNode();
    CHECK_NULL_RETURN(node, false);
    auto selectionContainerId = node->GetSelectionContainerId();
    if (selectionContainerId <= 0) {
        return false;
    }

    SelectionEndEventInfo eventInfo;
    eventInfo.child = Claim(this);
    eventInfo.localPoint = OffsetF(localPoint.GetX(), localPoint.GetY());

    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->ProcessMouseLeftRelease(eventInfo);
    }

    auto selectionContainerManager = GetSelectionContainerManagerFromNode(node);
    CHECK_NULL_RETURN(selectionContainerManager, false);
    auto handled = selectionContainerManager->ProcessMouseLeftRelease(selectionContainerId, eventInfo);
    return handled;
}

bool SelectionContainerChild::IsSelectionSessionOwner() const
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->IsSelectionSessionOwner(Claim(const_cast<SelectionContainerChild*>(this)));
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, false);
    return container->IsSelectionSessionOwner(Claim(const_cast<SelectionContainerChild*>(this)));
}

void SelectionContainerChild::SetSelectionHoldCallback()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->SetSelectionHoldCallback();
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_VOID(container);
    container->SetSelectionHoldCallback();
}

bool SelectionContainerChild::IsSelectedBindSelectionMenu() const
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->IsSelectedBindSelectionMenu();
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, false);
    return container->IsSelectedBindSelectionMenu();
}

bool SelectionContainerChild::ExtendSelectionFromFixedAnchor(const Offset& localPoint)
{
    auto node = GetHostNode();
    CHECK_NULL_RETURN(node, false);
    auto selectionContainerId = node->GetSelectionContainerId();
    if (selectionContainerId <= 0) {
        return false;
    }

    SelectionEndEventInfo eventInfo;
    eventInfo.child = Claim(this);
    eventInfo.localPoint = OffsetF(localPoint.GetX(), localPoint.GetY());

    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->ExtendSelectionFromFixedAnchor(eventInfo);
    }

    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, false);
    return container->ExtendSelectionFromFixedAnchor(eventInfo);
}

void SelectionContainerChild::CloseSelectOverlay(bool animation, CloseReason reason)
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->CloseSelectOverlay(animation, reason);
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_VOID(container);
    container->CloseSelectOverlay(animation, reason);
}

void SelectionContainerChild::ProcessOverlay(const OverlayRequest& request)
{
    auto self = AceType::DynamicCast<SelectionContainerChild>(Claim(this));
    CHECK_NULL_VOID(self);
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->UpdateSelectionBoundaryChild(self);
        parentContainer->ProcessOverlay(request);
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_VOID(container);
    container->UpdateSelectionBoundaryChild(self);
    container->ProcessOverlay(request);
}

void SelectionContainerChild::SwitchToOverlayMode()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->SwitchToOverlayMode();
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_VOID(container);
    container->SwitchToOverlayMode();
}

void SelectionContainerChild::ToggleMenu()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->ToggleMenu();
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_VOID(container);
    container->ToggleMenu();
}

void SelectionContainerChild::HideMenu(bool noAnimation, bool showSubMenu)
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->HideMenu(noAnimation, showSubMenu);
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_VOID(container);
    container->HideMenu(noAnimation, showSubMenu);
}

bool SelectionContainerChild::IsUsingMouse()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->IsUsingMouse();
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, false);
    return container->IsUsingMouse();
}

bool SelectionContainerChild::IsTriggerParentToScroll()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->IsTriggerParentToScroll();
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, false);
    return container->IsTriggerParentToScroll();
}

bool SelectionContainerChild::HasScrollableParent()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->HasScrollableParent();
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, false);
    return container->HasScrollableParent();
}

void SelectionContainerChild::TriggerScrollableParentToScroll(const OffsetF& globalPoint, bool isStopAutoScroll)
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->TriggerScrollableParentToScroll(globalPoint, isStopAutoScroll);
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_VOID(container);
    container->TriggerScrollableParentToScroll(globalPoint, isStopAutoScroll);
}

bool SelectionContainerChild::ProcessMouseLeftSelectionUpdate(const Offset& localPoint, const OffsetF& globalPoint)
{
    auto node = GetHostNode();
    CHECK_NULL_RETURN(node, false);
    auto selectionContainerId = node->GetSelectionContainerId();
    if (selectionContainerId <= 0) {
        return false;
    }

    SelectionEndEventInfo eventInfo;
    eventInfo.child = Claim(this);
    eventInfo.localPoint = OffsetF(localPoint.GetX(), localPoint.GetY());

    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->ProcessMouseLeftSelectionUpdate(eventInfo, globalPoint);
    }

    auto selectionContainerManager = GetSelectionContainerManagerFromNode(node);
    CHECK_NULL_RETURN(selectionContainerManager, false);
    auto container = selectionContainerManager->GetSelectionContainer(selectionContainerId);
    CHECK_NULL_RETURN(container, false);
    return container->ProcessMouseLeftSelectionUpdate(eventInfo, globalPoint);
}

void SelectionContainerChild::StopMouseSelectionTracking(const OffsetF& globalPoint)
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->StopMouseSelectionTracking(globalPoint);
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_VOID(container);
    container->StopMouseSelectionTracking(globalPoint);
}

void SelectionContainerChild::UpdateHandleColor()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->UpdateHandleColor();
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_VOID(container);
    container->UpdateHandleColor();
}

std::optional<CopyOptions> SelectionContainerChild::GetContainerCopyOption() const
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->GetCopyOption();
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, CopyOptions::InApp);
    return container->GetCopyOption();
}

std::optional<bool> SelectionContainerChild::GetContainerEnableHapticFeedback() const
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->GetEnableHapticFeedback();
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, true);
    return container->GetEnableHapticFeedback();
}

std::optional<Color> SelectionContainerChild::GetContainerSelectedBackgroundColor() const
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->GetSelectedBackgroundColor();
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, std::nullopt);
    return container->GetSelectedBackgroundColor();
}

bool SelectionContainerChild::SelectOverlayIsOn()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->SelectOverlayIsOn();
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, false);
    return container->SelectOverlayIsOn();
}

void SelectionContainerChild::ResetAllSelection()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->ResetAllSelection();
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    if (container) {
        container->ResetAllSelection();
    }
}

bool SelectionContainerChild::HandleOnCopy()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->HandleOnCopy();
        return true;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, false);
    container->HandleOnCopy();
    return true;
}

bool SelectionContainerChild::HandleOnSelectAll()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->HandleOnSelectAll();
        return true;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, false);
    container->HandleOnSelectAll();
    return true;
}

void SelectionContainerChild::MarkChildSortDirty()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->MarkChildSortDirty();
        return;
    }

    auto node = GetHostNode();
    CHECK_NULL_VOID(node);
    auto selectionContainerId = node->GetSelectionContainerId();
    if (selectionContainerId <= 0) {
        return;
    }
    auto pipeline = node->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto selectOverlayManager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_VOID(selectOverlayManager);
    auto selectionContainerManager = selectOverlayManager->GetSelectionContainerManager();
    CHECK_NULL_VOID(selectionContainerManager);
    selectionContainerManager->MarkChildSortDirty(selectionContainerId);
}
void SelectionContainerChild::NotifySelectionChanged(const std::u16string& selectedText)
{
    auto hostNode = GetHostNode();
    std::vector<ChildSelectionInfo> selectionState;
    if (hostNode) {
        auto indexes = GetSelectionIndexes();
        selectionState.push_back({ hostNode->GetId(), indexes.startIndex, indexes.endIndex });
    }
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->OnSelectionRangeChanged({ selectedText }, selectionState);
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    if (container) {
        container->OnSelectionRangeChanged({ selectedText }, selectionState);
    }
}

void SelectionContainerChild::NotifyResponseTypeChanged(TextResponseType responseType)
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->OnChildResponseTypeChanged(responseType);
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    if (container) {
        container->OnChildResponseTypeChanged(responseType);
    }
}

void SelectionContainerChild::NotifySourceTypeChanged(SourceType sourceType)
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->SetSourceType(sourceType);
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    if (container) {
        container->SetSourceType(sourceType);
    }
}

void SelectionContainerChild::SetMouseMenuOffset(const OffsetF& offset)
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->SetMouseMenuOffset(offset);
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    if (container) {
        container->SetMouseMenuOffset(offset);
    }
}

bool SelectionContainerChild::BetweenContainerSelectedPosition(const Offset& globalOffset) const
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        return parentContainer->BetweenSelectedPosition(globalOffset);
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    CHECK_NULL_RETURN(container, false);
    return container->BetweenSelectedPosition(globalOffset);
}

void SelectionContainerChild::NotifySelectedTypeSave()
{
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->OnChildSelectedTypeSave();
        return;
    }

    auto node = GetHostNode();
    auto container = GetSelectionContainerFromNode(node);
    if (container) {
        container->OnChildSelectedTypeSave();
    }
}

void SelectionContainerChild::NotifyContainerSelectionSpanTypeChanged(const ChildSelectionSummary& selectionSummary)
{
    auto oldSummary = lastReportedSelectionSummary_.value_or(ChildSelectionSummary {});
    if (oldSummary == selectionSummary) {
        return;
    }
    auto node = GetHostNode();
    CHECK_NULL_VOID(node);
    auto childId = node->GetId();
    auto parentContainer = GetSelectionContainer();
    if (parentContainer) {
        parentContainer->OnChildSelectionSpanTypeChanged(childId, oldSummary, selectionSummary);
    } else {
        auto container = GetSelectionContainerFromNode(node);
        if (container) {
            container->OnChildSelectionSpanTypeChanged(childId, oldSummary, selectionSummary);
        }
    }
    if (selectionSummary.contributes) {
        lastReportedSelectionSummary_ = selectionSummary;
    } else {
        lastReportedSelectionSummary_.reset();
    }
}

} // namespace OHOS::Ace::NG
