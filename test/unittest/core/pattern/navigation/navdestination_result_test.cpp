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

#include "gtest/gtest.h"

#define protected public
#define private public
#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/pipeline/pipeline_base.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "mock_navigation_stack.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

int onPopIndex_ = 0;

class NavDestinationResultTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
    RefPtr<NavDestinationGroupNode> CreateNavDestinationNode(const std::string& name);
};

void NavDestinationResultTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavDestinationResultTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavDestinationResultTest::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == NavigationBarTheme::TypeId()) {
            return AceType::MakeRefPtr<NavigationBarTheme>();
        } else if (type == AgingAdapationDialogTheme::TypeId()) {
            return AceType::MakeRefPtr<AgingAdapationDialogTheme>();
        } else {
            return AceType::MakeRefPtr<DialogTheme>();
        }
    });
}

RefPtr<NavDestinationGroupNode> NavDestinationResultTest::CreateNavDestinationNode(const std::string& name)
{
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(
        NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG, 101,
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); }));
    EXPECT_FALSE(navDestinationGroupNode == nullptr);
    auto pattern = navDestinationGroupNode->GetPattern<NavDestinationPattern>();
    EXPECT_FALSE(pattern == nullptr);
    pattern->SetName(name);
    return navDestinationGroupNode;
}

/**
 * @tc.name: NavigationStackPopTest001
 * @tc.desc: Branch: if (info->GetOnPop) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationResultTest, NavigationStackPopTest001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navDestinationA and navDestinationB, and sync stack
     */
    auto navDestinationA = CreateNavDestinationNode("pageA");
    EXPECT_FALSE(navDestinationA == nullptr);
    auto patternA = navDestinationA->GetPattern<NavDestinationPattern>();
    EXPECT_FALSE(patternA == nullptr);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    EXPECT_FALSE(context == nullptr);
    patternA->SetNavDestinationContext(context);
    auto pathInfo = AceType::MakeRefPtr<MockNavPathInfo>("pageA");
    EXPECT_FALSE(pathInfo == nullptr);
    pathInfo->onPop_ = []() {
        onPopIndex_ = 1;
    };
    context->SetNavPathInfo(pathInfo);
    auto navDestinationB = CreateNavDestinationNode("pageB");
    EXPECT_FALSE(navDestinationB == nullptr);

    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG, -1,
        []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    EXPECT_FALSE(navigationGroupNode == nullptr);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(navigationPattern == nullptr);
    navigationPattern->SetNavigationStack(AceType::MakeRefPtr<MockNavigationStack>());
    navigationPattern->navigationStack_->Add("pageA", navDestinationA);
    navigationPattern->navigationStack_->Add("pageB", navDestinationB);
    navigationGroupNode->MarkModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step2.pop page
     * @tc.expected: step2.trigger onPop callback
     */
    navigationPattern->navigationStack_->Pop();
    EXPECT_FALSE(onPopIndex_ == 1);
}
}