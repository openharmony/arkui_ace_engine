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

#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components/close_icon/close_icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/panel/sliding_panel_event_hub.h"
#include "core/components_ng/pattern/panel/sliding_panel_layout_algorithm.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"
#include "core/components_ng/pattern/panel/sliding_panel_pattern.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/ace_events.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/panel/sliding_panel_layout_algorithm.h"
#include "core/components_ng/pattern/panel/drag_bar_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool SLIDING_PANEL_SHOW = true;
constexpr bool SLIDING_PANEL_HAS_DRAG_BAR_FALSE = false;
constexpr bool SLIDING_PANEL_HAS_DRAG_BAR_TRUE = true;
constexpr bool SLIDING_PANEL_SHOW_CLOSE_ICON_FALSE = false;
constexpr bool SLIDING_PANEL_SHOW_CLOSE_ICON_TRUE = true;

constexpr float ZERO = 0.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float PANEL_HEIGHT = 900.0f;
constexpr float COLUMN_HEIGHT = 100.0f;
constexpr float ROW_WIDTH = 300.f;
constexpr float ROW_HEIGHT = 100.f;
constexpr float START_X = 50.0f;
constexpr float START_Y = 100.0f;
constexpr float MAIN_VELOCITY = 500.0f;
constexpr float CURRENT_OFFSET = 200.f;
constexpr float DRAG_LENGTH = 100.0f;
constexpr float DRAG_VELOCITY = 50.0f;
constexpr float DRAG_ICON_WIDTH = 64.0f;
constexpr float DRAG_ICON_HEIGHT = 24.0f;

const Offset START_POINT(START_X, START_Y);
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF DRAGBAR_SIZE(DRAG_ICON_WIDTH, DRAG_ICON_HEIGHT);
const SizeF PANEL_SIZE(FULL_SCREEN_WIDTH, PANEL_HEIGHT);
const SizeF COLUMN_SIZE(FULL_SCREEN_WIDTH, COLUMN_HEIGHT);
const SizeF ROW_SIZE(ROW_WIDTH, ROW_HEIGHT);
const SizeF ROW_MAX_SIZE(FULL_SCREEN_HEIGHT, FULL_SCREEN_WIDTH);
const SizeF ROW_MIN_SIZE(-1, FULL_SCREEN_WIDTH);
const OffsetF ORIGIN_POINT(ZERO, ZERO);
const OffsetF COLUMN_OFFSET(ZERO, ZERO);
const OffsetF ROW_OFFSET(ZERO, COLUMN_HEIGHT);
constexpr Color BACKGROUND_COLOR_VALUE = Color(0XFFFF0000);
constexpr Color BORDER_COLOR = Color(0XFFDD0000);
constexpr Dimension BORDER_WIDTH = 5.0_px;
constexpr Dimension SLIDING_PANEL_HALF_HEIGHT = 300.0_px;
constexpr PanelType PANEL_TYPE_VALUE = PanelType::MINI_BAR;
constexpr PanelMode PANEL_MODE_VALUE = PanelMode::FULL;
constexpr BorderStyle BORDER_STYLE = BorderStyle::DASHED;
const std::vector<PanelType> PANEL_PANEL_TYPE = { PanelType::MINI_BAR, PanelType::FOLDABLE_BAR,
    PanelType::TEMP_DISPLAY };
} // namespace

struct TestProperty {
    std::optional<PanelType> panelType = std::nullopt;
    std::optional<PanelMode> panelMode = std::nullopt;
    std::optional<bool> hasDragBar = std::nullopt;
    std::optional<Dimension> miniHeight = std::nullopt;
    std::optional<Dimension> halfHeight = std::nullopt;
    std::optional<Dimension> fullHeight = std::nullopt;
    std::optional<bool> isShow = std::nullopt;
    std::optional<bool> showCloseIcon = std::nullopt;
};

class PanelTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;

    PaddingProperty CreatePadding(float left, float top, float right, float bottom)
    {
        PaddingProperty padding;
        padding.left = CalcLength(left);
        padding.right = CalcLength(right);
        padding.top = CalcLength(top);
        padding.bottom = CalcLength(bottom);
        return padding;
    }

protected:
    static RefPtr<FrameNode> CreateSlidingPanel(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateSlidingPanelwithCloseIcon();
    static RefPtr<LayoutWrapperNode> CreatChildLayoutWrapperNode(
        const std::string& tagName, const RefPtr<FrameNode>& panelFrameNode);
};

