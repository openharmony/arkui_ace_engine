/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/interfaces/native/implementation/text_input_controller_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
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
}

namespace {
const auto ATTRIBUTE_PLACEHOLDER_NAME = "placeholder";
const auto ATTRIBUTE_TEXT_NAME = "text";
const auto ATTRIBUTE_CARET_POSITION_NAME = "caretPosition";
const auto ATTRIBUTE_CARET_POSITION_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_INPUT_FILTER_NAME("inputFilter");
const std::string STR_TEST_TEXT("test_text");
const std::string STR_TEST_TEXT2("test_text2");
const std::u16string ERROR_TEXT = u"error_text";
const std::u16string ERROR_TEXT2 = u"error_text2";
const Ark_Int32 AINT32_POS(1234);
const Ark_Int32 AINT32_NEG(INT_MIN);
const Ark_Float32 AFLT32_POS(1.234f);
const Ark_Float32 AFLT32_NEG(-5.6789f);

using ArkNumberIntTest = std::pair<Ark_Int32, Ark_Int32>;
using ArkNumberFloatTest = std::pair<float, float>;

const std::vector<ArkNumberIntTest> INT_NUMBER_TEST_PLAN = {
    { AINT32_POS, AINT32_POS },
    { AINT32_NEG, AINT32_NEG },
};
const std::vector<ArkNumberFloatTest> FLOAT_NUMBER_TEST_PLAN = {
    { AFLT32_POS, AFLT32_POS },
    { AFLT32_NEG, AFLT32_NEG },
};

const std::vector<TextDeleteDirection> DELETE_DIRECTION_TEST_PLAN = {
    TextDeleteDirection::FORWARD,
    TextDeleteDirection::BACKWARD,
};
} // namespace

class TextInputModifierTest : public ModifierTestBase<GENERATED_ArkUITextInputModifier,
                                  &GENERATED_ArkUINodeModifiers::getTextInputModifier, GENERATED_ARKUI_TEXT_INPUT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TextFieldTheme>();
    }
};

