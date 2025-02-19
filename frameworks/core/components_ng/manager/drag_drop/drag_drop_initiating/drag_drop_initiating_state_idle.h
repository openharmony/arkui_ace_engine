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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_STATE_IDLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_STATE_IDLE_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_base.h"
#include "core/event/pointer_event.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEALY_TASK_DURATION = 350;
constexpr int32_t SNAPSHOT_DELAY_TIME = 150;
constexpr int32_t PRE_DRAG_DELAY_TIME = 50;
} // namespace

class DragDropInitiatingStateMachine;

class DragDropInitiatingStateIdle : public DragDropInitiatingStateBase {
    DECLARE_ACE_TYPE(DragDropInitiatingStateIdle, DragDropInitiatingStateBase);

public:
    DragDropInitiatingStateIdle(const WeakPtr<DragDropInitiatingStateMachine>& machine)
        : DragDropInitiatingStateBase(machine)
    {}
    ~DragDropInitiatingStateIdle() = default;

    void Init(int32_t currentState) override;
    void HandleHitTesting(const TouchEvent& touchEvent) override;

private:
    void RegisterDragListener();
    void UnRegisterDragListener();
    void AsyncDragEnd();
    void ResetStateForHitTest(const RefPtr<FrameNode>& frameNode);
    void StartCreateSnapshotTask(int32_t fingerId);
    void StartPreDragDetectingStartTask();
    void StartGatherTask();
    void StartPreDragStatusCallback(const TouchEvent& touchEvent);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_STATE_IDLE_H