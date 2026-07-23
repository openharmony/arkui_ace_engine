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

#include <optional>

#include "gtest/gtest.h"
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"

#define protected public
#define private public
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/pipeline/base/element_register.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"

#include "core/components_ng/manager/navigation/navigation_manager.h"
#include "core/components_ng/manager/toolbar/toolbar_manager.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr int32_t TEST_DATA = 10;
constexpr int32_t STANDARD_INDEX = -1;
const std::string NAVIGATION_TITLE = "NavigationTestNg";
const std::string TEST_TAG = "test";
constexpr float DEFAULT_ROOT_WIDTH = 480.f;
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;

class PlatformVersionGuard {
public:
    explicit PlatformVersionGuard(const RefPtr<MockPipelineContext>& context) : context_(context)
    {
        if (context_) {
            oldVersion_ = context_->GetMinPlatformVersion();
        }
    }

    ~PlatformVersionGuard()
    {
        if (context_) {
            context_->SetMinPlatformVersion(oldVersion_);
        }
    }

private:
    RefPtr<MockPipelineContext> context_;
    int32_t oldVersion_ = 0;
};
} // namespace

class NavigationLayoutTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
};

void NavigationLayoutTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationLayoutTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationLayoutTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/*
 * @tc.name: NavigationPatternTest017
 * @tc.desc: Test DumpInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest017, TestSize.Level1)
{
    NavigationPattern navigationPattern;
    navigationPattern.navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern.navigationStack_, nullptr);
    navigationPattern.DumpInfo();
}

/**
 * @tc.name: NavigationPatternTest018
 * @tc.desc: Test DumpInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest018, TestSize.Level1)
{
    NavigationPattern navigationPattern;
    navigationPattern.navigationStack_ = nullptr;
    ASSERT_EQ(navigationPattern.navigationStack_, nullptr);
    navigationPattern.DumpInfo();
}

/**
 * @tc.name: NavigationPatternTest019
 * @tc.desc: Test NotifyDialogLifecycle function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest019, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    cacheNodes.emplace_back(std::make_pair("pageOne", nullptr));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    navigationPattern->NotifyDialogLifecycle(NavDestinationLifecycle::ON_SHOW, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest020
 * @tc.desc: Test NotifyDialogLifecycle function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest020, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationPattern, nullptr);
    bool isOnShow = true;
    navDestinationPattern->SetIsOnShow(isOnShow);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    navigationPattern->NotifyDialogLifecycle(NavDestinationLifecycle::ON_SHOW, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest021
 * @tc.desc: Test NotifyDialogLifecycle function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest021, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationPattern, nullptr);
    bool isOnShow = false;
    navDestinationPattern->SetIsOnShow(isOnShow);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    navigationPattern->NotifyDialogLifecycle(NavDestinationLifecycle::ON_SHOW, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest022
 * @tc.desc: Test NotifyDialogLifecycle function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest022, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationPattern, nullptr);
    bool isOnShow = false;
    navDestinationPattern->SetIsOnShow(isOnShow);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    navigationPattern->NotifyDialogLifecycle(NavDestinationLifecycle::ON_SHOW, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest023
 * @tc.desc: Test NotifyDialogLifecycle function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest023, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    cacheNodes.emplace_back(std::make_pair("pageOne", nullptr));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = false;
    navigationPattern->NotifyDialogLifecycle(NavDestinationLifecycle::ON_SHOW, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest024
 * @tc.desc: Test NotifyDialogLifecycle function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest024, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationPattern, nullptr);
    bool isOnShow = false;
    navDestinationPattern->SetIsOnShow(isOnShow);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    navigationPattern->NotifyDialogLifecycle(NavDestinationLifecycle::ON_HIDE, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest025
 * @tc.desc: Test NotifyDialogLifecycle function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest025, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationPattern, nullptr);
    bool isOnShow = true;
    navDestinationPattern->SetIsOnShow(isOnShow);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    navigationPattern->NotifyDialogLifecycle(NavDestinationLifecycle::ON_HIDE, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest026
 * @tc.desc: Test NotifyDialogLifecycle function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest026, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationPattern, nullptr);
    bool isOnShow = true;
    navDestinationPattern->SetIsOnShow(isOnShow);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    navigationPattern->NotifyDialogLifecycle(NavDestinationLifecycle::ON_HIDE, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest027
 * @tc.desc: Test TriggerCustomAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest027, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationPattern navigationPattern;
    bool isPopPage = true;
    EXPECT_EQ(navigationPattern.TriggerCustomAnimation(nullptr, nullptr, isPopPage), false);
}

/**
 * @tc.name: NavigationPatternTest028
 * @tc.desc: Test OnCustomAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest028, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    bool isPopPage = false;
    navigationPattern->OnCustomAnimationFinish(nullptr, nullptr, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest029
 * @tc.desc: Test OnCustomAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest029, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    PageTransitionType type = PageTransitionType::NONE;
    preTopNavDestination->SetTransitionType(type);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = true;
    navigationPattern->OnCustomAnimationFinish(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest030
 * @tc.desc: Test OnCustomAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest030, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto preDestinationPattern = preTopNavDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(preDestinationPattern, nullptr);
    preDestinationPattern->shallowBuilder_ = nullptr;
    PageTransitionType type = PageTransitionType::EXIT_POP;
    preTopNavDestination->SetTransitionType(type);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = true;
    navigationPattern->OnCustomAnimationFinish(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest031
 * @tc.desc: Test OnCustomAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest031, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto preDestinationPattern = preTopNavDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(preDestinationPattern, nullptr);
    preDestinationPattern->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(
        []() { return FrameNode::CreateFrameNode("temp", 234, AceType::MakeRefPtr<ButtonPattern>()); });
    PageTransitionType type = PageTransitionType::EXIT_POP;
    preTopNavDestination->SetTransitionType(type);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = true;
    navigationPattern->OnCustomAnimationFinish(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest032
 * @tc.desc: Test OnCustomAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest032, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    PageTransitionType type = PageTransitionType::EXIT_POP;
    preTopNavDestination->SetTransitionType(type);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = false;
    navigationPattern->OnCustomAnimationFinish(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest033
 * @tc.desc: Test OnCustomAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest033, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    PageTransitionType type = PageTransitionType::EXIT_PUSH;
    preTopNavDestination->SetTransitionType(type);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = false;
    navigationPattern->OnCustomAnimationFinish(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest034
 * @tc.desc: Test UpdatePreNavDesZIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest034, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = nullptr;
    auto newTopNavDestination = nullptr;
    navigationPattern->UpdatePreNavDesZIndex(preTopNavDestination, newTopNavDestination);
}

/**
 * @tc.name: NavigationPatternTest036
 * @tc.desc: Test SyncWithJsStackIfNeeded function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest036, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->needSyncWithJsStack_ = false;
    navigationPattern->SyncWithJsStackIfNeeded();
}

/**
 * @tc.name: NavigationPatternTest037
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest037, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = false;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest038
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest038, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);

    auto frameNode_test = AceType::MakeRefPtr<FrameNode>(V2::ROW_COMPONENT_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto parent = AceType::WeakClaim(AceType::RawPtr(frameNode_test));
    preTopNavDestination->SetParent(parent);
    auto navigationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 12,
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    preTopNavDestination->SetContentNode(navigationContentNode);

    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = true;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest039
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest039, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);

    auto frameNode_test = AceType::MakeRefPtr<FrameNode>(V2::ROW_COMPONENT_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto parent = AceType::WeakClaim(AceType::RawPtr(frameNode_test));
    preTopNavDestination->SetParent(parent);
    auto navigationContentNode = nullptr;
    preTopNavDestination->SetContentNode(navigationContentNode);

    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = true;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest040
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest040, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    auto preTopNavDestination = nullptr;
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    NavDestinationMode mode = NavDestinationMode::STANDARD;
    newTopNavDestination->SetNavDestinationMode(mode);
    bool isPopPage = false;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest041
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest041, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    auto preTopNavDestination = nullptr;
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    NavDestinationMode mode = NavDestinationMode::DIALOG;
    newTopNavDestination->SetNavDestinationMode(mode);
    bool isPopPage = false;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest042
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest042, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto frameNode_test = AceType::MakeRefPtr<FrameNode>(V2::ROW_COMPONENT_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto parent = AceType::WeakClaim(AceType::RawPtr(frameNode_test));
    preTopNavDestination->SetParent(parent);
    auto navigationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 12,
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    preTopNavDestination->SetContentNode(navigationContentNode);
    auto newTopNavDestination = nullptr;
    bool isPopPage = false;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest043
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest043, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto frameNode_test = AceType::MakeRefPtr<FrameNode>(V2::ROW_COMPONENT_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto parent = AceType::WeakClaim(AceType::RawPtr(frameNode_test));
    preTopNavDestination->SetParent(parent);
    preTopNavDestination->SetContentNode(nullptr);
    auto newTopNavDestination = nullptr;
    bool isPopPage = false;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest044
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest044, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = nullptr;
    auto newTopNavDestination = nullptr;
    bool isPopPage = false;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest045
 * @tc.desc: Test FireNavDestinationStateChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest045, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    navDestinationPattern->SetIsOnShow(false);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    EXPECT_EQ(navigationPattern->FireNavDestinationStateChange(NavDestinationLifecycle::ON_HIDE,
        NavDestVisibilityChangeReason::TRANSITION), STANDARD_INDEX);
}

/**
 * @tc.name: NavigationPatternTest046
 * @tc.desc: Test FireNavDestinationStateChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest046, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = nullptr;
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    EXPECT_EQ(navigationPattern->FireNavDestinationStateChange(NavDestinationLifecycle::ON_SHOW,
        NavDestVisibilityChangeReason::TRANSITION), STANDARD_INDEX);
}

/**
 * @tc.name: NavigationPatternTest047
 * @tc.desc: Test FireNavDestinationStateChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest047, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    navDestinationPattern->SetIsOnShow(false);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    EXPECT_EQ(navigationPattern->FireNavDestinationStateChange(NavDestinationLifecycle::ON_SHOW,
        NavDestVisibilityChangeReason::TRANSITION), STANDARD_INDEX);
}

/**
 * @tc.name: NavigationPatternTest048
 * @tc.desc: Test FireNavDestinationStateChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest048, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    navDestinationPattern->SetIsOnShow(true);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    EXPECT_EQ(navigationPattern->FireNavDestinationStateChange(NavDestinationLifecycle::ON_HIDE,
        NavDestVisibilityChangeReason::TRANSITION), STANDARD_INDEX);
}

/**
 * @tc.name: NavigationPatternTest049
 * @tc.desc: Test TransitionWithAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest049, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = nullptr;
    auto newTopNavDestination = nullptr;
    bool isPopPage = false;
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest050
 * @tc.desc: Test TransitionWithAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest050, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    navigationPattern->isCustomAnimation_ = true;
    bool isPopPage = false;
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest051
 * @tc.desc: Test TransitionWithAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest051, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = nullptr;
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    navigationPattern->isCustomAnimation_ = true;
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    bool isPopPage = false;
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest052
 * @tc.desc: Test TransitionWithAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest052, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto newTopNavDestination = nullptr;
    navigationPattern->isCustomAnimation_ = true;
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    bool isPopPage = false;
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest053
 * @tc.desc: Test TransitionWithAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest053, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto newTopNavDestination = nullptr;
    navigationPattern->isCustomAnimation_ = true;
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    bool isPopPage = false;
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest054
 * @tc.desc: Test OnHover function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest054, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->isInDividerDrag_ = true;
    bool isHover = false;
    navigationPattern->OnHover(isHover);
}

/**
 * @tc.name: NavigationPatternTest055
 * @tc.desc: Test OnHover function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest055, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->isInDividerDrag_ = false;
    navigationPattern->userSetNavBarWidthFlag_ = true;
    navigationPattern->userSetNavBarRangeFlag_ = true;
    bool isHover = false;
    navigationPattern->OnHover(isHover);
}

/**
 * @tc.name: NavigationPatternTest056
 * @tc.desc: Test OnHover function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest056, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->isInDividerDrag_ = false;
    navigationPattern->userSetNavBarWidthFlag_ = false;
    navigationPattern->userSetNavBarRangeFlag_ = false;
    bool isHover = false;
    navigationPattern->OnHover(isHover);
}

/**
 * @tc.name: NavigationPatternTest057
 * @tc.desc: Test AddDividerHotZoneRect function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest057, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->realDividerWidth_ = 0.0f;
    navigationPattern->AddDividerHotZoneRect();
}

/**
 * @tc.name: NavigationPatternTest058
 * @tc.desc: Branch: bool isVisible = forceSplitSuccess_ && navBarIsHome_; => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationPatternTest058, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationProperty = navigation->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationProperty, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navBar = AceType::DynamicCast<NavBarNode>(navigation->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarProperty = navBar->GetLayoutProperty();
    ASSERT_NE(navBarProperty, nullptr);
    auto newTop = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTop, nullptr);

    navigationPattern->forceSplitSuccess_ = true;
    navigationPattern->navBarIsHome_ = true;
    newTop->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navigationProperty->UpdateUsrNavigationMode(NavigationMode::STACK);
    navBarProperty->UpdateVisibility(VisibleType::INVISIBLE);
    navigationPattern->TransitionWithOutAnimation(nullptr, newTop, false, false);
    EXPECT_EQ(navBarProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: HandleBack001
 * @tc.desc: Test HandleBack and match all conditions of "!isOverride && !isLastChild".
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, HandleBack001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    bool isLastChild = true, isOverride = true;
    EXPECT_TRUE(isLastChild && isOverride);
    navigationNode->HandleBack(nullptr, isLastChild, isOverride);

    isOverride = false;
    EXPECT_TRUE(isLastChild && !isOverride);
    navigationNode->HandleBack(nullptr, isLastChild, isOverride);

    isLastChild = false;
    EXPECT_TRUE(!isLastChild && !isOverride);
    navigationNode->HandleBack(nullptr, isLastChild, isOverride);
}

/**
 * @tc.name: HandleBack002
 * @tc.desc: Test HandleBack and match all conditions of "isLastChild &&...".
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, HandleBack002, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    bool isLastChild = false, isOverride = true;
    EXPECT_TRUE(!isLastChild && isOverride);
    navigationNode->HandleBack(navDestinationNode, isLastChild, isOverride);

    isLastChild = true;
    EXPECT_TRUE(isLastChild && isOverride);
    EXPECT_NE(navigationPattern->GetNavigationMode(), NavigationMode::SPLIT);
    EXPECT_NE(navigationPattern->GetNavigationMode(), NavigationMode::STACK);
    navigationNode->HandleBack(navDestinationNode, isLastChild, isOverride);

    navigationPattern->navigationMode_ = NavigationMode::STACK;
    EXPECT_EQ(navigationPattern->GetNavigationMode(), NavigationMode::STACK);
    auto layoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    EXPECT_FALSE(layoutProperty->GetHideNavBar().value_or(false));
    navigationNode->HandleBack(navDestinationNode, isLastChild, isOverride);

    layoutProperty->propHideNavBar_ = true;
    EXPECT_TRUE(layoutProperty->GetHideNavBar().value_or(false));
    navigationNode->HandleBack(navDestinationNode, isLastChild, isOverride);

    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    EXPECT_EQ(navigationPattern->GetNavigationMode(), NavigationMode::SPLIT);
    navigationNode->HandleBack(navDestinationNode, isLastChild, isOverride);
}

/**
 * @tc.name: TransitionWithPush001
 * @tc.desc: Test TransitionWithPush and match the logic as follows:
 *               isNavBar is false
 *               needSetInvisible is false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, TransitionWithPush001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 201, AceType::MakeRefPtr<TitleBarPattern>());

    bool isNavBar = false;
    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 301, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    // Make needSetInvisible false
    auto curNode = preNode;
    ASSERT_NE(curNode, nullptr);
    // Make preTitleNode and curTitleNode not NULL
    preNode->titleBarNode_ = titleBarNode;

    // Make sure isNavBar is false
    EXPECT_FALSE(isNavBar);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(preNode->GetTitleBarNode()), nullptr);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(curNode->GetTitleBarNode()), nullptr);
    navigationNode->TransitionWithPush(preNode, curNode, isNavBar);
}

/**
 * @tc.name: TransitionWithPush002
 * @tc.desc: Test TransitionWithPush and match the logic as follows:
 *               isNavBar is true
 *               needSetInvisible is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, TransitionWithPush002, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 201, AceType::MakeRefPtr<TitleBarPattern>());

    bool isNavBar = true;
    // Make needSetInvisible true
    auto preNode = NavBarNode::GetOrCreateNavBarNode(
        "navBarNode", 301, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto curNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 401, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    // Make preTitleNode and curTitleNode not NULL
    preNode->titleBarNode_ = titleBarNode;
    curNode->titleBarNode_ = titleBarNode;

    // Make sure isNavBar is true
    EXPECT_TRUE(isNavBar);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(preNode->GetTitleBarNode()), nullptr);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(curNode->GetTitleBarNode()), nullptr);
    navigationNode->TransitionWithPush(preNode, curNode, isNavBar);
}

/**
 * @tc.name: TransitionWithPush003
 * @tc.desc: Test TransitionWithPush and match the logic as follows:
 *               isNavBar is false
 *               needSetInvisible is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, TransitionWithPush003, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 201, AceType::MakeRefPtr<TitleBarPattern>());

    bool isNavBar = false;
    // Make needSetInvisible true
    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 301, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto curNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 302, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    // Make preTitleNode and curTitleNode not NULL
    preNode->titleBarNode_ = titleBarNode;
    curNode->titleBarNode_ = titleBarNode;

    // Make sure isNavBar is false
    EXPECT_FALSE(isNavBar);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(preNode->GetTitleBarNode()), nullptr);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(curNode->GetTitleBarNode()), nullptr);
    navigationNode->TransitionWithPush(preNode, curNode, isNavBar);
}

/**
 * @tc.name: TransitionWithReplace001
 * @tc.desc: Test TransitionWithReplace and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, TransitionWithReplace001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto preNode1 = NavBarNode::GetOrCreateNavBarNode(
        "navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto curNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    bool isNavBar = true;
    EXPECT_NE(preNode1, nullptr);
    EXPECT_NE(curNode, nullptr);
    // Make sure isNavBar is true
    EXPECT_TRUE(isNavBar);
    navigationNode->TransitionWithReplace(preNode1, curNode, isNavBar);

    isNavBar = false;
    // Make sure isNavBar is false
    EXPECT_FALSE(isNavBar);
    // Make sure navDestination is false
    EXPECT_EQ(AceType::DynamicCast<NavDestinationGroupNode>(preNode1), nullptr);
    navigationNode->TransitionWithReplace(preNode1, curNode, isNavBar);

    auto preNode2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 4, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    // Make sure navDestination is true
    EXPECT_NE(AceType::DynamicCast<NavDestinationGroupNode>(preNode2), nullptr);
    navigationNode->TransitionWithReplace(preNode2, curNode, isNavBar);
}

/**
 * @tc.name: CheckContentNeedMeasure
 * @tc.desc:
 *           test navigationpattern::CheckContentNeedMeasure
 *           if navigation height is "auto"
 *           dirtynodes is not empty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, CheckContentNeedMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1 create navigation and setHeight
     * @tc.expected: success create navigation
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationLayoutProperty = navigation->GetLayoutProperty<NavigationLayoutProperty>();
    EXPECT_NE(navigationLayoutProperty, nullptr);
    navigationLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_NORMAL);
    CalcSize idealSize = { CalcLength("100%"), CalcLength("auto") };
    MeasureProperty layoutConstraint = { .selfIdealSize = idealSize };
    navigationLayoutProperty->UpdateCalcLayoutProperty(layoutConstraint);
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    /**
     * @tc.steps: step2 call CheckContentNeedMeasure
     * @tc.expected: dirty flag is PROPERTY_UPDATE_MEASURE
     */
    auto navigationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 12,
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(navigationContentNode, nullptr);
    auto layoutProperty = navigationContentNode->GetLayoutProperty<LayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->CleanDirty();
    navigation->SetContentNode(navigationContentNode);
    navigationPattern->CheckContentNeedMeasure(navigation);
    auto layoutFlag = layoutProperty->GetPropertyChangeFlag();
    ASSERT_EQ(layoutFlag, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: CheckContentNeedMeasure
 * @tc.desc:
 *           test navigationpattern::CheckContentNeedMeasure
 *           if navigation height is "auto"
 *           dirtynodes is not empty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, CheckContentNeedMeasure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1 create navigation and setHeight "1111"
     * @tc.expected: success create navigation
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationLayoutProperty = navigation->GetLayoutProperty<NavigationLayoutProperty>();
    EXPECT_NE(navigationLayoutProperty, nullptr);
    CalcSize idealSize = { CalcLength("100%"), CalcLength("1111") };
    MeasureProperty layoutConstraint = { .selfIdealSize = idealSize };
    navigationLayoutProperty->UpdateCalcLayoutProperty(layoutConstraint);
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    /**
     * @tc.steps: step2 call CheckContentNeedMeasure
     * @tc.expected: dirty flag is not PROPERTY_UPDATE_MEASURE
     */
    auto navigationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 22,
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(navigationContentNode, nullptr);
    auto layoutProperty = navigationContentNode->GetLayoutProperty<LayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->CleanDirty();
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), PROPERTY_UPDATE_NORMAL);
    navigation->SetContentNode(navigationContentNode);
    navigationPattern->CheckContentNeedMeasure(navigation);
    auto layoutFlag = layoutProperty->GetPropertyChangeFlag();
    ASSERT_NE(layoutFlag, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: DealNavigationExit001
 * @tc.desc: Test DealNavigationExit and make the logic as follows:
 *               GetEventHub return false
 *               isNavBar is false
 *               shallowBuilder is false
 *               GetContentNode is false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, DealNavigationExit001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 301, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preNode->eventHub_ = nullptr;
    bool isNavBar = false;

    EXPECT_FALSE(isNavBar);
    // Make sure navDestination is true
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
    ASSERT_NE(navDestinationNode, nullptr);
    EXPECT_EQ(navDestinationNode->GetPattern<NavDestinationPattern>()->GetShallowBuilder(), nullptr);
    EXPECT_EQ(navDestinationNode->GetContentNode(), nullptr);
    navigationNode->DealNavigationExit(preNode, isNavBar, true);
    preNode->eventHub_ = preNode->GetPattern<NavDestinationPattern>()->CreateEventHub();
}

