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

#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "text_input_base.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float MIN_RECT_X = 0.0f;
constexpr float MIN_RECT_Y = 0.0f;
constexpr float DEFAULT_RECT_X = 5.0f;
constexpr float DEFAULT_RECT_Y = 5.0f;
constexpr float MIN_RECT_WIDTH = 0.0f;
constexpr float MIN_RECT_HEIGHT = 0.0f;
constexpr float DEFAULT_RECT_WIDTH = 10.0f;
constexpr float DEFAULT_RECT_HEIGHT = 10.0f;
constexpr uint32_t UPDATE_NORMAL = 0;
constexpr uint32_t UPDATE_MEASURE = 1;
constexpr uint32_t UPDATE_DIFF = 4;
constexpr uint32_t UPDATE_MEASURE_SELF = 8;
constexpr uint32_t UPDATE_MEASURE_SELF_AND_PARENT = 16;
} // namespace

class TextFieldContentModifierTest : public TextInputBases {
public:
};

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: Test textfield to create paint.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, CreateNodePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step3. call CreateNodePaintMethod
     * tc.expected: step3. Check if the value is created.
     */
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step4. get FrameRect by textFieldPattern.
     * tc.expected: step4. clipRect is default.
     */
    RSRect clipRect;
    std::vector<RSPoint> clipRadius;
    textFieldContentModifier->GetFrameRectClip(clipRect, clipRadius);
    auto rectX = clipRect.GetLeft();
    EXPECT_EQ(rectX, MIN_RECT_X);
    auto rectY = clipRect.GetTop();
    EXPECT_EQ(rectY, MIN_RECT_Y);

    /**
     * @tc.steps: step5. change FrameRect
     * tc.expected: step5. check OnDirtyLayoutWrapperSwap() result.
     */
    auto host = pattern_->GetHost();
    EXPECT_NE(host, nullptr);
    auto geometryNode = host->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    RectF textRect(DEFAULT_RECT_X, DEFAULT_RECT_Y, DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT);
    SizeF size(DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT);
    OffsetF translate(DEFAULT_RECT_X, DEFAULT_RECT_Y);
    geometryNode->SetContentSize(size);
    geometryNode->SetContentOffset(translate);

    /**
     * @tc.steps: step4. get FrameRect by textFieldPattern.
     * tc.expected: step4. clipRect changed.
     */
    textFieldContentModifier->GetFrameRectClip(clipRect, clipRadius);
    rectX = clipRect.GetLeft();
    EXPECT_EQ(rectX, MIN_RECT_X);
    rectY = clipRect.GetTop();
    EXPECT_EQ(rectY, MIN_RECT_Y);
    auto rectWidth = clipRect.GetWidth();
    EXPECT_NE(rectWidth, MIN_RECT_WIDTH);
    auto rectHeight = clipRect.GetHeight();
    EXPECT_NE(rectHeight, MIN_RECT_HEIGHT);
}

/**
 * @tc.name: CreateNodePaintMethod002
 * @tc.desc: Test textfield to create paint.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, CreateNodePaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    pattern_->scrollBar_->SetScrollable(true);
    pattern_->scrollBar_->SetDisplayMode(DisplayMode::ON);
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step3. get default value
     * tc.expected: step3. Check if the value is created.
     */
    auto contentOffsetY = textFieldContentModifier->GetContentOffsetY();
    EXPECT_EQ(contentOffsetY, MIN_RECT_Y);
    auto textRectX = textFieldContentModifier->GetTextRectX();
    EXPECT_EQ(textRectX, MIN_RECT_X);
    auto textRectY = textFieldContentModifier->GetTextRectY();
    EXPECT_EQ(textRectY, MIN_RECT_Y);

    /**
     * @tc.steps: step4. change textRect
     */
    RectF textRect(DEFAULT_RECT_X, DEFAULT_RECT_Y, DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT);
    pattern_->SetTextRect(textRect);

    /**
     * @tc.steps: step4. do SetDefaultPropertyValue()
     * tc.expected: step4. Check if the value is changed.
     */
    textFieldContentModifier->SetDefaultPropertyValue();
    contentOffsetY = textFieldContentModifier->GetContentOffsetY();
    EXPECT_NE(contentOffsetY, MIN_RECT_Y);
    textRectX = textFieldContentModifier->GetTextRectX();
    EXPECT_NE(textRectX, MIN_RECT_X);
    textRectY = textFieldContentModifier->GetTextRectY();
    EXPECT_NE(textRectY, MIN_RECT_Y);
}

/**
 * @tc.name: NeedMeasureUpdate001
 * @tc.desc: Test change propertyChangeFlag.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, NeedMeasureUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input.
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    pattern_->scrollBar_->SetScrollable(true);
    pattern_->scrollBar_->SetDisplayMode(DisplayMode::ON);
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step3. set propertyChangeFlag = PROPERTY_UPDATE_MEASURE
     * tc.expected: step3. Check real flag.
     */
    PropertyChangeFlag flag = UPDATE_MEASURE;
    EXPECT_FALSE(textFieldContentModifier->NeedMeasureUpdate(flag));
    EXPECT_NE(flag, UPDATE_MEASURE);

    /**
     * @tc.steps: step4. set propertyChangeFlag = PROPERTY_UPDATE_MEASURE_SELF
     * tc.expected: step4. Check real flag.
     */
    flag = UPDATE_MEASURE_SELF;
    EXPECT_FALSE(textFieldContentModifier->NeedMeasureUpdate(flag));
    EXPECT_NE(flag, UPDATE_MEASURE_SELF);

    /**
     * @tc.steps: step5. set propertyChangeFlag = PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT
     * tc.expected: step5. Check real flag.
     */
    flag = UPDATE_MEASURE_SELF_AND_PARENT;
    EXPECT_FALSE(textFieldContentModifier->NeedMeasureUpdate(flag));
    EXPECT_NE(flag, UPDATE_MEASURE_SELF_AND_PARENT);

    /**
     * @tc.steps: step6. set propertyChangeFlag = PROPERTY_UPDATE_DIFF
     * tc.expected: step6. Check real flag.
     */
    flag = UPDATE_DIFF;
    EXPECT_FALSE(textFieldContentModifier->NeedMeasureUpdate(flag));
    EXPECT_EQ(flag, UPDATE_NORMAL);
}

