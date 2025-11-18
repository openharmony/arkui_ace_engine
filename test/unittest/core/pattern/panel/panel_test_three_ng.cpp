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
constexpr bool SLIDING_PANEL_HAS_DRAG_BAR_TRUE = true;
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
constexpr float CURRENT_OFFSET = 200.f;
constexpr float DRAG_LENGTH = 100.0f;
constexpr float VELOCITY_THRESHOLD = 1000.0; // Move 1000px per second.
constexpr float FULL_HALF_BOUNDARY = 800.0f;
constexpr float HALF_MINI_BOUNDARY = 200.0f;
constexpr float TARGET_LOCATION = 480.0f;
constexpr float DEFAULT_BLANK_HEIGHT_MODE_HALF = 568.0f;
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

class PanelTestThreeNg : public testing::Test {
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

void PanelTestThreeNg::SetUp()
{
    MockPipelineContext::SetUp();
}
void PanelTestThreeNg::TearDown()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> PanelTestThreeNg::CreateSlidingPanel(const TestProperty& testProperty)
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

RefPtr<FrameNode> PanelTestThreeNg::CreateSlidingPanelwithCloseIcon()
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

RefPtr<LayoutWrapperNode> PanelTestThreeNg::CreatChildLayoutWrapperNode(
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
 * @tc.name: PanelTestThreeNg0047
 * @tc.desc: Test SlidingPanelPattern::CalculateModeTypeFold.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0047, TestSize.Level1)
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
    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->fullHalfBoundary_ = FULL_HALF_BOUNDARY;
    slidingPanelPattern->halfMiniBoundary_ = HALF_MINI_BOUNDARY;
    slidingPanelPattern->CalculateModeTypeFold(DRAG_LENGTH, -VELOCITY_THRESHOLD);
    EXPECT_LT(slidingPanelPattern->currentOffset_, slidingPanelPattern->fullHalfBoundary_);
    EXPECT_GE(slidingPanelPattern->currentOffset_, slidingPanelPattern->halfMiniBoundary_);
}

