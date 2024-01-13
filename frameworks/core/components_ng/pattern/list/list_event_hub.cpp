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

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
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

void ListEventHub::HandleOnItemDragStart(const GestureEvent& info)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    auto globalX = static_cast<float>(info.GetGlobalPoint().GetX());
    auto globalY = static_cast<float>(info.GetGlobalPoint().GetY());

    draggedIndex_ = GetListItemIndexByPosition(globalX, globalY, true);
    if (draggedIndex_ == -1) {
        return;
    }

    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    OHOS::Ace::ItemDragInfo itemDragInfo;
    itemDragInfo.SetX(pipeline->ConvertPxToVp(Dimension(globalX, DimensionUnit::PX)));
    itemDragInfo.SetY(pipeline->ConvertPxToVp(Dimension(globalY, DimensionUnit::PX)));
    auto customNode = FireOnItemDragStart(itemDragInfo, draggedIndex_);
    CHECK_NULL_VOID(customNode);
#if defined(PIXEL_MAP_SUPPORTED)
    auto callback = [id = Container::CurrentId(), pipeline, info, host, weak = WeakClaim(this)](
                        std::shared_ptr<Media::PixelMap> mediaPixelMap, int32_t /*arg*/,
                        const std::function<void()>& /*unused*/) {
        ContainerScope scope(id);
        if (!mediaPixelMap) {
            TAG_LOGE(AceLogTag::ACE_DRAG, "listItem drag start failed, custom component screenshot is empty.");
            return;
        }
        auto pixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&mediaPixelMap));
        CHECK_NULL_VOID(pixelMap);
        auto taskScheduler = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        taskScheduler->PostTask(
            [weak, pipeline, info, pixelMap, host]() {
                auto eventHub = weak.Upgrade();
                CHECK_NULL_VOID(eventHub);
                auto manager = pipeline->GetDragDropManager();
                CHECK_NULL_VOID(manager);
                eventHub->dragDropProxy_ = manager->CreateAndShowDragWindow(pixelMap, info);
                CHECK_NULL_VOID(eventHub->dragDropProxy_);
                eventHub->dragDropProxy_->OnItemDragStart(info, host);
            },
            TaskExecutor::TaskType::UI);
    };
    auto frameNode = AceType::DynamicCast<FrameNode>(customNode);
    NG::ComponentSnapshot::Create(frameNode, std::move(callback), false, CREATE_PIXELMAP_TIME);
#else
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    dragDropProxy_ = manager->CreateAndShowDragWindow(customNode, info);
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->OnItemDragStart(info, GetFrameNode());
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
        auto itemFrameNode = listNode->FindChildByPosition(x, y);
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
