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

#ifndef TEST_UNITTEST_CORE_EVENT_DRAG_EVENT_TEST_NG_H
#define TEST_UNITTEST_CORE_EVENT_DRAG_EVENT_TEST_NG_H
#include "gtest/gtest.h"
#include <string>

#define private public
#define protected public

#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/theme/blur_style_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/event/drag_event.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double GESTURE_EVENT_PROPERTY_DEFAULT_VALUE = 0.0;
constexpr double GESTURE_EVENT_PROPERTY_VALUE = 10.0;
const PanDirection DRAG_DIRECTION = { PanDirection::LEFT };
const TouchRestrict DRAG_TOUCH_RESTRICT = { TouchRestrict::CLICK };
const TouchRestrict DRAG_TOUCH_RESTRICT_MOUSE = {
    .forbiddenType = TouchRestrict::CLICK,
    .sourceType = SourceType::MOUSE
};
constexpr int32_t UNKNOWN = 1;
constexpr int32_t FINGERS_NUMBER = 2;
constexpr int32_t TOUCH_TEST_RESULT_SIZE = 1;
constexpr int32_t TOUCH_TEST_RESULT_SIZE_2 = 2;
constexpr int32_t NUMBER_BADGE_SIZE_3 = 3;
constexpr int32_t NUMBER_BADGE_SIZE_100 = 100;
constexpr float DISTANCE = 10.5f;
constexpr float WIDTH = 400.0f;
constexpr float HEIGHT = 400.0f;
const OffsetF COORDINATE_OFFSET(WIDTH, HEIGHT);
constexpr int32_t FINGERS_NUMBER_GREATER_THAN_DEFAULT = 2;
constexpr float DISTANCE_GREATER_THAN_DEFAULT = 6.0f;
constexpr float DISTANCE_EQUAL_DEFAULT = 5.0f;
constexpr float IMAGE_INVALID_RECT_WIDTH = 100.0f;
const std::string COMPONENT_ID = "id of component which you want to get screenshot from";
const std::string NO_COMPONENT_ID = "";
const std::string TOUCH_EVENT_INFO_TYPE = "onTouchDown";
constexpr int32_t LONG_PRESS_DURATION = 500;
} // namespace

class DragEventTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};
} // namespace OHOS::Ace::NG

#endif //TEST_UNITTEST_CORE_EVENT_DRAG_EVENT_TEST_NG_H