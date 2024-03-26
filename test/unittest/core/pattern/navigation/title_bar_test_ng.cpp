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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"

#define protected public
#define private public
#include "core/animation/spring_curve.h"
#include "core/animation/spring_motion.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/bar_item_event_hub.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float RET_VALUE = 0.0;
constexpr float OFFSET_HANDLED = 0.07;
constexpr float OFFSET_VALUE = 59.001;
constexpr float DEFAULT_SIZE_LENGTH = 20.0f;
constexpr Color FRONT_COLOR = Color(0xff0000ff);
const std::string BAR_ITEM_ETS_TAG = "TitleBar";
const std::string NAV_BAR_ITEM_ETS_TAG = "NavBar";
const std::string EMPTY_TEXT = "";
const std::string TITLE_BAR_TEXT = "title";
const std::string TITLE_BAR_NODE_MENU = "menu";
const std::string FRAME_ITEM_ETS_TAG = "FrameItem";
const std::string NAVDES_GROUP_NODE =  "navdestination_group_node";
const std::string NAVIGATION_MENU_ETS_TAG = "NavigationMenu";

} // namespace

class TitleBarTestNg : public testing::Test {
public:
    void InitTitleBarTestNg();
    void DestroyTitleBarObject();
    void CreateNavBar();

    RefPtr<TitleBarNode> frameNode_;
    RefPtr<TitleBarPattern> titleBarPattern_;
    RefPtr<TitleBarAccessibilityProperty> titleBarAccessibilityProperty_;
    RefPtr<NavBarNode> navBarNode_;
};

void TitleBarTestNg::InitTitleBarTestNg()
{
    frameNode_ =
        AceType::MakeRefPtr<TitleBarNode>(V2::TITLE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode_, nullptr);
    frameNode_->InitializePatternAndContext();
    titleBarPattern_ = frameNode_->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern_, nullptr);
    auto titleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->SetTitle(titleNode);
    titleBarAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<TitleBarAccessibilityProperty>();
    ASSERT_NE(titleBarAccessibilityProperty_, nullptr);
}

void TitleBarTestNg::CreateNavBar()
{
    std::string barTag = NAV_BAR_ITEM_ETS_TAG;
    auto navBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    navBarNode_ = NavBarNode::GetOrCreateNavBarNode(
        barTag, navBarNodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::NavBarPattern>(); });
    ASSERT_NE(navBarNode_, nullptr);
}

void TitleBarTestNg::DestroyTitleBarObject()
{
    frameNode_ = nullptr;
    titleBarPattern_ = nullptr;
    titleBarAccessibilityProperty_ = nullptr;
    navBarNode_ = nullptr;
}

