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

#include "base/i18n/localization.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"

#include "core/animation/spring_curve.h"
#include "core/animation/spring_motion.h"

#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/bar_item_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float RET_VALUE = 0.0;
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
 * @tc.name: GetTempTitleBarHeight002
 * @tc.desc: Test GetTempTitleBarHeight interface after scroll by overDragging
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetTempTitleBarHeight002, TestSize.Level1)
{
    /*
     * @tc.steps: step1. init titleBar relative environment
     */
    InitTitleBarTestNg();
    MockPipelineContext::SetUp();
    auto subtitleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->SetSubtitle(subtitleNode);
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::FREE);
    auto fullTitleHeight = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern_->maxTitleBarHeight_ = fullTitleHeight;
    EXPECT_TRUE(NearEqual(titleBarPattern_->maxTitleBarHeight_, fullTitleHeight));
    titleBarPattern_->currentTitleBarHeight_ = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    EXPECT_TRUE(NearEqual(titleBarPattern_->currentTitleBarHeight_, fullTitleHeight));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    auto paddingTwoLines = theme->GetPaddingTopTwolines();
    auto titleSpaceVertical = static_cast<float>(theme->GetTitleSpaceVertical().ConvertToPx());
    auto titleSpace = fullTitleHeight - static_cast<float>(paddingTwoLines.ConvertToPx());
    auto titleNode = frameNode_->GetTitle();
    ASSERT_NE(titleNode, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(titleNode);
    ASSERT_NE(frameNode, nullptr);
    auto titleGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(titleGeometryNode, nullptr);
    auto titleHeight = titleGeometryNode->GetFrameSize().Height();
    frameNode = AceType::DynamicCast<FrameNode>(subtitleNode);
    ASSERT_NE(frameNode, nullptr);
    auto subtitleGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(subtitleGeometryNode, nullptr);
    auto subtitleHeight = subtitleGeometryNode->GetFrameSize().Height();
    auto titleRealHeight = titleHeight + subtitleHeight + titleSpaceVertical;
    float dividerOffset = 2.0f;
    auto titleOffsetY = (titleSpace - titleRealHeight +
        static_cast<float>(paddingTwoLines.ConvertToPx())) / dividerOffset;
    titleBarPattern_->SetCurrentTitleOffsetY(titleOffsetY);
    titleBarPattern_->initialTitleOffsetY_ = titleOffsetY;

    /*
     * @tc.steps: step2. start titleBar scroll and check whether tempTitleBarHeight is equal to fullTitleBarHeight.
     */
    titleBarPattern_->OnCoordScrollStart();
    auto startTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    EXPECT_TRUE(NearEqual(startTempTitleBarHeight, fullTitleHeight));

    /*
     * @tc.steps: step3. start overDragging and check whether tempTitleBarHeight is changing as well.
     */
    float overDragDistance = 100.0f;
    auto offsetHandled = titleBarPattern_->OnCoordScrollUpdate(overDragDistance);
    EXPECT_TRUE(NearZero(offsetHandled));
    auto overDragTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    auto expectedOverDragHeight = fullTitleHeight + overDragDistance / 6.0f;
    EXPECT_TRUE(NearEqual(overDragTempTitleBarHeight, expectedOverDragHeight));

    /*
     * @tc.steps: step4. overDrag again,
     * and check whether tempTitleBarHeight is changing as well.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(overDragDistance);
    EXPECT_TRUE(NearZero(offsetHandled));
    overDragTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    expectedOverDragHeight += overDragDistance / 6.0f;
    EXPECT_TRUE(NearEqual(overDragTempTitleBarHeight, expectedOverDragHeight));

    /*
     * @tc.steps: step4. recover drag state,
     * check whether tempTitleBarHeight is equal to fullTitleBarHeight.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(-overDragDistance * 2.0f);
    EXPECT_TRUE(NearZero(offsetHandled));
    overDragTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    expectedOverDragHeight = fullTitleHeight;
    EXPECT_TRUE(NearEqual(overDragTempTitleBarHeight, expectedOverDragHeight));

    /*
     * @tc.steps: step5. overdrag and send scroll end,
     * check whether tempTitleBarHeight recover to fullTitleBarHeight.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(overDragDistance * 3.0f);
    EXPECT_TRUE(NearZero(offsetHandled));
    titleBarPattern_->OnCoordScrollEnd();
    overDragTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    expectedOverDragHeight = fullTitleHeight;
    EXPECT_TRUE(NearEqual(overDragTempTitleBarHeight, expectedOverDragHeight));
}

/**
 * @tc.name: GetTempTitleBarHeight003
 * @tc.desc: Test GetTempTitleBarHeight after scrolling between min title height and max title height
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetTempTitleBarHeight003, TestSize.Level1)
{
    /*
     * @tc.steps: step1. init titleBar relative environment
     */
    InitTitleBarTestNg();
    MockPipelineContext::SetUp();
    auto subtitleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->SetSubtitle(subtitleNode);
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::FREE);
    auto fullTitleHeight = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern_->maxTitleBarHeight_ = fullTitleHeight;
    EXPECT_TRUE(NearEqual(titleBarPattern_->maxTitleBarHeight_, fullTitleHeight));
    titleBarPattern_->currentTitleBarHeight_ = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    EXPECT_TRUE(NearEqual(titleBarPattern_->currentTitleBarHeight_, fullTitleHeight));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    auto paddingTwoLines = theme->GetPaddingTopTwolines();
    auto titleSpaceVertical = static_cast<float>(theme->GetTitleSpaceVertical().ConvertToPx());
    auto titleSpace = fullTitleHeight - static_cast<float>(paddingTwoLines.ConvertToPx());
    auto titleNode = frameNode_->GetTitle();
    ASSERT_NE(titleNode, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(titleNode);
    ASSERT_NE(frameNode, nullptr);
    auto titleGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(titleGeometryNode, nullptr);
    auto titleHeight = titleGeometryNode->GetFrameSize().Height();
    frameNode = AceType::DynamicCast<FrameNode>(subtitleNode);
    ASSERT_NE(frameNode, nullptr);
    auto subtitleGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(subtitleGeometryNode, nullptr);
    auto subtitleHeight = subtitleGeometryNode->GetFrameSize().Height();
    auto titleRealHeight = titleHeight + subtitleHeight + titleSpaceVertical;
    float dividerOffset = 2.0f;
    auto titleOffsetY = (titleSpace - titleRealHeight +
        static_cast<float>(paddingTwoLines.ConvertToPx())) / dividerOffset;
    titleBarPattern_->SetCurrentTitleOffsetY(titleOffsetY);
    titleBarPattern_->initialTitleOffsetY_ = titleOffsetY;

    /*
     * @tc.steps: step2. start titleBar scroll and check whether tempTitleBarHeight is equal to fullTitleBarHeight.
     */
    titleBarPattern_->OnCoordScrollStart();
    auto startTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    EXPECT_TRUE(NearEqual(startTempTitleBarHeight, fullTitleHeight));

    /*
     * @tc.steps: step3. start dragging,
     * and check whether tempTitleBarHeight is changing between min and max titlebar height.
     */
    float dragDistance = -10.0f;
    auto offsetHandled = titleBarPattern_->OnCoordScrollUpdate(dragDistance);
    EXPECT_TRUE(NearEqual(offsetHandled, dragDistance));
    auto dragTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    auto expectedDragHeight = fullTitleHeight + dragDistance;
    EXPECT_TRUE(NearEqual(dragTempTitleBarHeight, expectedDragHeight));

    /*
     * @tc.steps: step4. drag again,
     * and check whether tempTitleBarHeight is changing between min and max titlebar height.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(dragDistance);
    EXPECT_TRUE(NearEqual(offsetHandled, dragDistance));
    dragTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    expectedDragHeight += dragDistance;
    EXPECT_TRUE(NearEqual(dragTempTitleBarHeight, expectedDragHeight));

    /*
     * @tc.steps: step4. recover drag state,
     * check whether tempTitleBarHeight is equal to fullTitleBarHeight.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(-dragDistance * 2.0f);
    EXPECT_TRUE(NearEqual(offsetHandled, -dragDistance * 2.0f));
    dragTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    expectedDragHeight = fullTitleHeight;
    EXPECT_TRUE(NearEqual(dragTempTitleBarHeight, expectedDragHeight));

    /*
     * @tc.steps: step5. drag and send scroll end,
     * check whether tempTitleBarHeight recover to fullTitleBarHeight.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(dragDistance);
    EXPECT_TRUE(NearEqual(offsetHandled, dragDistance));
    titleBarPattern_->OnCoordScrollEnd();
    dragTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    expectedDragHeight = fullTitleHeight;
    EXPECT_TRUE(NearEqual(dragTempTitleBarHeight, expectedDragHeight));
}

/**
 * @tc.name: GetTempTitleBarHeight004
 * @tc.desc: Test GetTempTitleBarHeight after scrolling and the target height is smaller than the minHeight
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetTempTitleBarHeight004, TestSize.Level1)
{
    /*
     * @tc.steps: step1. init titleBar relative environment
     */
    InitTitleBarTestNg();
    MockPipelineContext::SetUp();
    auto subtitleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->SetSubtitle(subtitleNode);
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::FREE);
    auto fullTitleHeight = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern_->SetMaxTitleBarHeight();
    EXPECT_TRUE(NearEqual(titleBarPattern_->maxTitleBarHeight_, fullTitleHeight));
    auto minTitleHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern_->minTitleHeight_ = minTitleHeight;
    EXPECT_TRUE(NearEqual(titleBarPattern_->minTitleHeight_, minTitleHeight));
    titleBarPattern_->currentTitleBarHeight_ = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    EXPECT_TRUE(NearEqual(titleBarPattern_->currentTitleBarHeight_, fullTitleHeight));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    auto paddingTwoLines = theme->GetPaddingTopTwolines();
    auto titleSpaceVertical = static_cast<float>(theme->GetTitleSpaceVertical().ConvertToPx());
    auto titleSpace = fullTitleHeight - static_cast<float>(paddingTwoLines.ConvertToPx());
    auto titleNode = frameNode_->GetTitle();
    ASSERT_NE(titleNode, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(titleNode);
    ASSERT_NE(frameNode, nullptr);
    auto titleGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(titleGeometryNode, nullptr);
    auto titleHeight = titleGeometryNode->GetFrameSize().Height();
    frameNode = AceType::DynamicCast<FrameNode>(subtitleNode);
    ASSERT_NE(frameNode, nullptr);
    auto subtitleGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(subtitleGeometryNode, nullptr);
    auto subtitleHeight = subtitleGeometryNode->GetFrameSize().Height();
    auto titleRealHeight = titleHeight + subtitleHeight + titleSpaceVertical;
    float dividerOffset = 2.0f;
    auto titleOffsetY = (titleSpace - titleRealHeight +
        static_cast<float>(paddingTwoLines.ConvertToPx())) / dividerOffset;
    titleBarPattern_->SetCurrentTitleOffsetY(titleOffsetY);
    titleBarPattern_->initialTitleOffsetY_ = titleOffsetY;

    /*
     * @tc.steps: step2. start titleBar scroll and check whether tempTitleBarHeight is equal to fullTitleBarHeight.
     */
    titleBarPattern_->OnCoordScrollStart();
    auto startTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    EXPECT_TRUE(NearEqual(startTempTitleBarHeight, fullTitleHeight));

    /*
     * @tc.steps: step3. start dragging to minHeight
     * and check whether tempTitleBarHeight is equal to minHeight.
     */
    float dragDistance = minTitleHeight - fullTitleHeight;
    auto offsetHandled = titleBarPattern_->OnCoordScrollUpdate(dragDistance);
    EXPECT_TRUE(NearEqual(offsetHandled, dragDistance));
    auto dragTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    auto expectedDragHeight = fullTitleHeight + dragDistance;
    EXPECT_TRUE(NearEqual(dragTempTitleBarHeight, expectedDragHeight));

    /*
     * @tc.steps: step4. drag again,
     * and check whether tempTitleBarHeight is changing between min and max titlebar height.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(dragDistance);
    EXPECT_TRUE(NearEqual(offsetHandled, 0.0f));
    dragTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    EXPECT_TRUE(NearEqual(dragTempTitleBarHeight, expectedDragHeight));

    /*
     * @tc.steps: step4. recover drag state,
     * check whether tempTitleBarHeight is equal to fullTitleBarHeight.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(-dragDistance * 2.0f);
    EXPECT_TRUE(NearEqual(offsetHandled, -dragDistance));
    dragTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    expectedDragHeight = fullTitleHeight;
    EXPECT_TRUE(NearEqual(dragTempTitleBarHeight, expectedDragHeight));

    /*
     * @tc.steps: step5. drag and send scroll end,
     * check whether tempTitleBarHeight recover to minTitleHeight.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(dragDistance);
    EXPECT_TRUE(NearEqual(offsetHandled, dragDistance));
    titleBarPattern_->OnCoordScrollEnd();
    dragTempTitleBarHeight = titleBarPattern_->GetTempTitleBarHeight();
    expectedDragHeight = minTitleHeight;
    EXPECT_TRUE(NearEqual(dragTempTitleBarHeight, expectedDragHeight));
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
 * @tc.name: GetTempTitleOffsetY002
 * @tc.desc: Test GetTempTitleOffsetY interface after overDragging
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetTempTitleOffsetY002, TestSize.Level1)
{
    /*
     * @tc.steps: step1. init titleBar relative environment
     */
    InitTitleBarTestNg();
    MockPipelineContext::SetUp();
    auto subtitleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->SetSubtitle(subtitleNode);
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::FREE);
    auto fullTitleHeight = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern_->SetMaxTitleBarHeight();
    EXPECT_TRUE(NearEqual(titleBarPattern_->maxTitleBarHeight_, fullTitleHeight));
    auto minTitleHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern_->minTitleHeight_ = minTitleHeight;
    EXPECT_TRUE(NearEqual(titleBarPattern_->minTitleHeight_, minTitleHeight));
    titleBarPattern_->currentTitleBarHeight_ = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    EXPECT_TRUE(NearEqual(titleBarPattern_->currentTitleBarHeight_, fullTitleHeight));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    auto paddingTwoLines = theme->GetPaddingTopTwolines();
    auto titleSpaceVertical = static_cast<float>(theme->GetTitleSpaceVertical().ConvertToPx());
    auto titleSpace = fullTitleHeight - static_cast<float>(paddingTwoLines.ConvertToPx());
    auto titleNode = frameNode_->GetTitle();
    ASSERT_NE(titleNode, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(titleNode);
    ASSERT_NE(frameNode, nullptr);
    auto titleGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(titleGeometryNode, nullptr);
    auto titleHeight = titleGeometryNode->GetFrameSize().Height();
    frameNode = AceType::DynamicCast<FrameNode>(subtitleNode);
    ASSERT_NE(frameNode, nullptr);
    auto subtitleGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(subtitleGeometryNode, nullptr);
    auto subtitleHeight = subtitleGeometryNode->GetFrameSize().Height();
    auto titleRealHeight = titleHeight + subtitleHeight + titleSpaceVertical;
    float dividerOffset = 2.0f;
    auto titleOffsetY = (titleSpace - titleRealHeight +
        static_cast<float>(paddingTwoLines.ConvertToPx())) / dividerOffset;
    titleBarPattern_->SetCurrentTitleOffsetY(titleOffsetY);
    titleBarPattern_->initialTitleOffsetY_ = titleOffsetY;
    
    /*
     * @tc.steps: step2. start titleBar scroll and check whether tempTitleOffsetY is equal to titleOffsetY.
     */
    titleBarPattern_->OnCoordScrollStart();
    auto startTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    EXPECT_TRUE(NearEqual(startTempTitleOffsetY, 0.f));

    /*
     * @tc.steps: step3. start overDragging and check whether tempTitleOffsetY is changing as well.
     */
    float overDragDistance = 100.0f;
    auto offsetHandled = titleBarPattern_->OnCoordScrollUpdate(overDragDistance);
    EXPECT_TRUE(NearZero(offsetHandled));
    auto overDragTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    auto expectedOverDragTitleOffsetY = titleOffsetY;
    EXPECT_TRUE(NearEqual(overDragTempTitleOffsetY, expectedOverDragTitleOffsetY));

    /*
     * @tc.steps: step4. overDrag again,
     * and check whether tempTitleOffsetY is changing as well.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(overDragDistance);
    EXPECT_TRUE(NearZero(offsetHandled));
    overDragTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    expectedOverDragTitleOffsetY = titleOffsetY;
    EXPECT_TRUE(NearEqual(overDragTempTitleOffsetY, expectedOverDragTitleOffsetY));

    /*
     * @tc.steps: step4. recover drag state,
     * check whether tempTitleOffsetY is equal to titleOffsetY.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(-overDragDistance * 2.0f);
    EXPECT_TRUE(NearZero(offsetHandled));
    overDragTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    expectedOverDragTitleOffsetY = titleOffsetY;
    EXPECT_TRUE(NearEqual(overDragTempTitleOffsetY, expectedOverDragTitleOffsetY));

    /*
     * @tc.steps: step5. overdrag and send scroll end,
     * check whether tempTitleOffsetY recover to 0.f.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(overDragDistance * 3.0f);
    EXPECT_TRUE(NearZero(offsetHandled));
    titleBarPattern_->OnCoordScrollEnd();
    overDragTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    expectedOverDragTitleOffsetY = titleOffsetY;
    EXPECT_TRUE(NearEqual(overDragTempTitleOffsetY, 0.f));
}

/**
 * @tc.name: GetTempTitleOffsetY003
 * @tc.desc: Test GetTempTitleOffsetY interface after scrolling between min title height and max title height
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetTempTitleOffsetY003, TestSize.Level1)
{
    /*
     * @tc.steps: step1. init titleBar relative environment
     */
    InitTitleBarTestNg();
    MockPipelineContext::SetUp();
    auto subtitleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->SetSubtitle(subtitleNode);
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::FREE);
    auto fullTitleHeight = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern_->SetMaxTitleBarHeight();
    EXPECT_TRUE(NearEqual(titleBarPattern_->maxTitleBarHeight_, fullTitleHeight));
    auto minTitleHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern_->minTitleHeight_ = minTitleHeight;
    EXPECT_TRUE(NearEqual(titleBarPattern_->minTitleHeight_, minTitleHeight));
    titleBarPattern_->currentTitleBarHeight_ = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    EXPECT_TRUE(NearEqual(titleBarPattern_->currentTitleBarHeight_, fullTitleHeight));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    auto paddingTwoLines = theme->GetPaddingTopTwolines();
    auto titleSpaceVertical = static_cast<float>(theme->GetTitleSpaceVertical().ConvertToPx());
    auto titleSpace = fullTitleHeight - static_cast<float>(paddingTwoLines.ConvertToPx());
    auto titleNode = frameNode_->GetTitle();
    ASSERT_NE(titleNode, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(titleNode);
    ASSERT_NE(frameNode, nullptr);
    auto titleGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(titleGeometryNode, nullptr);
    auto titleHeight = titleGeometryNode->GetFrameSize().Height();
    frameNode = AceType::DynamicCast<FrameNode>(subtitleNode);
    ASSERT_NE(frameNode, nullptr);
    auto subtitleGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(subtitleGeometryNode, nullptr);
    auto subtitleHeight = subtitleGeometryNode->GetFrameSize().Height();
    auto titleRealHeight = titleHeight + subtitleHeight + titleSpaceVertical;
    float dividerOffset = 2.0f;
    auto titleOffsetY = (titleSpace - titleRealHeight +
        static_cast<float>(paddingTwoLines.ConvertToPx())) / dividerOffset;
    titleBarPattern_->SetCurrentTitleOffsetY(titleOffsetY);
    titleBarPattern_->initialTitleOffsetY_ = titleOffsetY;
    
    /*
     * @tc.steps: step2. start titleBar scroll and check whether tempTitleOffsetY is equal to 0.f.
     */
    titleBarPattern_->OnCoordScrollStart();
    auto startTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    EXPECT_TRUE(NearEqual(startTempTitleOffsetY, 0.f));
    auto moveRatio = titleBarPattern_->moveRatio_;

    /*
     * @tc.steps: step3. start dragging
     * and check whether tempTitleOffsetY is changing between min and max title offsetY.
     */
    float dragDistance = -10.0f;
    auto offsetHandled = titleBarPattern_->OnCoordScrollUpdate(dragDistance);
    EXPECT_TRUE(NearEqual(offsetHandled, dragDistance));
    auto dragTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    auto expectedDragTitleOffsetY = titleOffsetY + dragDistance * moveRatio;
    EXPECT_TRUE(NearEqual(dragTempTitleOffsetY, expectedDragTitleOffsetY));

    /*
     * @tc.steps: step4. drag again,
     * and check whether tempTitleOffsetY is changing between min and max title offsetY.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(dragDistance);
    EXPECT_TRUE(NearEqual(offsetHandled, dragDistance));
    dragTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    expectedDragTitleOffsetY += dragDistance * moveRatio;
    EXPECT_TRUE(NearEqual(dragTempTitleOffsetY, expectedDragTitleOffsetY));

    /*
     * @tc.steps: step4. recover drag state,
     * check whether tempTitleOffsetY is equal to titleOffsetY.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(-dragDistance * 2.0f);
    EXPECT_TRUE(NearEqual(offsetHandled, -dragDistance * 2.0f));
    dragTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    expectedDragTitleOffsetY = titleOffsetY;
    EXPECT_TRUE(NearEqual(dragTempTitleOffsetY, expectedDragTitleOffsetY));

    /*
     * @tc.steps: step5. drag and send scroll end,
     * check whether tempTitleOffsetY recover to 0.f.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(dragDistance);
    EXPECT_TRUE(NearEqual(offsetHandled, dragDistance));
    titleBarPattern_->OnCoordScrollEnd();
    dragTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    expectedDragTitleOffsetY = titleOffsetY;
    EXPECT_TRUE(NearEqual(dragTempTitleOffsetY, 0.f));
}

/**
 * @tc.name: GetTempTitleOffsetY004
 * @tc.desc: Test GetTempTitleOffsetY interface after scrolling and the target height is smaller than the minHeight
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetTempTitleOffsetY004, TestSize.Level1)
{
    /*
     * @tc.steps: step1. init titleBar relative environment
     */
    InitTitleBarTestNg();
    MockPipelineContext::SetUp();
    auto subtitleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->SetSubtitle(subtitleNode);
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::FREE);
    auto fullTitleHeight = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern_->SetMaxTitleBarHeight();
    EXPECT_TRUE(NearEqual(titleBarPattern_->maxTitleBarHeight_, fullTitleHeight));
    auto minTitleHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern_->minTitleHeight_ = minTitleHeight;
    EXPECT_TRUE(NearEqual(titleBarPattern_->minTitleHeight_, minTitleHeight));
    titleBarPattern_->currentTitleBarHeight_ = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    EXPECT_TRUE(NearEqual(titleBarPattern_->currentTitleBarHeight_, fullTitleHeight));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    auto paddingTwoLines = theme->GetPaddingTopTwolines();
    auto titleSpaceVertical = static_cast<float>(theme->GetTitleSpaceVertical().ConvertToPx());
    auto titleSpace = fullTitleHeight - static_cast<float>(paddingTwoLines.ConvertToPx());
    auto titleNode = frameNode_->GetTitle();
    ASSERT_NE(titleNode, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(titleNode);
    ASSERT_NE(frameNode, nullptr);
    auto titleGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(titleGeometryNode, nullptr);
    auto titleHeight = titleGeometryNode->GetFrameSize().Height();
    frameNode = AceType::DynamicCast<FrameNode>(subtitleNode);
    ASSERT_NE(frameNode, nullptr);
    auto subtitleGeometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(subtitleGeometryNode, nullptr);
    auto subtitleHeight = subtitleGeometryNode->GetFrameSize().Height();
    auto titleRealHeight = titleHeight + subtitleHeight + titleSpaceVertical;
    float dividerOffset = 2.0f;
    auto titleOffsetY = (titleSpace - titleRealHeight +
        static_cast<float>(paddingTwoLines.ConvertToPx())) / dividerOffset;
    titleBarPattern_->SetCurrentTitleOffsetY(titleOffsetY);
    titleBarPattern_->initialTitleOffsetY_ = titleOffsetY;
    
    /*
     * @tc.steps: step2. start titleBar scroll and check whether tempTitleOffsetY is equal to 0.f.
     */
    titleBarPattern_->OnCoordScrollStart();
    auto startTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    EXPECT_TRUE(NearEqual(startTempTitleOffsetY, 0.f));
    auto moveRatio = titleBarPattern_->moveRatio_;

    /*
     * @tc.steps: step3. start dragging to minHeight
     * and check whether tempTitleOffsetY is equal to minHeight.
     */
    float dragDistance = minTitleHeight - fullTitleHeight;
    auto offsetHandled = titleBarPattern_->OnCoordScrollUpdate(dragDistance);
    EXPECT_TRUE(NearEqual(offsetHandled, dragDistance));
    auto dragTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    auto expectedDragTitleOffsetY = titleOffsetY + dragDistance * moveRatio;
    EXPECT_TRUE(NearEqual(dragTempTitleOffsetY, expectedDragTitleOffsetY));

    /*
     * @tc.steps: step4. drag again,
     * and check whether tempTitleOffsetY is equal to minHeight.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(dragDistance);
    EXPECT_TRUE(NearEqual(offsetHandled, 0.0f));
    dragTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    EXPECT_TRUE(NearEqual(dragTempTitleOffsetY, expectedDragTitleOffsetY));

    /*
     * @tc.steps: step4. recover drag state,
     * check whether tempTitleOffsetY is equal to titleOffsetY.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(-dragDistance * 2.0f);
    EXPECT_TRUE(NearEqual(offsetHandled, -dragDistance));
    dragTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    expectedDragTitleOffsetY = titleOffsetY;
    EXPECT_TRUE(NearEqual(dragTempTitleOffsetY, expectedDragTitleOffsetY));

    /*
     * @tc.steps: step5. drag and send scroll end,
     * check whether tempTitleOffsetY recover to min titleOffsetY.
     */
    offsetHandled = titleBarPattern_->OnCoordScrollUpdate(dragDistance);
    EXPECT_TRUE(NearEqual(offsetHandled, dragDistance));
    titleBarPattern_->OnCoordScrollEnd();
    dragTempTitleOffsetY = titleBarPattern_->GetTempTitleOffsetY();
    expectedDragTitleOffsetY = titleBarPattern_->minTitleOffsetY_;
    EXPECT_TRUE(NearEqual(dragTempTitleOffsetY, expectedDragTitleOffsetY));
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
    titleBarPattern->SetTitlebarOptions(opt);
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
    titleBarPattern->SetTitlebarOptions(opt);
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
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    opt.bgOptions.blurStyleOption = blurStyleOption;
    titleBarPattern->SetTitlebarOptions(opt);
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
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<ButtonPattern>());
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
    auto backButton = FrameNode::CreateFrameNode("Navigator", 33, AceType::MakeRefPtr<ButtonPattern>());
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
        FrameNode::CreateFrameNode("Navigator", 33, AceType::MakeRefPtr<TitleBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto titleBarPattern = frameNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    NavigationTitlebarOptions opt;
    opt.brOptions.barStyle = std::make_optional(BarStyle::STACK);
    titleBarPattern->SetTitlebarOptions(opt);
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
    titleBarPattern->SetTitlebarOptions(opt);
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
    titleBarPattern->SetTitlebarOptions(opt);
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
    titleBarPattern->SetTitlebarOptions(options1);
    ASSERT_NE(titleBarPattern->options_.textOptions.mainTitleApplyFunc, nullptr);
    ASSERT_NE(titleBarPattern->options_.textOptions.subTitleApplyFunc, nullptr);

    /**
     * @tc.steps: step3. set reset-flags to false, set emtpy TitleOptions.
     * @tc.expected: modifier apply functions were setted to nullptr, reset-flags change to true.
     */
    NavigationTitlebarOptions options2;
    titleBarPattern->shouldResetMainTitleProperty_ = false;
    titleBarPattern->shouldResetSubTitleProperty_ = false;
    titleBarPattern->SetTitlebarOptions(options2);
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
    titleBarPattern->SetTitlebarOptions(options);
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
 * @tc.name: TitleBarPatternOnModifyDone002
 * @tc.desc: Test SetBackButtonImgAboveVersionTen function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternOnModifyDone002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init titleBar environment and theme, set api version 12
     */
    MockPipelineContext::SetUp();
    InitTitleBarTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    MockContainer::SetUp();
    int32_t apiTargetVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step2. create backButtonNode and layoutProperty.
     */
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(backButtonNode, nullptr);
    frameNode_->SetBackButton(backButtonNode);
    auto backButtonImageNode = FrameNode::CreateFrameNode(V2::BACK_BUTTON_IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(backButtonImageNode, nullptr);
    backButtonImageNode->MountToParent(backButtonNode);
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    ImageSourceInfo srcImageSourceInfo = ImageSourceInfo("file://data/data/com.example.test/res/example.svg",
        Dimension(300.0), Dimension(200.0));
    titleBarLayoutProperty->UpdateImageSource(srcImageSourceInfo);
    bool titleBarHasImage = titleBarLayoutProperty->HasImageSource();
    ASSERT_NE(titleBarHasImage, false);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    titleBarLayoutProperty->UpdatePixelMap(pixelMap);

    titleBarLayoutProperty->UpdateIsValidImage(true);
    auto hasIsValidImage = titleBarLayoutProperty->HasIsValidImage();
    ASSERT_EQ(hasIsValidImage, true);
    auto curIsValidImage = titleBarLayoutProperty->GetIsValidImageValue();
    ASSERT_EQ(curIsValidImage, true);

    /**
     * @tc.steps: step3. call SetBackButtonImgAboveVersionTen.
     * @tc.expected: set image source info successfully and is equal to pixelMap.
     */
    titleBarPattern_->OnModifyDone();
    backButtonImageNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetChildren().front());
    ASSERT_NE(backButtonImageNode, nullptr);
    auto backButtonImageProperty = backButtonImageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(backButtonImageProperty, nullptr);
    auto hasImageSourceInfo = backButtonImageProperty->HasImageSourceInfo();
    ASSERT_NE(hasImageSourceInfo, false);
    auto imageSourceInfo = backButtonImageProperty->GetImageSourceInfoValue();
    auto isPixMap = imageSourceInfo.IsPixmap();
    ASSERT_NE(isPixMap, false);
    auto pixMapValue = imageSourceInfo.GetPixmap();
    ASSERT_NE(pixMapValue, nullptr);
    ASSERT_EQ(pixMapValue, pixelMap);

    auto expectColor = theme->GetIconColor();
    auto curColor = imageSourceInfo.GetFillColor();
    ASSERT_TRUE(curColor.has_value());
    EXPECT_EQ(expectColor, curColor.value());

    /**
     * @tc.steps: step4. recover api version
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    MockContainer::Current()->SetApiTargetVersion(apiTargetVersion);
    MockContainer::TearDown();
}

/**
 * @tc.name: TitleBarPatternOnModifyDone003
 * @tc.desc: Test SetBackButtonImgAboveVersionTen function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternOnModifyDone003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init titleBar environment and theme, set api version 12
     */
    MockPipelineContext::SetUp();
    InitTitleBarTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    MockContainer::SetUp();
    int32_t apiTargetVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step2. create backButtonNode and layoutProperty.
     */
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(backButtonNode, nullptr);
    frameNode_->SetBackButton(backButtonNode);
    auto backButtonImageNode = FrameNode::CreateFrameNode(V2::BACK_BUTTON_IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(backButtonImageNode, nullptr);
    backButtonImageNode->MountToParent(backButtonNode);
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    ImageSourceInfo srcImageSourceInfo = ImageSourceInfo("file://data/data/com.example.test/res/example.svg",
        Dimension(300.0), Dimension(200.0));
    titleBarLayoutProperty->UpdateImageSource(srcImageSourceInfo);
    bool titleBarHasImage = titleBarLayoutProperty->HasImageSource();
    ASSERT_NE(titleBarHasImage, false);

    titleBarLayoutProperty->UpdateIsValidImage(true);
    auto hasIsValidImage = titleBarLayoutProperty->HasIsValidImage();
    ASSERT_EQ(hasIsValidImage, true);
    auto curIsValidImage = titleBarLayoutProperty->GetIsValidImageValue();
    ASSERT_EQ(curIsValidImage, true);

    /**
     * @tc.steps: step3. call SetBackButtonImgAboveVersionTen.
     * @tc.expected: set image source info successfully and is equal to ImageSourceValue.
     */
    titleBarPattern_->OnModifyDone();
    backButtonImageNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetChildren().front());
    ASSERT_NE(backButtonImageNode, nullptr);
    auto backButtonImageProperty = backButtonImageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(backButtonImageProperty, nullptr);
    auto hasImageSourceInfo = backButtonImageProperty->HasImageSourceInfo();
    ASSERT_NE(hasImageSourceInfo, false);
    auto imageSourceInfo = backButtonImageProperty->GetImageSourceInfoValue();
    auto isPixMap = imageSourceInfo.IsPixmap();
    ASSERT_NE(isPixMap, true);

    auto expectColor = theme->GetIconColor();
    auto curColor = imageSourceInfo.GetFillColor();
    ASSERT_TRUE(curColor.has_value());
    EXPECT_EQ(expectColor, curColor.value());

    /**
     * @tc.steps: step4. recover api version
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    MockContainer::Current()->SetApiTargetVersion(apiTargetVersion);
    MockContainer::TearDown();
}

/**
 * @tc.name: TitleBarPatternOnModifyDone004
 * @tc.desc: Test SetBackButtonImgAboveVersionTen function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternOnModifyDone004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init titleBar environment and theme, set api version 9
     */
    MockPipelineContext::SetUp();
    InitTitleBarTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    MockContainer::SetUp();
    int32_t apiTargetVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));

    /**
     * @tc.steps: step2. create backButtonNode and layoutProperty.
     */
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(backButtonNode, nullptr);
    frameNode_->SetBackButton(backButtonNode);
    auto backButtonImageNode = FrameNode::CreateFrameNode(V2::BACK_BUTTON_IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(backButtonImageNode, nullptr);
    backButtonImageNode->MountToParent(backButtonNode);
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    ImageSourceInfo srcImageSourceInfo = ImageSourceInfo("file://data/data/com.example.test/res/example.svg",
        Dimension(300.0), Dimension(200.0));
    titleBarLayoutProperty->UpdateImageSource(srcImageSourceInfo);
    bool titleBarHasImage = titleBarLayoutProperty->HasImageSource();
    ASSERT_NE(titleBarHasImage, false);

    titleBarLayoutProperty->UpdateIsValidImage(true);
    auto hasIsValidImage = titleBarLayoutProperty->HasIsValidImage();
    ASSERT_EQ(hasIsValidImage, true);
    auto curIsValidImage = titleBarLayoutProperty->GetIsValidImageValue();
    ASSERT_EQ(curIsValidImage, true);

    /**
     * @tc.steps: step3. call SetBackButtonImgAboveVersionTen.
     * @tc.expected: set image source info successfully and is equal to ImageSourceValue.
     */
    titleBarPattern_->OnModifyDone();
    backButtonImageNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetChildren().front());
    ASSERT_NE(backButtonImageNode, nullptr);
    auto backButtonImageProperty = backButtonImageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(backButtonImageProperty, nullptr);
    auto hasImageSourceInfo = backButtonImageProperty->HasImageSourceInfo();
    ASSERT_NE(hasImageSourceInfo, false);
    auto imageSourceInfo = backButtonImageProperty->GetImageSourceInfoValue();
    auto isPixMap = imageSourceInfo.IsPixmap();
    ASSERT_NE(isPixMap, true);

    auto expectColor = theme->GetIconColor();
    auto curColor = imageSourceInfo.GetFillColor();
    ASSERT_TRUE(curColor.has_value());
    EXPECT_EQ(expectColor, curColor.value());

    /**
     * @tc.steps: step4. recover api version
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    MockContainer::Current()->SetApiTargetVersion(apiTargetVersion);
    MockContainer::TearDown();
}

/**
 * @tc.name: TitleBarPatternOnModifyDone005
 * @tc.desc: Test ApplyThemeIconSize function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternOnModifyDone005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init titleBar environment and theme
     */
    InitTitleBarTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    /**
     * @tc.steps: step2. create backButtonNode and layoutProperty.
     */
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(backButtonNode, nullptr);
    frameNode_->SetBackButton(backButtonNode);
    auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(symbolNode, nullptr);
    symbolNode->MountToParent(backButtonNode);
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(symbolProperty, nullptr);
    symbolProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    std::function callback = [](WeakPtr<NG::FrameNode> frameNode) {
        return;
    };
    titleBarLayoutProperty->SetBackIconSymbol(callback);

    /**
     * @tc.steps: step3. call ApplyThemeIconSize.
     * @tc.expected: update symbol icon size successfully and is equal to theme size.
     */
    titleBarPattern_->OnModifyDone();
    auto expectIconSize = theme->GetIconWidth();
    auto hasIconSize = symbolProperty->HasFontSize();
    ASSERT_NE(hasIconSize, false);
    Dimension defaultSize = 0.0_vp;
    auto curIconSize = symbolProperty->GetFontSizeValue(defaultSize);
    ASSERT_EQ(curIconSize, expectIconSize);
}

