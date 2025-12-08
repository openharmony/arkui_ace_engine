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
#include <gtest/gtest.h>

#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"
#include "core/interfaces/native/implementation/submit_event_peer.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace Converter;

namespace GeneratedModifier {
    const GENERATED_ArkUITextInputControllerAccessor* GetTextInputControllerAccessor();
    const GENERATED_ArkUISubmitEventAccessor* GetSubmitEventAccessor();
} // namespace GeneratedModifier

namespace {
Ark_EnterKeyType g_EventTestKey {};
const std::string TEST_CONTENT_ONE = "ContentTestOne";
const std::string TEST_CONTENT_TWO = "ContentTestTwo";

const auto ATTRIBUTE_AUTOCAPITALIZATION_MODE_NAME = "autocapitalizationMode";
const auto ATTRIBUTE_AUTOCAPITALIZATION_MODE_DEFAULT_VALUE = "AutoCapitalizationMode.NONE";

std::vector<std::tuple<std::string, Opt_AutoCapitalizationMode, std::string>>
    testFixtureEnumAutoCapitalizationModeTestPlan = {
        { "AutoCapitalizationMode.NONE", Converter::ArkValue<Opt_AutoCapitalizationMode>(AutoCapitalizationMode::NONE),
            "AutoCapitalizationMode.NONE" },
        { "AutoCapitalizationMode.WORDS",
            Converter::ArkValue<Opt_AutoCapitalizationMode>(AutoCapitalizationMode::WORDS),
            "AutoCapitalizationMode.WORDS" },
        { "AutoCapitalizationMode.SENTENCES",
            Converter::ArkValue<Opt_AutoCapitalizationMode>(AutoCapitalizationMode::SENTENCES),
            "AutoCapitalizationMode.SENTENCES" },
        { "AutoCapitalizationMode.ALL_CHARACTERS",
            Converter::ArkValue<Opt_AutoCapitalizationMode>(AutoCapitalizationMode::ALL_CHARACTERS),
            "AutoCapitalizationMode.ALL_CHARACTERS" },
        { "AutoCapitalizationMode.INVALID",
            Converter::ArkValue<Opt_AutoCapitalizationMode>(Converter::INVALID_ENUM_VAL<Ark_AutoCapitalizationMode>),
            ATTRIBUTE_AUTOCAPITALIZATION_MODE_DEFAULT_VALUE },
    };
} // namespace

class TextInputModifierTest2 : public ModifierTestBase<GENERATED_ArkUITextInputModifier,
                                  &GENERATED_ArkUINodeModifiers::getTextInputModifier, GENERATED_ARKUI_TEXT_INPUT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<TextFieldTheme>();
    }

    std::vector<MenuItemParam> GetMenuItemParams()
    {
        std::vector<MenuItemParam> params;
        MenuOptionsParam menuOptionItemOne;
        menuOptionItemOne.content = TEST_CONTENT_ONE;
        menuOptionItemOne.action = [](const std::string&) {};
        MenuOptionsParam menuOptionItemTwo;
        menuOptionItemTwo.content = TEST_CONTENT_TWO;
        menuOptionItemTwo.action = [](const std::string&) {};
        MenuItemParam param1;
        param1.menuOptionsParam = menuOptionItemOne;
        MenuItemParam param2;
        param2.menuOptionsParam = menuOptionItemTwo;
        params.push_back(param1);
        params.push_back(param2);
        return params;
    }
};

