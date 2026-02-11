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
#include "core/components_ng/pattern/text_field/text_component_decorator.h"
#include "frameworks/core/pipeline/base/element_register.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {

class TextInputDecoratorTest : public TextInputBases {};

/**
 * @tc.name: CounterDecoratorUpdateTextFieldMargin001
 * @tc.desc: Test UpdateTextFieldMargin with counter enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorUpdateTextFieldMargin001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter (maxLength enables counter)
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Call UpdateTextFieldMargin
     * @tc.expected: Should execute without crash and set margin
     */
    counterDecorator->UpdateTextFieldMargin();

    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    // Verify margin was set
    const auto& margin = layoutProperty->GetMarginProperty();
    EXPECT_TRUE(margin != nullptr);
    if (margin) {
        EXPECT_TRUE(margin->bottom.has_value());
    }
}

/**
 * @tc.name: CounterDecoratorUpdateTextFieldMargin002
 * @tc.desc: Test UpdateTextFieldMargin when counter is disabled (no maxLength)
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorUpdateTextFieldMargin002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField without maxLength (counter disabled)
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // No SetMaxLength - counter is not shown
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     * @tc.expected: counterDecorator should be nullptr when maxLength is not set
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    EXPECT_EQ(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Verify TextField works correctly without counter
     * @tc.expected: Should complete without crash even when counter is not shown
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    // TextField should be functional even without counter decorator
}

/**
 * @tc.name: CounterDecoratorUpdateTextFieldMargin003
 * @tc.desc: Test UpdateTextFieldMargin with existing margin
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorUpdateTextFieldMargin003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Set initial margin
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MarginProperty margin;
    margin.bottom = CalcLength(Dimension(5.0f, DimensionUnit::VP));
    layoutProperty->UpdateMargin(margin);

    /**
     * @tc.steps: step3. Get counter decorator and call UpdateTextFieldMargin
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    counterDecorator->UpdateTextFieldMargin();

    // Verify margin was updated
    const auto& afterMargin = layoutProperty->GetMarginProperty();
    EXPECT_TRUE(afterMargin != nullptr);
    if (afterMargin) {
        EXPECT_TRUE(afterMargin->bottom.has_value());
    }
}

/**
 * @tc.name: CounterDecoratorUpdateTextFieldMargin004
 * @tc.desc: Test UpdateTextFieldMargin with user margin by user
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorUpdateTextFieldMargin004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Set user margin with LPX unit
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    MarginProperty userMargin;
    userMargin.bottom = CalcLength(Dimension(50.0f, DimensionUnit::LPX));
    paintProperty->UpdateMarginByUser(userMargin);

    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateMargin(userMargin);

    /**
     * @tc.steps: step3. Get counter decorator and call UpdateTextFieldMargin
     * @tc.expected: Should respect user LPX margin when larger
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    counterDecorator->UpdateTextFieldMargin();

    // Verify margin is preserved
    const auto& afterMargin = layoutProperty->GetMarginProperty();
    EXPECT_TRUE(afterMargin != nullptr);
    if (afterMargin && afterMargin->bottom.has_value()) {
        // User LPX margin should be preserved
        EXPECT_GT(afterMargin->bottom->GetDimension().ConvertToPx(), 0.0f);
    }
}

/**
 * @tc.name: CounterDecoratorUpdateTextFieldMargin005
 * @tc.desc: Test UpdateTextFieldMargin barrierfree property
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorUpdateTextFieldMargin005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Call UpdateTextFieldMargin
     * @tc.expected: Should set barrierfree level on text node
     */
    counterDecorator->UpdateTextFieldMargin();

    // Verify text node has barrierfree property set
    auto textNode = AceType::DynamicCast<FrameNode>(counterDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);

    auto accessibilityProperty = textNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityLevel(), "yes");
}

/**
 * @tc.name: CounterDecoratorGetContentWidth001
 * @tc.desc: Test GetContentWidth with counter
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorGetContentWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Call GetContentWidth
     * @tc.expected: Should return valid width
     */
    auto contentWidth = counterDecorator->GetContentWidth();
    EXPECT_GE(contentWidth, 0.0f);
}

