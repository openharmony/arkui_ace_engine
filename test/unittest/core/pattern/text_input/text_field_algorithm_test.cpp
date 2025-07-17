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
#include "ui/base/geometry/dimension.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace::NG {

namespace {
const Color STROKE_COLOR_VALUE_0 = Color::FromRGB(255, 100, 100);
const Color STORKE_COLOR_VALUE_1 = Color::FromRGB(255, 255, 100);
} // namespace

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
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_, false);
    EXPECT_EQ(textStyle.GetTextOverflow(), TextOverflow::CLIP);
    layoutProperty_->UpdateTextOverflow(OVERFLOW_ELLIPSIS);
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_, false);
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
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_, false);
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
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_, false);
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
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, false, true, layoutProperty_, false);
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
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, false, true, layoutProperty_, false);
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
    textInputLayoutAlgorithm->UpdateTextStyleTextOverflowAndWordBreak(textStyle, true, true, layoutProperty_, false);
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
    layoutProperty_->UpdateErrorText(u"Error!");
    layoutProperty_->UpdateShowErrorText(true);
    layoutProperty_->UpdateItalicFontStyle(Ace::FontStyle::ITALIC);
    layoutProperty_->UpdateTextIndent(Dimension(10));
    textInputLayoutAlgorithm->UpdateTextStyleMore(frameNode_, layoutProperty_, textStyle, true);
    textInputLayoutAlgorithm->UpdateTextStyle(frameNode_, layoutProperty_, textFieldTheme, textStyle, true);
    textInputLayoutAlgorithm->ErrorLayout(&layoutWrapper);
    EXPECT_EQ(textStyle.GetTextIndent(), Dimension(10));
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
    textInputLayoutAlgorithm->UpdateTextStyle(frameNode_, layoutProperty_, textFieldTheme, textStyle, true);
}