/**
 * @tc.name: DealNavigationExit002
 * @tc.desc: Test DealNavigationExit and make the logic as follows:
 *               GetEventHub return true
 *               isNavBar is true
 *               isAnimated is false
 *               shallowBuilder is true
 *               GetContentNode is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, DealNavigationExit002, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto prePattern = preNode->GetPattern<NavDestinationPattern>();
    prePattern->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(
        []() { return FrameNode::CreateFrameNode("shallowBuilder", 301, AceType::MakeRefPtr<ButtonPattern>()); });
    preNode->contentNode_ = FrameNode::CreateFrameNode("button", 401, AceType::MakeRefPtr<ButtonPattern>());
    bool isNavBar = true, isAnimated = false;

    EXPECT_NE(preNode->GetEventHub<EventHub>(), nullptr);
    EXPECT_TRUE(isNavBar && !isAnimated);
    // Make sure navDestination is true
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
    ASSERT_NE(navDestinationNode, nullptr);
    EXPECT_NE(navDestinationNode->GetPattern<NavDestinationPattern>()->GetShallowBuilder(), nullptr);
    EXPECT_NE(navDestinationNode->GetContentNode(), nullptr);
    navigationNode->DealNavigationExit(preNode, isNavBar, isAnimated);
}

/**
 * @tc.name: UpdateNavigationNode
 * @tc.desc: branch if (usrnavigationMode == NavigationMode::AUTO)
 *           Condition enableModeChangeAnimation false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, UpdateNavigationMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Navigation
     * @tc.expected: create success
     */
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 1001, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
  
    /**
     * @tc.steps: step2. enableAnimation is false, isFirstTimeLayout:false, isNotOnSwitchAnimation:false
     * @tc.expected: navigationModeChange is true
     */
    navigationPattern->SetNavigationModeChange(false);
    navigationLayoutProperty->UpdateEnableModeChangeAnimation(false);
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationNode->SetDoingModeSwitchAnimationFlag(false);
    
    /**
     * @tc.steps: step3. call updateNavitionMode
     * @tc.expected: navigationPattern->GetNavigationModeChange() value is true
     */
    auto navigationLayoutAlgorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    ASSERT_NE(navigationLayoutAlgorithm, nullptr);
    auto frameSize = SizeF(2560, 2340);
    navigationLayoutAlgorithm->UpdateNavigationMode(navigationLayoutProperty, frameSize, navigationNode);
    
    bool value = navigationPattern->GetNavigationModeChange();
    ASSERT_EQ(value, true);
}