/**
 * @tc.name: PanelTestThreeNg0048
 * @tc.desc: Test panel pattern OnAnimationStop.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0048, TestSize.Level1)
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
    EXPECT_TRUE(slidingPanelPattern->isShowQueue_.empty());
    slidingPanelPattern->isShowQueue_.push(true);
    slidingPanelPattern->isShowQueue_.push(false);
    slidingPanelPattern->OnAnimationStop();
    EXPECT_FALSE(slidingPanelPattern->invisibleFlag_.value_or(true));
}

/**
 * @tc.name: PanelTestThreeNg0049
 * @tc.desc: Test panel pattern CalculateModeTypeTemp.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0049, TestSize.Level1)
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
    slidingPanelPattern->currentOffset_ = -1.0f;
    slidingPanelPattern->fullHalfBoundary_ = FULL_HALF_BOUNDARY;
    slidingPanelPattern->halfMiniBoundary_ = HALF_MINI_BOUNDARY;
    slidingPanelPattern->CalculateModeTypeTemp(DRAG_LENGTH, -VELOCITY_THRESHOLD);
    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->defaultBlankHeights_[PanelMode::HALF] = DEFAULT_BLANK_HEIGHT_MODE_HALF;
    slidingPanelPattern->CalculateModeTypeTemp(DRAG_LENGTH, VELOCITY_THRESHOLD);
    EXPECT_LT(slidingPanelPattern->currentOffset_, slidingPanelPattern->fullHalfBoundary_);
    EXPECT_GE(slidingPanelPattern->currentOffset_, slidingPanelPattern->halfMiniBoundary_);
}

/**
 * @tc.name: PanelTestThreeNg0050
 * @tc.desc: Test panel pattern OnAnimationStop UpdateCurrentOffset and UpdateCurrentOffsetOnAnimate.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0050, TestSize.Level1)
{
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);
    auto host = slidingPanelPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    slidingPanelPattern->UpdateCurrentOffset(1.0f);
    slidingPanelPattern->UpdateCurrentOffsetOnAnimate(1.0f);
}

/**
 * @tc.name: PanelTestThreeNg0051
 * @tc.desc: Test SlidingPanelPattern::ResetLayoutWeight.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0051, TestSize.Level1)
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
    auto layoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto isShow = layoutProperty->GetIsShowValue(false);
    EXPECT_TRUE(isShow);
    slidingPanelPattern->isShow_ = false;
    slidingPanelPattern->ResetLayoutWeight();
    EXPECT_TRUE(slidingPanelPattern->isShow_.value() != isShow);
    auto host = slidingPanelPattern->GetHost();
    auto child = host->GetChildren();
    auto tempLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(tempLayoutProperty, nullptr);
    auto frameNode_test1 = AceType::MakeRefPtr<FrameNode>(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    auto frameNode1 =
        AceType::MakeRefPtr<FrameNode>(V2::COLUMN_ATTRS_ALIGN_ITEMS, 1, AceType::MakeRefPtr<Pattern>(), false);
    frameNode_test1->Clean(false, false);
    frameNode_test1->AddChild(frameNode1);
    host->AddChild(frameNode_test1);
    slidingPanelPattern->ResetLayoutWeight();
    EXPECT_TRUE(slidingPanelPattern->isShow_);
    host->Clean(false, false);
    slidingPanelPattern->ResetLayoutWeight();
    EXPECT_TRUE(slidingPanelPattern->isShow_);
}

/**
 * @tc.name: PanelTestThreeNg0052
 * @tc.desc: Test panel pattern Layout and Measure.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0052, TestSize.Level1)
{
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    EXPECT_FALSE(layoutWrapper == nullptr);
    auto frameNode_test1 = AceType::MakeRefPtr<FrameNode>(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    auto frameNode_test2 =
        AceType::MakeRefPtr<FrameNode>(V2::PANEL_CLOSE_ICON_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    auto layoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_test1, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper1, nullptr);
    auto layoutWrapper2 =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_test2, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper2, nullptr);
    auto panelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(panelPattern == nullptr);
    auto panelLayoutProperty = panelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(panelLayoutProperty == nullptr);
    auto panelLayoutAlgorithm = panelPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(panelLayoutAlgorithm == nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->currentChildCount_ = 2;
    panelLayoutProperty->UpdateCustomHeight(Dimension(0.0));
    panelLayoutProperty->UpdatePanelType(PanelType::CUSTOM);
    geometryNode->padding_ = std::make_unique<MarginPropertyF>();
    geometryNode->padding_->left = 200.0f;
    geometryNode->padding_->right = 200.0f;
    geometryNode->padding_->top = 200.0f;
    geometryNode->padding_->bottom = 200.0f;
    layoutWrapper->geometryNode_ = geometryNode;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(PANEL_HEIGHT)));
    layoutWrapper->childrenMap_.emplace(std::make_pair(0, layoutWrapper1));
    layoutWrapper->childrenMap_.emplace(std::make_pair(1, layoutWrapper2));
    panelLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    panelLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    panelLayoutProperty->UpdatePanelType(PanelType::MINI_BAR);
    panelLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
}

/**
 * @tc.name: PanelTestThreeNg0053
 * @tc.desc: test panel Node Layout and Measure
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create mock theme manager and slidingPanel, Update Padding
     */
    auto panelFrameNode = CreateSlidingPanelwithCloseIcon();
    ASSERT_NE(panelFrameNode, nullptr);
    auto geometryNode = panelFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    PaddingPropertyF padding;
    padding.left = ZERO;
    padding.right = ZERO;
    padding.top = ZERO;
    padding.bottom = ZERO;
    geometryNode->UpdatePaddingWithBorder(padding);
    /**
     * @tc.steps: step2. get childLayoutWrapper and append to panelLayoutWrapper
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        panelFrameNode, panelFrameNode->GetGeometryNode(), panelFrameNode->GetLayoutProperty());
    auto panelPattern = panelFrameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(panelPattern, nullptr);
    auto columnLayoutWrapper = CreatChildLayoutWrapperNode(V2::COLUMN_ETS_TAG, panelFrameNode);
    auto closeIconLayoutWrapper = CreatChildLayoutWrapperNode(V2::PANEL_CLOSE_ICON_ETS_TAG, panelFrameNode);
    layoutWrapper->AppendChild(std::move(columnLayoutWrapper));
    layoutWrapper->AppendChild(std::move(closeIconLayoutWrapper));
    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(PANEL_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    /**
     * @tc.steps: step4. use layoutAlgorithm to measure and layout.
     * @tc.expected: step4. check whether the value of geometry's frameSize and frameOffset is correct.
     */
    auto panelLayoutAlgorithm = panelPattern->CreateLayoutAlgorithm();
    ASSERT_NE(panelLayoutAlgorithm, nullptr);
    panelLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    panelLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), PANEL_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
}

