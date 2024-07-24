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
#include "gtest/gtest.h"
#include "gtest/hwext/gtest-ext.h"

#include "core/components/common/layout/constants.h"

#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "test/unittest/core/pattern/scrollable/scrollable_test_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components/scroll/scroll_bar_theme.h"

namespace OHOS::Ace::NG {
class ScrollableCoverTestNg : public ScrollableTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void SetUpMockThemeManager();
};

constexpr char BAR_STATE_AUTO[] = "BarState.Auto";
constexpr char BAR_STATE_ON[] = "BarState.On";
constexpr char BAR_STATE_OFF[] = "BarState.Off";
constexpr const char* SCROLLBAR_WIDTH_PX = "5.00px";
constexpr const char* SCROLLBAR_WIDTH_VP = "15.0vp";
constexpr const char* SCROLLBAR_WIDTH_PERCENT = "100%";
constexpr char SCROLLBAR_COLOR_BLUE[] = "#FF0000FF";
constexpr char SCROLLBAR_COLOR_RED[] = "#FF0000";
constexpr double SCROLLBAR_WIDTH_VALUE_PX = 5.0;
constexpr double SCROLLBAR_WIDTH_VALUE_VP = 15.0;
constexpr double SCROLLBAR_WIDTH_VALUE_PERCENT = 1.0;
constexpr double SCROLLBARTHEME_WIDTH_VALUE_PX = 100.0;

void ScrollableCoverTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void ScrollableCoverTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ScrollableCoverTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    InitNestedScrolls();
    ScrollableCoverTestNg::SetUpMockThemeManager();
}

void ScrollableCoverTestNg::TearDown()
{
    scroll_.Reset();
    mockScroll_.Reset();
}

void ScrollableCoverTestNg::SetUpMockThemeManager()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_SCROLL_BAR);
    auto scrollBarTheme = ScrollBarTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollBarTheme));
    scrollBarTheme->normalWidth_ = Dimension(SCROLLBARTHEME_WIDTH_VALUE_PX, DimensionUnit::VP);
}

/**
 * @tc.name: SetScrollBarModeTest001
 * @tc.desc: Test GetBarStateString and SetScrollBarMode method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, SetScrollBarModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ScrollBarMode to AUTO
     * @tc.expected: ScrollablePaintProperty ScrollBarMode is updated to AUTO
     */
    ScrollableModelNG::SetScrollBarMode(DisplayMode::AUTO);
    auto scrollablePn = scroll_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(scrollablePn->GetBarStateString(), BAR_STATE_AUTO);

    /**
     * @tc.steps: step2. Set ScrollBarMode to ON
     * @tc.expected: ScrollablePaintProperty ScrollBarMode is updated to ON
     */
    ScrollableModelNG::SetScrollBarMode(DisplayMode::ON);
    EXPECT_EQ(scrollablePn->GetBarStateString(), BAR_STATE_ON);

    /**
     * @tc.steps: step3. Set ScrollBarMode to OFF
     * @tc.expected: ScrollablePaintProperty ScrollBarMode is updated to OFF
     */
    ScrollableModelNG::SetScrollBarMode(DisplayMode::OFF);
    EXPECT_EQ(scrollablePn->GetBarStateString(), BAR_STATE_OFF);
}

/**
 * @tc.name: SetScrollBarWidthTest001
 * @tc.desc: Test SetScrollBarWidth and GetBarWidth method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, SetScrollBarWidthTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ScrollBarWidth to vp width
     * @tc.expected: ScrollablePaintProperty ScrollBarWidth is updated to vp width
     */
    ScrollableModelNG::SetScrollBarWidth(SCROLLBAR_WIDTH_VP);
    auto scrollablePn = scroll_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(scrollablePn->GetBarWidth().Value(), SCROLLBAR_WIDTH_VALUE_VP);
    EXPECT_EQ(scrollablePn->GetBarWidth().Unit(), DimensionUnit::VP);

    /**
     * @tc.steps: step2. Set ScrollBarWidth to px width
     * @tc.expected: ScrollablePaintProperty ScrollBarWidth is updated to px width
     */
    ScrollableModelNG::SetScrollBarWidth(SCROLLBAR_WIDTH_PX);
    EXPECT_EQ(scrollablePn->GetBarWidth().Value(), SCROLLBAR_WIDTH_VALUE_PX);
    EXPECT_EQ(scrollablePn->GetBarWidth().Unit(), DimensionUnit::PX);

    /**
     * @tc.steps: step3. Set ScrollBarWidth to percent width
     * @tc.expected: ScrollablePaintProperty ScrollBarWidth is updated to percent width
     */
    ScrollableModelNG::SetScrollBarWidth(SCROLLBAR_WIDTH_PERCENT);
    EXPECT_EQ(scrollablePn->GetBarWidth().Value(), SCROLLBAR_WIDTH_VALUE_PERCENT);
    EXPECT_EQ(scrollablePn->GetBarWidth().Unit(), DimensionUnit::PERCENT);
}

/**
 * @tc.name: SetScrollBarColorTest001
 * @tc.desc: Test SetScrollBarColor and GetBarColor method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, SetScrollBarColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ScrollBarColor to blue
     * @tc.expected: ScrollablePaintProperty ScrollBarColor is updated to blue
     */
    ScrollableModelNG::SetScrollBarColor(SCROLLBAR_COLOR_BLUE);
    auto scrollablePn = scroll_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(scrollablePn->GetBarColor(), Color::FromString(SCROLLBAR_COLOR_BLUE));

    /**
     * @tc.steps: step2. Set ScrollBarColor to red
     * @tc.expected: ScrollablePaintProperty ScrollBarColor is updated to red
     */
    ScrollableModelNG::SetScrollBarColor(SCROLLBAR_COLOR_RED);
    EXPECT_EQ(scrollablePn->GetBarColor(), Color::FromString(SCROLLBAR_COLOR_RED));
}

/**
 * @tc.name: ToJsonValueTest001
 * @tc.desc: Test ToJsonValue method of ScrollablePaintProperty
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, ToJsonValueTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a ScrollablePaintProperty object and set Property
    */
    ScrollableModelNG::SetScrollBarColor(SCROLLBAR_COLOR_BLUE);
    ScrollableModelNG::SetScrollBarWidth(SCROLLBAR_WIDTH_PX);
    auto scrollablePn = scroll_->GetPaintProperty<ScrollablePaintProperty>();

    /**
     * @tc.steps: step2. Set properties
    */
    scrollablePn->UpdateScrollBarMode(DisplayMode::AUTO);
    /**
     * @tc.steps: step3. Convert to JSON
    */
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    scrollablePn->ToJsonValue(json, filter);

    /**
     * @tc.steps: step4. Convert to JSON
    */
    EXPECT_EQ(json->GetString("scrollBar"), BAR_STATE_AUTO);
    EXPECT_EQ(json->GetString("scrollBarColor"), SCROLLBAR_COLOR_BLUE);
    EXPECT_EQ(json->GetString("scrollBarWidth"), SCROLLBAR_WIDTH_PX);
}
} // namespace OHOS::Ace::NG
