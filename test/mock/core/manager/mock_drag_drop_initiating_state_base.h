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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_MANAGER_DRAG_DROP_INITIATING_STATE_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_MANAGER_DRAG_DROP_INITIATING_STATE_BASE_H

#include "gmock/gmock-function-mocker.h"
#include "gmock/gmock.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_base.h"

namespace OHOS::Ace {
class MockDragDropInitiatingStateBase : public NG::DragDropInitiatingStateBase {
    DECLARE_ACE_TYPE(MockDragDropInitiatingStateBase, DragDropInitiatingStateBase);

public:
    MOCK_METHOD(void, Init, (int32_t currentState), (override));
    MOCK_METHOD(void, HandleLongPressOnAction, (const GestureEvent& info), (override));
    MOCK_METHOD(void, HandleLongPressOnActionEnd, (const GestureEvent& info), (override));
    MOCK_METHOD(void, HandleLongPressOnActionCancel, (const GestureEvent& info), (override));
    MOCK_METHOD(void, HandlePreviewLongPressOnAction, (const GestureEvent& info), (override));
    MOCK_METHOD(void, HandlePreviewLongPressOnActionEnd, (const GestureEvent& info), (override));
    MOCK_METHOD(void, HandlePreviewLongPressOnActionCancel, (const GestureEvent& info), (override));
    MOCK_METHOD(void, HandlePanOnActionStart, (const GestureEvent& info), (override));
    MOCK_METHOD(void, HandlePanOnActionUpdate, (const GestureEvent& info), (override));
    MOCK_METHOD(void, HandlePanOnActionEnd, (const GestureEvent& info), (override));
    MOCK_METHOD(void, HandlePanOnActionCancel, (const GestureEvent& info), (override));
    MOCK_METHOD(void, HandlePanOnReject, (), (override));
    MOCK_METHOD(void, HandleSequenceOnActionCancel, (const GestureEvent& info), (override));
    MOCK_METHOD(void, HandleHitTesting, (const TouchEvent& touchEvent), (override));
    MOCK_METHOD(void, HandleTouchEvent, (const TouchEvent& touchEvent), (override));
    MOCK_METHOD(void, HandlePullEvent, (const DragPointerEvent& dragPointerEvent), (override));
    MOCK_METHOD(void, HandleReStartDrag, (const GestureEvent& info), (override));
    MOCK_METHOD(void, HandleDragStart, (), (override));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_MANAGER_DRAG_DROP_INITIATING_STATE_BASE_H