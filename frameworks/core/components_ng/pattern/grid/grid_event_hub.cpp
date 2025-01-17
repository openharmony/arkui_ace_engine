/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_event_hub.h"

#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/render/adapter/component_snapshot.h"

namespace OHOS::Ace::NG {
#if defined(PIXEL_MAP_SUPPORTED)
constexpr int32_t CREATE_PIXELMAP_TIME = 80;
#endif

void GridEventHub::InitItemDragEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto eventHub = weak.Upgrade();
        if (eventHub) {
            eventHub->HandleOnItemDragStart(info);
        }
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto eventHub = weak.Upgrade();
        if (eventHub) {
            eventHub->HandleOnItemDragUpdate(info);
        }
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto eventHub = weak.Upgrade();
        if (eventHub) {
            eventHub->HandleOnItemDragEnd(info);
        }
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto eventHub = weak.Upgrade();
        if (eventHub) {
            eventHub->HandleOnItemDragCancel();
        }
    };

    auto dragEvent = MakeRefPtr<DragEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->SetDragEvent(dragEvent, { PanDirection::ALL }, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

bool GridEventHub::CheckPostionInGrid(float x, float y)
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    auto size = host->GetRenderContext()->GetPaintRectWithTransform();
    size.SetOffset(host->GetTransformRelativeOffset());
    return size.IsInRegion(PointF(x, y));
}

int32_t GridEventHub::GetInsertPosition(float x, float y)
{
    if (!CheckPostionInGrid(x, y)) {
        return -1;
    }

    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, -1);
    auto pattern = AceType::DynamicCast<GridPattern>(host->GetPattern());
    CHECK_NULL_RETURN(pattern, -1);
    auto itemFrameNode = host->FindChildByPositionWithoutChildTransform(x, y);
    if (itemFrameNode) {
        RefPtr<GridItemLayoutProperty> itemLayoutProperty = itemFrameNode->GetLayoutProperty<GridItemLayoutProperty>();
        CHECK_NULL_RETURN(itemLayoutProperty, 0);
        auto mainIndex = itemLayoutProperty->GetMainIndex().value_or(-1);
        auto crossIndex = itemLayoutProperty->GetCrossIndex().value_or(-1);
        return mainIndex * pattern->GetCrossCount() + crossIndex;
    }

    // on virtual grid item dragged in this grid
    if (pattern->GetGridLayoutInfo().currentRect_.IsInRegion(PointF(x, y))) {
        return pattern->GetOriginalIndex();
    }

    // in grid, but not on any grid item
    return pattern->GetChildrenCount();
}

int GridEventHub::GetFrameNodeChildSize()
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, 0);
    auto pattern = host->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(pattern, 0);
    return pattern->GetChildrenCount();
}

int32_t GridEventHub::GetGridItemIndex(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto gridFrameNode = GetFrameNode();
    CHECK_NULL_RETURN(gridFrameNode, 0);
    auto gridPattern = gridFrameNode->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(gridPattern, 0);
    RefPtr<GridItemPattern> itemPattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_RETURN(itemPattern, 0);
    auto itemProperty = frameNode->GetLayoutProperty<GridItemLayoutProperty>();
    CHECK_NULL_RETURN(itemProperty, 0);

    auto gridLayoutInfo = gridPattern->GetGridLayoutInfo();
    auto mainIndex = itemProperty->GetMainIndex().value_or(-1);
    auto crossIndex = itemProperty->GetCrossIndex().value_or(-1);
    auto crossIndexIterator = gridLayoutInfo.gridMatrix_.find(mainIndex);
    if (crossIndexIterator != gridLayoutInfo.gridMatrix_.end()) {
        auto crossIndexMap = crossIndexIterator->second;

        auto indexIterator = crossIndexMap.find(crossIndex);
        if (indexIterator != crossIndexMap.end()) {
            return indexIterator->second;
        }
    }

    return 0;
}

bool GridEventHub::GetEditable() const
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetEditable().value_or(false);
}

