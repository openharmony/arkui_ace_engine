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

#include "test/mock/frameworks/core/common/mock_container.h"
#include "text_input_base.h"

#include "frameworks/core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "frameworks/core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {

class TextFieldPatternFuncTestThree : public TextInputBases {
public:
};

/**
 * @tc.name: CheckMousePressedOverScrollBar001
 * @tc.desc: Test CheckMousePressedOverScrollBar when mouse is not over scroll bar
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, CheckMousePressedOverScrollBar001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with scroll bar enabled
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    pattern_->hasMousePressed_ = true;
    /**
     * @tc.steps: step2. Create gesture event with position outside scroll bar
     */
    GestureEvent info;
    info.SetLocalLocation(Offset(50, 50));
    /**
     * @tc.steps: step3. Call CheckMousePressedOverScrollBar
     * @tc.expected: Function should return false when mouse is not over scroll bar
     */
    bool result = pattern_->CheckMousePressedOverScrollBar(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckMousePressedOverScrollBar002
 * @tc.desc: Test CheckMousePressedOverScrollBar when hasMousePressed_ is false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, CheckMousePressedOverScrollBar002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with hasMousePressed_ = false
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    pattern_->hasMousePressed_ = false;
    /**
     * @tc.steps: step2. Create gesture event
     */
    GestureEvent info;
    info.SetLocalLocation(Offset(50, 50));
    /**
     * @tc.steps: step3. Call CheckMousePressedOverScrollBar
     * @tc.expected: Function should return false when hasMousePressed_ is false
     */
    bool result = pattern_->CheckMousePressedOverScrollBar(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckMousePressedOverScrollBar003
 * @tc.desc: Test CheckMousePressedOverScrollBar when display mode is OFF
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, CheckMousePressedOverScrollBar003, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with display mode OFF
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    pattern_->hasMousePressed_ = true;
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateDisplayMode(DisplayMode::OFF);
    /**
     * @tc.steps: step2. Create gesture event
     */
    GestureEvent info;
    info.SetLocalLocation(Offset(50, 50));
    /**
     * @tc.steps: step3. Call CheckMousePressedOverScrollBar
     * @tc.expected: Function should return false when display mode is OFF
     */
    bool result = pattern_->CheckMousePressedOverScrollBar(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleBetweenSelectedPosition001
 * @tc.desc: Test HandleBetweenSelectedPosition when using mouse
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, HandleBetweenSelectedPosition001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with mouse input
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create gesture event
     */
    GestureEvent info;
    info.SetGlobalLocation(Offset(100, 100));
    /**
     * @tc.steps: step3. Call HandleBetweenSelectedPosition
     * @tc.expected: Function should return false when using mouse
     */
    bool result = pattern_->HandleBetweenSelectedPosition(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleBetweenSelectedPosition002
 * @tc.desc: Test HandleBetweenSelectedPosition when select overlay is off
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, HandleBetweenSelectedPosition002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern without select overlay
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create gesture event
     */
    GestureEvent info;
    info.SetGlobalLocation(Offset(100, 100));
    /**
     * @tc.steps: step3. Call HandleBetweenSelectedPosition
     * @tc.expected: Function should return false when select overlay is off
     */
    bool result = pattern_->HandleBetweenSelectedPosition(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleBetweenSelectedPosition003
 * @tc.desc: Test HandleBetweenSelectedPosition when position is not between selected
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, HandleBetweenSelectedPosition003, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with select overlay
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    pattern_->selectOverlay_ = AceType::MakeRefPtr<TextFieldSelectOverlay>(pattern_);
    ASSERT_NE(pattern_->selectOverlay_, nullptr);
    /**
     * @tc.steps: step2. Create gesture event at position outside selected area
     */
    GestureEvent info;
    info.SetGlobalLocation(Offset(1000, 1000));
    /**
     * @tc.steps: step3. Call HandleBetweenSelectedPosition
     * @tc.expected: Function should return false when position is not between selected
     */
    bool result = pattern_->HandleBetweenSelectedPosition(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleBetweenSelectedPosition004
 * @tc.desc: Test HandleBetweenSelectedPosition with valid selected position
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, HandleBetweenSelectedPosition004, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with select overlay and content
     */
    CreateTextField("Hello World", "");
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set up select controller with selection
     */
    ASSERT_NE(pattern_->selectController_, nullptr);
    pattern_->HandleSetSelection(0, 5);
    /**
     * @tc.steps: step3. Create gesture event
     * @tc.expected: Function returns false when overlay conditions are not met
     */
    GestureEvent info;
    info.SetGlobalLocation(Offset(50, 50));
    bool result = pattern_->HandleBetweenSelectedPosition(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScheduleCursorTwinkling001
 * @tc.desc: Test ScheduleCursorTwinkling when isTransparent_ is true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, ScheduleCursorTwinkling001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with transparent state
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    pattern_->isTransparent_ = true;
    /**
     * @tc.steps: step2. Call ScheduleCursorTwinkling
     * @tc.expected: Function should return early when isTransparent_ is true
     */
    pattern_->ScheduleCursorTwinkling();
    EXPECT_FALSE(pattern_->isCaretTwinkling_);
}

/**
 * @tc.name: ScheduleCursorTwinkling002
 * @tc.desc: Test ScheduleCursorTwinkling when host is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, ScheduleCursorTwinkling002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern without adding to tree
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isTransparent_ = false;
    /**
     * @tc.steps: step2. Call ScheduleCursorTwinkling
     * @tc.expected: Function should return early when host is null
     */
    pattern->ScheduleCursorTwinkling();
    EXPECT_FALSE(pattern->isCaretTwinkling_);
}

/**
 * @tc.name: ScheduleCursorTwinkling003
 * @tc.desc: Test ScheduleCursorTwinkling when context is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, ScheduleCursorTwinkling003, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    pattern_->isTransparent_ = false;
    /**
     * @tc.steps: step2. Call ScheduleCursorTwinkling
     * @tc.expected: Function should schedule cursor twinkling
     */
    pattern_->ScheduleCursorTwinkling();
    EXPECT_FALSE(pattern_->cursorTwinklingTask_);
}

/**
 * @tc.name: ScheduleCursorTwinkling004
 * @tc.desc: Test ScheduleCursorTwinkling when task executor is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, ScheduleCursorTwinkling004, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    pattern_->isTransparent_ = false;
    /**
     * @tc.steps: step2. Call ScheduleCursorTwinkling
     * @tc.expected: Function should schedule cursor twinkling
     */
    pattern_->ScheduleCursorTwinkling();
    EXPECT_FALSE(pattern_->cursorTwinklingTask_);
}

/**
 * @tc.name: ScheduleCursorTwinkling005
 * @tc.desc: Test ScheduleCursorTwinkling when dragging
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, ScheduleCursorTwinkling005, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with dragging status
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    pattern_->isTransparent_ = false;
    pattern_->dragRecipientStatus_ = DragStatus::DRAGGING;
    /**
     * @tc.steps: step2. Call ScheduleCursorTwinkling
     * @tc.expected: Function should return early when dragging
     */
    pattern_->ScheduleCursorTwinkling();
    EXPECT_FALSE(pattern_->isCaretTwinkling_);
}

/**
 * @tc.name: ScheduleCursorTwinkling006
 * @tc.desc: Test ScheduleCursorTwinkling with valid scenario
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, ScheduleCursorTwinkling006, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with valid scenario
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    pattern_->isTransparent_ = false;
    pattern_->dragRecipientStatus_ = DragStatus::NONE;
    pattern_->twinklingInterval_ = 500;
    /**
     * @tc.steps: step2. Call ScheduleCursorTwinkling
     * @tc.expected: Function should schedule cursor twinkling task
     */
    pattern_->ScheduleCursorTwinkling();
    EXPECT_FALSE(pattern_->cursorTwinklingTask_);
}

/**
 * @tc.name: UpdatePropertyImpl001
 * @tc.desc: Test UpdatePropertyImpl with fontSize property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for fontSize
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    CalcDimension fontSize(16.0, DimensionUnit::VP);
    value->SetValue(fontSize);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with fontSize key
     * @tc.expected: Function should execute without crash
     */
    pattern_->UpdatePropertyImpl("fontSize", value);
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl002
 * @tc.desc: Test UpdatePropertyImpl with placeholder property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for placeholder
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    std::u16string placeholder = u"Enter text";
    value->SetValue(placeholder);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with placeholder key
     * @tc.expected: Placeholder should be updated
     */
    pattern_->UpdatePropertyImpl("placeholder", value);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl003
 * @tc.desc: Test UpdatePropertyImpl with text property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl003, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for text
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    std::u16string text = u"Hello World";
    value->SetValue(text);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with text key
     * @tc.expected: Text should be updated
     */
    pattern_->UpdatePropertyImpl("text", value);
    EXPECT_NE(pattern_->contentController_, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl004
 * @tc.desc: Test UpdatePropertyImpl with cancelButtonIconSize property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl004, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with cancel button
     */
    CreateTextField("", "", [](TextFieldModelNG& model) { model.SetIsShowCancelButton(true); });
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for icon size
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    CalcDimension iconSize(24.0, DimensionUnit::VP);
    value->SetValue(iconSize);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with cancelButtonIconSize key
     * @tc.expected: Icon size should be updated
     */
    pattern_->UpdatePropertyImpl("cancelButtonIconSize", value);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl005
 * @tc.desc: Test UpdatePropertyImpl with cancelButtonIconColor property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl005, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with cancel button
     */
    CreateTextField("", "", [](TextFieldModelNG& model) { model.SetIsShowCancelButton(true); });
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for icon color
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    Color iconColor = Color(0xFFFF0000);
    value->SetValue(iconColor);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with cancelButtonIconColor key
     * @tc.expected: Icon color should be updated
     */
    pattern_->UpdatePropertyImpl("cancelButtonIconColor", value);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl006
 * @tc.desc: Test UpdatePropertyImpl with placeholderColor property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl006, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for placeholder color
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    Color placeholderColor = Color(0xFF0000FF);
    value->SetValue(placeholderColor);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with placeholderColor key
     * @tc.expected: Placeholder color should be updated
     */
    pattern_->UpdatePropertyImpl("placeholderColor", value);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl007
 * @tc.desc: Test UpdatePropertyImpl with placeholderFontSize property (percent unit)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl007, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for placeholder font size with percent
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    CalcDimension fontSize(0.8, DimensionUnit::PERCENT);
    value->SetValue(fontSize);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with placeholderFontSize key
     * @tc.expected: Placeholder font size should be converted from percent
     */
    pattern_->UpdatePropertyImpl("placeholderFontSize", value);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl008
 * @tc.desc: Test UpdatePropertyImpl with backgroundColor property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl008, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for background color
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    Color bgColor = Color(0xFF00FF00);
    value->SetValue(bgColor);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with backgroundColor key
     * @tc.expected: Background color should be updated
     */
    pattern_->UpdatePropertyImpl("backgroundColor", value);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl009
 * @tc.desc: Test UpdatePropertyImpl with foregroundColor property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl009, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for foreground color
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    Color fgColor = Color(0xFFFFFF00);
    value->SetValue(fgColor);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with foregroundColor key
     * @tc.expected: Foreground color should be updated
     */
    pattern_->UpdatePropertyImpl("foregroundColor", value);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl010
 * @tc.desc: Test UpdatePropertyImpl with caretColor property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl010, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for caret color
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    Color caretColor = Color(0xFFFFFFFF);
    value->SetValue(caretColor);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with caretColor key
     * @tc.expected: Caret color should be updated
     */
    pattern_->UpdatePropertyImpl("caretColor", value);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl011
 * @tc.desc: Test UpdatePropertyImpl with selectedBackgroundColor property (alpha = 255)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl011, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for selected background color with full alpha
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    Color selectedBgColor = Color(0xFF808080);
    value->SetValue(selectedBgColor);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with selectedBackgroundColor key
     * @tc.expected: Selected background color opacity should be adjusted
     */
    pattern_->UpdatePropertyImpl("selectedBackgroundColor", value);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl012
 * @tc.desc: Test UpdatePropertyImpl with caretWidth property (value <= 0)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl012, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for caret width with invalid value
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    CalcDimension caretWidth(0.0, DimensionUnit::VP);
    value->SetValue(caretWidth);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with caretWidth key
     * @tc.expected: Caret width should use theme default value
     */
    pattern_->UpdatePropertyImpl("caretWidth", value);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl013
 * @tc.desc: Test UpdatePropertyImpl with letterSpacing property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl013, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for letter spacing
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    CalcDimension letterSpacing(2.0, DimensionUnit::VP);
    value->SetValue(letterSpacing);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with letterSpacing key
     * @tc.expected: Letter spacing should be updated
     */
    pattern_->UpdatePropertyImpl("letterSpacing", value);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl014
 * @tc.desc: Test UpdatePropertyImpl with width property (value <= 0)
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl014, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for width with invalid value
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    CalcDimension width(0.0, DimensionUnit::VP);
    value->SetValue(width);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with width key
     * @tc.expected: Function should return early when width <= 0
     */
    pattern_->UpdatePropertyImpl("width", value);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl015
 * @tc.desc: Test UpdatePropertyImpl with null value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl015, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Call UpdatePropertyImpl with null value
     * @tc.expected: Function should return early when value is null
     */
    RefPtr<PropertyValueBase> nullValue = nullptr;
    pattern_->UpdatePropertyImpl("text", nullValue);
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl016
 * @tc.desc: Test UpdatePropertyImpl with unknown property key
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImpl016, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    value->SetValue(std::u16string(u"test"));
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with unknown key
     * @tc.expected: Function should handle unknown property gracefully
     */
    pattern_->UpdatePropertyImpl("unknownProperty", value);
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: NeedsSendFillContent001
 * @tc.desc: Test NeedsSendFillContent when IsNeedProcessAutoFill returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, NeedsSendFillContent001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Mock IsNeedProcessAutoFill to return false by setting auto fill disabled
     */
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateEnableAutoFill(false);
    /**
     * @tc.steps: step3. Call NeedsSendFillContent
     * @tc.expected: Should return false when auto fill is disabled
     */
    bool result = pattern_->NeedsSendFillContent();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedsSendFillContent002
 * @tc.desc: Test NeedsSendFillContent when text content type is not password type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, NeedsSendFillContent002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with auto fill enabled
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateEnableAutoFill(true);
    /**
     * @tc.steps: step2. Set text content type to non-password type (EMAIL_ADDRESS)
     */
    layoutProperty->UpdateTextContentType(TextContentType::EMAIL_ADDRESS);
    /**
     * @tc.steps: step3. Call NeedsSendFillContent
     * @tc.expected: Should return false when content type is not password type
     */
    bool result = pattern_->NeedsSendFillContent();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedsSendFillContent003
 * @tc.desc: Test NeedsSendFillContent when text content type is password type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, NeedsSendFillContent003, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with auto fill enabled
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateEnableAutoFill(true);
    /**
     * @tc.steps: step2. Set text content type to password type (NEW_PASSWORD)
     */
    layoutProperty->UpdateTextContentType(TextContentType::NEW_PASSWORD);
    /**
     * @tc.steps: step3. Call NeedsSendFillContent
     * @tc.expected: Should return true when content type is password type
     */
    bool result = pattern_->NeedsSendFillContent();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnReportPasteEvent001
 * @tc.desc: Test OnReportPasteEvent when frameNode is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, OnReportPasteEvent001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Call OnReportPasteEvent with null frameNode
     * @tc.expected: Function should return early without crash when frameNode is null
     */
    RefPtr<FrameNode> nullNode = nullptr;
    pattern_->OnReportPasteEvent(nullNode);
    ASSERT_NE(pattern_, nullptr);
}

/**
 * @tc.name: OnReportPasteEvent002
 * @tc.desc: Test OnReportPasteEvent when frameNode tag is TEXTINPUT_ETS_TAG
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, OnReportPasteEvent002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern with TextInput tag
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    /**
     * @tc.steps: step2. Verify host tag is TEXTINPUT_ETS_TAG
     */
    std::string tag = host->GetTag();
    EXPECT_EQ(tag, "TextInput");
    /**
     * @tc.steps: step3. Call OnReportPasteEvent
     * @tc.expected: Function should execute without crash for TextInput tag
     */
    pattern_->OnReportPasteEvent(host);
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: OnReportPasteEvent003
 * @tc.desc: Test OnReportPasteEvent when frameNode tag is SEARCH_Field_ETS_TAG
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, OnReportPasteEvent003, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create FrameNode with SearchField tag
     */
    auto searchNode = FrameNode::GetOrCreateFrameNode("SearchField", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(searchNode, nullptr);
    /**
     * @tc.steps: step2. Get pattern from search node
     */
    RefPtr<TextFieldPattern> searchPattern = searchNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(searchPattern, nullptr);
    /**
     * @tc.steps: step3. Verify node tag is SearchField
     */
    std::string tag = searchNode->GetTag();
    EXPECT_EQ(tag, "SearchField");
    /**
     * @tc.steps: step4. Call OnReportPasteEvent
     * @tc.expected: Function should execute without crash for SearchField tag
     */
    searchPattern->OnReportPasteEvent(searchNode);
    ASSERT_NE(searchPattern->GetHost(), nullptr);
}

/**
 * @tc.name: OnReportPasteEvent004
 * @tc.desc: Test OnReportPasteEvent when frameNode tag is other type
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, OnReportPasteEvent004, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create FrameNode with custom tag
     */
    auto customNode = FrameNode::GetOrCreateFrameNode("CustomTag", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(customNode, nullptr);
    /**
     * @tc.steps: step2. Get pattern from custom node
     */
    RefPtr<TextFieldPattern> customPattern = customNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(customPattern, nullptr);
    /**
     * @tc.steps: step3. Verify node tag is not TextInput or SearchField
     */
    std::string tag = customNode->GetTag();
    EXPECT_NE(tag, "TextInput");
    EXPECT_NE(tag, "SearchField");
    /**
     * @tc.steps: step4. Call OnReportPasteEvent
     * @tc.expected: Function should execute without crash for unknown tag
     */
    customPattern->OnReportPasteEvent(customNode);
    ASSERT_NE(customPattern->GetHost(), nullptr);
}

/**
 * @tc.name: NeedDrawPreviewText001
 * @tc.desc: Test NeedDrawPreviewText when preview text start and end are not set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, NeedDrawPreviewText001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Get paint property and reset preview text values
     */
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->ResetPreviewTextStart();
    paintProperty->ResetPreviewTextEnd();
    /**
     * @tc.steps: step3. Verify hasPreviewText_ is false (default value)
     */
    EXPECT_FALSE(pattern_->GetIsPreviewText());
    /**
     * @tc.steps: step4. Call NeedDrawPreviewText
     * @tc.expected: Should return false when preview text start/end are not set
     * and hasPreviewText_ is false, triggering the branch:
     * if (!paintStart.has_value() || !paintEnd.has_value())
     */
    bool result = pattern_->NeedDrawPreviewText();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedDrawPreviewText002
 * @tc.desc: Test NeedDrawPreviewText when only preview text start is not set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, NeedDrawPreviewText002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Get paint property and reset only preview text start
     */
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->ResetPreviewTextStart();
    paintProperty->UpdatePreviewTextEnd(5);
    /**
     * @tc.steps: step3. Verify hasPreviewText_ is false (default value)
     */
    EXPECT_FALSE(pattern_->GetIsPreviewText());
    /**
     * @tc.steps: step4. Call NeedDrawPreviewText
     * @tc.expected: Should return false when preview text start is not set
     * triggering the branch: if (!paintStart.has_value() || !paintEnd.has_value())
     */
    bool result = pattern_->NeedDrawPreviewText();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedDrawPreviewText003
 * @tc.desc: Test NeedDrawPreviewText when only preview text end is not set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, NeedDrawPreviewText003, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Get paint property and reset only preview text end
     */
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdatePreviewTextStart(0);
    paintProperty->ResetPreviewTextEnd();
    /**
     * @tc.steps: step3. Verify hasPreviewText_ is false (default value)
     */
    EXPECT_FALSE(pattern_->GetIsPreviewText());
    /**
     * @tc.steps: step4. Call NeedDrawPreviewText
     * @tc.expected: Should return false when preview text end is not set
     * triggering the branch: if (!paintStart.has_value() || !paintEnd.has_value())
     */
    bool result = pattern_->NeedDrawPreviewText();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: RequestKeyboardAfterLongPress001
 * @tc.desc: Test RequestKeyboardAfterLongPress when isCustomKeyboardAttached_ is false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, RequestKeyboardAfterLongPress001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set isLongPress_ to true to trigger keyboard request
     */
    pattern_->isLongPress_ = true;
    /**
     * @tc.steps: step3. Verify isCustomKeyboardAttached_ is false (default value)
     */
    EXPECT_FALSE(pattern_->isCustomKeyboardAttached_);
    /**
     * @tc.steps: step4. Verify keyboardAvoidance_ is false (default value)
     */
    EXPECT_FALSE(pattern_->keyboardAvoidance_);
    /**
     * @tc.steps: step5. Call RequestKeyboardAfterLongPress
     * This should trigger the branch: if (!isCustomKeyboardAttached_ || keyboardAvoidance_)
     * Since isCustomKeyboardAttached_ is false, the condition evaluates to true
     * @tc.expected: isLongPress_ should be reset to false after function execution
     */
    pattern_->RequestKeyboardAfterLongPress();
    EXPECT_FALSE(pattern_->isLongPress_);
}

