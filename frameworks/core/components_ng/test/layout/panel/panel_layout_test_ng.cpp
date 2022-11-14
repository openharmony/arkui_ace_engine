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

#include <cstdint>
#include <optional>

#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/panel/sliding_panel_layout_algorithm.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"
#include "core/components_ng/pattern/panel/sliding_panel_node.h"
#include "core/components_ng/pattern/panel/sliding_panel_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const bool SLIDING_PANEL_SHOW = true;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float ZERO = 0.0f;
constexpr float PANEL_HEIGHT = 900.0f;
constexpr float COLUMN_HEIGHT = 100.0f;
constexpr float ROW_WIDTH = 300.f;
constexpr float ROW_HEIGHT = 100.f;

const SizeF PANEL_SIZE(FULL_SCREEN_WIDTH, PANEL_HEIGHT);
const SizeF COLUMN_SIZE(FULL_SCREEN_WIDTH, COLUMN_HEIGHT);
const SizeF ROW_SIZE(ROW_WIDTH, ROW_HEIGHT);
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const OffsetF ORIGIN_POINT(ZERO, ZERO);
const OffsetF COLUMN_OFFSET(ZERO, ZERO);
const OffsetF ROW_OFFSET(ZERO, COLUMN_HEIGHT);
} // namespace
class PanelLayoutTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void PanelLayoutTestNg::SetUp() {}

void PanelLayoutTestNg::TearDown() {}

PaddingProperty CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

/**
 * @tc.name: PanelLayoutTest001
 * @tc.desc: test panel Layout in different panelMode and panelType
 * @tc.type: FUNC
 */
HWTEST_F(PanelLayoutTestNg, PanelLayoutTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelMode(PanelMode::FULL);
    auto panelFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(panelFrameNode == nullptr);
    auto columnNode = AceType::DynamicCast<NG::FrameNode>(panelFrameNode->GetChildren().front());
    EXPECT_FALSE(columnNode == nullptr);

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
    auto panelLayoutAlgorithm = panelPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(panelLayoutAlgorithm == nullptr);

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
    /* corresponding ets code:
        Panel(true){
        }
        .width('100%')
        .height(900)
        .mode(PanelMode.FULL)
    */

    /**
     * @tc.steps: step3. use layoutAlgorithm to measure and layout.
     * @tc.expected: step3. check whether the value of geometry's frameSize and frameOffset is correct.
     */
    panelLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    panelLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), PANEL_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
}

/**
 * @tc.name: PanelLayoutTest002
 * @tc.desc: test panel Layout in different panelMode and panelType
 * @tc.type: FUNC
 */
HWTEST_F(PanelLayoutTestNg, PanelLayoutTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelMode(PanelMode::HALF);
    slidingPanelModelNG.SetPanelType(PanelType::MINI_BAR);
    auto panelFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(panelFrameNode == nullptr);
    auto columnNode = AceType::DynamicCast<NG::FrameNode>(panelFrameNode->GetChildren().front());
    EXPECT_FALSE(columnNode == nullptr);

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
    auto panelLayoutAlgorithm = panelPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(panelLayoutAlgorithm == nullptr);

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
    /* corresponding ets code:
        Panel(true){
        }
        .width('100%')
        .height(900)
        .mode(PanelMode.Half)
        .type(PanelType.Minibar)
    */

    /**
     * @tc.steps: step3. use layoutAlgorithm to measure and layout.
     * @tc.expected: step3. check whether the value of geometry's frameSize and frameOffset is correct.
     */
    panelLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    panelLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), PANEL_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
}

/**
 * @tc.name: PanelLayoutTest003
 * @tc.desc: test panel Layout in different panelMode and panelType
 * @tc.type: FUNC
 */
HWTEST_F(PanelLayoutTestNg, PanelLayoutTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelMode(PanelMode::MINI);
    slidingPanelModelNG.SetPanelType(PanelType::TEMP_DISPLAY);
    auto panelFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(panelFrameNode == nullptr);
    auto columnNode = AceType::DynamicCast<NG::FrameNode>(panelFrameNode->GetChildren().front());
    EXPECT_FALSE(columnNode == nullptr);

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
    auto panelLayoutAlgorithm = panelPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(panelLayoutAlgorithm == nullptr);

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
    /* corresponding ets code:
        Panel(true){
        }
        .width('100%')
        .height(900)
        .mode(PanelMode.Mini)
        .type(PanelType.Temporary)
    */

    /**
     * @tc.steps: step3. use layoutAlgorithm to measure and layout.
     * @tc.expected: step3. check whether the value of geometry's frameSize and frameOffset is correct.
     */
    panelLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    panelLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), PANEL_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
}

/**
 * @tc.name: PanelLayoutTest004
 * @tc.desc: test panel Layout in different panelMode and panelType
 * @tc.type: FUNC
 */
HWTEST_F(PanelLayoutTestNg, PanelLayoutTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelMode(PanelMode::AUTO);
    slidingPanelModelNG.SetPanelType(PanelType::FOLDABLE_BAR);
    auto panelFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(panelFrameNode == nullptr);
    auto columnNode = AceType::DynamicCast<NG::FrameNode>(panelFrameNode->GetChildren().front());
    EXPECT_FALSE(columnNode == nullptr);

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
    auto panelLayoutAlgorithm = panelPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(panelLayoutAlgorithm == nullptr);

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
    /* corresponding ets code:
        Panel(true){
        }
        .width('100%')
        .height(900)
        .type(PanelType.Foldable)
    */

    /**
     * @tc.steps: step3. use layoutAlgorithm to measure and layout.
     * @tc.expected: step3. check whether the value of geometry's frameSize and frameOffset is correct.
     */
    panelLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    panelLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), PANEL_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
}

/**
 * @tc.name: PanelLayoutTest005
 * @tc.desc:  test panel Layout in different panelMode and panelType.
 * @tc.type: FUNC
 */
HWTEST_F(PanelLayoutTestNg, PanelLayoutTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel and get frameNode.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetPanelMode(PanelMode::HALF);
    slidingPanelModelNG.SetPanelType(PanelType::FOLDABLE_BAR);
    auto panelFrameNode = FrameNode::CreateFrameNode(V2::PANEL_ETS_TAG, 1, AceType::MakeRefPtr<SlidingPanelPattern>());
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
    auto panelLayoutAlgorithm = panelPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(panelLayoutAlgorithm == nullptr);

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

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Panel(true){
        }
        .width('100%')
        .height(900)
        .mode(PanelMode.Half)
        .type(PanelType.Foldable)
    */

    /**
     * @tc.steps: step3. use layoutAlgorithm to measure and layout.
     * @tc.expected: step3. check whether the value of geometry's frameSize and frameOffset is correct.
     */
    panelLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    panelLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), PANEL_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
}
} // namespace OHOS::Ace::NG