/*
 * @tc.name: setAutoCapitalizationModeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setAutoCapitalizationModeTest, TestSize.Level1)
{
    ASSERT_TRUE(modifier_->setAutoCapitalizationMode);
    auto jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTOCAPITALIZATION_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_AUTOCAPITALIZATION_MODE_DEFAULT_VALUE) << "Default value is: " << resultStr
                                        << ", method: setAutoCapitalizationMode, attribute: keyboardAppearance";
    auto checkValue = [this](const std::string& input, const std::string& expectedStr,
                          const Opt_AutoCapitalizationMode& value) {
        modifier_->setAutoCapitalizationMode(node_, &value);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTOCAPITALIZATION_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input
                                        << ", method: setAutoCapitalizationMode, attribute: keyboardAppearance";
    };
    for (auto& [input, value, expected] : testFixtureEnumAutoCapitalizationModeTestPlan) {
        checkValue(input, expected, value);
    }
}

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

    auto arkCallback = [](Ark_Int32 nodeId, const Ark_String value, const Opt_PreviewText previewText,
        Opt_TextChangeOptions options) {
        auto convPreviewText = Converter::OptConvert<PreviewText>(previewText).value_or(PreviewText{});
        resultOffset = convPreviewText.offset;
        resultPreviewText.append(convPreviewText.value);
        resultText.append(Converter::OptConvert<std::u16string>(value).value_or(u""));
    };

    auto onChange = Converter::ArkCallback<Opt_EditableTextOnChangeCallback>(arkCallback);
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

    auto onPaste = Converter::ArkCallback<Opt_OnPasteCallback>(arkCallback, frameNode->GetId());
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
    auto builder = Converter::ArkValue<Opt_CustomNodeBuilder>(builderHelper.GetBuilder());
    modifier_->setCustomKeyboard(node_, &builder, nullptr);

    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_TRUE(textFieldPattern->HasCustomKeyboard());
    EXPECT_TRUE(textFieldPattern->RequestCustomKeyboard());
    EXPECT_EQ(builderHelper.GetCallsCountAsync(), ++callsCount);
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
    auto builder = Converter::ArkValue<Opt_CustomNodeBuilder>(builderHelper.GetBuilder());
    modifier_->setCustomKeyboard(node_, &builder, &optKeyboardOptions);

    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_TRUE(textFieldPattern->HasCustomKeyboard());
    EXPECT_TRUE(textFieldPattern->RequestCustomKeyboard());
    EXPECT_EQ(builderHelper.GetCallsCountAsync(), ++callsCount);
}

/**
 * @tc.name: OnSubmitTest
 * @tc.desc: setOnSubmit test
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, OnSubmitTest, TestSize.Level1)
{
    static const int expectedResId = 123;
    static const std::u16string testValue(u"string text");
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<NG::TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto onSubmitFunc = [](
        Ark_VMContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, const Ark_SubmitEvent event
    ) {
        auto peer = event;
        ASSERT_NE(peer, nullptr);
        auto submitEventInfo = peer->GetEventInfo();
        ASSERT_NE(submitEventInfo, nullptr);
        EXPECT_EQ(submitEventInfo->GetText(), testValue);
        GeneratedModifier::GetSubmitEventAccessor()->destroyPeer(peer);
        EXPECT_EQ(resourceId, expectedResId);
        g_EventTestKey = enterKeyType;
    };

    auto func = Converter::ArkCallback<Opt_OnSubmitCallback>(onSubmitFunc);
    modifier_->setOnSubmit(node_, &func);
    TextFieldCommonEvent event;
    event.SetText(testValue);
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

#ifdef WRONG_GEN
/**
 * @tc.name: setEditMenuOptionsTest
 * @tc.desc: setEditMenuOptions test
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setEditMenuOptionsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEditMenuOptions, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t testID = 323;
    struct CheckEvent {
        int32_t resourceId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testOnCreateMenuCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Array_TextMenuItem menuItems, const Callback_Array_TextMenuItem_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        CallbackHelper(continuation).Invoke(menuItems);
    };
    auto arkCreateCallback = Converter::ArkCallback<Opt_OnCreateMenuCallback>(testOnCreateMenuCallback);

    auto testOnMenuItemClickCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_TextMenuItem menuItem, const Ark_TextRange range, const Callback_Boolean_Void continuation) {
        auto item = Converter::OptConvert<MenuOptionsParam>(menuItem);
        ASSERT_TRUE(item.has_value());
        ASSERT_TRUE(item->content.has_value());
        CallbackHelper(continuation).Invoke(Converter::ArkValue<Ark_Boolean>(*item->content == TEST_CONTENT_ONE));
    };
    auto arkClickCallback = Converter::ArkCallback<Opt_OnMenuItemClickCallback>(testOnMenuItemClickCallback);

    Ark_EditMenuOptions options {
        .onCreateMenu = arkCreateCallback,
        .onMenuItemClick = arkClickCallback
    };
    auto optOptions = Converter::ArkValue<Opt_EditMenuOptions>(options);

    SelectOverlayInfo selectOverlayInfo;
    auto params = GetMenuItemParams();
    FriendClassAccessor::OnUpdateOnCreateMenuCallback(selectOverlayInfo, pattern);
    EXPECT_TRUE(selectOverlayInfo.onCreateCallback.onCreateMenuCallback == nullptr);
    modifier_->setEditMenuOptions(node_, &optOptions);
    FriendClassAccessor::OnUpdateOnCreateMenuCallback(selectOverlayInfo, pattern);
    ASSERT_NE(selectOverlayInfo.onCreateCallback.onCreateMenuCallback, nullptr);
    selectOverlayInfo.onCreateCallback.onCreateMenuCallback(params);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, testID);

    ASSERT_NE(selectOverlayInfo.onCreateCallback.onMenuItemClick, nullptr);
    EXPECT_TRUE(selectOverlayInfo.onCreateCallback.onMenuItemClick(params[0]));
    EXPECT_FALSE(selectOverlayInfo.onCreateCallback.onMenuItemClick(params[1]));
}
#endif
} // namespace OHOS::Ace::NG