/**
 * @tc.name: TextFieldContentModifierTest001
 * @tc.desc: Test textfield to draw caret.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, TextFieldContentModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. create scrollEdgeEffect
     * tc.expected: step2. Check if scrollEdgeEffect is created.
     */
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    EXPECT_NE(scrollEdgeEffect, nullptr);

    /**
     * @tc.steps: step3. call CreateNodePaintMethod
     * tc.expected: step3. Check if the value is created.
     */
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step4. set cursorOffset
     */
    OffsetF caretOffset(DEFAULT_RECT_X, DEFAULT_RECT_Y);
    pattern_->SetMovingCaretOffset(caretOffset);

    /**
     * @tc.steps: step5. Create DrawingContext
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };

    /**
     * @tc.steps: step6. Do onDraw()
     */
    textFieldContentModifier->onDraw(context);

    /**
     * @tc.steps: step7. get ContentRect
     * tc.expected: step7. Check ContentRect.
     */
    auto contentRectWidth = pattern_->GetContentRect().Width();
    auto contentRectHeight = pattern_->GetContentRect().Height();
    EXPECT_NE(contentRectWidth, MIN_RECT_WIDTH);
    EXPECT_NE(contentRectHeight, MIN_RECT_HEIGHT);
}

/**
 * @tc.name: TextFieldContentModifierUTSuit001
 * @tc.desc: Test SetFontStyle to update fontStyle_.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, TextFieldContentModifierUTSuit001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step3. call SetFontStyle
     * tc.expected: step3. Check if the ITALIC value is setted.
     */
    textFieldContentModifier->SetFontStyle(Ace::FontStyle::ITALIC);
    EXPECT_EQ(textFieldContentModifier->fontStyle_->Get(), 1);

    /**
     * @tc.steps: step4. call SetFontStyle
     * tc.expected: step4. Check if the NONE value is setted.
     */
    textFieldContentModifier->SetFontStyle(Ace::FontStyle::NONE);
    EXPECT_EQ(textFieldContentModifier->fontStyle_->Get(), 2);

    /**
     * @tc.steps: step5. call SetFontStyle
     * tc.expected: step5. Check if the NORMAL value is setted.
     */
    textFieldContentModifier->SetFontStyle(Ace::FontStyle::NORMAL);
    EXPECT_EQ(textFieldContentModifier->fontStyle_->Get(), 0);
}

/**
 * @tc.name: TextFieldContentModifierUTSuit002
 * @tc.desc: Test SetShowUnderlineState to update showUnderline_.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, TextFieldContentModifierUTSuit002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step3. call SetShowUnderlineState
     * tc.expected: step3. Check if the showUnderline_ is correct
     */
    auto propertyBool = AceType::MakeRefPtr<PropertyBool>(false);
    textFieldContentModifier->SetShowUnderlineState(propertyBool);
    EXPECT_EQ(textFieldContentModifier->showUnderline_, nullptr);

    /**
     * @tc.steps: step4. call SetShowUnderlineState
     * tc.expected: step4. Check if the showUnderline_ is correct
     */
    propertyBool = AceType::MakeRefPtr<PropertyBool>(true);
    textFieldContentModifier->SetShowUnderlineState(propertyBool);
    EXPECT_EQ(textFieldContentModifier->showUnderline_, nullptr);

    /**
     * @tc.steps: step5. call SetShowUnderlineState
     * tc.expected: step5. Check if the showUnderline_ is correct
     */
    textFieldContentModifier->showUnderline_ = AceType::MakeRefPtr<PropertyBool>(false);
    EXPECT_NE(textFieldContentModifier->showUnderline_, nullptr);

    /**
     * @tc.steps: step6. call SetShowUnderlineState
     * tc.expected: step6. Check if the showUnderline_ is correct
     */
    textFieldContentModifier->SetShowUnderlineState(propertyBool);
    EXPECT_EQ(textFieldContentModifier->showUnderline_->Get(), true);

    /**
     * @tc.steps: step7. call SetShowUnderlineState
     * tc.expected: step7. Check if the showUnderline_ is correct
     */
    propertyBool = AceType::MakeRefPtr<PropertyBool>(true);
    textFieldContentModifier->SetShowUnderlineState(propertyBool);
    EXPECT_EQ(textFieldContentModifier->showUnderline_->Get(), true);
}

/**
 * @tc.name: TextFieldContentModifierUTSuit003
 * @tc.desc: Test SetTextDecoration to update textDecorationStyle_, textDecorationColor_, textDecoration_.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, TextFieldContentModifierUTSuit003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step3. check default value
     * tc.expected: step3. Check if the default value right
     */
    EXPECT_EQ(textFieldContentModifier->textDecoration_.value_or(TextDecoration::NONE), TextDecoration::NONE);
    EXPECT_EQ(textFieldContentModifier->textDecorationColor_.value_or(Color::BLACK), Color::BLACK);
    EXPECT_EQ(textFieldContentModifier->textDecorationStyle_.value_or(TextDecorationStyle::SOLID),
        TextDecorationStyle::SOLID);

    /**
     * @tc.steps: step4. call SetTextDecoration
     * tc.expected: step4. Check if the textDecoration_ is correct
     */
    TextDecoration textDecoration = TextDecoration::INHERIT;
    Color color = Color::BLUE;
    TextDecorationStyle textDecorationStyle = TextDecorationStyle::SOLID;
    textFieldContentModifier->SetTextDecoration(textDecoration, color, textDecorationStyle);
    EXPECT_EQ(textFieldContentModifier->textDecoration_.value_or(TextDecoration::NONE), TextDecoration::INHERIT);
    EXPECT_EQ(textFieldContentModifier->textDecorationColor_.value_or(Color::BLACK), Color::BLUE);
    EXPECT_EQ(textFieldContentModifier->textDecorationStyle_.value_or(TextDecorationStyle::DOTTED),
        TextDecorationStyle::SOLID);
    EXPECT_EQ(textFieldContentModifier->textDecorationColorAlpha_->Get(), 255.0f);

    /**
     * @tc.steps: step5. call SetTextDecoration
     * tc.expected: step5. Check if the textDecorationStyle_ is correct
     */
    textDecorationStyle = TextDecorationStyle::DASHED;
    textFieldContentModifier->SetTextDecoration(textDecoration, color, textDecorationStyle);
    EXPECT_EQ(textFieldContentModifier->textDecoration_.value_or(TextDecoration::NONE), TextDecoration::INHERIT);
    EXPECT_EQ(textFieldContentModifier->textDecorationColor_.value_or(Color::BLACK), Color::BLUE);
    EXPECT_EQ(textFieldContentModifier->textDecorationStyle_.value_or(TextDecorationStyle::DOTTED),
        TextDecorationStyle::DASHED);
    EXPECT_EQ(textFieldContentModifier->textDecorationColorAlpha_->Get(), 255.0f);

    /**
     * @tc.steps: step6. call SetTextDecoration
     * tc.expected: step6. Check if the textDecoration_ is correct
     */
    textDecoration = TextDecoration::NONE;
    textFieldContentModifier->SetTextDecoration(textDecoration, color, textDecorationStyle);
    EXPECT_EQ(textFieldContentModifier->textDecoration_.value_or(TextDecoration::NONE), TextDecoration::NONE);
    EXPECT_EQ(textFieldContentModifier->textDecorationColor_.value_or(Color::BLACK), Color::BLUE);
    EXPECT_EQ(textFieldContentModifier->textDecorationStyle_.value_or(TextDecorationStyle::DOTTED),
        TextDecorationStyle::DASHED);
    EXPECT_EQ(textFieldContentModifier->textDecorationColorAlpha_->Get(), 0.0f);

    /**
     * @tc.steps: step7. call SetTextDecoration
     * tc.expected: step7. Check if the textDecorationAnimatable_ is correct
     */
    textDecoration = TextDecoration::UNDERLINE;
    EXPECT_EQ(textFieldContentModifier->textDecorationAnimatable_, false);
    textFieldContentModifier->SetTextDecoration(textDecoration, color, textDecorationStyle);
    EXPECT_EQ(textFieldContentModifier->textDecorationAnimatable_, true);
}

