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

class TextFieldPatternTestFive : public TextInputBases {
public:
};

/**
 * @tc.name: UpdateInputFilterErrorText001
 * @tc.desc: test testInput text UpdateInputFilterErrorText
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, UpdateInputFilterErrorText001, TestSize.Level0)
{
    CreateTextField();
    auto textFieldEventHub = frameNode_->GetEventHub<TextFieldEventHub>();

    textFieldEventHub->SetOnInputFilterError([](std::string errorText) { ASSERT_TRUE(errorText.empty()); });
    pattern_->UpdateInputFilterErrorText("");

    textFieldEventHub->SetOnInputFilterError([](std::string errorText) { ASSERT_FALSE(errorText.empty()); });
    pattern_->UpdateInputFilterErrorText("hasErrorText");
}

/**
 * @tc.name: RequestFocusReasonToString001
 * @tc.desc: test testInput text RequestFocusReasonToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, RequestFocusReasonToString001, TestSize.Level0)
{
    CreateTextField();
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::DRAG_END), "DragEnd");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::DRAG_MOVE), "DragMove");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::CLICK), "Click");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::LONG_PRESS), "LongPress");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::AUTO_FILL), "AutoFill");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::CLEAN_NODE), "CleanNode");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(RequestFocusReason::UNKNOWN), "Unknown");
    ASSERT_EQ(pattern_->RequestFocusReasonToString(static_cast<RequestFocusReason>(999)), "Unknown");
}

/**
 * @tc.name: RequestKeyboardReasonToString001
 * @tc.desc: test testInput text RequestKeyboardReasonToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, RequestKeyboardReasonToString001, TestSize.Level0)
{
    CreateTextField();
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::ON_KEY_EVENT), "KeyEvent");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::SINGLE_CLICK), "SingleClick");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::DOUBLE_CLICK), "DoubleClick");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::LONG_PRESS), "LongPress");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::RESET_KEYBOARD), "ResetKeyboard");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::SET_SELECTION), "SetSelection");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::SEARCH_REQUEST), "SearchRequest");
    ASSERT_EQ(
        pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::AUTO_FILL_REQUEST_FAIL), "AutoFillRequestFail");
    ASSERT_EQ(
        pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::SHOW_KEYBOARD_ON_FOCUS), "ShowKeyboardOnFocus");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::STYLUS_DETECTOR), "StylusDetector");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::CUSTOM_KEYBOARD), "CustomKeyboard");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(RequestKeyboardReason::UNKNOWN), "Unknown");
    ASSERT_EQ(pattern_->RequestKeyboardReasonToString(static_cast<RequestKeyboardReason>(999)), "Unknown");
}

/**
 * @tc.name: TextInputTypeToString001
 * @tc.desc: test testInput text TextInputTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, TextInputTypeToString001, TestSize.Level0)
{
    CreateTextField();
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER);
    layoutProperty->UpdateMaxLines(2);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.NUMBER");
    layoutProperty->UpdateMaxLines(1);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.Number");
    layoutProperty->UpdateTextInputType(TextInputType::EMAIL_ADDRESS);
    layoutProperty->UpdateMaxLines(2);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.EMAIL");
    layoutProperty->UpdateMaxLines(1);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.Email");
    layoutProperty->UpdateTextInputType(TextInputType::PHONE);
    layoutProperty->UpdateMaxLines(2);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.PHONE_NUMBER");
    layoutProperty->UpdateMaxLines(1);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.PhoneNumber");
    layoutProperty->UpdateTextInputType(TextInputType::URL);
    layoutProperty->UpdateMaxLines(2);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.URL");
    layoutProperty->UpdateMaxLines(1);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.URL");
    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.Password");
    layoutProperty->UpdateTextInputType(TextInputType::USER_NAME);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.USER_NAME");
    layoutProperty->UpdateTextInputType(TextInputType::NEW_PASSWORD);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.NEW_PASSWORD");
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER_PASSWORD);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.NUMBER_PASSWORD");
    layoutProperty->UpdateTextInputType(TextInputType::NUMBER_DECIMAL);
    layoutProperty->UpdateMaxLines(2);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.NUMBER_DECIMAL");
    layoutProperty->UpdateMaxLines(1);
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.NUMBER_DECIMAL");
    layoutProperty->UpdateTextInputType(static_cast<TextInputType>(999));
    pattern_->isTextInput_ = false;
    ASSERT_EQ(pattern_->TextInputTypeToString(), "TextAreaType.NORMAL");
    pattern_->isTextInput_ = true;
    ASSERT_EQ(pattern_->TextInputTypeToString(), "InputType.Normal");
}

/**
 * @tc.name: AutoCapTypeToString001
 * @tc.desc: test testInput text AutoCapTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, AutoCapTypeToString001, TestSize.Level0)
{
    CreateTextField();
    pattern_->UpdateAutoCapitalizationMode(AutoCapitalizationMode::NONE);
    ASSERT_EQ(pattern_->AutoCapTypeToString(), "AutoCapitalizationMode.NONE");
    pattern_->UpdateAutoCapitalizationMode(AutoCapitalizationMode::WORDS);
    ASSERT_EQ(pattern_->AutoCapTypeToString(), "AutoCapitalizationMode.WORDS");
    pattern_->UpdateAutoCapitalizationMode(AutoCapitalizationMode::SENTENCES);
    ASSERT_EQ(pattern_->AutoCapTypeToString(), "AutoCapitalizationMode.SENTENCES");
    pattern_->UpdateAutoCapitalizationMode(AutoCapitalizationMode::ALL_CHARACTERS);
    ASSERT_EQ(pattern_->AutoCapTypeToString(), "AutoCapitalizationMode.ALL_CHARACTERS");
    pattern_->UpdateAutoCapitalizationMode(static_cast<AutoCapitalizationMode>(999));
    ASSERT_EQ(pattern_->AutoCapTypeToString(), "AutoCapitalizationMode.NONE");
}

/**
 * @tc.name: GetInputStyleString001
 * @tc.desc: test testInput text GetInputStyleString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, GetInputStyleString001, TestSize.Level0)
{
    CreateTextField();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    pattern_->isTextInput_ = false;
    ASSERT_EQ(pattern_->GetInputStyleString(), "TextContentStyle.INLINE");
    pattern_->isTextInput_ = true;
    ASSERT_EQ(pattern_->GetInputStyleString(), "TextInputStyle.Inline");
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    pattern_->isTextInput_ = false;
    ASSERT_EQ(pattern_->GetInputStyleString(), "TextContentStyle.DEFAULT");
    pattern_->isTextInput_ = true;
    ASSERT_EQ(pattern_->GetInputStyleString(), "TextInputStyle.Default");
    paintProperty->UpdateInputStyle(static_cast<InputStyle>(999));
    pattern_->isTextInput_ = false;
    ASSERT_EQ(pattern_->GetInputStyleString(), "TextContentStyle.DEFAULT");
    pattern_->isTextInput_ = true;
    ASSERT_EQ(pattern_->GetInputStyleString(), "TextInputStyle.Default");
}


/**
 * @tc.name: SetShowError001
 * @tc.desc: test testInput text SetShowError
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, SetShowError001, TestSize.Level0)
{
    CreateTextField();
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();

    pattern_->SetShowError();
    ASSERT_EQ(pattern_->underlineWidth_, Dimension(1.0_px));

    layoutProperty->UpdateErrorText("This is Error Text");
    layoutProperty->UpdateShowErrorText(true);
    layoutProperty->UpdateShowUnderline(true);
    pattern_->SetShowError();
    ASSERT_EQ(pattern_->underlineWidth_, Dimension(2.0_px));

    layoutProperty->UpdateShowUnderline(false);
    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    BorderWidthProperty borderWidthProperty;
    paintProperty->UpdateBorderWidthFlagByUser(borderWidthProperty);
    pattern_->SetShowError();
    ASSERT_FALSE(paintProperty->HasInnerBorderWidth());

    paintProperty->ResetBorderWidthFlagByUser();
    pattern_->SetShowError();
    ASSERT_EQ(paintProperty->GetInnerBorderWidthValue(), Dimension(1.0_vp));
}

/**
 * @tc.name: GetPaddingByUserValue001
 * @tc.desc: test testInput text GetPaddingByUserValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestFive, GetPaddingByUserValue001, TestSize.Level0)
{
    CreateTextField();
    auto theme = pattern_->GetTheme();
    CHECK_NULL_VOID(theme);
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    PaddingProperty padding;
    paintProperty->UpdatePaddingByUser(padding);
    std::cout << "GetPaddingByUserValue001" << std::endl;
    theme->padding_ = Edge(1, 3, 2, 4);
    PaddingProperty paddingWhenEmpty = pattern_->GetPaddingByUserValue();
    ASSERT_EQ(paddingWhenEmpty.left, CalcLength(1));
    ASSERT_EQ(paddingWhenEmpty.right, CalcLength(2));
    ASSERT_EQ(paddingWhenEmpty.top, CalcLength(3));
    ASSERT_EQ(paddingWhenEmpty.bottom, CalcLength(4));

    std::cout << "GetPaddingByUserValue002" << std::endl;
    padding.SetEdges(CalcLength(1), CalcLength(2), CalcLength(3), CalcLength(4));
    paintProperty->UpdatePaddingByUser(padding);
    theme->padding_ = Edge(5, 7, 6, 8);
    PaddingProperty paddingWhenHasValue = pattern_->GetPaddingByUserValue();
    ASSERT_EQ(paddingWhenEmpty.left, CalcLength(1));
    ASSERT_EQ(paddingWhenEmpty.right, CalcLength(2));
    ASSERT_EQ(paddingWhenEmpty.top, CalcLength(3));
    ASSERT_EQ(paddingWhenEmpty.bottom, CalcLength(4));
}
} // namespace OHOS::Ace::NG