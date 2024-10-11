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

RefPtr<SelectContentOverlayPattern> GetSelectMenuPattern(const WeakPtr<SelectContentOverlayManager>& manager)
{
    auto overlayManager = manager.Upgrade();
    CHECK_NULL_RETURN(overlayManager, nullptr);
    auto pattern = overlayManager->GetMenuPattern();
    return AceType::DynamicCast<SelectContentOverlayPattern>(pattern);
}

RefPtr<SelectContentOverlayPattern> GetSelectHandlePattern(const WeakPtr<SelectContentOverlayManager>& manager)
{
    auto overlayManager = manager.Upgrade();
    CHECK_NULL_RETURN(overlayManager, nullptr);
    auto pattern = overlayManager->GetHandlePattern();
    return AceType::DynamicCast<SelectContentOverlayPattern>(pattern);
}
} // namespace

const RefPtr<SelectContentOverlayManager> SelectContentOverlayManager::GetOverlayManager(
    const RefPtr<SelectOverlayHolder>& holder)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
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
    info.enableHandleLevel = info.enableHandleLevel && !info.isUsingMouse;
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
    overlayInfo.menuCallback.onAIWrite = MakeMenuCallback(OptionMenuActionId::AI_WRITE, overlayInfo);
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
    info.onHandleMoveStart =
        [weakCallback = WeakClaim(AceType::RawPtr(callback))](const GestureEvent& event, bool isFirst) {
            auto overlayCallback = weakCallback.Upgrade();
            CHECK_NULL_VOID(overlayCallback);
            overlayCallback->OnHandleMoveStart(event, isFirst);
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
    info.onHandleIsHidden = [weakCallback = WeakClaim(AceType::RawPtr(callback))]() {
        auto overlayCallback = weakCallback.Upgrade();
        CHECK_NULL_VOID(overlayCallback);
        overlayCallback->OnHandleIsHidden();
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
    info.onClick = [weakCallback = WeakClaim(AceType::RawPtr(callback))](const GestureEvent& event, bool isClickCaret) {
        auto callback = weakCallback.Upgrade();
        CHECK_NULL_VOID(callback);
        callback->OnOverlayClick(event, isClickCaret);
    };
    info.onMouseEvent = [weakCallback = WeakClaim(AceType::RawPtr(callback))](const MouseInfo& event) {
        auto callback = weakCallback.Upgrade();
        CHECK_NULL_VOID(callback);
        callback->OnHandleMouseEvent(event);
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

void SelectContentOverlayManager::UpdateExistOverlay(const SelectOverlayInfo& info, bool animation, int32_t requestCode)
{
    // update menu node
    auto menuPattern = GetSelectMenuPattern(WeakClaim(this));
    if (menuPattern) {
        if (!info.isSingleHandle) {
            menuPattern->UpdateSelectArea(info.selectArea);
            menuPattern->SetSelectInfo(info.selectText);
        }
        menuPattern->UpdateMenuInfo(info.menuInfo);
        menuPattern->UpdateViewPort(info.ancestorViewPort);
    }
    // update handle node
    auto handlePattern = GetSelectHandlePattern(WeakClaim(this));
    if (handlePattern) {
        handlePattern->UpdateIsSingleHandle(info.isSingleHandle);
        handlePattern->UpdateIsShowHandleLine(info.isHandleLineShow);
        handlePattern->UpdateFirstAndSecondHandleInfo(info.firstHandle, info.secondHandle);
        TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY,
            "Update first %{public}s isShow %{public}d, second %{public}s isShow %{public}d",
            info.firstHandle.paintRect.ToString().c_str(), info.firstHandle.isShow,
            info.secondHandle.paintRect.ToString().c_str(), info.secondHandle.isShow);
        if (info.isSingleHandle) {
            if (selectOverlayHolder_->CheckRestartHiddenHandleTask(requestCode)) {
                handlePattern->RestartHiddenHandleTask(true);
            }
        } else {
            handlePattern->CancelHiddenHandleTask();
        }
    }
    selectOverlayHolder_->OnHandleExistOverlay(info, requestCode);
    NotifySelectOverlayShow(false);
}

void SelectContentOverlayManager::SwitchToHandleMode(HandleLevelMode mode, bool forceChange)
{
    CHECK_NULL_VOID(shareOverlayInfo_);
    if (shareOverlayInfo_->handleLevelMode == mode) {
        return;
    }
    if (selectOverlayHolder_ && selectOverlayHolder_->GetCallback()) {
        if (!forceChange && !selectOverlayHolder_->GetCallback()->CheckSwitchToMode(mode)) {
            return;
        }
        selectOverlayHolder_->GetCallback()->OnHandleLevelModeChanged(mode);
    }
    TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY, "Set handle mode: %{public}d", mode);
    shareOverlayInfo_->handleLevelMode = mode;
    auto handleNode = handleNode_.Upgrade();
    CHECK_NULL_VOID(handleNode);
    if (mode == HandleLevelMode::OVERLAY) {
        auto taskExecutor = Container::CurrentTaskExecutor();
        taskExecutor->PostTask(
            [weak = WeakClaim(this), node = handleNode] {
                auto manager = weak.Upgrade();
                CHECK_NULL_VOID(manager);
                CHECK_NULL_VOID(node);
                if (!manager->IsOpen()) {
                    return;
                }
                manager->DestroySelectOverlayNode(node);
                manager->MountNodeToRoot(node, false);
                node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            },
            TaskExecutor::TaskType::UI, "SwitchToOverlayModeTask");
        return;
    }
    if (mode == HandleLevelMode::EMBED) {
        auto taskExecutor = Container::CurrentTaskExecutor();
        taskExecutor->PostTask(
            [weak = WeakClaim(this), node = handleNode] {
                auto manager = weak.Upgrade();
                CHECK_NULL_VOID(manager);
                CHECK_NULL_VOID(node);
                if (!manager->IsOpen()) {
                    return;
                }
                manager->DestroySelectOverlayNode(node);
                manager->MountNodeToCaller(node, false);
                node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            },
            TaskExecutor::TaskType::UI, "SwitchToEmbedModeTask");
    }
}

void SelectContentOverlayManager::MarkInfoChange(SelectOverlayDirtyFlag dirty)
{
    CHECK_NULL_VOID(selectOverlayHolder_);
    CHECK_NULL_VOID(IsOpen());
    auto menuPattern = GetSelectMenuPattern(WeakClaim(this));
    if (menuPattern) {
        if ((dirty & DIRTY_SELECT_AREA) == DIRTY_SELECT_AREA) {
            auto selectArea = selectOverlayHolder_->GetSelectArea();
            menuPattern->UpdateSelectArea(selectArea);
        }
        if ((dirty & DIRTY_ALL_MENU_ITEM) == DIRTY_ALL_MENU_ITEM) {
            SelectMenuInfo menuInfo;
            selectOverlayHolder_->OnUpdateMenuInfo(menuInfo, DIRTY_ALL_MENU_ITEM);
            menuPattern->UpdateSelectMenuInfo(menuInfo);
        }
        if ((dirty & DIRTY_COPY_ALL_ITEM) == DIRTY_COPY_ALL_ITEM) {
            auto oldMenuInfo = menuPattern->GetSelectMenuInfo();
            SelectMenuInfo menuInfo = { .showCopy = oldMenuInfo.showCopy, .showCopyAll = oldMenuInfo.showCopyAll };
            selectOverlayHolder_->OnUpdateMenuInfo(menuInfo, DIRTY_COPY_ALL_ITEM);
            oldMenuInfo.showCopyAll = menuInfo.showCopyAll;
            oldMenuInfo.showCopy = menuInfo.showCopy;
            menuPattern->UpdateSelectMenuInfo(oldMenuInfo);
        }
        if ((dirty & DIRTY_SELECT_TEXT) == DIRTY_SELECT_TEXT) {
            auto selectedInfo = selectOverlayHolder_->GetSelectedText();
            menuPattern->SetSelectInfo(selectedInfo);
        }
    }
    if ((dirty & DIRTY_VIEWPORT) == DIRTY_VIEWPORT) {
        auto viewPort = selectOverlayHolder_->GetAncestorNodeViewPort();
        if (menuPattern) {
            menuPattern->UpdateViewPort(viewPort);
        }
        auto handlePattern = GetSelectHandlePattern(WeakClaim(this));
        if (handlePattern) {
            handlePattern->UpdateViewPort(viewPort);
        }
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
    auto pattern = GetSelectHandlePattern(WeakClaim(this));
    CHECK_NULL_VOID(pattern);
    std::optional<SelectHandleInfo> firstHandleInfo;
    if ((static_cast<uint32_t>(updateFlag) & DIRTY_FIRST_HANDLE) == DIRTY_FIRST_HANDLE) {
        firstHandleInfo = selectOverlayHolder_->GetFirstHandleInfo();
    }
    std::optional<SelectHandleInfo> secondHandleInfo;
    if ((static_cast<uint32_t>(updateFlag) & DIRTY_SECOND_HANDLE) == DIRTY_SECOND_HANDLE) {
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
    if (!info.enableHandleLevel) {
        CreateNormalSelectOverlay(info, animation);
        return;
    }
    CreateHandleLevelSelectOverlay(info, animation, info.handleLevelMode);
}

void SelectContentOverlayManager::CreateNormalSelectOverlay(SelectOverlayInfo& info, bool animation)
{
    shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(info);
    auto overlayNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo_);
    selectOverlayNode_ = overlayNode;
    auto taskExecutor = Container::CurrentTaskExecutor();
    taskExecutor->PostTask(
        [animation, weak = WeakClaim(this), node = overlayNode] {
            auto manager = weak.Upgrade();
            CHECK_NULL_VOID(manager);
            if (node && node == manager->selectOverlayNode_) {
                manager->MountNodeToRoot(node, animation);
                manager->NotifySelectOverlayShow(true);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUISelectOverlayCreate");
}

void SelectContentOverlayManager::CreateHandleLevelSelectOverlay(
    SelectOverlayInfo& info, bool animation, HandleLevelMode mode)
{
    TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY,
        "Show SelectOverlay, first %{public}s isShow %{public}d, second %{public}s isShow %{public}d",
        info.firstHandle.paintRect.ToString().c_str(), info.firstHandle.isShow,
        info.secondHandle.paintRect.ToString().c_str(), info.secondHandle.isShow);
    shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>(info);
    auto menuNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo_, SelectOverlayMode::MENU_ONLY);
    menuNode_ = menuNode;
    auto handleNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo_, SelectOverlayMode::HANDLE_ONLY);
    handleNode_ = handleNode;
    auto taskExecutor = Container::CurrentTaskExecutorSafely();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [animation, weak = WeakClaim(this), menuNode, handleNode, mode] {
            auto manager = weak.Upgrade();
            CHECK_NULL_VOID(manager);
            auto isMenuNodeValid = (menuNode && menuNode == manager->menuNode_);
            auto isHandleNodeValid = (handleNode && handleNode == manager->handleNode_);
            if (!isMenuNodeValid || !isHandleNodeValid) {
                return;
            }
            manager->MountNodeToRoot(menuNode, animation);
            if (mode == HandleLevelMode::EMBED) {
                manager->MountNodeToCaller(handleNode, animation);
            } else if (mode == HandleLevelMode::OVERLAY) {
                manager->MountNodeToRoot(handleNode, animation);
            }
            manager->NotifySelectOverlayShow(true);
        },
        TaskExecutor::TaskType::UI, "CreateHandleLevelSelectOverlay");
}

void SelectContentOverlayManager::MountNodeToRoot(const RefPtr<FrameNode>& overlayNode, bool animation)
{
    auto rootNode = GetSelectOverlayRoot();
    CHECK_NULL_VOID(rootNode);
    const auto& children = rootNode->GetChildren();
    auto slotIt = FindSelectOverlaySlot(rootNode, children);
    auto index = static_cast<int32_t>(std::distance(children.begin(), slotIt));
    auto slot = (index > 0) ? index : DEFAULT_NODE_SLOT;
    for (auto it = slotIt; it != children.end(); ++it) {
        // get keyboard index to put selet_overlay before keyboard node
        if ((*it)->GetTag() == V2::KEYBOARD_ETS_TAG) {
            slot = std::min(slot, index);
            break;
        }
        // keep handle node before menu node
        if ((*it)->GetTag() == V2::SELECT_OVERLAY_ETS_TAG) {
            slot = index;
            break;
        }
        // keep handle and menu node before magnifier
        if ((*it)->GetTag() == V2::TEXTINPUT_ETS_TAG) {
            slot = std::min(slot, index);
            break;
        }
        index++;
    }

    TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY, "MountNodeToRoot:%{public}s, id:%{public}d", rootNode->GetTag().c_str(),
        rootNode->GetId());
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
}

