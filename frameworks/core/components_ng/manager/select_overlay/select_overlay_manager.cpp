/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"

#include <memory>

#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
RefPtr<SelectOverlayProxy> SelectOverlayManager::CreateAndShowSelectOverlay(
    const SelectOverlayInfo& info, const WeakPtr<SelectionHost>& host, bool animation)
{
    host_ = host;
    auto current = selectOverlayItem_.Upgrade();
    if (current) {
        if (info.isUsingMouse && IsSameSelectOverlayInfo(info)) {
            auto proxy = MakeRefPtr<SelectOverlayProxy>(current->GetId());
            return proxy;
        }
        NotifyOverlayClosed(true);
        DestroySelectOverlay(current->GetId());
    }
    selectOverlayInfo_ = info;
    SelectOverlayInfo selectInfo = info;
    if (selectInfo.callerFrameNode.Invalid()) {
        selectInfo.callerFrameNode = GetCallerHost();
    }
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    selectOverlayItem_ = selectOverlayNode;

    auto taskExecutor = Container::CurrentTaskExecutor();
    taskExecutor->PostTask(
        [weakRoot = rootNodeWeak_, overlayNode = selectOverlayNode, animation,
            isUsingMouse = infoPtr->isUsingMouse, weak = WeakClaim(this), weakCaller = infoPtr->callerFrameNode] {
            auto selectOverlayManager = weak.Upgrade();
            CHECK_NULL_VOID(selectOverlayManager);
            CHECK_NULL_VOID(overlayNode);
            if (overlayNode != selectOverlayManager->GetSelectOverlayItem()) {
                LOGD("current selectOverlayItem not is %{public}d", selectOverlayNode->GetId());
                return;
            }
            auto rootNode = weakRoot.Upgrade();
            auto container = Container::Current();
            if (container && container->IsScenceBoardWindow()) {
                auto root = selectOverlayManager->FindWindowScene(weakCaller.Upgrade());
                rootNode = DynamicCast<FrameNode>(root);
            }
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
            if (!isUsingMouse) {
                auto node = DynamicCast<SelectOverlayNode>(overlayNode);
                CHECK_NULL_VOID(node);
                node->ShowSelectOverlay(animation);
            }
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(context);
            context->AddAfterLayoutTask([weakNode = WeakPtr<FrameNode>(rootNode)]() {
                auto hostNode = weakNode.Upgrade();
                CHECK_NULL_VOID(hostNode);
                hostNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
            });
        },
        TaskExecutor::TaskType::UI);

    auto proxy = MakeRefPtr<SelectOverlayProxy>(selectOverlayNode->GetId());
    return proxy;
}

// This function will be used in SceneBoard Thread only.
// if need to show the select-overlay component,
//   it expects to receive the target component bound by the select-overlay component to find the windowScene component.
// if need to hide the select-overlay component,
//   it expects to receive the the select-overlay component to return the parent component.
//   And the parent component will be the windowScene component exactly.
RefPtr<UINode> SelectOverlayManager::FindWindowScene(RefPtr<FrameNode> targetNode)
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
    LOGI("FindWindowScene success");
    return parent;
}

void SelectOverlayManager::DestroySelectOverlay(const RefPtr<SelectOverlayProxy>& proxy, bool animation)
{
    auto id = proxy->GetSelectOverlayId();
    DestroySelectOverlay(id, animation);
}

void SelectOverlayManager::DestroySelectOverlay(int32_t overlayId, bool animation)
{
    auto current = selectOverlayItem_.Upgrade();
    if (current && (current->GetId() == overlayId)) {
        DestroyHelper(current, animation);
    } else {
        LOGD("current overlay id %{public}d is already destroyed.", overlayId);
    }
}

void SelectOverlayManager::DestroySelectOverlay(bool animation)
{
    auto current = selectOverlayItem_.Upgrade();
    if (current) {
        DestroyHelper(current, animation);
    }
}

