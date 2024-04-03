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

#include "core/components_ng/manager/select_content_overlay/select_content_overlay_manager.h"

#include <optional>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/select_content_overlay/select_content_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<SelectContentOverlayPattern> GetSelectOverlayPattern(const WeakPtr<FrameNode>& overlayNode)
{
    auto node = overlayNode.Upgrade();
    CHECK_NULL_RETURN(node, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(node);
    CHECK_NULL_RETURN(selectOverlayNode, nullptr);
    return selectOverlayNode->GetPattern<SelectContentOverlayPattern>();
}
} // namespace

const RefPtr<SelectContentOverlayManager> SelectContentOverlayManager::GetOverlayManager(
    const RefPtr<SelectOverlayHolder>& holder)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto overlayManager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_RETURN(overlayManager, nullptr);
    auto contentManager = overlayManager->GetSelectContentOverlayManager();
    if (!holder) {
        return contentManager;
    }
    if (!contentManager->HasHolder(holder->GetOwnerId())) {
        contentManager->SetHolder(holder);
    }
    return contentManager;
}

void SelectContentOverlayManager::SetHolder(const RefPtr<SelectOverlayHolder>& holder)
{
    CHECK_NULL_VOID(holder);
    if (!selectOverlayHolder_) {
        SetHolderInternal(holder);
        return;
    }
    auto prevOwnerId = selectOverlayHolder_->GetOwnerId();
    auto ownerId = holder->GetOwnerId();
    if (selectionHoldId_ > 0 && ownerId != selectionHoldId_) {
        ResetSelectionRect();
        if (legacyManagerCallbacks_.selectionResetCallback) {
            legacyManagerCallbacks_.selectionResetCallback();
        }
    }
    if (prevOwnerId == ownerId) {
        return;
    }
    CloseInternal(prevOwnerId, false, CloseReason::CLOSE_REASON_HOLD_BY_OTHER);
    SetHolderInternal(holder);
}

void SelectContentOverlayManager::SetHolderInternal(const RefPtr<SelectOverlayHolder>& holder)
{
    // unbind old holder
    if (selectOverlayHolder_) {
        selectOverlayHolder_->OnBind(nullptr);
    }
    selectOverlayHolder_ = holder;
    // bind new holder
    if (selectOverlayHolder_) {
        selectOverlayHolder_->OnBind(WeakClaim(this));
    }
}
bool SelectContentOverlayManager::HasHolder(int32_t id)
{
    CHECK_NULL_RETURN(selectOverlayHolder_, false);
    return selectOverlayHolder_->GetOwnerId() == id;
}

void SelectContentOverlayManager::Show(bool animation, int32_t requestCode)
{
    CHECK_NULL_VOID(selectOverlayHolder_);
    auto info = BuildSelectOverlayInfo(requestCode);
    if (!info.menuInfo.menuIsShow && info.isUsingMouse) {
        return;
    }
    if (legacyManagerCallbacks_.closeCallback) {
        legacyManagerCallbacks_.closeCallback(false, true);
    }
    if (IsOpen()) {
        if (info.recreateOverlay || info.menuInfo.menuType != shareOverlayInfo_->menuInfo.menuType) {
            auto holder = selectOverlayHolder_;
            CloseInternal(selectOverlayHolder_->GetOwnerId(), false, CloseReason::CLOSE_REASON_BY_RECREATE);
            SetHolder(holder);
            CreateSelectOverlay(info, animation);
            return;
        }
        UpdateExistOverlay(info, animation, requestCode);
    } else {
        CreateSelectOverlay(info, animation);
    }
}