/**
 * @tc.name: PanelTestThreeNg0054
 * @tc.desc: test closeIcon Node Layout and Measure
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create mock theme manager and slidingPanel
     */
    auto panelFrameNode = CreateSlidingPanelwithCloseIcon();
    ASSERT_NE(panelFrameNode, nullptr);
    /**
     * @tc.steps: step2. get childLayoutWrapper and append to closeIconLayoutWrapper
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        panelFrameNode, panelFrameNode->GetGeometryNode(), panelFrameNode->GetLayoutProperty());
    auto panelPattern = panelFrameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(panelPattern, nullptr);
    auto closeIconLayoutWrapper = CreatChildLayoutWrapperNode(V2::PANEL_CLOSE_ICON_ETS_TAG, panelFrameNode);
    auto closeIconNode = AceType::DynamicCast<FrameNode>(panelPattern->GetChildNodeByTag(V2::PANEL_CLOSE_ICON_ETS_TAG));
    auto buttonNode = AceType::DynamicCast<FrameNode>(closeIconNode->GetChildAtIndex(0));
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty();
    RefPtr<LayoutWrapperNode> buttonLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(buttonNode, buttonNode->GetGeometryNode(), buttonLayoutProperty);
    closeIconLayoutWrapper->AppendChild(std::move(buttonLayoutWrapper));
    /**
     * @tc.steps: step3. use layoutAlgorithm to measure and layout.
     * @tc.expected: step3. check measure and layout execute correct.
     */
    auto closeIconLayoutAlgorithm = closeIconNode->GetLayoutAlgorithm();
    ASSERT_NE(closeIconLayoutAlgorithm, nullptr);
    closeIconLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(closeIconLayoutWrapper));
    closeIconLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(closeIconLayoutWrapper));
    auto buttonGeometryNode = buttonLayoutWrapper->GetGeometryNode();
    ASSERT_NE(buttonGeometryNode, nullptr);
    auto closeIconLayoutProperty = closeIconNode->GetLayoutProperty<CloseIconLayoutProperty>();
    ASSERT_NE(closeIconLayoutProperty, nullptr);
    EXPECT_EQ(
        buttonGeometryNode->GetFrameSize().Width(), closeIconLayoutProperty->GetCloseIconWidthValue().ConvertToPx());
    EXPECT_EQ(
        buttonGeometryNode->GetFrameSize().Height(), closeIconLayoutProperty->GetCloseIconHeightValue().ConvertToPx());
}

