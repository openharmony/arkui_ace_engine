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

#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#define private public
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/panel/sliding_panel_event_hub.h"
#include "core/components_ng/pattern/panel/sliding_panel_layout_algorithm.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"
#include "core/components_ng/pattern/panel/sliding_panel_pattern.h"
#include "core/event/ace_events.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool SLIDING_PANEL_SHOW = true;
constexpr bool SLIDING_PANEL_LAYOUT_PROPERTY_HAS_DRAG_BAR = false;
constexpr bool SLIDING_PANEL_HAS_DRAG_BAR_FALSE = false;
constexpr bool SLIDING_PANEL_HAS_DRAG_BAR_TRUE = true;

constexpr float ZERO = 0.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float PANEL_HEIGHT = 900.0f;
constexpr float HEIGHT_1 = 100.0f;
constexpr float HEIGHT_2 = 400.0f;
constexpr float START_X = 50.0f;
constexpr float START_Y = 100.0f;
constexpr float MAIN_DELTA = 80.0f;
constexpr float MAIN_VELOCITY = 500.0f;
constexpr float CURRENT_OFFSET = 200.f;
constexpr float DRAG_LENGTH = 100.0f;
constexpr float DRAG_VELOCITY = 50.0f;
constexpr float VELOCITY_THRESHOLD = 1000.0; // Move 1000px per second.
constexpr float FULL_MIN_BOUNDARY = 500.0f;
constexpr float FULL_HALF_BOUNDARY = 800.0f;
constexpr float HALF_MINI_BOUNDARY = 200.0f;
constexpr float TARGET_LOCATION = 480.0f;
constexpr float DEFAULT_BLANK_HEIGHT_MODE_HALF = 568.0f;

const Offset START_POINT(START_X, START_Y);
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
constexpr Color BACKGROUND_COLOR_VALUE = Color(0XFFFF0000);
constexpr Color BORDER_COLOR = Color(0XFFDD0000);
constexpr Dimension BORDER_WIDTH = 5.0_px;
constexpr Dimension SLIDING_PANEL_MINI_HEIGHT = 50.0_px;
constexpr Dimension SLIDING_PANEL_HALF_HEIGHT = 300.0_px;
constexpr Dimension SLIDING_PANEL_FULL_HEIGHT = 600.0_px;
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
};

class PanelPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateSlidingPanel(const TestProperty& testProperty);
};

void PanelPatternTestNg::SetUp() {}
void PanelPatternTestNg::TearDown() {}

PaddingProperty CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

RefPtr<FrameNode> PanelPatternTestNg::CreateSlidingPanel(const TestProperty& testProperty)
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

    return ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

/**
 * @tc.name: PanelPatternTest001
 * @tc.desc: Verify whether the layout property, layoutAlgorithm and event functions are created.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest001, TestSize.Level1)
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
    slidingPanelModelNG.Pop();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get pattern and create layout property, layoutAlgorithm, event.
     * @tc.expected: step2. related function is called.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);
    auto slidingPanelLayoutProperty = slidingPanelPattern->CreateLayoutProperty();
    EXPECT_FALSE(slidingPanelLayoutProperty == nullptr);
    auto layoutAlgorithm = slidingPanelPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    auto eventHub = slidingPanelPattern->GetEventHub<SlidingPanelEventHub>();
    EXPECT_FALSE(eventHub == nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithmWrapper == nullptr);
    auto slidingPanelLayoutAlgorithm =
        AceType::DynamicCast<SlidingPanelLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_FALSE(slidingPanelLayoutAlgorithm == nullptr);
}

/**
 * @tc.name: PanelPatternTest002
 * @tc.desc: Test event function of slidingPanel.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);

    /**
     * @tc.steps: step2. set slidingPanel event.
     * @tc.expected: step2. function is called.
     */
    auto height_1 = HEIGHT_1;
    auto onHeightChange = [&height_1](float isHeight) { height_1 = isHeight; };
    slidingPanelModelNG.SetOnHeightChange(onHeightChange);

    auto height_2 = HEIGHT_2;
    PanelMode mode = PanelMode::MINI;
    auto sizeChangeEvent = [&mode, &height_2](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<SlidingPanelSizeChangeEvent>(info);
        mode = eventInfo->GetMode();
        height_2 = eventInfo->GetHeight();
    };
    slidingPanelModelNG.SetOnSizeChange(sizeChangeEvent);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto heightEventHub = frameNode->GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(heightEventHub);
    auto changeEvent = frameNode->GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(changeEvent);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    heightEventHub->FireHeightChangeEvent(HEIGHT_2);
    EXPECT_EQ(height_1, HEIGHT_2);
    changeEvent->FireSizeChangeEvent(PanelMode::HALF, FULL_SCREEN_WIDTH, HEIGHT_2);
    EXPECT_EQ(mode, PanelMode::HALF);
    EXPECT_EQ(height_2, HEIGHT_2);
}

