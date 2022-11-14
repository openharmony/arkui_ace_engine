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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/panel/sliding_panel_event_hub.h"
#include "core/components_ng/pattern/panel/sliding_panel_layout_algorithm.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"
#include "core/components_ng/pattern/panel/sliding_panel_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const bool SLIDING_PANEL_SHOW = false;
constexpr PanelType PANEL_TYPE_VALUE = PanelType::MINI_BAR;
constexpr PanelMode PANEL_MODE_VALUE = PanelMode::FULL;
const bool SLIDING_PANEL_HAS_DRAG_BAR = false;
constexpr Dimension SLIDING_PANEL_MINI_HEIGHT = 50.0_px;
constexpr Dimension SLIDING_PANEL_HALF_HEIGHT = 300.0_px;
constexpr Dimension SLIDING_PANEL_FULL_HEIGHT = 600.0_px;
constexpr int32_t HEIGHT_1 = 200;
constexpr Color BACKGROUND_COLOR_VALUE = Color(0XFFFF0000);
void onSizeChange(const BaseEventInfo* info) {};
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
    slidingPanelModelNG.SetHasDragBar(SLIDING_PANEL_HAS_DRAG_BAR);
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto eventHub = frameNode->GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(eventHub);

    /**
     * @tc.steps: step2. set slidingPanel event.
     * @tc.expected: step2. function is called.
     */
    int32_t height = HEIGHT_1;
    auto onHeightChange = [&height](int32_t isHeight) { height = isHeight; };
    slidingPanelModelNG.SetOnHeightChange(onHeightChange);
    slidingPanelModelNG.SetOnSizeChange(onSizeChange);
    auto heightEventHub = frameNode->GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(heightEventHub);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    heightEventHub->FireHeightChangeEvent(HEIGHT_1);
    EXPECT_EQ(height, HEIGHT_1);
}

/**
 * @tc.name: PanelPatternTest003
 * @tc.desc: Test all the properties of slidingPanel.
 * @tc.type: FUNC
 */
HWTEST_F(PanelPatternTestNg, PanelPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of texttimer.
     */
    TestProperty testProperty;
    testProperty.panelType = std::make_optional(PANEL_TYPE_VALUE);
    testProperty.panelMode = std::make_optional(PANEL_MODE_VALUE);
    testProperty.hasDragBar = std::make_optional(SLIDING_PANEL_HAS_DRAG_BAR);
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
    EXPECT_EQ(slidingPanelLayoutProperty->GetHasDragBar(), SLIDING_PANEL_HAS_DRAG_BAR);
    EXPECT_EQ(slidingPanelLayoutProperty->GetMiniHeight(), SLIDING_PANEL_MINI_HEIGHT);
    EXPECT_EQ(slidingPanelLayoutProperty->GetHalfHeight(), SLIDING_PANEL_HALF_HEIGHT);
    EXPECT_EQ(slidingPanelLayoutProperty->GetFullHeight(), SLIDING_PANEL_FULL_HEIGHT);
    EXPECT_EQ(slidingPanelLayoutProperty->GetIsShow(), SLIDING_PANEL_SHOW);
}
} // namespace OHOS::Ace::NG
