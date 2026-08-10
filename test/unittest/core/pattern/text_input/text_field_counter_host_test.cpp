/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/common_text/counter_host.h"
#include "core/components_ng/pattern/common_text/counter_decorator.h"
#include "core/components_ng/pattern/text_field/text_field_foreground_modifier.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {

class TextFieldCounterHostTest : public TextInputBases {};

/**
 * @tc.name: TextFieldCounterHostCast001
 * @tc.desc: Test that TextFieldPattern can be cast to ICounterHost interface
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, TextFieldCounterHostCast001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    EXPECT_NE(counterHost, nullptr);
}

/**
 * @tc.name: TextFieldCounterHostCast002
 * @tc.desc: Test that TextFieldPattern can be claimed as ICounterHost via WeakClaim
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, TextFieldCounterHostCast002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto weakHost = AceType::WeakClaim(static_cast<ICounterHost*>(AceType::RawPtr(pattern_)));
    auto upgraded = weakHost.Upgrade();
    EXPECT_NE(upgraded, nullptr);
}

/**
 * @tc.name: GetRealMaxLength001
 * @tc.desc: Test GetRealMaxLength delegates to GetMaxLength, returns default 1000000 when not explicitly set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetRealMaxLength001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    auto result = counterHost->GetRealMaxLength();
    EXPECT_EQ(result, 1000000u);
}

/**
 * @tc.name: GetRealMaxLength002
 * @tc.desc: Test GetRealMaxLength returns the value set via MaxLength
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetRealMaxLength002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(10);
    });
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    auto result = counterHost->GetRealMaxLength();
    EXPECT_EQ(result, 10u);
}

/**
 * @tc.name: HasMaxLength001
 * @tc.desc: Test HasMaxLength returns false by default (CreateTextInput sets default MaxLength)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasMaxLength001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->HasMaxLength());
}

/**
 * @tc.name: HasMaxLength002
 * @tc.desc: Test HasMaxLength returns true when MaxLength is set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasMaxLength002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetMaxLength(10);
    });
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->HasMaxLength());
}

/**
 * @tc.name: GetTextLength001
 * @tc.desc: Test GetTextLength returns the length of text content
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetTextLength001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_EQ(counterHost->GetTextLength(), static_cast<uint32_t>(HELLO_TEXT.length()));
}

/**
 * @tc.name: GetTextLength002
 * @tc.desc: Test GetTextLength returns 0 when text is empty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetTextLength002, TestSize.Level1)
{
    CreateTextField("");
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_EQ(counterHost->GetTextLength(), 0u);
}

/**
 * @tc.name: GetTextValue001
 * @tc.desc: Test GetTextValue returns the text content from content controller
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetTextValue001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_EQ(counterHost->GetTextValue(), HELLO_TEXT);
}

/**
 * @tc.name: GetShowCounterValue001
 * @tc.desc: Test GetShowCounterValue returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetShowCounterValue001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->GetShowCounterValue());
}

/**
 * @tc.name: GetShowCounterValue002
 * @tc.desc: Test GetShowCounterValue returns true when ShowCounter is set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetShowCounterValue002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
    });
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->GetShowCounterValue());
}

/**
 * @tc.name: GetCounterType001
 * @tc.desc: Test GetCounterType returns -1 by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetCounterType001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_EQ(counterHost->GetCounterType(), -1);
}

/**
 * @tc.name: GetCounterType002
 * @tc.desc: Test GetCounterType returns the value set via SetCounter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetCounterType002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    layoutProperty_->UpdateSetCounter(1);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_EQ(counterHost->GetCounterType(), 1);
}

/**
 * @tc.name: GetShowHighlightBorder001
 * @tc.desc: Test GetShowHighlightBorder returns true by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetShowHighlightBorder001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->GetShowHighlightBorder());
}

/**
 * @tc.name: GetShowHighlightBorder002
 * @tc.desc: Test GetShowHighlightBorder returns false when set to false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetShowHighlightBorder002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    layoutProperty_->UpdateShowHighlightBorder(false);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->GetShowHighlightBorder());
}

/**
 * @tc.name: HasCounterTextColor001
 * @tc.desc: Test HasCounterTextColor returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasCounterTextColor001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->HasCounterTextColor());
}

/**
 * @tc.name: HasCounterTextColor002
 * @tc.desc: Test HasCounterTextColor returns true when counter text color is set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasCounterTextColor002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetCounterTextColor(Color::BLUE);
    });
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->HasCounterTextColor());
}

/**
 * @tc.name: GetCounterTextColor001
 * @tc.desc: Test GetCounterTextColor returns BLACK by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetCounterTextColor001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_EQ(counterHost->GetCounterTextColor(), Color::BLACK);
}

/**
 * @tc.name: GetCounterTextColor002
 * @tc.desc: Test GetCounterTextColor returns the color set via model
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetCounterTextColor002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetCounterTextColor(Color::BLUE);
    });
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_EQ(counterHost->GetCounterTextColor(), Color::BLUE);
}

/**
 * @tc.name: HasCounterTextOverflowColor001
 * @tc.desc: Test HasCounterTextOverflowColor returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasCounterTextOverflowColor001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->HasCounterTextOverflowColor());
}

/**
 * @tc.name: HasCounterTextOverflowColor002
 * @tc.desc: Test HasCounterTextOverflowColor returns true when set via model
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasCounterTextOverflowColor002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetCounterTextOverflowColor(Color::GREEN);
    });
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->HasCounterTextOverflowColor());
}

/**
 * @tc.name: GetCounterTextOverflowColor001
 * @tc.desc: Test GetCounterTextOverflowColor returns RED by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetCounterTextOverflowColor001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_EQ(counterHost->GetCounterTextOverflowColor(), Color::RED);
}

/**
 * @tc.name: GetCounterTextOverflowColor002
 * @tc.desc: Test GetCounterTextOverflowColor returns the color set via model
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetCounterTextOverflowColor002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetCounterTextOverflowColor(Color::GREEN);
    });
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_EQ(counterHost->GetCounterTextOverflowColor(), Color::GREEN);
}

/**
 * @tc.name: GetNonAutoLayoutDirection001
 * @tc.desc: Test GetNonAutoLayoutDirection returns LTR by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetNonAutoLayoutDirection001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_EQ(counterHost->GetNonAutoLayoutDirection(), TextDirection::LTR);
}

/**
 * @tc.name: GetNonAutoLayoutDirection002
 * @tc.desc: Test GetNonAutoLayoutDirection returns RTL when layout direction is set to RTL
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetNonAutoLayoutDirection002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_EQ(counterHost->GetNonAutoLayoutDirection(), TextDirection::RTL);
}

/**
 * @tc.name: GetFontScaleFromEnv001
 * @tc.desc: Test GetFontScaleFromEnv returns a valid value from pipeline
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetFontScaleFromEnv001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    auto fontScale = counterHost->GetFontScaleFromEnv();
    EXPECT_GT(fontScale, 0.0f);
}

/**
 * @tc.name: GetMarginProperty001
 * @tc.desc: Test GetMarginProperty when margin is not set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetMarginProperty001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    auto margin = counterHost->GetMarginProperty();
    EXPECT_TRUE(margin.has_value());
}

/**
 * @tc.name: GetMarginProperty002
 * @tc.desc: Test GetMarginProperty returns the margin set on layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetMarginProperty002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    MarginProperty margin;
    margin.left = CalcLength(10.0, DimensionUnit::VP);
    margin.right = CalcLength(20.0, DimensionUnit::VP);
    layoutProperty_->UpdateMargin(margin);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    auto result = counterHost->GetMarginProperty();
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->left.has_value());
    EXPECT_TRUE(result->right.has_value());
}

/**
 * @tc.name: UpdateMargin001
 * @tc.desc: Test UpdateMargin updates the margin on layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, UpdateMargin001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    MarginProperty margin;
    margin.bottom = CalcLength(15.0, DimensionUnit::VP);
    counterHost->UpdateMargin(margin);
    auto result = counterHost->GetMarginProperty();
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->bottom.has_value());
}

/**
 * @tc.name: HasMarginByUser001
 * @tc.desc: Test HasMarginByUser returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasMarginByUser001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->HasMarginByUser());
}

/**
 * @tc.name: HasMarginByUser002
 * @tc.desc: Test HasMarginByUser returns true when MarginByUser is set on paint property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasMarginByUser002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMarginByUser(MarginProperty());
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->HasMarginByUser());
}

/**
 * @tc.name: GetMarginByUserValue001
 * @tc.desc: Test GetMarginByUserValue returns default when not set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetMarginByUserValue001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    auto result = counterHost->GetMarginByUserValue();
    EXPECT_FALSE(result.left.has_value());
}

/**
 * @tc.name: GetMarginByUserValue002
 * @tc.desc: Test GetMarginByUserValue returns the value set on paint property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetMarginByUserValue002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    MarginProperty margin;
    margin.top = CalcLength(5.0, DimensionUnit::VP);
    paintProperty->UpdateMarginByUser(margin);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    auto result = counterHost->GetMarginByUserValue();
    EXPECT_TRUE(result.top.has_value());
}

/**
 * @tc.name: UpdateInnerBorderWidth001
 * @tc.desc: Test UpdateInnerBorderWidth updates the inner border width on paint property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, UpdateInnerBorderWidth001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    counterHost->UpdateInnerBorderWidth(5.0f);
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto innerWidth = paintProperty->GetInnerBorderWidthValue(Dimension(0));
    EXPECT_FLOAT_EQ(innerWidth.Value(), 5.0f);
    EXPECT_EQ(innerWidth.Unit(), DimensionUnit::PX);
}

/**
 * @tc.name: UpdateInnerBorderColor001
 * @tc.desc: Test UpdateInnerBorderColor updates the inner border color on paint property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, UpdateInnerBorderColor001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    counterHost->UpdateInnerBorderColor(Color::RED);
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetInnerBorderColorValue(Color::BLACK), Color::RED);
}

/**
 * @tc.name: HasBorderWidthFlagByUser001
 * @tc.desc: Test HasBorderWidthFlagByUser returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasBorderWidthFlagByUser001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->HasBorderWidthFlagByUser());
}

/**
 * @tc.name: HasBorderWidthFlagByUser002
 * @tc.desc: Test HasBorderWidthFlagByUser returns true when set on paint property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasBorderWidthFlagByUser002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateBorderWidthFlagByUser(BorderWidthProperty());
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->HasBorderWidthFlagByUser());
}

/**
 * @tc.name: GetBorderWidthFlagByUserValue001
 * @tc.desc: Test GetBorderWidthFlagByUserValue returns default when not set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetBorderWidthFlagByUserValue001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    auto result = counterHost->GetBorderWidthFlagByUserValue();
    EXPECT_FALSE(result.leftDimen.has_value());
}

/**
 * @tc.name: HasBorderColorFlagByUser001
 * @tc.desc: Test HasBorderColorFlagByUser returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasBorderColorFlagByUser001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->HasBorderColorFlagByUser());
}

/**
 * @tc.name: HasBorderColorFlagByUser002
 * @tc.desc: Test HasBorderColorFlagByUser returns true when set on paint property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasBorderColorFlagByUser002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateBorderColorFlagByUser(BorderColorProperty());
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->HasBorderColorFlagByUser());
}

/**
 * @tc.name: GetBorderColorFlagByUserValue001
 * @tc.desc: Test GetBorderColorFlagByUserValue returns default when not set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetBorderColorFlagByUserValue001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    auto result = counterHost->GetBorderColorFlagByUserValue();
    EXPECT_FALSE(result.leftColor.has_value());
}

/**
 * @tc.name: HasBorderRadiusFlagByUser001
 * @tc.desc: Test HasBorderRadiusFlagByUser returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasBorderRadiusFlagByUser001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->HasBorderRadiusFlagByUser());
}

/**
 * @tc.name: HasBorderRadiusFlagByUser002
 * @tc.desc: Test HasBorderRadiusFlagByUser returns true when set on paint property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasBorderRadiusFlagByUser002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateBorderRadiusFlagByUser(BorderRadiusProperty());
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->HasBorderRadiusFlagByUser());
}

/**
 * @tc.name: GetBorderRadiusFlagByUserValue001
 * @tc.desc: Test GetBorderRadiusFlagByUserValue returns default when not set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetBorderRadiusFlagByUserValue001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    auto result = counterHost->GetBorderRadiusFlagByUserValue();
    EXPECT_FALSE(result.radiusTopLeft.has_value());
}

/**
 * @tc.name: UpdateBorderColor001
 * @tc.desc: Test UpdateBorderColor updates border color on render context
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, UpdateBorderColor001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    BorderColorProperty borderColor;
    borderColor.leftColor = Color::RED;
    borderColor.rightColor = Color::BLUE;
    counterHost->UpdateBorderColor(borderColor);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto result = renderContext->GetBorderColorValue(BorderColorProperty());
    EXPECT_EQ(result.leftColor.value_or(Color::BLACK), Color::RED);
    EXPECT_EQ(result.rightColor.value_or(Color::BLACK), Color::BLUE);
}

/**
 * @tc.name: IsShowCounterEnabled001
 * @tc.desc: Test IsShowCounterEnabled returns false by default (no ShowCounter)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, IsShowCounterEnabled001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->IsShowCounterEnabled());
}

/**
 * @tc.name: IsShowCounterEnabled002
 * @tc.desc: Test IsShowCounterEnabled returns true when ShowCounter and MaxLength are set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, IsShowCounterEnabled002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->IsShowCounterEnabled());
}

/**
 * @tc.name: IsTextAreaOnCounter001
 * @tc.desc: Test IsTextAreaOnCounter delegates to IsTextArea, returns false for TextInput
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, IsTextAreaOnCounter001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->IsTextAreaOnCounter());
}

/**
 * @tc.name: IsUnderlineAndButtonMode001
 * @tc.desc: Test IsUnderlineAndButtonMode returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, IsUnderlineAndButtonMode001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->IsUnderlineAndButtonMode());
}

/**
 * @tc.name: HasMaxFontScale001
 * @tc.desc: Test HasMaxFontScale returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasMaxFontScale001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->HasMaxFontScale());
}

/**
 * @tc.name: HasMaxFontScale002
 * @tc.desc: Test HasMaxFontScale returns true when MaxFontScale is set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasMaxFontScale002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    layoutProperty_->UpdateMaxFontScale(2.0f);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->HasMaxFontScale());
}

/**
 * @tc.name: GetMaxFontScale001
 * @tc.desc: Test GetMaxFontScale returns MAXFONTSCALE (3.20f) by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetMaxFontScale001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FLOAT_EQ(counterHost->GetMaxFontScale(), 3.20f);
}

/**
 * @tc.name: GetMaxFontScale002
 * @tc.desc: Test GetMaxFontScale returns the value set on layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetMaxFontScale002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    layoutProperty_->UpdateMaxFontScale(2.5f);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FLOAT_EQ(counterHost->GetMaxFontScale(), 2.5f);
}

/**
 * @tc.name: HasMinFontScale001
 * @tc.desc: Test HasMinFontScale returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasMinFontScale001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->HasMinFontScale());
}

/**
 * @tc.name: HasMinFontScale002
 * @tc.desc: Test HasMinFontScale returns true when MinFontScale is set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasMinFontScale002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    layoutProperty_->UpdateMinFontScale(0.5f);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->HasMinFontScale());
}

/**
 * @tc.name: GetMinFontScale001
 * @tc.desc: Test GetMinFontScale returns MINFONTSCALE (0.85f) by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetMinFontScale001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FLOAT_EQ(counterHost->GetMinFontScale(), 0.85f);
}

/**
 * @tc.name: GetMinFontScale002
 * @tc.desc: Test GetMinFontScale returns the value set on layout property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetMinFontScale002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    layoutProperty_->UpdateMinFontScale(0.5f);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FLOAT_EQ(counterHost->GetMinFontScale(), 0.5f);
}

/**
 * @tc.name: SetUnderlineWidth001
 * @tc.desc: Test SetUnderlineWidth(float) sets underline width in PX
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, SetUnderlineWidth001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    counterHost->SetUnderlineWidth(10.0f);
    EXPECT_FLOAT_EQ(pattern_->GetUnderlineWidth(), 10.0f);
}

/**
 * @tc.name: IsShowError001
 * @tc.desc: Test IsShowError returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, IsShowError001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->IsShowError());
}

/**
 * @tc.name: IsShowError002
 * @tc.desc: Test IsShowError returns true when ShowErrorText is set and error text is not empty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, IsShowError002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    layoutProperty_->UpdateShowErrorText(true);
    layoutProperty_->UpdateErrorText(u"error message");
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->IsShowError());
}

/**
 * @tc.name: IsShowCount001
 * @tc.desc: Test IsShowCount returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, IsShowCount001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    EXPECT_FALSE(pattern_->IsShowCount());
}

/**
 * @tc.name: IsShowCount002
 * @tc.desc: Test IsShowCount returns true when ShowCounter and MaxLength are set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, IsShowCount002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    EXPECT_TRUE(pattern_->IsShowCount());
}

/**
 * @tc.name: AddCounterNode001
 * @tc.desc: Test AddCounterNode creates CounterDecorator and sets CounterHost
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, AddCounterNode001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    pattern_->AddCounterNode();
    auto counterDecorator = AceType::DynamicCast<CounterDecorator>(pattern_->GetCounterDecorator());
    EXPECT_NE(counterDecorator, nullptr);
}

/**
 * @tc.name: AddCounterNode002
 * @tc.desc: Test AddCounterNode does not recreate decorator when already exists
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, AddCounterNode002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT, "", [](TextFieldModelNG model) {
        model.SetShowCounter(true);
        model.SetMaxLength(10);
    });
    pattern_->AddCounterNode();
    auto decorator1 = pattern_->GetCounterDecorator();
    pattern_->AddCounterNode();
    auto decorator2 = pattern_->GetCounterDecorator();
    EXPECT_EQ(decorator1, decorator2);
}

/**
 * @tc.name: GetShowCounterStyleValue001
 * @tc.desc: Test GetShowCounterStyleValue returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetShowCounterStyleValue001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->GetShowCounterStyleValue());
}

/**
 * @tc.name: SetShowCounterStyleValue001
 * @tc.desc: Test SetShowCounterStyleValue sets and GetShowCounterStyleValue returns the value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, SetShowCounterStyleValue001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    counterHost->SetShowCounterStyleValue(true);
    EXPECT_TRUE(counterHost->GetShowCounterStyleValue());
    counterHost->SetShowCounterStyleValue(false);
    EXPECT_FALSE(counterHost->GetShowCounterStyleValue());
}

/**
 * @tc.name: GetHost001
 * @tc.desc: Test GetHost returns the FrameNode via pattern interface
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetHost001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    EXPECT_EQ(host, frameNode_);
}

/**
 * @tc.name: GetRenderContext001
 * @tc.desc: Test GetRenderContext returns a valid RenderContext via pattern interface
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, GetRenderContext001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto* renderContext = host->GetRenderContext().GetRawPtr();
    EXPECT_NE(renderContext, nullptr);
}

/**
 * @tc.name: HasFocus001
 * @tc.desc: Test HasFocus returns false when not focused
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasFocus001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_FALSE(counterHost->HasFocus());
}

/**
 * @tc.name: HasFocus002
 * @tc.desc: Test HasFocus returns true when focused
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, HasFocus002, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    GetFocus();
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    EXPECT_TRUE(counterHost->HasFocus());
}

/**
 * @tc.name: SetThemeBorderAttr001
 * @tc.desc: Test SetThemeBorderAttr executes without crash
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldCounterHostTest, SetThemeBorderAttr001, TestSize.Level1)
{
    CreateTextField(HELLO_TEXT);
    auto* counterHost = static_cast<ICounterHost*>(AceType::RawPtr(pattern_));
    ASSERT_NE(counterHost, nullptr);
    counterHost->SetThemeBorderAttr();
    auto renderContext = frameNode_->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
}

} // namespace OHOS::Ace::NG