void GridEventHub::HandleOnItemDragStart(const GestureEvent& info)
{
    if (!GetEditable()) {
        return;
    }

    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);

    auto globalX = static_cast<float>(info.GetGlobalPoint().GetX());
    auto globalY = static_cast<float>(info.GetGlobalPoint().GetY());

    auto gridItem = host->FindChildByPositionWithoutChildTransform(globalX, globalY);
    CHECK_NULL_VOID(gridItem);
    draggedIndex_ = GetGridItemIndex(gridItem);

    OHOS::Ace::ItemDragInfo itemDragInfo;
    itemDragInfo.SetX(globalX);
    itemDragInfo.SetY(globalY);
    auto customNode = FireOnItemDragStart(itemDragInfo, draggedIndex_);
    CHECK_NULL_VOID(customNode);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetDraggingPointer(info.GetPointerId());
    dragDropManager->SetDraggingPressedState(true);
#if defined(PIXEL_MAP_SUPPORTED)
    auto callback = [id = Container::CurrentId(), pipeline, info, host, gridItem, weak = WeakClaim(this)](
                        std::shared_ptr<Media::PixelMap> mediaPixelMap, int32_t /*arg*/,
                        const std::function<void()>& /*unused*/) {
        ContainerScope scope(id);
        if (!mediaPixelMap) {
            TAG_LOGE(AceLogTag::ACE_DRAG, "gridItem drag start failed, custom component screenshot is empty.");
            return;
        }
        auto pixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&mediaPixelMap));
        CHECK_NULL_VOID(pixelMap);
        auto taskScheduler = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        taskScheduler->PostTask(
            [weak, pipeline, info, pixelMap, host, gridItem]() {
                auto eventHub = weak.Upgrade();
                CHECK_NULL_VOID(eventHub);
                auto manager = pipeline->GetDragDropManager();
                CHECK_NULL_VOID(manager);
                eventHub->dragDropProxy_ = manager->CreateAndShowItemDragOverlay(pixelMap, info, eventHub);
                CHECK_NULL_VOID(eventHub->dragDropProxy_);
                eventHub->dragDropProxy_->OnItemDragStart(info, host);
                gridItem->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
                eventHub->draggingItem_ = gridItem;
                if (!manager->IsDraggingPressed(info.GetPointerId())) {
                    eventHub->HandleOnItemDragEnd(info);
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIGridItemDragStart",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    };
    SnapshotParam param;
    if (auto pixmap = ComponentSnapshot::CreateSync(customNode, param); pixmap) {
        callback(pixmap, 0, nullptr);
        return;
    }
    param.delay = CREATE_PIXELMAP_TIME;
    NG::ComponentSnapshot::Create(customNode, std::move(callback), true, param);
#else
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    dragDropProxy_ = manager->CreateAndShowItemDragOverlay(customNode, info, AceType::Claim(this));
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->OnItemDragStart(info, host);
    gridItem->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    draggingItem_ = gridItem;
    if (!manager->IsDraggingPressed(info.GetPointerId())) {
        HandleOnItemDragEnd(info);
    }
#endif
}

void GridEventHub::HandleOnItemDragUpdate(const GestureEvent& info)
{
    if (!GetEditable()) {
        return;
    }

    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->OnItemDragMove(info, draggedIndex_, DragType::GRID);
}

void GridEventHub::HandleOnItemDragEnd(const GestureEvent& info)
{
    CHECK_NULL_VOID(dragDropProxy_);
    if (GetEditable()) {
        dragDropProxy_->OnItemDragEnd(info, draggedIndex_, DragType::GRID);
    } else {
        dragDropProxy_->onItemDragCancel();
    }
    dragDropProxy_->DestroyDragWindow();
    dragDropProxy_ = nullptr;
    draggedIndex_ = 0;
    if (draggingItem_) {
        draggingItem_->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
        draggingItem_ = nullptr;
    }

    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    auto pattern = AceType::DynamicCast<GridPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->ClearDragState();
}

void GridEventHub::HandleOnItemDragCancel()
{
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->onItemDragCancel();
    dragDropProxy_->DestroyDragWindow();
    dragDropProxy_ = nullptr;
    draggedIndex_ = 0;
    if (draggingItem_) {
        draggingItem_->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
        draggingItem_ = nullptr;
    }

    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    auto pattern = AceType::DynamicCast<GridPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->ClearDragState();
}

void GridEventHub::FireOnItemDragEnter(const ItemDragInfo& dragInfo)
{
    if (onItemDragEnter_) {
        onItemDragEnter_(dragInfo);
    }
}

void GridEventHub::FireOnItemDragLeave(const ItemDragInfo& dragInfo, int32_t itemIndex)
{
    if (itemIndex == -1) {
        auto host = GetFrameNode();
        CHECK_NULL_VOID(host);
        auto pattern = AceType::DynamicCast<GridPattern>(host->GetPattern());
        CHECK_NULL_VOID(pattern);
        auto insertIndex = pattern->GetChildrenCount();
        MoveItems(itemIndex, insertIndex);
    }

    if (onItemDragLeave_) {
        onItemDragLeave_(dragInfo, itemIndex);
    }
}

bool GridEventHub::FireOnItemDrop(const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess)
{
    TAG_LOGI(AceLogTag::ACE_GRID, "itemIndex:%{public}d, insertIndex:%{public}d", itemIndex, insertIndex);
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    auto pattern = AceType::DynamicCast<GridPattern>(host->GetPattern());
    CHECK_NULL_RETURN(pattern, false);
    if (pattern->SupportAnimation()) {
        insertIndex = (itemIndex == -1 || insertIndex == -1) ? insertIndex : pattern->GetOriginalIndex();
        pattern->ClearDragState();
    }

    if (onItemDrop_) {
        onItemDrop_(dragInfo, itemIndex, insertIndex, isSuccess);
        host->ChildrenUpdatedFrom(0);
        return true;
    }
    host->ChildrenUpdatedFrom(0);
    return false;
}

void GridEventHub::FireOnItemDragMove(const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex) const
{
    MoveItems(itemIndex, insertIndex);

    if (onItemDragMove_) {
        auto host = GetFrameNode();
        CHECK_NULL_VOID(host);
        auto pattern = AceType::DynamicCast<GridPattern>(host->GetPattern());
        CHECK_NULL_VOID(pattern);
        if (pattern->SupportAnimation()) {
            insertIndex = (itemIndex == -1 || insertIndex == -1) ? insertIndex : pattern->GetOriginalIndex();
        }
        onItemDragMove_(dragInfo, itemIndex, insertIndex);
    }
}

void GridEventHub::MoveItems(int32_t itemIndex, int32_t insertIndex) const
{
    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    auto pattern = AceType::DynamicCast<GridPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    if (!pattern->SupportAnimation()) {
        return;
    }
    constexpr float ANIMATION_CURVE_VELOCITY = 0.0f;    // The move animation spring curve velocity is 0.0
    constexpr float ANIMATION_CURVE_MASS = 1.0f;        // The move animation spring curve mass is 1.0
    constexpr float ANIMATION_CURVE_STIFFNESS = 400.0f; // The move animation spring curve stiffness is 110.0
    constexpr float ANIMATION_CURVE_DAMPING = 38.0f;    // The move animation spring curve damping is 17.0
    AnimationOption option;
    constexpr int32_t duration = 400;
    option.SetDuration(duration);
    auto curve = MakeRefPtr<SpringCurve>(
        ANIMATION_CURVE_VELOCITY, ANIMATION_CURVE_MASS, ANIMATION_CURVE_STIFFNESS, ANIMATION_CURVE_DAMPING);
    option.SetCurve(curve);
    AnimationUtils::Animate(
        option, [pattern, itemIndex, insertIndex]() { pattern->MoveItems(itemIndex, insertIndex); }, nullptr);
}
} // namespace OHOS::Ace::NG