SelectOverlayInfo SelectContentOverlayManager::BuildSelectOverlayInfo(int32_t requestCode)
{
    SelectOverlayInfo overlayInfo;
    UpdateStatusInfos(overlayInfo);
    overlayInfo.menuCallback.onCopy = MakeMenuCallback(OptionMenuActionId::COPY, overlayInfo);
    overlayInfo.menuCallback.onPaste = MakeMenuCallback(OptionMenuActionId::PASTE, overlayInfo);
    overlayInfo.menuCallback.onCut = MakeMenuCallback(OptionMenuActionId::CUT, overlayInfo);
    overlayInfo.menuCallback.onSelectAll = MakeMenuCallback(OptionMenuActionId::SELECT_ALL, overlayInfo);
    overlayInfo.menuCallback.onCameraInput = MakeMenuCallback(OptionMenuActionId::CAMERA_INPUT, overlayInfo);
    overlayInfo.menuCallback.onAppear = MakeMenuCallback(OptionMenuActionId::APPEAR, overlayInfo);
    overlayInfo.menuCallback.onDisappear = MakeMenuCallback(OptionMenuActionId::DISAPPEAR, overlayInfo);
    overlayInfo.isUseOverlayNG = true;
    RegisterTouchCallback(overlayInfo);
    RegisterHandleCallback(overlayInfo);
    selectOverlayHolder_->OnUpdateSelectOverlayInfo(overlayInfo, requestCode);
    return overlayInfo;
}

void SelectContentOverlayManager::UpdateStatusInfos(SelectOverlayInfo& overlayInfo)
{
    auto firstHandle = selectOverlayHolder_->GetFirstHandleInfo();
    auto secondHandle = selectOverlayHolder_->GetSecondHandleInfo();
    if (firstHandle.has_value()) {
        overlayInfo.firstHandle = firstHandle.value();
    } else {
        overlayInfo.firstHandle.isShow = false;
    }
    if (secondHandle.has_value()) {
        overlayInfo.secondHandle = secondHandle.value();
    } else {
        overlayInfo.secondHandle.isShow = false;
    }
    SelectMenuInfo menuInfo;
    selectOverlayHolder_->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
    overlayInfo.menuInfo = menuInfo;
    overlayInfo.callerFrameNode = selectOverlayHolder_->GetOwner();
    overlayInfo.selectText = selectOverlayHolder_->GetSelectedText();
    overlayInfo.selectArea = selectOverlayHolder_->GetSelectArea();
}

void SelectContentOverlayManager::RegisterHandleCallback(SelectOverlayInfo& info)
{
    CHECK_NULL_VOID(selectOverlayHolder_);
    auto callback = selectOverlayHolder_->GetCallback();
    CHECK_NULL_VOID(callback);
    if (!callback->IsRegisterHandleCallback()) {
        return;
    }
    info.onHandleMoveStart = [weakCallback = WeakClaim(AceType::RawPtr(callback))](bool isFirst) {
        auto overlayCallback = weakCallback.Upgrade();
        CHECK_NULL_VOID(overlayCallback);
        overlayCallback->OnHandleMoveStart(isFirst);
    };
    info.onHandleMove = [weakCallback = WeakClaim(AceType::RawPtr(callback))](const RectF& rect, bool isFirst) {
        auto overlayCallback = weakCallback.Upgrade();
        CHECK_NULL_VOID(overlayCallback);
        overlayCallback->OnHandleMove(rect, isFirst);
    };
    info.onHandleMoveDone = [weakCallback = WeakClaim(AceType::RawPtr(callback))](const RectF& rect, bool isFirst) {
        auto overlayCallback = weakCallback.Upgrade();
        CHECK_NULL_VOID(overlayCallback);
        overlayCallback->OnHandleMoveDone(rect, isFirst);
    };
    info.onHandleReverse = [weakCallback = WeakClaim(AceType::RawPtr(callback))](bool isReverse) {
        auto overlayCallback = weakCallback.Upgrade();
        CHECK_NULL_VOID(overlayCallback);
        overlayCallback->OnHandleReverse(isReverse);
    };
}