/**
 * @tc.name: PanelPatternTest003
 * @tc.desc: Test all the properties of slidingPanel.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of panel.
     */
    TestProperty testProperty;
    testProperty.panelType = std::make_optional(PANEL_TYPE_VALUE);
    testProperty.panelMode = std::make_optional(PANEL_MODE_VALUE);
    testProperty.hasDragBar = std::make_optional(SLIDING_PANEL_HAS_DRAG_BAR_FALSE);
    testProperty.miniHeight = std::make_optional(SLIDING_PANEL_MINI_HEIGHT);
    testProperty.halfHeight = std::make_optional(SLIDING_PANEL_HALF_HEIGHT);
    testProperty.fullHeight = std::make_optional(SLIDING_PANEL_FULL_HEIGHT);
    testProperty.isShow = std::make_optional(SLIDING_PANEL_SHOW);

    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<FrameNode> frameNode = CreateSlidingPanel(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<SlidingPanelLayoutProperty> slidingPanelLayoutProperty =
        AceType::DynamicCast<SlidingPanelLayoutProperty>(layoutProperty);
    EXPECT_NE(slidingPanelLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_EQ(slidingPanelLayoutProperty->GetPanelType(), PANEL_TYPE_VALUE);
    EXPECT_EQ(slidingPanelLayoutProperty->GetPanelMode(), PANEL_MODE_VALUE);
    EXPECT_EQ(slidingPanelLayoutProperty->GetHasDragBar(), SLIDING_PANEL_HAS_DRAG_BAR_FALSE);
    EXPECT_EQ(slidingPanelLayoutProperty->GetMiniHeight(), SLIDING_PANEL_MINI_HEIGHT);
    EXPECT_EQ(slidingPanelLayoutProperty->GetHalfHeight(), SLIDING_PANEL_HALF_HEIGHT);
    EXPECT_EQ(slidingPanelLayoutProperty->GetFullHeight(), SLIDING_PANEL_FULL_HEIGHT);
    EXPECT_EQ(slidingPanelLayoutProperty->GetIsShow(), SLIDING_PANEL_SHOW);
}

/**
 * @tc.name: PanelPatternTest004
 * @tc.desc: Test panel onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHalfHeight(SLIDING_PANEL_HALF_HEIGHT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    frameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);
    auto slidingPanelLayoutProperty = slidingPanelPattern->CreateLayoutProperty();
    EXPECT_FALSE(slidingPanelLayoutProperty == nullptr);
    auto eventHub = slidingPanelPattern->CreateEventHub();
    EXPECT_FALSE(eventHub == nullptr);
    slidingPanelModelNG.SetFullHeight(SLIDING_PANEL_FULL_HEIGHT);
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_LAYOUT_PROPERTY_HAS_DRAG_BAR);
    auto newFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(newFrameNode == nullptr);
    /**
     * @tc.steps: step3. frameNode markOnModifyDone.
     * @tc.expected: step3. check whether the properties is correct.
     */
    newFrameNode->MarkModifyDone();
    auto layoutProperty = newFrameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    EXPECT_EQ(layoutProperty->GetFullHeight().value_or(Dimension(700)).Value(), SLIDING_PANEL_FULL_HEIGHT.Value());
    EXPECT_EQ(layoutProperty->GetHasDragBar().value_or(true), SLIDING_PANEL_LAYOUT_PROPERTY_HAS_DRAG_BAR);
}