/**
 * @tc.name: SetDefaultTitleFontSize001
 * @tc.desc: Test SetDefaultTitleFontSize function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, SetDefaultTitleFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init titleBar environment and theme
     */
    InitTitleBarTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    /**
     * @tc.steps: step2. call SetDefaultTitleFontSize.
     * @tc.expected: defaultTitleFontSize_ is equal to theme size.
     */
    titleBarPattern_->SetDefaultTitleFontSize();
    auto expectedTitleFontSize = theme->GetTitleFontSize();
    ASSERT_EQ(titleBarPattern_->defaultTitleFontSize_, expectedTitleFontSize);
}

/**
 * @tc.name: GetSubTitleOffsetY001
 * @tc.desc: Test GetSubTitleOffsetY function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, GetSubTitleOffsetY001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init titleBar environment and theme
     */
    InitTitleBarTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    /**
     * @tc.steps: step2. call GetSubTitleOffsetY.
     * @tc.expected: defaultTitleFontSize_ is equal to theme size.
     */
    auto offsetY = titleBarPattern_->GetSubTitleOffsetY();
    ASSERT_EQ(offsetY, 0.f);
}

/**
 * @tc.name: OnColorConfigurationUpdate003
 * @tc.desc: Test OnColorConfigurationUpdate function in api version 12.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, OnColorConfigurationUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init titleBar environment and theme, set api version 12
     */
    InitTitleBarTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step2. create backButtonNode and layoutProperty.
     */
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(backButtonNode, nullptr);
    frameNode_->SetBackButton(backButtonNode);
    auto backButtonImageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(backButtonImageNode, nullptr);
    backButtonImageNode->MountToParent(backButtonNode);

    /**
     * @tc.steps: step3. call OnColorConfigurationUpdate.
     * @tc.expected: value is set successfully
     */
    titleBarPattern_->OnColorConfigurationUpdate();
    auto renderContext = backButtonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto backButtonPattern = backButtonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(backButtonPattern, nullptr);

    auto iconColor = theme->GetIconColor();
    backButtonImageNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetChildren().front());
    ASSERT_NE(backButtonImageNode, nullptr);
    auto backButtonImageRender = backButtonImageNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(backButtonImageRender, nullptr);
    auto hasSvgFillColor = backButtonImageRender->HasSvgFillColor();
    ASSERT_NE(hasSvgFillColor, false);
    auto defaultColor = Color::TRANSPARENT;
    auto svgFillColor = backButtonImageRender->GetSvgFillColorValue(defaultColor);
    ASSERT_EQ(svgFillColor, iconColor);

    auto backButtonColor = theme->GetCompBackgroundColor();
    auto hasBackgroundColor = renderContext->HasBackgroundColor();
    ASSERT_NE(hasBackgroundColor, false);
    auto backgroundColor = renderContext->GetBackgroundColorValue();
    ASSERT_EQ(backgroundColor, backButtonColor);

    auto backgroundPressedColor = theme->GetBackgroundPressedColor();
    auto backgroundHoverColor = theme->GetBackgroundHoverColor();
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    auto blendClickColor = backButtonPattern->GetColorFromType(buttonTheme, 0);
    auto blendHoverColor = backButtonPattern->GetColorFromType(buttonTheme, 1);
    ASSERT_EQ(blendClickColor, backgroundPressedColor);
    ASSERT_EQ(backgroundHoverColor, blendHoverColor);

    /**
     * @tc.steps: step4. recover api version
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: OnColorConfigurationUpdate004
 * @tc.desc: Test OnColorConfigurationUpdate function in api version 10.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, OnColorConfigurationUpdate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init titleBar environment and theme, set api version 10
     */
    InitTitleBarTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));

    /**
     * @tc.steps: step2. create backButtonNode and layoutProperty.
     */
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(backButtonNode, nullptr);
    frameNode_->SetBackButton(backButtonNode);
    auto backButtonImageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(backButtonImageNode, nullptr);
    backButtonImageNode->MountToParent(backButtonNode);

    /**
     * @tc.steps: step3. call OnColorConfigurationUpdate.
     * @tc.expected: defaultTitleFontSize_ is equal to theme size.
     */
    titleBarPattern_->OnColorConfigurationUpdate();
    auto iconColor = theme->GetBackButtonIconColor();
    backButtonImageNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetChildren().front());
    ASSERT_NE(backButtonImageNode, nullptr);
    auto backButtonImageRender = backButtonImageNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(backButtonImageRender, nullptr);
    auto hasSvgFillColor = backButtonImageRender->HasSvgFillColor();
    ASSERT_NE(hasSvgFillColor, false);
    auto defaultColor = Color::TRANSPARENT;
    auto svgFillColor = backButtonImageRender->GetSvgFillColorValue(defaultColor);
    ASSERT_EQ(svgFillColor, iconColor);

    /**
     * @tc.steps: step4. recover api version
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: OnLanguageConfigurationUpdate001
 * @tc.desc: Test OnLanguageConfigurationUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, OnLanguageConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init titleBar environment and theme
     */
    InitTitleBarTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(backButtonNode, nullptr);
    frameNode_->SetBackButton(backButtonNode);

    /**
     * @tc.steps: step2. call OnLanguageConfigurationUpdate.
     * @tc.expected: relative value is set successfully.
     */
    titleBarPattern_->OnLanguageConfigurationUpdate();
    std::string message = theme->GetNavigationBack();
    auto accessibilityProperty = backButtonNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto accessibilityText = accessibilityProperty->GetAccessibilityText();
    ASSERT_EQ(message, accessibilityText);
    auto isAccessibilityGroup = accessibilityProperty->IsAccessibilityGroup();
    ASSERT_EQ(isAccessibilityGroup, true);
}

