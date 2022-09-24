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

#include "core/components/root/render_root.h"
#include "core/components/tab_bar/render_tab_bar.h"
#include "core/components/flex/render_flex.h"
#include "core/components/box/render_box.h"
#include "core/components/flex/flex_component.h"
#include "core/components/tab_bar/tab_bar_component.h"
#include "core/components/tab_bar/tab_controller.h"
#include "core/components/test/unittest/mock/mock_render_common.h"
#include "core/components/test/unittest/tabbar/tabbar_test_utils.h"
#include "core/components_v2/tabs/tab_content_item_component.h"
#include "core/components_v2/tabs/tabs_component.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::V2 {

class RenderTabsTestV2 : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void RenderTabsTestV2::SetUpTestCase() {}
void RenderTabsTestV2::TearDownTestCase() {}
void RenderTabsTestV2::SetUp() {}
void RenderTabsTestV2::TearDown() {}

/**
 * @tc.name: RenderTabsContinuation001
 * @tc.desc: Test state transfer of the tabbar component
 * @tc.type: FUNC
 * @tc.require: issueI5NC9F
 */
HWTEST_F(RenderTabsTestV2, RenderTabsContinuation001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTabsTestV2 Continuation001 start";

    /**
     * @tc.steps: step1. construct TabBarComponent.
     */
    TabBarMode mode = TabBarMode::SCROLLABLE;
    RefPtr<TabBarComponent> tabBarComponent = AceType::MakeRefPtr<TabBarComponent>(
        std::list<RefPtr<Component>>(), TabController::GetController(0));
    tabBarComponent->SetMode(mode);

    /**
     * @tc.steps: step2. Set index state of tabbar component.
     */
    std::list<RefPtr<Component>> children;
    auto flexComponent = AceType::MakeRefPtr<FlexComponent>(FlexDirection::ROW, FlexAlign::CENTER,
        FlexAlign::CENTER, children);
    flexComponent->SetTabsFlag(true);
    EXPECT_TRUE(flexComponent->GetTabsFlag());
    RefPtr<RenderFlex> renderFlex = AceType::MakeRefPtr<RenderFlex>();
    RefPtr<RenderBox> renderBox = AceType::MakeRefPtr<RenderBox>();
    RefPtr<MockRenderTabBar> renderTabBar = AceType::MakeRefPtr<MockRenderTabBar>();
    renderTabBar->SetIndex(2);
    renderFlex->Update(flexComponent);
    renderBox->AddChild(renderTabBar);
    renderFlex->AddChild(renderBox);

    /**
     * @tc.steps: step3. Store index state of tabbar component.
     * @tc.expected: step3. The return string is correct.
     */
    std::string info = renderFlex->ProvideRestoreInfo();
    std::string expectStateResult = "{\"index\":2,\"OffsetX\":0,\"OffsetY\":0}";
    EXPECT_EQ(info, expectStateResult);

    /**
     * @tc.steps: step4. Restore index state of tabbar component.
     * @tc.expected: step4. The index state is correct.
     */
    renderFlex->SetRestoreInfo(expectStateResult);
    renderTabBar->Update(tabBarComponent);
    EXPECT_EQ(renderTabBar->GetIndex(), 2);

    /**
     * @tc.steps: step5. Second Update doesn't restore the state.
     * @tc.expected: step5. The stored string is empty.
     */
    renderTabBar->Update(tabBarComponent);
    EXPECT_TRUE(renderFlex->GetRestoreInfo().empty());

    /**
     * @tc.steps: step6. Restore state from invalid json string.
     * @tc.expected: step6. The state is unchanged.
     */
    std::string invalidInfo = "{\"index\":3,\"OffsetX\":0,\"OffsetY\":0}";
    renderTabBar->SetRestoreInfo(invalidInfo);
    renderTabBar->Update(tabBarComponent);
    EXPECT_EQ(renderTabBar->GetIndex(), -1);

    GTEST_LOG_(INFO) << "RenderTabsTestV2 Continuation001 stop";
}

/**
 * @tc.name: RenderTabsContinuation002
 * @tc.desc: Test state transfer of the tabcontent component
 * @tc.type: FUNC
 * @tc.require: issueI5NC9F
 */