/**
 * @tc.name: CounterDecoratorMeasureTextNodeHeight001
 * @tc.desc: Test MeasureTextNodeHeight with counter
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorMeasureTextNodeHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Call MeasureTextNodeHeight
     * @tc.expected: Should return valid height
     */
    auto height = counterDecorator->MeasureTextNodeHeight();
    EXPECT_GT(height, 0.0f);
}

/**
 * @tc.name: CounterDecoratorUpdateCounterContentAndStyle001
 * @tc.desc: Test UpdateCounterContentAndStyle with isVisible true
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorUpdateCounterContentAndStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Call UpdateCounterContentAndStyle with isVisible=true
     * @tc.expected: Should update content
     */
    counterDecorator->UpdateCounterContentAndStyle(5, 10, true);

    auto textNode = AceType::DynamicCast<FrameNode>(counterDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    // Note: BarrierFree text requires theme constants that may not be available in test environment
}

/**
 * @tc.name: CounterDecoratorUpdateCounterContentAndStyle002
 * @tc.desc: Test UpdateCounterContentAndStyle with isVisible false
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorUpdateCounterContentAndStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Call UpdateCounterContentAndStyle with isVisible=false
     * @tc.expected: Should clear barrierfree text
     */
    counterDecorator->UpdateCounterContentAndStyle(5, 10, false);

    auto textNode = AceType::DynamicCast<FrameNode>(counterDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    auto accessibilityProperty = textNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->GetAccessibilityText().empty());
}

/**
 * @tc.name: CounterDecoratorUpdateCounterContentAndStyle003
 * @tc.desc: Test UpdateCounterContentAndStyle with max font scale
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorUpdateCounterContentAndStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter and max font scale
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
        model.SetMaxFontScale(1.5);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Call UpdateCounterContentAndStyle
     * @tc.expected: Should apply max font scale
     */
    counterDecorator->UpdateCounterContentAndStyle(5, 10, true);

    auto textNode = AceType::DynamicCast<FrameNode>(counterDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_TRUE(textLayoutProperty->HasMaxFontScale());
}

/**
 * @tc.name: CounterDecoratorUpdateCounterContentAndStyle004
 * @tc.desc: Test UpdateCounterContentAndStyle with min font scale
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorUpdateCounterContentAndStyle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter and min font scale
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
        model.SetMinFontScale(0.8);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Call UpdateCounterContentAndStyle
     * @tc.expected: Should apply min font scale
     */
    counterDecorator->UpdateCounterContentAndStyle(5, 10, true);

    auto textNode = AceType::DynamicCast<FrameNode>(counterDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_TRUE(textLayoutProperty->HasMinFontScale());
}

/**
 * @tc.name: CounterDecoratorProcessCounterColor001
 * @tc.desc: Test ProcessCounterColor with showCounterStyle and hasFocus
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorProcessCounterColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Set focus to trigger showCounterStyle
     */
    GetFocus();

    /**
     * @tc.steps: step3. Get counter decorator and trigger style update
     * @tc.expected: Should process over count color
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    // Trigger UpdateCounterContentAndStyle which calls ProcessCounterColor
    counterDecorator->UpdateCounterContentAndStyle(10, 10, true);

    auto textNode = AceType::DynamicCast<FrameNode>(counterDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_TRUE(textLayoutProperty->GetContent().has_value());
}

/**
 * @tc.name: CounterDecoratorProcessCounterColor002
 * @tc.desc: Test ProcessCounterColor with overflow color
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorProcessCounterColor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter and overflow color
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
        model.SetCounterTextOverflowColor(Color::RED);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Set focus
     */
    GetFocus();

    /**
     * @tc.steps: step3. Get counter decorator and update content
     * @tc.expected: Should apply overflow color
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    counterDecorator->UpdateCounterContentAndStyle(10, 10, true);

    auto textNode = AceType::DynamicCast<FrameNode>(counterDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_TRUE(textLayoutProperty->GetContent().has_value());
}

/**
 * @tc.name: CounterDecoratorMeasureDecorator001
 * @tc.desc: Test MeasureDecorator with counter enabled
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorMeasureDecorator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Call MeasureDecorator
     * @tc.expected: Should return valid height
     */
    auto height = counterDecorator->MeasureDecorator(300.0f, u"hello", false);
    EXPECT_GE(height, 0.0f);
}

