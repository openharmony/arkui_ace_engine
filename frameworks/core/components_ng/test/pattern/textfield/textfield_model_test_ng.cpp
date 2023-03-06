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
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "textfield_test_ng_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class TextFieldControllerTestNG : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
};

void TextFieldControllerTestNG::SetUp() {}

void TextFieldControllerTestNG::TearDown() {}

/**
 * @tc.name: CaretPosition001
 * @tc.desc: test CaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTestNG, CaretPosition001, TestSize.Level1)
{
    int32_t caretPositionGlobal = 10;
    int32_t caretPositionCallback = 0;
    auto TextFieldNode = TextFieldTestNgUtils::CreatTextFieldNode();
    if (!TextFieldNode) {
        GTEST_LOG_(INFO) << "create textfield node failed!";
        return;
    }
    auto pattern = TextFieldNode->GetPattern<TextFieldPattern>();
    if (!pattern) {
        GTEST_LOG_(INFO) << "Get TextFieldPattern failed!";
        return;
    }
    auto textFieldController = AceType::MakeRefPtr<TextFieldController>();
    if (!textFieldController) {
        GTEST_LOG_(INFO) << "make textfield Controller failed!";
        return;
    }
    pattern->InitEditingValueText("caretPosition");
    textFieldController->SetPattern(pattern);
    textFieldController->SetCaretPosition([&caretPositionCallback] (const int32_t caretPosition) {
        caretPositionCallback = caretPosition;
    });
    textFieldController->CaretPosition(caretPositionGlobal);
    EXPECT_EQ(pattern->GetTextEditingValue().caretPosition, caretPositionGlobal);
    EXPECT_EQ(caretPositionCallback, caretPositionGlobal);
}

/**
 * @tc.name: EscapeString001
 * @tc.desc: test EscapeString success
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTestNG, EscapeString001, TestSize.Level1)
{
    std::string result;
    EXPECT_TRUE(TextFieldControllerBase::EscapeString("textfield", result));
    EXPECT_EQ(result, "textfield");
    EXPECT_TRUE(TextFieldControllerBase::EscapeString("_tes\\t", result));
    EXPECT_EQ(result, "textfield_tes\t");
}

/**
 * @tc.name: EscapeString002
 * @tc.desc: test EscapeString failed
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldControllerTestNG, EscapeString002, TestSize.Level2)
{
    std::string result;
    EXPECT_FALSE(TextFieldControllerBase::EscapeString("textfield\\", result));
    EXPECT_EQ(result, "textfield");
    EXPECT_FALSE(TextFieldControllerBase::EscapeString("_test\\_", result));
    EXPECT_EQ(result, "textfield_test");
}

class TextFieldModelTestNG : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    RefPtr<TextFieldLayoutProperty> CreateNodeAndGetLayoutProperty(TextFieldModelNG& textFieldModelInstance);
    RefPtr<TextFieldPaintProperty> CreateNodeAndGetPaintProperty(TextFieldModelNG& textFieldModelInstance);
};

void TextFieldModelTestNG::SetUp() {}

void TextFieldModelTestNG::TearDown()
{
    ViewStackProcessor::GetInstance()->Finish();
}

RefPtr<TextFieldLayoutProperty> TextFieldModelTestNG::CreateNodeAndGetLayoutProperty(
    TextFieldModelNG& textFieldModelInstance)
{
    textFieldModelInstance.CreateNode(PLACEHOLDER, EMPTY_TEXT_VALUE, false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    if (!frameNode) {
        GTEST_LOG_(INFO) << "create textfield node failed!";
        return nullptr;
    }
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    return layoutProperty;
}

RefPtr<TextFieldPaintProperty> TextFieldModelTestNG::CreateNodeAndGetPaintProperty(
    TextFieldModelNG& textFieldModelInstance)
{
    textFieldModelInstance.CreateNode(PLACEHOLDER, EMPTY_TEXT_VALUE, false);
    auto frameNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    if (!frameNode_) {
        GTEST_LOG_(INFO) << "create textfield node failed!";
        return nullptr;
    }
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    return paintProperty;
}

/**
 * @tc.name: CreateNode001
 * @tc.desc: Create framenode of empty value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelTestNG, CreateNode001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    textFieldModelInstance.CreateNode(PLACEHOLDER, EMPTY_TEXT_VALUE, false);
    EXPECT_TRUE(ViewStackProcessor::GetInstance()->GetMainFrameNode());
}

/**
 * @tc.name: CreateNode002
 * @tc.desc: Create framenode of value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelTestNG, CreateNode002, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    textFieldModelInstance.CreateNode(PLACEHOLDER, "value", false);
    EXPECT_TRUE(ViewStackProcessor::GetInstance()->GetMainFrameNode());
}

/**
 * @tc.name: CreateTextInput001
 * @tc.desc: Create framenode of empty value about textinput
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelTestNG, CreateTextInput001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto controller = textFieldModelInstance.CreateTextInput(PLACEHOLDER, EMPTY_TEXT_VALUE);
    EXPECT_TRUE(controller);
}

/**
 * @tc.name: CreateTextArea001
 * @tc.desc: Create framenode of empty value about textarea
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelTestNG, CreateTextArea001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto controller = textFieldModelInstance.CreateTextArea(PLACEHOLDER, EMPTY_TEXT_VALUE);
    EXPECT_TRUE(controller);
}

/**
 * @tc.name: SetType001
 * @tc.desc: Create framenode and settype
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelTestNG, SetType001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto layoutProperty = CreateNodeAndGetLayoutProperty(textFieldModelInstance);
    if (!layoutProperty) {
        EXPECT_TRUE(layoutProperty);
        return;
    }
    textFieldModelInstance.SetType(TextInputType::TEXT);
    EXPECT_EQ(layoutProperty->GetTextInputTypeValue(), TextInputType::TEXT);
    textFieldModelInstance.SetType(TextInputType::MULTILINE);
    EXPECT_EQ(layoutProperty->GetTextInputTypeValue(), TextInputType::MULTILINE);
    EXPECT_TRUE(layoutProperty->GetTypeChangedValue());
}

/**
 * @tc.name: SetPlaceholderColor001
 * @tc.desc: Create framenode and PlaceholderColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelTestNG, SetPlaceholderColor001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto layoutProperty = CreateNodeAndGetLayoutProperty(textFieldModelInstance);
    if (!layoutProperty) {
        EXPECT_TRUE(layoutProperty);
        return;
    }
    textFieldModelInstance.SetPlaceholderColor(Color::WHITE);
    EXPECT_TRUE(layoutProperty->HasPlaceholderTextColor());
}

/**
 * @tc.name: SetPlaceholderFont001
 * @tc.desc: Create framenode and SetPlaceholderFont
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelTestNG, SetPlaceholderFont001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto layoutProperty = CreateNodeAndGetLayoutProperty(textFieldModelInstance);
    if (!layoutProperty) {
        EXPECT_TRUE(layoutProperty);
        return;
    }
    std::vector<std::string> fontFamilies;
    fontFamilies.push_back("fontFamilies");
    Font font { .fontWeight = Ace::FontWeight::W200,
                .fontSize = Dimension(10.0),
                .fontStyle = Ace::FontStyle::NORMAL,
                .fontFamilies = fontFamilies };
    textFieldModelInstance.SetPlaceholderFont(font);
    EXPECT_EQ(layoutProperty->GetPlaceholderFontSize().value().Value(), 10.0);
    EXPECT_EQ(layoutProperty->GetPlaceholderItalicFontStyle().value(), Ace::FontStyle::NORMAL);
    EXPECT_EQ(layoutProperty->GetPlaceholderFontWeight().value(), Ace::FontWeight::W200);
    EXPECT_EQ(layoutProperty->GetPlaceholderFontFamily().value().size(), fontFamilies.size());
    EXPECT_TRUE(layoutProperty->GetPreferredTextLineHeightNeedToUpdate().value());
}

/**
 * @tc.name: SetEnterKeyType001
 * @tc.desc: Create framenode and SetEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelTestNG, SetEnterKeyType001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto layoutProperty = CreateNodeAndGetLayoutProperty(textFieldModelInstance);
    if (!layoutProperty) {
        EXPECT_TRUE(layoutProperty);
        return;
    }
    textFieldModelInstance.SetEnterKeyType(TextInputAction::GO);
    auto textFieldPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TextFieldPattern>();
    EXPECT_TRUE(textFieldPattern);
}

/**
 * @tc.name: SetOnEditChanged001
 * @tc.desc: Create framenode and SetOnEditChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelTestNG, SetOnEditChanged001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelInstance;
    auto layoutProperty = CreateNodeAndGetLayoutProperty(textFieldModelInstance);
    if (!layoutProperty) {
        EXPECT_TRUE(layoutProperty);
        return;
    }
    bool callback = false;
    textFieldModelInstance.SetOnEditChanged([&callback] (bool info) {
        callback = info;
    });
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextFieldEventHub>();
    if (!eventHub) {
        EXPECT_TRUE(eventHub);
        return;
    }
    eventHub->FireOnEditChanged(true);
    EXPECT_TRUE(callback);
}
} // namespace OHOS::Ace::NG
