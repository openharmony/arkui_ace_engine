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

#ifndef TEST_UNITTEST_CORE_EVENT_GESTURE_EVENT_HUB_TEST_NG_H
#define TEST_UNITTEST_CORE_EVENT_GESTURE_EVENT_HUB_TEST_NG_H
#include "gtest/gtest.h"

#define private public
#define protected public
#undef SECURITY_COMPONENT_ENABLE

#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/pan_event.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/core/common/event_manager.h"
#include "frameworks/core/components_ng/pattern/text_drag/text_drag_base.h"

namespace OHOS::Ace::NG {
namespace {
const std::string NODE_TAG("node");
const OffsetF COORDINATE_OFFSET(20.0f, 20.0f);
constexpr int32_t TOUCH_ID = 0;
const Axis AXIS_VERTICAL = Axis::VERTICAL;
const PanDirection PAN_DIRECTION_ALL;
constexpr int32_t FINGERS = 1;
constexpr int32_t DOUBLE_FINGERS = 2;
constexpr int32_t CLICK_COUNTS = 2;
constexpr Dimension DISTANCE = 10.0_vp;
const std::string CHECK_TAG_1("HELLO");
const std::string CHECK_TAG_2("WORLD");
const PointF GLOBAL_POINT { 20.0f, 20.0f };
const PointF LOCAL_POINT { 15.0f, 15.0f };
RefPtr<DragWindow> MOCK_DRAG_WINDOW;
constexpr int32_t GESTURES_COUNTS = 2;
RefPtr<MockTaskExecutor> MOCK_TASK_EXECUTOR;
constexpr float DRAG_DISTANCE = 10.5f;
const PanDirection DRAG_DIRECTION = { PanDirection::LEFT };
constexpr int32_t FINGERS_NUMBER = 2;
constexpr int32_t PARALLEL_INDEX_1 = 2;
constexpr int32_t PARALLEL_INDEX_2 = 0;
constexpr float PREVIEW_DOWN_SCALE = 0.8f;
constexpr float PREVIEW_UP_SCALE = 1.2f;
constexpr float EXPECT_SCALE = 1.0f;
constexpr float PREVIEW_NEGA_SCALE = -1.0f;
constexpr int32_t PIXELMAP_WIDTH_LARGE = 200;
constexpr int32_t PIXELMAP_WIDTH = 100;
constexpr int32_t PIXELMAP_HEIGHT = 200;
constexpr int32_t INSTANCE_ID = 123;
constexpr float SIZE_X = 100.0f;
constexpr float SIZE_Y = 100.0f;
constexpr float INIT_MOVE_X = 50.0f;
constexpr float INIT_MOVE_Y = 50.0f;
constexpr float LAST_MOVE_X = 30.0f;
constexpr float LAST_MOVE_Y = 30.0f;
constexpr float TOTAL_MOVE_X = 20.0f;
constexpr float TOTAL_MOVE_Y = 20.0f;
constexpr float SIZE_ZERO = 0.0f;
constexpr float DEFAULT_SCALE = 1.0f;
constexpr float FRAME_OFFSET_X = 30.0f;
constexpr float FRAME_OFFSET_Y = 40.0f;
constexpr float FRAME_WIDTH = 30.0f;
constexpr float FRAME_HEIGHT = 60.0f;
constexpr float MOVE_OFFSET_X = 10.0f;
constexpr float MOVE_OFFSET_Y = 10.0f;
constexpr float GESTURE_GLOBAL_X = 10.0f;
constexpr float GESTURE_GLOBAL_Y = 20.0f;
constexpr float INNER_OFFSET_X = 5.0f;
constexpr float INNER_OFFSET_Y = 10.0f;
constexpr float DRAG_OFFSET_X = 40.0f;
constexpr float DRAG_OFFSET_Y = 40.0f;
} // namespace

class GestureEventHubTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};
class GestureEventHubTestCoverageNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};
} // namespace OHOS::Ace::NG

#endif //TEST_UNITTEST_CORE_EVENT_GESTURE_EVENT_HUB_TEST_NG_H