/**
 * @tc.name: TextFieldContentModifierUTSuit004
 * @tc.desc: Test ModifyDecorationInTextStyle to update textStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, TextFieldContentModifierUTSuit004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and focusHub
     */
    CreateTextField();
    GetFocus();

    /**
     * @tc.steps: step2. call CreateNodePaintMethod
     * tc.expected: step2. Check if the value is created.
     */
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step3. prepare the textDecoration_, textDecorationColor_,
     *                   textDecorationStyle_ of textFieldContentModifier
     * tc.expected: step3. Check if the textDecoration_ and so on are correct
     */
    TextDecoration textDecoration = TextDecoration::UNDERLINE;
    Color color = Color::GRAY;
    TextDecorationStyle textDecorationStyle = TextDecorationStyle::WAVY;
    textFieldContentModifier->SetTextDecoration(textDecoration, color, textDecorationStyle);
    EXPECT_EQ(textFieldContentModifier->textDecoration_.value_or(TextDecoration::NONE), TextDecoration::UNDERLINE);
    EXPECT_EQ(textFieldContentModifier->textDecorationColor_.value_or(Color::BLACK), Color::GRAY);
    EXPECT_EQ(textFieldContentModifier->textDecorationStyle_.value_or(TextDecorationStyle::DOTTED),
        TextDecorationStyle::WAVY);
    EXPECT_EQ(textFieldContentModifier->textDecorationColorAlpha_->Get(), 255.0f);

    /**
     * @tc.steps: step4. call SetTextDecoration, satisfy the condition of UNDERLINE to NONE
     * tc.expected: step4. Check if the textDecoration_ is correctly setted
     */
    textDecoration = TextDecoration::NONE;
    textFieldContentModifier->SetTextDecoration(textDecoration, color, textDecorationStyle);
    EXPECT_EQ(textFieldContentModifier->textDecoration_.value_or(TextDecoration::NONE), TextDecoration::NONE);
    EXPECT_EQ(textFieldContentModifier->textDecorationAnimatable_, true);

    /**
     * @tc.steps: step5. call ModifyDecorationInTextStyle
     * tc.expected: step5. Check if the textStyle is correct
     */
    TextStyle textStyle;
    textStyle.SetTextDecoration(TextDecoration::LINE_THROUGH);
    textStyle.SetTextDecorationColor(Color::GREEN);
    textFieldContentModifier->ModifyDecorationInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetTextDecorationFirst(), TextDecoration::NONE);
    EXPECT_EQ(textStyle.GetTextDecorationColor(), Color::GRAY);
}

/**
 * @tc.name: ModifyTextStyle001
 * @tc.desc: Test ModifyTextStyle with fontSize_ set and fontSizeFloat_ valid.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set fontSize via SetFontSize method.
     */
    TextStyle textStyle;
    Dimension fontSizeValue(20.0, DimensionUnit::PX);
    textFieldContentModifier->SetFontSize(fontSizeValue, textStyle);

    /**
     * @tc.steps: step3. Call ModifyTextStyle and verify fontSize is set correctly.
     */
    TextStyle resultTextStyle;
    resultTextStyle.SetFontSize(Dimension(10.0, DimensionUnit::PX));
    textFieldContentModifier->ModifyTextStyle(resultTextStyle);
    EXPECT_EQ(resultTextStyle.GetFontSize().Value(), 20.0);
}

/**
 * @tc.name: ModifyTextStyle002
 * @tc.desc: Test ModifyTextStyle with fontWeight_ set and fontWeightFloat_ valid.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set fontWeight via SetFontWeight method.
     */
    textFieldContentModifier->SetFontWeight(FontWeight::BOLD);

    /**
     * @tc.steps: step3. Call ModifyTextStyle and verify fontWeight is set correctly.
     * Note: FontWeight::BOLD is converted to FontWeight::W700 by ConvertFontWeight.
     */
    TextStyle resultTextStyle;
    resultTextStyle.SetFontWeight(FontWeight::NORMAL);
    textFieldContentModifier->ModifyTextStyle(resultTextStyle);
    EXPECT_EQ(resultTextStyle.GetFontWeight(), FontWeight::W700);
}

/**
 * @tc.name: ModifyTextStyle003
 * @tc.desc: Test ModifyTextStyle with textColor_ set and animatableTextColor_ valid.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyTextStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set textColor via SetTextColor method.
     */
    Color textColorValue = Color::RED;
    textFieldContentModifier->SetTextColor(textColorValue);

    /**
     * @tc.steps: step3. Call ModifyTextStyle and verify textColor is set correctly.
     */
    TextStyle resultTextStyle;
    resultTextStyle.SetTextColor(Color::BLACK);
    textFieldContentModifier->ModifyTextStyle(resultTextStyle);
    EXPECT_EQ(resultTextStyle.GetTextColor(), Color::RED);
}