void PanelTestTwoNg::SetUp()
{
    MockPipelineContext::SetUp();
}
void PanelTestTwoNg::TearDown()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> PanelTestTwoNg::CreateSlidingPanel(const TestProperty& testProperty)
{
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    if (testProperty.panelType.has_value()) {
        slidingPanelModelNG.SetPanelType(testProperty.panelType.value());
    }
    if (testProperty.panelMode.has_value()) {
        slidingPanelModelNG.SetPanelMode(testProperty.panelMode.value());
    }
    if (testProperty.hasDragBar.has_value()) {
        slidingPanelModelNG.SetHasDragBar(testProperty.hasDragBar.value());
    }
    if (testProperty.miniHeight.has_value()) {
        slidingPanelModelNG.SetMiniHeight(testProperty.miniHeight.value());
    }
    if (testProperty.halfHeight.has_value()) {
        slidingPanelModelNG.SetHalfHeight(testProperty.halfHeight.value());
    }
    if (testProperty.fullHeight.has_value()) {
        slidingPanelModelNG.SetFullHeight(testProperty.fullHeight.value());
    }
    if (testProperty.isShow.has_value()) {
        slidingPanelModelNG.SetIsShow(testProperty.isShow.value());
    }
    if (testProperty.showCloseIcon.has_value()) {
        slidingPanelModelNG.SetShowCloseIcon(testProperty.showCloseIcon.value());
    }
    
    return AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
}

RefPtr<FrameNode> PanelTestTwoNg::CreateSlidingPanelwithCloseIcon()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto closeIconTheme = AceType::MakeRefPtr<CloseIconTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(closeIconTheme));
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetShowCloseIcon(SLIDING_PANEL_SHOW_CLOSE_ICON_TRUE);
    slidingPanelModelNG.SetPanelMode(PanelMode::FULL);
    return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
}

RefPtr<LayoutWrapperNode> PanelTestTwoNg::CreatChildLayoutWrapperNode(
    const std::string& tagName, const RefPtr<FrameNode>& panelFrameNode)
{
    auto panelPattern = panelFrameNode->GetPattern<SlidingPanelPattern>();
    auto childNode = AceType::DynamicCast<FrameNode>(panelPattern->GetChildNodeByTag(tagName));
    auto childLayoutProperty = childNode->GetLayoutProperty();
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childNode->GetGeometryNode(), childLayoutProperty);
    return childLayoutWrapper;
}

/**
 * @tc.name: PanelTestTwoNg0020
 * @tc.desc: Test SlidingPanelNode::AddChildToGroup.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get slidingPanelNode, set children_.
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);
    SlidingPanelNode slidingPanelNode("SlidingPanelNode", 100, pattern);
    slidingPanelNode.columnChildren_.insert(1);
    auto child = AceType::MakeRefPtr<SlidingPanelNode>("child1", 1, pattern);
    ASSERT_NE(child, nullptr);
    slidingPanelNode.AddChildToGroup(child, 1);
    EXPECT_NE(
        slidingPanelNode.columnChildren_.find(child->GetId()), slidingPanelNode.columnChildren_.end());
    /**
     * @tc.steps: step2. construct a UINode of children.
     * @tc.expected: check whether the value is correct.
     */
    std::list<RefPtr<UINode>> list;
    list.push_back(AceType::MakeRefPtr<SlidingPanelNode>("child3", 3, pattern));
    auto child4 = AceType::MakeRefPtr<SlidingPanelNode>("child4", 4, pattern);
    child4->children_ = list;
    slidingPanelNode.children_.clear();
    slidingPanelNode.children_.push_back(child4);
    auto child2 = AceType::MakeRefPtr<SlidingPanelNode>("child2", 2, pattern);
    slidingPanelNode.AddChildToGroup(child2, 1);
        EXPECT_NE(
        slidingPanelNode.columnChildren_.find(child2->GetId()), slidingPanelNode.columnChildren_.end());
}

/**
 * @tc.name: PanelTestTwoNg0021
 * @tc.desc: Test SlidingPanelPattern::CheckPanelModeAndType.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelMode(PanelMode::FULL);
    auto panelFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(panelFrameNode, nullptr);
    /**
     * @tc.steps: step2. get layoutproperty, geometryNode and create layoutWrapper.
     * @tc.expected: related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(panelFrameNode, geometryNode, panelFrameNode->GetLayoutProperty());
    auto panelPattern = panelFrameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(panelPattern, nullptr);
    panelPattern->mode_ = PanelMode::HALF;
    panelPattern->type_ = PanelType::MINI_BAR;
    panelPattern->CheckPanelModeAndType();
    EXPECT_EQ(panelPattern->mode_, PanelMode::MINI);
    panelPattern->type_ = PanelType::TEMP_DISPLAY;
    panelPattern->CheckPanelModeAndType();
    EXPECT_EQ(panelPattern->mode_, PanelMode::HALF);
}

/**
 * @tc.name: PanelTestTwoNg0022
 * @tc.desc: Test SlidingPanelPattern::OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    /**
     * @tc.steps: step2. change slidingPanelPattern->isShowQueue_ and slidingPanelPattern->isShow_.
     * @tc.expected: slidingPanelPattern->isShowQueue_.empty() is correct.
     */
    auto host = slidingPanelPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto isShow = layoutProperty->GetIsShowValue(false);
    EXPECT_TRUE(isShow);
    slidingPanelPattern->isShowQueue_ = std::queue<bool>();
    EXPECT_TRUE(slidingPanelPattern->isShowQueue_.empty());
    slidingPanelPattern->isShow_ = false;
    slidingPanelPattern->OnModifyDone();
    EXPECT_FALSE(slidingPanelPattern->isShowQueue_.empty());
}