/**
 * @tc.name: TitleBarPatternLongPress001
 * @tc.desc: Test TitleBarPattern back button long press event with fontScale 1.75.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternLongPress001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set backButton to TitleBarNode.
     */
    InitTitleBarTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
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
     * @tc.steps: step2. Set fontScale to 1.75 scale.
     */
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 1.75f;

    /**
     * @tc.steps: step3. call HandleLongPress.
     * @tc.expected: dialogNode != nullptr
     */
    titleBarPattern->HandleLongPress(backButton);
    auto dialogNode = titleBarPattern->dialogNode_;
    ASSERT_EQ(dialogNode, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialogNode = nullptr
     */
    titleBarPattern->HandleLongPressActionEnd();
    ASSERT_EQ(titleBarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: TitleBarPatternLongPress002
 * @tc.desc: Test TitleBarPattern back button long press event with fontScale 2.0.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternLongPress002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set backButton to TitleBarNode.
     */
    InitTitleBarTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
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
     * @tc.steps: step2. Set fontScale to 2.0 scale.
     */
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 2.0f;

    /**
     * @tc.steps: step3. call HandleLongPress.
     * @tc.expected: dialogNode != nullptr
     */
    titleBarPattern->HandleLongPress(backButton);
    ASSERT_EQ(titleBarPattern->dialogNode_, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialogNode = nullptr
     */
    titleBarPattern->HandleLongPressActionEnd();
    ASSERT_EQ(titleBarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: TitleBarPatternLongPress003
 * @tc.desc: Test TitleBarPattern back button long press event with fontScale 3.2.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarPatternLongPress003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set backButton to TitleBarNode.
     */
    InitTitleBarTestNg();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
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
     * @tc.steps: step2. Set fontScale to 3.2 scale.
     */
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 3.2f;

    /**
     * @tc.steps: step3. call HandleLongPress.
     * @tc.expected: dialogNode != nullptr
     */
    titleBarPattern->HandleLongPress(backButton);
    auto dialogNode = titleBarPattern->dialogNode_;
    ASSERT_EQ(dialogNode, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialogNode = nullptr
     */
    titleBarPattern->HandleLongPressActionEnd();
    ASSERT_EQ(titleBarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: TitleBarHoverModeTest001
 * @tc.desc: Test IsNeedHoverModeAction and CalculateTitlebarOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarHoverModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters
     */
    CreateNavBar();
    InitTitleBarTestNg();

    /**
     * @tc.steps: step2. itleBarParentTypeValue is NAVBAR and NavigationTitleMode is MINI.
     * @tc.expected: Hover mode is false and offset is 0.0f.
     */
    auto titleBarLayoutProperty = frameNode_->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdateTitleBarParentType(TitleBarParentType::NAVBAR);
    titleBarLayoutProperty->UpdateTitleMode(NavigationTitleMode::MINI);
    bool hover = NavigationTitleUtil::IsNeedHoverModeAction(frameNode_);
    ASSERT_FALSE(hover);
    auto offset = NavigationTitleUtil::CalculateTitlebarOffset(frameNode_);
    EXPECT_EQ(offset, 0.0f);
}

/**
 * @tc.name: TitleBarHoverModeTest002
 * @tc.desc: Test IsNeedHoverModeAction and CalculateTitlebarOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, TitleBarHoverModeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters
     */
    InitTitleBarTestNg();

    /**
     * @tc.steps: step2. When barStyle is STANDARD or enableHoverMode is false.
     * @tc.expected: Hover mode is false and offset is 0.0f.
     */
    NavigationTitlebarOptions opt1;
    opt1.brOptions.barStyle = std::make_optional(BarStyle::STANDARD);
    titleBarPattern_->SetTitlebarOptions(opt1);
    bool hover1 = NavigationTitleUtil::IsNeedHoverModeAction(frameNode_);
    ASSERT_FALSE(hover1);
    NavigationTitlebarOptions opt2;
    opt2.enableHoverMode = false;
    titleBarPattern_->SetTitlebarOptions(opt2);
    bool hover2 = NavigationTitleUtil::IsNeedHoverModeAction(frameNode_);
    ASSERT_FALSE(hover2);
    auto offset = NavigationTitleUtil::CalculateTitlebarOffset(frameNode_);
    EXPECT_EQ(offset, 0.0f);
}

/**
 * @tc.name: createBarIemTextNode
 * @tc.desc: noBranch
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, createBarIemTextNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set text value
     */
    std::string text = "hello";
    auto barItemNode = NavigationTitleUtil::CreateBarItemTextNode(text);
    ASSERT_NE(barItemNode, nullptr);

    /**
     * @tc.steps: step2. test content value, textAlign,
     * @tc.expected: expect value equal text, textAlign equal CENTER
     */
    auto layoutProperty = barItemNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto barItemText = layoutProperty->GetContent().value_or(u"");
    EXPECT_EQ(barItemText, UtfUtils::Str8DebugToStr16(text));
    auto alignValue = static_cast<int32_t>(layoutProperty->GetTextAlign().value());
    EXPECT_EQ(alignValue, 1);
}

/**
 * @tc.name: CreateBarItemIconNode
 * @tc.desc: if (greatOrEqualTargetApiVersion(PlatformVersion::VERSION_TWELVE))  true;
 *           if (isButtonEnable) true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, CreateBarItemIconNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create barItem, theme, setApi version
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(navigationTheme));
    ASSERT_NE(navigationTheme, nullptr);
    BarItem barItem;
    barItem.icon = "icon";
    bool isButtonEnable = true;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step2. createBarItemIconNode
     * @tc.expected: expect equal target value
     */
    auto iconNode = NavigationTitleUtil::CreateBarItemIconNode(barItem, isButtonEnable, navigationTheme);
    ASSERT_NE(iconNode, nullptr);
    auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto info = imageLayoutProperty->GetImageSourceInfo().value();
    EXPECT_EQ(navigationTheme->GetIconColor(), info.GetFillColor());
}

/**
 * @tc.name: CreateBarItemIconNod2
 * @tc.desc: if (greatOrEqualTargetApiVersion(PlatformVersion::VERSION_TWELVE))  false;
 *           if (isButtonEnable) true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, CreateBarItemIconNode2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create barItem, theme, setApi version
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(navigationTheme));
    ASSERT_NE(navigationTheme, nullptr);
    BarItem barItem;
    barItem.icon = "icon";
    bool isButtonEnable = true;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    /**
     * @tc.steps: step2. createBarItemIconNode
     * @tc.expected: expect equal target value
     */
    auto iconNode = NavigationTitleUtil::CreateBarItemIconNode(barItem, isButtonEnable, navigationTheme);
    ASSERT_NE(iconNode, nullptr);
    auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto info = imageLayoutProperty->GetImageSourceInfo().value();
    EXPECT_EQ(navigationTheme->GetMenuIconColor(), info.GetFillColor());
}

/**
 * @tc.name: CreateBarItemIconNod3
 * @tc.desc: if (greatOrEqualTargetApiVersion(PlatformVersion::VERSION_TWELVE))  true;
 *           if (isButtonEnable) false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, CreateBarItemIconNode3, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create barItem, theme, setApi version
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(navigationTheme));
    ASSERT_NE(navigationTheme, nullptr);
    BarItem barItem;
    barItem.icon = "icon";
    bool isButtonEnable = false;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step2. createBarItemIconNode
     * @tc.expected: expect equal target value
     */
    auto iconNode = NavigationTitleUtil::CreateBarItemIconNode(barItem, isButtonEnable, navigationTheme);
    ASSERT_NE(iconNode, nullptr);
    auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto info = imageLayoutProperty->GetImageSourceInfo().value();
    auto opacity = navigationTheme->GetIconDisableAlpha();
    EXPECT_EQ(navigationTheme->GetIconColor().BlendOpacity(opacity), info.GetFillColor());
}