/**
 * @tc.name: ModifyTextStyle004
 * @tc.desc: Test ModifyTextStyle with adaptMinFontSize and adaptMaxFontSize when GetAdaptTextSize is true.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyTextStyle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set adaptMinFontSize and adaptMaxFontSize via SetAdaptMinFontSize and SetAdaptMaxFontSize.
     */
    TextStyle textStyle;
    Dimension adaptMinValue(10.0, DimensionUnit::PX);
    Dimension adaptMaxValue(30.0, DimensionUnit::PX);
    textFieldContentModifier->SetAdaptMinFontSize(adaptMinValue, textStyle);
    textFieldContentModifier->SetAdaptMaxFontSize(adaptMaxValue, textStyle);

    /**
     * @tc.steps: step3. Call ModifyTextStyle with GetAdaptTextSize true and verify adapt font sizes are set.
     */
    TextStyle resultTextStyle;
    resultTextStyle.SetAdaptTextSize(true);
    textFieldContentModifier->ModifyTextStyle(resultTextStyle);
    EXPECT_EQ(resultTextStyle.GetAdaptMinFontSize().Value(), 10.0);
    EXPECT_EQ(resultTextStyle.GetAdaptMaxFontSize().Value(), 30.0);
}

/**
 * @tc.name: ModifyTextStyle005
 * @tc.desc: Test ModifyTextStyle with fontSize and fontWeight without adapt font sizes.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyTextStyle005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set fontSize and fontWeight on the modifier.
     */
    TextStyle textStyle;
    textFieldContentModifier->SetFontSize(Dimension(18.0, DimensionUnit::PX), textStyle);
    textFieldContentModifier->SetFontWeight(FontWeight::W500);

    /**
     * @tc.steps: step3. Call ModifyTextStyle and verify fontSize and fontWeight are set.
     */
    TextStyle resultTextStyle;
    resultTextStyle.SetFontSize(Dimension(10.0, DimensionUnit::PX));
    resultTextStyle.SetFontWeight(FontWeight::W300);
    textFieldContentModifier->ModifyTextStyle(resultTextStyle);
    EXPECT_EQ(resultTextStyle.GetFontSize().Value(), 18.0);
    EXPECT_EQ(resultTextStyle.GetFontWeight(), FontWeight::W500);
}

/**
 * @tc.name: NeedMeasureUpdate002
 * @tc.desc: Test NeedMeasureUpdate returns true when fontSize mismatch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, NeedMeasureUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set fontSize to a value and then modify fontSizeFloat_ to create mismatch.
     */
    TextStyle textStyle;
    textFieldContentModifier->SetFontSize(Dimension(20.0, DimensionUnit::PX), textStyle);
    textFieldContentModifier->fontSizeFloat_->Set(30.0);

    /**
     * @tc.steps: step3. Call NeedMeasureUpdate and verify flag has PROPERTY_UPDATE_MEASURE.
     */
    PropertyChangeFlag flag = 0;
    bool result = textFieldContentModifier->NeedMeasureUpdate(flag);
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag & PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: NeedMeasureUpdate003
 * @tc.desc: Test NeedMeasureUpdate returns true when adaptMinFontSize mismatch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, NeedMeasureUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set adaptMinFontSize and modify adaptMinFontSizeFloat_ to create mismatch.
     */
    TextStyle textStyle;
    textFieldContentModifier->SetAdaptMinFontSize(Dimension(10.0, DimensionUnit::PX), textStyle);
    textFieldContentModifier->adaptMinFontSizeFloat_->Set(20.0);

    /**
     * @tc.steps: step3. Call NeedMeasureUpdate and verify flag has PROPERTY_UPDATE_MEASURE.
     */
    PropertyChangeFlag flag = 0;
    bool result = textFieldContentModifier->NeedMeasureUpdate(flag);
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag & PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: NeedMeasureUpdate004
 * @tc.desc: Test NeedMeasureUpdate returns true when adaptMaxFontSize mismatch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, NeedMeasureUpdate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set adaptMaxFontSize and modify adaptMaxFontSizeFloat_ to create mismatch.
     */
    TextStyle textStyle;
    textFieldContentModifier->SetAdaptMaxFontSize(Dimension(30.0, DimensionUnit::PX), textStyle);
    textFieldContentModifier->adaptMaxFontSizeFloat_->Set(40.0);

    /**
     * @tc.steps: step3. Call NeedMeasureUpdate and verify flag has PROPERTY_UPDATE_MEASURE.
     */
    PropertyChangeFlag flag = 0;
    bool result = textFieldContentModifier->NeedMeasureUpdate(flag);
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag & PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: NeedMeasureUpdate005
 * @tc.desc: Test NeedMeasureUpdate returns true when fontWeight mismatch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, NeedMeasureUpdate005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set fontWeight and modify fontWeightFloat_ to create mismatch.
     */
    textFieldContentModifier->SetFontWeight(FontWeight::BOLD);
    textFieldContentModifier->fontWeightFloat_->Set(static_cast<int>(FontWeight::NORMAL));

    /**
     * @tc.steps: step3. Call NeedMeasureUpdate and verify flag has PROPERTY_UPDATE_MEASURE.
     */
    PropertyChangeFlag flag = 0;
    bool result = textFieldContentModifier->NeedMeasureUpdate(flag);
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag & PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: NeedMeasureUpdate006
 * @tc.desc: Test NeedMeasureUpdate returns true when textColor mismatch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, NeedMeasureUpdate006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set textColor and modify animatableTextColor_ to create mismatch.
     */
    textFieldContentModifier->SetTextColor(Color::RED);
    textFieldContentModifier->animatableTextColor_->Set(LinearColor(Color::BLUE));

    /**
     * @tc.steps: step3. Call NeedMeasureUpdate and verify flag has PROPERTY_UPDATE_MEASURE_SELF.
     */
    PropertyChangeFlag flag = 0;
    bool result = textFieldContentModifier->NeedMeasureUpdate(flag);
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag & PROPERTY_UPDATE_MEASURE_SELF);
}