/**
 * @tc.name: PanelTestTwoNg0023
 * @tc.desc: Test SlidingPanelPattern::Update.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    /**
     * @tc.steps: step2. change slidingPanelPattern->mode_, layoutProperty->propPanelType_ and so on.
     * @tc.expected: slidingPanelPattern->mode_.value() is correct.
     */
    auto layoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propPanelMode_ = PanelMode::HALF;
    slidingPanelPattern->mode_ = PanelMode::HALF;
    auto mode = layoutProperty->GetPanelMode() == PanelMode::AUTO
                    ? PanelMode::FULL
                    : layoutProperty->GetPanelMode().value_or(PanelMode::HALF);
    slidingPanelPattern->type_ = layoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
    EXPECT_EQ(slidingPanelPattern->type_, PanelType::MINI_BAR);
    EXPECT_EQ(slidingPanelPattern->mode_.value(), mode);
    EXPECT_EQ(slidingPanelPattern->mode_.value(), PanelMode::HALF);
    slidingPanelPattern->isShow_ = true;
    EXPECT_TRUE(slidingPanelPattern->isShow_);
    layoutProperty->propIsShow_ = true;
    slidingPanelPattern->previousMode_ = PanelMode::AUTO;
    slidingPanelPattern->Update();

    layoutProperty->propPanelType_ = PanelType::TEMP_DISPLAY;
    layoutProperty->propPanelMode_ = PanelMode::MINI;
    slidingPanelPattern->mode_ = PanelMode::MINI;
    slidingPanelPattern->Update();
    EXPECT_EQ(slidingPanelPattern->mode_.value(), PanelMode::HALF);
}

/**
 * @tc.name: PanelTestTwoNg0024
 * @tc.desc: Test SlidingPanelPattern::InitializeLayoutProps.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    /**
     * @tc.steps: step2. change slidingPanelPattern->isShow_, child.
     * @tc.expected: slidingPanelPattern->isShow_ is correct.
     */
    auto layoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto isShow = layoutProperty->GetIsShowValue(false);
    EXPECT_TRUE(isShow);
    slidingPanelPattern->isShow_ = false;
    EXPECT_TRUE(slidingPanelPattern->isShow_.value() != isShow);
    slidingPanelPattern->InitializeLayoutProps();
    EXPECT_FALSE(slidingPanelPattern->isShow_.value() != isShow);

    auto host = slidingPanelPattern->GetHost();
    auto child = host->GetChildren();
    EXPECT_FALSE(child.empty() || child.size() != 1);
    child.clear();
    EXPECT_TRUE(child.empty() || child.size() != 1);
    slidingPanelPattern->InitializeLayoutProps();
    EXPECT_TRUE(slidingPanelPattern->isShow_);
}

/**
 * @tc.name: PanelTestTwoNg0025
 * @tc.desc: Test SlidingPanelPattern::FirstLayout.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto closeIconNode = FrameNode::GetOrCreateFrameNode(V2::PANEL_CLOSE_ICON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<CloseIconPattern>(); });
    closeIconNode->MountToParent(frameNode, 1);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    /**
     * @tc.steps: step2. change layoutProperty->propIsShow_.
     * @tc.expected: slidingPanelPattern->FirstLayout() is called.
     */
    auto layoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->GetIsShowValue(false));
    EXPECT_TRUE(slidingPanelPattern->previousMode_ != slidingPanelPattern->mode_.value_or(PanelMode::HALF));
    EXPECT_TRUE(layoutProperty->GetHasDragBarValue(true));
    auto dragBar = slidingPanelPattern->GetDragBarNode();
    ASSERT_NE(dragBar, nullptr);
    auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    auto closeIcon = slidingPanelPattern->GetCloseIconNode();
    ASSERT_NE(closeIcon, nullptr);
    auto closeIconPattern = closeIcon->GetPattern<CloseIconPattern>();
    ASSERT_NE(closeIconPattern, nullptr);
    slidingPanelPattern->FirstLayout();
    layoutProperty->propIsShow_ = false;

    EXPECT_FALSE(layoutProperty->GetIsShowValue(false));
    slidingPanelPattern->FirstLayout();
}

