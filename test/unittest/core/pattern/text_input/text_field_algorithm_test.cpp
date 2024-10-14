/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "text_input_base.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldAlgorithmTest : public TextInputBases {
public:
};

/**
 * @tc.name: IsAdaptExceedLimit
 * @tc.desc: Test the function IsAdaptExceedLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, IsAdaptExceedLimit, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    SizeF size(50.0f, 460.0f);
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_FALSE(textInputLayoutAlgorithm->IsAdaptExceedLimit(size));
}

/**
 * @tc.name: UpdateTextStyleTextOverflowAndWordBreak001
 * @tc.desc: Test the function UpdateTextStyleTextOverflowAndWordBreak.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyleTextOverflowAndWordBreak001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_DEFAULT);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_);
    EXPECT_EQ(textStyle.GetTextOverflow(), TextOverflow::CLIP);
    layoutProperty_->UpdateTextOverflow(OVERFLOW_ELLIPSIS);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_);
    EXPECT_EQ(textStyle.GetTextOverflow(), OVERFLOW_ELLIPSIS);
}

/**
 * @tc.name: UpdateTextStyleTextOverflowAndWordBreak002
 * @tc.desc: Test the function UpdateTextStyleTextOverflowAndWordBreak.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyleTextOverflowAndWordBreak002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_ELLIPSIS);
    layoutProperty_->UpdateTextOverflow(OVERFLOW_DEFAULT);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_);
    EXPECT_EQ(textStyle.GetTextOverflow(), TextOverflow::CLIP);
}

/**
 * @tc.name: UpdateTextStyleTextOverflowAndWordBreak003
 * @tc.desc: Test the function UpdateTextStyleTextOverflowAndWordBreak.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyleTextOverflowAndWordBreak003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_MARQUEE);
    layoutProperty_->UpdateWordBreak(WORDBREAK_ALL);
    layoutProperty_->UpdateTextOverflow(OVERFLOW_DEFAULT);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_);
    EXPECT_EQ(textStyle.GetWordBreak(), WORDBREAK_ALL);
}

/**
 * @tc.name: UpdateTextStyleTextOverflowAndWordBreak004
 * @tc.desc: Test the function UpdateTextStyleTextOverflowAndWordBreak.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyleTextOverflowAndWordBreak004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_MARQUEE);
    layoutProperty_->UpdateTextOverflow(OVERFLOW_DEFAULT);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, false, true, layoutProperty_);
    EXPECT_EQ(textStyle.GetTextOverflow(), OVERFLOW_ELLIPSIS);
}

/**
 * @tc.name: UpdateTextStyleTextOverflowAndWordBreak005
 * @tc.desc: Test the function UpdateTextStyleTextOverflowAndWordBreak.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyleTextOverflowAndWordBreak005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_MARQUEE);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, false, true, layoutProperty_);
    EXPECT_EQ(textStyle.GetTextOverflow(), OVERFLOW_ELLIPSIS);
}

/**
 * @tc.name: UpdateTextStyleTextOverflowAndWordBreak006
 * @tc.desc: Test the function UpdateTextStyleTextOverflowAndWordBreak.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyleTextOverflowAndWordBreak006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_MARQUEE);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_);
    EXPECT_EQ(textStyle.GetTextOverflow(), TextOverflow::CLIP);
}

/**
 * @tc.name: UpdateTextStyle001
 * @tc.desc: Test the function UpdateTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyle001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    auto pipeline = frameNode_->GetContext();
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    pattern_->AddCounterNode();
    FlushLayoutTask(frameNode_);
    TextStyle textStyle;
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    textInputLayoutAlgorithm->UpdateTextStyleMore(frameNode_, layoutProperty_, textStyle, true);
    textInputLayoutAlgorithm->UpdateTextStyle(frameNode_, layoutProperty_, textFieldTheme, textStyle, true);
}

/**
 * @tc.name: UpdateTextStyle002
 * @tc.desc: Test the function UpdateTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyle002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    auto pipeline = frameNode_->GetContext();
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    pattern_->AddCounterNode();
    FlushLayoutTask(frameNode_);
    TextStyle textStyle;
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateForegroundColorStrategy(ForegroundColorStrategy::INVERT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    textInputLayoutAlgorithm->UpdateTextStyle(frameNode_, layoutProperty_, textFieldTheme, textStyle, false);
}

/**
 * @tc.name: UpdatePlaceholderTextStyle
 * @tc.desc: Test the function UpdatePlaceholderTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdatePlaceholderTextStyle, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    auto pipeline = frameNode_->GetContext();
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    pattern_->AddCounterNode();
    FlushLayoutTask(frameNode_);
    TextStyle textStyle;
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    textInputLayoutAlgorithm->UpdatePlaceholderTextStyle(
        frameNode_, layoutProperty_, textFieldTheme, textStyle, true);
}

/**
 * @tc.name: UpdateCounterNode
 * @tc.desc: Test the function UpdateCounterNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateCounterNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    pattern_->AddCounterNode();
    FlushLayoutTask(frameNode_);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    LayoutConstraintF layoutConstraint;
    layoutProperty_->UpdateTextAlign(TextAlign::END);
    textInputLayoutAlgorithm->UpdateCounterNode(50, 460, layoutConstraint, &layoutWrapper);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(layoutProperty_->GetTextAlign(), TextAlign::END);
}

/**
 * @tc.name: CounterLayout001
 * @tc.desc: Test the function CounterLayout.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CounterLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    pattern_->AddCounterNode();
    FlushLayoutTask(frameNode_);

    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    layoutWrapper.GetGeometryNode()->SetContentSize({ 40.0f, 40.0f });

    textInputLayoutAlgorithm->CounterLayout(&layoutWrapper);
    EXPECT_FALSE(pattern_->IsTextArea());
}

/**
 * @tc.name: CounterLayout002
 * @tc.desc: Test the function CounterLayout.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CounterLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowPasswordIcon(false);
    });
    pattern_->AddCounterNode();
    FlushLayoutTask(frameNode_);

    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);

    textInputLayoutAlgorithm->CounterLayout(&layoutWrapper);
    EXPECT_FALSE(pattern_->IsTextArea());
}

/**
 * @tc.name: CounterLayout003
 * @tc.desc: Test the function CounterLayout.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CounterLayout003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowPasswordIcon(false);
    });
    pattern_->AddCounterNode();
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushLayoutTask(frameNode_);

    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    layoutWrapper.GetGeometryNode()->SetContentSize({ 40.0f, 40.0f });

    textInputLayoutAlgorithm->CounterLayout(&layoutWrapper);
    EXPECT_FALSE(pattern_->IsTextArea());
}

/**
 * @tc.name: HandleTextArea001
 * @tc.desc: Test the function HandleTextArea
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, HandleTextArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    pattern_->AddCounterNode();
    FlushLayoutTask(frameNode_);

    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    layoutWrapper.GetGeometryNode()->SetContentSize({ 40.0f, 40.0f });
    RefPtr<LayoutWrapper> counterNode = pattern_->GetCounterNode().Upgrade();
    float countX = 0;
    textInputLayoutAlgorithm->HandleTextArea(&layoutWrapper, counterNode, pattern_, true, countX);
}

/**
 * @tc.name: HandleTextArea002
 * @tc.desc: Test the function HandleTextArea
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, HandleTextArea002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    pattern_->AddCounterNode();
    FlushLayoutTask(frameNode_);

    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    layoutWrapper.GetGeometryNode()->SetContentSize({ 40.0f, 40.0f });
    RefPtr<LayoutWrapper> counterNode = pattern_->GetCounterNode().Upgrade();
    float countX = 0;
    textInputLayoutAlgorithm->HandleTextArea(&layoutWrapper, counterNode, pattern_, false, countX);
}

/**
 * @tc.name: CounterNodeMeasure
 * @tc.desc: Test the function CounterNodeMeasure.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CounterNodeMeasure, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounterBorder(true);
        model.SetShowPasswordIcon(false);
    });
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    textInputLayoutAlgorithm->UpdateUnitLayout(&layoutWrapper);
    EXPECT_EQ(textInputLayoutAlgorithm->CounterNodeMeasure(1.0f, &layoutWrapper), 0.0);
}

/**
 * @tc.name: CreateParagraph001
 * @tc.desc: Test the function CreateParagraph.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CreateParagraph001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    std::vector<std::string> strVec = { "0", "1", "2" };
    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_ELLIPSIS);
    textInputLayoutAlgorithm->CreateParagraph(textStyle, strVec, "content", true, true);
}

/**
 * @tc.name: CreateParagraph002
 * @tc.desc: Test the function CreateParagraph.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CreateParagraph002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    std::vector<std::string> strVec = { "0", "1", "2" };
    TextStyle textStyle;
    textStyle.SetTextAlign(TextAlign::LEFT);
    textInputLayoutAlgorithm->CreateParagraph(textStyle, strVec, "content", false, false);
    EXPECT_NE(textInputLayoutAlgorithm->paragraph_, nullptr);
}

/**
 * @tc.name: CreateParagraph003
 * @tc.desc: Test the function CreateParagraph.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, CreateParagraph003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    std::vector<std::string> strVec = {"0", "1", "2"};
    TextStyle textStyle;
    textStyle.SetTextAlign(TextAlign::LEFT);
    textStyle.SetMaxLines(1);
    textInputLayoutAlgorithm->CreateParagraph(textStyle, strVec, "content", false, false);
    textInputLayoutAlgorithm->GetTextFieldDefaultHeight();
}

/**
 * @tc.name: AdaptInlineFocusFontSize001
 * @tc.desc: Test the function AdaptInlineFocusFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, AdaptInlineFocusFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    Dimension maxDimension(10);
    textStyle.SetAdaptMaxFontSize(maxDimension);
    Dimension minDimension(1);
    textStyle.SetAdaptMinFontSize(minDimension);
    textStyle.SetTextAlign(TextAlign::LEFT);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    LayoutConstraintF layoutConstraint;
    auto content = "content";
    textInputLayoutAlgorithm->AdaptInlineFocusFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(content, "content");
}

/**
 * @tc.name: AdaptInlineFocusFontSize002
 * @tc.desc: Test the function AdaptInlineFocusFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, AdaptInlineFocusFontSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    Dimension maxDimension(0);
    textStyle.SetAdaptMaxFontSize(maxDimension);
    Dimension minDimension(0);
    textStyle.SetAdaptMinFontSize(minDimension);
    textStyle.SetTextAlign(TextAlign::LEFT);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    LayoutConstraintF layoutConstraint;
    auto content = "content";
    textInputLayoutAlgorithm->AdaptInlineFocusFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(content, "content");
}

/**
 * @tc.name: AdaptInlineFocusFontSize003
 * @tc.desc: Test the function AdaptInlineFocusFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, AdaptInlineFocusFontSize003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    Dimension maxDimension(10);
    textStyle.SetAdaptMaxFontSize(maxDimension);
    Dimension minDimension(0);
    textStyle.SetAdaptMinFontSize(minDimension);
    textStyle.SetTextAlign(TextAlign::LEFT);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize.SetWidth(10);
    layoutConstraint.selfIdealSize.SetHeight(10);
    auto content = "content";
    textInputLayoutAlgorithm->AdaptInlineFocusFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(content, "content");
}

/**
 * @tc.name: AdaptInlineFocusFontSize004
 * @tc.desc: Test the function AdaptInlineFocusFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, AdaptInlineFocusFontSize004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    Dimension maxDimension(0);
    textStyle.SetAdaptMaxFontSize(maxDimension);
    Dimension minDimension(0);
    textStyle.SetAdaptMinFontSize(minDimension);
    textStyle.SetTextAlign(TextAlign::LEFT);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize.SetWidth(0);
    layoutConstraint.selfIdealSize.SetHeight(0);
    auto content = "content";
    textInputLayoutAlgorithm->AdaptInlineFocusFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(content, "content");
}

/**
 * @tc.name: AdaptInlineFocusMinFontSize001
 * @tc.desc: Test the function AdaptInlineFocusMinFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, AdaptInlineFocusMinFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    Dimension maxDimension(0);
    textStyle.SetAdaptMaxFontSize(maxDimension);
    Dimension minDimension(0);
    textStyle.SetAdaptMinFontSize(minDimension);
    textStyle.SetTextAlign(TextAlign::LEFT);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize.SetWidth(0);
    layoutConstraint.selfIdealSize.SetHeight(0);
    auto content = "content";
    textInputLayoutAlgorithm->AdaptInlineFocusMinFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(content, "content");
}

/**
 * @tc.name: AdaptInlineFocusMinFontSize002
 * @tc.desc: Test the function AdaptInlineFocusMinFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, AdaptInlineFocusMinFontSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    Dimension maxDimension(10);
    textStyle.SetAdaptMaxFontSize(maxDimension);
    Dimension minDimension(0);
    textStyle.SetAdaptMinFontSize(minDimension);
    textStyle.SetTextAlign(TextAlign::LEFT);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize.SetWidth(0);
    layoutConstraint.selfIdealSize.SetHeight(0);
    auto content = "content";
    textInputLayoutAlgorithm->AdaptInlineFocusMinFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(content, "content");
}

/**
 * @tc.name: AdaptInlineFocusMinFontSize003
 * @tc.desc: Test the function AdaptInlineFocusMinFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, AdaptInlineFocusMinFontSize003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    TextStyle textStyle;
    Dimension maxDimension(10);
    textStyle.SetAdaptMaxFontSize(maxDimension);
    Dimension minDimension(0);
    textStyle.SetAdaptMinFontSize(minDimension);
    textStyle.SetTextAlign(TextAlign::LEFT);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize.SetWidth(10);
    layoutConstraint.selfIdealSize.SetHeight(10);
    auto content = "content";
    textInputLayoutAlgorithm->AdaptInlineFocusMinFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(content, "content");
}

/**
 * @tc.name: GetCounterNodeAlignment001
 * @tc.desc: Test the function GetCounterNodeAlignment.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, GetCounterNodeAlignment001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    textInputLayoutAlgorithm->GetCounterNodeAlignment(&layoutWrapper);
}

/**
 * @tc.name: AddAdaptFontSizeAndAnimations001
 * @tc.desc: Test the function AddAdaptFontSizeAndAnimations
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, AddAdaptFontSizeAndAnimations001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    });
    TextStyle textStyle;
    LayoutConstraintF layoutConstraint;
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    textInputLayoutAlgorithm->BuildInlineFocusLayoutConstraint(layoutConstraint, &layoutWrapper);
    textInputLayoutAlgorithm->AddAdaptFontSizeAndAnimations(
        textStyle, layoutProperty_, layoutConstraint, &layoutWrapper);
}

/**
 * @tc.name: IsInlineFocusAdaptMinExceedLimit
 * @tc.desc: Test the function IsInlineFocusAdaptMinExceedLimit
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, IsInlineFocusAdaptMinExceedLimit, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    LayoutConstraintF contentConstraint;
    SizeF maxSize;
    uint32_t maxViewLines = 2;
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_FALSE(textInputLayoutAlgorithm->IsInlineFocusAdaptMinExceedLimit(maxSize, maxViewLines));
}

/**
 * @tc.name: DidExceedMaxLines
 * @tc.desc: Test the function DidExceedMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, DidExceedMaxLines, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    SizeF maxSize;
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    EXPECT_FALSE(textInputLayoutAlgorithm->DidExceedMaxLines(maxSize));
}

} // namespace OHOS::Ace::NG //