/**
 * @tc.name: TitleBarPattern001
 * @tc.desc: Test TitleBarPattern interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern001, TestSize.Level1)
{
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    auto ret = titleBarPattern->CreateLayoutProperty();
    ASSERT_NE(ret, nullptr);
}

/**
 * @tc.name: CreateLayoutAlgorithm001
 * @tc.desc: Test CreateLayoutAlgorithm interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, CreateLayoutAlgorithm001, TestSize.Level1)
{
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    auto ret = titleBarPattern->CreateLayoutAlgorithm();
    ASSERT_NE(ret, nullptr);
}

/**
 * @tc.name: IsAtomicNode001
 * @tc.desc: Test IsAtomicNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, IsAtomicNode001, TestSize.Level1)
{
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    auto ret = titleBarPattern->IsAtomicNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: IsAtomicNode002
 * @tc.desc: Test IsAtomicNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, IsAtomicNode002, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>(barTag, nodeId);
    auto ret = titleBarNode->IsAtomicNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: GetTempTitleBarHeight001
 * @tc.desc: Test GetTempTitleBarHeight interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetTempTitleBarHeight001, TestSize.Level1)
{
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    auto ret = titleBarPattern->GetTempTitleBarHeight();
    EXPECT_EQ(ret, RET_VALUE);
}

/**
 * @tc.name: GetDefaultTitleBarHeight001
 * @tc.desc: Test GetDefaultTitleBarHeight interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetDefaultTitleBarHeight001, TestSize.Level1)
{
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    auto ret = titleBarPattern->GetDefaultTitleBarHeight();
    EXPECT_EQ(ret, RET_VALUE);
}

/**
 * @tc.name: GetTempTitleOffsetY001
 * @tc.desc: Test GetTempTitleOffsetY interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetTempTitleOffsetY001, TestSize.Level1)
{
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    auto ret = titleBarPattern->GetTempTitleOffsetY();
    EXPECT_EQ(ret, RET_VALUE);
}

/**
 * @tc.name: GetTempSubTitleOffsetY001
 * @tc.desc: Test GetTempSubTitleOffsetY interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetTempSubTitleOffsetY001, TestSize.Level1)
{
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    auto ret = titleBarPattern->GetTempSubTitleOffsetY();
    EXPECT_EQ(ret, RET_VALUE);
}

/**
 * @tc.name: GetMaxTitleBarHeight001
 * @tc.desc: Test GetMaxTitleBarHeight interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetMaxTitleBarHeight001, TestSize.Level1)
{
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    auto ret = titleBarPattern->GetMaxTitleBarHeight();
    EXPECT_EQ(ret, RET_VALUE);
}

/**
 * @tc.name: IsInitialTitle001
 * @tc.desc: Test IsInitialTitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, IsInitialTitle001, TestSize.Level1)
{
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    titleBarPattern->IsInitialTitle();
    EXPECT_EQ(titleBarPattern->isInitialTitle_, true);
}

/**
 * @tc.name: MarkIsInitialTitle001
 * @tc.desc: Test MarkIsInitialTitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, MarkIsInitialTitle001, TestSize.Level1)
{
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    titleBarPattern->MarkIsInitialTitle(true);
    EXPECT_EQ(titleBarPattern->isInitialTitle_, true);
}

/**
 * @tc.name: IsInitialSubtitle001
 * @tc.desc: Test IsInitialSubtitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, IsInitialSubtitle001, TestSize.Level1)
{
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    auto ret = titleBarPattern->IsInitialSubtitle();
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: MarkIsInitialSubtitle001
 * @tc.desc: Test MarkIsInitialSubtitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, MarkIsInitialSubtitle001, TestSize.Level1)
{
    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    titleBarPattern->MarkIsInitialSubtitle(true);
    EXPECT_EQ(titleBarPattern->isInitialSubtitle_, true);
}

/**
 * @tc.name: SetBackButton001
 * @tc.desc: Test SetBackButton interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, SetBackButton001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>(barTag, nodeId);
    titleBarNode->SetBackButton(nullptr);
    EXPECT_EQ(titleBarNode->backButton_, nullptr);
}

/**
 * @tc.name: SetTitle001
 * @tc.desc: Test SetTitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, SetTitle001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>(barTag, nodeId);
    titleBarNode->SetTitle(nullptr);
    EXPECT_EQ(titleBarNode->title_, nullptr);
}

/**
 * @tc.name: GetTitle001
 * @tc.desc: Test GetTitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetTitle001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>(barTag, nodeId);
    auto ret = titleBarNode->GetTitle();
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: SetSubtitle001
 * @tc.desc: Test SetSubtitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, SetSubtitle001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>(barTag, nodeId);
    titleBarNode->SetSubtitle(nullptr);
    EXPECT_EQ(titleBarNode->subtitle_, nullptr);
}

/**
 * @tc.name: SetMenu001
 * @tc.desc: Test SetMenu interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, SetMenu001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>(barTag, nodeId);
    titleBarNode->SetMenu(nullptr);
    EXPECT_EQ(titleBarNode->menu_, nullptr);
}

/**
 * @tc.name: GetMenu001
 * @tc.desc: Test GetMenu interface.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetMenu001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>(barTag, nodeId);
    auto ret = titleBarNode->GetMenu();
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: GetOrCreateTitleBarNode001
 * @tc.desc: Test create title bar node.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetOrCreateTitleBarNode001, TestSize.Level1)
{
    ElementRegister::GetInstance()->Clear();
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<TitleBarNode>(barTag, nodeId);
    auto frameNode = FrameNode::GetFrameNode(barTag, nodeId);
    EXPECT_EQ(frameNode, nullptr);
    RefPtr<TitleBarNode> titleBarNode = barNode->GetOrCreateTitleBarNode(barTag, nodeId, nullptr);
    ASSERT_NE(titleBarNode, nullptr);
}

/**
 * @tc.name: TitleBarAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of titleBar.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarAccessibilityPropertyGetText001, TestSize.Level1)
{
    InitTitleBarTestNg();
    EXPECT_EQ(titleBarAccessibilityProperty_->GetText(), "");
    auto titleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(titleNode, nullptr);
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(TITLE_BAR_TEXT);
    frameNode_->SetTitle(titleNode);
    EXPECT_EQ(titleBarAccessibilityProperty_->GetText(), TITLE_BAR_TEXT);
    DestroyTitleBarObject();
}

/**
 * @tc.name: TitleBarPattern002
 * @tc.desc: Test ProcessTittleDragStart function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern002, TestSize.Level1)
{
    constexpr float offset = 200.0f;
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    frameNode_->GetSubtitle();
    titleBarPattern_->ProcessTitleDragStart(offset);
    EXPECT_EQ(titleBarPattern_->GetTempTitleBarHeight(), titleBarPattern_->maxTitleBarHeight_);
}

/**
 * @tc.name: TitleBarPatternProcessTitleDragStartTest002
 * @tc.desc: Test ProcessTitleDragStart function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternProcessTitleDragStartTest002, TestSize.Level1)
{
    constexpr float offset = 200.0f;
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    frameNode_->GetSubtitle();
    titleBarPattern_->springController_ = nullptr;
    titleBarPattern_->animator_  = nullptr;
    titleBarPattern_->ProcessTitleDragStart(offset);
    EXPECT_EQ(titleBarPattern_->GetTempTitleBarHeight(), titleBarPattern_->maxTitleBarHeight_);

    titleBarPattern_->springMotion_ = nullptr;
    titleBarPattern_->SpringAnimation(100.0f, 0);
    titleBarPattern_->AnimateTo(offset);
    titleBarPattern_->ProcessTitleDragStart(offset);
    EXPECT_EQ(titleBarPattern_->GetTempTitleBarHeight(), titleBarPattern_->maxTitleBarHeight_);
}

/**
 * @tc.name: TitleBarPattern003
 * @tc.desc: Test ProcessTittleDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern003, TestSize.Level1)
{
    constexpr float offset = 190.0f;
    InitTitleBarTestNg();
    frameNode_->GetSubtitle();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    titleBarPattern_->ProcessTitleDragUpdate(offset);
    titleBarPattern_->ProcessTitleDragEnd();
    titleBarPattern_->SetTempTitleOffsetY();
    EXPECT_EQ(titleBarPattern_->GetTempTitleOffsetY(), titleBarPattern_->maxTitleOffsetY_);
    titleBarPattern_->SetTempSubTitleOffsetY();
    EXPECT_EQ(titleBarPattern_->GetTempSubTitleOffsetY(), titleBarPattern_->maxTitleOffsetY_);
}

/**
 * @tc.name: TitleBarPattern004
 * @tc.desc: Test SpringAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern004, TestSize.Level1)
{
    constexpr float startPos = 100.0f;
    float mass = 1.0f;
    float stiffness = 228.0f;
    float damping = 30.0f;

    auto titleBarPattern = AceType::MakeRefPtr<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY = AceType::MakeRefPtr<SpringProperty>(mass, stiffness, damping);
    titleBarPattern->springMotion_ = AceType::MakeRefPtr<SpringMotion>(startPos, 0, 0, DEFAULT_OVER_SPRING_PROPERTY);
    titleBarPattern->SpringAnimation(startPos, 0);
    titleBarPattern->SetOverDragOffset(startPos);
    EXPECT_EQ(titleBarPattern->GetOverDragOffset(), startPos);
}

/**
 * @tc.name: TitleBarPattern005
 * @tc.desc: Test TransformScale function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern005, TestSize.Level1)
{
    constexpr float overDragOffset = 100.0f;
    InitTitleBarTestNg();
    CreateNavBar();
    /**
     * @tc.case: case1.Test title transform scale.
     */
    auto titleNode = frameNode_->GetTitle();
    ASSERT_NE(titleNode, nullptr);
    auto title = AceType::DynamicCast<FrameNode>(titleNode);
    titleBarPattern_->TransformScale(overDragOffset, title);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateTransformScale(VectorF(1.0f, 1.0f));
    EXPECT_EQ(renderContext->GetTransformScale(), VectorF(1.0f, 1.0f));
}