std::list<RefPtr<UINode>>::const_iterator SelectContentOverlayManager::FindSelectOverlaySlot(
    const RefPtr<FrameNode>& root, const std::list<RefPtr<UINode>>& children)
{
    auto begin = children.begin();
    CHECK_NULL_RETURN(selectOverlayHolder_, begin);
    auto callerNode = selectOverlayHolder_->GetOwner();
    CHECK_NULL_RETURN(callerNode, begin);
    RefPtr<UINode> prevNode = nullptr;
    auto parent = callerNode->GetParent();
    while (parent) {
        if (parent == root) {
            break;
        }
        prevNode = parent;
        parent = parent->GetParent();
    }
    CHECK_NULL_RETURN(parent, begin);
    CHECK_NULL_RETURN(prevNode, begin);
    for (auto it = begin; it != children.end(); ++it) {
        if (prevNode == *it) {
            return ++it;
        }
    }
    return begin;
}

void SelectContentOverlayManager::MountNodeToCaller(const RefPtr<FrameNode>& overlayNode, bool animation)
{
    CHECK_NULL_VOID(selectOverlayHolder_);
    auto ownerFrameNode = selectOverlayHolder_->GetOwner();
    CHECK_NULL_VOID(ownerFrameNode);
    TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY,
        "Mount SelectOverlay node: %{public}s, id: %{public}d", ownerFrameNode->GetTag().c_str(),
        ownerFrameNode->GetId());
    ownerFrameNode->SetOverlayNode(overlayNode);
    overlayNode->SetParent(AceType::WeakClaim(AceType::RawPtr(ownerFrameNode)));
    overlayNode->SetActive(true);
    auto overlayProperty = AceType::DynamicCast<LayoutProperty>(overlayNode->GetLayoutProperty());
    CHECK_NULL_VOID(overlayProperty);
    overlayProperty->SetIsOverlayNode(true);
    overlayProperty->UpdateAlignment(Alignment::CENTER);
    overlayProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    ownerFrameNode->MarkNeedSyncRenderTree();
    ownerFrameNode->RebuildRenderContextTree();
    overlayNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (!shareOverlayInfo_->isUsingMouse) {
        auto node = DynamicCast<SelectOverlayNode>(overlayNode);
        if (node) {
            node->ShowSelectOverlay(animation);
        }
    }
}

