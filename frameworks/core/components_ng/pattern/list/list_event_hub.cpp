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

#include "core/components_ng/pattern/list/list_event_hub.h"

#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
#if defined(PIXEL_MAP_SUPPORTED)
constexpr int32_t CREATE_PIXELMAP_TIME = 80;
#endif

void ListEventHub::InitItemDragEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto eventHub = weak.Upgrade();
        CHECK_NULL_VOID(eventHub);
        eventHub->HandleOnItemDragStart(info);
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto eventHub = weak.Upgrade();
        CHECK_NULL_VOID(eventHub);
        eventHub->HandleOnItemDragUpdate(info);
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto eventHub = weak.Upgrade();
        CHECK_NULL_VOID(eventHub);
        eventHub->HandleOnItemDragEnd(info);
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto eventHub = weak.Upgrade();
        CHECK_NULL_VOID(eventHub);
        eventHub->HandleOnItemDragCancel();
    };

    auto dragEvent = MakeRefPtr<DragEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->SetDragEvent(dragEvent, { PanDirection::ALL }, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void ListEventHub::OnItemDragStart(const GestureEvent& info, const DragDropInfo& dragDropInfo)
{
    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    if (dragDropInfo.pixelMap) {
        dragDropProxy_ = manager->CreateAndShowItemDragOverlay(dragDropInfo.pixelMap, info, AceType::Claim(this));
    } else if (dragDropInfo.customNode) {
        dragDropProxy_ = manager->CreateAndShowItemDragOverlay(dragDropInfo.customNode, info, AceType::Claim(this));
    }
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->OnItemDragStart(info, GetFrameNode());
    if (!manager->IsDraggingPressed(info.GetPointerId())) {
        HandleOnItemDragEnd(info);
    }
}

void ListEventHub::HandleOnItemDragStart(const GestureEvent& info)
{
    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);

    auto globalX = static_cast<float>(info.GetGlobalPoint().GetX());
    auto globalY = static_cast<float>(info.GetGlobalPoint().GetY());

    draggedIndex_ = GetListItemIndexByPosition(globalX, globalY, true);
    if (draggedIndex_ == -1) {
        return;
    }

    OHOS::Ace::ItemDragInfo itemDragInfo;
    itemDragInfo.SetX(globalX);
    itemDragInfo.SetY(globalY);
    auto customNode = FireOnItemDragStart(itemDragInfo, draggedIndex_);
    CHECK_NULL_VOID(customNode);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetDraggingPointer(info.GetPointerId());
    dragDropManager->SetDraggingPressedState(true);
    dragDropManager->SetDragStartPoint(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY());
#if defined(PIXEL_MAP_SUPPORTED)
    auto callback = [weakHost = WeakClaim(RawPtr(host)), info, weak = WeakClaim(this)](
                        std::shared_ptr<Media::PixelMap> mediaPixelMap, int32_t /*arg*/,
                        const std::function<void()>& finishCallback) {
        auto host = weakHost.Upgrade();
        CHECK_NULL_VOID(host);
        ContainerScope scope(host->GetInstanceId());
        if (!mediaPixelMap) {
            TAG_LOGE(AceLogTag::ACE_DRAG, "listItem drag start failed, custom component screenshot is empty.");
            return;
        }
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto taskScheduler = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        taskScheduler->PostTask(
            [finishCallback]() {
                if (finishCallback) {
                    finishCallback();
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIListItemDragRemoveCustomNode");
        DragDropInfo dragDropInfo;
        dragDropInfo.pixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&mediaPixelMap));
        taskScheduler->PostTask(
            [weak, info, dragDropInfo]() {
                auto eventHub = weak.Upgrade();
                CHECK_NULL_VOID(eventHub);
                eventHub->OnItemDragStart(info, dragDropInfo);
            },
            TaskExecutor::TaskType::UI, "ArkUIListItemDragStart");
    };
    NG::ComponentSnapshot::Create(customNode, std::move(callback), true, SnapshotParam(CREATE_PIXELMAP_TIME));
#else
    DragDropInfo dragDropInfo;
    dragDropInfo.customNode = customNode;
    OnItemDragStart(info, dragDropInfo);
#endif
}

void ListEventHub::HandleOnItemDragUpdate(const GestureEvent& info)
{
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->OnItemDragMove(info, draggedIndex_, DragType::LIST);
}

void ListEventHub::HandleOnItemDragEnd(const GestureEvent& info)
{
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->OnItemDragEnd(info, draggedIndex_, DragType::LIST);
    dragDropProxy_->DestroyDragWindow();
    dragDropProxy_ = nullptr;
    draggedIndex_ = 0;
}

void ListEventHub::HandleOnItemDragCancel()
{
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->onItemDragCancel();
    dragDropProxy_->DestroyDragWindow();
    dragDropProxy_ = nullptr;
    draggedIndex_ = 0;
}

int32_t ListEventHub::GetListItemIndexByPosition(float x, float y, bool strict)
{
    auto listNode = GetFrameNode();
    CHECK_NULL_RETURN(listNode, 0);

    if (strict) {
        auto itemFrameNode = listNode->FindChildByPositionWithoutChildTransform(x, y);
        CHECK_NULL_RETURN(itemFrameNode, -1);
        RefPtr<ListItemPattern> itemPattern = itemFrameNode->GetPattern<ListItemPattern>();
        CHECK_NULL_RETURN(itemPattern, -1);
        return itemPattern->GetIndexInList();
    }

    auto listPattern = listNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(listPattern, 0);
    return listPattern->GetItemIndexByPosition(x, y);
}
} // namespace OHOS::Ace::NG