/**
 * @tc.name: PanelTestTwoNg0026
 * @tc.desc: Test SlidingPanelPattern::FirstLayout.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    /**
     * @tc.steps: step2. change slidingPanelPattern->previousMode_, slidingPanelPattern->mode_.
     * @tc.expected: hasDragBar is correct.
     */
    auto layoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto hasDragBar = layoutProperty->GetHasDragBarValue(true);
    slidingPanelPattern->previousMode_ = PanelMode::HALF;
    slidingPanelPattern->mode_ = PanelMode::FULL;
    slidingPanelPattern->IsShowChanged(true);
    EXPECT_EQ(slidingPanelPattern->previousMode_, slidingPanelPattern->mode_);
    slidingPanelPattern->IsShowChanged(false);
    EXPECT_TRUE(hasDragBar);
}

/**
 * @tc.name: PanelTestTwoNg0027
 * @tc.desc: Test SlidingPanelPattern::HeightDynamicUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    /**
     * @tc.steps: step2. change slidingPanelPattern->previousMode_, slidingPanelPattern->isAnimating_ and so on.
     * @tc.expected: slidingPanelPattern->previousMode_ is correct.
     */
    slidingPanelPattern->isShow_ = true;
    EXPECT_TRUE(slidingPanelPattern->isShow_.value_or(false));
    EXPECT_FALSE(slidingPanelPattern->isDrag_);
    EXPECT_FALSE(slidingPanelPattern->isAnimating_);

    slidingPanelPattern->previousMode_ = PanelMode::FULL;
    slidingPanelPattern->currentOffset_ = 0.3f;
    slidingPanelPattern->defaultBlankHeights_[PanelMode::FULL] = 0.5f;
    slidingPanelPattern->HeightDynamicUpdate();

    EXPECT_TRUE(slidingPanelPattern->isShow_.value_or(false));
    EXPECT_FALSE(slidingPanelPattern->isDrag_);
    EXPECT_TRUE(slidingPanelPattern->isAnimating_);
    slidingPanelPattern->isAnimating_ = false;
    slidingPanelPattern->previousMode_ = PanelMode::HALF;
    slidingPanelPattern->currentOffset_ = 0.3f;
    slidingPanelPattern->defaultBlankHeights_[PanelMode::HALF] = 0.5f;
    slidingPanelPattern->HeightDynamicUpdate();
    EXPECT_TRUE(slidingPanelPattern->isShow_.value_or(false));
    EXPECT_FALSE(slidingPanelPattern->isDrag_);
    EXPECT_TRUE(slidingPanelPattern->isAnimating_);
    slidingPanelPattern->isAnimating_ = false;
    slidingPanelPattern->previousMode_ = PanelMode::MINI;
    slidingPanelPattern->currentOffset_ = 0.3f;
    slidingPanelPattern->defaultBlankHeights_[PanelMode::MINI] = 0.5f;
    slidingPanelPattern->HeightDynamicUpdate();
    EXPECT_EQ(slidingPanelPattern->previousMode_, PanelMode::MINI);
    slidingPanelPattern->previousMode_ = PanelMode::AUTO;
    slidingPanelPattern->HeightDynamicUpdate();
    EXPECT_EQ(slidingPanelPattern->previousMode_, PanelMode::AUTO);
}

/**
 * @tc.name: PanelTestTwoNg0028
 * @tc.desc: Test SlidingPanelPattern::CheckPanelModeAndType.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    /**
     * @tc.steps: step2. change slidingPanelPattern->mode_, slidingPanelPattern->type_.
     * @tc.expected: slidingPanelPattern->mode_ and slidingPanelPattern->type_ are correct.
     */
    slidingPanelPattern->mode_ = PanelMode::HALF;
    slidingPanelPattern->type_ = PanelType::MINI_BAR;
    slidingPanelPattern->CheckPanelModeAndType();
    EXPECT_EQ(slidingPanelPattern->mode_, PanelMode::MINI);
    EXPECT_EQ(slidingPanelPattern->type_, PanelType::MINI_BAR);

    slidingPanelPattern->type_ = PanelType::TEMP_DISPLAY;
    slidingPanelPattern->CheckPanelModeAndType();
    EXPECT_EQ(slidingPanelPattern->mode_, PanelMode::HALF);
    EXPECT_EQ(slidingPanelPattern->type_, PanelType::TEMP_DISPLAY);
}