/**
 * @tc.name: CreateBarItemIconNod4
 * @tc.desc: if (greatOrEqualTargetApiVersion(PlatformVersion::VERSION_TWELVE))  false;
 *           if (isButtonEnable) false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, CreateBarItemIconNode4, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create barItem, theme, setApi version
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(navigationTheme));
    ASSERT_NE(navigationTheme, nullptr);
    BarItem barItem;
    barItem.icon = "icon";
    bool isButtonEnable = false;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    /**
     * @tc.steps: step2. createBarItemIconNode
     * @tc.expected: expect equal target value
     */
    auto iconNode = NavigationTitleUtil::CreateBarItemIconNode(barItem, isButtonEnable, navigationTheme);
    ASSERT_NE(iconNode, nullptr);
    auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto info = imageLayoutProperty->GetImageSourceInfo().value();
    auto opacity = navigationTheme->GetAlphaDisabled();
    EXPECT_EQ(navigationTheme->GetMenuIconColor().BlendOpacity(opacity), info.GetFillColor());
}

/**
 * @tc.name: InitTitleBarButtonEvent
 * @tc.desc: if (menuItem.action)  true;
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, InitTitleBarButtonEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create barItem, buttonNode
     */
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    BarItem menuItem;
    std::function<void()> func = []() {};
    menuItem.action = func;
    bool isButtonEnabled = false;

    /**
     * @tc.steps: step2. call func, test clickEvent and eventhub
     */
    NavigationTitleUtil::InitTitleBarButtonEvent(buttonNode, nullptr, false, menuItem, isButtonEnabled);
    auto gestureEventhub = buttonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventhub, nullptr);
    EXPECT_EQ(gestureEventhub->IsClickEventsEmpty(), false);
    EXPECT_EQ(isButtonEnabled, false);

    auto eventHub = buttonNode->GetEventHub<ButtonEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->IsEnabled(), false);
}

