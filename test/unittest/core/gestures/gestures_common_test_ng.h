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

#ifndef TEST_UNITTEST_CORE_GESTURES_GESTURES_COMMON_TEST_NG_H
#define TEST_UNITTEST_CORE_GESTURES_GESTURES_COMMON_TEST_NG_H
#include <optional>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public

#undef SECURITY_COMPONENT_ENABLE

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/gestures/gesture_group.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/pinch_gesture.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/components_ng/gestures/recognizers/pinch_recognizer.h"
#include "core/components_ng/gestures/recognizers/rotation_recognizer.h"
#include "core/components_ng/gestures/recognizers/swipe_recognizer.h"
#include "core/components_ng/gestures/rotation_gesture.h"
#include "core/components_ng/gestures/swipe_gesture.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/gesture/gesture_model_ng.h"
#include "test/mock/core/render/mock_media_player.h"
#include "test/mock/core/render/mock_render_context.h"
#include "core/event/axis_event.h"
#include "core/event/key_event.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components/scroll/scroll_bar_controller.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DURATION = 100;
constexpr int32_t FINGER_NUMBER = 5;
constexpr int32_t FINGER_NUMBER_OVER_MAX = 11;
constexpr int32_t SINGLE_FINGER_NUMBER = 1;
constexpr int32_t COUNT = 2;
constexpr int32_t TAPPED_COUNT = 1;
constexpr int32_t LONG_PRESS_DURATION = 3000;
constexpr double PINCH_GESTURE_DISTANCE = 100.0;
constexpr double ROTATION_GESTURE_ANGLE = 1.0;
constexpr double CLICK_MULTI_TAP_SLOP = 110.0;
constexpr double PI = 360.0;
constexpr double COMMON_VALUE_RANGE_CASE = 101.0;
constexpr double SPECIAL_VALUE_RANGE_CASE1 = 181.0;
constexpr double SPECIAL_VALUE_RANGE_CASE2 = -181.0;
constexpr double SWIPE_SPEED = 10.0;
constexpr double VERTICAL_ANGLE = 90.0;
constexpr double HORIZONTAL_ANGLE = 180.0;
constexpr int32_t DEFAULT_PAN_FINGER = 1;
constexpr Dimension DEFAULT_PAN_DISTANCE = 5.0_vp;
constexpr int32_t DEFAULT_SLIDE_FINGER = DEFAULT_PAN_FINGER;
constexpr double DEFAULT_SLIDE_SPEED = 100.0;
constexpr double PAN_DISTANCE = 1.0;
constexpr int32_t TEST_EVENT_ID = 11;
} // namespace

class GesturesCommonTestNg : public testing::Test {
};
} // namespace OHOS::Ace::NG

#endif //TEST_UNITTEST_CORE_GESTURES_GESTURES_COMMON_TEST_NG_H