/**
 * @tc.name: PanelTestTwoNg0029
 * @tc.desc: Test SlidingPanelPattern::CalculateModeTypeFold.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    /**
     * @tc.steps: step2. change slidingPanelPattern->currentOffset_.
     * @tc.expected: slidingPanelPattern->currentOffset_ is correct.
     */
    slidingPanelPattern->currentOffset_ = 55.0f;
    slidingPanelPattern->fullHalfBoundary_ = 50.0f;
    slidingPanelPattern->halfMiniBoundary_ = 60.0f;
    slidingPanelPattern->CalculateModeTypeFold(DRAG_LENGTH, DRAG_VELOCITY);
    EXPECT_GE(slidingPanelPattern->currentOffset_, slidingPanelPattern->fullHalfBoundary_);
    EXPECT_LT(slidingPanelPattern->currentOffset_, slidingPanelPattern->halfMiniBoundary_);
    slidingPanelPattern->currentOffset_ = 100.0f;
    slidingPanelPattern->CalculateModeTypeFold(DRAG_LENGTH, DRAG_VELOCITY);
    EXPECT_GE(slidingPanelPattern->currentOffset_, slidingPanelPattern->fullHalfBoundary_);
    EXPECT_GE(slidingPanelPattern->currentOffset_, slidingPanelPattern->halfMiniBoundary_);
}

/**
 * @tc.name: PanelTestTwoNg0030
 * @tc.desc: Test SlidingPanelPattern::CalculateModeTypeFold.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    /**
     * @tc.steps: step2. call GetAnimationDuration.
     * @tc.expected: dragRange is correct.
     */
    float delta = 10.0f;
    float dragRange = 5.0f;
    slidingPanelPattern->GetAnimationDuration(delta, dragRange);
    EXPECT_NE(dragRange, 0.0f);
}

/**
 * @tc.name: PanelTestTwoNg0031
 * @tc.desc: Test SlidingPanelPattern::CalculateModeTypeFold.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    /**
     * @tc.steps: step2. change slidingPanelPattern->isShowQueue_.
     * @tc.expected: slidingPanelPattern->invisibleFlag_.value_or(true) is correct.
     */
    EXPECT_TRUE(slidingPanelPattern->isShowQueue_.empty());
    slidingPanelPattern->isShowQueue_.push(true);
    slidingPanelPattern->isShowQueue_.push(true);
    slidingPanelPattern->OnAnimationStop();
    EXPECT_FALSE(slidingPanelPattern->invisibleFlag_.value_or(true));
}

/**
 * @tc.name: PanelTestTwoNg0032
 * @tc.desc: Test DragBarPattern::ShowArrow.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dragBarPattern, change showMode_.
     * @tc.expected: dragBarPattern.showMode_ is correct.
     */
    DragBarPattern dragBarPattern;
    dragBarPattern.showMode_ = PanelMode::FULL;
    dragBarPattern.ShowArrow(true);
    EXPECT_EQ(dragBarPattern.showMode_, PanelMode::FULL);
    dragBarPattern.ShowArrow(false);
    EXPECT_EQ(dragBarPattern.showMode_, PanelMode::HALF);
}

/**
 * @tc.name: PanelTestTwoNg0033
 * @tc.desc: Test DragBarPattern::ShowArrow.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dragBarPattern, set clickArrowCallback_.
     * @tc.expected: dragBarPattern.clickArrowCallback_ is correct.
     */
    DragBarPattern dragBarPattern;
    dragBarPattern.OnClick();
    EXPECT_FALSE(dragBarPattern.clickArrowCallback_);
    dragBarPattern.clickArrowCallback_ = []() {};
    dragBarPattern.OnClick();
    EXPECT_TRUE(dragBarPattern.clickArrowCallback_);
}

/**
 * @tc.name: PanelTestTwoNg0034
 * @tc.desc: Test panel pattern GetCloseIconNode and GetChildNodeByTag.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto closeIconTheme = AceType::MakeRefPtr<CloseIconTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(closeIconTheme));
    /**
     * @tc.steps: step2. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetShowCloseIcon(SLIDING_PANEL_SHOW_CLOSE_ICON_TRUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    /**
     * @tc.steps: step3. get pattern.
     * @tc.expected: step3. check closeIconNode is not nullptr.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);
    slidingPanelPattern->OnModifyDone();
    auto closeIconNode = slidingPanelPattern->GetChildNodeByTag(V2::PANEL_CLOSE_ICON_ETS_TAG);
    ASSERT_NE(closeIconNode, nullptr);
    closeIconNode->MarkDirtyNode();
    closeIconNode = slidingPanelPattern->GetCloseIconNode();
    ASSERT_NE(closeIconNode, nullptr);
    /**
     * @tc.steps: step4. get panelLayoutProperty.
     * @tc.expected: step4. check closeIconNode is nullptr.
     */
    auto panelLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    panelLayoutProperty->UpdateHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_FALSE);
    panelLayoutProperty->UpdateShowCloseIcon(SLIDING_PANEL_SHOW_CLOSE_ICON_FALSE);
    slidingPanelPattern->OnModifyDone();
    closeIconNode = slidingPanelPattern->GetChildNodeByTag(V2::PANEL_CLOSE_ICON_ETS_TAG);
    auto dragBarNode = slidingPanelPattern->GetChildNodeByTag(V2::DRAG_BAR_ETS_TAG);
    ASSERT_EQ(closeIconNode, nullptr);
    ASSERT_EQ(dragBarNode, nullptr);
}

