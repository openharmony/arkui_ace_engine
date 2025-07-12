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
#include "core/components/button/button_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_container_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class NavigationModelTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
};

void NavigationModelTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationModelTestTwoNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationModelTestTwoNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: Create001
 * @tc.desc: Branch: if (!useHomeDest.has_value()) { => true
 *                   if (!useHomeDest.value() && !CreateNavBarNodeIfNeeded(navigationGroupNode)) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, Create001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create(true);
    navigationModel.SetNavigationStack();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navNode->GetNavBarNode());
    EXPECT_EQ(navBarNode, nullptr);
    auto useHomeDest = navNode->GetUseHomeDestination();
    ASSERT_TRUE(useHomeDest.has_value());
    EXPECT_TRUE(useHomeDest.value());
}

/**
 * @tc.name: Create002
 * @tc.desc: Branch: if (!useHomeDest.has_value()) { => true
 *                   if (!useHomeDest.value() && !CreateNavBarNodeIfNeeded(navigationGroupNode)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, Create002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create(false);
    navigationModel.SetNavigationStack();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navNode->GetNavBarNode());
    EXPECT_NE(navBarNode, nullptr);
    auto useHomeDest = navNode->GetUseHomeDestination();
    ASSERT_TRUE(useHomeDest.has_value());
    EXPECT_FALSE(useHomeDest.value());
}
} // namespace OHOS::Ace::NG