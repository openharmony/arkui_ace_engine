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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SCROLL_BAR_SCROLL_BAR_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SCROLL_BAR_SCROLL_BAR_TEST_NG_H

#include "test/unittest/core/pattern/test_ng.h"

#define private public
#define protected public
#include "test/mock/core/animation/mock_animation_manager.h"

#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float SCROLL_WIDTH = 480.f;
constexpr float SCROLL_HEIGHT = 800.f;
constexpr float CONTENT_MAIN_SIZE = 1000.f;
constexpr float SCROLL_BAR_CHILD_WIDTH = 20.f;
constexpr float SCROLL_BAR_CHILD_HEIGHT = 160.f;

class ScrollBarTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetScrollBar();

    RefPtr<FrameNode> CreateMainFrameNode();
    void CreateStack(Alignment align = Alignment::CENTER_RIGHT);
    void CreateScroll(float mainSize = CONTENT_MAIN_SIZE, Axis axis = Axis::VERTICAL);
    void CreateContent(float mainSize = CONTENT_MAIN_SIZE, Axis axis = Axis::VERTICAL);
    void CreateScrollBar(bool infoflag, bool proxyFlag, Axis axis, DisplayMode displayMode);
    void CreateScrollBarChild(float mainSize = SCROLL_BAR_CHILD_HEIGHT);
    void SetScrollContentMainSize(float mainSize);

    RefPtr<FrameNode> stackNode_;

    RefPtr<FrameNode> scrollNode_;
    RefPtr<ScrollPattern> scrollPattern_;

    RefPtr<FrameNode> frameNode_;
    RefPtr<ScrollBarPattern> pattern_;
    RefPtr<ScrollBarLayoutProperty> layoutProperty_;
    RefPtr<ScrollablePaintProperty> paintProperty_;
    RefPtr<ScrollBarAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_SCROLL_BAR_SCROLL_BAR_TEST_NG_H