/**
 * @tc.name: UpdateNavigationNode
 * @tc.desc: branch if (usrnavigationMode == NavigationMode::AUTO)
 *           Condition enableModeChangeAnimation true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, UpdateNavigationMode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Navigation
     * @tc.expected: create success
     */
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 1002, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
  
    /**
     * @tc.steps: step2. enableAnimation is true, isFirstTimeLayout:false, isNotOnSwitchAnimation:false
     * @tc.expected: navigationModeChange is false
     */
    navigationPattern->SetNavigationModeChange(false);
    navigationLayoutProperty->UpdateEnableModeChangeAnimation(true);
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationNode->SetDoingModeSwitchAnimationFlag(false);
    
    /**
     * @tc.steps: step3. call updateNavitionMode
     * @tc.expected: navigationPattern->GetNavigationModeChange() value is false
     */
    auto navigationLayoutAlgorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    ASSERT_NE(navigationLayoutAlgorithm, nullptr);
    auto frameSize = SizeF(2560, 2340);
    navigationLayoutAlgorithm->UpdateNavigationMode(navigationLayoutProperty, frameSize, navigationNode);
    
    bool value = navigationPattern->GetNavigationModeChange();
    ASSERT_EQ(value, false);
}

/**
 * @tc.name: UpdateNavigationMode003
 * @tc.desc: Test AUTO_WITH_ASPECT_RATIO mode, height / width > 1.2 should use STACK.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, UpdateNavigationMode003, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 1003, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    navigationLayoutProperty->UpdateEnableModeChangeAnimation(false);
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO_WITH_ASPECT_RATIO);
    navigationPattern->SetNavigationMode(NavigationMode::SPLIT);

    auto navigationLayoutAlgorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    ASSERT_NE(navigationLayoutAlgorithm, nullptr);
    auto frameSize = SizeF(1000.0f, 1300.0f);
    navigationLayoutAlgorithm->UpdateNavigationMode(navigationLayoutProperty, frameSize, navigationNode);
    EXPECT_EQ(navigationPattern->GetNavigationMode(), NavigationMode::STACK);
}

/**
 * @tc.name: UpdateNavigationMode004
 * @tc.desc: Test AUTO_WITH_ASPECT_RATIO mode, height / width <= 1.2 should use SPLIT.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, UpdateNavigationMode004, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 1004, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    navigationLayoutProperty->UpdateEnableModeChangeAnimation(false);
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO_WITH_ASPECT_RATIO);
    navigationPattern->SetNavigationMode(NavigationMode::STACK);

    auto navigationLayoutAlgorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    ASSERT_NE(navigationLayoutAlgorithm, nullptr);
    auto frameSize = SizeF(1000.0f, 1200.0f);
    navigationLayoutAlgorithm->UpdateNavigationMode(navigationLayoutProperty, frameSize, navigationNode);
    EXPECT_EQ(navigationPattern->GetNavigationMode(), NavigationMode::SPLIT);
}

/**
 * @tc.name: DealNavigationExit003
 * @tc.desc: Test DealNavigationExit and make the logic as follows:
 *               GetEventHub return true
 *               isNavBar is true
 *               isAnimated is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, DealNavigationExit003, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    bool isNavBar = true, isAnimated = true;

    EXPECT_NE(preNode->GetEventHub<EventHub>(), nullptr);
    EXPECT_TRUE(isNavBar && isAnimated);
    navigationNode->DealNavigationExit(preNode, isNavBar, isAnimated);
}

/**
 * @tc.name: NavigationAvoidKeyboard
 * @tc.desc: Test the value of avoidKeyboardOffset
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationAvoidKeyboardTest, TestSize.Level1)
{
    /**
     *  step 0. add method GetSafeAreaManager() in MockPipelineContext
     */
    auto safeAreaManager = MockPipelineContext::GetCurrent()->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    auto textFiledManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFiledManager);
    ASSERT_NE(textFiledManager, nullptr);

    /**
     *  step 1. create navBar node and check the value of avoidKeyboardOffset
     */
    float offOne = 12.34;
    safeAreaManager->UpdateKeyboardOffset(offOne);
    auto navBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    RefPtr<NavBarNode> navBarNode = NavBarNode::GetOrCreateNavBarNode(
        V2::NAVBAR_ETS_TAG, navBarNodeId, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    textFiledManager->weakNavNode_ = navBarNode;
        
    textFiledManager->AvoidKeyBoardInNavigation();
    
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarPattern, nullptr);
    float offsetOne = navBarPattern->GetAvoidKeyboardOffset();
    EXPECT_EQ(offsetOne, offOne);
    
    /**
     *  step 2. create navDestination node and check the value of avoidKeyboardOffset
     */
    float offTwo = 56.78;
    safeAreaManager->UpdateKeyboardOffset(offTwo);
    auto navDestinationNodeId = ElementRegister::GetInstance()->MakeUniqueId();

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        navDestinationNodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();

    textFiledManager->weakNavNode_ = navDestination;
    textFiledManager->AvoidKeyBoardInNavigation();
    ASSERT_NE(navDestinationPattern, nullptr);
    float offsetTwo = navDestinationPattern->GetAvoidKeyboardOffset();
    EXPECT_EQ(offsetTwo, offTwo);
}