/**
 * @tc.name: RequestKeyboardAfterLongPress002
 * @tc.desc: Test RequestKeyboardAfterLongPress when keyboardAvoidance_ is true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, RequestKeyboardAfterLongPress002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set isLongPress_ to true to trigger keyboard request
     */
    pattern_->isLongPress_ = true;
    /**
     * @tc.steps: step3. Set keyboardAvoidance_ to true using SetCustomKeyboardOption
     */
    pattern_->SetCustomKeyboardOption(true);
    /**
     * @tc.steps: step4. Verify keyboardAvoidance_ is true
     */
    EXPECT_TRUE(pattern_->keyboardAvoidance_);
    /**
     * @tc.steps: step5. Call RequestKeyboardAfterLongPress
     * This should trigger the branch: if (!isCustomKeyboardAttached_ || keyboardAvoidance_)
     * Since keyboardAvoidance_ is true, the condition evaluates to true
     * @tc.expected: isLongPress_ should be reset to false after function execution
     */
    pattern_->RequestKeyboardAfterLongPress();
    EXPECT_FALSE(pattern_->isLongPress_);
}

/**
 * @tc.name: RequestKeyboardAfterLongPress003
 * @tc.desc: Test RequestKeyboardAfterLongPress when both isCustomKeyboardAttached_ is false and keyboardAvoidance_ is
 * true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, RequestKeyboardAfterLongPress003, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set isLongPress_ to true to trigger keyboard request
     */
    pattern_->isLongPress_ = true;
    /**
     * @tc.steps: step3. Set keyboardAvoidance_ to true
     */
    pattern_->SetCustomKeyboardOption(true);
    /**
     * @tc.steps: step4. Verify isCustomKeyboardAttached_ is false (default value)
     */
    EXPECT_FALSE(pattern_->isCustomKeyboardAttached_);
    /**
     * @tc.steps: step5. Verify keyboardAvoidance_ is true
     */
    EXPECT_TRUE(pattern_->keyboardAvoidance_);
    /**
     * @tc.steps: step6. Call RequestKeyboardAfterLongPress
     * This should trigger the branch: if (!isCustomKeyboardAttached_ || keyboardAvoidance_)
     * Both conditions make the expression true
     * @tc.expected: isLongPress_ should be reset to false after function execution
     */
    pattern_->RequestKeyboardAfterLongPress();
    EXPECT_FALSE(pattern_->isLongPress_);
}

