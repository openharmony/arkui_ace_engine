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

#ifndef TEST_UNITTEST_CORE_EVENT_EVENT_MANAGER_TEST_NG_H
#define TEST_UNITTEST_CORE_EVENT_EVENT_MANAGER_TEST_NG_H
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "mock_touch_event_target.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/geometry/point.h"
#include "base/geometry/rect.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components/ability_component/ability_component.h"
#include "core/components/ability_component/render_ability_component.h"
#include "core/components/box/render_box.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/swipe_recognizer.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/ace_events.h"
#include "core/event/axis_event.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/animation/animatable_properties.h"
#include "frameworks/core/common/event_manager.h"
#include "frameworks/core/common/font_manager.h"
#include "frameworks/core/common/manager_interface.h"
#include "frameworks/base/ressched/ressched_report.h"

namespace OHOS::Ace::NG {
namespace {
const std::string CTRL = "Ctrl";
const std::string SHIFT = "shift";
const std::string ALT = "alt";
const std::string CTRLSHIFT = "Ctrl + shift";
const std::string MOUSE = "mouse";
const std::string MOUSE_EVENT = "mouse_event";
const std::string MOUSE_EVENT_2 = "mouse_event_2";

const std::string CHARACTER_C = "C";
const std::string CHARACTER_A = "A";
const std::string CHARACTER_V = "V";
const std::string CHARACTER_Z = "Z";
const std::string CHARACTER_EIGHT = "8";
const std::string CHARACTER_X = "X";

const std::string SHORT_CUT_VALUE_X = "X";
const std::string SHORT_CUT_VALUE_Y = "Y";
const std::string SHORT_CUT_VALUE_Z = "Z";
const std::string SHORT_CUT_VALUE_A = "A";
const std::string SHORT_CUT_VALUE_C = "C";
const std::string SHORT_CUT_VALUE_V = "V";

constexpr int32_t NUM_CTRL_VALUE = 1;
constexpr int32_t NUM_SHIFT_VALUE = 2;
constexpr int32_t NUM_ALT_VALUE = 4;

constexpr int32_t NODEID = 1;
constexpr int32_t NODEID_2 = 2;
constexpr int32_t NODEID_3 = 3;

enum class CtrlKeysBit {
    CTRL = 1,
    SHIFT = 2,
    ALT = 4,
};

RefPtr<MockTaskExecutor> MOCK_TASK_EXECUTOR;
const int32_t CONTAINER_INSTANCE_ID = 777;
} // namespace

struct MockMouseEvent {
    MouseAction action;
    MouseButton button;
    bool expectedResult;
};

class EventManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};
} // namespace OHOS::Ace::NG

#endif //TEST_UNITTEST_CORE_EVENT_EVENT_MANAGER_TEST_NG_H