/**
 * @tc.name: ModifyDecorationInTextStyle002
 * @tc.desc: Test ModifyDecorationInTextStyle with textDecorationAnimatable_ true and alpha != 0.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyDecorationInTextStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set textDecoration to UNDERLINE then NONE to trigger animatable true.
     */
    Color color = Color::BLUE;
    TextDecorationStyle style = TextDecorationStyle::SOLID;
    textFieldContentModifier->SetTextDecoration(TextDecoration::UNDERLINE, color, style);
    textFieldContentModifier->SetTextDecoration(TextDecoration::NONE, color, style);
    EXPECT_TRUE(textFieldContentModifier->textDecorationAnimatable_);

    /**
     * @tc.steps: step3. Set alpha to non-zero value.
     */
    textFieldContentModifier->textDecorationColorAlpha_->Set(128.0f);

    /**
     * @tc.steps: step4. Call ModifyDecorationInTextStyle and verify textDecoration is UNDERLINE with modified alpha.
     */
    TextStyle textStyle;
    textFieldContentModifier->ModifyDecorationInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetTextDecorationFirst(), TextDecoration::UNDERLINE);
    EXPECT_EQ(textStyle.GetTextDecorationColor().GetAlpha(), 128);
}

/**
 * @tc.name: ModifyDecorationInTextStyle003
 * @tc.desc: Test ModifyDecorationInTextStyle with textDecorationAnimatable_ false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyDecorationInTextStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. First set to INHERIT, then to UNDERLINE (not from NONE, so animatable is false).
     */
    Color color = Color::GREEN;
    TextDecorationStyle style = TextDecorationStyle::DASHED;
    textFieldContentModifier->SetTextDecoration(TextDecoration::INHERIT, color, style);
    textFieldContentModifier->SetTextDecoration(TextDecoration::UNDERLINE, color, style);
    EXPECT_FALSE(textFieldContentModifier->textDecorationAnimatable_);

    /**
     * @tc.steps: step3. Call ModifyDecorationInTextStyle and verify textDecoration is set directly.
     */
    TextStyle textStyle;
    textFieldContentModifier->ModifyDecorationInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetTextDecorationFirst(), TextDecoration::UNDERLINE);
    EXPECT_EQ(textStyle.GetTextDecorationColor(), Color::GREEN);
    EXPECT_EQ(textStyle.GetTextDecorationStyle(), TextDecorationStyle::DASHED);
}

/**
 * @tc.name: ModifyDecorationInTextStyle004
 * @tc.desc: Test ModifyDecorationInTextStyle with textDecorationStyle_ set.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyDecorationInTextStyle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set textDecoration with WAVY style.
     */
    Color color = Color::GRAY;
    TextDecorationStyle style = TextDecorationStyle::WAVY;
    textFieldContentModifier->SetTextDecoration(TextDecoration::UNDERLINE, color, style);

    /**
     * @tc.steps: step3. Call ModifyDecorationInTextStyle and verify textDecorationStyle is set.
     */
    TextStyle textStyle;
    textFieldContentModifier->ModifyDecorationInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetTextDecorationStyle(), TextDecorationStyle::WAVY);
}

/**
 * @tc.name: UpdateTextDecorationMeasureFlag001
 * @tc.desc: Test UpdateTextDecorationMeasureFlag with UNDERLINE and alpha mismatch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, UpdateTextDecorationMeasureFlag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set textDecoration to UNDERLINE with color alpha 255, then modify alpha to create mismatch.
     */
    Color color(0xFF0000FF);
    TextDecorationStyle style = TextDecorationStyle::SOLID;
    textFieldContentModifier->SetTextDecoration(TextDecoration::UNDERLINE, color, style);
    textFieldContentModifier->textDecorationColorAlpha_->Set(128.0f);

    /**
     * @tc.steps: step3. Call NeedMeasureUpdate and verify flag has PROPERTY_UPDATE_MEASURE.
     */
    PropertyChangeFlag flag = 0;
    bool result = textFieldContentModifier->NeedMeasureUpdate(flag);
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag & PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateTextDecorationMeasureFlag002
 * @tc.desc: Test UpdateTextDecorationMeasureFlag with NONE and alpha != 0.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, UpdateTextDecorationMeasureFlag002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set textDecoration to NONE but keep alpha non-zero.
     */
    Color color(0xFF0000FF);
    TextDecorationStyle style = TextDecorationStyle::SOLID;
    textFieldContentModifier->SetTextDecoration(TextDecoration::UNDERLINE, color, style);
    textFieldContentModifier->textDecoration_ = TextDecoration::NONE;
    textFieldContentModifier->textDecorationColorAlpha_->Set(128.0f);

    /**
     * @tc.steps: step3. Call NeedMeasureUpdate and verify flag has PROPERTY_UPDATE_MEASURE.
     */
    PropertyChangeFlag flag = 0;
    bool result = textFieldContentModifier->NeedMeasureUpdate(flag);
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag & PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateTextDecorationMeasureFlag003
 * @tc.desc: Test UpdateTextDecorationMeasureFlag with no flag update when conditions not met.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, UpdateTextDecorationMeasureFlag003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set textDecoration to UNDERLINE with matching alpha.
     */
    Color color(0xFF0000FF);
    TextDecorationStyle style = TextDecorationStyle::SOLID;
    textFieldContentModifier->SetTextDecoration(TextDecoration::UNDERLINE, color, style);

    /**
     * @tc.steps: step3. Call NeedMeasureUpdate and verify flag does not have PROPERTY_UPDATE_MEASURE from decoration.
     */
    PropertyChangeFlag flag = 0;
    textFieldContentModifier->NeedMeasureUpdate(flag);
    EXPECT_FALSE(flag & PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: ModifyTextStyle006
 * @tc.desc: Test ModifyTextStyle when AdaptTextSize is false, adaptMinFontSize and adaptMaxFontSize should not be set.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyTextStyle006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set adaptMinFontSize and adaptMaxFontSize on the modifier.
     */
    TextStyle textStyle;
    Dimension adaptMinValue(10.0, DimensionUnit::PX);
    Dimension adaptMaxValue(30.0, DimensionUnit::PX);
    textFieldContentModifier->SetAdaptMinFontSize(adaptMinValue, textStyle);
    textFieldContentModifier->SetAdaptMaxFontSize(adaptMaxValue, textStyle);

    /**
     * @tc.steps: step3. Call ModifyTextStyle with AdaptTextSize false (default).
     * tc.expected: step3. AdaptMinFontSize and AdaptMaxFontSize should remain unchanged.
     */
    TextStyle resultTextStyle;
    resultTextStyle.SetAdaptTextSize(false);
    Dimension defaultMinFontSize = resultTextStyle.GetAdaptMinFontSize();
    Dimension defaultMaxFontSize = resultTextStyle.GetAdaptMaxFontSize();
    textFieldContentModifier->ModifyTextStyle(resultTextStyle);
    EXPECT_EQ(resultTextStyle.GetAdaptMinFontSize().Value(), defaultMinFontSize.Value());
    EXPECT_EQ(resultTextStyle.GetAdaptMaxFontSize().Value(), defaultMaxFontSize.Value());
}