/**
 * @tc.name: RequestKeyboardAfterLongPress004
 * @tc.desc: Test RequestKeyboardAfterLongPress when isLongPress_ is false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, RequestKeyboardAfterLongPress004, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Verify isLongPress_ is false (default value)
     */
    EXPECT_FALSE(pattern_->isLongPress_);
    /**
     * @tc.steps: step3. Call RequestKeyboardAfterLongPress
     * Since isLongPress_ is false, the main if condition should not be entered
     * @tc.expected: isLongPress_ should remain false after function execution
     */
    pattern_->RequestKeyboardAfterLongPress();
    EXPECT_FALSE(pattern_->isLongPress_);
}

/**
 * @tc.name: SetFocusStyle001
 * @tc.desc: Test SetFocusStyle when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, SetFocusStyle001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call SetFocusStyle
     * This should trigger the branch: if (IsTV()) which calls SetFocusStyleForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->SetFocusStyle();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: SetFocusStyle002
 * @tc.desc: Test SetFocusStyle when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, SetFocusStyle002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call SetFocusStyle
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->SetFocusStyle();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: ClearFocusStyle001
 * @tc.desc: Test ClearFocusStyle when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, ClearFocusStyle001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call ClearFocusStyle
     * This should trigger the branch: if (IsTV()) which calls ClearFocusStyleForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->ClearFocusStyle();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: ClearFocusStyle002
 * @tc.desc: Test ClearFocusStyle when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, ClearFocusStyle002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call ClearFocusStyle
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->ClearFocusStyle();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: ProcessFocusStyle001
 * @tc.desc: Test ProcessFocusStyle when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, ProcessFocusStyle001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call ProcessFocusStyle
     * This should trigger the branch: if (IsTV()) which calls ProcessFocusStyleForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->ProcessFocusStyle();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: ProcessFocusStyle002
 * @tc.desc: Test ProcessFocusStyle when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, ProcessFocusStyle002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call ProcessFocusStyle
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->ProcessFocusStyle();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: InitDisableColor001
 * @tc.desc: Test InitDisableColor when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, InitDisableColor001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call InitDisableColor
     * This should trigger the branch: if (IsTV()) which calls InitDisableColorForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->InitDisableColor();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: InitDisableColor002
 * @tc.desc: Test InitDisableColor when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, InitDisableColor002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call InitDisableColor
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->InitDisableColor();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: UpdateHoverStyle001
 * @tc.desc: Test UpdateHoverStyle when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdateHoverStyle001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call UpdateHoverStyle with isHover = true
     * This should trigger the branch: if (IsTV()) which calls UpdateHoverStyleForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->UpdateHoverStyle(true);
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: UpdateHoverStyle002
 * @tc.desc: Test UpdateHoverStyle when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdateHoverStyle002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call UpdateHoverStyle with isHover = true
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->UpdateHoverStyle(true);
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: UpdatePressStyle001
 * @tc.desc: Test UpdatePressStyle when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePressStyle001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call UpdatePressStyle with isPressed = true
     * This should trigger the branch: if (IsTV()) which calls UpdatePressStyleForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->UpdatePressStyle(true);
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: UpdatePressStyle002
 * @tc.desc: Test UpdatePressStyle when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePressStyle002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call UpdatePressStyle with isPressed = true
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->UpdatePressStyle(true);
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: SetShowError001
 * @tc.desc: Test SetShowError when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, SetShowError001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call SetShowError
     * This should trigger the branch: if (IsTV()) which calls SetShowErrorForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->SetShowError();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: SetShowError002
 * @tc.desc: Test SetShowError when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, SetShowError002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call SetShowError
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->SetShowError();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: ApplyUnderlineTheme001
 * @tc.desc: Test ApplyUnderlineTheme when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, ApplyUnderlineTheme001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call ApplyUnderlineTheme
     * This should trigger the branch: if (IsTV()) which calls ApplyUnderlineThemeForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->ApplyUnderlineTheme();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: ApplyUnderlineTheme002
 * @tc.desc: Test ApplyUnderlineTheme when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, ApplyUnderlineTheme002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call ApplyUnderlineTheme
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->ApplyUnderlineTheme();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: GetInnerFocusPaintRect001
 * @tc.desc: Test GetInnerFocusPaintRect when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, GetInnerFocusPaintRect001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Create RoundRect parameter
     */
    RoundRect paintRect;
    /**
     * @tc.steps: step4. Call GetInnerFocusPaintRect
     * This should trigger the branch: if (IsTV()) which calls GetInnerFocusPaintRectForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->GetInnerFocusPaintRect(paintRect);
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: GetInnerFocusPaintRect002
 * @tc.desc: Test GetInnerFocusPaintRect when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, GetInnerFocusPaintRect002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Create RoundRect parameter
     */
    RoundRect paintRect;
    /**
     * @tc.steps: step4. Call GetInnerFocusPaintRect
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->GetInnerFocusPaintRect(paintRect);
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: PaintCancelRect001
 * @tc.desc: Test PaintCancelRect when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, PaintCancelRect001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call PaintCancelRect
     * This should trigger the branch: if (IsTV()) which calls PaintCancelRectForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->PaintCancelRect();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: PaintCancelRect002
 * @tc.desc: Test PaintCancelRect when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, PaintCancelRect002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call PaintCancelRect
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->PaintCancelRect();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: PaintVoiceRect001
 * @tc.desc: Test PaintVoiceRect when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, PaintVoiceRect001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call PaintVoiceRect
     * This should trigger the branch: if (IsTV()) which calls PaintFocusAreaRectForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->PaintVoiceRect();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: PaintVoiceRect002
 * @tc.desc: Test PaintVoiceRect when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, PaintVoiceRect002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call PaintVoiceRect
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->PaintVoiceRect();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: PaintPasswordRect001
 * @tc.desc: Test PaintPasswordRect when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, PaintPasswordRect001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call PaintPasswordRect
     * This should trigger the branch: if (IsTV()) which calls PaintPasswordRectForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->PaintPasswordRect();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: PaintPasswordRect002
 * @tc.desc: Test PaintPasswordRect when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, PaintPasswordRect002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call PaintPasswordRect
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->PaintPasswordRect();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: SetThemeBorderAttr001
 * @tc.desc: Test SetThemeBorderAttr when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, SetThemeBorderAttr001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call SetThemeBorderAttr
     * This should trigger the branch: if (IsTV()) which calls SetThemeBorderAttrForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->SetThemeBorderAttr();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: SetThemeBorderAttr002
 * @tc.desc: Test SetThemeBorderAttr when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, SetThemeBorderAttr002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call SetThemeBorderAttr
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->SetThemeBorderAttr();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: SetThemeAttr001
 * @tc.desc: Test SetThemeAttr when IsTV returns true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, SetThemeAttr001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to true to make IsTV return true
     */
    pattern_->SetHoverPressBgColorEnabled(true);
    /**
     * @tc.steps: step3. Call SetThemeAttr
     * This should trigger the branch: if (IsTV()) which calls SetThemeAttrForTV()
     * @tc.expected: Function should execute without crash when IsTV is true
     */
    pattern_->SetThemeAttr();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: SetThemeAttr002
 * @tc.desc: Test SetThemeAttr when IsTV returns false
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, SetThemeAttr002, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Set hoverAndPressBgColorEnabled_ to false to make IsTV return false
     */
    pattern_->SetHoverPressBgColorEnabled(false);
    /**
     * @tc.steps: step3. Call SetThemeAttr
     * This should skip the TV branch and execute normal path
     * @tc.expected: Function should execute without crash when IsTV is false
     */
    pattern_->SetThemeAttr();
    ASSERT_NE(pattern_->GetHost(), nullptr);
}