/**
 * @tc.name: PanelTestThreeNg0055
 * @tc.desc: Test panel pattern SetDragBarCallBack.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0055, TestSize.Level1)
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
    auto layoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto dragBar = slidingPanelPattern->GetDragBarNode();
    ASSERT_NE(dragBar, nullptr);
    auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    auto closeIcon = slidingPanelPattern->GetCloseIconNode();
    ASSERT_NE(closeIcon, nullptr);
    auto closeIconPattern = closeIcon->GetPattern<CloseIconPattern>();
    ASSERT_NE(closeIconPattern, nullptr);
    slidingPanelPattern->SetDragBarCallBack();
    dragBarPattern->clickArrowCallback_();
    slidingPanelPattern->previousMode_ = PanelMode::CUSTOM;
    slidingPanelPattern->SetDragBarCallBack();
    dragBarPattern->clickArrowCallback_();
    slidingPanelPattern->previousMode_ = PanelMode::MINI;
    slidingPanelPattern->SetDragBarCallBack();
    dragBarPattern->clickArrowCallback_();
    EXPECT_EQ(slidingPanelPattern->previousMode_, PanelMode::MINI);
    slidingPanelPattern->type_ = PanelType::TEMP_DISPLAY;
    slidingPanelPattern->mode_ = PanelMode::HALF;
    slidingPanelPattern->SetDragBarCallBack();
    dragBarPattern->clickArrowCallback_();
    slidingPanelPattern->previousMode_ = PanelMode::HALF;
    slidingPanelPattern->mode_ = PanelMode::HALF;
    slidingPanelPattern->SetDragBarCallBack();
    dragBarPattern->clickArrowCallback_();
    EXPECT_EQ(slidingPanelPattern->previousMode_, PanelMode::HALF);
}

/**
 * @tc.name: PanelTestThreeNg0056
 * @tc.desc: Test panel pattern AnimateTo.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0056, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto panelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(panelPattern == nullptr);
    auto layoutProperty = panelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<SlidingPanelLayoutAlgorithm>(panelPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    panelPattern->currentOffset_ = CURRENT_OFFSET;
    panelPattern->AnimateTo(TARGET_LOCATION, PANEL_MODE_VALUE);
    panelPattern->animator_->NotifyStopListener();
}

/**
 * @tc.name: PanelTestThreeNg0057
 * @tc.desc: Test panel pattern InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto panelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(panelPattern == nullptr);
    auto layoutProperty = panelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<SlidingPanelLayoutAlgorithm>(panelPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto hub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    layoutProperty->UpdatePanelType(PanelType::CUSTOM);
    panelPattern->InitPanEvent(gestureHub);
    layoutProperty->UpdatePanelType(PanelType::FOLDABLE_BAR);
    GestureEvent gestureEvent;
    panelPattern->InitPanEvent(gestureHub);
    panelPattern->panEvent_->actionStart_(gestureEvent);
    layoutProperty->UpdatePanelType(PanelType::MINI_BAR);
    panelPattern->InitPanEvent(gestureHub);
    panelPattern->panEvent_->actionUpdate_(gestureEvent);
    layoutProperty->UpdatePanelType(PanelType::TEMP_DISPLAY);
    panelPattern->InitPanEvent(gestureHub);
    panelPattern->panEvent_->actionEnd_(gestureEvent);
}

/**
 * @tc.name: PanelTestThreeNg0058
 * @tc.desc: Test panel pattern GetOrCreateSlidingPanelNode.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0058, TestSize.Level1)
{
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    /**
     * step1. GetLinearLayoutProperty
     */
    auto patternCreator = []() -> RefPtr<Pattern> { return AceType::MakeRefPtr<SlidingPanelPattern>(); };
    ElementRegister::GetInstance()->Clear();
    auto temp = AceType::MakeRefPtr<SlidingPanelNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ElementRegister::GetInstance()->AddReferenced(5, AceType::WeakClaim(AceType::RawPtr(temp)));
    auto columnLayoutProperty = slidingPanelModelNG.GetOrCreateSlidingPanelNode(V2::PANEL_ETS_TAG, 5, patternCreator);
    EXPECT_NE(columnLayoutProperty, nullptr);
    auto panelNode = ElementRegister::GetInstance()->GetSpecificItemById<SlidingPanelNode>(5);
    panelNode->tag_ = V2::PANEL_ETS_TAG;
    columnLayoutProperty = slidingPanelModelNG.GetOrCreateSlidingPanelNode(V2::PANEL_ETS_TAG, 5, patternCreator);
    EXPECT_NE(columnLayoutProperty, nullptr);
}

