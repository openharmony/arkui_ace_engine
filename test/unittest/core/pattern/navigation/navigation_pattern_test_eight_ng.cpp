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

#include <optional>

#include "gtest/gtest.h"
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"

#define protected public
#define private public
#include "core/common/multi_thread_build_manager.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/stage/page_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_WINDOW_WIDTH = 100;
constexpr int32_t TEST_WINDOW_HEIGHT = 100;
} // namespace

class NavigationPatternTestEightNg : public testing::Test {
public:
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
};

RefPtr<NavigationBarTheme> NavigationPatternTestEightNg::navigationBarTheme_ = nullptr;

void NavigationPatternTestEightNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    navigationBarTheme_ = AceType::MakeRefPtr<NavigationBarTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == NavigationBarTheme::TypeId()) {
            return navigationBarTheme_;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void NavigationPatternTestEightNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationPatternTestEightNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: OnWindowSizeChanged001
 * @tc.desc: Branch: if (runningTransitionCount_ > 0) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, OnWindowSizeChanged001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->windowSizeChangedDuringTransition_ = false;
    pattern->runningTransitionCount_ = 1;
    pattern->OnWindowSizeChanged(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT, WindowSizeChangeReason::UNDEFINED);
    EXPECT_TRUE(pattern->windowSizeChangedDuringTransition_);
}

/**
 * @tc.name: OnWindowSizeChanged002
 * @tc.desc: Branch: if (runningTransitionCount_ > 0) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, OnWindowSizeChanged002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->windowSizeChangedDuringTransition_ = false;
    pattern->runningTransitionCount_ = 0;
    pattern->OnWindowSizeChanged(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT, WindowSizeChangeReason::UNDEFINED);
    EXPECT_FALSE(pattern->windowSizeChangedDuringTransition_);
}

/**
 * @tc.name: onHover
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, onHover, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pattern = navNode->GetPattern<NavigationPattern>();
    auto layoutProperty = pattern->GetLayoutProperty<NavigationLayoutProperty>();
    navNode->GetGeometryNode()->SetFrameSize(SizeF(1000.0, 1000.0));
    pattern->userSetNavBarWidthFlag_ = false;
    pattern->userSetNavBarRangeFlag_ = true;
    pattern->isInDividerDrag_ = false;

    /*
     *   test 500 < 1000 * 0.8
     */
    layoutProperty->UpdateMinNavBarWidth(Dimension(500, DimensionUnit::PX));
    layoutProperty->UpdateMaxNavBarWidth(Dimension(0.8, DimensionUnit::PERCENT));
    pattern->isDividerDraggable_ = false;
    pattern->OnHover(true);
    EXPECT_TRUE(pattern->isDividerDraggable_);

    /*
     *   test 1000 * 0.5 > 400
     */
    layoutProperty->UpdateMinNavBarWidth(Dimension(0.5, DimensionUnit::PERCENT));
    layoutProperty->UpdateMaxNavBarWidth(Dimension(400, DimensionUnit::PX));
    pattern->OnHover(true);
    EXPECT_FALSE(pattern->isDividerDraggable_);

    /*
     *  test 500px > 400px
     */
    layoutProperty->UpdateMinNavBarWidth(Dimension(500, DimensionUnit::PX));
    layoutProperty->UpdateMaxNavBarWidth(Dimension(400, DimensionUnit::PX));
    pattern->OnHover(true);
    EXPECT_FALSE(pattern->isDividerDraggable_);

    /*
     *  test 400px > 500px
     */
    layoutProperty->UpdateMinNavBarWidth(Dimension(400, DimensionUnit::PX));
    layoutProperty->UpdateMaxNavBarWidth(Dimension(500, DimensionUnit::PX));
    pattern->OnHover(true);
    EXPECT_TRUE(pattern->isDividerDraggable_);
}

/**
 * @tc.name: test CheckNeedInitRangeCalculation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, CheckNeedInitRangeCalculation, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pattern = navNode->GetPattern<NavigationPattern>();

    pattern->navigationSize_ = SizeF(100, 100);
    auto temp = SizeF(100, 100);
    bool ret = pattern->CheckNeedInitRangeCalculation(temp);
    EXPECT_FALSE(ret);

    auto tepm2 = SizeF(200, 200);
    ret = pattern->CheckNeedInitRangeCalculation(tepm2);
    EXPECT_TRUE(ret);
}
} // namespace OHOS::Ace::NG
