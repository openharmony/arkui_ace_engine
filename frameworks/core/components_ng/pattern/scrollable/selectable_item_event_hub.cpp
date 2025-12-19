/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/selectable_item_event_hub.h"
#include "ui/base/ace_type.h"

#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/scrollable/selectable_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t GATHER_DELAY_TIME = 150;
} // namespace
void SelectableItemEventHub::BindContextMenu()
{
    auto gestureHub = GetGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto longPress = gestureHub->GetLongPressEventActuator();
    CHECK_NULL_VOID(longPress);
    if (!AceType::InstanceOf<LongPressEventActuatorWithMultiSelect>(longPress)) {
        return;
    }
    auto longPressActuator = AceType::DynamicCast<LongPressEventActuatorWithMultiSelect>(longPress);
    CHECK_NULL_VOID(longPressActuator);
    auto callback = [weak = AceType::WeakClaim(this)](RefPtr<LongPressRecognizer>& longPressRecognizer) {
        auto eventHub = weak.Upgrade();
        CHECK_NULL_VOID(eventHub);
        auto gestureHub = eventHub->GetGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        if (gestureHub->HasDragEvent()) {
            return;
        }

        if (gestureHub->GetPreviewMode() == MenuPreviewMode::NONE) {
            return;
        }

        auto frameNode = eventHub->GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        if (!SelectableUtils::IsGatherSelectedItemsAnimationEnabled(frameNode)) {
            return;
        }

        auto&& onReject = [weak]() {
            auto eventHub = weak.Upgrade();
            CHECK_NULL_VOID(eventHub);
            eventHub->RestoreGatherNode();
        };
        longPressRecognizer->SetOnReject(onReject);

        auto&& showGatherTask = [weak]() {
            auto eventHub = weak.Upgrade();
            CHECK_NULL_VOID(eventHub);
            auto gestureHub = eventHub->GetGestureEventHub();
            CHECK_NULL_VOID(gestureHub);
            auto frameNode = eventHub->GetFrameNode();
            CHECK_NULL_VOID(frameNode);
            if (gestureHub->HasDragEvent()) {
                return;
            }
            DragAnimationHelper::ShowGatherNodeAnimation(frameNode);
        };
        eventHub->gatherTask_.Reset(showGatherTask);
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto taskExecutor = SingleTaskExecutor::Make(pipeline->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        taskExecutor.PostDelayedTask(eventHub->gatherTask_, GATHER_DELAY_TIME, "ArkUIContextMenuStartGather");
    };
    longPressActuator->SetMultiSelectHandler(callback);
}

void SelectableItemEventHub::RestoreGatherNode()
{
    gatherTask_.Cancel();

    auto gestureHub = GetGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (gestureHub->HasDragEvent()) {
        return;
    }

    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->RemovePreviewBadgeNode();
    manager->RemoveGatherNodeWithAnimation();

    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTransformScale({ 1.0f, 1.0f });
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
}
} // namespace OHOS::Ace::NG