/**
 * @tc.name: PanelPatternTest005
 * @tc.desc: Test panel pattern OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelMode(PanelMode::FULL);
    auto panelFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(panelFrameNode == nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(panelFrameNode, geometryNode, panelFrameNode->GetLayoutProperty());
    auto panelPattern = panelFrameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(panelPattern == nullptr);
    auto panelLayoutProperty = panelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(panelLayoutProperty == nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<SlidingPanelLayoutAlgorithm>(panelPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(PANEL_HEIGHT)));

    /**
     * @tc.steps: step4. frameNode onDirtyLayoutWrapperSwap.
     */
    DirtySwapConfig config;
    config.skipLayout = false;
    config.skipMeasure = false;
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
    EXPECT_TRUE(flag == true);
}

/**
 * @tc.name: PanelPatternTest006
 * @tc.desc: Test panel pattern HandleDragStart .
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHalfHeight(SLIDING_PANEL_HALF_HEIGHT);
    slidingPanelModelNG.SetPanelType(PANEL_PANEL_TYPE[0]);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get pattern and test handleDrag.
     * @tc.expected: step2. check whether the gestureEvent info is correct.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);
    auto panelLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(panelLayoutProperty == nullptr);
    slidingPanelPattern->isAnimating_ = false;
    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->dragStartCurrentOffset_ = ZERO;
    slidingPanelPattern->mode_ = panelLayoutProperty->GetPanelMode().value_or(PanelMode::HALF);
    slidingPanelPattern->type_ = panelLayoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
    slidingPanelPattern->previousMode_ = slidingPanelPattern->mode_.value_or(PanelMode::HALF);
    slidingPanelPattern->defaultBlankHeights_[slidingPanelPattern->mode_.value_or(PanelMode::HALF)] =
        DEFAULT_BLANK_HEIGHT_MODE_HALF;

    GestureEvent startInfo;
    startInfo.SetLocalLocation(START_POINT);
    slidingPanelPattern->HandleDragStart(startInfo.GetLocalLocation());
    EXPECT_TRUE(startInfo.GetLocalLocation() == START_POINT);

    GestureEvent endInfo;
    endInfo.SetMainVelocity(MAIN_VELOCITY);
    slidingPanelPattern->HandleDragEnd(static_cast<float>(endInfo.GetMainVelocity()));
    EXPECT_TRUE(endInfo.GetMainVelocity() == MAIN_VELOCITY);
}

/**
 * @tc.name: PanelPatternTest007
 * @tc.desc: Test panel pattern HandleDragUpdate .
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHalfHeight(SLIDING_PANEL_HALF_HEIGHT);
    slidingPanelModelNG.SetPanelType(PANEL_PANEL_TYPE[1]);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get pattern and test handleDrag.
     * @tc.expected: step2. check whether the gestureEvent info is correct.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);
    auto panelLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(panelLayoutProperty == nullptr);
    slidingPanelPattern->isAnimating_ = false;
    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->dragStartCurrentOffset_ = ZERO;
    slidingPanelPattern->mode_ = panelLayoutProperty->GetPanelMode().value_or(PanelMode::HALF);
    slidingPanelPattern->type_ = panelLayoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
    slidingPanelPattern->previousMode_ = slidingPanelPattern->mode_.value_or(PanelMode::HALF);
    slidingPanelPattern->defaultBlankHeights_[slidingPanelPattern->mode_.value_or(PanelMode::HALF)] =
        DEFAULT_BLANK_HEIGHT_MODE_HALF;
    slidingPanelPattern->fullHalfBoundary_ = FULL_HALF_BOUNDARY;
    slidingPanelPattern->halfMiniBoundary_ = HALF_MINI_BOUNDARY;

    GestureEvent updateInfo;
    updateInfo.SetMainDelta(MAIN_DELTA);
    slidingPanelPattern->HandleDragUpdate(updateInfo);
    EXPECT_TRUE(updateInfo.GetMainDelta() == MAIN_DELTA);

    GestureEvent endInfo;
    endInfo.SetMainVelocity(MAIN_VELOCITY);
    slidingPanelPattern->HandleDragEnd(static_cast<float>(endInfo.GetMainVelocity()));
    EXPECT_TRUE(endInfo.GetMainVelocity() == MAIN_VELOCITY);
}

/**
 * @tc.name: PanelPatternTest008
 * @tc.desc: Test panel pattern HandleDragEnd .
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetHalfHeight(SLIDING_PANEL_HALF_HEIGHT);
    slidingPanelModelNG.SetPanelType(PANEL_PANEL_TYPE[2]);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get pattern and test handleDrag.
     * @tc.expected: step2. check whether the gestureEvent info is correct.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);
    auto panelLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(panelLayoutProperty == nullptr);
    slidingPanelPattern->isAnimating_ = false;
    slidingPanelPattern->mode_ = panelLayoutProperty->GetPanelMode().value_or(PanelMode::HALF);
    slidingPanelPattern->type_ = panelLayoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR);
    slidingPanelPattern->previousMode_ = slidingPanelPattern->mode_.value_or(PanelMode::HALF);

    GestureEvent endInfo;
    endInfo.SetMainVelocity(MAIN_VELOCITY);
    slidingPanelPattern->HandleDragEnd(static_cast<float>(endInfo.GetMainVelocity()));
    EXPECT_TRUE(endInfo.GetMainVelocity() == MAIN_VELOCITY);
}

/**
 * @tc.name: PanelPatternTest009
 * @tc.desc: Test panel pattern CalculateModeTypeMini.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get pattern and update pattern member variable.
     * @tc.expected: step2. check whether CalculateModeTypeMini function can be executed.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);

    // Drag velocity not reached to threshold, mode based on the location.
    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->fullMiniBoundary_ = FULL_MIN_BOUNDARY;
    slidingPanelPattern->CalculateModeTypeMini(DRAG_LENGTH, DRAG_VELOCITY);

    slidingPanelPattern->currentOffset_ = FULL_MIN_BOUNDARY;
    slidingPanelPattern->fullMiniBoundary_ = FULL_MIN_BOUNDARY;
    slidingPanelPattern->CalculateModeTypeMini(DRAG_LENGTH, DRAG_VELOCITY);

    // Drag velocity reached to threshold, mode based on the drag direction.
    slidingPanelPattern->CalculateModeTypeMini(DRAG_LENGTH, VELOCITY_THRESHOLD);
    slidingPanelPattern->CalculateModeTypeMini(DRAG_LENGTH, -VELOCITY_THRESHOLD);
}

/**
 * @tc.name: PanelPatternTest0010
 * @tc.desc: Test panel pattern CalculateModeTypeFold.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get pattern and update pattern member variable.
     * @tc.expected: step2. check whether CalculateModeTypeFold function can be executed.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);

    // Drag velocity not reached to threshold, mode based on the location.
    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->fullHalfBoundary_ = FULL_HALF_BOUNDARY;
    slidingPanelPattern->halfMiniBoundary_ = HALF_MINI_BOUNDARY;
    slidingPanelPattern->CalculateModeTypeFold(DRAG_LENGTH, DRAG_VELOCITY);

    slidingPanelPattern->currentOffset_ = FULL_HALF_BOUNDARY;
    slidingPanelPattern->CalculateModeTypeFold(DRAG_LENGTH, DRAG_VELOCITY);

    // Drag velocity reached to threshold, mode based on the drag direction.
    slidingPanelPattern->defaultBlankHeights_[PanelMode::HALF] = DEFAULT_BLANK_HEIGHT_MODE_HALF;
    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->CalculateModeTypeFold(DRAG_LENGTH, VELOCITY_THRESHOLD);

    slidingPanelPattern->currentOffset_ = DEFAULT_BLANK_HEIGHT_MODE_HALF;
    slidingPanelPattern->CalculateModeTypeFold(DRAG_LENGTH, VELOCITY_THRESHOLD);

    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->CalculateModeTypeFold(DRAG_LENGTH, -VELOCITY_THRESHOLD);

    slidingPanelPattern->currentOffset_ = DEFAULT_BLANK_HEIGHT_MODE_HALF;
    slidingPanelPattern->CalculateModeTypeFold(DRAG_LENGTH, -VELOCITY_THRESHOLD);
}

/**
 * @tc.name: PanelPatternTest0011
 * @tc.desc: Test panel pattern CalculateModeTypeFold.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get pattern and update pattern member variable.
     * @tc.expected: step2. check whether CalculateModeTypeFold function can be executed.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);

    // Drag velocity not reached to threshold, mode based on the location.
    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->fullHalfBoundary_ = FULL_HALF_BOUNDARY;
    slidingPanelPattern->CalculateModeTypeTemp(DRAG_LENGTH, DRAG_VELOCITY);

    slidingPanelPattern->currentOffset_ = FULL_HALF_BOUNDARY;
    slidingPanelPattern->CalculateModeTypeTemp(DRAG_LENGTH, DRAG_VELOCITY);

    // Drag velocity reached to threshold, mode based on the drag direction.
    slidingPanelPattern->currentOffset_ = CURRENT_OFFSET;
    slidingPanelPattern->CalculateModeTypeTemp(DRAG_LENGTH, VELOCITY_THRESHOLD);
    slidingPanelPattern->CalculateModeTypeTemp(DRAG_LENGTH, -VELOCITY_THRESHOLD);
}

/**
 * @tc.name: PanelPatternTest0012
 * @tc.desc: Test panel pattern AnimateTo.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get pattern, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto panelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(panelPattern == nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<SlidingPanelLayoutAlgorithm>(panelPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper and measure layout.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(PANEL_HEIGHT)));
    panelPattern->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4.  update pattern member variable.
     * @tc.expected: step4. check whether AnimateTo function can be executed.
     */
    panelPattern->currentOffset_ = CURRENT_OFFSET;
    panelPattern->AnimateTo(TARGET_LOCATION, PANEL_MODE_VALUE);
}

