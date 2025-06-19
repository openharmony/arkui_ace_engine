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
#ifndef PATTERNLOCK_TEST_NG_H
#define PATTERNLOCK_TEST_NG_H
#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#define private public
#define protected public
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/patternlock/patternlock_layout_algorithm.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_method.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_property.h"
#include "core/components_ng/pattern/patternlock/patternlock_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_v2/pattern_lock/pattern_lock_component.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float SCROLL_WIDTH = 480.f;
constexpr float SCROLL_HEIGHT = 800.f;
constexpr float PATTERNLOCK_WIDTH = 400.f;
constexpr float PATTERNLOCK_HEIGHT = 400.f;
constexpr Dimension SIDE_LENGTH = 300.0_vp;
constexpr Dimension CIRCLE_RADIUS = 14.0_vp;
constexpr Dimension ACTIVE_CIRCLE_RADIUS = 18.0_vp;
const Color REGULAR_COLOR = Color::BLACK;
const Color SELECTED_COLOR = Color::BLUE;
const Color ACTIVE_COLOR = Color::RED;
const Color PATH_COLOR = Color::GRAY;
const Color HOVER_COLOR = Color::GRAY;
const Color ACTIVE_CIRCLE_COLOR = Color::GREEN;
constexpr Dimension PATH_STROKE_WIDTH = 34.0_vp;
constexpr Dimension HOTSPOT_CIRCLE_RADIUS = 48.0_vp;
constexpr float SIDE_LENGH = 36.0f;
constexpr float POINT_NOT_CHECK_FLOAT = -4.0f;
constexpr float POINT_CHECK_FLOAT = 10.0f;
constexpr float LAST_POINT_CHECK_FLOAT = 3.0f;
constexpr float FIRST_POINT_CHECK_FLOAT = 200.0f;
constexpr float CONTENT_SIZE_FLOAT = 300.0f;
constexpr float CONTENT_OFFSET_FLOAT = 150.0f;
constexpr float CIRCLE_RADIUS_FLOAT = 200.0f;
constexpr float DEFAULT_SIDE_LENGTH = 20.0f;
constexpr int32_t PATTERN_LOCK_COL_COUNT = 3;
constexpr int32_t RADIUS_TO_DIAMETER = 2;
constexpr float TOUCHPOINT_OFFSET_FLOAT = 200.0f;
inline int32_t GetPointIndex(int32_t x, int32_t y)
{
    return (x - 1) * PATTERN_LOCK_COL_COUNT + (y - 1);
}

class PatternLockTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    void Create(const std::function<void(PatternLockModelNG)>& callback);

    RefPtr<FrameNode> frameNode_;
    RefPtr<PatternLockPattern> pattern_;
    RefPtr<PatternLockEventHub> eventHub_;
    RefPtr<PatternLockLayoutProperty> layoutProperty_;
    RefPtr<PatternLockPaintProperty> paintProperty_;
};
#endif