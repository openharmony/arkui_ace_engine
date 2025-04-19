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

#ifndef TEST_UNITTEST_CORE_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_TEST_NG_H
#define TEST_UNITTEST_CORE_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_TEST_NG_H
#include <cstdint>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_interaction_interface.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/theme/blur_style_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/event/drag_drop_event.h"
#include "core/components_ng/event/drag_event.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_machine.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {
constexpr int32_t DEFAULT_DRAG_POINTER_ID = 5;
enum class DragDropInitiatingReceivedInput {
    HandleLongPressOnAction = 1 << 0,
    HandleLongPressOnActionEnd = 1 << 1,
    HandleLongPressOnActionCancel = 1 << 2,
    HandlePreviewLongPressOnAction = 1 << 3,
    HandlePreviewLongPressOnActionEnd = 1 << 4,
    HandlePreviewLongPressOnActionCancel = 1 << 5,
    HandlePanOnActionStart = 1 << 6,
    HandlePanOnActionUpdate = 1 << 7,
    HandlePanOnActionEnd = 1 << 8,
    HandlePanOnActionCancel = 1 << 9,
    HandlePanOnReject = 1 << 10,
    HandleSequenceOnActionCancel = 1 << 11,
    HandleHitTesting = 1 << 12,
    HandleTouchEvent = 1 << 13,
    HandlePullEvent = 1 << 14,
    HandleReStartDrag = 1 << 15,
    HandleDragStart = 1 << 16,
    HandleDragEnd = 1 << 17,
    TransMenuShow = 1 << 18,
    TransDragWindowToFwk = 1 << 19,
};

struct DragDropInitiatingStateTestCase {
    DragDropInitiatingStatus originStatus = DragDropInitiatingStatus::IDLE;
    DragDropInitiatingReceivedInput receivedInput = DragDropInitiatingReceivedInput::HandleLongPressOnAction;
    DragDropInitiatingStatus expectStatus = DragDropInitiatingStatus::IDLE;
    DragDropInitiatingStateTestCase(DragDropInitiatingStatus originStatus,
        DragDropInitiatingReceivedInput receivedInput, DragDropInitiatingStatus expectStatus)
        : originStatus(originStatus), receivedInput(receivedInput), expectStatus(expectStatus)
    {}
};

constexpr int32_t DRAG_ACTION_NONE_ARGS = 1024;
constexpr int32_t DRAG_ACTION_DRAG_POINTER_EVENT_ARGS = 16384;
constexpr int32_t DRAG_ACTION_TOUCH_EVENT_ARGS = 12288;
constexpr int32_t DRAG_ACTION_GESTURE_EVENT_ARGS = 35839;

class DragDropInitiatingStateTestNG : public testing::Test {
public:
    static void DoMachineAction(const RefPtr<DragDropInitiatingStateMachine>& machine,
        DragDropInitiatingReceivedInput receivedInput, const DragPointerEvent& dragPointerEvent);
    static void DoMachineAction(const RefPtr<DragDropInitiatingStateMachine>& machine,
        DragDropInitiatingReceivedInput receivedInput, const TouchEvent& touchEvent);
    static void DoMachineAction(const RefPtr<DragDropInitiatingStateMachine>& machine,
        DragDropInitiatingReceivedInput receivedInput, const GestureEvent& info);
    static void DoMachineAction(
        const RefPtr<DragDropInitiatingStateMachine>& machine, DragDropInitiatingReceivedInput receivedInput);
    static testing::AssertionResult CheckDragDropInitiatingStatus(
        int32_t caseNum, DragDropInitiatingStatus dragStatus, DragDropInitiatingStatus expectStatus);
};

class DragDropInitiatingStateIdleTestNG : public DragDropInitiatingStateTestNG {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

class DragDropInitiatingStateLiftingTestNG : public DragDropInitiatingStateTestNG {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

class DragDropInitiatingStateMachineTestNG : public DragDropInitiatingStateTestNG {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

class DragDropInitiatingStateMovingTestNG : public DragDropInitiatingStateTestNG {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

class DragDropInitiatingStatePressTestNG : public DragDropInitiatingStateTestNG {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

class DragDropInitiatingStateReadyTestNG : public DragDropInitiatingStateTestNG {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

class DragDropInitiatingHandlerTestNg : public DragDropInitiatingStateTestNG {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};
} // namespace OHOS::Ace::NG
#endif // TEST_UNITTEST_CORE_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_TEST_NG_H