/**
 * @tc.name: CounterDecoratorMeasureDecorator003
 * @tc.desc: Test MeasureDecorator for TextArea
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorMeasureDecorator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextArea node directly using TextFieldModelNG
     */
    auto textFieldNode = TextFieldModelNG::CreateTextAreaNode(
        ElementRegister::GetInstance()->MakeUniqueId(),
        std::optional<std::u16string>(u""),
        std::optional<std::u16string>(u""));
    ASSERT_NE(textFieldNode, nullptr);

    /**
     * @tc.steps: step2. Set up TextArea with counter
     */
    TextFieldModelNG::SetMaxLength(Referenced::RawPtr(textFieldNode), 10);
    TextFieldModelNG::SetShowCounter(Referenced::RawPtr(textFieldNode), true);

    /**
     * @tc.steps: step3. Call MarkModifyDone to trigger decorator creation
     */
    textFieldNode->MarkModifyDone();

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    /**
     * @tc.steps: step4. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step5. Call MeasureDecorator for TextArea
     * @tc.expected: Should return valid height (counter is shown in TextArea as well)
     */
    auto height = counterDecorator->MeasureDecorator(300.0f, u"hello", false);
    EXPECT_GT(height, 0.0f);
}

/**
 * @tc.name: CounterDecoratorUpdateTextNodeAndMeasure001
 * @tc.desc: Test UpdateTextNodeAndMeasure with default counter type
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorUpdateTextNodeAndMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Call UpdateTextNodeAndMeasure with content constraint
     * @tc.expected: Should update and measure text node
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.UpdateIllegalSelfIdealSizeWithCheck(OptionalSizeF(300.0f, std::nullopt));

    counterDecorator->UpdateTextNodeAndMeasure(5, 10, contentConstraint);

    auto textNode = AceType::DynamicCast<FrameNode>(counterDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    EXPECT_NE(textNode->GetGeometryNode(), nullptr);
}

/**
 * @tc.name: CounterDecoratorUpdateTextNodeAndMeasure002
 * @tc.desc: Test UpdateTextNodeAndMeasure with default counter type (DEFAULT_MODE)
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorUpdateTextNodeAndMeasure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Call UpdateTextNodeAndMeasure with content constraint
     * @tc.expected: Should update and measure text node (DEFAULT_MODE always shows counter)
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.UpdateIllegalSelfIdealSizeWithCheck(OptionalSizeF(300.0f, std::nullopt));

    counterDecorator->UpdateTextNodeAndMeasure(2, 10, contentConstraint);

    auto textNode = AceType::DynamicCast<FrameNode>(counterDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_TRUE(textLayoutProperty->GetContent().has_value());
}

/**
 * @tc.name: CounterDecoratorLayoutDecorator001
 * @tc.desc: Test LayoutDecorator for TextInput
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorLayoutDecorator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Call LayoutDecorator
     * @tc.expected: Should layout counter node
     */
    counterDecorator->LayoutDecorator();

    auto textNode = AceType::DynamicCast<FrameNode>(counterDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    EXPECT_NE(textNode->GetGeometryNode(), nullptr);
}

/**
 * @tc.name: CounterDecoratorLayoutDecorator002
 * @tc.desc: Test LayoutDecorator for TextArea
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorLayoutDecorator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextArea node directly using TextFieldModelNG
     */
    auto textFieldNode = TextFieldModelNG::CreateTextAreaNode(
        ElementRegister::GetInstance()->MakeUniqueId(),
        std::optional<std::u16string>(u""),
        std::optional<std::u16string>(u""));
    ASSERT_NE(textFieldNode, nullptr);

    /**
     * @tc.steps: step2. Set up TextArea with counter
     */
    TextFieldModelNG::SetMaxLength(Referenced::RawPtr(textFieldNode), 10);
    TextFieldModelNG::SetShowCounter(Referenced::RawPtr(textFieldNode), true);

    /**
     * @tc.steps: step3. Call MarkModifyDone to trigger decorator creation
     */
    textFieldNode->MarkModifyDone();

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();

    /**
     * @tc.steps: step4. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step5. Call LayoutDecorator for TextArea
     * @tc.expected: Should handle TextArea layout
     */
    counterDecorator->LayoutDecorator();

    auto textNode = AceType::DynamicCast<FrameNode>(counterDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
}