/**
 * @tc.name: NavigationSize001
 * @tc.desc: Test GetNavigationSize & SetNavigationSize of NavigationPattern.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationSize001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. Create NavigationNode & NavigationPattern.
     * @tc.expected: step1. NavigationPattern has default size.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto size = navigationPattern->GetNavigationSize();
    ASSERT_EQ(size, SizeF());

    /**
     * @tc.steps: step2. Set Navigation size.
     * @tc.expected: step2. Success to set navigation size.
     */
    const SizeF TEST_SIZE = SizeF(200.0f, 300.0f);
    navigationPattern->SetNavigationSize(TEST_SIZE);
    size = navigationPattern->GetNavigationSize();
    ASSERT_EQ(size, TEST_SIZE);

    /**
     * @tc.steps: step3. Measure NavigationNode.
     * @tc.expected: step3. NavigationSize of NavigationPattern will be update after measure.
     */
    auto layoutWrapper = navigation->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    const SizeF ROOT_SIZE = SizeF(DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT);
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    size = navigationPattern->GetNavigationSize();
    ASSERT_EQ(size, ROOT_SIZE);
}

/**
 * @tc.name: NeedForceMeasure001
 * @tc.desc: Test ForceMeasure logic of NavDestination when NavigationContent measure.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NeedForceMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NavigationContentNode & NavDestinationNode.
     * @tc.expected: step1. NavDestination's needForceMeasure flag has default value: false.
     */
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 1,
        []() { return AceType::MakeRefPtr<NavigationContentPattern>(); });
    ASSERT_NE(contentNode, nullptr);
    auto navDestNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 2, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestNode, nullptr);
    ASSERT_FALSE(navDestNode->NeedForceMeasure());

    /**
     * @tc.steps: step2. Set NavDestination need force measure.
     * @tc.expected: step2. Flag will be update.
     */
    navDestNode->SetNeedForceMeasure(true);
    ASSERT_TRUE(navDestNode->NeedForceMeasure());

    /**
     * @tc.steps: step3. Add NavDestination to NavigationContentNode and measure NavigationContentNode.
     * @tc.expected: step3. ForceMeasure flag of NavDestiantion will be reset to false.
     */
    auto destLayoutProperty = navDestNode->GetLayoutProperty();
    ASSERT_NE(destLayoutProperty, nullptr);
    destLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    contentNode->AddChild(navDestNode);
    auto layoutWrapper = contentNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    ASSERT_FALSE(navDestNode->NeedForceMeasure());
}

