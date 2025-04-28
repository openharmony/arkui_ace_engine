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

#include "test/unittest/capi/stubs/friend_class_accessor.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace Converter;

namespace GeneratedModifier {
    const GENERATED_ArkUITextInputControllerAccessor* GetTextInputControllerAccessor();
    const GENERATED_ArkUISubmitEventAccessor* GetSubmitEventAccessor();
} // namespace GeneratedModifier

namespace {
    Ark_EnterKeyType g_EventTestKey{};
    const std::string TEST_CONTENT_ONE = "ContentTestOne";
    const std::string TEST_CONTENT_TWO = "ContentTestTwo";
    static const auto ATTRIBUTE_TEXT_OVERFLOW_NAME = "textOverflow";
    static const auto ATTRIBUTE_TEXT_DEFAULT_VALUE = "TextOverflow.Clip";
    static const auto ATTRIBUTE_MAX_LINES_NAME = "maxLines";
    static const auto ATTRIBUTE_MAX_LINES_DEFAULT_STR_VALUE = "1";
    static const auto ATTRIBUTE_SHOW_COUNTER_NAME = "showCounter";
    static const auto ATTRIBUTE_SHOW_COUNTER_DEFAULT_VALUE =
        "{\"value\":false,\"options\":{\"thresholdPercentage\":-1,\"highlightBorder\":true}}";
    static const auto ATTRIBUTE_KEYBOARD_APPEARANCE_NAME = "keyboardAppearance";
}

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
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
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

    auto func = Converter::ArkValue<OnSubmitCallback>(onSubmitFunc, expectedResId);
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
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
        };
        CallbackHelper(continuation).Invoke(menuItems);
    };
    auto arkCreateCallback = Converter::ArkValue<
        AsyncCallback_Array_TextMenuItem_Array_TextMenuItem>(testOnCreateMenuCallback, testID);

    auto testOnMenuItemClickCallback = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_TextMenuItem menuItem, const Ark_TextRange range, const Callback_Boolean_Void continuation) {
        auto item = Converter::OptConvert<MenuOptionsParam>(menuItem);
        ASSERT_TRUE(item.has_value());
        ASSERT_TRUE(item->content.has_value());
        CallbackHelper(continuation).Invoke(Converter::ArkValue<Ark_Boolean>(*item->content == TEST_CONTENT_ONE));
    };
    auto arkClickCallback = Converter::ArkValue<
        AsyncCallback_TextMenuItem_TextRange_Boolean>(testOnMenuItemClickCallback, testID);

    Ark_EditMenuOptions options {
        .onCreateMenu = arkCreateCallback,
        .onMenuItemClick = arkClickCallback
    };

    SelectOverlayInfo selectOverlayInfo;
    auto params = GetMenuItemParams();
    FriendClassAccessor::OnUpdateOnCreateMenuCallback(selectOverlayInfo, pattern);
    EXPECT_TRUE(selectOverlayInfo.onCreateCallback.onCreateMenuCallback == nullptr);
    modifier_->setEditMenuOptions(node_, &options);
    FriendClassAccessor::OnUpdateOnCreateMenuCallback(selectOverlayInfo, pattern);
    ASSERT_NE(selectOverlayInfo.onCreateCallback.onCreateMenuCallback, nullptr);
    selectOverlayInfo.onCreateCallback.onCreateMenuCallback(params);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, testID);

    ASSERT_NE(selectOverlayInfo.onCreateCallback.onMenuItemClick, nullptr);
    EXPECT_TRUE(selectOverlayInfo.onCreateCallback.onMenuItemClick(params[0]));
    EXPECT_FALSE(selectOverlayInfo.onCreateCallback.onMenuItemClick(params[1]));
}