/**
 * @tc.name: PanelTestThreeNg0059
 * @tc.desc: Test panel pattern GetMaxWidthByScreenSizeType.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0059, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto panelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(panelPattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<SlidingPanelLayoutAlgorithm>(panelPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    panelPattern->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    EXPECT_TRUE(layoutAlgorithm->GetMaxWidthByScreenSizeType(DRAGBAR_SIZE, DRAGBAR_SIZE));
    EXPECT_TRUE(layoutAlgorithm->GetMaxWidthByScreenSizeType(ROW_MAX_SIZE, DRAGBAR_SIZE));
    EXPECT_TRUE(layoutAlgorithm->GetMaxWidthByScreenSizeType(DRAGBAR_SIZE, ROW_MAX_SIZE));
}

/**
 * @tc.name: PanelTestThreeNg0060
 * @tc.desc: Test panel pattern SetDragBarCallBack.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0060, TestSize.Level1)
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
    auto layoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto dragBar = slidingPanelPattern->GetDragBarNode();
    ASSERT_NE(dragBar, nullptr);
    auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    auto closeIcon = slidingPanelPattern->GetCloseIconNode();
    ASSERT_NE(closeIcon, nullptr);
    auto closeIconPattern = closeIcon->GetPattern<CloseIconPattern>();
    ASSERT_NE(closeIconPattern, nullptr);
    slidingPanelPattern->previousMode_ = PanelMode::CUSTOM;
    slidingPanelPattern->mode_ = PanelMode::FULL;
    slidingPanelPattern->type_ = PanelType::TEMP_DISPLAY;
    slidingPanelPattern->SetDragBarCallBack();
    dragBarPattern->clickArrowCallback_();
    slidingPanelPattern->mode_ = PanelMode::CUSTOM;
    slidingPanelPattern->SetDragBarCallBack();
    dragBarPattern->clickArrowCallback_();
}

/**
 * @tc.name: PanelTestThreeNg0061
 * @tc.desc: Test panel pattern AnimateTo.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0061, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto panelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(panelPattern == nullptr);
    auto layoutProperty = panelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<SlidingPanelLayoutAlgorithm>(panelPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    layoutProperty->UpdateHasDragBar(false);
    panelPattern->isShowQueue_ = std::queue<bool>();
    panelPattern->isShowQueue_.push(false);
    panelPattern->isShowQueue_.push(true);
    panelPattern->currentOffset_ = CURRENT_OFFSET;
    panelPattern->AnimateTo(TARGET_LOCATION, PANEL_MODE_VALUE);
    panelPattern->animator_->NotifyStopListener();
}

/**
 * @tc.name: PanelTestThreeNg0062
 * @tc.desc: Test panel pattern InitPanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0062, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto panelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(panelPattern == nullptr);
    auto layoutProperty = panelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<SlidingPanelLayoutAlgorithm>(panelPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto hub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    layoutProperty->UpdatePanelType(PanelType::CUSTOM);
    panelPattern->InitPanEvent(gestureHub);
    panelPattern->panEvent_->actionCancel_();
}

/**
 * @tc.name: PanelTestThreeNg0063
 * @tc.desc: Test panel pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0063, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto closeIconTheme = AceType::MakeRefPtr<CloseIconTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(closeIconTheme));
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetShowCloseIcon(SLIDING_PANEL_SHOW_CLOSE_ICON_TRUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);

    auto host = slidingPanelPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCustomHeight(BORDER_WIDTH);
    layoutProperty->UpdatePanelType(PanelType::CUSTOM);
    slidingPanelPattern->OnModifyDone();
}

/**
 * @tc.name: PanelTestThreeNg0064
 * @tc.desc: Test SlidingPanelPattern::IsShowChanged.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0064, TestSize.Level1)
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
    layoutProperty->UpdateHasDragBar(false);
    slidingPanelPattern->previousMode_ = PanelMode::HALF;
    slidingPanelPattern->mode_ = PanelMode::FULL;
    slidingPanelPattern->IsShowChanged(true);
    slidingPanelPattern->IsShowChanged(false);
    EXPECT_EQ(slidingPanelPattern->previousMode_, slidingPanelPattern->mode_);
}

/**
 * @tc.name: PanelTestThreeNg0065
 * @tc.desc: Test SlidingPanelPattern::FirstLayout.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0065, TestSize.Level1)
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
    layoutProperty->UpdateHasDragBar(false);
    slidingPanelPattern->FirstLayout();
}

/**
 * @tc.name: PanelTestThreeNg0066
 * @tc.desc: Test panel pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0066, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto closeIconTheme = AceType::MakeRefPtr<CloseIconTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(closeIconTheme));
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR_TRUE);
    slidingPanelModelNG.SetShowCloseIcon(SLIDING_PANEL_SHOW_CLOSE_ICON_TRUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);
    auto host = slidingPanelPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<SlidingPanelLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCustomHeight(CalcDimension("wrapContent"));
    layoutProperty->UpdatePanelType(PanelType::CUSTOM);
    auto dragBar = slidingPanelPattern->GetDragBarNode();
    ASSERT_NE(dragBar, nullptr);
    auto dragBarPattern = dragBar->GetPattern<DragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->clickArrowCallback_ = []() {};
    auto closeIconNode = slidingPanelPattern->GetCloseIconNode();
    ASSERT_NE(closeIconNode, nullptr);
    auto closeIconPattern = closeIconNode->GetPattern<CloseIconPattern>();
    ASSERT_NE(closeIconPattern, nullptr);
    closeIconPattern->clickButtonCallback_ = []() {};
    layoutProperty->UpdateIsShow(false);
    slidingPanelPattern->isShow_ = true;
    std::queue<bool> test;
    std::swap(test, slidingPanelPattern->isShowQueue_);
    slidingPanelPattern->OnModifyDone();
    EXPECT_FALSE(slidingPanelPattern->isShowQueue_.empty());
}

/**
 * @tc.name: PanelTestThreeNg0067
 * @tc.desc: Test panel pattern Measure and Layout.
 * @tc.type: FUNC
 */