/**
 * @tc.name: ReCalcNavigationSize001
 * @tc.desc: Test navigation constraintSize no branch
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, ReCalcNavigationSize001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. Create NavigationNode & NavigationPattern.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto layoutProperty = navigation->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. Update CalcSize
     */
    auto size = CalcSize(CalcLength(500), CalcLength(500));
    layoutProperty->UpdateCalcMaxSize(size);
    auto layoutWrapper = navigation->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(600, 600));

    auto navigationLayoutAlgorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    ASSERT_NE(navigationLayoutAlgorithm, nullptr);
    
    SizeF frameSize = SizeF(600, 600);
    navigationLayoutAlgorithm->ReCalcNavigationSize(AceType::RawPtr(layoutWrapper), frameSize);
    
    SizeF targetSize = SizeF(500, 500);
    EXPECT_EQ(geometryNode->GetFrameSize(), targetSize);
}

/**
 * @tc.name: NavigationLayoutRange001
 * @tc.desc: Test NavigationLayoutAlgorithm::RangeCalculation and GetRange.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationLayoutRange001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    /**
     * @tc.steps: Create navigation through model pipeline.
     * @tc.expected: Navigation node has complete pattern/property/context chain for range calculation.
     */
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto property = navigation->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    LayoutConstraintF constraint;
    constraint.parentIdealSize = OptionalSizeF(1000.0f, 800.0f);
    constraint.percentReference = SizeF(1000.0f, 800.0f);
    property->layoutConstraint_ = constraint;
    property->propMinNavBarWidth_ = 220.0_vp;
    property->propMaxNavBarWidth_ = 420.0_vp;
    property->propMinContentWidth_ = 260.0_vp;

    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    ASSERT_NE(algorithm, nullptr);
    algorithm->RangeCalculation(navigation, property);
    EXPECT_TRUE(algorithm->userSetNavBarRangeFlag_);
    EXPECT_TRUE(algorithm->userSetMinContentFlag_);

    // reset local cache then load from pattern to verify persistence path.
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->userSetMinContentFlag_ = false;
    algorithm->GetRange(navigation);
    /**
     * @tc.steps: Reset algorithm local flags, then reload via GetRange().
     * @tc.expected: Range/user flags persisted in pattern are restored to algorithm.
     */
    EXPECT_TRUE(algorithm->userSetNavBarRangeFlag_);
    EXPECT_TRUE(algorithm->userSetMinContentFlag_);
}

/**
 * @tc.name: NavigationLayoutRange002
 * @tc.desc: Test NavigationLayoutAlgorithm::CalculateNavigationWidth in different platform versions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, NavigationLayoutRange002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    PlatformVersionGuard versionGuard(context);

    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto property = navigation->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    LayoutConstraintF constraint;
    constraint.parentIdealSize = OptionalSizeF(1000.0f, 800.0f);
    constraint.percentReference = SizeF(1000.0f, 800.0f);
    property->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    ASSERT_NE(algorithm, nullptr);
    algorithm->minNavBarWidthValue_ = 200.0_vp;
    algorithm->minContentWidthValue_ = 300.0_vp;

    /**
     * @tc.steps: Switch platform version to hit both CalculateNavigationWidth branches.
     * @tc.expected: >=10 uses minNavBar+minContent branch, <10 uses fixed WINDOW_WIDTH branch.
     */
    context->SetMinPlatformVersion(10);
    auto widthForV10 = algorithm->CalculateNavigationWidth(navigation);
    context->SetMinPlatformVersion(9);
    auto widthForV9 = algorithm->CalculateNavigationWidth(navigation);

    /**
     * @tc.steps: Compare widths from both platform branches.
     * @tc.expected: Both values are valid and different due to different branch strategy.
     */
    EXPECT_GT(widthForV10, 0.0f);
    EXPECT_GT(widthForV9, 0.0f);
    EXPECT_NE(widthForV10, widthForV9);
}