/**
 * @tc.name: PanelTestTwoNg0035
 * @tc.desc: Test SlidingPanelPattern::GetCloseIconNode and GetDragBarNode.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto closeIconTheme = AceType::MakeRefPtr<CloseIconTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(closeIconTheme));
    /**
     * @tc.steps: step2. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetShowCloseIcon(true);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    /**
     * @tc.steps: step3. get closeIcon node and get dragBar node.
     * @tc.expected: node is not nullptr.
     */
    auto closeIconNode = slidingPanelPattern->GetCloseIconNode();
    ASSERT_NE(closeIconNode, nullptr);
    auto dargBarNode = slidingPanelPattern->GetDragBarNode();
    ASSERT_NE(dargBarNode, nullptr);
}

/**
 * @tc.name: PanelTestTwoNg0036
 * @tc.desc: Test CloseIconPattern::clickButtonCallback_.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create closeIconPattern, set clickButtonCallback_.
     * @tc.expected: closeIconPattern.clickButtonCallback_ is correct.
     */
    CloseIconPattern closeIconPattern;
    closeIconPattern.ButtonClickEvent();
    EXPECT_FALSE(closeIconPattern.clickButtonCallback_);
    closeIconPattern.clickButtonCallback_ = []() {};
    closeIconPattern.ButtonClickEvent();
    EXPECT_TRUE(closeIconPattern.clickButtonCallback_);
}

