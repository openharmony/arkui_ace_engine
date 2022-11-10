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

#include <optional>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/button_layout_algorithm.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/button_view.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

const float BUTTON_WIDTH = 150.0f;
const float BUTTON_HEIGHT = 75.0f;
const float BUTTON_ONLY_HAS_WIDTH_VALUE = 500.0f;
const float TEXT_WIDTH = 200.0f;
const float TEXT_HEIGHT = 100.0f;
const char TEXT_ETS_TAG[] = "Text";
const char CREATE_VALUE[] = "Hello World";
const SizeF BUTTON_SIZE(BUTTON_WIDTH, BUTTON_HEIGHT);
const SizeF TEXT_SIZE(TEXT_WIDTH, TEXT_HEIGHT);
const SizeF BUTTON_ONLY_HAS_WIDTH_SIZE(BUTTON_ONLY_HAS_WIDTH_VALUE, BUTTON_ONLY_HAS_WIDTH_VALUE);

namespace {

} // namespace

class ButtonLayoutTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: ButtonLayoutTest001
 * @tc.desc: Set an item with alignrules with Button and check it.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonLayoutTestNg, ButtonLayoutTest001, TestSize.Level1)
{
    ButtonView::CreateWithLabel(CREATE_VALUE);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); 
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_FALSE(frameNode == nullptr);
    auto textNode = FrameNode::CreateFrameNode(
            TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(textNode == nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_FALSE(textLayoutProperty == nullptr);
    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textNode->SetInternal();
    frameNode->AddChild(textNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    EXPECT_FALSE(buttonPattern == nullptr);
    auto buttonLayoutProperty = layoutWrapper.GetLayoutProperty();
    EXPECT_FALSE(buttonLayoutProperty == nullptr);
    auto buttonLayoutAlgorithm = buttonPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(buttonLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(buttonLayoutAlgorithm));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(BUTTON_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = BUTTON_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);

    buttonLayoutAlgorithm->Measure(&layoutWrapper);
    buttonLayoutAlgorithm->Layout(&layoutWrapper);

    EXPECT_EQ(
        layoutWrapper.GetGeometryNode()->GetFrameSize(), BUTTON_SIZE);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameOffset(), OffsetF());
}

/**
 * @tc.name: ButtonLayoutTest002
 * @tc.desc: Set an item with alignrules with Button and check it.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonLayoutTestNg, ButtonLayoutTest002, TestSize.Level1)
{
    ButtonView::CreateWithLabel(CREATE_VALUE);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); 
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_FALSE(frameNode == nullptr);
    auto textNode = FrameNode::CreateFrameNode(
            TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(textNode == nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_FALSE(textLayoutProperty == nullptr);
    textLayoutProperty->UpdateContent(CREATE_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    textLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    textLayoutProperty->UpdateContentConstraint();
    textNode->SetInternal();
    frameNode->AddChild(textNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(textNode, geometryNode, textLayoutProperty);
    auto textPattern = textNode->GetPattern<TextPattern>();
    EXPECT_FALSE(textPattern == nullptr);
    auto textLayoutAlgorithm = textPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(textLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(textLayoutAlgorithm));
    textLayoutAlgorithm->Measure(&layoutWrapper);
    textLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), TEXT_SIZE);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameOffset(), OffsetF());
}

/**
 * @tc.name: ButtonLayoutTest003
 * @tc.desc: Set an item with alignrules with Button and check it.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonLayoutTestNg, ButtonLayoutTest003, TestSize.Level1)
{
    ButtonView::CreateWithLabel(CREATE_VALUE);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); 
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_FALSE(frameNode == nullptr);
    auto textNode = FrameNode::CreateFrameNode(
            TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(textNode == nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_FALSE(textLayoutProperty == nullptr);
    textLayoutProperty->UpdateContent(CREATE_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    textLayoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    textLayoutProperty->UpdateContentConstraint();
    textNode->SetInternal();
    frameNode->AddChild(textNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto buttonLayoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_FALSE(buttonLayoutProperty == nullptr);
    buttonLayoutProperty->UpdateType(ButtonType::CIRCLE);
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    EXPECT_FALSE(buttonPattern == nullptr);
    auto buttonLayoutAlgorithm = buttonPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(buttonLayoutAlgorithm == nullptr);
    LayoutConstraintF buttonLayoutConstraint;
    buttonLayoutConstraint.selfIdealSize.SetWidth(BUTTON_ONLY_HAS_WIDTH_VALUE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(buttonLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    layoutWrapper.SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(buttonLayoutAlgorithm));
    buttonLayoutAlgorithm->Measure(&layoutWrapper);
    buttonLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), BUTTON_ONLY_HAS_WIDTH_SIZE);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameOffset(), OffsetF());
}

} // namespace OHOS::Ace::NG