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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldModelStaticTest : public TextInputBases {
public:
};

/**
 * @tc.name: TextFieldModelStatic_CreateTextInputNode_Normal
 * @tc.desc: Test CreateTextInputNode with normal parameters
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTest, TextFieldModelStatic_CreateTextInputNode_Normal, TestSize.Level1)
{
    int32_t nodeId = 100;
    std::optional<std::u16string> placeholder = std::make_optional<std::u16string>(u"Enter text");
    std::optional<std::u16string> value = std::make_optional<std::u16string>(u"Default value");
    auto frameNode = TextFieldModelNG::CreateTextInputNode(nodeId, placeholder, value);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TEXTINPUT_ETS_TAG);
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(textFieldLayoutProperty, nullptr);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderValue(), u"Enter text");
    EXPECT_EQ(textFieldLayoutProperty->GetMaxLinesValue(0), 1);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderMaxLinesValue(0), 1);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    EXPECT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->GetTextInputFlag());
    EXPECT_NE(pattern->GetTextFieldController(), nullptr);

    auto controller = pattern->GetTextFieldController();
    auto textFieldController = pattern->GetTextFieldController();
    int32_t caretIndex = textFieldController->GetCaretIndex();
    EXPECT_EQ(caretIndex, 13);
}

/**
 * @tc.name: TextFieldModelStatic_CreateTextInputNode_EmptyParams
 * @tc.desc: Test CreateTextInputNode with empty parameters
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTest, TextFieldModelStatic_CreateTextInputNode_EmptyParams, TestSize.Level1)
{
    int32_t nodeId = 101;
    std::optional<std::u16string> placeholder = std::nullopt;
    std::optional<std::u16string> value = std::nullopt;

    auto frameNode = TextFieldModelNG::CreateTextInputNode(nodeId, placeholder, value);
    
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TEXTINPUT_ETS_TAG);
    
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(textFieldLayoutProperty, nullptr);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderValue(), u"");
    EXPECT_EQ(textFieldLayoutProperty->GetMaxLinesValue(0), 1);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderMaxLinesValue(0), 1);
    
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    EXPECT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->GetTextInputFlag());
    EXPECT_NE(pattern->GetTextFieldController(), nullptr);
}

/**
 * @tc.name: TextFieldModelStatic_CreateTextInputNode_EmptyPlaceholder
 * @tc.desc: Test CreateTextInputNode with empty placeholder
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTest, TextFieldModelStatic_CreateTextInputNode_EmptyPlaceholder, TestSize.Level1)
{
    int32_t nodeId = 102;
    std::optional<std::u16string> placeholder = std::make_optional<std::u16string>(u"");
    std::optional<std::u16string> value = std::make_optional<std::u16string>(u"Default value");

    auto frameNode = TextFieldModelNG::CreateTextInputNode(nodeId, placeholder, value);
    
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TEXTINPUT_ETS_TAG);
    
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(textFieldLayoutProperty, nullptr);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderValue(), u"");
    EXPECT_EQ(textFieldLayoutProperty->GetMaxLinesValue(0), 1);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderMaxLinesValue(0), 1);
    
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    EXPECT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->GetTextInputFlag());
    EXPECT_NE(pattern->GetTextFieldController(), nullptr);
}

/**
 * @tc.name: TextFieldModelStatic_CreateTextInputNode_EmptyValue
 * @tc.desc: Test CreateTextInputNode with empty value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTest, TextFieldModelStatic_CreateTextInputNode_EmptyValue, TestSize.Level1)
{
    int32_t nodeId = 103;
    std::optional<std::u16string> placeholder = std::make_optional<std::u16string>(u"Enter text");
    std::optional<std::u16string> value = std::make_optional<std::u16string>(u"");

    auto frameNode = TextFieldModelNG::CreateTextInputNode(nodeId, placeholder, value);
    
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TEXTINPUT_ETS_TAG);
    
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(textFieldLayoutProperty, nullptr);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderValue(), u"Enter text");
    EXPECT_EQ(textFieldLayoutProperty->GetMaxLinesValue(0), 1);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderMaxLinesValue(0), 1);
    
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    EXPECT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->GetTextInputFlag());
    EXPECT_NE(pattern->GetTextFieldController(), nullptr);
}

/**
 * @tc.name: TextFieldModelStatic_CreateTextAreaNode_Normal
 * @tc.desc: Test CreateTextAreaNode with normal parameters
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTest, TextFieldModelStatic_CreateTextAreaNode_Normal, TestSize.Level1)
{
    int32_t nodeId = 1001;
    std::optional<std::u16string> placeholder = std::make_optional<std::u16string>(u"Enter text here");
    std::optional<std::u16string> value = std::make_optional<std::u16string>(u"Default value");

    auto frameNode = TextFieldModelNG::CreateTextAreaNode(nodeId, placeholder, value);
    
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TEXTAREA_ETS_TAG);
    
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(textFieldLayoutProperty, nullptr);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderValue(), u"Enter text here");
    EXPECT_TRUE(textFieldLayoutProperty->GetPlaceholderMaxLinesValue(0) == Infinity<uint32_t>());
    
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    pattern->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    pattern->GetTextFieldController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    EXPECT_NE(pattern, nullptr);
    EXPECT_NE(pattern->GetTextFieldController(), nullptr);
    
    auto controller = pattern->GetTextFieldController();
    auto textFieldController = pattern->GetTextFieldController();
    int32_t caretIndex = textFieldController->GetCaretIndex();
    EXPECT_EQ(caretIndex, 13);
}

/**
 * @tc.name: TextFieldModelStatic_CreateTextAreaNode_EmptyPlaceholder
 * @tc.desc: Test CreateTextAreaNode with empty placeholder
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTest, TextFieldModelStatic_CreateTextAreaNode_EmptyPlaceholder, TestSize.Level1)
{
    int32_t nodeId = 1002;
    std::optional<std::u16string> placeholder = std::make_optional<std::u16string>(u"");
    std::optional<std::u16string> value = std::make_optional<std::u16string>(u"Default value");

    auto frameNode = TextFieldModelNG::CreateTextAreaNode(nodeId, placeholder, value);
    
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TEXTAREA_ETS_TAG);
    
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(textFieldLayoutProperty, nullptr);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderValue(), u"");
    EXPECT_TRUE(textFieldLayoutProperty->GetPlaceholderMaxLinesValue(0) == Infinity<uint32_t>());
}

/**
 * @tc.name: TextFieldModelStatic_CreateTextAreaNode_EmptyValue
 * @tc.desc: Test CreateTextAreaNode with empty value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTest, TextFieldModelStatic_CreateTextAreaNode_EmptyValue, TestSize.Level1)
{
    int32_t nodeId = 1003;
    std::optional<std::u16string> placeholder = std::make_optional<std::u16string>(u"Enter text here");
    std::optional<std::u16string> value = std::make_optional<std::u16string>(u"");

    auto frameNode = TextFieldModelNG::CreateTextAreaNode(nodeId, placeholder, value);
    
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TEXTAREA_ETS_TAG);
    
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(textFieldLayoutProperty, nullptr);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderValue(), u"Enter text here");
    EXPECT_TRUE(textFieldLayoutProperty->GetPlaceholderMaxLinesValue(0) == Infinity<uint32_t>());
}

/**
 * @tc.name: TextFieldModelStatic_CreateTextAreaNode_NoPlaceholder
 * @tc.desc: Test CreateTextAreaNode without placeholder
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTest, TextFieldModelStatic_CreateTextAreaNode_NoPlaceholder, TestSize.Level1)
{
    int32_t nodeId = 1004;
    std::optional<std::u16string> placeholder = std::nullopt;
    std::optional<std::u16string> value = std::make_optional<std::u16string>(u"Default value");

    auto frameNode = TextFieldModelNG::CreateTextAreaNode(nodeId, placeholder, value);
    
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TEXTAREA_ETS_TAG);
    
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(textFieldLayoutProperty, nullptr);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderValue(), u"");
    EXPECT_TRUE(textFieldLayoutProperty->GetPlaceholderMaxLinesValue(0) == Infinity<uint32_t>());
}

/**
 * @tc.name: TextFieldModelStatic_CreateTextAreaNodeTest
 * @tc.desc: Test CreateTextAreaNode without any optional parameters
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTest, TextFieldModelStatic_CreateTextAreaNodeTest, TestSize.Level1)
{
    int32_t nodeId = 1006;
    std::optional<std::u16string> placeholder = std::nullopt;
    std::optional<std::u16string> value = std::nullopt;

    auto frameNode = TextFieldModelNG::CreateTextAreaNode(nodeId, placeholder, value);
    
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TEXTAREA_ETS_TAG);
    
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(textFieldLayoutProperty, nullptr);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderValue(), u"");
    EXPECT_TRUE(textFieldLayoutProperty->GetPlaceholderMaxLinesValue(0) == Infinity<uint32_t>());
}

/**
 * @tc.name: TextFieldModelStatic_CreateTextAreaNode_NoValue
 * @tc.desc: Test CreateTextAreaNode without value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTest, TextFieldModelStatic_CreateTextAreaNode_NoValue, TestSize.Level1)
{
    int32_t nodeId = 1005;
    std::optional<std::u16string> placeholder = std::make_optional<std::u16string>(u"Enter text here");
    std::optional<std::u16string> value = std::nullopt;

    auto frameNode = TextFieldModelNG::CreateTextAreaNode(nodeId, placeholder, value);
    
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TEXTAREA_ETS_TAG);
    
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(textFieldLayoutProperty, nullptr);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderValue(), u"Enter text here");
    EXPECT_TRUE(textFieldLayoutProperty->GetPlaceholderMaxLinesValue(0) == Infinity<uint32_t>());
}

/**
 * @tc.name: TextFieldModelStatic_CreateTextAreaNode_NoParams
 * @tc.desc: Test CreateTextAreaNode without any optional parameters
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTest, TextFieldModelStatic_CreateTextAreaNode_NoParams, TestSize.Level1)
{
    int32_t nodeId = 1006;
    std::optional<std::u16string> placeholder = std::nullopt;
    std::optional<std::u16string> value = std::nullopt;

    auto frameNode = TextFieldModelNG::CreateTextAreaNode(nodeId, placeholder, value);
    
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TEXTAREA_ETS_TAG);
    
    auto textFieldLayoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(textFieldLayoutProperty, nullptr);
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderValue(), u"");
    EXPECT_TRUE(textFieldLayoutProperty->GetPlaceholderMaxLinesValue(0) == Infinity<uint32_t>());
}

/**
 * @tc.name: TextFieldModelStatic_SetBackgroundColor_NullFrameNode
 * @tc.desc: Test SetBackgroundColor with null frame node
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldModelStaticTest, TextFieldModelStatic_SetBackgroundColor_NullFrameNode, TestSize.Level1)
{
    // Test with null frame node, should not crash
    TextFieldModelNG::SetBackgroundColor(nullptr, Color::RED);
    EXPECT_TRUE(true); // If we reach here, no crash occurred
}

} // namespace OHOS::Ace::NG
