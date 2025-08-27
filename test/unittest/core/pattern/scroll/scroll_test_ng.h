/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "test/unittest/core/pattern/scrollable/scrollable_utils_test_ng.h"

#define private public
#define protected public
#include "test/mock/core/animation/mock_animation_manager.h"

#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

namespace OHOS::Ace::NG {
constexpr float DEFAULT_ACTIVE_WIDTH = 8.0f;
constexpr float DEFAULT_INACTIVE_WIDTH = 4.0f;
constexpr float DEFAULT_NORMAL_WIDTH = 4.0f;
constexpr float DEFAULT_TOUCH_WIDTH = 32.0f;
constexpr float NORMAL_WIDTH = 4.f;

constexpr float SCROLL_PAGING_SPEED_THRESHOLD = 1200.0f;
constexpr float BAR_WIDTH = 10.f;
constexpr char SCROLL_BAR_COLOR[] = "#66182431";

class ScrollTestNg : public ScrollableUtilsTestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetScroll();
    RefPtr<PaintWrapper> CreateScrollDone(const RefPtr<FrameNode>& frameNode = nullptr);
    ScrollModelNG CreateScroll();
    void CreateContent(float mainSize = CONTENT_MAIN_SIZE);
    void CreateFreeContent(const SizeF& size);
    void CreateContentChild(int32_t childNumber = 10);
    void ScrollBy(double pixelX, double pixelY, bool smooth = false) override;

    RefPtr<ScrollPattern> pattern_;
    RefPtr<ScrollEventHub> eventHub_;
    RefPtr<ScrollLayoutProperty> layoutProperty_;
    RefPtr<ScrollAccessibilityProperty> accessibilityProperty_;
    std::vector<RefPtr<FrameNode>> contentChildren_;
    RefPtr<ScrollBar> scrollBar_;
    RefPtr<Scrollable> scrollable_;
};

class ScrollModelNGTestNg : public TestNG {
    void SetUp() override;
    void TearDown() override;
};

class ScrollPatternTestNg : public TestNG {
    void SetUp() override;
    void TearDown() override;
};

class ScrollBarOverlayTestNg : public TestNG {
    void SetUp() override;
    void TearDown() override;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SCROLL_SCROLL_TEST_NG_H