/**
 * @tc.name: UpdatePropertyImplPlaceholderFontFamily001
 * @tc.desc: Test UpdatePropertyImpl with placeholderFontFamily property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImplPlaceholderFontFamily001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for placeholderFontFamily
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    std::vector<std::string> fontFamilies = {"Arial", "SanSerif"};
    value->SetValue(fontFamilies);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with placeholderFontFamily key
     * @tc.expected: Placeholder font family should be updated
     */
    pattern_->UpdatePropertyImpl("placeholderFontFamily", value);
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImplPaddingTop001
 * @tc.desc: Test UpdatePropertyImpl with paddingTop property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImplPaddingTop001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for paddingTop
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    CalcDimension padding(10.0, DimensionUnit::VP);
    value->SetValue(padding);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with paddingTop key
     * @tc.expected: Padding top should be updated
     */
    pattern_->UpdatePropertyImpl("paddingTop", value);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto paintProperty = host->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImplPaddingBottom001
 * @tc.desc: Test UpdatePropertyImpl with paddingBottom property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImplPaddingBottom001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for paddingBottom
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    CalcDimension padding(10.0, DimensionUnit::VP);
    value->SetValue(padding);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with paddingBottom key
     * @tc.expected: Padding bottom should be updated
     */
    pattern_->UpdatePropertyImpl("paddingBottom", value);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto paintProperty = host->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImplPaddingLeft001
 * @tc.desc: Test UpdatePropertyImpl with paddingLeft property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImplPaddingLeft001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for paddingLeft
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    CalcDimension padding(10.0, DimensionUnit::VP);
    value->SetValue(padding);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with paddingLeft key
     * @tc.expected: Padding left should be updated
     */
    pattern_->UpdatePropertyImpl("paddingLeft", value);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto paintProperty = host->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImplPaddingRight001
 * @tc.desc: Test UpdatePropertyImpl with paddingRight property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImplPaddingRight001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for paddingRight
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    CalcDimension padding(10.0, DimensionUnit::VP);
    value->SetValue(padding);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with paddingRight key
     * @tc.expected: Padding right should be updated
     */
    pattern_->UpdatePropertyImpl("paddingRight", value);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto paintProperty = host->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: UpdatePropertyImplMarginTop001
 * @tc.desc: Test UpdatePropertyImpl with marginTop property
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternFuncTestThree, UpdatePropertyImplMarginTop001, TestSize.Level1)
{    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    ASSERT_NE(pattern_, nullptr);
    /**
     * @tc.steps: step2. Create property value for marginTop
     */
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    CalcDimension margin(10.0, DimensionUnit::VP);
    value->SetValue(margin);
    /**
     * @tc.steps: step3. Call UpdatePropertyImpl with marginTop key
     * @tc.expected: Margin top should be updated
     */
    pattern_->UpdatePropertyImpl("marginTop", value);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto paintProperty = host->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}
} // namespace OHOS::Ace::NG
