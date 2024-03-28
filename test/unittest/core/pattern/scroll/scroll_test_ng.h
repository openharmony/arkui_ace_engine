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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SCROLL_SCROLL_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SCROLL_SCROLL_TEST_NG_H

#include <cstdint>
#include <memory>
#include <utility>

#include "gtest/gtest.h"

#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/animation/animator.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/color.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float SCROLL_WIDTH = 480.f;
constexpr float SCROLL_HEIGHT = 800.f;
constexpr int32_t TOTAL_LINE_NUMBER = 10;
constexpr int32_t VIEW_LINE_NUMBER = 8;
constexpr int32_t SNAP_ITEM_NUMBER = 30;
constexpr float DEFAULT_ACTIVE_WIDTH = 8.0f;
constexpr float DEFAULT_INACTIVE_WIDTH = 4.0f;
constexpr float DEFAULT_NORMAL_WIDTH = 4.0f;
constexpr float DEFAULT_TOUCH_WIDTH = 32.0f;
constexpr float ITEM_WIDTH = SCROLL_WIDTH / VIEW_LINE_NUMBER;
constexpr float ITEM_HEIGHT = SCROLL_HEIGHT / VIEW_LINE_NUMBER;
constexpr float VERTICAL_SCROLLABLE_DISTANCE = (TOTAL_LINE_NUMBER - VIEW_LINE_NUMBER) * ITEM_HEIGHT;
constexpr float SNAP_SCROLLABLE_DISTANCE = (SNAP_ITEM_NUMBER - VIEW_LINE_NUMBER) * ITEM_HEIGHT;
constexpr float NORMAL_WIDTH = 4.f;
constexpr float SCROLL_PAGING_SPEED_THRESHOLD = 1200.0f;

class ScrollTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    void UpdateCurrentOffset(float offset);

    void Create(const std::function<void(ScrollModelNG)>& callback = nullptr);
    void CreateWithContent(
        const std::function<void(ScrollModelNG)>& callback = nullptr, int32_t childNumber = TOTAL_LINE_NUMBER);
    void CreateSnapScroll(ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
        const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide);

    static void CreateContent(int32_t childNumber = TOTAL_LINE_NUMBER);
    RefPtr<FrameNode> GetContentChild(int32_t index);
    void Touch(TouchLocationInfo locationInfo, SourceType sourceType);
    void Touch(TouchType touchType, Offset offset, SourceType sourceType);
    void Mouse(MouseInfo mouseInfo);
    void Mouse(Offset moveOffset);
    void Hover(bool isHover);
    bool OnScrollCallback(float offset, int32_t source);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType);
    void ScrollTo(float offset);
    static Axis GetAxis();
    float GetOffset(float childNumber);
    AssertionResult UpdateAndVerifyPosition(float offset, float expectOffset, int32_t source = SCROLL_FROM_UPDATE);
    AssertionResult ScrollToNode(int32_t childIndex, float expectChildNumber);
    AssertionResult IsEqualCurrentPosition(float expectOffset);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ScrollPattern> pattern_;
    RefPtr<ScrollEventHub> eventHub_;
    RefPtr<ScrollLayoutProperty> layoutProperty_;
    RefPtr<ScrollablePaintProperty> paintProperty_;
    RefPtr<ScrollAccessibilityProperty> accessibilityProperty_;
    RefPtr<ScrollBar> scrollBar_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SCROLL_SCROLL_TEST_NG_H