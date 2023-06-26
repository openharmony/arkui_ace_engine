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
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
RefPtr<SelectOverlayProxy> SelectOverlayManager::CreateAndShowSelectOverlay(
    const SelectOverlayInfo& info, const WeakPtr<SelectionHost>& host)
{
    host_ = host;
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, nullptr);
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
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    // mount to parent
    selectOverlayNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    auto proxy = MakeRefPtr<SelectOverlayProxy>(selectOverlayNode->GetId());
    selectOverlayItem_ = selectOverlayNode;
    return proxy;
}

void SelectOverlayManager::DestroySelectOverlay(const RefPtr<SelectOverlayProxy>& proxy)
{
    auto id = proxy->GetSelectOverlayId();
    DestroySelectOverlay(id);
}

void SelectOverlayManager::DestroySelectOverlay(int32_t overlayId)
{
    auto current = selectOverlayItem_.Upgrade();
    if (current && (current->GetId() == overlayId)) {
        DestroyHelper(current);
    } else {
        LOGD("current overlay id %{public}d is already destroyed.", overlayId);
    }
}

void SelectOverlayManager::DestroySelectOverlay()
{
    auto current = selectOverlayItem_.Upgrade();
    if (current) {
        DestroyHelper(current);
    }
}

void SelectOverlayManager::DestroyHelper(const RefPtr<FrameNode>& overlay)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    LOGD("destroy overlay, id is %{public}d.", overlay->GetId());
    rootNode->RemoveChild(overlay);
    rootNode->MarkNeedSyncRenderTree();
    rootNode->RebuildRenderContextTree();
    selectOverlayItem_.Reset();
    host_.Reset();
    touchDownPoints_.clear();
    selectOverlayInfo_.callerFrameNode.Reset();
}

bool SelectOverlayManager::HasSelectOverlay(int32_t overlayId)
{
    auto current = selectOverlayItem_.Upgrade();
    CHECK_NULL_RETURN_NOLOG(current, false);
    return current->GetId() == overlayId;
}

bool SelectOverlayManager::IsInSelectedOrSelectOverlayArea(const PointF& point)
{
    auto host = host_.Upgrade();
    if (host && host->BetweenSelectedPosition(Offset { point.GetX(), point.GetY() })) {
        return true;
    }
    auto current = selectOverlayItem_.Upgrade();
    CHECK_NULL_RETURN_NOLOG(current, false);
    auto selectOverlayNode = DynamicCast<SelectOverlayNode>(current);
    if (selectOverlayNode) {
        return selectOverlayNode->IsInSelectedOrSelectOverlayArea(point);
    }
    auto menuRect = current->GetGeometryNode()->GetFrameRect();
    return menuRect.IsInRegion(point);
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
        NG::PointF rootPoint { touchPoint.x, touchPoint.y };
        if ((IsInCallerArea(rootPoint, rootOffset)) || IsInSelectedOrSelectOverlayArea(point)) {
            return;
        }
        touchDownPoints_.push_back(point);
        return;
    }
    bool acceptTouchUp = !touchDownPoints_.empty();
    if (touchPoint.type == TouchType::UP && touchPoint.sourceType == SourceType::TOUCH && acceptTouchUp) {
        auto lastTouchDownPoint = touchDownPoints_.back();
        touchDownPoints_.pop_back();
        point.SetX(lastTouchDownPoint.GetX());
        point.SetY(lastTouchDownPoint.GetY());
    }

    // handle global mouse event.
    if ((touchPoint.type != TouchType::DOWN || touchPoint.sourceType != SourceType::MOUSE) && !acceptTouchUp) {
        return;
    }
    if (!IsInSelectedOrSelectOverlayArea(point)) {
        NotifyOverlayClosed(true);
        DestroySelectOverlay();
    }
}

bool SelectOverlayManager::IsInCallerArea(const PointF& point, const NG::OffsetF& rootOffset)
{
    auto frameNode = selectOverlayInfo_.callerFrameNode.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto parentOffset = frameNode->GetPaintRectOffset(true) - rootOffset;
    auto localPoint = point - parentOffset;
    auto paintRect = frameNode->GetPaintRectWithTransform();
    return paintRect.IsInRegion(localPoint);
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
} // namespace OHOS::Ace::NG