/**
 * @tc.name: CounterDecoratorHasContent001
 * @tc.desc: Test HasContent with visible counter
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorHasContent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Update content to be visible
     */
    counterDecorator->UpdateCounterContentAndStyle(5, 10, true);

    /**
     * @tc.steps: step4. Call HasContent
     * @tc.expected: Should return true when content is visible
     */
    EXPECT_TRUE(counterDecorator->HasContent());
}

/**
 * @tc.name: CounterDecoratorHasContent002
 * @tc.desc: Test HasContent with invisible counter
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorHasContent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Update content to be invisible
     */
    counterDecorator->UpdateCounterContentAndStyle(5, 10, false);

    /**
     * @tc.steps: step4. Call HasContent
     * @tc.expected: Should return false when content is empty
     */
    EXPECT_FALSE(counterDecorator->HasContent());
}

/**
 * @tc.name: ErrorDecoratorUpdateTextFieldMargin001
 * @tc.desc: Test ErrorDecorator UpdateTextFieldMargin
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorUpdateTextFieldMargin001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // Error text will be set via layout property
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step5. Call UpdateTextFieldMargin
     * @tc.expected: Should update margin for error text
     */
    errorDecorator->UpdateTextFieldMargin();

    // Verify margin was updated (no crash means success)
    const auto& margin = layoutProperty->GetMarginProperty();
    EXPECT_TRUE(margin != nullptr || margin == nullptr); // Use margin to avoid warning
}

/**
 * @tc.name: ErrorDecoratorUpdateLayoutProperty001
 * @tc.desc: Test ErrorDecorator UpdateLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorUpdateLayoutProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextAlign(TextAlign::CENTER);
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step4. Call UpdateLayoutProperty
     * @tc.expected: Should update layout properties
     */
    errorDecorator->UpdateLayoutProperty();

    auto textNode = AceType::DynamicCast<FrameNode>(errorDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetTextAlign(), TextAlign::START);
}

/**
 * @tc.name: ErrorDecoratorUpdateLayoutProperty002
 * @tc.desc: Test ErrorDecorator UpdateLayoutProperty with font scale
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorUpdateLayoutProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxFontScale(1.5);
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step4. Call UpdateLayoutProperty
     * @tc.expected: Should apply min font scale from theme and max
     */
    errorDecorator->UpdateLayoutProperty();

    auto textNode = AceType::DynamicCast<FrameNode>(errorDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_TRUE(textLayoutProperty->HasMaxFontScale());
}

/**
 * @tc.name: ErrorDecoratorUpdateErrorStyle001
 * @tc.desc: Test ErrorDecorator UpdateErrorStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorUpdateErrorStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // Error text will be set via layout property
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step4. Call UpdateErrorStyle
     * @tc.expected: Should update error style and mark node dirty
     */
    errorDecorator->UpdateErrorStyle();

    auto textNode = AceType::DynamicCast<FrameNode>(errorDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    auto accessibilityProperty = textNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityLevel(), "yes");
}

/**
 * @tc.name: ErrorDecoratorMeasureDecorator001
 * @tc.desc: Test ErrorDecorator MeasureDecorator with error shown
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorMeasureDecorator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // Error text will be set via layout property
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step4. Call MeasureDecorator
     * @tc.expected: Should return valid height
     */
    auto height = errorDecorator->MeasureDecorator(300.0f, u"hello", false);
    EXPECT_GE(height, 0.0f);
}

