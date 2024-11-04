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

#define protected public
#define private public

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"

#include "core/animation/spring_curve.h"
#include "core/animation/spring_motion.h"

#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/bar_item_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
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
const CalcDimension DEFAULT_PADDING = 24.0_vp;
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
 * @tc.name: TitleBarPatternTest039
 * @tc.desc: Test SetTitlebarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternTest039, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    NavigationTitlebarOptions opt;
    opt.brOptions.barStyle = std::make_optional(BarStyle::STACK);
    titleBarPattern->SetTitlebarOptions(std::move(opt));
    auto options = titleBarPattern->GetTitleBarOptions();
    EXPECT_TRUE(options.brOptions.barStyle.has_value());
}

/**
 * @tc.name: TitleBarPatternTest040
 * @tc.desc: Test SetTitlebarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternTest040, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    NavigationTitlebarOptions opt;
    opt.brOptions.barStyle = std::make_optional(BarStyle::STANDARD);
    titleBarPattern->SetTitlebarOptions(std::move(opt));
    auto options = titleBarPattern->GetTitleBarOptions();
    EXPECT_TRUE(options.brOptions.barStyle.has_value());
}

/**
 * @tc.name: TitleBarPatternTest041
 * @tc.desc: Test SetTitlebarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternTest041, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    NavigationTitlebarOptions opt;
    opt.brOptions.paddingStart = std::make_optional(DEFAULT_PADDING);
    opt.brOptions.paddingEnd = std::make_optional(DEFAULT_PADDING);
    titleBarPattern->SetTitlebarOptions(std::move(opt));
    auto options = titleBarPattern->GetTitleBarOptions();
    EXPECT_TRUE(options.brOptions.paddingStart.has_value());
    EXPECT_TRUE(options.brOptions.paddingEnd.has_value());
}

/**
 * @tc.name: TitleBarPatternTest042
 * @tc.desc: Test SetTitlebarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternTest042, TestSize.Level1)
{
     /**
     * @tc.steps: step1. initialize parameters.
     */
    InitTitleBarTestNg();

    /**
     * @tc.steps: step2. Get options default values.
     */
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    auto options = titleBarPattern->GetTitleBarOptions();
    EXPECT_FALSE(options.brOptions.paddingStart.has_value());
    EXPECT_FALSE(options.brOptions.paddingEnd.has_value());
}

