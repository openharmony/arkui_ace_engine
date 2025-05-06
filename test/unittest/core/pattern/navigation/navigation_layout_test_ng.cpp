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
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

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
 * @tc.desc: Test NotifyDialogChange function.
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
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest020
 * @tc.desc: Test NotifyDialogChange function.
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
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest021
 * @tc.desc: Test NotifyDialogChange function.
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
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest022
 * @tc.desc: Test NotifyDialogChange function.
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
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest023
 * @tc.desc: Test NotifyDialogChange function.
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
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest024
 * @tc.desc: Test NotifyDialogChange function.
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
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_HIDE, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest025
 * @tc.desc: Test NotifyDialogChange function.
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
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_HIDE, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest026
 * @tc.desc: Test NotifyDialogChange function.
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
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_HIDE, isFromStandard);
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

    EXPECT_EQ(navigationPattern->FireNavDestinationStateChange(NavDestinationLifecycle::ON_HIDE), STANDARD_INDEX);
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

    EXPECT_EQ(navigationPattern->FireNavDestinationStateChange(NavDestinationLifecycle::ON_SHOW), STANDARD_INDEX);
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

    EXPECT_EQ(navigationPattern->FireNavDestinationStateChange(NavDestinationLifecycle::ON_SHOW), STANDARD_INDEX);
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

    EXPECT_EQ(navigationPattern->FireNavDestinationStateChange(NavDestinationLifecycle::ON_HIDE), STANDARD_INDEX);
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
 * @tc.name: DealNavigationExit001
 * @tc.desc: Test DealNavigationExit and make the logic as follows:
 *               GetOrCreateEventHub return false
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

    EXPECT_EQ(preNode->GetEventHub<EventHub>(), nullptr);
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
 *               GetOrCreateEventHub return true
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

    EXPECT_NE(preNode->GetOrCreateEventHub<EventHub>(), nullptr);
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
 * @tc.name: DealNavigationExit003
 * @tc.desc: Test DealNavigationExit and make the logic as follows:
 *               GetOrCreateEventHub return true
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

    EXPECT_NE(preNode->GetOrCreateEventHub<EventHub>(), nullptr);
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
} // namespace OHOS::Ace::NG