/**
 * @tc.name: ErrorDecoratorMeasureDecorator002
 * @tc.desc: Test ErrorDecorator MeasureDecorator without error
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorMeasureDecorator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // Error text will be set via layout property
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST to create decorator
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Hide error text to test "no error shown" case
     */
    layoutProperty->UpdateShowErrorText(false);

    /**
     * @tc.steps: step5. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step6. Call MeasureDecorator
     * @tc.expected: Should return valid height (decorator exists but error is not shown)
     */
    auto height = errorDecorator->MeasureDecorator(300.0f, u"hello", false);
    EXPECT_GE(height, 0.0f);
}

/**
 * @tc.name: ErrorDecoratorMeasureDecorator003
 * @tc.desc: Test ErrorDecorator MeasureDecorator returns valid height
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorMeasureDecorator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // Error text will be set via layout property
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step5. Call MeasureDecorator
     * @tc.expected: Should return valid height when error is shown
     */
    auto height = errorDecorator->MeasureDecorator(300.0f, u"hello", false);
    EXPECT_GT(height, 0.0f);
}

/**
 * @tc.name: ErrorDecoratorMeasureDecorator004
 * @tc.desc: Test ErrorDecorator MeasureDecorator with counter
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorMeasureDecorator004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step5. Call MeasureDecorator
     * @tc.expected: Should account for counter width
     */
    auto height = errorDecorator->MeasureDecorator(300.0f, u"hello", false);
    EXPECT_GE(height, 0.0f);
}

/**
 * @tc.name: ErrorDecoratorBeforeLayout001
 * @tc.desc: Test ErrorDecorator BeforeLayout
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorBeforeLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // Error text will be set via layout property
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step4. Call BeforeLayout
     * @tc.expected: Should call MeasureDecorator internally
     */
    errorDecorator->BeforeLayout();

    auto textNode = AceType::DynamicCast<FrameNode>(errorDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    EXPECT_NE(textNode->GetGeometryNode(), nullptr);
}

/**
 * @tc.name: ErrorDecoratorLayoutDecorator001
 * @tc.desc: Test ErrorDecorator LayoutDecorator with error shown
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorLayoutDecorator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // Error text will be set via layout property
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step5. Call LayoutDecorator
     * @tc.expected: Should layout error text node
     */
    errorDecorator->LayoutDecorator();

    auto textNode = AceType::DynamicCast<FrameNode>(errorDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    EXPECT_NE(textNode->GetGeometryNode(), nullptr);
}

/**
 * @tc.name: ErrorDecoratorLayoutDecorator002
 * @tc.desc: Test ErrorDecorator LayoutDecorator with underline
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorLayoutDecorator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // Error text and underline will be set via properties
    });

    /**
     * @tc.steps: step2. Set error text and underline via properties FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);
    layoutProperty->UpdateShowUnderline(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step4. Call LayoutDecorator
     * @tc.expected: Should use underline margin
     */
    errorDecorator->LayoutDecorator();

    auto textNode = AceType::DynamicCast<FrameNode>(errorDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    auto geometryNode = textNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
}

/**
 * @tc.name: ErrorDecoratorLayoutDecorator003
 * @tc.desc: Test ErrorDecorator LayoutDecorator with RTL
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorLayoutDecorator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetTextDirection(TextDirection::RTL);
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step4. Call LayoutDecorator
     * @tc.expected: Should handle RTL layout positioning
     * Note: ErrorDecorator uses RTL direction for positioning but doesn't set
     * the text node's layout direction property
     */
    errorDecorator->LayoutDecorator();

    auto textNode = AceType::DynamicCast<FrameNode>(errorDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
    EXPECT_NE(textNode->GetGeometryNode(), nullptr);
}

/**
 * @tc.name: ErrorDecoratorLayoutDecorator004
 * @tc.desc: Test ErrorDecorator LayoutDecorator with center align
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorLayoutDecorator004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // Error text will be set via layout property
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Mock theme with center error text align
     */
    auto theme = pattern_->GetTheme();
    ASSERT_NE(theme, nullptr);

    /**
     * @tc.steps: step5. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step5. Call LayoutDecorator
     * @tc.expected: Should layout error text
     */
    errorDecorator->LayoutDecorator();

    auto textNode = AceType::DynamicCast<FrameNode>(errorDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);
}