/**
 * @tc.name:SetMenu002
 * @tc.desc: Test SetMenu function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, SetMenu002, TestSize.Level1)
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
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
            V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    barItemNode->MountToParent(buttonNode);
    barItemNode->SetIsMoreItemNode(true);

    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleBarParentType(TitleBarParentType::NAV_DESTINATION);
}

/**
 * @tc.name: TitleBarPatternAnimateToTest001
 * @tc.desc: Test AnimateTo function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternAnimateToTest001, TestSize.Level1)
{
    constexpr float offset = 200.0f;
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::FREE);
    ASSERT_EQ(titleBarPattern_->animation_, nullptr);
    titleBarPattern_->AnimateTo(offset);
    ASSERT_NE(titleBarPattern_->animation_, nullptr);
    titleBarPattern_->OnCoordScrollStart();
    ASSERT_EQ(titleBarPattern_->animation_, nullptr);
}

/**
 * @tc.name: TitleBarPatternSpringAnimationTest001
 * @tc.desc: Test SpringAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternSpringAnimationTest001, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::FREE);
    ASSERT_EQ(titleBarPattern_->springAnimation_, nullptr);
    titleBarPattern_->SpringAnimation(100.0f, 0);
    ASSERT_NE(titleBarPattern_->springAnimation_, nullptr);
    titleBarPattern_->OnCoordScrollStart();
    ASSERT_EQ(titleBarPattern_->springAnimation_, nullptr);
}

/**
 * @tc.name: TitleBarPatternOnModifyDone001
 * @tc.desc: Increase the coverage of OnModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternOnModifyDone001, TestSize.Level1)
{
    InitTitleBarTestNg();
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::FREE);
    titleBarPattern_->isInitialTitle_ = false;
    titleBarPattern_->isTitleChanged_ = true;
    titleBarPattern_->tempTitleBarHeight_ = 10.0_vp;
    // Make ConvertToPx return not 0.
    titleBarPattern_->tempTitleBarHeight_.SetUnit(DimensionUnit::NONE);
    EXPECT_EQ(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    EXPECT_TRUE(!titleBarPattern_->isInitialTitle_ && titleBarPattern_->isTitleChanged_);
    EXPECT_FALSE(NearEqual(titleBarPattern_->GetTempTitleBarHeight(),
        static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx())));
    EXPECT_FALSE(NearEqual(titleBarPattern_->GetTempTitleBarHeight(),
        static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx())));
    titleBarPattern_->OnModifyDone();
    
    titleBarPattern_->isTitleChanged_ = true;
    titleBarPattern_->tempTitleBarHeight_ = FULL_DOUBLE_LINE_TITLEBAR_HEIGHT;
    EXPECT_EQ(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    EXPECT_TRUE(!titleBarPattern_->isInitialTitle_ && titleBarPattern_->isTitleChanged_);
    EXPECT_TRUE(NearEqual(titleBarPattern_->GetTempTitleBarHeight(),
        static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx())));
    titleBarPattern_->OnModifyDone();
    
    titleBarPattern_->isTitleChanged_ = false;
    EXPECT_EQ(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    EXPECT_TRUE(!titleBarPattern_->isInitialTitle_ && !titleBarPattern_->isTitleChanged_);
    titleBarPattern_->OnModifyDone();

    titleBarPattern_->isInitialTitle_ = true;
    EXPECT_EQ(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    EXPECT_TRUE(titleBarPattern_->isInitialTitle_);
    titleBarPattern_->OnModifyDone();

    titleBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::MINI);
    EXPECT_NE(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    titleBarPattern_->OnModifyDone();
}

/**
 * @tc.name: TitleBarPatternUpdateScaleByDragOverDragOffset001
 * @tc.desc: Increase the coverage of UpdateScaleByDragOverDragOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, UpdateScaleByDragOverDragOffset001, TestSize.Level1)
{
    InitTitleBarTestNg();
    CreateNavBar();
    titleBarPattern_->GetHost()->SetParent(navBarNode_);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(titleBarPattern_->GetHost()->GetParent());
    ASSERT_NE(navBarNode, nullptr);
    navBarNode->propPrevTitleIsCustom_ = false;
    float overDragOffset = 10.0f;
    EXPECT_FALSE(Negative(overDragOffset));
    EXPECT_FALSE(navBarNode->GetPrevTitleIsCustomValue(true));
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(titleBarPattern_->GetHost());
    EXPECT_EQ(titleBarNode->GetSubtitle(), nullptr);
    titleBarPattern_->UpdateScaleByDragOverDragOffset(overDragOffset);

    titleBarNode->subtitle_ = FrameNode::CreateFrameNode("SubTitle", 101, AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(Negative(overDragOffset));
    EXPECT_FALSE(navBarNode->GetPrevTitleIsCustomValue(true));
    EXPECT_NE(titleBarNode->GetSubtitle(), nullptr);
    titleBarPattern_->UpdateScaleByDragOverDragOffset(overDragOffset);

    navBarNode->propPrevTitleIsCustom_ = true;
    EXPECT_FALSE(Negative(overDragOffset));
    EXPECT_TRUE(navBarNode->GetPrevTitleIsCustomValue(true));
    titleBarPattern_->UpdateScaleByDragOverDragOffset(overDragOffset);

    overDragOffset = -10.0f;
    EXPECT_TRUE(Negative(overDragOffset));
    titleBarPattern_->UpdateScaleByDragOverDragOffset(overDragOffset);
}

/**
 * @tc.name: GetFontSize001
 * @tc.desc: Increase the coverage of GetFontSize function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetFontSize001, TestSize.Level1)
{
    InitTitleBarTestNg();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    float singleHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern_->maxTitleBarHeight_ = singleHeight;
    EXPECT_FALSE(AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE));
    EXPECT_TRUE(NearZero(titleBarPattern_->maxTitleBarHeight_ - singleHeight));
    float offset = 0.0f;
    auto titleBarHeight = titleBarPattern_->defaultTitleBarHeight_ + offset;
    Dimension titleL = theme->GetTitleFontSizeBig();
    Dimension titleM = theme->GetTitleFontSize();
    auto tempFontSize = titleM.Value() + (titleBarHeight - singleHeight) * titleBarPattern_->fontSizeRatio_;
    EXPECT_FALSE(GreatNotEqual(tempFontSize, titleL.Value()));
    EXPECT_FALSE(LessNotEqual(tempFontSize, titleM.Value()));
    titleBarPattern_->GetFontSize(offset);

    titleBarPattern_->defaultTitleBarHeight_ = singleHeight - 2.0f;
    titleBarPattern_->fontSizeRatio_ = 1.0f;
    theme->titleFontSizeBig_.SetValue(1.0f);
    theme->titleFontSize_.SetValue(5.0f);
    EXPECT_TRUE(NearZero(titleBarPattern_->maxTitleBarHeight_ - singleHeight));
    titleBarHeight = titleBarPattern_->defaultTitleBarHeight_ + offset;
    titleL = theme->GetTitleFontSizeBig();
    titleM = theme->GetTitleFontSize();
    tempFontSize = titleM.Value() + (titleBarHeight - singleHeight) * titleBarPattern_->fontSizeRatio_;
    EXPECT_TRUE(GreatNotEqual(tempFontSize, titleL.Value()));
    EXPECT_TRUE(LessNotEqual(tempFontSize, titleM.Value()));
    titleBarPattern_->GetFontSize(offset);

    titleBarPattern_->maxTitleBarHeight_ = singleHeight - 2.0f;
    EXPECT_FALSE(NearZero(titleBarPattern_->maxTitleBarHeight_ - singleHeight));
    titleBarPattern_->GetFontSize(offset);

    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    EXPECT_TRUE(AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE));
    titleBarPattern_->GetFontSize(offset);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: TitleBarModifier001
 * @tc.desc: Test function of ResetProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TitleBarNode and TitleBarPattern.
     * @tc.expected: success to create titleBarNode and titleBarPattern,
     *               check some basic attributes of TitleBarPattern.
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    ASSERT_FALSE(titleBarPattern->IsFontSizeSettedByDeveloper());
    ASSERT_TRUE(titleBarPattern->shouldResetMainTitleProperty_);
    ASSERT_TRUE(titleBarPattern->shouldResetSubTitleProperty_);
    ASSERT_EQ(titleBarPattern->options_.textOptions.mainTitleApplyFunc, nullptr);
    ASSERT_EQ(titleBarPattern->options_.textOptions.subTitleApplyFunc, nullptr);

    /**
     * @tc.steps: step2. set TitleBarOptions to TitleBarPattern.
     * @tc.expected: success to set modifier apply functions.
     */
    NavigationTitlebarOptions options1;
    options1.textOptions.mainTitleApplyFunc = [](WeakPtr<FrameNode> weakNode) {};
    options1.textOptions.subTitleApplyFunc = [](WeakPtr<FrameNode> weakNode) {};
    titleBarPattern->SetTitlebarOptions(std::move(options1));
    ASSERT_NE(titleBarPattern->options_.textOptions.mainTitleApplyFunc, nullptr);
    ASSERT_NE(titleBarPattern->options_.textOptions.subTitleApplyFunc, nullptr);

    /**
     * @tc.steps: step3. set reset-flags to false, set emtpy TitleOptions.
     * @tc.expected: modifier apply functions were setted to nullptr, reset-flags change to true.
     */
    NavigationTitlebarOptions options2;
    titleBarPattern->shouldResetMainTitleProperty_ = false;
    titleBarPattern->shouldResetSubTitleProperty_ = false;
    titleBarPattern->SetTitlebarOptions(std::move(options2));
    ASSERT_TRUE(titleBarPattern->shouldResetMainTitleProperty_);
    ASSERT_TRUE(titleBarPattern->shouldResetSubTitleProperty_);
    ASSERT_EQ(titleBarPattern->options_.textOptions.mainTitleApplyFunc, nullptr);
    ASSERT_EQ(titleBarPattern->options_.textOptions.subTitleApplyFunc, nullptr);
}