/*
 * @tc.name: setCaretPositionTestCaretPositionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setCaretPositionTestCaretPositionValidValues, TestSize.Level1)
{
    auto checkValue = [this](const std::string& input) {
        auto textLength = input.length();
        std::vector<int32_t> invalidPositionValues = {
            -1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), textLength + 1
        };

        Ark_TextInputOptions textInputOptions = {};
        textInputOptions.text = ArkUnion<Opt_Union_ResourceStr_Bindable_ResourceStr_Bindable_Resource_Bindable_String,
            Ark_ResourceStr>(ArkUnion<Ark_ResourceStr, Ark_String>(input));
        auto inputValue = ArkValue<Opt_TextInputOptions>(textInputOptions);
        modifier_->setTextInputOptions(node_, &inputValue);
        for (auto index = 0; index <= textLength; index++) {
            auto testValue = Converter::ArkValue<Opt_Int32>(index);
            modifier_->setCaretPosition(node_, &testValue);
            auto jsonValue = GetJsonValue(node_);
            auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_POSITION_NAME);
            EXPECT_EQ(resultStr, std::to_string(index))
                << "Input value is: " << input << ", method: setCaretPosition, attribute: caretPosition: "
                << index;
        }
        for (auto index = static_cast<int>(textLength); index >= 0; index--) {
            auto testValue = Converter::ArkValue<Opt_Int32>(index);
            modifier_->setCaretPosition(node_, &testValue);
            auto jsonValue = GetJsonValue(node_);
            auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_POSITION_NAME);
            EXPECT_EQ(resultStr, std::to_string(index))
                << "Input value is: " << input << ", method: setCaretPosition (reverse), attribute: caretPosition: "
                << index;
        }
        for (auto invalidIndex: invalidPositionValues) {
            auto testValue = Converter::ArkValue<Opt_Int32>(invalidIndex);
            modifier_->setCaretPosition(node_, &testValue);
            auto jsonValue = GetJsonValue(node_);
            auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_POSITION_NAME);
            std::string expectedResult =
                invalidIndex < 0 ? ATTRIBUTE_CARET_POSITION_DEFAULT_VALUE : std::to_string(textLength);
            EXPECT_EQ(resultStr, expectedResult)
                << "Input value is: " << input
                << ", method: setCaretPosition exceed than Text length, attribute: caretPosition: " << invalidIndex;
        }
    };

    std::vector<std::string> testPlan = {
        "", "T", "Text", "   ",
    };

    for (auto& input : testPlan) {
        checkValue(input);
    }
}

/*
 * @tc.name: setShowUnitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setShowUnitTest, TestSize.Level1)
{
#ifdef WRONG_MERGE
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();

    struct CheckEvent {
        int32_t resourceId;
        Ark_NativePointer parentNode;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    int32_t nodeId = 555;
    auto node = BlankModelNG::CreateFrameNode(nodeId);
    EXPECT_NE(node, nullptr);
    static std::optional<RefPtr<UINode>> uiNode = node;

    auto checkCallback = [](
        const Ark_Int32 resourceId,
        const Ark_NativePointer parentNode,
        const Callback_Pointer_Void continuation) {
        checkEvent = CheckEvent{
            .resourceId = resourceId,
            .parentNode = parentNode
        };

        if (uiNode) {
            CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode.value()));
        }
    };

    static constexpr int32_t contextId = 123;
    CustomNodeBuilder customBuilder =
        Converter::ArkValue<CustomNodeBuilder>(checkCallback, contextId);

    EXPECT_EQ(checkEvent.has_value(), false);
    EXPECT_EQ(pattern->GetUnitNode(), nullptr);
    modifier_->setShowUnit(node_, &customBuilder);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(reinterpret_cast<FrameNode*>(checkEvent->parentNode), frameNode);
    EXPECT_EQ(pattern->GetUnitNode(), node);
#endif
}

/**
 * @tc.name: setOnWillInsertTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextInputModifier.setOnWillInsert.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setOnWillInsertTest, TestSize.Level1)
{
    static const auto checkText = u"test_text";
    static const Ark_Int32 AINT32_POS(1234);
    const Ark_Int32 AINT32_NEG(INT_MIN);

    static const Ark_Int32 expectedResId = 123;
    auto onWillInsertHandler = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_InsertValue data,
        const Callback_Boolean_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Converter::Convert<std::u16string>(data.insertValue), checkText);
        auto result = Converter::Convert<int32_t>(data.insertOffset) > 0;
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_Boolean>(result));
    };
    auto arkCallback = Converter::ArkCallback<Opt_Callback_InsertValue_Boolean>(onWillInsertHandler, expectedResId);
    modifier_->setOnWillInsert(node_, &arkCallback);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);

    {
        InsertValueInfo checkValue = { .insertOffset = AINT32_POS, .insertValue = checkText };
        auto returnVal = eventHub->FireOnWillInsertValueEvent(checkValue);
        EXPECT_TRUE(returnVal);
    }
    {
        InsertValueInfo checkValue = { .insertOffset = AINT32_NEG, .insertValue = checkText };
        auto returnVal = eventHub->FireOnWillInsertValueEvent(checkValue);
        EXPECT_FALSE(returnVal);
    }
}

/**
 * @tc.name: setOnWillDeleteTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextInputModifier.setOnWillDelete.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setOnWillDeleteTest, TestSize.Level1)
{
    static const auto checkText = u"test_text";
    static const Ark_Int32 AINT32_POS(1234);

    static const Ark_Int32 expectedResId = 123;
    static const Ark_Int32 expectedOffset = AINT32_POS;

    ASSERT_NE(modifier_->setOnWillDelete, nullptr);
    auto callbackSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_DeleteValue data, const Callback_Boolean_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Converter::Convert<std::u16string>(data.deleteValue), checkText);
        EXPECT_EQ(Converter::Convert<int32_t>(data.deleteOffset), expectedOffset);
        auto willDeleteDirection = Converter::OptConvert<TextDeleteDirection>(data.direction);
        auto result = willDeleteDirection == TextDeleteDirection::FORWARD;
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_Boolean>(result));
    };
    auto arkCallback = Converter::ArkCallback<Opt_Callback_DeleteValue_Boolean>(callbackSyncFunc, expectedResId);
    modifier_->setOnWillDelete(node_, &arkCallback);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    DeleteValueInfo checkValueDefault;

    {
        DeleteValueInfo checkValue = {
            .deleteOffset = expectedOffset, .deleteValue = checkText, .direction = TextDeleteDirection::FORWARD
        };
        auto checkVal = eventHub->FireOnWillDeleteEvent(checkValue);
        EXPECT_TRUE(checkVal);
    }
    {
        DeleteValueInfo checkValue = {
            .deleteOffset = expectedOffset, .deleteValue = checkText, .direction = TextDeleteDirection::BACKWARD
        };
        auto checkVal = eventHub->FireOnWillDeleteEvent(checkValue);
        EXPECT_FALSE(checkVal);
    }
}

/*
 * @tc.name: setTextInputOptionsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextInputOptionsTest, TestSize.Level1)
{
    const std::string placeholderTestValue = "Placeholder 511";
    const std::string textTestValue = "Text 512";

    Ark_TextInputOptions options;
    std::string resultStr;

    auto placeholder = ArkUnion<Ark_ResourceStr, Ark_String>(placeholderTestValue);
    auto text = ArkUnion<Ark_ResourceStr, Ark_String>(textTestValue);

    options.placeholder = ArkValue<Opt_ResourceStr>(placeholder);
    options.text = ArkUnion<Opt_Union_ResourceStr_Bindable_ResourceStr_Bindable_Resource_Bindable_String,
        Ark_ResourceStr>(ArkValue<Ark_ResourceStr>(text));
    options.controller = ArkValue<Opt_TextInputController>();

    auto optOptions = ArkValue<Opt_TextInputOptions>(options);
    modifier_->setTextInputOptions(node_, &optOptions);

    auto jsonValue = GetJsonValue(node_);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PLACEHOLDER_NAME);
    EXPECT_EQ(resultStr, placeholderTestValue);

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_TEXT_NAME);
    EXPECT_EQ(resultStr, textTestValue);
}

/*
 * @tc.name: setTextInputOptionsTestController
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setTextInputOptionsTestController, TestSize.Level1)
{
    Ark_TextInputOptions options;
    std::string resultStr;

    auto controllerAccessor = GeneratedModifier::GetTextInputControllerAccessor();
    ASSERT_NE(controllerAccessor, nullptr);

    auto peer = controllerAccessor->construct();
    ASSERT_NE(peer, nullptr);
    EXPECT_EQ(peer->GetController(), nullptr);

    options.placeholder = ArkValue<Opt_ResourceStr>();
    options.text = ArkValue<Opt_Union_ResourceStr_Bindable_ResourceStr_Bindable_Resource_Bindable_String>();
    options.controller = ArkValue<Opt_TextInputController>(peer);

    auto optOptions = ArkValue<Opt_TextInputOptions>(options);
    modifier_->setTextInputOptions(node_, &optOptions);
    EXPECT_NE(peer->GetController(), nullptr);

    controllerAccessor->destroyPeer(peer);
}

/**
 * @tc.name: setOnEditChangeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextInputModifier.setOnEditChangeTest.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setOnEditChangeTest, TestSize.Level1)
{
    const int32_t id = 123;
    static std::optional<std::tuple<int32_t, bool>> checkData;
    ASSERT_NE(modifier_->setOnEditChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onEditChange = [](const Ark_Int32 resourceId, Ark_Boolean parameter) {
        checkData = { resourceId, Converter::Convert<bool>(parameter) };
    };
    auto arkCallback = Converter::ArkCallback<Opt_arkui_component_common_Callback_Boolean_Void>(onEditChange, id);
    modifier_->setOnEditChange(node_, &arkCallback);
    eventHub->FireOnEditChanged(true);
    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(std::get<0>(checkData.value()), id);
    EXPECT_EQ(std::get<1>(checkData.value()), true);
    eventHub->FireOnEditChanged(false);
    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(std::get<0>(checkData.value()), id);
    EXPECT_EQ(std::get<1>(checkData.value()), false);
}

/**
 * @tc.name: setOnSecurityStateChangeTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextInputModifier.setOnSecurityStateChangeTest.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setOnSecurityStateChangeTest, TestSize.Level1)
{
    const int32_t id = 123;
    static std::optional<std::tuple<int32_t, bool>> checkData;
    ASSERT_NE(modifier_->setOnEditChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto onEditChange = [](const Ark_Int32 resourceId, Ark_Boolean parameter) {
        checkData = { resourceId, Converter::Convert<bool>(parameter) };
    };
    auto arkCallback = Converter::ArkCallback<Opt_arkui_component_common_Callback_Boolean_Void>(onEditChange, id);
    modifier_->setOnSecurityStateChange(node_, &arkCallback);
    eventHub->FireOnSecurityStateChanged(true);
    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(std::get<0>(checkData.value()), id);
    EXPECT_EQ(std::get<1>(checkData.value()), true);
    eventHub->FireOnSecurityStateChanged(false);
    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(std::get<0>(checkData.value()), id);
    EXPECT_EQ(std::get<1>(checkData.value()), false);
}

/**
 * @tc.name: setOnContentScrollTest
 * @tc.desc: Check the functionality of setOnContentScroll
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setOnContentScrollTest, TestSize.Level1)
{
    const int32_t id = 123;
    ASSERT_NE(modifier_->setOnContentScroll, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    static std::optional<float> expectedX = std::nullopt;
    static std::optional<float> expectedY = std::nullopt;
    auto onContentScroll = [](const Ark_Int32 resourceId, Ark_Float64 totalOffsetX, Ark_Float64 totalOffsetY) {
        expectedX = Convert<float>(totalOffsetX);
        expectedY = Convert<float>(totalOffsetY);
    };
    auto arkCallback = Converter::ArkCallback<Opt_OnContentScrollCallback>(onContentScroll, id);
    for (const auto& [value, expectVal] : FLOAT_NUMBER_TEST_PLAN) {
        modifier_->setOnContentScroll(node_, &arkCallback);
        eventHub->FireOnScrollChangeEvent(value, value);
        EXPECT_EQ(expectedX, expectVal);
        EXPECT_EQ(expectedY, expectVal);
    }
}

/**
 * @tc.name: setOnTextSelectionChangeTest
 * @tc.desc: Check the functionality of setOnTextSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setOnTextSelectionChangeTest, TestSize.Level1)
{
    const int32_t id = 123;
    ASSERT_NE(modifier_->setOnTextSelectionChange, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    static std::optional<int32_t> expectedStart = std::nullopt;
    static std::optional<int32_t> expectedEnd = std::nullopt;
    auto onTextSelection = [](const Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end) {
        expectedStart = Convert<int32_t>(start);
        expectedEnd = Convert<int32_t>(end);
    };
    auto arkCallback = Converter::ArkCallback<Opt_OnTextSelectionChangeCallback>(onTextSelection, id);
    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        modifier_->setOnTextSelectionChange(node_, &arkCallback);
        eventHub->FireOnSelectionChange(value, value);
        EXPECT_EQ(expectedStart, expectVal);
        EXPECT_EQ(expectedEnd, expectVal);
    }
}

/**
 * @tc.name: setOnCopyTest
 * @tc.desc: Check the functionality of setOnCopy.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setOnCopyTest, TestSize.Level1)
{
    const int32_t id = 123;
    constexpr auto checkText = u"test_text";
    ASSERT_NE(modifier_->setOnCopy, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    static std::optional<std::u16string> expected = std::nullopt;
    auto onCopy = [](const Ark_Int32 resourceId, Ark_String parameter) {
        expected = Converter::Convert<std::u16string>(parameter);
    };
    auto arkCallback = Converter::ArkCallback<Opt_Callback_String_Void>(onCopy, id);
    modifier_->setOnCopy(node_, &arkCallback);
    eventHub->FireOnCopy(checkText);
    EXPECT_TRUE(expected.has_value());
    EXPECT_EQ(expected, checkText);
}

/**
 * @tc.name: setOnCutTest
 * @tc.desc: Check the functionality of setOnCut.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setOnCutTest, TestSize.Level1)
{
    const int32_t id = 123;
    constexpr auto checkText = u"test_text";
    ASSERT_NE(modifier_->setOnCut, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    static std::optional<std::u16string> expected = std::nullopt;
    auto onCut = [](const Ark_Int32 resourceId, Ark_String parameter) {
        expected = Converter::Convert<std::u16string>(parameter);
    };
    auto arkCallback = Converter::ArkCallback<Opt_Callback_String_Void>(onCut, id);
    modifier_->setOnCut(node_, &arkCallback);
    eventHub->FireOnCut(checkText);
    EXPECT_TRUE(expected.has_value());
    EXPECT_EQ(expected, checkText);
}

/**
 * @tc.name: setOnDidInsertTest
 * @tc.desc: Check the functionality of setOnDidInsert
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setOnDidInsertTest, TestSize.Level1)
{
    const int32_t id = 123;
    constexpr auto checkText = u"test_text";
    constexpr int32_t offset = 0;
    ASSERT_NE(modifier_->setOnDidInsert, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    static std::optional<std::u16string> expectedText = std::nullopt;
    static std::optional<int32_t> expectedOffset = std::nullopt;
    auto onDidInsert = [](Ark_Int32 nodeId, const Ark_InsertValue data) {
        expectedText = Convert<std::u16string>(data.insertValue);
        expectedOffset = Convert<int32_t>(data.insertOffset);
    };
    auto arkCallback = Converter::ArkCallback<Opt_Callback_InsertValue_Void>(onDidInsert, id);
    InsertValueInfo checkValue = { .insertOffset = offset, .insertValue = checkText };
    modifier_->setOnDidInsert(node_, &arkCallback);
    eventHub->FireOnDidInsertValueEvent(checkValue);
    EXPECT_EQ(expectedText, checkText);
    EXPECT_EQ(expectedOffset, offset);

    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        InsertValueInfo checkValue = { .insertOffset = value, .insertValue = checkText };
        eventHub->FireOnDidInsertValueEvent(checkValue);
        EXPECT_EQ(expectedText, checkText);
        EXPECT_EQ(expectedOffset, expectVal);
    }
}

/**
 * @tc.name: setOnDidDeleteTest
 * @tc.desc: Check the functionality of setOnDidDelete
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setOnDidDeleteTest, TestSize.Level1)
{
    const int32_t id = 123;
    constexpr auto checkText = u"test_text";
    constexpr int32_t offset = 0;
    constexpr TextDeleteDirection DIRECTION(TextDeleteDirection::FORWARD);
    ASSERT_NE(modifier_->setOnDidDelete, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    static std::optional<std::u16string> expectedText = std::nullopt;
    static std::optional<int32_t> expectedOffset = std::nullopt;
    static std::optional<TextDeleteDirection> expectedDirection = std::nullopt;
    auto onDidDelete = [](Ark_Int32 nodeId, const Ark_DeleteValue data) {
        expectedText = Convert<std::u16string>(data.deleteValue);
        expectedOffset = Convert<int32_t>(data.deleteOffset);
        expectedDirection = OptConvert<TextDeleteDirection>(data.direction);
    };
    auto arkCallback = Converter::ArkCallback<Opt_Callback_DeleteValue_Void>(onDidDelete, id);
    DeleteValueInfo checkValue = { .deleteOffset = offset, .direction = DIRECTION, .deleteValue = checkText };
    modifier_->setOnDidDelete(node_, &arkCallback);
    eventHub->FireOnDidDeleteValueEvent(checkValue);
    EXPECT_EQ(expectedText, checkText);
    EXPECT_EQ(expectedDirection, DIRECTION);
    EXPECT_EQ(expectedOffset, offset);
    for (const auto& [value, expectVal] : INT_NUMBER_TEST_PLAN) {
        for (const auto& deleteDirection : DELETE_DIRECTION_TEST_PLAN) {
            DeleteValueInfo checkValue = {
                .deleteOffset = value, .direction = deleteDirection, .deleteValue = checkText
            };
            eventHub->FireOnDidDeleteValueEvent(checkValue);
            EXPECT_EQ(expectedText, checkText);
            EXPECT_EQ(expectedOffset, expectVal);
            EXPECT_EQ(expectedDirection, deleteDirection);
        }
    }
}

/**
 * @tc.name: setInputFilterTest
 * @tc.desc: Check the functionality of setOnCut.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, DISABLED_setInputFilterTest, TestSize.Level1)
{
    const int32_t id = 123;
    ASSERT_NE(modifier_->setInputFilter, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    struct CheckEvent {
        int32_t nodeId;
        std::u16string error;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto onErrorChange = [](Ark_Int32 nodeId, const Ark_String error) {
        checkEvent = CheckEvent{
            .nodeId = id,
            .error = Converter::Convert<std::u16string>(error)
        };
    };
    auto arkCallback = Converter::ArkCallback<Opt_Callback_String_Void>(onErrorChange, id);
    Converter::ConvContext ctx;
    auto sendResource = Converter::ArkUnion<Opt_ResourceStr, Ark_String>(STR_TEST_TEXT, &ctx);
    auto sendResource2 = Converter::ArkUnion<Opt_ResourceStr, Ark_String>(STR_TEST_TEXT2, &ctx);
    modifier_->setInputFilter(node_, &sendResource, &arkCallback);
    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnInputFilterError(ERROR_TEXT);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, id);
    EXPECT_EQ(checkEvent->error, ERROR_TEXT);
    auto attrValue = GetStringAttribute(node_, ATTRIBUTE_INPUT_FILTER_NAME);
    EXPECT_EQ(attrValue, STR_TEST_TEXT);
    checkEvent.reset();
    modifier_->setInputFilter(node_, &sendResource2, &arkCallback);
    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnInputFilterError(ERROR_TEXT2);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, id);
    EXPECT_EQ(checkEvent->error, ERROR_TEXT2);
    attrValue = GetStringAttribute(node_, ATTRIBUTE_INPUT_FILTER_NAME);
    EXPECT_EQ(attrValue, STR_TEST_TEXT2);
}

#ifdef WRONG_OLD_CALLBACK
/*
 * @tc.name: setOnChangeEventTextImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setOnChangeEventTextImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<std::string> value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_ResourceStr parameter) {
        checkEvent = CheckEvent{
            .nodeId = resourceId,
            .value = Converter::OptConvert<std::string>(parameter)
        };
    };

    auto arkCallback = Converter::ArkCallback<Opt_Callback_ResourceStr_Void>(checkCallback, contextId);
    modifier_->set_onChangeEvent_text(node_, &arkCallback);

    PreviewText previewText {.offset = -1, .value = u""};
    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireOnChange({u"test", previewText});
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    ASSERT_EQ(checkEvent->value.has_value(), true);
    EXPECT_EQ(checkEvent->value.value(), "test");
    eventHub->FireOnChange({u"test_2", previewText});
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    ASSERT_EQ(checkEvent->value.has_value(), true);
    EXPECT_EQ(checkEvent->value.value(), "test_2");
}
#endif

} // namespace OHOS::Ace::NG