void SelectContentOverlayManager::RegisterTouchCallback(SelectOverlayInfo& info)
{
    CHECK_NULL_VOID(selectOverlayHolder_);
    auto callback = selectOverlayHolder_->GetCallback();
    CHECK_NULL_VOID(callback);
    if (!callback->IsRegisterTouchCallback()) {
        return;
    }
    info.onTouchDown = [weakCallback = WeakClaim(AceType::RawPtr(callback))](const TouchEventInfo& event) {
        auto callback = weakCallback.Upgrade();
        CHECK_NULL_VOID(callback);
        callback->OnOverlayTouchDown(event);
    };
    info.onTouchUp = [weakCallback = WeakClaim(AceType::RawPtr(callback))](const TouchEventInfo& event) {
        auto callback = weakCallback.Upgrade();
        CHECK_NULL_VOID(callback);
        callback->OnOverlayTouchUp(event);
    };
    info.onTouchMove = [weakCallback = WeakClaim(AceType::RawPtr(callback))](const TouchEventInfo& event) {
        auto callback = weakCallback.Upgrade();
        CHECK_NULL_VOID(callback);
        callback->OnOverlayTouchMove(event);
    };
}

std::function<void()> SelectContentOverlayManager::MakeMenuCallback(
    OptionMenuActionId id, const SelectOverlayInfo& info)
{
    auto callback = selectOverlayHolder_->GetCallback();
    CHECK_NULL_RETURN(callback, nullptr);
    return [actionId = id, weakCallback = WeakClaim(AceType::RawPtr(callback)), menuType = info.menuInfo.menuType]() {
        auto callback = weakCallback.Upgrade();
        CHECK_NULL_VOID(callback);
        callback->OnMenuItemAction(actionId, menuType);
    };
}

void SelectContentOverlayManager::UpdateExistOverlay(SelectOverlayInfo info, bool animation, int32_t requestCode)
{
    auto pattern = GetSelectOverlayPattern(selectOverlayNode_);
    CHECK_NULL_VOID(pattern);
    pattern->UpdateIsSingleHandle(info.isSingleHandle);
    if (!info.isSingleHandle) {
        pattern->UpdateSelectArea(info.selectArea);
        pattern->SetSelectInfo(info.selectText);
    }
    pattern->UpdateIsShowHandleLine(info.isHandleLineShow);
    pattern->UpdateFirstAndSecondHandleInfo(info.firstHandle, info.secondHandle);
    pattern->UpdateMenuInfo(info.menuInfo);
    if (info.isSingleHandle) {
        if (selectOverlayHolder_->CheckRestartHiddenHandleTask(requestCode)) {
            pattern->RestartHiddenHandleTask(true);
        }
    } else {
        pattern->CancelHiddenHandleTask();
    }
    selectOverlayHolder_->OnHandleExistOverlay(info, requestCode);
    auto callback = selectOverlayHolder_->GetCallback();
    CHECK_NULL_VOID(callback);
    callback->OnAfterSelectOverlayShow(false);
}

void SelectContentOverlayManager::MarkInfoChange(SelectOverlayDirtyFlag dirty)
{
    CHECK_NULL_VOID(selectOverlayHolder_);
    CHECK_NULL_VOID(IsOpen());
    auto pattern = GetSelectOverlayPattern(selectOverlayNode_);
    CHECK_NULL_VOID(pattern);
    if ((dirty & DIRTY_SELECT_AREA) == DIRTY_SELECT_AREA) {
        auto selectArea = selectOverlayHolder_->GetSelectArea();
        pattern->UpdateSelectArea(selectArea);
    }
    if ((dirty & DIRTY_ALL_MENU_ITEM) == DIRTY_ALL_MENU_ITEM) {
        SelectMenuInfo menuInfo;
        selectOverlayHolder_->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
        pattern->UpdateSelectMenuInfo(menuInfo);
    }
    if ((dirty & DIRTY_COPY_ALL_ITEM) == DIRTY_COPY_ALL_ITEM) {
        SelectMenuInfo menuInfo;
        selectOverlayHolder_->OnUpdateMenuInfo(menuInfo, DIRTY_COPY_ALL_ITEM);
        auto oldMenuInfo = pattern->GetSelectMenuInfo();
        oldMenuInfo.showCopyAll = menuInfo.showCopyAll;
        pattern->UpdateSelectMenuInfo(oldMenuInfo);
    }
    if ((dirty & DIRTY_SELECT_TEXT) == DIRTY_SELECT_TEXT) {
        auto selectedInfo = selectOverlayHolder_->GetSelectedText();
        pattern->SetSelectInfo(selectedInfo);
    }
    UpdateHandleInfosWithFlag(dirty);
    selectOverlayHolder_->OnHandleMarkInfoChange(shareOverlayInfo_, dirty);
}