/**
 * @tc.name: InitTitleBarButtonEvent
 * @tc.desc: if (menuItem.action)  false;
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, InitTitleBarButtonEvent2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create barItem, buttonNode
     */
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    BarItem menuItem;
    menuItem.action = nullptr;
    bool isButtonEnabled = true;

    /**
     * @tc.steps: step2. call func, test clickEvent and eventhub
     */
    NavigationTitleUtil::InitTitleBarButtonEvent(buttonNode, nullptr, false, menuItem, isButtonEnabled);
    auto gestureEventhub = buttonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventhub, nullptr);
    EXPECT_EQ(gestureEventhub->IsClickEventsEmpty(), true);
    EXPECT_EQ(isButtonEnabled, true);

    auto eventHub = buttonNode->GetEventHub<ButtonEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_EQ(eventHub->IsEnabled(), true);
}

/**
 * @tc.name: UpdatebarItemNodeWithItem
 * @tc.desc: if (LessThanAPIVersion(10) && barItem.text.has_vlaue() && !barItem.text.value().empty)  true;
 *           if (barItem.icon.has_value()) || (barItem.iconSymbol.has_value() && barItem.iconSymbol.value() != nullptr)
 * true if (barItem.action) true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, UpdatebarItemNodeWithItem, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create barItem, buttonNode
     */
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(V2::BAR_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    BarItem barItem;
    bool isButtonEnabled = true;
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    ASSERT_NE(theme, nullptr);

    /**
     * @tc.steps: step2. set apiVersion, textnode
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    std::optional<std::string> opt1 = "Hello";
    barItem.text = opt1;

    std::optional<std::string> icon = "icon";
    barItem.icon = icon;

    std::function<void()> func = []() {};
    barItem.action = func;

    NavigationTitleUtil::UpdateBarItemNodeWithItem(barItemNode, barItem, isButtonEnabled, theme);
    auto eventHub = barItemNode->GetEventHub<BarItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    EXPECT_NE(barItemNode->GetTextNode(), nullptr);
    EXPECT_NE(barItemNode->GetIconNode(), nullptr);
    EXPECT_NE(eventHub->itemAction_, nullptr);
}

/**
 * @tc.name: UpdatebarItemNodeWithItem1
 * @tc.desc: if (LessThanAPIVersion(10) && barItem.text.has_vlaue() && !barItem.text.value().empty)  true;
 *           if (barItem.icon.has_value()) || (barItem.iconSymbol.has_value() && barItem.iconSymbol.value() != nullptr)
 * false if (barItem.action) true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, UpdatebarItemNodeWithItem1, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create barItem, buttonNode
     */
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(V2::BAR_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    BarItem barItem;
    bool isButtonEnabled = true;
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    ASSERT_NE(theme, nullptr);

    /**
     * @tc.steps: step2. set apiVersion, textnode
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    std::optional<std::string> opt1 = "Hello";
    barItem.text = opt1;

    std::function<void()> func = []() {};
    barItem.action = func;

    NavigationTitleUtil::UpdateBarItemNodeWithItem(barItemNode, barItem, isButtonEnabled, theme);
    auto eventHub = barItemNode->GetEventHub<BarItemEventHub>();

    EXPECT_NE(barItemNode->GetTextNode(), nullptr);
    EXPECT_EQ(barItemNode->GetIconNode(), nullptr);
    EXPECT_NE(eventHub->itemAction_, nullptr);
}

/**
 * @tc.name: UpdatebarItemNodeWithItem2
 * @tc.desc: if (LessThanAPIVersion(10) && barItem.text.has_vlaue() && !barItem.text.value().empty)  true;
 *           if (barItem.icon.has_value()) || (barItem.iconSymbol.has_value() && barItem.iconSymbol.value() != nullptr)
 * true if (barItem.action) false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, UpdatebarItemNodeWithItem2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create barItem, buttonNode
     */
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(V2::BAR_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    BarItem barItem;
    bool isButtonEnabled = true;
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    ASSERT_NE(theme, nullptr);

    /**
     * @tc.steps: step2. set apiVersion, textnode
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    std::optional<std::string> opt1 = "Hello";
    barItem.text = opt1;

    std::optional<std::string> icon = "icon";
    barItem.icon = icon;
    NavigationTitleUtil::UpdateBarItemNodeWithItem(barItemNode, barItem, isButtonEnabled, theme);
    auto eventHub = barItemNode->GetEventHub<BarItemEventHub>();

    EXPECT_NE(barItemNode->GetTextNode(), nullptr);
    EXPECT_NE(barItemNode->GetIconNode(), nullptr);
    EXPECT_EQ(eventHub->itemAction_, nullptr);
}

/**
 * @tc.name: CreateOrUpdateMainTitle
 * @tc.desc: if (ignoreMainTitle) true  case1
 *           if (ignoreMainTitle) false   if (!titleInfo.hasMainTitle) case2
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, CreateOrUpdateMainTitle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create titleBarNode
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto mainTitle = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(mainTitle, nullptr);
    titleBarNode->SetTitle(mainTitle);

    /**
     * @tc.steps: step2. setIgnoreMaintitle , still has title
     */
    NG::NavigationTitleInfo info = { false, true, "sub", "main" };
    NavigationTitleUtil::CreateOrUpdateMainTitle(titleBarNode, info, true);
    EXPECT_EQ(titleBarNode->GetTitle(), mainTitle);

    info.hasMainTitle = false;
    NavigationTitleUtil::CreateOrUpdateMainTitle(titleBarNode, info, false);
    EXPECT_EQ(titleBarNode->GetTitle(), nullptr);
}

/**
 * @tc.name: CreateOrUpdateMainTitle1
 * @tc.desc: if (ignoreMainTitle) false
 *           if (!titleInfo.hasMainTitle) fasle
 *           if (mainTitle) true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, CreateOrUpdateMainTitle1, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create titleBarNode
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto mainTitle = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(mainTitle, nullptr);
    titleBarNode->SetTitle(mainTitle);

    /**
     * @tc.steps: step2. settitle and update it
     */
    NG::NavigationTitleInfo info = { false, true, "sub", "main" };
    auto textLayout = mainTitle->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayout, nullptr);
    textLayout->UpdateContent("test");

    NavigationTitleUtil::CreateOrUpdateMainTitle(titleBarNode, info, false);
    auto value = textLayout->GetContent().value_or(u"");
    EXPECT_EQ(value, UtfUtils::Str8DebugToStr16("main"));
}