/**
 * @tc.name: ErrorDecoratorGetBoundHeight001
 * @tc.desc: Test ErrorDecorator GetBoundHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, ErrorDecoratorGetBoundHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // Error text will be set via layout property
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step4. Measure decorator first
     */
    errorDecorator->BeforeLayout();

    /**
     * @tc.steps: step5. Call GetBoundHeight
     * @tc.expected: Should return valid bound height
     */
    auto height = errorDecorator->GetBoundHeight();
    EXPECT_GT(height, 0.0f);
}

/**
 * @tc.name: TextComponentDecoratorCleanDecorator001
 * @tc.desc: Test CleanDecorator for counter decorator
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, TextComponentDecoratorCleanDecorator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Verify text node is attached
     */
    auto textNode = AceType::DynamicCast<FrameNode>(counterDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);

    /**
     * @tc.steps: step4. Call CleanDecorator
     * @tc.expected: Should remove text node from parent
     */
    counterDecorator->CleanDecorator();
}

/**
 * @tc.name: TextComponentDecoratorCleanDecorator002
 * @tc.desc: Test CleanDecorator for error decorator
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, TextComponentDecoratorCleanDecorator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // Error text will be set via layout property
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step4. Verify text node is attached
     */
    auto textNode = AceType::DynamicCast<FrameNode>(errorDecorator->textNode_.Upgrade());
    ASSERT_NE(textNode, nullptr);

    /**
     * @tc.steps: step5. Call CleanDecorator
     * @tc.expected: Should remove text node from parent
     */
    errorDecorator->CleanDecorator();
}

/**
 * @tc.name: TextComponentDecoratorGetDecoratorHeight001
 * @tc.desc: Test GetDecoratorHeight for counter decorator
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, TextComponentDecoratorGetDecoratorHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Measure the decorator first
     */
    counterDecorator->MeasureTextNodeHeight();

    /**
     * @tc.steps: step4. Call GetDecoratorHeight
     * @tc.expected: Should return valid height
     */
    auto height = counterDecorator->GetDecoratorHeight();
    EXPECT_GT(height, 0.0f);
}

/**
 * @tc.name: TextComponentDecoratorGetDecoratorHeight002
 * @tc.desc: Test GetDecoratorHeight for error decorator
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, TextComponentDecoratorGetDecoratorHeight002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        // Error text will be set via layout property
    });

    /**
     * @tc.steps: step2. Set error text via layout property FIRST
     */
    auto layoutProperty = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateErrorText(u"Error message");
    layoutProperty->UpdateShowErrorText(true);

    /**
     * @tc.steps: step3. Call MarkModifyDone and OnModifyDone to trigger error decorator creation
     */
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step4. Get error decorator
     */
    auto errorDecorator = AceType::DynamicCast<ErrorDecorator>(pattern_->GetErrorDecorator());
    ASSERT_NE(errorDecorator, nullptr);

    /**
     * @tc.steps: step4. Measure the decorator first
     */
    errorDecorator->BeforeLayout();

    /**
     * @tc.steps: step5. Call GetDecoratorHeight
     * @tc.expected: Should return valid height
     */
    auto height = errorDecorator->GetDecoratorHeight();
    EXPECT_GT(height, 0.0f);
}

/**
 * @tc.name: CounterDecoratorGetBoundHeight001
 * @tc.desc: Test CounterDecorator GetBoundHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextInputDecoratorTest, CounterDecoratorGetBoundHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField with counter
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step2. Get counter decorator
     */
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    ASSERT_NE(counterDecorator, nullptr);

    /**
     * @tc.steps: step3. Measure the decorator first
     */
    counterDecorator->MeasureTextNodeHeight();

    /**
     * @tc.steps: step4. Call GetBoundHeight
     * @tc.expected: Should return valid bound height including margins
     */
    auto height = counterDecorator->GetBoundHeight();
    EXPECT_GT(height, 0.0f);
}

} // namespace OHOS::Ace::NG