void SelectContentOverlayManager::MarkSelectOverlayDirty(PropertyChangeFlag changeFlag)
{
    CHECK_NULL_VOID(IsOpen());
    selectOverlayNode_.Upgrade()->MarkDirtyNode(changeFlag);
}

void SelectContentOverlayManager::UpdateHandleInfosWithFlag(int32_t updateFlag)
{
    auto pattern = GetSelectOverlayPattern(selectOverlayNode_);
    CHECK_NULL_VOID(pattern);
    std::optional<SelectHandleInfo> firstHandleInfo;
    if ((updateFlag & DIRTY_FIRST_HANDLE) == DIRTY_FIRST_HANDLE) {
        firstHandleInfo = selectOverlayHolder_->GetFirstHandleInfo();
    }
    std::optional<SelectHandleInfo> secondHandleInfo;
    if ((updateFlag & DIRTY_SECOND_HANDLE) == DIRTY_SECOND_HANDLE) {
        secondHandleInfo = selectOverlayHolder_->GetSecondHandleInfo();
    }
    if (!firstHandleInfo && !secondHandleInfo) {
        return;
    }
    if (firstHandleInfo && secondHandleInfo) {
        pattern->UpdateFirstAndSecondHandleInfo(*firstHandleInfo, *secondHandleInfo);
    } else if (firstHandleInfo) {
        pattern->UpdateFirstSelectHandleInfo(*firstHandleInfo);
    } else {
        pattern->UpdateSecondSelectHandleInfo(*secondHandleInfo);
    }
}

void SelectContentOverlayManager::CreateSelectOverlay(SelectOverlayInfo& info, bool animation)
{
    shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(info);
    auto overlayNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo_);
    selectOverlayNode_ = overlayNode;
    auto taskExecutor = Container::CurrentTaskExecutor();
    taskExecutor->PostTask(
        [animation, weak = WeakClaim(this), node = overlayNode] {
            auto manager = weak.Upgrade();
            CHECK_NULL_VOID(manager);
            manager->CreateAndMountNode(node, animation);
        },
        TaskExecutor::TaskType::UI);
}

