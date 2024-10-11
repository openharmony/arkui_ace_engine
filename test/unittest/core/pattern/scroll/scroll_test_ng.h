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

#include "test/unittest/core/pattern/test_ng.h"

#define private public
#define protected public
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float SCROLL_WIDTH = 240.f;
constexpr float SCROLL_HEIGHT = 400.f;
constexpr float CONTENT_MAIN_SIZE = 1000.f;
constexpr float ITEM_MAIN_SIZE = 100.f;
constexpr float VERTICAL_SCROLLABLE_DISTANCE = CONTENT_MAIN_SIZE - SCROLL_HEIGHT;
constexpr float HORIZONTAL_SCROLLABLE_DISTANCE = CONTENT_MAIN_SIZE - SCROLL_WIDTH;

constexpr float DEFAULT_ACTIVE_WIDTH = 8.0f;
constexpr float DEFAULT_INACTIVE_WIDTH = 4.0f;
constexpr float DEFAULT_NORMAL_WIDTH = 4.0f;
constexpr float DEFAULT_TOUCH_WIDTH = 32.0f;
constexpr float NORMAL_WIDTH = 4.f;

constexpr float SCROLL_PAGING_SPEED_THRESHOLD = 1200.0f;
constexpr int32_t TICK = 2;
constexpr float BAR_WIDTH = 10.f;

class ScrollTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetScroll();
    RefPtr<PaintWrapper> CreateScrollDone(const RefPtr<FrameNode>& frameNode = nullptr);
    ScrollModelNG CreateScroll();
    void CreateContent(float mainSize = CONTENT_MAIN_SIZE);
    void CreateContentChild(int32_t childNumber = 10);
    void ScrollToEdge(ScrollEdgeType scrollEdgeType);
    void ScrollTo(float offset);
    void ScrollBy(float pixelX, float pixelY);
    AssertionResult Position(const RefPtr<FrameNode>& frameNode, float expectOffset);
    AssertionResult TickPosition(const RefPtr<FrameNode>& frameNode, float expectOffset);
    AssertionResult TickByVelocityPosition(const RefPtr<FrameNode>& frameNode, float velocity, float expectOffset);
    AssertionResult Position(float expectOffset);
    AssertionResult TickPosition(float expectOffset);
    AssertionResult TickByVelocityPosition(float velocity, float expectOffset);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ScrollPattern> pattern_;
    RefPtr<ScrollEventHub> eventHub_;
    RefPtr<ScrollLayoutProperty> layoutProperty_;
    RefPtr<ScrollablePaintProperty> paintProperty_;
    RefPtr<ScrollAccessibilityProperty> accessibilityProperty_;
    RefPtr<ScrollableController> positionController_;
    std::vector<RefPtr<FrameNode>> contentChildren_;
    RefPtr<ScrollBar> scrollBar_;
    RefPtr<Scrollable> scrollable_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SCROLL_SCROLL_TEST_NG_H