/**
 * @tc.name: TitleBarModifier002
 * @tc.desc: Test ApplyTitleModifier function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TitleBarNode and TitleBarPattern.
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    /**
     * @tc.steps: step2. create TextNode and TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. update fontSize, maxFontSize, minFontSize.
     */
    static const Dimension TEST_FONT_SIZE(40);
    static const Dimension TEST_MAX_FONT_SIZE(50);
    static const Dimension TEST_MIN_FONT_SIZE(20);
    textLayoutProperty->UpdateFontSize(TEST_FONT_SIZE);
    ASSERT_TRUE(textLayoutProperty->HasFontSize());
    ASSERT_EQ(textLayoutProperty->GetFontSizeValue(Dimension()), TEST_FONT_SIZE);
    textLayoutProperty->UpdateAdaptMaxFontSize(TEST_MAX_FONT_SIZE);
    ASSERT_TRUE(textLayoutProperty->HasAdaptMaxFontSize());
    ASSERT_EQ(textLayoutProperty->GetAdaptMaxFontSizeValue(Dimension()), TEST_MAX_FONT_SIZE);
    textLayoutProperty->UpdateAdaptMinFontSize(TEST_MIN_FONT_SIZE);
    ASSERT_TRUE(textLayoutProperty->HasAdaptMinFontSize());
    ASSERT_EQ(textLayoutProperty->GetAdaptMinFontSizeValue(Dimension()), TEST_MIN_FONT_SIZE);

    /**
     * @tc.steps: step4. call ApplyTitleModifier with applyFunc.
     * @tc.expected: applyFunc will be called, and fontSize will be update, maxFontSize and minFontSize will be reset.
     */
    std::optional<RefPtr<FrameNode>> applyNode;
    auto applyFunc = [&applyNode](WeakPtr<FrameNode> weakNode) {
        auto textNode = weakNode.Upgrade();
        applyNode = textNode;
        auto property = textNode->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(property, nullptr);
        property->UpdateFontSize(Dimension(80));
    };
    titleBarPattern->ApplyTitleModifier(textNode, applyFunc, false);
    ASSERT_TRUE(applyNode.has_value());
    ASSERT_EQ(applyNode, textNode);
    ASSERT_TRUE(textLayoutProperty->HasFontSize());
    ASSERT_EQ(textLayoutProperty->GetFontSizeValue(Dimension()), Dimension(80));
    ASSERT_FALSE(textLayoutProperty->HasAdaptMaxFontSize());
    ASSERT_FALSE(textLayoutProperty->HasAdaptMinFontSize());

    /**
     * @tc.steps: step5. call ApplyTitleModifier with applyFunc.
     * @tc.expected: flag 'isFontSizeSettedByDeveloper' will be update.
     */
    ASSERT_FALSE(titleBarPattern->IsFontSizeSettedByDeveloper());
    titleBarPattern->ApplyTitleModifier(textNode, applyFunc, true);
    ASSERT_TRUE(titleBarPattern->IsFontSizeSettedByDeveloper());
}