/**
 * @tc.name: CreateOrUpdateMainTitle2
 * @tc.desc: if (ignoreMainTitle) false
 *           if (!titleInfo.hasMainTitle) fasle
 *           if (mainTitle) false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, CreateOrUpdateMainTitle2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create titleBarNode.
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);

    /**
     * @tc.steps: step2. createtitle and check it.
     */
    NG::NavigationTitleInfo info = { false, true, "sub", "main" };

    NavigationTitleUtil::CreateOrUpdateMainTitle(titleBarNode, info, false);
    ASSERT_NE(titleBarNode->GetTitle(), nullptr);
    auto text = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    auto textLayout = text->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayout, nullptr);
    auto value = textLayout->GetContent().value_or(u"");
    EXPECT_EQ(value, UtfUtils::Str8DebugToStr16("main"));
}

/**
 * @tc.name: test ToJsonValue
 * @tc.desc: nobranch
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarTestNg, ToJsonValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create titleBarNode.
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);

    /**
     * @tc.steps: step2. setcolor and test
     */
    auto ctx = titleBarNode->GetRenderContext();
    ASSERT_NE(ctx, nullptr);
    ctx->UpdateBackgroundColor(Color::RED);
    
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    InspectorFilter filter;
    titleBarNode->ToJsonValue(json, filter);
    ASSERT_NE(json->GetString("backgroundColor"), "0xffff0000");
}
} // namespace OHOS::Ace::NG