/**
 * @tc.name: PanelPatternTest0013
 * @tc.desc: Test panel pattern GetDragBarNode GetPanelType GetPanelMode.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get pattern.
     * @tc.expected: step2. check whether some function can be executed.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);
    auto panelLayoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    EXPECT_FALSE(panelLayoutProperty == nullptr);

    auto panelDragBar = slidingPanelPattern->GetDragBarNode();
    auto panelMode = slidingPanelPattern->GetPanelMode();
    EXPECT_TRUE(panelMode == panelLayoutProperty->GetPanelMode().value_or(PanelMode::HALF));
    auto panelType = slidingPanelPattern->GetPanelType();
    EXPECT_TRUE(panelType == panelLayoutProperty->GetPanelType().value_or(PanelType::FOLDABLE_BAR));
}

/**
 * @tc.name: PanelPatternTest0014
 * @tc.desc: Test panel pattern OnAnimationStop UpdateCurrentOffset UpdateCurrentOffsetOnAnimate.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest0014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get pattern, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto panelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(panelPattern == nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<SlidingPanelLayoutAlgorithm>(panelPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper and measure layout.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(PANEL_HEIGHT)));
    panelPattern->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. get pattern.
     * @tc.expected: step4. check whether some function can be executed.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    EXPECT_FALSE(slidingPanelPattern == nullptr);

    slidingPanelPattern->OnAnimationStop();
    EXPECT_TRUE(slidingPanelPattern->isAnimating_ == false);
    slidingPanelPattern->UpdateCurrentOffset(CURRENT_OFFSET);
    slidingPanelPattern->UpdateCurrentOffsetOnAnimate(CURRENT_OFFSET);
}

} // namespace OHOS::Ace::NG