/**
 * @tc.name: TitleBarModifier003
 * @tc.desc: Test ApplyTitleModifierIfNeeded function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TitleBarNode and TitleBarPattern.
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    /**
     * @tc.steps: step2. set modifier apply options.
     */
    std::optional<RefPtr<FrameNode>> mainTextNode;
    NavigationTitlebarOptions options;
    options.textOptions.mainTitleApplyFunc = [&mainTextNode](WeakPtr<FrameNode> weakNode) {
        auto textNode = weakNode.Upgrade();
        ASSERT_NE(textNode, nullptr);
        mainTextNode = textNode;
    };
    std::optional<RefPtr<FrameNode>> subTextNode;
    options.textOptions.subTitleApplyFunc = [&subTextNode](WeakPtr<FrameNode> weakNode) {
        auto textNode = weakNode.Upgrade();
        ASSERT_NE(textNode, nullptr);
        subTextNode = textNode;
    };
    titleBarPattern->SetTitlebarOptions(std::move(options));
    ASSERT_NE(titleBarPattern->options_.textOptions.mainTitleApplyFunc, nullptr);
    ASSERT_NE(titleBarPattern->options_.textOptions.subTitleApplyFunc, nullptr);

    /**
     * @tc.steps: step3. call ApplyTitleModifierIfNeeded.
     * @tc.expected: applyFunc will not be called.
     */
    titleBarPattern->ApplyTitleModifierIfNeeded(titleBarNode);
    ASSERT_FALSE(mainTextNode.has_value());
    ASSERT_FALSE(subTextNode.has_value());

    /**
     * @tc.steps: step4. set title and subtitle to TitleBar.
     */
    auto mainTitleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(mainTitleNode, nullptr);
    titleBarNode->SetTitle(mainTitleNode);
    auto subTitleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 3, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(subTitleNode, nullptr);
    titleBarNode->SetSubtitle(subTitleNode);

    /**
     * @tc.steps: step5. call ApplyTitleModifierIfNeeded again.
     * @tc.expected: applyFunc will be called.
     */
    titleBarPattern->ApplyTitleModifierIfNeeded(titleBarNode);
    ASSERT_TRUE(mainTextNode.has_value());
    ASSERT_EQ(mainTextNode.value(), mainTitleNode);
    ASSERT_TRUE(subTextNode.has_value());
    ASSERT_EQ(subTextNode.value(), subTitleNode);
}

/**
 * @tc.name: TitleBarPatternLongPress
 * @tc.desc: Test TitleBarPattern back button long press event.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternLongPress, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set backButton to TitleBarNode.
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<TitleBarPattern>());
    ASSERT_NE(backButton, nullptr);
    auto image = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 1, AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(image, nullptr);
    const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";
    auto imageLayoutProperty = image->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(IMAGE_SRC_URL));
    image->MountToParent(backButton);
    titleBarNode->SetBackButton(backButton);

    /**
     * @tc.steps: step2. Set fontScale to aging scale.
     */
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 2.0f;

    /**
     * @tc.steps: step3. call HandleLongPress.
     * @tc.expected: dialogNode != nullptr
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).Times(5).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else {
            return AceType::MakeRefPtr<AgingAdapationDialogTheme>();
        }
    });
    titleBarPattern->HandleLongPress(backButton);
    ASSERT_NE(titleBarPattern->dialogNode_, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialogNode = nullptr
     */
    titleBarPattern->HandleLongPressActionEnd();
    ASSERT_EQ(titleBarPattern->dialogNode_, nullptr);
}
} // namespace OHOS::Ace::NG