void SelectContentOverlayManager::CreateAndMountNode(const RefPtr<FrameNode>& overlayNode, bool animation)
{
    CHECK_NULL_VOID(overlayNode);
    CHECK_NULL_VOID(overlayNode == selectOverlayNode_);
    auto rootNode = GetSelectOverlayRoot();
    CHECK_NULL_VOID(rootNode);
    // get keyboard index to put selet_overlay before keyboard node
    int32_t slot = DEFAULT_NODE_SLOT;
    int32_t index = 0;
    for (const auto& it : rootNode->GetChildren()) {
        if (it->GetTag() == V2::KEYBOARD_ETS_TAG) {
            slot = index;
            break;
        }
        index++;
    }

    overlayNode->MountToParent(rootNode, slot);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    if (!shareOverlayInfo_->isUsingMouse) {
        auto node = DynamicCast<SelectOverlayNode>(overlayNode);
        if (node) {
            node->ShowSelectOverlay(animation);
        }
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->AddAfterLayoutTask([weakNode = WeakPtr<FrameNode>(rootNode)]() {
        auto hostNode = weakNode.Upgrade();
        CHECK_NULL_VOID(hostNode);
        hostNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
    });
    CHECK_NULL_VOID(selectOverlayHolder_);
    auto callback = selectOverlayHolder_->GetCallback();
    CHECK_NULL_VOID(callback);
    callback->OnAfterSelectOverlayShow(true);
}

const RefPtr<FrameNode> SelectContentOverlayManager::GetSelectOverlayRoot()
{
    auto realRootNode = realRootNodeWeak_.Upgrade();
    if (realRootNode) {
        return realRootNode;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(shareOverlayInfo_, rootNode);
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        auto root = FindWindowScene(shareOverlayInfo_->callerFrameNode.Upgrade());
        rootNode = DynamicCast<FrameNode>(root);
    }
    realRootNodeWeak_ = rootNode;
    return rootNode;
}

/**
 * @description: This function will be used in SceneBoard Thread only.
 * if need to show the select-overlay component, it expects to receive the target component bound by
 * the select-overlay component to find the windowScene component.
 * if need to hide the select-overlay component, it expects to receive the the select-overlay component
 * to return the parent component. And the parent component will be the windowScene component exactly.
 */
RefPtr<UINode> SelectContentOverlayManager::FindWindowScene(RefPtr<FrameNode> targetNode)
{
    auto container = Container::Current();
    if (!container || !container->IsScenceBoardWindow()) {
        return rootNodeWeak_.Upgrade();
    }
    CHECK_NULL_RETURN(targetNode, nullptr);
    auto parent = targetNode->GetParent();
    while (parent && parent->GetTag() != V2::WINDOW_SCENE_ETS_TAG) {
        parent = parent->GetParent();
    }
    CHECK_NULL_RETURN(parent, nullptr);
    return parent;
}

void SelectContentOverlayManager::CloseInternal(int32_t id, bool animation, CloseReason reason)
{
    CHECK_NULL_VOID(selectOverlayHolder_);
    CHECK_NULL_VOID(selectOverlayHolder_->GetOwnerId() == id);
    auto overlay = selectOverlayNode_.Upgrade();
    CHECK_NULL_VOID(overlay);
    auto node = DynamicCast<SelectOverlayNode>(overlay);
    auto callback = selectOverlayHolder_->GetCallback();
    auto menuType = shareOverlayInfo_->menuInfo.menuType;
    if (node && animation) {
        ClearAllStatus();
        node->HideSelectOverlay([weakOverlay = WeakClaim(AceType::RawPtr(overlay)), managerWeak = WeakClaim(this)]() {
            auto manager = managerWeak.Upgrade();
            CHECK_NULL_VOID(manager);
            manager->DestroySelectOverlayNode(weakOverlay.Upgrade());
        });
    } else {
        DestroySelectOverlayNode(overlay);
        ClearAllStatus();
    }
    if (callback) {
        callback->OnCloseOverlay(menuType, reason);
    }
}

void SelectContentOverlayManager::DestroySelectOverlayNode(const RefPtr<FrameNode>& overlay)
{
    CHECK_NULL_VOID(overlay);
    auto rootNode = overlay->GetParent();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(overlay);
    rootNode->MarkNeedSyncRenderTree();
    rootNode->RebuildRenderContextTree();
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->AddAfterRenderTask([weakNode = WeakPtr<UINode>(rootNode)]() {
        auto hostNode = weakNode.Upgrade();
        CHECK_NULL_VOID(hostNode);
        if (AceType::InstanceOf<FrameNode>(hostNode)) {
            auto frameNode = AceType::DynamicCast<FrameNode>(hostNode);
            CHECK_NULL_VOID(frameNode);
            frameNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
        }
    });
}

void SelectContentOverlayManager::ClearAllStatus()
{
    selectOverlayNode_.Reset();
    shareOverlayInfo_.reset();
    if (selectOverlayHolder_) {
        selectOverlayHolder_->OnBind(nullptr);
    }
    selectOverlayHolder_.Reset();
}

bool SelectContentOverlayManager::CloseCurrent(bool animation, CloseReason reason)
{
    CHECK_NULL_RETURN(selectOverlayHolder_, false);
    CHECK_NULL_RETURN(selectOverlayNode_.Upgrade(), false);
    CloseInternal(selectOverlayHolder_->GetOwnerId(), animation, reason);
    return true;
}

void SelectContentOverlayManager::CloseWithOverlayId(int32_t overlayId, CloseReason reason, bool animation)
{
    CHECK_NULL_VOID(IsOpen());
    CHECK_NULL_VOID(overlayId == selectOverlayNode_.Upgrade()->GetId());
    CloseInternal(selectOverlayHolder_->GetOwnerId(), animation, reason);
}

void SelectContentOverlayManager::Close(int32_t id, bool animation, CloseReason reason)
{
    CloseInternal(id, animation, reason);
}

void SelectContentOverlayManager::ShowOptionMenu()
{
    auto pattern = GetSelectOverlayPattern(selectOverlayNode_);
    CHECK_NULL_VOID(pattern);
    pattern->UpdateMenuIsShow(true);
}

void SelectContentOverlayManager::HideOptionMenu()
{
    auto pattern = GetSelectOverlayPattern(selectOverlayNode_);
    CHECK_NULL_VOID(pattern);
    pattern->UpdateMenuIsShow(false);
}

void SelectContentOverlayManager::ToggleOptionMenu()
{
    CHECK_NULL_VOID(shareOverlayInfo_);
    auto pattern = GetSelectOverlayPattern(selectOverlayNode_);
    CHECK_NULL_VOID(pattern);
    pattern->UpdateMenuIsShow(!shareOverlayInfo_->menuInfo.menuIsShow);
}

void SelectContentOverlayManager::DisableMenu()
{
    auto pattern = GetSelectOverlayPattern(selectOverlayNode_);
    CHECK_NULL_VOID(pattern);
    pattern->DisableMenu(true);
}

void SelectContentOverlayManager::EnableMenu()
{
    auto pattern = GetSelectOverlayPattern(selectOverlayNode_);
    CHECK_NULL_VOID(pattern);
    pattern->DisableMenu(false);
}

void SelectContentOverlayManager::HideHandle()
{
    auto pattern = GetSelectOverlayPattern(selectOverlayNode_);
    CHECK_NULL_VOID(pattern);
    pattern->StartHiddenHandleTask(false);
}

bool SelectContentOverlayManager::IsOpen()
{
    auto overlayNode = selectOverlayNode_.Upgrade();
    return overlayNode && overlayNode->GetParent();
}

bool SelectContentOverlayManager::IsCreating()
{
    auto overlayNode = selectOverlayNode_.Upgrade();
    return overlayNode && !overlayNode->GetParent();
}

bool SelectContentOverlayManager::IsMenuShow()
{
    return IsOpen() && shareOverlayInfo_ && shareOverlayInfo_->menuInfo.menuIsShow;
}

bool SelectContentOverlayManager::IsSingleHandle()
{
    return IsOpen() && shareOverlayInfo_ && shareOverlayInfo_->isSingleHandle;
}

bool SelectContentOverlayManager::IsHandleReverse()
{
    return IsOpen() && shareOverlayInfo_ && shareOverlayInfo_->handleReverse;
}

void SelectContentOverlayManager::RestartHiddenHandleTask(bool isDelay)
{
    auto pattern = GetSelectOverlayPattern(selectOverlayNode_);
    CHECK_NULL_VOID(pattern);
    pattern->RestartHiddenHandleTask(isDelay);
}

void SelectContentOverlayManager::CancelHiddenHandleTask()
{
    auto pattern = GetSelectOverlayPattern(selectOverlayNode_);
    CHECK_NULL_VOID(pattern);
    pattern->CancelHiddenHandleTask();
}

RefPtr<SelectOverlayNode> SelectContentOverlayManager::GetSelectOverlayNode()
{
    return AceType::DynamicCast<SelectOverlayNode>(selectOverlayNode_.Upgrade());
}

OptionMenuType SelectContentOverlayManager::GetShowMenuType()
{
    return IsOpen() && shareOverlayInfo_ ? shareOverlayInfo_->menuInfo.menuType : OptionMenuType::NO_MENU;
}

void SelectContentOverlayManager::HandleGlobalEvent(const TouchEvent& touchPoint, const NG::OffsetF& rootOffset)
{
    NG::PointF point { touchPoint.x - rootOffset.GetX(), touchPoint.y - rootOffset.GetY() };
    if (touchPoint.type == TouchType::DOWN) {
        isIntercept_ = IsTouchInSelectOverlayArea(point);
    }
    if (!isIntercept_) {
        HandleSelectionEvent(point, touchPoint);
        if (selectOverlayHolder_ && selectOverlayHolder_->GetCallback()) {
            selectOverlayHolder_->GetCallback()->OnHandleGlobalEvent(point, touchPoint);
        }
    }
    if (touchPoint.type == TouchType::UP) {
        isIntercept_ = false;
    }
}

bool SelectContentOverlayManager::IsTouchInSelectOverlayArea(const PointF& point)
{
    auto current = selectOverlayNode_.Upgrade();
    CHECK_NULL_RETURN(current, false);
    auto selectOverlayNode = DynamicCast<SelectOverlayNode>(current);
    if (selectOverlayNode) {
        return selectOverlayNode->IsInSelectedOrSelectOverlayArea(point);
    }
    // get the menu rect not the out wrapper
    const auto& children = current->GetChildren();
    for (const auto& it : children) {
        auto child = DynamicCast<FrameNode>(it);
        if (child == nullptr) {
            continue;
        }
        auto frameRect = child->GetGeometryNode()->GetFrameRect();
        if (frameRect.IsInRegion(point)) {
            return true;
        }
    }
    return false;
}

void SelectContentOverlayManager::HandleSelectionEvent(const PointF& point, const TouchEvent& rawTouchEvent)
{
    CHECK_NULL_VOID(holdSelectionInfo_);
    CHECK_NULL_VOID(holdSelectionInfo_->checkTouchInArea);
    CHECK_NULL_VOID(holdSelectionInfo_->resetSelectionCallback);
    if (holdSelectionInfo_->IsAcceptEvent(rawTouchEvent.sourceType, rawTouchEvent.type) &&
        !holdSelectionInfo_->checkTouchInArea(point) && !IsOpen()) {
        ResetSelectionRect();
    }
}

void SelectContentOverlayManager::ResetSelectionRect()
{
    CHECK_NULL_VOID(holdSelectionInfo_);
    if (holdSelectionInfo_->resetSelectionCallback) {
        holdSelectionInfo_->resetSelectionCallback();
    }
    selectionHoldId_ = -1;
    holdSelectionInfo_.reset();
}

void SelectContentOverlayManager::SetHoldSelectionCallback(int32_t id, const HoldSelectionInfo& selectionInfo)
{
    if (id == selectionHoldId_) {
        return;
    }
    if (holdSelectionInfo_ && id != selectionHoldId_ && holdSelectionInfo_->resetSelectionCallback) {
        holdSelectionInfo_->resetSelectionCallback();
    }
    selectionHoldId_ = id;
    holdSelectionInfo_ = selectionInfo;
}

void SelectContentOverlayManager::RemoveHoldSelectionCallback(int32_t id)
{
    CHECK_NULL_VOID(holdSelectionInfo_);
    if (selectionHoldId_ == id) {
        selectionHoldId_ = -1;
        holdSelectionInfo_.reset();
    }
}
} // namespace OHOS::Ace::NG