/**
 * @tc.name: ModifyTextStyle007
 * @tc.desc: Test ModifyTextStyle when AdaptTextSize is true and only adaptMinFontSize is set.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyTextStyle007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set only adaptMinFontSize on the modifier.
     */
    TextStyle textStyle;
    Dimension adaptMinValue(12.0, DimensionUnit::PX);
    textFieldContentModifier->SetAdaptMinFontSize(adaptMinValue, textStyle);

    /**
     * @tc.steps: step3. Call ModifyTextStyle with AdaptTextSize true.
     * tc.expected: step3. Only AdaptMinFontSize should be set, AdaptMaxFontSize remains default.
     */
    TextStyle resultTextStyle;
    resultTextStyle.SetAdaptTextSize(true);
    Dimension defaultMaxFontSize = resultTextStyle.GetAdaptMaxFontSize();
    textFieldContentModifier->ModifyTextStyle(resultTextStyle);
    EXPECT_EQ(resultTextStyle.GetAdaptMinFontSize().Value(), 12.0);
    EXPECT_EQ(resultTextStyle.GetAdaptMaxFontSize().Value(), defaultMaxFontSize.Value());
}

/**
 * @tc.name: ModifyTextStyle008
 * @tc.desc: Test ModifyTextStyle when AdaptTextSize is true and only adaptMaxFontSize is set.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyTextStyle008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set only adaptMaxFontSize on the modifier.
     */
    TextStyle textStyle;
    Dimension adaptMaxValue(35.0, DimensionUnit::PX);
    textFieldContentModifier->SetAdaptMaxFontSize(adaptMaxValue, textStyle);

    /**
     * @tc.steps: step3. Call ModifyTextStyle with AdaptTextSize true.
     * tc.expected: step3. Only AdaptMaxFontSize should be set, AdaptMinFontSize remains default.
     */
    TextStyle resultTextStyle;
    resultTextStyle.SetAdaptTextSize(true);
    Dimension defaultMinFontSize = resultTextStyle.GetAdaptMinFontSize();
    textFieldContentModifier->ModifyTextStyle(resultTextStyle);
    EXPECT_EQ(resultTextStyle.GetAdaptMinFontSize().Value(), defaultMinFontSize.Value());
    EXPECT_EQ(resultTextStyle.GetAdaptMaxFontSize().Value(), 35.0);
}

/**
 * @tc.name: ModifyTextStyle009
 * @tc.desc: Test ModifyTextStyle with textColor placeholder property set.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyTextStyle009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create a color with placeholder and set it as textColor.
     */
    Color textColorWithPlaceholder = Color(ColorPlaceholder::FONT_PRIMARY);
    textFieldContentModifier->SetTextColor(textColorWithPlaceholder);

    /**
     * @tc.steps: step3. Call ModifyTextStyle and verify textColor placeholder is preserved.
     * tc.expected: step3. The placeholder property should be set on the result text color.
     */
    TextStyle resultTextStyle;
    resultTextStyle.SetTextColor(Color::BLACK);
    textFieldContentModifier->ModifyTextStyle(resultTextStyle);
    EXPECT_EQ(resultTextStyle.GetTextColor().GetPlaceholder(), ColorPlaceholder::FONT_PRIMARY);
}

/**
 * @tc.name: ModifyTextStyle010
 * @tc.desc: Test ModifyTextStyle with all properties set together.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, ModifyTextStyle010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Set all properties on the modifier.
     */
    TextStyle textStyle;
    textFieldContentModifier->SetFontSize(Dimension(22.0, DimensionUnit::PX), textStyle);
    textFieldContentModifier->SetFontWeight(FontWeight::W600);
    textFieldContentModifier->SetTextColor(Color::GREEN);
    textFieldContentModifier->SetAdaptMinFontSize(Dimension(8.0, DimensionUnit::PX), textStyle);
    textFieldContentModifier->SetAdaptMaxFontSize(Dimension(40.0, DimensionUnit::PX), textStyle);

    /**
     * @tc.steps: step3. Call ModifyTextStyle with AdaptTextSize true.
     * tc.expected: step3. All properties should be applied correctly.
     */
    TextStyle resultTextStyle;
    resultTextStyle.SetAdaptTextSize(true);
    textFieldContentModifier->ModifyTextStyle(resultTextStyle);
    EXPECT_EQ(resultTextStyle.GetFontSize().Value(), 22.0);
    EXPECT_EQ(resultTextStyle.GetFontWeight(), FontWeight::W600);
    EXPECT_EQ(resultTextStyle.GetTextColor(), Color::GREEN);
    EXPECT_EQ(resultTextStyle.GetAdaptMinFontSize().Value(), 8.0);
    EXPECT_EQ(resultTextStyle.GetAdaptMaxFontSize().Value(), 40.0);
}

/**
 * @tc.name: UpdateTextFadeout001
 * @tc.desc: Test UpdateTextFadeout with leftFade=true and rightFade=true and valid gradientPercent.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, UpdateTextFadeout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create MockCanvas and set expectations.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);

    /**
     * @tc.steps: step3. Call UpdateTextFadeout with leftFade=true, rightFade=true, gradientPercent=0.3.
     * tc.expected: step3. Function executes successfully, DrawRect is called.
     */
    RectF textRect(0.0f, 0.0f, 100.0f, 50.0f);
    float gradientPercent = 0.3f;
    bool leftFade = true;
    bool rightFade = true;
    textFieldContentModifier->UpdateTextFadeout(rsCanvas, textRect, gradientPercent, leftFade, rightFade);
    EXPECT_NE(textFieldContentModifier, nullptr);
}

/**
 * @tc.name: UpdateTextFadeout002
 * @tc.desc: Test UpdateTextFadeout with leftFade=true and rightFade=false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, UpdateTextFadeout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create MockCanvas and set expectations.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);

    /**
     * @tc.steps: step3. Call UpdateTextFadeout with leftFade=true, rightFade=false.
     * tc.expected: step3. Function executes successfully, leftEndPercent should be gradientPercent.
     */
    RectF textRect(10.0f, 5.0f, 200.0f, 30.0f);
    float gradientPercent = 0.25f;
    bool leftFade = true;
    bool rightFade = false;
    textFieldContentModifier->UpdateTextFadeout(rsCanvas, textRect, gradientPercent, leftFade, rightFade);
    EXPECT_NE(textFieldContentModifier, nullptr);
}