/**
 * @tc.name: TitleBarPattern006
 * @tc.desc: Test AnimateTo function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern006, TestSize.Level1)
{
    InitTitleBarTestNg();
    CreateNavBar();
    titleBarPattern_->AnimateTo(0);
    EXPECT_NE(titleBarPattern_->animator_, nullptr);
}

/**
 * @tc.name: TitleBarPattern007
 * @tc.desc: Test CalculateHandledOffsetMinTitle function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern007, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    float offset = 0.07f;
    float lastCordScrollOffset = 56.0001f;
    EXPECT_EQ(titleBarPattern->CalculateHandledOffsetMinTitle(offset, lastCordScrollOffset), RET_VALUE);
}

/**
 * @tc.name: TitleBarPattern008
 * @tc.desc: Test CalculateHandledOffsetMinTitle function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern008, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    float offset = 0.07f;
    float lastCordScrollOffset = 0.0001f;
    EXPECT_EQ(titleBarPattern->CalculateHandledOffsetMinTitle(offset, lastCordScrollOffset), RET_VALUE);
}

/**
 * @tc.name: TitleBarPattern009
 * @tc.desc: Test CalculateHandledOffsetMinTitle function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern009, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    float offset = 0.07f;
    float lastCordScrollOffset = 56.01f;
    titleBarPattern->maxTitleBarHeight_ = 59.001f;
    EXPECT_EQ(titleBarPattern->CalculateHandledOffsetMinTitle(offset, lastCordScrollOffset), OFFSET_HANDLED);
}

/**
 * @tc.name: TitleBarPattern010
 * @tc.desc: Test CalculateHandledOffsetMaxTitle function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern010, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    float offset = 0.07f;
    float lastCordScrollOffset = 56.0001f;
    EXPECT_EQ(titleBarPattern->CalculateHandledOffsetMaxTitle(offset, lastCordScrollOffset), RET_VALUE);
}

/**
 * @tc.name: TitleBarPattern011
 * @tc.desc: Test CalculateHandledOffsetMaxTitle function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern011, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    float offset = 0.07f;
    float lastCordScrollOffset = 0.0001f;
    titleBarPattern->maxTitleBarHeight_ = 59.001f;
    EXPECT_EQ(titleBarPattern->CalculateHandledOffsetMaxTitle(offset, lastCordScrollOffset), OFFSET_VALUE);
}

/**
 * @tc.name: TitleBarPattern013
 * @tc.desc: Test CalculateHandledOffsetBetweenMinAndMaxTitle function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern013, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    float offset = 0.07f;
    float lastCordScrollOffset = 0.0001f;
    EXPECT_EQ(titleBarPattern->CalculateHandledOffsetBetweenMinAndMaxTitle(offset, lastCordScrollOffset), RET_VALUE);
}

/**
 * @tc.name: TitleBarPattern014
 * @tc.desc: Test CalculateHandledOffsetBetweenMinAndMaxTitle function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern014, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    float offset = 0.07f;
    float lastCordScrollOffset = 0.01f;
    EXPECT_EQ(titleBarPattern->CalculateHandledOffsetBetweenMinAndMaxTitle(offset, lastCordScrollOffset), RET_VALUE);
}

/**
 * @tc.name: TitleBarPattern015
 * @tc.desc: Test SetTitlebarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern015, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    NavigationTitlebarOptions opt;
    titleBarPattern->SetTitlebarOptions(std::move(opt));
}

/**
 * @tc.name: TitleBarPattern016
 * @tc.desc: Test SetTitlebarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern016, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    NavigationTitlebarOptions opt;
    opt.bgOptions.color = std::make_optional(FRONT_COLOR);
    titleBarPattern->SetTitlebarOptions(std::move(opt));
}

/**
 * @tc.name: TitleBarPattern017
 * @tc.desc: Test SetTitlebarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern017, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    NavigationTitlebarOptions opt;
    opt.bgOptions.blurStyle = std::make_optional(BlurStyle::NO_MATERIAL);
    titleBarPattern->SetTitlebarOptions(std::move(opt));
}

/**
 * @tc.name: TitleBarPattern018
 * @tc.desc: Test UpdateScaleByDragOverDragOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPattern018, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    float overDragOffset = -0.1;
    titleBarPattern->UpdateScaleByDragOverDragOffset(overDragOffset);
}

/**
 * @tc.name: TitleBarPatternProcessTitleDragStartTest019
 * @tc.desc: Test ProcessTitleDragStart function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternProcessTitleDragStartTest019, TestSize.Level1)
{
    constexpr float offset = 200.0f;
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarPattern_->overDragOffset_ = 11.01;
    titleBarPattern_->ProcessTitleDragStart(offset);
}

/**
 * @tc.name: TitleBarPatternProcessTitleDragStartTest020
 * @tc.desc: Test ProcessTitleDragEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternProcessTitleDragStartTest020, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarPattern_->overDragOffset_ = 11.01;
    titleBarPattern_->ProcessTitleDragEnd();
}

/**
 * @tc.name: TitleBarPatternProcessTitleDragStartTest021
 * @tc.desc: Test ProcessTitleDragEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternProcessTitleDragStartTest021, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarPattern_->CanOverDrag_ = true;
    titleBarPattern_->isTitleScaleChange_ = true;
    titleBarPattern_->ProcessTitleDragEnd();
}

/**
 * @tc.name: TitleBarPatternProcessTitleDragStartTest022
 * @tc.desc: Test ProcessTitleDragEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternProcessTitleDragStartTest022, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarPattern_->CanOverDrag_ = false;
    titleBarPattern_->isTitleScaleChange_ = false;
    titleBarPattern_->ProcessTitleDragEnd();
}

/**
 * @tc.name: TitleBarPatternOnCoordScrollStartTest023
 * @tc.desc: Test OnCoordScrollStart function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternOnCoordScrollStartTest023, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    titleBarPattern_->OnCoordScrollStart();
}

/**
 * @tc.name: TitleBarPatternOnCoordScrollStartTest024
 * @tc.desc: Test OnCoordScrollStart function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternOnCoordScrollStartTest024, TestSize.Level1)
{
    constexpr float offset = 190.0f;
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    titleBarPattern_->springMotion_ = nullptr;
    titleBarPattern_->SpringAnimation(100.0f, 0);
    titleBarPattern_->AnimateTo(offset);
    titleBarPattern_->OnCoordScrollStart();
}

/**
 * @tc.name: TitleBarPatternOnCoordScrollUpdateTest025
 * @tc.desc: Test OnCoordScrollUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternOnCoordScrollUpdateTest025, TestSize.Level1)
{
    constexpr float offset = -0.01f;
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    EXPECT_EQ(titleBarPattern_->OnCoordScrollUpdate(offset), RET_VALUE);
}

/**
 * @tc.name: TitleBarPatternOnCoordScrollUpdateTest026
 * @tc.desc: Test OnCoordScrollUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternOnCoordScrollUpdateTest026, TestSize.Level1)
{
    constexpr float offset = 0.01f;
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    EXPECT_EQ(titleBarPattern_->OnCoordScrollUpdate(offset), RET_VALUE);
}

/**
 * @tc.name: TitleBarPatterOnCoordScrollEndTest027
 * @tc.desc: Test OnCoordScrollEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatterOnCoordScrollEndTest027, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarPattern_->OnCoordScrollEnd();
}

/**
 * @tc.name: TitleBarPatterOnCoordScrollEndTest028
 * @tc.desc: Test OnCoordScrollEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatterOnCoordScrollEndTest028, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarPattern_->coordScrollOffset_ = 0.1f;
    titleBarPattern_->defaultTitleBarHeight_ = 0.003f;
    titleBarPattern_->maxTitleBarHeight_ = 0.008f;
    titleBarPattern_->OnCoordScrollEnd();
}

/**
 * @tc.name: TitleBarPatterOnCoordScrollEndTest029
 * @tc.desc: Test OnCoordScrollEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatterOnCoordScrollEndTest029, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarPattern_->coordScrollOffset_ = 0.1f;
    titleBarPattern_->maxTitleBarHeight_ = -0.008f;
    titleBarPattern_->OnCoordScrollEnd();
}

/**
 * @tc.name: TitleBarPatternUpdateTitleBarByCoordScrollTest030
 * @tc.desc: Test UpdateTitleBarByCoordScroll function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternUpdateTitleBarByCoordScrollTest030, TestSize.Level1)
{
    constexpr float offset = 190.0f;
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    titleBarPattern_->UpdateTitleBarByCoordScroll(offset);
}

/**
 * @tc.name: TitleBarPatternUpdateTitleBarByCoordScrollTest031
 * @tc.desc: Test SetTitleStyleByCoordScrollOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternUpdateTitleBarByCoordScrollTest031, TestSize.Level1)
{
    constexpr float offset = 190.0f;
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    titleBarPattern_->overDragOffset_ = 0.002f;
    titleBarPattern_->SetTitleStyleByCoordScrollOffset(offset);
}

/**
 * @tc.name: TitleBarPatternUpdateTitleBarByCoordScrollTest032
 * @tc.desc: Test SetTitleStyleByCoordScrollOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternUpdateTitleBarByCoordScrollTest032, TestSize.Level1)
{
    constexpr float offset = 190.0f;
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    titleBarPattern_->overDragOffset_ = 0.00001f;
    titleBarPattern_->SetTitleStyleByCoordScrollOffset(offset);
}

/**
 * @tc.name: TitleBarPatternTest033
 * @tc.desc: Test OnColorConfigurationUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternTest033, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    ASSERT_NE(backButton, nullptr);
    frameNode_->SetBackButton(backButton);
    titleBarPattern_->OnColorConfigurationUpdate();
}

/**
 * @tc.name: TitleBarPatternTest034
 * @tc.desc: Test OnColorConfigurationUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternTest034, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto backButton = FrameNode::CreateFrameNode("Navigator", 33, AceType::MakeRefPtr<TitleBarPattern>());
    ASSERT_NE(backButton, nullptr);
    frameNode_->SetBackButton(backButton);
    titleBarPattern_->OnColorConfigurationUpdate();
}

/**
 * @tc.name: TitleBarPatternTest035
 * @tc.desc: Test SetDefaultSubtitleOpacity function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternTest035, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto subtitle = FrameNode::CreateFrameNode("Navigator", 33, AceType::MakeRefPtr<TitleBarPattern>());
    ASSERT_NE(subtitle, nullptr);
    frameNode_->SetSubtitle(subtitle);
    titleBarPattern_->SetDefaultSubtitleOpacity();
}

/**
 * @tc.name: TitleBarPatternTest036
 * @tc.desc: Test SetDefaultSubtitleOpacity function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternTest036, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto subtitle = FrameNode::CreateFrameNode("Navigator", 33, AceType::MakeRefPtr<TitleBarPattern>());
    ASSERT_NE(subtitle, nullptr);
    frameNode_->SetSubtitle(subtitle);
    titleBarPattern_->defaultTitleBarHeight_ = 0.3f;
    titleBarPattern_->SetDefaultSubtitleOpacity();
}

/**
 * @tc.name: TitleBarPatternTest037
 * @tc.desc: Test SetTempSubTitleOffsetY function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternTest037, TestSize.Level1)
{
    InitTitleBarTestNg();
    titleBarPattern_->tempTitleOffsetY_ = 0.3;
    titleBarPattern_->SetTempSubTitleOffsetY();
    EXPECT_EQ(titleBarPattern_->tempSubTitleOffsetY_, RET_VALUE);
}

/**
 * @tc.name: TitleBarPatternTest038
 * @tc.desc: Test SetMaxTitleBarHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternTest038, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto subtitle = FrameNode::CreateFrameNode("Navigator", 33, AceType::MakeRefPtr<TitleBarPattern>());
    ASSERT_NE(subtitle, nullptr);
    frameNode_->SetSubtitle(subtitle);
    titleBarPattern_->SetMaxTitleBarHeight();
}

/**
 * @tc.name: MountMenu001
 * @tc.desc: Test MountMenu function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, MountMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    InitTitleBarTestNg();

    /**
     * @tc.steps: step2. Call MountMenu when TitleBarParentTypeValue is not NAV_DESTINATION.
     */
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleBarParentType(TitleBarParentType::NAVBAR);
    titleBarPattern_->MountMenu(frameNode_);
    EXPECT_EQ(frameNode_->GetLastChild(), nullptr);
}

