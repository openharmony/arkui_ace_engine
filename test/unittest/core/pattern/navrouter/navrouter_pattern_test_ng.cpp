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

#include <cstddef>
#include <list>
#include <optional>
#include <string>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/base/mock_pixel_map.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_model.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string TITLE_BAR_NODE_MENU = "menu";
} // namespace

class NavrouterPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void MockPipelineContextGetTheme();
};

void NavrouterPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}
void NavrouterPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void NavrouterPatternTestNg::SetUp() {}
void NavrouterPatternTestNg::TearDown() {}

void NavrouterPatternTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: OnAttachToMainTree001
 * @tc.desc: Test OnAttachToMainTree and make node return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, OnAttachToMainTree001, TestSize.Level1)
{
    // Make node return false.
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);

    ASSERT_EQ(AceType::DynamicCast<UINode>(navDestinationPattern->GetHost()), nullptr);
    navDestinationPattern->OnAttachToMainTree();
}

/**
 * @tc.name: OnAttachToMainTree002
 * @tc.desc: Test OnAttachToMainTree and make node and GetTag return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, OnAttachToMainTree002, TestSize.Level1)
{
    // Make node return true.
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>(
        "navDestinationNode", 11, AceType::MakeRefPtr<NavDestinationPattern>());
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    RefPtr<UINode> node = AceType::DynamicCast<UINode>(navDestinationPattern->GetHost());
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->GetTag(), V2::NAVIGATION_VIEW_ETS_TAG);
    navDestinationPattern->OnAttachToMainTree();
}

/**
 * @tc.name: OnAttachToMainTree003
 * @tc.desc: Test OnAttachToMainTree and make node and GetTag return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, OnAttachToMainTree003, TestSize.Level1)
{
    // Make node return true.
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>(
        "navDestinationNode", 11, AceType::MakeRefPtr<NavDestinationPattern>());
    ASSERT_NE(navDestinationNode, nullptr);
    navDestinationNode->tag_ = V2::NAVIGATION_VIEW_ETS_TAG;
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    RefPtr<UINode> node = AceType::DynamicCast<UINode>(navDestinationPattern->GetHost());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::NAVIGATION_VIEW_ETS_TAG);
    navDestinationPattern->OnAttachToMainTree();
}

/**
 * @tc.name: ParseCommonTitle001
 * @tc.desc: Test NavrouterTestNg and cover all conditions of hasSubTitle and hasMainTitle
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, ParseCommonTitle001, TestSize.Level1)
{
    NavDestinationModelNG navDestinationModel;
    bool hasSubTitle = true, hasMainTitle = true;
    EXPECT_FALSE(!hasSubTitle && !hasMainTitle);
    navDestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "");

    hasSubTitle = false;
    EXPECT_FALSE(!hasSubTitle && !hasMainTitle);
    navDestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "");

    hasMainTitle = false;
    EXPECT_TRUE(!hasSubTitle && !hasMainTitle);
    navDestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "");
}

/**
 * @tc.name: ParseCommonTitle002
 * @tc.desc: Test NavrouterTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return false
 *               hasMainTitle is false
 *               !hasSubTitle is false
 *               subTitle is false
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, ParseCommonTitle002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto* stack = ViewStackProcessor::GetInstance();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    navDestinationNode->titleBarNode_ = titleBarNode;
    // Make GetPrevTitleIsCustomValue return false
    navDestinationNode->propPrevTitleIsCustom_ = false;
    stack->Push(navDestinationNode);

    // Make sure hasMainTitle is false and !hasSubTitle is false
    bool hasSubTitle = true, hasMainTitle = false;
    EXPECT_FALSE(!hasSubTitle);
    EXPECT_FALSE(hasMainTitle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto titleBarNodeTest = AceType::DynamicCast<TitleBarNode>(navDestinationNodeTest->GetTitleBarNode());
    ASSERT_NE(titleBarNodeTest, nullptr);
    // Make sure GetPrevTitleIsCustomValue return false
    EXPECT_FALSE(navDestinationNodeTest->GetPrevTitleIsCustomValue(false));
    ASSERT_EQ(AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle()), nullptr);
    bool ret = navDestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "");
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ParseCommonTitle003
 * @tc.desc: Test NavrouterTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return true
 *               HasTitleHeight return false
 *               hasMainTitle is true
 *               mainTitle is false
 *               !hasSubTitle is false
 *               subTitle is true
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, ParseCommonTitle003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto* stack = ViewStackProcessor::GetInstance();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    auto subTitle = FrameNode::CreateFrameNode("SubTitle", 36, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->subtitle_ = subTitle;
    navDestinationNode->titleBarNode_ = titleBarNode;
    // Make GetPrevTitleIsCustomValue return true
    navDestinationNode->propPrevTitleIsCustom_ = true;
    stack->Push(navDestinationNode);

    // Make sure hasMainTitle is true and !hasSubTitle is false
    bool hasSubTitle = true, hasMainTitle = true;
    EXPECT_FALSE(!hasSubTitle);
    EXPECT_TRUE(hasMainTitle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto titleBarNodeTest = AceType::DynamicCast<TitleBarNode>(navDestinationNodeTest->GetTitleBarNode());
    ASSERT_NE(titleBarNodeTest, nullptr);
    // Make sure GetPrevTitleIsCustomValue return true
    EXPECT_TRUE(navDestinationNodeTest->GetPrevTitleIsCustomValue(false));
    // Make sure HasTitleHeight return false
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    EXPECT_FALSE(titleBarLayoutProperty->HasTitleHeight());
    // Make sure mainTitle is false
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle()), nullptr);
    // subTitle is true
    auto subTitleTest = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    EXPECT_NE(AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle()), nullptr);
    bool ret = navDestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "");
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ParseCommonTitle004
 * @tc.desc: Test NavrouterTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return true
 *               HasTitleHeight return true
 *               hasMainTitle is true
 *               mainTitle is true
 *               !hasSubTitle is true
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, ParseCommonTitle004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto* stack = ViewStackProcessor::GetInstance();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    auto title = FrameNode::CreateFrameNode("SubTitle", 36, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = title;
    // Make HasTitleHeight return true
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleHeight_ = NG::DOUBLE_LINE_TITLEBAR_HEIGHT;
    navDestinationNode->titleBarNode_ = titleBarNode;
    // Make GetPrevTitleIsCustomValue return true
    navDestinationNode->propPrevTitleIsCustom_ = true;
    stack->Push(navDestinationNode);

    // Make sure hasMainTitle is true and !hasSubTitle is true
    bool hasSubTitle = false, hasMainTitle = true;
    EXPECT_TRUE(!hasSubTitle);
    EXPECT_TRUE(hasMainTitle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto titleBarNodeTest = AceType::DynamicCast<TitleBarNode>(navDestinationNodeTest->GetTitleBarNode());
    ASSERT_NE(titleBarNodeTest, nullptr);
    // Make sure GetPrevTitleIsCustomValue return true
    EXPECT_TRUE(navDestinationNodeTest->GetPrevTitleIsCustomValue(false));
    // Make sure HasTitleHeight return true
    auto titleBarLayoutPropertyTest = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    EXPECT_TRUE(titleBarLayoutPropertyTest->HasTitleHeight());
    // Make sure mainTitle is true
    EXPECT_NE(AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle()), nullptr);
    bool ret = navDestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "");
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: Create001
 * @tc.desc: Test NavrouterTestNg and make navDestinationNode false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, Create001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(ElementRegister::GetInstance()->MakeUniqueId());

    NavDestinationModelNG navDestinationModel;
    bool deepRenderCalled = false;
    auto deepRenderFunc = [&deepRenderCalled]() { deepRenderCalled = true; };
    navDestinationModel.Create(std::move(deepRenderFunc), AceType::MakeRefPtr<NavDestinationContext>());
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navDestinationNode, nullptr);
    // Make navDestinationNode false
    int32_t originNodeId = navDestinationNode->nodeId_;
    navDestinationNode->nodeId_ = originNodeId + 1;

    // Make sure navDestinationNodeTest is false
    auto parent = AceType::DynamicCast<UINode>(
        FrameNode::GetFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, navDestinationNode->nodeId_));
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(parent);
    EXPECT_EQ(AceType::DynamicCast<NavDestinationGroupNode>(parent), nullptr);
    // Prepare for calling the deepRender defined in NavDestinationModelNG::Create()
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
    ASSERT_NE(shallowBuilder, nullptr);
    EXPECT_FALSE(shallowBuilder->IsExecuteDeepRenderDone());
    shallowBuilder->ExecuteDeepRender();
    EXPECT_TRUE(deepRenderCalled);
}

/**
 * @tc.name: Create002
 * @tc.desc: Test NavrouterTestNg and make navDestinationNode true and GetContentNode return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, Create002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(ElementRegister::GetInstance()->MakeUniqueId());

    NavDestinationModelNG navDestinationModel;
    bool deepRenderCalled = false;
    auto deepRenderFunc = [&deepRenderCalled]() { deepRenderCalled = true; };
    navDestinationModel.Create(std::move(deepRenderFunc), AceType::MakeRefPtr<NavDestinationContext>());
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navDestinationNode, nullptr);
    // Make GetContentNode return false
    navDestinationNode->contentNode_ = nullptr;

    // Make sure navDestinationNodeTest is true
    auto parent = AceType::DynamicCast<UINode>(
        FrameNode::GetFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, navDestinationNode->nodeId_));
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(parent);
    ASSERT_NE(navDestinationNodeTest, nullptr);
    EXPECT_EQ(navDestinationNodeTest->GetContentNode(), nullptr);
    // Prepare for calling the deepRender defined in NavDestinationModelNG::Create()
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
    ASSERT_NE(shallowBuilder, nullptr);
    EXPECT_FALSE(shallowBuilder->IsExecuteDeepRenderDone());
    shallowBuilder->ExecuteDeepRender();
    EXPECT_TRUE(deepRenderCalled);
}

/**
 * @tc.name: Create003
 * @tc.desc: Test NavrouterTestNg and make navDestinationNode true and GetContentNode return true.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, Create003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(ElementRegister::GetInstance()->MakeUniqueId());
    
    NavDestinationModelNG navDestinationModel;
    bool deepRenderCalled = false;
    auto deepRenderFunc = [&deepRenderCalled]() { deepRenderCalled = true; };
    navDestinationModel.Create(std::move(deepRenderFunc), AceType::MakeRefPtr<NavDestinationContext>());
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navDestinationNode, nullptr);

    // Make sure navDestinationNodeTest is true
    auto parent = AceType::DynamicCast<UINode>(
        FrameNode::GetFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, navDestinationNode->nodeId_));
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(parent);
    ASSERT_NE(navDestinationNodeTest, nullptr);
    EXPECT_NE(navDestinationNodeTest->GetContentNode(), nullptr);
    // Prepare for calling the deepRender defined in NavDestinationModelNG::Create()
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
    ASSERT_NE(shallowBuilder, nullptr);
    EXPECT_FALSE(shallowBuilder->IsExecuteDeepRenderDone());
    shallowBuilder->ExecuteDeepRender();
    EXPECT_TRUE(deepRenderCalled);
}

/**
 * @tc.name: SetCustomTitle001
 * @tc.desc: Test NavrouterTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return false
 *               currentTitle is false
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, SetCustomTitle001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    // Make GetPrevTitleIsCustomValue return false
    navDestinationNode->propPrevTitleIsCustom_ = false;

    auto customNode = FrameNode::CreateFrameNode("Title", 99, AceType::MakeRefPtr<CustomNodePattern>());
    EXPECT_NE(customNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    // Make sure GetPrevTitleIsCustomValue return false
    EXPECT_FALSE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    // Make sure currentTitle is false
    EXPECT_EQ(titleBarNode->GetTitle(), nullptr);
    navDestinationModel.SetCustomTitle(customNode);
}

/**
 * @tc.name: SetCustomTitle002
 * @tc.desc: Test NavrouterTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return true
 *               currentTitle is true
 *               GetId is not GetId
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, SetCustomTitle002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    // Make GetPrevTitleIsCustomValue return true
    navDestinationNode->propPrevTitleIsCustom_ = true;
    // Make currentTitle true
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    auto title = FrameNode::CreateFrameNode("Title", 36, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = title;
    navDestinationNode->titleBarNode_ = titleBarNode;

    auto customNode = FrameNode::CreateFrameNode("Title", 99, AceType::MakeRefPtr<CustomNodePattern>());
    EXPECT_NE(customNode, nullptr);
    auto titleBarNodeTest = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNodeTest, nullptr);
    // Make sure GetPrevTitleIsCustomValue return true
    EXPECT_TRUE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    // Make sure currentTitle is true
    auto currentTitle = titleBarNodeTest->GetTitle();
    EXPECT_NE(currentTitle, nullptr);
    // Make sure GetId is not GetId
    EXPECT_NE(currentTitle->GetId(), customNode->GetId());
    navDestinationModel.SetCustomTitle(customNode);
}

/**
 * @tc.name: SetCustomTitle003
 * @tc.desc: Test NavrouterTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return true
 *               currentTitle is true
 *               GetId is GetId
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, SetCustomTitle003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    // Make GetPrevTitleIsCustomValue return true
    navDestinationNode->propPrevTitleIsCustom_ = true;
    // Make currentTitle true
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    auto title = FrameNode::CreateFrameNode("Title", 36, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = title;
    navDestinationNode->titleBarNode_ = titleBarNode;

    auto titleBarNodeTest = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNodeTest, nullptr);
    // Make sure GetPrevTitleIsCustomValue return true
    EXPECT_TRUE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    // Make sure currentTitle is true
    auto currentTitle = titleBarNodeTest->GetTitle();
    EXPECT_NE(currentTitle, nullptr);
    // Make sure GetId is GetId
    EXPECT_EQ(currentTitle->GetId(), title->GetId());
    navDestinationModel.SetCustomTitle(title);
}

/**
 * @tc.name: SetTitleHeight001
 * @tc.desc: Test NavrouterTestNg and cover all conditions of isValid.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, SetTitleHeight001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationGroupNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationGroupNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);

    // Make sure isValid is true
    bool isValid = true;
    EXPECT_TRUE(isValid);
    navDestinationModel.SetTitleHeight(NG::DOUBLE_LINE_TITLEBAR_HEIGHT, isValid);
    // Make sure isValid is false
    isValid = false;
    EXPECT_FALSE(isValid);
    navDestinationModel.SetTitleHeight(NG::DOUBLE_LINE_TITLEBAR_HEIGHT, isValid);
}

/**
 * @tc.name: SetMenuItems001
 * @tc.desc: Test SetMenuItems function.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, SetMenuItems001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationGroupNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationGroupNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);

    NG::BarItem bar;
    std::vector<NG::BarItem> barItems;
    barItems.push_back(bar);

    /**
     * @tc.steps: step2. Call SetMenuItems when UpdatePrevMenuIsCustom is true.
     */
    navDestinationGroupNode->UpdatePrevMenuIsCustom(true);
    navDestinationModel.SetMenuItems(std::move(barItems));
    EXPECT_FALSE(navDestinationGroupNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(navDestinationGroupNode->GetMenuNodeOperationValue(), ChildNodeOperation::REPLACE);

    /**
     * @tc.steps: step3. Call SetMenuItems when UpdatePrevMenuIsCustom is false.
     * and navDestinationGroupNode has no menu
     */
    navDestinationGroupNode->UpdatePrevMenuIsCustom(false);
    navDestinationModel.SetMenuItems(std::move(barItems));
    EXPECT_FALSE(navDestinationGroupNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(navDestinationGroupNode->GetMenuNodeOperationValue(), ChildNodeOperation::ADD);

    /**
     * @tc.steps: step4. Call SetMenuItems when UpdatePrevMenuIsCustom is false
     * and navDestinationGroupNode has menu
     */
    navDestinationGroupNode->UpdatePrevMenuIsCustom(false);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode = AceType::MakeRefPtr<FrameNode>(TITLE_BAR_NODE_MENU, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    navDestinationGroupNode->SetMenu(menuNode);
    navDestinationModel.SetMenuItems(std::move(barItems));
    EXPECT_FALSE(navDestinationGroupNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(navDestinationGroupNode->GetMenuNodeOperationValue(), ChildNodeOperation::REPLACE);
}

/**
 * @tc.name: SetCustomMenu001
 * @tc.desc: Test SetCustomMenu function.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, SetCustomMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationGroupNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationGroupNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);

    RefPtr<AceType> customNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Call SetCustomMenu when previous node is not custom.
     */
    navDestinationModel.SetCustomMenu(customNode);
    EXPECT_TRUE(navDestinationGroupNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(navDestinationGroupNode->GetMenuNodeOperationValue(), ChildNodeOperation::ADD);

    auto menuNode = AceType::MakeRefPtr<FrameNode>(TITLE_BAR_NODE_MENU, 33, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    navDestinationGroupNode->SetMenu(menuNode);

    /**
     * @tc.steps: step3. Call SetMenuItems when previous menu exists.
     */
    navDestinationGroupNode->SetMenu(menuNode);
    navDestinationModel.SetCustomMenu(customNode);
    EXPECT_TRUE(navDestinationGroupNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(navDestinationGroupNode->GetMenuNodeOperationValue(), ChildNodeOperation::REPLACE);
}

/**
 * @tc.name: ProcessShallowBuilder001
 * @tc.desc: Test NavrouterTestNg and make isCacheNode_ true.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, ProcessShallowBuilder001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->isCacheNode_ = true;
    
    EXPECT_TRUE(navDestinationNode->isCacheNode_);
    navDestinationNode->ProcessShallowBuilder();
}

/**
 * @tc.name: GetNavDestinationCustomNode001
 * @tc.desc: Test NavrouterTestNg and make child false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, GetNavDestinationCustomNode001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto customNode = FrameNode::CreateFrameNode("Title", 99, AceType::MakeRefPtr<CustomNodePattern>());
    navDestinationPattern->customNode_ = customNode;

    EXPECT_NE(navDestinationPattern->GetCustomNode(), nullptr);
    EXPECT_EQ(navDestinationNode->GetFirstChild(), nullptr);
    navDestinationNode->GetNavDestinationCustomNode();
}

/**
 * @tc.name: GetNavDestinationCustomNode002
 * @tc.desc: Test NavrouterTestNg and make child true and two InstanceOfs false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, GetNavDestinationCustomNode002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    // Make child true
    auto customNode = FrameNode::CreateFrameNode("Custom", 99, AceType::MakeRefPtr<CustomNodePattern>());
    navDestinationNode->children_.emplace_back(customNode);
    navDestinationPattern->customNode_ = navDestinationNode;

    auto navDestinationNodeTest = navDestinationPattern->GetCustomNode();
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto child = navDestinationNodeTest->GetFirstChild();
    EXPECT_NE(child, nullptr);
    EXPECT_FALSE(AceType::InstanceOf<NavDestinationGroupNode>(child));
    EXPECT_FALSE(AceType::InstanceOf<CustomNodeBase>(child));
    navDestinationNode->GetNavDestinationCustomNode();
}

/**
 * @tc.name: GetNavDestinationCustomNode003
 * @tc.desc: Test NavrouterTestNg and make child true and the first InstanceOf true
 *               and the second InstanceOf false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, GetNavDestinationCustomNode003, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    // Make child true and InstanceOf<NavDestinationGroupNode> true
    auto navDestinationChildNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        102, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->children_.emplace_front(navDestinationChildNode);
    navDestinationPattern->customNode_ = navDestinationNode;

    auto navDestinationNodeTest = navDestinationPattern->GetCustomNode();
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto child = navDestinationNodeTest->GetFirstChild();
    EXPECT_NE(child, nullptr);
    EXPECT_TRUE(AceType::InstanceOf<NavDestinationGroupNode>(child));
    EXPECT_FALSE(AceType::InstanceOf<CustomNodeBase>(child));
    navDestinationNode->GetNavDestinationCustomNode();
}

/**
 * @tc.name: GetNavDestinationCustomNode004
 * @tc.desc: Test NavrouterTestNg and make child true and the first InstanceOf false
 *               and the second InstanceOf true.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, GetNavDestinationCustomNode004, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    // Make child true and InstanceOf<NavDestinationGroupNode> true
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(201, "Custom");
    navDestinationNode->children_.emplace_front(customNode);
    navDestinationPattern->customNode_ = navDestinationNode;

    auto navDestinationNodeTest = navDestinationPattern->GetCustomNode();
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto child = navDestinationNodeTest->GetFirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_FALSE(AceType::InstanceOf<NavDestinationGroupNode>(child));
    EXPECT_TRUE(AceType::InstanceOf<CustomNodeBase>(child));
    navDestinationNode->GetNavDestinationCustomNode();
}

/**
 * @tc.name: MeasureContentChild001
 * @tc.desc: Test NavrouterTestNg and cover all conditions of IsAutoHeight.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, MeasureContentChild001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavDestinationLayoutAlgorithm>();
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    // Make hostNode not NULL
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    navDestinationNode->titleBarNode_ = titleBarNode;
    navDestinationNode->children_.push_back(titleBarNode);
    // Make contentNode not NULL
    navDestinationNode->contentNode_ = titleBarNode;

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    // Make navDestinationLayoutProperty not NULL
    auto navDestinationLayoutProperty = AceType::MakeRefPtr<NavDestinationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;
    // Make constraint not NULL
    navDestinationLayoutProperty->layoutConstraint_ = constraint;
    navDestinationLayoutProperty->contentConstraint_ = constraint;

    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(
        AceType::WeakClaim(AceType::RawPtr(navDestinationNode)), geometryNode, navDestinationLayoutProperty);
    RefPtr<LayoutWrapperNode> titleBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(titleBarNode, geometryNode, titleBarNode->GetLayoutProperty());
    layoutWrapper->currentChildCount_ = 0;
    layoutWrapper->childrenMap_.try_emplace(layoutWrapper->currentChildCount_++, titleBarLayoutWrapper);
    // Make sure IsAutoHeight is false
    auto contentNode = navDestinationNode->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto index = navDestinationNode->GetChildIndexById(contentNode->GetId());
    EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(index));
    EXPECT_FALSE(NavigationLayoutAlgorithm::IsAutoHeight(navDestinationLayoutProperty));
    algorithm->Measure(layoutWrapper);

    // Make IsAutoHeight false
    navDestinationLayoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    auto& calcLayoutConstraint = navDestinationLayoutProperty->GetCalcLayoutConstraint();
    ASSERT_NE(calcLayoutConstraint, nullptr);
    auto calcSize = CalcSize();
    calcSize.height_ = CalcLength(200);
    calcLayoutConstraint->selfIdealSize = calcSize;
    // Make sure IsAutoHeight is false
    EXPECT_FALSE(NavigationLayoutAlgorithm::IsAutoHeight(navDestinationLayoutProperty));
    algorithm->Measure(layoutWrapper);
}

/*
 * @tc.name: OnDetachFromMainTree001
 * @tc.desc: Test NavrouterTestNg and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, OnDetachFromMainTree001, TestSize.Level1)
{
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });

    // Make sure navDestinationNode_ is false
    EXPECT_EQ(navRouterNode->navDestinationNode_, nullptr);
    navRouterNode->OnDetachFromMainTree(false);

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navRouterNode->navDestinationNode_ = navDestinationNode;

    EXPECT_NE(navRouterNode->navDestinationNode_, nullptr);
    // Make sure Upgrade return false
    EXPECT_EQ(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    navRouterNode->OnDetachFromMainTree(false);

    // Make Upgrade return true
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterNode->weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);

    EXPECT_NE(navRouterNode->navDestinationNode_, nullptr);
    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_EQ(navigationPattern->GetNavigationStack(), nullptr);
    // Make sure stack is false
    navRouterNode->OnDetachFromMainTree(false);

    // Make stack true
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    
    EXPECT_NE(navRouterNode->navDestinationNode_, nullptr);
    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    EXPECT_NE(navigationPattern->GetNavigationStack(), nullptr);
    navRouterNode->OnDetachFromMainTree(false);
}

/*
 * @tc.name: AddNavDestinationToNavigation001
 * @tc.desc: Test AddNavDestinationToNavigation and cover all conditions of
 *               GetNavigationMode and GetNavigationStackProvided.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, AddNavDestinationToNavigation001, TestSize.Level1)
{
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    // Make navigationNode not NULL
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterNode->weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    // Make GetNavigationMode not NavigationMode::SPLIT
    navigationPattern->navigationMode_ = NavigationMode::AUTO;

    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    EXPECT_EQ(AceType::DynamicCast<NavDestinationGroupNode>(navRouterNode->GetNavDestinationNode()), nullptr);
    EXPECT_NE(navigationPattern->GetNavigationMode(), NavigationMode::SPLIT);
    navRouterNode->AddNavDestinationToNavigation();

    // Make GetNavigationMode NavigationMode::SPLIT
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    // Make GetNavigationStackProvided return true
    navigationPattern->navigationStackProvided_ = true;
    EXPECT_EQ(navigationPattern->GetNavigationMode(), NavigationMode::SPLIT);
    EXPECT_FALSE(!navigationPattern->GetNavigationStackProvided());
    navRouterNode->AddNavDestinationToNavigation();

    // Make GetNavigationStackProvided return false
    navigationPattern->navigationStackProvided_ = false;
    EXPECT_EQ(navigationPattern->GetNavigationMode(), NavigationMode::SPLIT);
    EXPECT_TRUE(!navigationPattern->GetNavigationStackProvided());
    navRouterNode->AddNavDestinationToNavigation();
}

/*
 * @tc.name: AddNavDestinationToNavigation002
 * @tc.desc: Test AddNavDestinationToNavigation and make the logic as follows:
 *               routeInfo is false
 *               navDestination is false
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, AddNavDestinationToNavigation002, TestSize.Level1)
{
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    // Make navigationNode not NULL
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterNode->weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    // Make sure navDestination is false
    EXPECT_EQ(AceType::DynamicCast<NavDestinationGroupNode>(navRouterNode->GetNavDestinationNode()), nullptr);
    // Make sure routeInfo is false
    auto navRouterPattern = navRouterNode->GetPattern<NavRouterPattern>();
    auto routeInfo = navRouterPattern->GetRouteInfo();
    EXPECT_EQ(navRouterPattern->GetRouteInfo(), nullptr);
    navRouterNode->AddNavDestinationToNavigation();
}

/*
 * @tc.name: AddNavDestinationToNavigation003
 * @tc.desc: Test AddNavDestinationToNavigation and make the logic as follows:
 *               routeInfo is false
 *               navDestination is true
 *               shallowBuilder is false
 *               destinationContent is false
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, AddNavDestinationToNavigation003, TestSize.Level1)
{
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    // Make navigationNode not NULL
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterNode->weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    // Make navDestination true
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navRouterNode->navDestinationNode_ = navDestinationNode;
    
    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(navRouterNode->GetNavDestinationNode());
    auto currentNavDestination =
        AceType::DynamicCast<NavDestinationGroupNode>(navigationPattern->GetNavDestinationNode());
    EXPECT_NE(currentNavDestination, navDestinationNodeTest);
    auto navRouterPattern = navRouterNode->GetPattern<NavRouterPattern>();
    EXPECT_EQ(navRouterPattern->GetRouteInfo(), nullptr);
    // Make sure shallowBuilder is false
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    EXPECT_EQ(navDestinationPattern->GetShallowBuilder(), nullptr);
    // Make sure destinationContent is false
    EXPECT_EQ(navDestinationNode->GetContentNode(), nullptr);
    navRouterNode->AddNavDestinationToNavigation();
}

/*
 * @tc.name: AddNavDestinationToNavigation004
 * @tc.desc: Test AddNavDestinationToNavigation and make the logic as follows:
 *               routeInfo is false
 *               navDestination is true
 *               shallowBuilder is true
 *               navRouteMode is NavRouteMode::PUSH
 *               destinationContent is true
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, AddNavDestinationToNavigation004, TestSize.Level1)
{
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    // Make navigationNode not NULL
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterNode->weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    // Make navDestination true
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navRouterNode->navDestinationNode_ = navDestinationNode;
    // Make shallowBuilder true
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    auto deepRender = []() -> RefPtr<UINode> {
        return ViewStackProcessor::GetInstance()->Finish();
    };
    navDestinationPattern->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender));
    auto navRouterPattern = navRouterNode->GetPattern<NavRouterPattern>();
    // Make navRouteMode NavRouteMode::PUSH
    navRouterPattern->mode_ = NavRouteMode::PUSH;
    // Make destinationContent true
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    navDestinationNode->contentNode_ = titleBarNode;
    
    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(navRouterNode->GetNavDestinationNode());
    auto currentNavDestination =
        AceType::DynamicCast<NavDestinationGroupNode>(navigationPattern->GetNavDestinationNode());
    EXPECT_NE(currentNavDestination, navDestinationNodeTest);
    EXPECT_EQ(navRouterPattern->GetRouteInfo(), nullptr);
    // Make sure shallowBuilder is true
    EXPECT_NE(navDestinationPattern->GetShallowBuilder(), nullptr);
    // Make sure navRouteMode is NavRouteMode::PUSH
    EXPECT_EQ(navRouterPattern->GetNavRouteMode(), NavRouteMode::PUSH);
    // Make sure destinationContent is true
    EXPECT_NE(navDestinationNode->GetContentNode(), nullptr);
    navRouterNode->AddNavDestinationToNavigation();
}

/*
 * @tc.name: AddNavDestinationToNavigation005
 * @tc.desc: Test AddNavDestinationToNavigation and make the logic as follows:
 *               routeInfo is false
 *               navDestination is true
 *               shallowBuilder is true
 *               navRouteMode is not NavRouteMode::PUSH
 *               destinationContent is true
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, AddNavDestinationToNavigation005, TestSize.Level1)
{
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    // Make navigationNode not NULL
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterNode->weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    // Make navDestination true
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navRouterNode->navDestinationNode_ = navDestinationNode;
    // Make shallowBuilder true
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    auto deepRender = []() -> RefPtr<UINode> {
        return ViewStackProcessor::GetInstance()->Finish();
    };
    navDestinationPattern->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender));
    // Make destinationContent true
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    navDestinationNode->contentNode_ = titleBarNode;

    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(navRouterNode->GetNavDestinationNode());
    auto currentNavDestination =
        AceType::DynamicCast<NavDestinationGroupNode>(navigationPattern->GetNavDestinationNode());
    EXPECT_NE(currentNavDestination, navDestinationNodeTest);
    auto navRouterPattern = navRouterNode->GetPattern<NavRouterPattern>();
    EXPECT_EQ(navRouterPattern->GetRouteInfo(), nullptr);
    // Make sure shallowBuilder is true
    EXPECT_NE(navDestinationPattern->GetShallowBuilder(), nullptr);
    // Make sure navRouteMode is not NavRouteMode::PUSH
    EXPECT_NE(navRouterPattern->GetNavRouteMode(), NavRouteMode::PUSH);
    // Make sure destinationContent is true
    EXPECT_NE(navDestinationNode->GetContentNode(), nullptr);
    navRouterNode->AddNavDestinationToNavigation();
}

/**
 * @tc.name: NavrouterTestNg0033
 * @tc.desc: Test TitleBarPattern::OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterPatternTestNg, NavrouterTestNg0033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navBar titleBarNode etc.
     */
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 11, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 22, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto menu = FrameNode::CreateFrameNode("menu", 34, AceType::MakeRefPtr<ButtonPattern>());
    auto subtitle = FrameNode::CreateFrameNode("subtitle", 35, AceType::MakeRefPtr<TextPattern>());
    auto title = FrameNode::CreateFrameNode("title", 36, AceType::MakeRefPtr<TextPattern>());
    auto toolBarNode = FrameNode::CreateFrameNode("toolBar", 44, AceType::MakeRefPtr<ButtonPattern>());

    auto buttonNode = FrameNode::CreateFrameNode("BackButton", 55, AceType::MakeRefPtr<ButtonPattern>());
    auto backButtonImageNode = FrameNode::CreateFrameNode("Image", 66, AceType::MakeRefPtr<ImagePattern>());

    navBar->AddChild(titleBarNode);
    auto pattern = titleBarNode->GetPattern<TitleBarPattern>();
    titleBarNode->backButton_ = buttonNode;
    titleBarNode->AddChild(titleBarNode->GetBackButton());
    titleBarNode->title_ = title;

    ASSERT_TRUE(buttonNode->children_.empty());
    backButtonImageNode->MountToParent(buttonNode);
    backButtonImageNode->MarkModifyDone();
    buttonNode->MarkModifyDone();
    /**
     * @tc.steps: step2. set properties then call pattern->OnModifyDone();.
     * @tc.expected: check whether the properties is correct.
     */
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleBarParentType_ =
        TitleBarParentType::NAV_DESTINATION;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleMode_ = NavigationTitleMode::MINI;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propHideBackButton_ = std::nullopt;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propNoPixMap_ = true;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propImageSource_ = ImageSourceInfo();
    pattern->OnModifyDone();
    ASSERT_NE(titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleBarParentType_.value(),
        TitleBarParentType::NAVBAR);

    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propImageSource_ = std::nullopt;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propHideBackButton_ = false;
    pattern->OnModifyDone();

    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propPixelMap_ = mockPixelMap;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propHideBackButton_ = true;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    navBar->GetLayoutProperty<NavBarLayoutProperty>()->propHideBackButton_ = true;
    pattern->OnModifyDone();
    EXPECT_EQ(buttonNode->GetLayoutProperty<ButtonLayoutProperty>()->propVisibility_.value(), VisibleType::GONE);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = AceType::MakeRefPtr<NavBarLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(titleBarNode)), geometryNode, layoutProperty);
    DirtySwapConfig config;
    auto algorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithm;
    /**
     * @tc.steps: step1. call pattern->OnDirtyLayoutWrapperSwap();.
     * @tc.expected: check whether the res is correct.
     */
    config.skipMeasure = true;
    config.skipLayout = true;
    auto res = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    ASSERT_FALSE(res);
    config.skipMeasure = true;
    config.skipLayout = false;
    res = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    ASSERT_FALSE(res);
}
} // namespace OHOS::Ace::NG