/**
 * @tc.name: UpdateTextStyle003
 * @tc.desc: Test strokeWidth and strokeColor.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextStyle003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetStrokeWidth(Dimension(2.0f));
        model.SetStrokeColor(STORKE_COLOR_VALUE_1);
    });
    auto pipeline = frameNode_->GetContext();
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    pattern_->AddCounterNode();
    FlushLayoutTask(frameNode_);
    TextStyle textStyle;
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());

    textInputLayoutAlgorithm->UpdateTextStyle(frameNode_, layoutProperty_, textFieldTheme, textStyle, true);

    EXPECT_EQ(layoutProperty_->GetStrokeWidth(), Dimension(2.0f));
    EXPECT_EQ(layoutProperty_->GetStrokeColor(), STORKE_COLOR_VALUE_1);
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
    layoutProperty_->UpdatePlaceholderTextAlign(TextAlign::START);
    textInputLayoutAlgorithm->UpdatePlaceholderTextStyle(
        frameNode_, layoutProperty_, textFieldTheme, textStyle, true);
    EXPECT_EQ(textStyle.GetTextOverflow(), TextOverflow::ELLIPSIS);
}

/**
 * @tc.name: LayoutRectTest001
 * @tc.desc: Test the function LayoutRectTest001
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, LayoutRectTest001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT);
    LayoutConstraintF constraint;
    constraint.minSize = SizeF(100, 100);
    constraint.maxSize = SizeF(100, 100);
    constraint.percentReference = SizeF(100, 100);
    frameNode_->GetLayoutProperty()->SetLayoutRect(RectF(0, 0, 100, 100));
    frameNode_->GetLayoutProperty()->UpdateCalcMinSize(CalcSize(CalcLength(200), CalcLength(200)));
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    std::vector<std::u16string> strVec = { u"0", u"1", u"2" };
    TextStyle textStyle;
    auto paragraphData = CreateParagraphData { false, textStyle.GetFontSize().ConvertToPx() };
    textInputLayoutAlgorithm->CreateParagraph(textStyle, strVec, u"content", false, paragraphData);
    float width = textInputLayoutAlgorithm->CalculateContentWidth(constraint, AceType::RawPtr(frameNode_), 0);
    EXPECT_EQ(width, 100);
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
    std::vector<std::u16string> strVec = { u"0", u"1", u"2" };
    TextStyle textStyle;
    textStyle.SetTextOverflow(OVERFLOW_ELLIPSIS);
    auto paragraphData = CreateParagraphData { true, textStyle.GetFontSize().ConvertToPx() };
    textInputLayoutAlgorithm->CreateParagraph(textStyle, strVec, u"content", true, paragraphData);
    EXPECT_EQ(textInputLayoutAlgorithm->GetTextFieldDefaultHeight(), 0.0f);
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
    std::vector<std::u16string> strVec = { u"0", u"1", u"2" };
    TextStyle textStyle;
    textStyle.SetTextAlign(TextAlign::LEFT);
    auto paragraphData = CreateParagraphData { false, textStyle.GetFontSize().ConvertToPx() };
    textInputLayoutAlgorithm->CreateParagraph(textStyle, strVec, u"content", false, paragraphData);
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
    std::vector<std::u16string> strVec = { u"0", u"1", u"2" };
    TextStyle textStyle;
    textStyle.SetTextAlign(TextAlign::LEFT);
    textStyle.SetMaxLines(1);
    auto paragraphData = CreateParagraphData { false, textStyle.GetFontSize().ConvertToPx() };
    textInputLayoutAlgorithm->CreateParagraph(textStyle, strVec, u"content", false, paragraphData);
    EXPECT_EQ(textInputLayoutAlgorithm->GetTextFieldDefaultHeight(), 0.0f);
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
    auto content = u"content";
    textInputLayoutAlgorithm->AdaptInlineFocusFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(StringUtils::Str16ToStr8(content), "content");
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
    auto content = u"content";
    textInputLayoutAlgorithm->AdaptInlineFocusFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(StringUtils::Str16ToStr8(content), "content");
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
    auto content = u"content";
    textInputLayoutAlgorithm->AdaptInlineFocusFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(StringUtils::Str16ToStr8(content), "content");
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
    auto content = u"content";
    textInputLayoutAlgorithm->AdaptInlineFocusFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(StringUtils::Str16ToStr8(content), "content");
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
    auto content = u"content";
    textInputLayoutAlgorithm->AdaptInlineFocusMinFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(StringUtils::Str16ToStr8(content), "content");
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
    auto content = u"content";
    textInputLayoutAlgorithm->AdaptInlineFocusMinFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(StringUtils::Str16ToStr8(content), "content");
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
    auto content = u"content";
    textInputLayoutAlgorithm->AdaptInlineFocusMinFontSize(textStyle, content, 1.0_px, layoutConstraint, &layoutWrapper);
    EXPECT_EQ(StringUtils::Str16ToStr8(content), "content");
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
    EXPECT_TRUE(textInputLayoutAlgorithm->AddAdaptFontSizeAndAnimations(
        textStyle, layoutProperty_, layoutConstraint, &layoutWrapper));
}

/**
 * @tc.name: AddAdaptFontSizeAndAnimations002
 * @tc.desc: Test the function AddAdaptFontSizeAndAnimations
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, AddAdaptFontSizeAndAnimations002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    });
    TextStyle textStyle;
    LayoutConstraintF layoutConstraint;
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    textInputLayoutAlgorithm->BuildInlineFocusLayoutConstraint(layoutConstraint, &layoutWrapper);
    EXPECT_TRUE(textInputLayoutAlgorithm->AddAdaptFontSizeAndAnimations(
        textStyle, layoutProperty_, layoutConstraint, &layoutWrapper));
}

/**
 * @tc.name: AddAdaptFontSizeAndAnimations003
 * @tc.desc: Test the function AddAdaptFontSizeAndAnimations
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, AddAdaptFontSizeAndAnimations003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    });
    TextStyle textStyle;
    LayoutConstraintF layoutConstraint;
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    textInputLayoutAlgorithm->BuildInlineFocusLayoutConstraint(layoutConstraint, &layoutWrapper);
    EXPECT_TRUE(textInputLayoutAlgorithm->AddAdaptFontSizeAndAnimations(
        textStyle, layoutProperty_, layoutConstraint, &layoutWrapper));
}

/**
 * @tc.name: AddAdaptFontSizeAndAnimations004
 * @tc.desc: Test the function AddAdaptFontSizeAndAnimations
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, AddAdaptFontSizeAndAnimations004, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    });
    TextStyle textStyle;
    LayoutConstraintF layoutConstraint;
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, AceType::MakeRefPtr<GeometryNode>(), layoutProperty_);
    auto textInputLayoutAlgorithm =
        AceType::DynamicCast<TextInputLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    textInputLayoutAlgorithm->BuildInlineFocusLayoutConstraint(layoutConstraint, &layoutWrapper);
    EXPECT_TRUE(textInputLayoutAlgorithm->AddAdaptFontSizeAndAnimations(
        textStyle, layoutProperty_, layoutConstraint, &layoutWrapper));
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

/**
 * @tc.name: UpdateTextAreaMaxLines001
 * @tc.desc: Test the function UpdateTextAreaMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextAreaMaxLines001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    GetFocus();

    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    PaddingProperty paddingProperty { .top = CalcLength(300), .bottom = CalcLength(300) };
    paintProperty->UpdatePaddingByUser(paddingProperty);
    MarginProperty margin = { CalcLength(1), CalcLength(3), CalcLength(5), CalcLength(7) };
    paintProperty->UpdateMarginByUser(margin);

    auto textFieldLayoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    TextStyle textStyle;
    textFieldLayoutProperty->UpdateOverflowMode(OverflowMode::SCROLL);
    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::NONE);
    textFieldLayoutProperty->UpdateNormalMaxViewLines(1);
    auto textAreaLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextAreaLayoutAlgorithm>();
    textAreaLayoutAlgorithm->UpdateTextAreaMaxLines(textStyle, textFieldLayoutProperty);
    EXPECT_EQ(textStyle.GetMaxLines(), INT32_MAX);
    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::CLIP);
    textAreaLayoutAlgorithm->UpdateTextAreaMaxLines(textStyle, textFieldLayoutProperty);
    EXPECT_EQ(textStyle.GetMaxLines(), INT32_MAX);

    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textAreaLayoutAlgorithm->UpdateTextAreaMaxLines(textStyle, textFieldLayoutProperty);
    EXPECT_EQ(textStyle.GetMaxLines(), 1);
    
    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::DEFAULT);
    textAreaLayoutAlgorithm->UpdateTextAreaMaxLines(textStyle, textFieldLayoutProperty);
    EXPECT_EQ(textStyle.GetMaxLines(), INT32_MAX);
}

/**
 * @tc.name: UpdateTextAreaMaxLines002
 * @tc.desc: Test the function UpdateTextAreaMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, UpdateTextAreaMaxLines002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    GetFocus();

    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    PaddingProperty paddingProperty { .top = CalcLength(300), .bottom = CalcLength(300) };
    paintProperty->UpdatePaddingByUser(paddingProperty);
    MarginProperty margin = { CalcLength(1), CalcLength(3), CalcLength(5), CalcLength(7) };
    paintProperty->UpdateMarginByUser(margin);

    auto textFieldLayoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    TextStyle textStyle;
    textFieldLayoutProperty->UpdateOverflowMode(OverflowMode::CLIP);
    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::NONE);
    textFieldLayoutProperty->UpdateNormalMaxViewLines(1);
    auto textAreaLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextAreaLayoutAlgorithm>();

    textAreaLayoutAlgorithm->UpdateTextAreaMaxLines(textStyle, textFieldLayoutProperty);
    EXPECT_EQ(textStyle.GetMaxLines(), 1);
}

/**
 * @tc.name: ShouldUseInfiniteMaxLines001
 * @tc.desc: Test the function ShouldUseInfiniteMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, ShouldUseInfiniteMaxLines001, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    GetFocus();
    auto textFieldLayoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    textFieldLayoutProperty->UpdateOverflowMode(OverflowMode::SCROLL);
    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::NONE);
    auto textAreaLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextAreaLayoutAlgorithm>();
    EXPECT_TRUE(textAreaLayoutAlgorithm->ShouldUseInfiniteMaxLines(textFieldLayoutProperty));
}

/**
 * @tc.name: ShouldUseInfiniteMaxLines002
 * @tc.desc: Test the function ShouldUseInfiniteMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, ShouldUseInfiniteMaxLines002, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    GetFocus();
    auto textFieldLayoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    textFieldLayoutProperty->UpdateOverflowMode(OverflowMode::SCROLL);
    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::CLIP);
    auto textAreaLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextAreaLayoutAlgorithm>();
    EXPECT_TRUE(textAreaLayoutAlgorithm->ShouldUseInfiniteMaxLines(textFieldLayoutProperty));
}

/**
 * @tc.name: ShouldUseInfiniteMaxLines003
 * @tc.desc: Test the function ShouldUseInfiniteMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, ShouldUseInfiniteMaxLines003, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    GetFocus();
    auto textFieldLayoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    textFieldLayoutProperty->UpdateOverflowMode(OverflowMode::SCROLL);
    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::DEFAULT);
    auto textAreaLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextAreaLayoutAlgorithm>();
    EXPECT_TRUE(textAreaLayoutAlgorithm->ShouldUseInfiniteMaxLines(textFieldLayoutProperty));
}

/**
 * @tc.name: ShouldUseInfiniteMaxLines004
 * @tc.desc: Test the function ShouldUseInfiniteMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, ShouldUseInfiniteMaxLines004, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    GetFocus();
    auto textFieldLayoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    textFieldLayoutProperty->UpdateOverflowMode(OverflowMode::SCROLL);
    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    auto textAreaLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextAreaLayoutAlgorithm>();
    EXPECT_FALSE(textAreaLayoutAlgorithm->ShouldUseInfiniteMaxLines(textFieldLayoutProperty));
}

/**
 * @tc.name: ShouldUseInfiniteMaxLines005
 * @tc.desc: Test the function ShouldUseInfiniteMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldAlgorithmTest, ShouldUseInfiniteMaxLines005, TestSize.Level1)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::VISIBLE_PASSWORD); });
    GetFocus();
    auto textFieldLayoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    textFieldLayoutProperty->UpdateOverflowMode(OverflowMode::CLIP);
    textFieldLayoutProperty->UpdateTextOverflow(TextOverflow::NONE);
    auto textAreaLayoutAlgorithm = AccessibilityManager::MakeRefPtr<TextAreaLayoutAlgorithm>();
    EXPECT_FALSE(textAreaLayoutAlgorithm->ShouldUseInfiniteMaxLines(textFieldLayoutProperty));
}
} // namespace OHOS::Ace::NG //
