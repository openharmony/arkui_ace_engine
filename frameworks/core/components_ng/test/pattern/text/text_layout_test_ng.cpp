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

#define private public

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/paragraph.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

constexpr float RK356_WIDTH = 720.0f;
constexpr float RK356_HEIGHT = 1136.0f;
constexpr float TEXT_WIDTH = 100.0f;
constexpr float TEXT_HEIGHT = 75.0f;
constexpr Dimension BASELINE_OFFSET_VALUE = Dimension(20, DimensionUnit::PX);
constexpr Dimension ADAPT_MIN_FONT_SIZE_VALUE = Dimension(50, DimensionUnit::PX);
constexpr Dimension ADAPT_MAX_FONT_SIZE_VALUE = Dimension(80, DimensionUnit::PX);
constexpr Dimension ADAPT_FONT_SIZE_STEP_VALUE = Dimension(10, DimensionUnit::PX);
const std::string CREATE_VALUE = "Hello World";
const SizeF CONTAINER_SIZE(RK356_WIDTH, RK356_HEIGHT);
const SizeF TEXT_SIZE(TEXT_WIDTH, TEXT_HEIGHT);

} // namespace

class TextLayoutTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void TextLayoutTestNg::SetUp() {}

void TextLayoutTestNg::TearDown() {}
/**
 * @tc.name: TextCreatParagraphTest001
 * @tc.desc: Correctly create Paragraph only Set content.
 * @tc.type: FUNC
 */
HWTEST_F(TextLayoutTestNg, TextCreatParagraphTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(textFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    EXPECT_FALSE(textPattern == nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_FALSE(textLayoutProperty == nullptr);

    /**
     * @tc.steps: step2. set Content.
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    EXPECT_FALSE(textLayoutAlgorithm == nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    auto siezX =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. check if it correctly create paragraph and the width and height.
     */

    auto paragraph = textLayoutAlgorithm->GetParagraph();
    EXPECT_FALSE(paragraph == nullptr);
    EXPECT_TRUE(paragraph->GetMaxWidth() == 150.0);
    EXPECT_TRUE(siezX->Height() == 50.0);
}

/**
 * @tc.name: TextLayoutTest001
 * @tc.desc: Set content , width and height to Text and the check result.
 * @tc.type: FUNC
 */
HWTEST_F(TextLayoutTestNg, TextLayoutTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(textFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    EXPECT_FALSE(textPattern == nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_FALSE(textLayoutProperty == nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * content: CREATE_VALUE
     * width: 100.0f
     * height: 75.0f
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. check the size.
     */

    auto paragraph = textLayoutAlgorithm->GetParagraph();
    EXPECT_TRUE(paragraph->GetMaxWidth() == TEXT_WIDTH);
}

/**
 * @tc.name: TextLayoutTest002
 * @tc.desc: set baselineOffset and maxsize of Text check height
 * @tc.type: FUNC
 */
HWTEST_F(TextLayoutTestNg, TextLayoutTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(textFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    EXPECT_FALSE(textPattern == nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_FALSE(textLayoutProperty == nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * baselineOffset: 20_px
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto sizeX =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. check the size.
     */

    EXPECT_EQ(sizeX->Height(), BASELINE_OFFSET_VALUE.Value() + 50.0);
}

/**
 * @tc.name: TextLayoutTest003
 * @tc.desc: set minFontSize and maxFontSize of Text check then check
 * @tc.type: FUNC
 */
HWTEST_F(TextLayoutTestNg, TextLayoutTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(textFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    EXPECT_FALSE(textPattern == nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_FALSE(textLayoutProperty == nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * minFontSize: 50_px
     * macFontSize: 80_px
     */

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    TextStyle textStyle;
    textStyle.SetTextAlign(TextAlign::CENTER);
    textStyle.SetAdaptTextSize(ADAPT_MIN_FONT_SIZE_VALUE, ADAPT_MAX_FONT_SIZE_VALUE);
    textStyle.SetAdaptFontSizeStep(ADAPT_FONT_SIZE_STEP_VALUE);

    auto pipeline = textFrameNode->GetContext();

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto result = textLayoutAlgorithm->AdaptMinTextSize(textStyle, CREATE_VALUE, parentLayoutConstraint, pipeline);

    /**
     * @tc.steps: step4. check the fontsize.
     */

    EXPECT_TRUE(result);
}

} // namespace OHOS::Ace::NG