HWTEST_F(PanelTestThreeNg, PanelTestThreeNg0067, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto frameNode1 = AceType::MakeRefPtr<FrameNode>(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    EXPECT_FALSE(frameNode1 == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto panelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(panelPattern == nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<SlidingPanelLayoutAlgorithm>(panelPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->layoutProperty_ = AceType::MakeRefPtr<SlidingPanelLayoutProperty>();
    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(PANEL_HEIGHT)));
    panelPattern->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    auto layoutProperty = AceType::DynamicCast<SlidingPanelLayoutProperty>(layoutWrapper->GetLayoutProperty());
    EXPECT_FALSE(layoutProperty == nullptr);
    auto layoutWrapper_test =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode1, geometryNode, frameNode1->GetLayoutProperty());
    layoutWrapper->currentChildCount_ = 2;
    layoutWrapper->childrenMap_.emplace(std::make_pair(1, layoutWrapper_test));
    layoutProperty->UpdateCustomHeight(CalcDimension("wrapContent"));
    layoutProperty->UpdatePanelType(PanelType::CUSTOM);
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->isFirstLayout_ = true;
    layoutAlgorithm->invisibleFlag_ = true;
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(layoutWrapper->GetGeometryNode()->GetFrameSize(), PANEL_SIZE);
    EXPECT_NE(layoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
    layoutProperty->layoutConstraint_.reset();
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(layoutWrapper->GetGeometryNode()->GetFrameSize(), PANEL_SIZE);
    EXPECT_NE(layoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
}
} // namespace OHOS::Ace::NG