HWTEST_F(RenderTabsTestV2, RenderTabsContinuation002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTabsTestV2 Continuation002 start";

    /**
     * @tc.steps: step1. construct TabContentComponent.
     */
    auto tabController = TabController::GetController(0);
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 5; i++) {
        componentChildren.emplace_back(AceType::MakeRefPtr<BoxComponent>());
    }
    RefPtr<TabContentComponent> tabContentComponent =
    AceType::MakeRefPtr<TabContentComponent>(componentChildren, tabController);

    /**
     * @tc.steps: step2. Set index state of tabcontent component.
     */
    std::list<RefPtr<Component>> children;
    auto flexComponent = AceType::MakeRefPtr<FlexComponent>(FlexDirection::ROW, FlexAlign::CENTER,
        FlexAlign::CENTER, children);
    flexComponent->SetTabContentFlag(true);
    EXPECT_TRUE(flexComponent->GetTabContentFlag());
    RefPtr<RenderFlex> renderFlex = AceType::MakeRefPtr<RenderFlex>();
    RefPtr<RenderBox> renderBox = AceType::MakeRefPtr<RenderBox>();
    RefPtr<RenderTabContent> renderTabContent = AceType::MakeRefPtr<RenderTabContent>();
    auto mockContext = MockRenderCommon::GetMockContext();
    renderTabContent->Attach(mockContext);
    renderFlex->Update(flexComponent);
    renderBox->AddChild(renderTabContent);
    renderFlex->AddChild(renderBox);

    /**
     * @tc.steps: step3. Store index state of tabcontent component.
     * @tc.expected: step3. The return string is correct.
     */
    std::string info = renderTabContent->ProvideRestoreInfo();
    std::string expectStateResult = "0";
    EXPECT_EQ(info, expectStateResult);

    /**
     * @tc.steps: step4. Restore index state of tabcontent component.
     * @tc.expected: step4. The index state is correct.
     */
    renderTabContent->SetRestoreInfo(expectStateResult);
    renderTabContent->Update(tabContentComponent);
    EXPECT_EQ(renderTabContent->GetCurrentIndex(), 0);

    /**
     * @tc.steps: step5. Second Update doesn't restore the state.
     * @tc.expected: step5. The stored string is empty.
     */
    renderTabContent->Update(tabContentComponent);
    EXPECT_TRUE(renderFlex->GetRestoreInfo().empty());

    GTEST_LOG_(INFO) << "RenderTabsTestV2 Continuation002 stop";
}

/**
 * @tc.name: RenderTabsContinuation003
 * @tc.desc: Test state transfer of the TabContentItemComponent
 * @tc.type: FUNC
 * @tc.require: issueI5NC9F
 */
HWTEST_F(RenderTabsTestV2, RenderTabsContinuation003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTabsTestV2 Continuation003 start";

    /**
     * @tc.steps: step1. construct TabContentItemComponent.
     * @tc.expected: step3. The flag is true.
     */
    std::list<RefPtr<Component>> components;
    auto tabContentItemComponent = AceType::MakeRefPtr<V2::TabContentItemComponent>(components);
    EXPECT_TRUE(tabContentItemComponent->GetTabContentFlag());

    GTEST_LOG_(INFO) << "RenderTabsTestV2 Continuation003 stop";
}

/**
 * @tc.name: RenderTabsContinuation004
 * @tc.desc: Test state transfer of the TabContentItemComponent
 * @tc.type: FUNC
 * @tc.require: issueI5NC9F
 */
HWTEST_F(RenderTabsTestV2, RenderTabsContinuation004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTabsTestV2 Continuation004 start";

    /**
     * @tc.steps: step1. construct TabContentItemComponent.
     * @tc.expected: step3. The flag is true.
     */
    BarPosition barVal = BarPosition::START;
    RefPtr<TabController> tabController;
    std::list<RefPtr<Component>> children;
    auto tabsComponent = AceType::MakeRefPtr<V2::TabsComponent>(children, barVal, tabController);
    EXPECT_TRUE(tabsComponent->GetTabsFlag());

    GTEST_LOG_(INFO) << "RenderTabsTestV2 Continuation004 stop";
}

} // namespace OHOS::Ace::V2