namespace {
RefPtr<NavigationGroupNode> CreateNavLayoutTestNode()
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    if (navigationNode) {
        auto pattern = navigationNode->GetPattern<NavigationPattern>();
        if (pattern) {
            pattern->SetNavigationStack(AceType::MakeRefPtr<MockNavigationStack>());
        }
        navigationNode->contentNode_ = FrameNode::CreateFrameNode(
            "content", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    }
    return navigationNode;
}

RefPtr<FrameNode> CreateLayoutTestChildNode(const std::string& tag)
{
    return FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
}

void SetupLayoutConstraint(const RefPtr<NavigationLayoutProperty>& layoutProperty)
{
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
}
} // namespace

/**
 * @tc.name: MeasurePrimaryContentNode001
 * @tc.desc: Test MeasurePrimaryContentNode with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasurePrimaryContentNode001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF primaryNodeSize(1000.0f, 1000.0f);
    algorithm->MeasurePrimaryContentNode(layoutWrapper.GetRawPtr(), nullptr, layoutProperty, primaryNodeSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasurePrimaryContentNode002
 * @tc.desc: Test MeasurePrimaryContentNode with null primaryContentNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasurePrimaryContentNode002, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF primaryNodeSize(1000.0f, 1000.0f);
    algorithm->MeasurePrimaryContentNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, primaryNodeSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasurePrimaryContentNode003
 * @tc.desc: Test MeasurePrimaryContentNode with invisible primaryContentNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasurePrimaryContentNode003, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto primaryContentNode = CreateLayoutTestChildNode("primaryContent");
    primaryContentNode->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF primaryNodeSize(1000.0f, 1000.0f);
    algorithm->MeasurePrimaryContentNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, primaryNodeSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasurePrimaryContentNode004
 * @tc.desc: Test MeasurePrimaryContentNode with null nodeWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasurePrimaryContentNode004, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto primaryContentNode = CreateLayoutTestChildNode("primaryContent");
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SetupLayoutConstraint(layoutProperty);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF primaryNodeSize(1000.0f, 1000.0f);
    algorithm->MeasurePrimaryContentNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, primaryNodeSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasurePrimaryContentNode005
 * @tc.desc: Test MeasurePrimaryContentNode with auto height
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasurePrimaryContentNode005, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto primaryContentNode = CreateLayoutTestChildNode("primaryContent");
    hostNode->AddChild(primaryContentNode);
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->selfIdealSize = CalcSize(CalcLength(1000.0f), CalcLength("auto"));
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = primaryContentNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(primaryContentNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF primaryNodeSize(500.0f, 800.0f);
    algorithm->MeasurePrimaryContentNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, primaryNodeSize);
    EXPECT_GT(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasurePrimaryContentNode006
 * @tc.desc: Test MeasurePrimaryContentNode with fixed height
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasurePrimaryContentNode006, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto primaryContentNode = CreateLayoutTestChildNode("primaryContent");
    hostNode->AddChild(primaryContentNode);
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SetupLayoutConstraint(layoutProperty);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = primaryContentNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(primaryContentNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF primaryNodeSize(500.0f, 800.0f);
    algorithm->MeasurePrimaryContentNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, primaryNodeSize);
    EXPECT_GT(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasureForceSplitPlaceHolderNode001
 * @tc.desc: Test MeasureForceSplitPlaceHolderNode with null phNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureForceSplitPlaceHolderNode001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureForceSplitPlaceHolderNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasureForceSplitPlaceHolderNode002
 * @tc.desc: Test MeasureForceSplitPlaceHolderNode with null phProperty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureForceSplitPlaceHolderNode002, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto phNode = FrameNode::CreateFrameNode(
        "forceSplitPH", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    phNode->layoutProperty_ = nullptr;
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureForceSplitPlaceHolderNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasureForceSplitPlaceHolderNode003
 * @tc.desc: Test MeasureForceSplitPlaceHolderNode with invisible node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureForceSplitPlaceHolderNode003, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto phNode = CreateLayoutTestChildNode("forceSplitPH");
    phNode->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->AddChild(phNode);
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SetupLayoutConstraint(layoutProperty);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = phNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(phNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureForceSplitPlaceHolderNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasureForceSplitPlaceHolderNode004
 * @tc.desc: Test MeasureForceSplitPlaceHolderNode with null phWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureForceSplitPlaceHolderNode004, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto phNode = CreateLayoutTestChildNode("forceSplitPH");
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SetupLayoutConstraint(layoutProperty);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureForceSplitPlaceHolderNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasureForceSplitPlaceHolderNode005
 * @tc.desc: Test MeasureForceSplitPlaceHolderNode visible with fixed height
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureForceSplitPlaceHolderNode005, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto phNode = CreateLayoutTestChildNode("forceSplitPH");
    hostNode->AddChild(phNode);
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SetupLayoutConstraint(layoutProperty);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = phNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(phNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureForceSplitPlaceHolderNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasureForceSplitPlaceHolderNode006
 * @tc.desc: Test MeasureForceSplitPlaceHolderNode visible with auto height
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureForceSplitPlaceHolderNode006, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto phNode = CreateLayoutTestChildNode("forceSplitPH");
    hostNode->AddChild(phNode);
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->selfIdealSize = CalcSize(CalcLength(1000.0f), CalcLength("auto"));
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = phNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(phNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureForceSplitPlaceHolderNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasureRelatedPageNode001
 * @tc.desc: Test MeasureRelatedPageNode with null node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureRelatedPageNode001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasureRelatedPageNode002
 * @tc.desc: Test MeasureRelatedPageNode with invisible node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureRelatedPageNode002, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto relatedNode = CreateLayoutTestChildNode("relatedPage");
    relatedNode->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasureRelatedPageNode003
 * @tc.desc: Test MeasureRelatedPageNode with null wrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureRelatedPageNode003, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto relatedNode = CreateLayoutTestChildNode("relatedPage");
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SetupLayoutConstraint(layoutProperty);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasureRelatedPageNode004
 * @tc.desc: Test MeasureRelatedPageNode with fixed height
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureRelatedPageNode004, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto relatedNode = CreateLayoutTestChildNode("relatedPage");
    hostNode->AddChild(relatedNode);
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SetupLayoutConstraint(layoutProperty);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = relatedNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(relatedNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasureRelatedPageNode005
 * @tc.desc: Test MeasureRelatedPageNode with auto height
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureRelatedPageNode005, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto relatedNode = CreateLayoutTestChildNode("relatedPage");
    hostNode->AddChild(relatedNode);
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->selfIdealSize = CalcSize(CalcLength(1000.0f), CalcLength("auto"));
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = relatedNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(relatedNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: LayoutRelatedPageNode001
 * @tc.desc: Test LayoutRelatedPageNode with null node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutRelatedPageNode001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: LayoutRelatedPageNode002
 * @tc.desc: Test LayoutRelatedPageNode with invisible node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutRelatedPageNode002, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto relatedNode = CreateLayoutTestChildNode("relatedPage");
    relatedNode->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: LayoutRelatedPageNode003
 * @tc.desc: Test LayoutRelatedPageNode with null wrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutRelatedPageNode003, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto relatedNode = CreateLayoutTestChildNode("relatedPage");
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: LayoutRelatedPageNode004
 * @tc.desc: Test LayoutRelatedPageNode normal path
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutRelatedPageNode004, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto relatedNode = CreateLayoutTestChildNode("relatedPage");
    hostNode->AddChild(relatedNode);
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = relatedNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(relatedNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->LayoutRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
    auto offset = childGeoNode->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 301.0f);
}

/**
 * @tc.name: LayoutForceSplitPlaceHolderNode001
 * @tc.desc: Test LayoutForceSplitPlaceHolderNode with null phNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutForceSplitPlaceHolderNode001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutForceSplitPlaceHolderNode(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: LayoutForceSplitPlaceHolderNode002
 * @tc.desc: Test LayoutForceSplitPlaceHolderNode with null phWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutForceSplitPlaceHolderNode002, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto phNode = CreateLayoutTestChildNode("forceSplitPH");
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutForceSplitPlaceHolderNode(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: LayoutForceSplitPlaceHolderNode003
 * @tc.desc: Test LayoutForceSplitPlaceHolderNode normal path
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutForceSplitPlaceHolderNode003, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto phNode = CreateLayoutTestChildNode("forceSplitPH");
    hostNode->AddChild(phNode);
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = phNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(phNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->LayoutForceSplitPlaceHolderNode(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
    auto offset = childGeoNode->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 301.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodes001
 * @tc.desc: Test LayoutForceSplitMaskNodes with null layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutForceSplitMaskNodes001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    algorithm->LayoutForceSplitMaskNodes(nullptr, hostNode, layoutProperty, 400.0f, 1.0f);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodes002
 * @tc.desc: Test LayoutForceSplitMaskNodes with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutForceSplitMaskNodes002, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutForceSplitMaskNodes(layoutWrapper.GetRawPtr(), nullptr, layoutProperty, 400.0f, 1.0f);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodes003
 * @tc.desc: Test LayoutForceSplitMaskNodes with null navigationLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutForceSplitMaskNodes003, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutForceSplitMaskNodes(layoutWrapper.GetRawPtr(), hostNode, nullptr, 400.0f, 1.0f);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodes004
 * @tc.desc: Test LayoutForceSplitMaskNodes with null navigationGeometryNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutForceSplitMaskNodes004, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, nullptr, layoutProperty);
    algorithm->LayoutForceSplitMaskNodes(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 400.0f, 1.0f);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodes005
 * @tc.desc: Test LayoutForceSplitMaskNodes with left mask not visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutForceSplitMaskNodes005, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto leftMask = CreateLayoutTestChildNode("leftMask");
    leftMask->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->AddChild(leftMask);
    hostNode->leftMaskNode_ = leftMask;
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto leftGeoNode = AceType::MakeRefPtr<GeometryNode>();
    leftGeoNode->SetFrameSize(SizeF(400.0f, 800.0f));
    auto leftProp = leftMask->GetLayoutProperty();
    auto leftWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(leftMask, leftGeoNode, leftProp);
    layoutWrapper->AppendChild(leftWrapper);
    algorithm->LayoutForceSplitMaskNodes(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 400.0f, 1.0f);
    EXPECT_EQ(leftGeoNode->GetMarginFrameOffset().GetX(), 0.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodes006
 * @tc.desc: Test LayoutForceSplitMaskNodes with right mask not visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutForceSplitMaskNodes006, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto leftMask = CreateLayoutTestChildNode("leftMask");
    auto rightMask = CreateLayoutTestChildNode("rightMask");
    rightMask->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->AddChild(leftMask);
    hostNode->AddChild(rightMask);
    hostNode->leftMaskNode_ = leftMask;
    hostNode->rightMaskNode_ = rightMask;
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto leftGeoNode = AceType::MakeRefPtr<GeometryNode>();
    leftGeoNode->SetFrameSize(SizeF(400.0f, 800.0f));
    auto leftProp = leftMask->GetLayoutProperty();
    auto leftWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(leftMask, leftGeoNode, leftProp);
    layoutWrapper->AppendChild(leftWrapper);
    auto rightGeoNode = AceType::MakeRefPtr<GeometryNode>();
    rightGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto rightProp = rightMask->GetLayoutProperty();
    auto rightWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(rightMask, rightGeoNode, rightProp);
    layoutWrapper->AppendChild(rightWrapper);
    algorithm->LayoutForceSplitMaskNodes(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 400.0f, 1.0f);
    EXPECT_EQ(rightGeoNode->GetMarginFrameOffset().GetX(), 0.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodes007
 * @tc.desc: Test LayoutForceSplitMaskNodes with both masks visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutForceSplitMaskNodes007, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto leftMask = CreateLayoutTestChildNode("leftMask");
    auto rightMask = CreateLayoutTestChildNode("rightMask");
    hostNode->AddChild(leftMask);
    hostNode->AddChild(rightMask);
    hostNode->leftMaskNode_ = leftMask;
    hostNode->rightMaskNode_ = rightMask;
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto leftGeoNode = AceType::MakeRefPtr<GeometryNode>();
    leftGeoNode->SetFrameSize(SizeF(400.0f, 800.0f));
    auto leftProp = leftMask->GetLayoutProperty();
    auto leftWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(leftMask, leftGeoNode, leftProp);
    layoutWrapper->AppendChild(leftWrapper);
    auto rightGeoNode = AceType::MakeRefPtr<GeometryNode>();
    rightGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto rightProp = rightMask->GetLayoutProperty();
    auto rightWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(rightMask, rightGeoNode, rightProp);
    layoutWrapper->AppendChild(rightWrapper);
    algorithm->LayoutForceSplitMaskNodes(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 400.0f, 1.0f);
    auto rightOffset = rightGeoNode->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(rightOffset.GetX(), 401.0f);
}

/**
 * @tc.name: SetNavigationWidth001
 * @tc.desc: Test SetNavigationWidth with empty navigation stack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, SetNavigationWidth001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->realNavBarWidth_ = 300.0f;
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF size(1000.0f, 1000.0f);
    algorithm->SetNavigationWidth(layoutWrapper.GetRawPtr(), size);
    EXPECT_FLOAT_EQ(size.Width(), 300.0f);
}

/**
 * @tc.name: SetNavigationWidth002
 * @tc.desc: Test SetNavigationWidth with STACK mode and non-empty stack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, SetNavigationWidth002, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->realNavBarWidth_ = 300.0f;
    algorithm->realContentWidth_ = 600.0f;
    auto hostNode = CreateNavLayoutTestNode();
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.emplace_back(std::make_pair("page1", nullptr));
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF size(1000.0f, 1000.0f);
    algorithm->SetNavigationWidth(layoutWrapper.GetRawPtr(), size);
    EXPECT_FLOAT_EQ(size.Width(), 600.0f);
}

/**
 * @tc.name: SetNavigationWidth003
 * @tc.desc: Test SetNavigationWidth with SPLIT mode and non-empty stack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, SetNavigationWidth003, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->realNavBarWidth_ = 300.0f;
    algorithm->realContentWidth_ = 600.0f;
    algorithm->realDividerWidth_ = 1.0f;
    auto hostNode = CreateNavLayoutTestNode();
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.emplace_back(std::make_pair("page1", nullptr));
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF size(1000.0f, 1000.0f);
    algorithm->SetNavigationWidth(layoutWrapper.GetRawPtr(), size);
    EXPECT_FLOAT_EQ(size.Width(), 901.0f);
}

/**
 * @tc.name: SetNavigationWidth004
 * @tc.desc: Test SetNavigationWidth with null hostNode (non-NavigationGroupNode host)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, SetNavigationWidth004, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->realNavBarWidth_ = 300.0f;
    auto plainNode = FrameNode::CreateFrameNode(
        "plain", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    auto layoutProperty = plainNode->GetLayoutProperty();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(plainNode, geometryNode, layoutProperty);
    SizeF size(1000.0f, 1000.0f);
    algorithm->SetNavigationWidth(layoutWrapper.GetRawPtr(), size);
    EXPECT_FLOAT_EQ(size.Width(), 1000.0f);
}

/**
 * @tc.name: SetNavigationWidth005
 * @tc.desc: Test SetNavigationWidth with null navigationStack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, SetNavigationWidth005, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->realNavBarWidth_ = 300.0f;
    auto hostNode = CreateNavLayoutTestNode();
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto savedStack = pattern->GetNavigationStack();
    pattern->SetNavigationStack(nullptr);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF size(1000.0f, 1000.0f);
    algorithm->SetNavigationWidth(layoutWrapper.GetRawPtr(), size);
    pattern->SetNavigationStack(savedStack);
    EXPECT_FLOAT_EQ(size.Width(), 1000.0f);
}

/**
 * @tc.name: MeasureSplitPlaceholder001
 * @tc.desc: Test MeasureSplitPlaceholder with null placeholderContentNode (via Measure)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureSplitPlaceholder001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(1000.0f, 1000.0f);
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    algorithm->Measure(layoutWrapper.GetRawPtr());
    EXPECT_GE(geometryNode->GetFrameSize().Width(), 0.0f);
}

/**
 * @tc.name: MeasureSplitPlaceholder002
 * @tc.desc: Test MeasureSplitPlaceholder with valid placeholder in SPLIT mode and empty stack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureSplitPlaceholder002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto placeholderNode = CreateLayoutTestChildNode("splitPlaceholder");
    hostNode->AddChild(placeholderNode);
    hostNode->SetPlaceholderContentNode(placeholderNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(1000.0f, 1000.0f);
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    layoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = placeholderNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    algorithm->Measure(layoutWrapper.GetRawPtr());
    EXPECT_GE(childGeoNode->GetFrameSize().Width(), 0.0f);
}

/**
 * @tc.name: MeasureSplitPlaceholder003
 * @tc.desc: Test MeasureSplitPlaceholder with hideNavBar true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureSplitPlaceholder003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto placeholderNode = CreateLayoutTestChildNode("splitPlaceholder");
    hostNode->AddChild(placeholderNode);
    hostNode->SetPlaceholderContentNode(placeholderNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(1000.0f, 1000.0f);
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    layoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    layoutProperty->UpdateHideNavBar(true);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = placeholderNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    algorithm->Measure(layoutWrapper.GetRawPtr());
    EXPECT_GE(childGeoNode->GetFrameSize().Width(), 0.0f);
}

/**
 * @tc.name: MeasureSplitPlaceholder004
 * @tc.desc: Test MeasureSplitPlaceholder with auto height and empty stack in SPLIT mode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, MeasureSplitPlaceholder004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto placeholderNode = CreateLayoutTestChildNode("splitPlaceholder");
    hostNode->AddChild(placeholderNode);
    hostNode->SetPlaceholderContentNode(placeholderNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(1000.0f, 1000.0f);
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->selfIdealSize = CalcSize(CalcLength(1000.0f), CalcLength("auto"));
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = placeholderNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    algorithm->Measure(layoutWrapper.GetRawPtr());
    EXPECT_GE(childGeoNode->GetFrameSize().Width(), 0.0f);
}

/**
 * @tc.name: LayoutPrimaryContentNode001
 * @tc.desc: Test LayoutPrimaryContentNode normal path with visible node (via Layout)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutPrimaryContentNode001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto primaryContentNode = CreateLayoutTestChildNode("primaryContent");
    hostNode->AddChild(primaryContentNode);
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = primaryContentNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(primaryContentNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    algorithm->Layout(layoutWrapper.GetRawPtr());
    auto offset = childGeoNode->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 0.0f);
}

/**
 * @tc.name: LayoutPrimaryContentNode002
 * @tc.desc: Test LayoutPrimaryContentNode with invisible primaryContentNode (via Layout)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutPrimaryContentNode002, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto primaryContentNode = CreateLayoutTestChildNode("primaryContent");
    primaryContentNode->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->AddChild(primaryContentNode);
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = primaryContentNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(primaryContentNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    algorithm->Layout(layoutWrapper.GetRawPtr());
    EXPECT_EQ(childGeoNode->GetMarginFrameOffset().GetX(), 0.0f);
}

/**
 * @tc.name: LayoutPrimaryContentNode003
 * @tc.desc: Test LayoutPrimaryContentNode with null primaryContentNode (via Layout)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutPrimaryContentNode003, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    algorithm->Layout(layoutWrapper.GetRawPtr());
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: LayoutSplitPlaceholderContent001
 * @tc.desc: Test LayoutSplitPlaceholderContent with valid placeholder in SPLIT mode and empty stack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutSplitPlaceholderContent001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto navBarNode = CreateLayoutTestChildNode("navBar");
    hostNode->AddChild(navBarNode);
    hostNode->navBarNode_ = navBarNode;
    auto dividerNode = CreateLayoutTestChildNode("divider");
    hostNode->AddChild(dividerNode);
    hostNode->dividerNode_ = dividerNode;
    auto placeholderNode = CreateLayoutTestChildNode("splitPlaceholder");
    hostNode->AddChild(placeholderNode);
    hostNode->SetPlaceholderContentNode(placeholderNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto navBarGeoNode = AceType::MakeRefPtr<GeometryNode>();
    navBarGeoNode->SetFrameSize(SizeF(500.0f, 1000.0f));
    auto navBarProp = navBarNode->GetLayoutProperty();
    auto navBarWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(navBarNode, navBarGeoNode, navBarProp);
    layoutWrapper->AppendChild(navBarWrapper);
    auto dividerGeoNode = AceType::MakeRefPtr<GeometryNode>();
    dividerGeoNode->SetFrameSize(SizeF(1.0f, 1000.0f));
    auto dividerProp = dividerNode->GetLayoutProperty();
    auto dividerWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, dividerGeoNode, dividerProp);
    layoutWrapper->AppendChild(dividerWrapper);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = placeholderNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    algorithm->Layout(layoutWrapper.GetRawPtr());
    auto offset = childGeoNode->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 501.0f);
}

/**
 * @tc.name: LayoutSplitPlaceholderContent002
 * @tc.desc: Test LayoutSplitPlaceholderContent with non-empty stack (condition not met)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutSplitPlaceholderContent002, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto placeholderNode = CreateLayoutTestChildNode("splitPlaceholder");
    hostNode->AddChild(placeholderNode);
    hostNode->SetPlaceholderContentNode(placeholderNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = placeholderNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.emplace_back(std::make_pair("page1", nullptr));
    algorithm->Layout(layoutWrapper.GetRawPtr());
    EXPECT_EQ(childGeoNode->GetMarginFrameOffset().GetX(), 0.0f);
}

/**
 * @tc.name: LayoutSplitPlaceholderContent003
 * @tc.desc: Test LayoutSplitPlaceholderContent with hideNavBar true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutTestNg, LayoutSplitPlaceholderContent003, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavLayoutTestNode();
    auto placeholderNode = CreateLayoutTestChildNode("splitPlaceholder");
    hostNode->AddChild(placeholderNode);
    hostNode->SetPlaceholderContentNode(placeholderNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    layoutProperty->UpdateHideNavBar(true);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = placeholderNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    algorithm->Layout(layoutWrapper.GetRawPtr());
    EXPECT_EQ(childGeoNode->GetMarginFrameOffset().GetX(), 0.0f);
}

} // namespace OHOS::Ace::NG