void SelectOverlayManager::DestroyHelper(const RefPtr<FrameNode>& overlay, bool animation)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    LOGD("destroy overlay, id is %{public}d.", overlay->GetId());
    if (animation && !selectOverlayInfo_.isUsingMouse) {
        selectOverlayItem_.Reset();
        host_.Reset();
        touchDownPoints_.clear();
        selectOverlayInfo_.callerFrameNode.Reset();
        auto node = DynamicCast<SelectOverlayNode>(overlay);
        node->HideSelectOverlay([overlayWeak = WeakClaim(RawPtr(overlay)), managerWeak = WeakClaim(this)]() {
            auto manager = managerWeak.Upgrade();
            CHECK_NULL_VOID(manager);
            auto overlay = overlayWeak.Upgrade();
            CHECK_NULL_VOID(overlay);
            manager->Destroy(overlay);
        });
    } else {
        Destroy(overlay);
        selectOverlayItem_.Reset();
        host_.Reset();
        touchDownPoints_.clear();
        selectOverlayInfo_.callerFrameNode.Reset();
    }
}

void SelectOverlayManager::Destroy(const RefPtr<FrameNode>& overlay)
{
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

bool SelectOverlayManager::HasSelectOverlay(int32_t overlayId)
{
    auto current = selectOverlayItem_.Upgrade();
    CHECK_NULL_RETURN(current, false);
    return current->GetId() == overlayId;
}

bool SelectOverlayManager::IsInSelectedOrSelectOverlayArea(const PointF& point)
{
    auto host = host_.Upgrade();
    if (host && host->IsTouchTestPointInArea(Offset { point.GetX(), point.GetY() }, IsTouchInCallerArea())) {
        return true;
    }
    auto current = selectOverlayItem_.Upgrade();
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

RefPtr<SelectOverlayNode> SelectOverlayManager::GetSelectOverlayNode(int32_t overlayId)
{
    auto current = selectOverlayItem_.Upgrade();
    if (current && (current->GetId() == overlayId)) {
        return DynamicCast<SelectOverlayNode>(current);
    }
    return nullptr;
}

bool SelectOverlayManager::IsSameSelectOverlayInfo(const SelectOverlayInfo& info)
{
    if (selectOverlayInfo_.menuInfo.IsIconChanged(info.menuInfo)) {
        return false;
    }
    if (selectOverlayInfo_.isUsingMouse != info.isUsingMouse) {
        return false;
    }
    if (selectOverlayInfo_.rightClickOffset != info.rightClickOffset) {
        return false;
    }
    return true;
}

void SelectOverlayManager::HandleGlobalEvent(const TouchEvent& touchPoint, const NG::OffsetF& rootOffset)
{
    CHECK_NULL_VOID(!selectOverlayItem_.Invalid());
    NG::PointF point { touchPoint.x - rootOffset.GetX(), touchPoint.y - rootOffset.GetY() };
    // handle global touch event.
    if (touchPoint.type == TouchType::DOWN && touchPoint.sourceType == SourceType::TOUCH) {
        if (touchDownPoints_.empty() && !IsTouchInCallerArea() && !IsInSelectedOrSelectOverlayArea(point)) {
            touchDownPoints_.emplace_back(touchPoint);
        }
        return;
    }
    if (touchPoint.type == TouchType::MOVE && touchPoint.sourceType == SourceType::TOUCH) {
        if (touchDownPoints_.empty()) {
            return;
        }
        auto lastTouchDownPoint = touchDownPoints_.back();
        if (lastTouchDownPoint.id != touchPoint.id) {
            return;
        }
        auto deltaOffset = touchPoint.GetOffset() - lastTouchDownPoint.GetOffset();
        auto deltaDistance = deltaOffset.GetDistance();
        auto context = PipelineBase::GetCurrentContext();
        auto thresholdDistance = context ? context->NormalizeToPx(Dimension(5, DimensionUnit::VP)) : 5;
        if (deltaDistance > thresholdDistance) {
            touchDownPoints_.clear();
        }
        return;
    }
    bool acceptTouchUp = !touchDownPoints_.empty();
    if (touchPoint.type == TouchType::UP && touchPoint.sourceType == SourceType::TOUCH && acceptTouchUp) {
        auto lastTouchDownPoint = touchDownPoints_.back();
        if (lastTouchDownPoint.id != touchPoint.id) {
            return;
        }
        touchDownPoints_.pop_back();
        point.SetX(lastTouchDownPoint.x - rootOffset.GetX());
        point.SetY(lastTouchDownPoint.y - rootOffset.GetY());
    }

    // handle global mouse event.
    if ((touchPoint.type != TouchType::DOWN || touchPoint.sourceType != SourceType::MOUSE) && !acceptTouchUp) {
        return;
    }
    if (!IsInSelectedOrSelectOverlayArea(point)) {
        LOGD("[SelectOverlay] closed by global event %{public}d", touchPoint.sourceType);
        NotifyOverlayClosed(true);
        DestroySelectOverlay();
    }
}

bool SelectOverlayManager::IsTouchInCallerArea() const
{
    if (touchTestResults_.empty()) {
        return false;
    }
    auto frameNode = GetCallerHost();
    CHECK_NULL_RETURN(frameNode, false);
    auto id = std::to_string(frameNode->GetId());
    for (auto testId : touchTestResults_) {
        if (testId == id) {
            return true;
        }
    }
    return false;
}

RefPtr<FrameNode> SelectOverlayManager::GetCallerHost() const
{
    auto host = host_.Upgrade();
    CHECK_NULL_RETURN(host, nullptr);
    auto pattern = DynamicCast<Pattern>(host);
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetHost();
}

void SelectOverlayManager::NotifyOverlayClosed(bool closedByGlobalEvent)
{
    auto current = selectOverlayItem_.Upgrade();
    if (current) {
        auto selectOverlayNode = DynamicCast<SelectOverlayNode>(current);
        CHECK_NULL_VOID(selectOverlayNode);
        selectOverlayNode->SetClosedByGlobalEvent(closedByGlobalEvent);
    }
}

void SelectOverlayManager::MarkDirty(PropertyChangeFlag flag)
{
    auto selectOverlayItem = selectOverlayItem_.Upgrade();
    if (selectOverlayItem) {
        selectOverlayItem->MarkDirtyNode(flag);
    }
}

void SelectOverlayManager::NotifyOnScrollCallback(int32_t id, bool isEnd)
{
    LOGI("NotifyOnScrollCallback scroll id %{public}d", id);
    if (parentScrollCallbacks_.empty()) {
        return;
    }
    auto it = parentScrollCallbacks_.find(id);
    if (it == parentScrollCallbacks_.end()) {
        return;
    }
    auto callbackMap = it->second;
    if (callbackMap.empty()) {
        parentScrollCallbacks_.erase(id);
        return;
    }
    for (const auto& pair : callbackMap) {
        pair.second(isEnd);
    }
}

void SelectOverlayManager::RegisterScrollCallback(
    int32_t scrollableParentId, int32_t callbackId, std::function<void(bool)>&& callback)
{
    LOGI("RegisterScrollCallback scroll parent id %{public}d, callbackId %{public}d", scrollableParentId, callbackId);
    auto it = parentScrollCallbacks_.find(scrollableParentId);
    if (it == parentScrollCallbacks_.end()) {
        std::map<int32_t, std::function<void(bool)>> callbackMap = { { callbackId, std::move(callback) } };
        parentScrollCallbacks_.insert(std::make_pair(scrollableParentId, callbackMap));
    } else {
        it->second.insert(std::make_pair(callbackId, std::move(callback)));
    }
}

void SelectOverlayManager::RemoveScrollCallback(int32_t callbackId)
{
    LOGI("RemoveScrollCallback callbackId %{public}d", callbackId);
    if (parentScrollCallbacks_.empty()) {
        return;
    }
    for (auto it = parentScrollCallbacks_.begin(); it != parentScrollCallbacks_.end();) {
        it->second.erase(callbackId);
        if (it->second.empty()) {
            it = parentScrollCallbacks_.erase(it);
        } else {
            ++it;
        }
    }
}
} // namespace OHOS::Ace::NG
