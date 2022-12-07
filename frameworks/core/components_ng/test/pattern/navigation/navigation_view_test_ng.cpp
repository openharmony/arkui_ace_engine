/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_view.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/components_ng/pattern/navigator/navigator_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class NavigationViewTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
protected:
};

/**
 * @tc.name: NavigationViewTest_001
 * @tc.desc: Test NavigationView SetTitleMode.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationViewTestNg, NavigationViewTest_001, TestSize.Level1)
{
    NavigationView navigationView;
    navigationView.Create();
    navigationView.SetTitle("navigationView", false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    EXPECT_NE(navBarNode, nullptr);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    EXPECT_NE(navBarLayoutProperty, nullptr);
    navigationView.SetTitleMode(NavigationTitleMode::FREE);
    navigationView.SetTitleMode(NavigationTitleMode::MINI);
    bool result = true;
    if (navBarLayoutProperty->GetTitleModeString() != "NavigationTitleMode.Mini") {
        result = false;
    }
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: NavigationViewTest_002
 * @tc.desc: Test NavigationView SetHideTitleBar false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationViewTestNg, NavigationViewTest_002, TestSize.Level1)
{
    NavigationView navigationView;
    navigationView.Create();
    navigationView.SetTitle("navigationView", false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    EXPECT_NE(navBarNode, nullptr);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    EXPECT_NE(navBarLayoutProperty, nullptr);
    navigationView.SetHideTitleBar(false);
    EXPECT_EQ(navBarLayoutProperty->GetHideTitleBar().value_or(false), false);
}

/**
 * @tc.name: NavigationViewTest_003
 * @tc.desc: Test NavigationView SetHideToolBar false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationViewTestNg, NavigationViewTest_003, TestSize.Level1)
{
    NavigationView navigationView;
    navigationView.Create();
    navigationView.SetTitle("navigationView", false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    EXPECT_NE(navBarNode, nullptr);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    EXPECT_NE(navBarLayoutProperty, nullptr);
    navigationView.SetHideToolBar(false);
    EXPECT_EQ(navBarLayoutProperty->GetHideToolBar().value_or(false), false);
}
}