/*
 * @tc.name: setTextOverflowTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setTextOverflowTestDefaultValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextOverflow, nullptr);
    auto jsonValue = GetJsonValue(node_);
    auto resultValue = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
    EXPECT_EQ(resultValue, ATTRIBUTE_TEXT_DEFAULT_VALUE) << "Passed value is: " << ATTRIBUTE_TEXT_DEFAULT_VALUE;
}

/*
 * @tc.name: setTextOverflowTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setTextOverflowTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextOverflow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultValue;

    using TestStep = std::tuple<Ark_TextOverflow, std::string>;
    static const std::vector<TestStep> testPlan = {
        {ARK_TEXT_OVERFLOW_NONE, "TextOverflow.None"},
        {ARK_TEXT_OVERFLOW_CLIP, "TextOverflow.Clip"},
        {ARK_TEXT_OVERFLOW_ELLIPSIS, "TextOverflow.Ellipsis"},
        {ARK_TEXT_OVERFLOW_MARQUEE, "TextOverflow.Marquee"},
    };

    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setTextOverflow(node_, inputValue);
        jsonValue = GetJsonValue(node_);
        resultValue = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setTextOverflowTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setTextOverflowTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTextOverflow, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultValue = "";
    auto invalidValue = static_cast<TextOverflow>(-1);

    using TestStep = std::tuple<Ark_TextOverflow, std::string>;
    static const std::vector<TestStep> testPlan = {
        {Converter::ArkValue<Ark_TextOverflow>(invalidValue), ATTRIBUTE_TEXT_DEFAULT_VALUE},
    };

    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setTextOverflow(node_, inputValue);
        jsonValue = GetJsonValue(node_);
        resultValue = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_OVERFLOW_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: setMaxLinesTestDefaultValues
 * @tc.desc: Check the functionality of setMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setMaxLinesTestDefaultValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaxLines, nullptr);
    auto jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MAX_LINES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MAX_LINES_DEFAULT_STR_VALUE)
        << "Passed value is: " << ATTRIBUTE_MAX_LINES_DEFAULT_STR_VALUE;
}

/**
 * @tc.name: setMaxLinesTestValidValues
 * @tc.desc: Check the functionality of setMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setMaxLinesTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaxLines, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    std::string resultValue;

    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(123321), "123321"},
        {Converter::ArkValue<Ark_Number>(321123), "321123"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMaxLines(node_, &inputValue);
        resultValue = GetStringAttribute(node_, ATTRIBUTE_MAX_LINES_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: setMaxLinesTestInvalidValues
 * @tc.desc: Check the functionality of setMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setMaxLinesTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMaxLines, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    std::string resultValue;
    const std::string invalidValue = "INF", zeroValue = "0";

    using OneTestStep = std::tuple<Ark_Number, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Number>(-1), invalidValue},
        {Converter::ArkValue<Ark_Number>(0), zeroValue},
        {Converter::ArkValue<Ark_Number>(-0.0), zeroValue},
        {Converter::ArkValue<Ark_Number>(-0.00001), zeroValue},
        {Converter::ArkValue<Ark_Number>(0.88), zeroValue},
        {Converter::ArkValue<Ark_Number>(INT32_MIN), invalidValue},
        {Converter::ArkValue<Ark_Number>(INT32_MIN+1), invalidValue},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMaxLines(node_, &inputValue);
        resultValue = GetStringAttribute(node_, ATTRIBUTE_MAX_LINES_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: OnWillChangeTest
 * @tc.desc: setOnWillChange test
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, OnWillChangeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnWillChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    struct CheckEvent {
        int32_t resourceId;
        ChangeValueInfo info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    int32_t expectedResourceId = 123321;
    auto expectedChangeValueInfo = ChangeValueInfo {
        .value = u"test content", .previewText.offset = 2, .previewText.value = u"previewText",
        .oldPreviewText.offset = 1, .oldPreviewText.value = u"oldPreviewText", .oldContent = u"oldContent",
        .rangeBefore.start = 1, .rangeBefore.end = 6, .rangeAfter.start = 2, .rangeAfter.end = 5};

    auto inputCallback = [] (Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_EditableTextChangeValue parameter, const Callback_Boolean_Void continuation) {
        auto value = Converter::Convert<ChangeValueInfo>(parameter);
        checkEvent = CheckEvent {resourceId, value};
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(true));
    };

    auto func = Converter::ArkValue<Callback_EditableTextChangeValue_Boolean>(nullptr,
        inputCallback, expectedResourceId);
    modifier_->setOnWillChange(node_, &func);

    auto eventHub = frameNode->GetEventHub<NG::TextFieldEventHub>();
    ASSERT_TRUE(eventHub);
    auto result = eventHub->FireOnWillChangeEvent(expectedChangeValueInfo);
    EXPECT_TRUE(result);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, expectedResourceId);
    EXPECT_EQ(checkEvent->info.value, expectedChangeValueInfo.value);
    EXPECT_EQ(checkEvent->info.previewText.offset, expectedChangeValueInfo.previewText.offset);
    EXPECT_EQ(checkEvent->info.previewText.value, expectedChangeValueInfo.previewText.value);
    EXPECT_EQ(checkEvent->info.oldPreviewText.offset, expectedChangeValueInfo.oldPreviewText.offset);
    EXPECT_EQ(checkEvent->info.oldPreviewText.value, expectedChangeValueInfo.oldPreviewText.value);
    EXPECT_EQ(checkEvent->info.oldContent, expectedChangeValueInfo.oldContent);
    EXPECT_EQ(checkEvent->info.rangeBefore.start, expectedChangeValueInfo.rangeBefore.start);
    EXPECT_EQ(checkEvent->info.rangeBefore.end, expectedChangeValueInfo.rangeBefore.end);
    EXPECT_EQ(checkEvent->info.rangeAfter.start, expectedChangeValueInfo.rangeAfter.start);
    EXPECT_EQ(checkEvent->info.rangeAfter.end, expectedChangeValueInfo.rangeAfter.end);
}

/**
 * @tc.name: ShowCounterTestDefaultValues
 * @tc.desc: setOnWillChange test
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, ShowCounterTestDefaultValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setShowCounter, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto resultValue = GetStringAttribute(node_, ATTRIBUTE_SHOW_COUNTER_NAME);
    EXPECT_EQ(resultValue, ATTRIBUTE_SHOW_COUNTER_DEFAULT_VALUE)
        << "Passed value is: " << ATTRIBUTE_SHOW_COUNTER_DEFAULT_VALUE;
}

/**
 * @tc.name: ShowCounterTestValidValues
 * @tc.desc: setOnWillChange test
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, ShowCounterTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setShowCounter, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    std::string resultValue;

    using OneTestStep = std::tuple<Opt_Number, Opt_Boolean, Ark_Boolean, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Number>(25), Converter::ArkValue<Opt_Boolean>(true),
            Converter::ArkValue<Ark_Boolean>(true),
            "{\"value\":true,\"options\":{\"thresholdPercentage\":25,\"highlightBorder\":true}}"},
        {Converter::ArkValue<Opt_Number>(30), Converter::ArkValue<Opt_Boolean>(false),
            Converter::ArkValue<Ark_Boolean>(true),
            "{\"value\":true,\"options\":{\"thresholdPercentage\":30,\"highlightBorder\":false}}"},
        {Converter::ArkValue<Opt_Number>(35), Converter::ArkValue<Opt_Boolean>(true),
            Converter::ArkValue<Ark_Boolean>(false),
            "{\"value\":false,\"options\":{\"thresholdPercentage\":35,\"highlightBorder\":true}}"},
        {Converter::ArkValue<Opt_Number>(40), Converter::ArkValue<Opt_Boolean>(false),
            Converter::ArkValue<Ark_Boolean>(false),
            "{\"value\":false,\"options\":{\"thresholdPercentage\":40,\"highlightBorder\":false}}"},
        };
    Opt_InputCounterOptions arkOptions;

    for (auto [inputThresholdPercentageValue, inputHighlightBorderValue, inputIsShowCounter, expectedValue]: testPlan) {
        arkOptions = Converter::ArkValue<Opt_InputCounterOptions>(
            Ark_InputCounterOptions {inputThresholdPercentageValue, inputHighlightBorderValue});
        modifier_->setShowCounter(node_, inputIsShowCounter, &arkOptions);
        resultValue = GetStringAttribute(node_, ATTRIBUTE_SHOW_COUNTER_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/**
 * @tc.name: ShowCounterTestInvalidValues
 * @tc.desc: setOnWillChange test
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, ShowCounterTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setShowCounter, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    std::string resultValue;

    using OneTestStep = std::tuple<Opt_Number, Opt_Boolean, Ark_Boolean, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {{.tag = Ark_Tag::INTEROP_TAG_UNDEFINED}, Converter::ArkValue<Opt_Boolean>(true),
            Converter::ArkValue<Ark_Boolean>(true),
            "{\"value\":true,\"options\":{\"thresholdPercentage\":-1,\"highlightBorder\":true}}"},
        {{.tag = Ark_Tag::INTEROP_TAG_UNDEFINED}, {.tag = Ark_Tag::INTEROP_TAG_UNDEFINED},
            Converter::ArkValue<Ark_Boolean>(false),
            "{\"value\":false,\"options\":{\"thresholdPercentage\":-1,\"highlightBorder\":true}}"},
        };
    Opt_InputCounterOptions arkOptions;

    for (auto [inputThresholdPercentageValue, inputHighlightBorderValue, inputIsShowCounter, expectedValue]: testPlan) {
        arkOptions = Converter::ArkValue<Opt_InputCounterOptions>(
            Ark_InputCounterOptions {inputThresholdPercentageValue, inputHighlightBorderValue});
        modifier_->setShowCounter(node_, inputIsShowCounter, &arkOptions);
        resultValue = GetStringAttribute(node_, ATTRIBUTE_SHOW_COUNTER_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }

    auto inputIsShowCounter = Converter::ArkValue<Ark_Boolean>(true);
    auto expectedValue = "{\"value\":true,\"options\":{\"thresholdPercentage\":-1,\"highlightBorder\":true}}";
    modifier_->setShowCounter(node_, inputIsShowCounter, nullptr);
    resultValue = GetStringAttribute(node_, ATTRIBUTE_SHOW_COUNTER_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
}

/**
 * @tc.name: setKeyboardAppearanceTest
 * @tc.desc: Check the functionality of setKeyboardAppearance
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest2, setKeyboardAppearanceTest, TestSize.Level1)
{
    typedef std::tuple<Opt_KeyboardAppearance, std::string> TestStep;
    const std::vector<TestStep> TEST_PLAN = {
        { Converter::ArkValue<Opt_KeyboardAppearance>(
            Ark_KeyboardAppearance::ARK_KEYBOARD_APPEARANCE_IMMERSIVE), "1" },
        { Converter::ArkValue<Opt_KeyboardAppearance>(
            Ark_KeyboardAppearance::ARK_KEYBOARD_APPEARANCE_NONE_IMMERSIVE), "0" },
        { Converter::ArkValue<Opt_KeyboardAppearance>(
            Ark_KeyboardAppearance::ARK_KEYBOARD_APPEARANCE_LIGHT_IMMERSIVE), "2" },
        { Converter::ArkValue<Opt_KeyboardAppearance>(
            Ark_KeyboardAppearance::ARK_KEYBOARD_APPEARANCE_DARK_IMMERSIVE), "3" },
        { Converter::ArkValue<Opt_KeyboardAppearance>(Ark_Empty()), "0" }}; // invalid

    ASSERT_NE(modifier_->setKeyboardAppearance, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_APPEARANCE_NAME);
    EXPECT_EQ(resultStr, "0");

    for (auto& [value, expected] : TEST_PLAN) {
        modifier_->setKeyboardAppearance(node_, &value);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_APPEARANCE_NAME);
        EXPECT_EQ(resultStr, expected);
    }

    modifier_->setKeyboardAppearance(node_, nullptr);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_APPEARANCE_NAME);
    EXPECT_EQ(resultStr, "0");
}

} // namespace OHOS::Ace::NG