/**
 * @tc.name: MountMenu002
 * @tc.desc: Test MountMenu function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, MountMenu002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    InitTitleBarTestNg();

    /**
     * @tc.steps: step2. Call MountMenu when TitleBarParentTypeValue is NAV_DESTINATION.
     * and MenuNodeOperationValue is REPLACE and PrevMenuIsCustomValue is true
     */
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleBarParentType(TitleBarParentType::NAV_DESTINATION);
    frameNode_->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
    frameNode_->UpdatePrevMenuIsCustom(true);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode = AceType::MakeRefPtr<FrameNode>(TITLE_BAR_NODE_MENU, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    frameNode_->SetMenu(menuNode);
    titleBarPattern_->MountMenu(frameNode_);
    ASSERT_NE(frameNode_->GetLastChild(), nullptr);
    EXPECT_EQ(frameNode_->GetLastChild()->GetTag(), TITLE_BAR_NODE_MENU);
}

/**
 * @tc.name: MountMenu003
 * @tc.desc: Test MountMenu function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, MountMenu003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    InitTitleBarTestNg();
    MockPipelineContext::SetUp();

    /**
     * @tc.steps: step2. Call MountMenu when TitleBarParentTypeValue is NAV_DESTINATION.
     * and MenuNodeOperationValue is REPLACE and PrevMenuIsCustomValue is false and HasMenuNodeId
     */
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleBarParentType(TitleBarParentType::NAV_DESTINATION);
    frameNode_->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
    frameNode_->UpdatePrevMenuIsCustom(false);
    titleBarPattern_->SetMenuNodeId(33);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    auto navdesGroupNode = AceType::MakeRefPtr<NavDestinationGroupNode>(NAVDES_GROUP_NODE,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavDestinationPattern>());
    ASSERT_NE(navdesGroupNode, nullptr);
    auto eventHub = navdesGroupNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    frameNode_->SetParent(navdesGroupNode);
    titleBarPattern_->SetMaxMenuNum(3);

    titleBarPattern_->MountMenu(frameNode_);
    ASSERT_NE(frameNode_->GetLastChild(), nullptr);
    EXPECT_EQ(frameNode_->GetLastChild()->GetTag(), NAVIGATION_MENU_ETS_TAG);
    MockPipelineContext::TearDown();
}


