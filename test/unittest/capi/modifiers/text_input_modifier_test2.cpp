/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace Converter;

namespace GeneratedModifier {
    const GENERATED_ArkUITextInputControllerAccessor* GetTextInputControllerAccessor();
    const GENERATED_ArkUISubmitEventAccessor* GetSubmitEventAccessor();
} // namespace GeneratedModifier

namespace Converter {
    template<>
    PreviewText Convert(const Ark_PreviewText& src)
    {
        PreviewText previewText = {.value = Convert<std::u16string>(src.value),
                                   .offset = Convert<int32_t>(src.offset)};
        return previewText;
    }
} // namespace Converter

namespace {
    Ark_EnterKeyType g_EventTestKey{};
}

class TextInputModifierTest2 : public ModifierTestBase<GENERATED_ArkUITextInputModifier,
                                  &GENERATED_ArkUINodeModifiers::getTextInputModifier, GENERATED_ARKUI_TEXT_INPUT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<TextFieldTheme>();
    }
};

/**
 * @tc.name: setOnChangeTest
 * @tc.desc: Check the functionality of setOnChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setOnChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);

    std::u16string expectedText = u"test_text";
    PreviewText expectedPreviewText = { .offset = 1234, .value = u"test_preview_text" };
    
    static std::u16string resultText = u"";
    static std::u16string resultPreviewText = u"";
    static int32_t resultOffset = 0;

    auto arkCallback = [](Ark_Int32 nodeId, const Ark_String value, const Opt_PreviewText previewText) {
        auto convPreviewText = Converter::OptConvert<PreviewText>(previewText).value_or(PreviewText{});
        resultOffset = convPreviewText.offset;
        resultPreviewText.append(convPreviewText.value);
        resultText.append(Converter::OptConvert<std::u16string>(value).value_or(u""));
    };

    auto onChange = Converter::ArkValue<EditableTextOnChangeCallback>(arkCallback, frameNode->GetId());

    modifier_->setOnChange(node_, &onChange);
    textFieldEventHub->FireOnChange({expectedText, expectedPreviewText});
    EXPECT_EQ(resultText, expectedText);
    EXPECT_EQ(resultPreviewText, expectedPreviewText.value);
    EXPECT_EQ(resultOffset, expectedPreviewText.offset);
}

/**
 * @tc.name: setOnPasteTest
 * @tc.desc: Check the functionality of setOnPaste.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setOnPasteTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnPaste, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto textFieldEventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(textFieldEventHub, nullptr);

    std::u16string expectedText = u"test_text";
    static std::u16string resultText = u"";

    auto arkCallback = [](const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event) {
        resultText = Converter::OptConvert<std::u16string>(content).value_or(u"");
    };

    auto onPaste = Converter::ArkValue<OnPasteCallback>(arkCallback, frameNode->GetId());
    modifier_->setOnPaste(node_, &onPaste);
    textFieldEventHub->FireOnPaste(expectedText);
    EXPECT_EQ(resultText, expectedText);
}

/*
 * @tc.name: setCustomKeyboard_CustomNodeBuilder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setCustomKeyboard_CustomNodeBuilder, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCustomKeyboard, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    int callsCount = 0;
    CustomNodeBuilderTestHelper<TextInputModifierTest2> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    modifier_->setCustomKeyboard(node_, &builder, nullptr);

    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_TRUE(textFieldPattern->HasCustomKeyboard());
    EXPECT_TRUE(textFieldPattern->RequestCustomKeyboard());
    EXPECT_EQ(builderHelper.GetCallsCount(), ++callsCount);
}

/*
 * @tc.name: setCustomKeyboard_CustomNodeBuilder_KeyboardOptions
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setCustomKeyboard_CustomNodeBuilder_KeyboardOptions, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCustomKeyboard, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    KeyboardOptions keyboardOptions = {.supportAvoidance = true};
    auto optKeyboardOptions = Converter::ArkValue<Opt_KeyboardOptions>(keyboardOptions);

    int callsCount = 0;
    CustomNodeBuilderTestHelper<TextInputModifierTest2> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    modifier_->setCustomKeyboard(node_, &builder, &optKeyboardOptions);

    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_TRUE(textFieldPattern->HasCustomKeyboard());
    EXPECT_TRUE(textFieldPattern->RequestCustomKeyboard());
    EXPECT_EQ(builderHelper.GetCallsCount(), ++callsCount);
}

/**
 * @tc.name: OnSubmitTest
 * @tc.desc: setOnSubmit test
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, OnSubmitTest, TestSize.Level1)
{
    static const int expectedResId = 123;
    static const std::u16string TEST_VALUE(u"string text");
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto onSubmitFunc = [](Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, const Ark_SubmitEvent event) {
        auto peer = reinterpret_cast<SubmitEventPeer*>(event.ptr);
        ASSERT_NE(peer, nullptr);
        auto submitEventInfo = peer->GetEventInfo();
        ASSERT_NE(submitEventInfo, nullptr);
        EXPECT_EQ(submitEventInfo->GetText(), TEST_VALUE);
        GeneratedModifier::GetSubmitEventAccessor()->destroyPeer(peer);
        EXPECT_EQ(resourceId, expectedResId);
        g_EventTestKey = enterKeyType;
    };

    auto func = Converter::ArkValue<OnSubmitCallback>(onSubmitFunc, expectedResId);
    modifier_->setOnSubmit(node_, &func);
    TextFieldCommonEvent event;
    event.SetText(TEST_VALUE);
    eventHub->FireOnSubmit(111, event);
    EXPECT_EQ(g_EventTestKey, -1);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEXT, event);
    EXPECT_EQ(g_EventTestKey, 5);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_GO, event);
    EXPECT_EQ(g_EventTestKey, 2);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_SEARCH, event);
    EXPECT_EQ(g_EventTestKey, 3);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_SEND, event);
    EXPECT_EQ(g_EventTestKey, 4);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEXT, event);
    EXPECT_EQ(g_EventTestKey, 5);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_DONE, event);
    EXPECT_EQ(g_EventTestKey, 6);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_PREVIOUS, event);
    EXPECT_EQ(g_EventTestKey, 7);
    eventHub->FireOnSubmit(ARK_ENTER_KEY_TYPE_NEW_LINE, event);
    EXPECT_EQ(g_EventTestKey, 8);
}
} // namespace OHOS::Ace::NG