void SelectContentOverlayManager::NotifySelectOverlayShow(bool isCreated)
{
    CHECK_NULL_VOID(selectOverlayHolder_);
    auto callback = selectOverlayHolder_->GetCallback();
    CHECK_NULL_VOID(callback);
    callback->OnAfterSelectOverlayShow(isCreated);
}

const RefPtr<FrameNode> SelectContentOverlayManager::GetSelectOverlayRoot()
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(shareOverlayInfo_, rootNode);
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        auto root = FindWindowScene(shareOverlayInfo_->callerFrameNode.Upgrade());
        rootNode = DynamicCast<FrameNode>(root);
    }
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

bool SelectContentOverlayManager::CloseInternal(int32_t id, bool animation, CloseReason reason)
{
    CHECK_NULL_RETURN(selectOverlayHolder_, false);
    CHECK_NULL_RETURN(selectOverlayHolder_->GetOwnerId() == id, false);
    CHECK_NULL_RETURN(shareOverlayInfo_, false);
    TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY, "Close selectoverlay, id:%{public}d, reason %{public}d",
        id, reason);
    auto callback = selectOverlayHolder_->GetCallback();
    auto menuType = shareOverlayInfo_->menuInfo.menuType;
    auto pattern = GetSelectHandlePattern(WeakClaim(this));
    RefPtr<OverlayInfo> info = nullptr;
    if (pattern) {
        info = AceType::MakeRefPtr<OverlayInfo>();
        info->isSingleHandle = shareOverlayInfo_->isSingleHandle;
        info->isShowMenu = shareOverlayInfo_->menuInfo.menuIsShow;
        info->isHiddenHandle = pattern->IsHiddenHandle();
    }
    auto selectOverlayNode = selectOverlayNode_.Upgrade();
    auto menuNode = menuNode_.Upgrade();
    auto handleNode = handleNode_.Upgrade();
    if (animation && !shareOverlayInfo_->isUsingMouse) {
        ClearAllStatus();
        DestroySelectOverlayNodeWithAnimation(selectOverlayNode);
        DestroySelectOverlayNodeWithAnimation(menuNode);
        DestroySelectOverlayNodeWithAnimation(handleNode);
    } else {
        DestroySelectOverlayNode(selectOverlayNode);
        DestroySelectOverlayNode(menuNode);
        DestroySelectOverlayNode(handleNode);
        ClearAllStatus();
    }
    if (callback) {
        callback->OnCloseOverlay(menuType, reason, info);
    }
    return true;
}