/**
 * @tc.name: UpdateTextFadeout003
 * @tc.desc: Test UpdateTextFadeout with leftFade=false and rightFade=true and valid gradientPercent.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, UpdateTextFadeout003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create MockCanvas and set expectations.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);

    /**
     * @tc.steps: step3. Call UpdateTextFadeout with leftFade=false, rightFade=true.
     * tc.expected: step3. Function executes successfully, leftEndPercent should be 0, rightStartPercent adjusted.
     */
    RectF textRect(0.0f, 0.0f, 150.0f, 40.0f);
    float gradientPercent = 0.4f;
    bool leftFade = false;
    bool rightFade = true;
    textFieldContentModifier->UpdateTextFadeout(rsCanvas, textRect, gradientPercent, leftFade, rightFade);
    EXPECT_NE(textFieldContentModifier, nullptr);
}

/**
 * @tc.name: UpdateTextFadeout004
 * @tc.desc: Test UpdateTextFadeout with leftFade=false and rightFade=false.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, UpdateTextFadeout004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create MockCanvas and set expectations.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);

    /**
     * @tc.steps: step3. Call UpdateTextFadeout with leftFade=false, rightFade=false.
     * tc.expected: step3. Function executes successfully, leftEndPercent=0, rightStartPercent=1.0f.
     */
    RectF textRect(20.0f, 10.0f, 300.0f, 60.0f);
    float gradientPercent = 0.5f;
    bool leftFade = false;
    bool rightFade = false;
    textFieldContentModifier->UpdateTextFadeout(rsCanvas, textRect, gradientPercent, leftFade, rightFade);
    EXPECT_NE(textFieldContentModifier, nullptr);
}

/**
 * @tc.name: UpdateTextFadeout005
 * @tc.desc: Test UpdateTextFadeout with rightFade=true and gradientPercent=0 (boundary condition).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, UpdateTextFadeout005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create MockCanvas and set expectations.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);

    /**
     * @tc.steps: step3. Call UpdateTextFadeout with gradientPercent=0.
     * tc.expected: step3. rightStartPercent remains 1.0f because gradientPercent <= 0.
     */
    RectF textRect(0.0f, 0.0f, 100.0f, 50.0f);
    float gradientPercent = 0.0f;
    bool leftFade = true;
    bool rightFade = true;
    textFieldContentModifier->UpdateTextFadeout(rsCanvas, textRect, gradientPercent, leftFade, rightFade);
    EXPECT_NE(textFieldContentModifier, nullptr);
}

/**
 * @tc.name: UpdateTextFadeout006
 * @tc.desc: Test UpdateTextFadeout with rightFade=true and gradientPercent=1.0f (boundary condition).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, UpdateTextFadeout006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create MockCanvas and set expectations.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);

    /**
     * @tc.steps: step3. Call UpdateTextFadeout with gradientPercent=1.0f.
     * tc.expected: step3. rightStartPercent remains 1.0f because gradientPercent >= 1.0f.
     */
    RectF textRect(5.0f, 5.0f, 200.0f, 40.0f);
    float gradientPercent = 1.0f;
    bool leftFade = false;
    bool rightFade = true;
    textFieldContentModifier->UpdateTextFadeout(rsCanvas, textRect, gradientPercent, leftFade, rightFade);
    EXPECT_NE(textFieldContentModifier, nullptr);
}

/**
 * @tc.name: UpdateTextFadeout007
 * @tc.desc: Test UpdateTextFadeout with gradientPercent greater than 1.0f.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, UpdateTextFadeout007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create MockCanvas and set expectations.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);

    /**
     * @tc.steps: step3. Call UpdateTextFadeout with gradientPercent > 1.0f.
     * tc.expected: step3. rightStartPercent remains 1.0f because gradientPercent > 1.0f.
     */
    RectF textRect(0.0f, 0.0f, 100.0f, 50.0f);
    float gradientPercent = 1.5f;
    bool leftFade = true;
    bool rightFade = true;
    textFieldContentModifier->UpdateTextFadeout(rsCanvas, textRect, gradientPercent, leftFade, rightFade);
    EXPECT_NE(textFieldContentModifier, nullptr);
}

/**
 * @tc.name: UpdateTextFadeout008
 * @tc.desc: Test UpdateTextFadeout with negative gradientPercent.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, UpdateTextFadeout008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create MockCanvas and set expectations.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);

    /**
     * @tc.steps: step3. Call UpdateTextFadeout with negative gradientPercent.
     * tc.expected: step3. rightStartPercent remains 1.0f because gradientPercent < 0.
     */
    RectF textRect(0.0f, 0.0f, 100.0f, 50.0f);
    float gradientPercent = -0.5f;
    bool leftFade = false;
    bool rightFade = true;
    textFieldContentModifier->UpdateTextFadeout(rsCanvas, textRect, gradientPercent, leftFade, rightFade);
    EXPECT_NE(textFieldContentModifier, nullptr);
}