/**
 * @tc.name: MountMenu004
 * @tc.desc: Test MountMenu function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, MountMenu004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    InitTitleBarTestNg();

    /**
     * @tc.steps: step2. Call MountMenu when TitleBarParentTypeValue is NAV_DESTINATION.
     * and MenuNodeOperationValue is REPLACE and PrevMenuIsCustomValue is false and HasMenuNodeId is false
     */
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleBarParentType(TitleBarParentType::NAV_DESTINATION);
    frameNode_->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
    frameNode_->UpdatePrevMenuIsCustom(true);

    titleBarPattern_->MountMenu(frameNode_);
    EXPECT_EQ(frameNode_->GetLastChild(), nullptr);
}

/**
 * @tc.name:OnWindowSizeChanged001
 * @tc.desc: Test OnWindowSizeChanged function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, OnWindowSizeChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters
     */
    InitTitleBarTestNg();

    /**
     * @tc.steps: step2. Create related objects for titleBar
     */
    auto size = SizeF(DEFAULT_SIZE_LENGTH, DEFAULT_SIZE_LENGTH);
    auto navGeometryNode = frameNode_->GetGeometryNode();
    ASSERT_NE(navGeometryNode, nullptr);
    navGeometryNode->SetFrameSize(size);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    frameNode_->SetMenu(menuNode);
    auto buttonNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(buttonNode, nullptr);
    buttonNode->MountToParent(menuNode);
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>(FRAME_ITEM_ETS_TAG, nodeId);
    ASSERT_NE(barItemNode, nullptr);
    barItemNode->MountToParent(buttonNode);
    barItemNode->SetIsMoreItemNode(true);
    frameNode_->SetIsTitleMenuNodeShowing(true);

    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleBarParentType(TitleBarParentType::NAV_DESTINATION);

    bool isItemActionFired = false;
    auto barItemEventHub = barItemNode->GetEventHub<BarItemEventHub>();
    ASSERT_NE(barItemEventHub, nullptr);
    barItemEventHub->SetItemAction([&]() { isItemActionFired = true; });

    /**
     * @tc.steps: step3. call OnWindowSizeChanged func when PrevMenuIsCustom is true
     * @tc.expected: Set isItemActionFired is true
     */
    frameNode_->UpdatePrevMenuIsCustom(true);
    titleBarPattern_->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::ROTATION);
    EXPECT_TRUE(isItemActionFired);

    /**
     * @tc.steps: step4. call OnWindowSizeChanged func when PrevMenuIsCustom is false
     * @tc.expected: isItemActionFired is true
     */
    frameNode_->UpdatePrevMenuIsCustom(false);
    titleBarPattern_->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::ROTATION);
    EXPECT_TRUE(isItemActionFired);
}

} // namespace OHOS::Ace::NG