/**
 * @tc.name: PanelTestTwoNg0037
 * @tc.desc: Test SlidingPanelPattern::HeightDynamicUpdate previousMode_
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    slidingPanelPattern->isShow_ = true;
    EXPECT_TRUE(slidingPanelPattern->isShow_.value_or(false));
    EXPECT_FALSE(slidingPanelPattern->isDrag_);
    EXPECT_FALSE(slidingPanelPattern->isAnimating_);
    slidingPanelPattern->isAnimating_ = false;
    slidingPanelPattern->previousMode_ = PanelMode::CUSTOM;
    slidingPanelPattern->currentOffset_ = 0.3f;
    slidingPanelPattern->defaultBlankHeights_[PanelMode::CUSTOM] = 0.3f;
    slidingPanelPattern->HeightDynamicUpdate();
    slidingPanelPattern->defaultBlankHeights_[PanelMode::CUSTOM] = 0.5f;
    slidingPanelPattern->HeightDynamicUpdate();
    EXPECT_TRUE(slidingPanelPattern->isShow_.value_or(false));
    EXPECT_FALSE(slidingPanelPattern->isDrag_);
    EXPECT_TRUE(slidingPanelPattern->isAnimating_);
    slidingPanelPattern->isClosePanel_ = true;
    slidingPanelPattern->HeightDynamicUpdate();
    EXPECT_EQ(slidingPanelPattern->isClosePanel_, true);
}

/**
 * @tc.name: PanelTestTwoNg0038
 * @tc.desc: Test SlidingPanelPattern::HeightDynamicUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    slidingPanelPattern->isShow_ = true;
    EXPECT_TRUE(slidingPanelPattern->isShow_.value_or(false));
    EXPECT_FALSE(slidingPanelPattern->isDrag_);
    EXPECT_FALSE(slidingPanelPattern->isAnimating_);
    slidingPanelPattern->isClosePanel_ = true;
    slidingPanelPattern->HeightDynamicUpdate();
    EXPECT_EQ(slidingPanelPattern->isClosePanel_, true);
    slidingPanelPattern->isShow_ = false;
    slidingPanelPattern->isAnimating_ = true;
    slidingPanelPattern->HeightDynamicUpdate();
    EXPECT_FALSE(slidingPanelPattern->isShow_.value_or(true));
    EXPECT_FALSE(slidingPanelPattern->isDrag_);
    EXPECT_TRUE(slidingPanelPattern->isAnimating_);
    slidingPanelPattern->isShow_ = true;
    slidingPanelPattern->isAnimating_ = true;
    slidingPanelPattern->isDrag_ = true;
    slidingPanelPattern->HeightDynamicUpdate();
    EXPECT_TRUE(slidingPanelPattern->isShow_.value_or(false));
    EXPECT_TRUE(slidingPanelPattern->isDrag_);
    EXPECT_TRUE(slidingPanelPattern->isAnimating_);
}

/**
 * @tc.name: PanelTestTwoNg0039
 * @tc.desc: Test SlidingPanelPattern::Update.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    auto layoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propPanelMode_ = PanelMode::HALF;
    slidingPanelPattern->mode_ = PanelMode::HALF;
    slidingPanelPattern->type_ = layoutProperty->GetPanelType().value_or(PanelType::CUSTOM);
    EXPECT_EQ(slidingPanelPattern->type_, PanelType::MINI_BAR);
    layoutProperty->UpdatePanelType(PanelType::CUSTOM);
    slidingPanelPattern->mode_.reset();
    slidingPanelPattern->Update();
    slidingPanelPattern->isShow_ = true;
    EXPECT_TRUE(slidingPanelPattern->isShow_);
    layoutProperty->propIsShow_ = true;
    slidingPanelPattern->previousMode_ = PanelMode::AUTO;
    layoutProperty->UpdatePanelType(PanelType::CUSTOM);
    slidingPanelPattern->Update();
    EXPECT_EQ(slidingPanelPattern->type_, PanelType::CUSTOM);
}

/**
 * @tc.name: PanelTestTwoNg0040
 * @tc.desc: Test SlidingPanelPattern::Update mode
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    auto layoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propPanelMode_ = PanelMode::HALF;
    slidingPanelPattern->mode_ = PanelMode::HALF;
    slidingPanelPattern->type_ = layoutProperty->GetPanelType().value_or(PanelType::CUSTOM);
    EXPECT_EQ(slidingPanelPattern->type_, PanelType::MINI_BAR);
    layoutProperty->UpdatePanelMode(PanelMode::AUTO);
    slidingPanelPattern->isShow_ = false;
    layoutProperty->propIsShow_ = true;
    slidingPanelPattern->previousMode_ = PanelMode::AUTO;
    layoutProperty->UpdatePanelType(PanelType::CUSTOM);
    slidingPanelPattern->Update();
    EXPECT_EQ(slidingPanelPattern->previousMode_, PanelMode::AUTO);
}

/**
 * @tc.name: PanelTestTwoNg0041
 * @tc.desc: Test panel pattern HandleDragStart  HandleDragEnd PanelType::TEMP_DISPLAY
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0041, TestSize.Level1)
{
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHalfHeight(SLIDING_PANEL_HALF_HEIGHT);
    slidingPanelModelNG.SetPanelType(PANEL_PANEL_TYPE[0]);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    auto panelLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(panelLayoutProperty, nullptr);
    slidingPanelPattern->isAnimating_ = false;
    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->dragStartCurrentOffset_ = ZERO;
    slidingPanelPattern->mode_ = panelLayoutProperty->GetPanelMode().value_or(PanelMode::HALF);
    slidingPanelPattern->type_ = panelLayoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
    slidingPanelPattern->previousMode_ = slidingPanelPattern->mode_.value_or(PanelMode::FULL);
    slidingPanelPattern->isShow_ = true;
    auto slidingLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    GestureEvent endInfo;
    endInfo.SetMainVelocity(MAIN_VELOCITY);
    slidingLayoutProperty->propPanelType_ = PanelType::TEMP_DISPLAY;
    slidingPanelPattern->halfMiniBoundary_ = 110.0f;
    slidingPanelPattern->HandleDragEnd(static_cast<float>(endInfo.GetMainVelocity()));
    EXPECT_EQ(endInfo.GetMainVelocity(), MAIN_VELOCITY);
}

/**
 * @tc.name: PanelTestTwoNg0042
 * @tc.desc: Test panel pattern HandleDragStart HandleDragEnd.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0042, TestSize.Level1)
{
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHalfHeight(SLIDING_PANEL_HALF_HEIGHT);
    slidingPanelModelNG.SetPanelType(PANEL_PANEL_TYPE[0]);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    auto panelLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(panelLayoutProperty, nullptr);
    slidingPanelPattern->isAnimating_ = false;
    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->dragStartCurrentOffset_ = ZERO;
    slidingPanelPattern->mode_ = panelLayoutProperty->GetPanelMode().value_or(PanelMode::HALF);
    slidingPanelPattern->type_ = panelLayoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
    slidingPanelPattern->previousMode_ = slidingPanelPattern->mode_.value_or(PanelMode::FULL);
    slidingPanelPattern->isShow_ = true;
    auto slidingLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    GestureEvent endInfo;
    endInfo.SetMainVelocity(MAIN_VELOCITY);
    slidingLayoutProperty->propPanelType_ = PanelType::FOLDABLE_BAR;
    slidingPanelPattern->halfMiniBoundary_ = 100.0f;
    slidingPanelPattern->HandleDragEnd(static_cast<float>(endInfo.GetMainVelocity()));
    EXPECT_EQ(endInfo.GetMainVelocity(), MAIN_VELOCITY);
}

/**
 * @tc.name: PanelTestTwoNg0043
 * @tc.desc: Test panel pattern HandleDragStart HandleDragEnd.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0043, TestSize.Level1)
{
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHalfHeight(SLIDING_PANEL_HALF_HEIGHT);
    slidingPanelModelNG.SetPanelType(PANEL_PANEL_TYPE[0]);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    auto panelLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(panelLayoutProperty, nullptr);
    slidingPanelPattern->isAnimating_ = false;
    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->dragStartCurrentOffset_ = ZERO;
    slidingPanelPattern->mode_ = panelLayoutProperty->GetPanelMode().value_or(PanelMode::HALF);
    slidingPanelPattern->type_ = panelLayoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
    slidingPanelPattern->previousMode_ = slidingPanelPattern->mode_.value_or(PanelMode::FULL);
    slidingPanelPattern->isShow_ = true;
    auto slidingLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    GestureEvent endInfo;
    endInfo.SetMainVelocity(MAIN_VELOCITY);
    slidingLayoutProperty->propPanelType_ = PanelType::CUSTOM;
    slidingPanelPattern->currentOffset_ = 110.0f;
    slidingPanelPattern->HandleDragEnd(static_cast<float>(endInfo.GetMainVelocity()));
    EXPECT_EQ(endInfo.GetMainVelocity(), MAIN_VELOCITY);
}

/**
 * @tc.name: PanelTestTwoNg0044
 * @tc.desc: Test panel pattern OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelMode(PanelMode::FULL);
    auto panelFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(panelFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(panelFrameNode, geometryNode, panelFrameNode->GetLayoutProperty());
    auto panelPattern = panelFrameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(panelPattern == nullptr);
    auto panelLayoutProperty = panelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(panelLayoutProperty == nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<SlidingPanelLayoutAlgorithm>(panelPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    DirtySwapConfig config;
    config.skipLayout = false;
    config.skipMeasure = true;
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithmWrapper == nullptr);
    auto slidingPanelLayoutAlgorithm =
        AceType::DynamicCast<SlidingPanelLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_FALSE(slidingPanelLayoutAlgorithm == nullptr);
    panelPattern->mode_ = panelLayoutProperty->GetPanelMode().value_or(PanelMode::HALF);
    panelPattern->type_ = panelLayoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
    panelPattern->previousMode_ = panelPattern->mode_.value_or(PanelMode::HALF);
    panelPattern->isFirstLayout_ = true;
    panelPattern->currentOffset_ = 0.0f;
    panelPattern->isFirstLayout_ = false;
    panelPattern->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    bool flag = panelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(flag == false);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    flag = panelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(flag == true);
}

/**
 * @tc.name: PanelTestTwoNg0045
 * @tc.desc: Test SlidingPanelPattern::OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    auto host = slidingPanelPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto hub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    slidingPanelPattern->panEvent_ = AceType::MakeRefPtr<PanEvent>(
        [](GestureEvent& info) {}, [](GestureEvent& info) {}, [](GestureEvent& info) {}, []() {});
    layoutProperty->UpdatePanelType(PanelType::CUSTOM);
    slidingPanelPattern->IsNeedResetPanEvent(gestureHub);
    EXPECT_EQ(layoutProperty->GetPanelType(), PanelType::CUSTOM);
}

/**
 * @tc.name: PanelTestTwoNg0046
 * @tc.desc: Test SlidingPanelPattern::InitializeLayoutProps.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestTwoNg, PanelTestTwoNg0046, TestSize.Level1)
{
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelType(PANEL_TYPE_VALUE);
    slidingPanelModelNG.SetPanelMode(PANEL_MODE_VALUE);
    slidingPanelModelNG.SetBackgroundColor(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetBorderColor(BORDER_COLOR);
    slidingPanelModelNG.SetBorderWidth(BORDER_WIDTH);
    slidingPanelModelNG.SetBorderStyle(BORDER_STYLE);
    slidingPanelModelNG.SetBorder(BORDER_STYLE, BORDER_WIDTH);
    slidingPanelModelNG.SetBackgroundMask(BACKGROUND_COLOR_VALUE);
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    /**
     * @tc.steps: step2. change slidingPanelPattern->isShow_, child.
     * @tc.expected: slidingPanelPattern->isShow_ is correct.
     */
    auto layoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto isShow = layoutProperty->GetIsShowValue(false);
    EXPECT_TRUE(isShow);
    slidingPanelPattern->isShow_ = false;
    EXPECT_TRUE(slidingPanelPattern->isShow_.value() != isShow);
    slidingPanelPattern->InitializeLayoutProps();
    EXPECT_FALSE(slidingPanelPattern->isShow_.value() != isShow);

    auto host = slidingPanelPattern->GetHost();
    auto child = host->GetChildren();
    auto tempLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(tempLayoutProperty, nullptr);
    auto frameNode_test = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    for (int i = 0; i < 3; i++) {
        child.push_back(frameNode_test);
    }
    EXPECT_TRUE(child.size() > 2);
    host->Clean(false, false);
    child.clear();
    EXPECT_TRUE(child.empty());
    slidingPanelPattern->InitializeLayoutProps();
    EXPECT_TRUE(slidingPanelPattern->isShow_);
}
} // namespace OHOS::Ace::NG