/**
 * @tc.name: DoAutoFillDraw001
 * @tc.desc: Test DoAutoFillDraw when autoFillParagraph is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, DoAutoFillDraw001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create autoFillController without paragraph and set animation status.
     */
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;
    autoFillController->SetAutoFillAnimationStatus(AutoFillAnimationStatus::SHOW_ICON);

    /**
     * @tc.steps: step3. Set content offset.
     */
    OffsetF contentOffset(10.0f, 20.0f);
    textFieldContentModifier->SetContentOffset(contentOffset);

    /**
     * @tc.steps: step4. Create DrawingContext and call onDraw.
     * tc.expected: step4. onDraw calls DoAutoFillDraw which returns early because paragraph is null.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, Save()).Times(0);
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textFieldContentModifier->onDraw(context);
    EXPECT_NE(textFieldContentModifier, nullptr);
}

/**
 * @tc.name: DoAutoFillDraw002
 * @tc.desc: Test DoAutoFillDraw with valid paragraph and LTR text direction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, DoAutoFillDraw002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create mock paragraph with text.
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetParagraphText()).WillRepeatedly(testing::Return(u"test123"));
    pattern_->paragraph_ = paragraph;

    /**
     * @tc.steps: step3. Create autoFillController and set paragraph.
     */
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;
    autoFillController->autoFillParagraph_ = paragraph;

    /**
     * @tc.steps: step4. Set content offset and auto fill properties.
     */
    OffsetF contentOffset(10.0f, 20.0f);
    textFieldContentModifier->SetContentOffset(contentOffset);
    textFieldContentModifier->SetAutoFillTranslationOffset(100.0f);
    textFieldContentModifier->SetAutoFillTextScrollOffset(5.0f);
    textFieldContentModifier->SetAutoFillDefaultCharIndex(3.0f);
    textFieldContentModifier->SetAutoFillEmphasizeCharIndex(3.0f);
    textFieldContentModifier->SetAutoFillOriginTextColor(Color::BLACK);

    /**
     * @tc.steps: step5. Create DrawingContext and call onDraw with LTR direction.
     * tc.expected: step5. DoAutoFillDraw executes successfully with LTR direction.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, Save()).Times(testing::AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(testing::AtLeast(1));
    EXPECT_CALL(rsCanvas, ClipRect(testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textFieldContentModifier->onDraw(context);
    EXPECT_NE(textFieldContentModifier, nullptr);
}

/**
 * @tc.name: DoAutoFillDraw003
 * @tc.desc: Test DoAutoFillDraw with RTL text direction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, DoAutoFillDraw003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput with RTL direction and get content modifier.
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create mock paragraph with text.
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetParagraphText()).WillRepeatedly(testing::Return(u"test456"));
    pattern_->paragraph_ = paragraph;

    /**
     * @tc.steps: step3. Create autoFillController and set paragraph.
     */
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;
    autoFillController->autoFillParagraph_ = paragraph;

    /**
     * @tc.steps: step4. Set content offset and auto fill properties with negative translation for RTL.
     */
    OffsetF contentOffset(10.0f, 20.0f);
    textFieldContentModifier->SetContentOffset(contentOffset);
    textFieldContentModifier->SetAutoFillTranslationOffset(-100.0f);
    textFieldContentModifier->SetAutoFillTextScrollOffset(5.0f);
    textFieldContentModifier->SetAutoFillDefaultCharIndex(3.0f);
    textFieldContentModifier->SetAutoFillEmphasizeCharIndex(3.0f);
    textFieldContentModifier->SetAutoFillOriginTextColor(Color::BLUE);

    /**
     * @tc.steps: step5. Set layout property with RTL direction.
     */
    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);

    /**
     * @tc.steps: step6. Create DrawingContext and call onDraw.
     * tc.expected: step6. DoAutoFillDraw executes successfully with RTL clip rect calculation.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, Save()).Times(testing::AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(testing::AtLeast(1));
    EXPECT_CALL(rsCanvas, ClipRect(testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textFieldContentModifier->onDraw(context);
    EXPECT_NE(textFieldContentModifier, nullptr);
}

/**
 * @tc.name: DoAutoFillDraw004
 * @tc.desc: Test DoAutoFillDraw with autoFillOriginTextColor not set (using default).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, DoAutoFillDraw004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create mock paragraph with text.
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetParagraphText()).WillRepeatedly(testing::Return(u"abc"));
    pattern_->paragraph_ = paragraph;

    /**
     * @tc.steps: step3. Create autoFillController and set paragraph.
     */
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;
    autoFillController->autoFillParagraph_ = paragraph;

    /**
     * @tc.steps: step4. Set content offset and auto fill properties without setting origin text color.
     */
    OffsetF contentOffset(5.0f, 15.0f);
    textFieldContentModifier->SetContentOffset(contentOffset);
    textFieldContentModifier->SetAutoFillTranslationOffset(50.0f);
    textFieldContentModifier->SetAutoFillTextScrollOffset(2.0f);
    textFieldContentModifier->SetAutoFillDefaultCharIndex(1.0f);
    textFieldContentModifier->SetAutoFillEmphasizeCharIndex(1.0f);

    /**
     * @tc.steps: step5. Create DrawingContext and call onDraw.
     * tc.expected: step5. DoAutoFillDraw uses default init text color when origin color not set.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, Save()).Times(testing::AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(testing::AtLeast(1));
    EXPECT_CALL(rsCanvas, ClipRect(testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textFieldContentModifier->onDraw(context);
    EXPECT_NE(textFieldContentModifier, nullptr);
}

/**
 * @tc.name: DoAutoFillDraw005
 * @tc.desc: Test DoAutoFillDraw with zero translation offset.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldContentModifierTest, DoAutoFillDraw005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textInput and get content modifier.
     */
    CreateTextField();
    GetFocus();
    auto paint = pattern_->CreateNodePaintMethod();
    auto textFieldContentModifier = pattern_->GetContentModifier();
    EXPECT_NE(textFieldContentModifier, nullptr);

    /**
     * @tc.steps: step2. Create mock paragraph with text.
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetParagraphText()).WillRepeatedly(testing::Return(u"test"));
    pattern_->paragraph_ = paragraph;

    /**
     * @tc.steps: step3. Create autoFillController and set paragraph.
     */
    auto autoFillController = AceType::MakeRefPtr<AutoFillController>(AceType::WeakClaim(AceType::RawPtr(pattern_)));
    pattern_->autoFillController_ = autoFillController;
    autoFillController->autoFillParagraph_ = paragraph;

    /**
     * @tc.steps: step4. Set content offset and auto fill properties with zero translation.
     */
    OffsetF contentOffset(0.0f, 0.0f);
    textFieldContentModifier->SetContentOffset(contentOffset);
    textFieldContentModifier->SetAutoFillTranslationOffset(0.0f);
    textFieldContentModifier->SetAutoFillTextScrollOffset(0.0f);
    textFieldContentModifier->SetAutoFillDefaultCharIndex(0.0f);
    textFieldContentModifier->SetAutoFillEmphasizeCharIndex(0.0f);

    /**
     * @tc.steps: step5. Create DrawingContext and call onDraw.
     * tc.expected: step5. DoAutoFillDraw executes with zero translation offset.
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, Save()).Times(testing::AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(testing::AtLeast(1));
    EXPECT_CALL(rsCanvas, ClipRect(testing::_, testing::_, testing::_)).Times(testing::AtLeast(1));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textFieldContentModifier->onDraw(context);
    EXPECT_NE(textFieldContentModifier, nullptr);
}
} // namespace OHOS::Ace::NG