void SelectContentOverlayManager::DestroySelectOverlayNodeWithAnimation(const RefPtr<FrameNode>& node)
{
    auto overlayNode = DynamicCast<SelectOverlayNode>(node);
    CHECK_NULL_VOID(overlayNode);
    overlayNode->HideSelectOverlay([weakOverlay = WeakClaim(AceType::RawPtr(node)), managerWeak = WeakClaim(this)]() {
        auto manager = managerWeak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->DestroySelectOverlayNode(weakOverlay.Upgrade());
    });
}

void SelectContentOverlayManager::DestroySelectOverlayNode(const RefPtr<FrameNode>& overlay)
{
    CHECK_NULL_VOID(overlay);
    auto parentNode = overlay->GetParent();
    CHECK_NULL_VOID(parentNode);

    auto parentFrameNode = DynamicCast<FrameNode>(parentNode);
    if (parentFrameNode) {
        auto pattern = overlay->GetPattern<SelectOverlayPattern>();
        if (pattern && pattern->GetMode() == SelectOverlayMode::HANDLE_ONLY) {
            parentFrameNode->SetOverlayNode(nullptr);
            overlay->SetParent(nullptr);
        }
    }
    TAG_LOGI(AceLogTag::ACE_SELECT_OVERLAY,
        "Remove node [%{public}s, %{public}d] from [%{public}s, %{public}d]", overlay->GetTag().c_str(),
        overlay->GetId(), parentNode->GetTag().c_str(), parentNode->GetId());
    parentNode->RemoveChild(overlay);
    parentNode->MarkNeedSyncRenderTree();
    parentNode->RebuildRenderContextTree();
    auto rootNode = GetSelectOverlayRoot();
    if (rootNode != DynamicCast<FrameNode>(parentNode)) {
        return;
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->AddAfterRenderTask([weakNode = WeakPtr<UINode>(parentNode)]() {
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
    handleNode_.Reset();
    menuNode_.Reset();
    shareOverlayInfo_.reset();
    if (selectOverlayHolder_) {
        selectOverlayHolder_->OnBind(nullptr);
    }
    selectOverlayHolder_.Reset();
}

bool SelectContentOverlayManager::CloseCurrent(bool animation, CloseReason reason)
{
    CHECK_NULL_RETURN(selectOverlayHolder_, false);
    CHECK_NULL_RETURN(selectOverlayNode_.Upgrade() || menuNode_.Upgrade() || handleNode_.Upgrade(), false);
    return CloseInternal(selectOverlayHolder_->GetOwnerId(), animation, reason);
}

void SelectContentOverlayManager::CloseWithOverlayId(int32_t overlayId, CloseReason reason, bool animation)
{
    CHECK_NULL_VOID(IsOpen());
    // call from menu button.
    auto hasOverlayId = (selectOverlayNode_.Upgrade() && overlayId == selectOverlayNode_.Upgrade()->GetId());
    hasOverlayId = hasOverlayId || (menuNode_.Upgrade() && menuNode_.Upgrade()->GetId());
    if (hasOverlayId) {
        CloseInternal(selectOverlayHolder_->GetOwnerId(), animation, reason);
    }
}

void SelectContentOverlayManager::Close(int32_t id, bool animation, CloseReason reason)
{
    CloseInternal(id, animation, reason);
}

void SelectContentOverlayManager::ShowOptionMenu()
{
    auto pattern = GetSelectMenuPattern(WeakClaim(this));
    CHECK_NULL_VOID(pattern);
    pattern->UpdateMenuIsShow(true);
}

void SelectContentOverlayManager::HideOptionMenu(bool noAnimation)
{
    auto pattern = GetSelectMenuPattern(WeakClaim(this));
    CHECK_NULL_VOID(pattern);
    pattern->UpdateMenuIsShow(false, noAnimation);
}

void SelectContentOverlayManager::ToggleOptionMenu()
{
    CHECK_NULL_VOID(shareOverlayInfo_);
    auto pattern = GetSelectMenuPattern(WeakClaim(this));
    CHECK_NULL_VOID(pattern);
    pattern->UpdateMenuIsShow(!shareOverlayInfo_->menuInfo.menuIsShow);
}

void SelectContentOverlayManager::DisableMenu()
{
    auto pattern = GetSelectMenuPattern(WeakClaim(this));
    CHECK_NULL_VOID(pattern);
    pattern->DisableMenu(true);
}

void SelectContentOverlayManager::EnableMenu()
{
    auto pattern = GetSelectMenuPattern(WeakClaim(this));
    CHECK_NULL_VOID(pattern);
    pattern->DisableMenu(false);
}

void SelectContentOverlayManager::HideHandle()
{
    auto pattern = GetSelectHandlePattern(WeakClaim(this));
    CHECK_NULL_VOID(pattern);
    pattern->StartHiddenHandleTask(false);
}

bool SelectContentOverlayManager::IsOpen()
{
    if (!IsEnableHandleLevel()) {
        auto overlayNode = selectOverlayNode_.Upgrade();
        return overlayNode && overlayNode->GetParent();
    }
    auto hasHandleNode = handleNode_.Upgrade() && handleNode_.Upgrade()->GetParent();
    auto hasMenuNode = menuNode_.Upgrade() && menuNode_.Upgrade()->GetParent();
    return hasHandleNode || hasMenuNode;
}

bool SelectContentOverlayManager::IsCreating()
{
    if (!IsEnableHandleLevel()) {
        auto overlayNode = selectOverlayNode_.Upgrade();
        return overlayNode && !overlayNode->GetParent();
    }
    auto menuNode = menuNode_.Upgrade();
    auto handleNode = handleNode_.Upgrade();
    return (menuNode && !menuNode->GetParent()) || (handleNode && !handleNode->GetParent());
}

bool SelectContentOverlayManager::IsMenuShow()
{
    return IsOpen() && shareOverlayInfo_ && shareOverlayInfo_->menuInfo.menuIsShow;
}

bool SelectContentOverlayManager::IsSingleHandle()
{
    return IsOpen() && shareOverlayInfo_ && shareOverlayInfo_->isSingleHandle;
}

bool SelectContentOverlayManager::IsHandlesShow()
{
    return IsOpen() && shareOverlayInfo_ && !shareOverlayInfo_->isSingleHandle;
}

bool SelectContentOverlayManager::IsHandleReverse()
{
    return IsOpen() && shareOverlayInfo_ && shareOverlayInfo_->handleReverse;
}

void SelectContentOverlayManager::RestartHiddenHandleTask(bool isDelay)
{
    auto pattern = GetSelectHandlePattern(WeakClaim(this));
    CHECK_NULL_VOID(pattern);
    pattern->RestartHiddenHandleTask(isDelay);
}

void SelectContentOverlayManager::CancelHiddenHandleTask()
{
    auto pattern = GetSelectHandlePattern(WeakClaim(this));
    CHECK_NULL_VOID(pattern);
    pattern->CancelHiddenHandleTask();
}

RefPtr<SelectOverlayNode> SelectContentOverlayManager::GetSelectOverlayNode()
{
    auto overlayNode = IsEnableHandleLevel() ? menuNode_.Upgrade() : selectOverlayNode_.Upgrade();
    return AceType::DynamicCast<SelectOverlayNode>(overlayNode);
}

OptionMenuType SelectContentOverlayManager::GetShowMenuType()
{
    return IsOpen() && shareOverlayInfo_ ? shareOverlayInfo_->menuInfo.menuType : OptionMenuType::NO_MENU;
}

void SelectContentOverlayManager::HandleGlobalEvent(const TouchEvent& touchEvent, const NG::OffsetF& rootOffset)
{
    NG::PointF point { touchEvent.x - rootOffset.GetX(), touchEvent.y - rootOffset.GetY() };
    if (touchEvent.type == TouchType::DOWN) {
        isIntercept_ = IsTouchInSelectOverlayArea(point);
    }
    if (!isIntercept_) {
        HandleSelectionEvent(point, touchEvent);
        if (selectOverlayHolder_ && selectOverlayHolder_->GetCallback() && selectOverlayHolder_->GetOwner()) {
            auto localPoint = point;
            ConvertPointRelativeToNode(selectOverlayHolder_->GetOwner(), localPoint);
            selectOverlayHolder_->GetCallback()->OnHandleGlobalEvent(point, localPoint, touchEvent);
        }
    }
    if (touchEvent.type == TouchType::UP) {
        isIntercept_ = false;
    }
}

bool SelectContentOverlayManager::IsTouchInSelectOverlayArea(const PointF& point)
{
    if (!IsEnableHandleLevel()) {
        return IsTouchInNormalSelectOverlayArea(point);
    }
    return IsTouchInHandleLevelOverlayArea(point);
}

bool SelectContentOverlayManager::IsTouchInNormalSelectOverlayArea(const PointF& point)
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
        if (child == nullptr || !child->GetGeometryNode()) {
            continue;
        }
        auto frameRect = RectF(child->GetTransformRelativeOffset(), child->GetGeometryNode()->GetFrameSize());
        if (frameRect.IsInRegion(point)) {
            return true;
        }
    }
    return false;
}

bool SelectContentOverlayManager::IsTouchInHandleLevelOverlayArea(const PointF& point)
{
    auto selectOverlayNode = DynamicCast<SelectOverlayNode>(menuNode_.Upgrade());
    if (selectOverlayNode && selectOverlayNode->IsInSelectedOrSelectOverlayArea(point)) {
        return true;
    }
    selectOverlayNode = DynamicCast<SelectOverlayNode>(handleNode_.Upgrade());
    CHECK_NULL_RETURN(selectOverlayNode, false);
    auto localPoint = point;
    ConvertPointRelativeToNode(selectOverlayNode->GetAncestorNodeOfFrame(), localPoint);
    return selectOverlayNode->IsInSelectedOrSelectOverlayArea(localPoint);
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

bool SelectContentOverlayManager::IsEnableHandleLevel()
{
    return shareOverlayInfo_ && shareOverlayInfo_->enableHandleLevel;
}

RefPtr<Pattern> SelectContentOverlayManager::GetMenuPattern()
{
    return IsEnableHandleLevel() ? GetSelectOverlayPattern(menuNode_)
                                      : GetSelectOverlayPattern(selectOverlayNode_);
}

RefPtr<Pattern> SelectContentOverlayManager::GetHandlePattern()
{
    return IsEnableHandleLevel() ? GetSelectOverlayPattern(handleNode_)
                                      : GetSelectOverlayPattern(selectOverlayNode_);
}

RefPtr<FrameNode> SelectContentOverlayManager::GetHandleOverlayNode()
{
    return handleNode_.Upgrade();
}

void SelectContentOverlayManager::NotifyUpdateToolBar(bool itemChanged)
{
    auto menuNode = DynamicCast<SelectOverlayNode>(menuNode_.Upgrade());
    CHECK_NULL_VOID(menuNode);
    menuNode->UpdateToolBar(itemChanged);
}

float SelectContentOverlayManager::GetHandleDiameter()
{
    return SelectOverlayPattern::GetHandleDiameter();
}

void SelectContentOverlayManager::ConvertPointRelativeToNode(const RefPtr<FrameNode>& node, PointF& point)
{
    CHECK_NULL_VOID(node);
    auto rootNode = GetSelectOverlayRoot();
    CHECK_NULL_VOID(rootNode);
    std::stack<RefPtr<FrameNode>> nodeStack;
    auto parent = node;
    while (parent && parent != rootNode) {
        nodeStack.push(parent);
        parent = parent->GetAncestorNodeOfFrame();
    }
    CHECK_NULL_VOID(!nodeStack.empty());
    PointF temp(point.GetX(), point.GetY());
    while (!nodeStack.empty()) {
        parent = nodeStack.top();
        CHECK_NULL_VOID(parent);
        nodeStack.pop();
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->GetPointWithRevert(temp);
        auto rectOffset = renderContext->GetPaintRectWithoutTransform().GetOffset();
        temp = temp - rectOffset;
    }
    point.SetX(temp.GetX());
    point.SetY(temp.GetY());
}

bool SelectContentOverlayManager::IsTouchAtHandle(const PointF& localPoint, const PointF& globalPoint)
{
    auto handleNode = handleNode_.Upgrade();
    CHECK_NULL_RETURN(handleNode, false);
    auto selectOverlayNode = DynamicCast<SelectOverlayNode>(handleNode);
    CHECK_NULL_RETURN(selectOverlayNode, false);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    CHECK_NULL_RETURN(pattern, false);
    if (pattern->IsHiddenHandle()) {
        return false;
    }
    CHECK_NULL_RETURN(selectOverlayHolder_, false);
    if (selectOverlayNode->GetParent() == selectOverlayHolder_->GetOwner()) {
        return selectOverlayNode->IsInSelectedOrSelectOverlayArea(localPoint);
    }
    return selectOverlayNode->IsInSelectedOrSelectOverlayArea(globalPoint);
}

void SelectContentOverlayManager::SetHandleCircleIsShow(bool isFirst, bool isShow)
{
    auto pattern = GetSelectHandlePattern(WeakClaim(this));
    CHECK_NULL_VOID(pattern);
    pattern->SetHandleCircleIsShow(isFirst, isShow);
}

void SelectContentOverlayManager::SetIsHandleLineShow(bool isShow)
{
    auto pattern = GetSelectHandlePattern(WeakClaim(this));
    CHECK_NULL_VOID(pattern);
    pattern->SetIsHandleLineShow(isShow);
}

void SelectContentOverlayManager::MarkHandleDirtyNode(PropertyChangeFlag flag)
{
    auto pattern = GetSelectHandlePattern(WeakClaim(this));
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(flag);
}

bool SelectContentOverlayManager::IsHiddenHandle()
{
    auto pattern = GetSelectHandlePattern(WeakClaim(this));
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsHiddenHandle();
}
} // namespace OHOS::Ace::NG
