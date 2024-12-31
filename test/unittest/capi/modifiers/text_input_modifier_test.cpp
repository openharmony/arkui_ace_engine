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

#include "test/unittest/capi/modifiers/generated/text_input_modifier_test.h"

#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/interfaces/native/utility/callback_helper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace Converter;
using namespace TypeHelper;
using namespace TestConst::TextInput;

class TextInputModifierTestNonGenerated : public ModifierTestBase<GENERATED_ArkUITextInputModifier,
                                  &GENERATED_ArkUINodeModifiers::getTextInputModifier, GENERATED_ARKUI_TEXT_INPUT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<TextFieldTheme>();
        for (auto& [id, strid, res]: Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
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

        Opt_TextInputOptions textInputOptions = {};
        textInputOptions.value.text = ArkUnion<Opt_ResourceStr, Ark_String>(input);
        modifier_->setTextInputOptions(node_, &textInputOptions);
        for (auto index = 0; index <= textLength; index++) {
            auto testValue = Converter::ArkValue<Ark_Number>(index);
            modifier_->setCaretPosition(node_, &testValue);
            auto jsonValue = GetJsonValue(node_);
            auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_POSITION_NAME);
            EXPECT_EQ(resultStr, std::to_string(index))
                << "Input value is: " << input << ", method: setCaretPosition, attribute: caretPosition: "
                << index;
        }
        for (auto index = static_cast<int>(textLength); index >= 0; index--) {
            auto testValue = Converter::ArkValue<Ark_Number>(index);
            modifier_->setCaretPosition(node_, &testValue);
            auto jsonValue = GetJsonValue(node_);
            auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CARET_POSITION_NAME);
            EXPECT_EQ(resultStr, std::to_string(index))
                << "Input value is: " << input << ", method: setCaretPosition (reverse), attribute: caretPosition: "
                << index;
        }
        for (auto invalidIndex: invalidPositionValues) {
            auto testValue = Converter::ArkValue<Ark_Number>(invalidIndex);
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

    for (auto& [input, value, unusedStr] : Fixtures::testFixtureTextInputCaretPositionValidValues) {
        checkValue(input);
    }
}

/*
 * @tc.name: setShowUnitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setShowUnitTest, TestSize.Level1)
{
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
        Ark_VMContext context,
        const Ark_Int32 resourceId,
        const Ark_NativePointer parentNode,
        const Callback_Pointer_Void continuation) {
        checkEvent = {
            .resourceId = resourceId,
            .parentNode = parentNode
        };

        if (uiNode) {
            CallbackHelper(continuation).Invoke(AceType::RawPtr(uiNode.value()));
        }
    };

    static constexpr int32_t contextId = 123;
    CustomNodeBuilder customBuilder =
        Converter::ArkValue<CustomNodeBuilder>(nullptr, checkCallback, contextId);

    EXPECT_EQ(checkEvent.has_value(), false);
    EXPECT_EQ(pattern->GetUnitNode(), nullptr);
    modifier_->setShowUnit(node_, &customBuilder);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->resourceId, contextId);
    EXPECT_EQ(reinterpret_cast<FrameNode*>(checkEvent->parentNode), frameNode);
    EXPECT_EQ(pattern->GetUnitNode(), node);
}
/**
 * @tc.name: setOnWillInsertTest
 * @tc.desc: Check the functionality of GENERATED_ArkUITextInputModifier.setOnWillInsert.
 * @tc.type: FUNC
 */
HWTEST_F(TextInputModifierTest, setOnWillInsertTest, TestSize.Level1)
{
    static const auto CHECK_TEXT("test_text");
    static const Ark_Int32 AINT32_POS(1234);
const Ark_Int32 AINT32_NEG(INT_MIN);


    static const Ark_Int32 expectedResId = 123;
    auto onWillInsertHandler = [](Ark_VMContext context, const Ark_Int32 resourceId, const Ark_InsertValue data,
        const Callback_Boolean_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Converter::Convert<std::string>(data.insertValue), CHECK_TEXT);
        auto result = Converter::Convert<int32_t>(data.insertOffset) > 0;
        CallbackHelper(cbReturn).Invoke(Converter::ArkValue<Ark_Boolean>(result));
    };
    auto arkCallback = Converter::ArkValue<Callback_InsertValue_Boolean>(nullptr, onWillInsertHandler, expectedResId);
    modifier_->setOnWillInsert(node_, &arkCallback);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);

    {
        InsertValueInfo checkValue = { .insertOffset = AINT32_POS, .insertValue = CHECK_TEXT };
        auto returnVal = eventHub->FireOnWillInsertValueEvent(checkValue);
        EXPECT_TRUE(returnVal);
    }
    {
        InsertValueInfo checkValue = { .insertOffset = AINT32_NEG, .insertValue = CHECK_TEXT };
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
    static const auto CHECK_TEXT("test_text");
    static const Ark_Int32 AINT32_POS(1234);

    static const Ark_Int32 expectedResId = 123;
    static const Ark_Int32 expectedOffset = AINT32_POS;

    ASSERT_NE(modifier_->setOnWillDelete, nullptr);
    auto callbackSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_DeleteValue data, const Callback_Boolean_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Converter::Convert<std::string>(data.deleteValue), CHECK_TEXT);
        EXPECT_EQ(Converter::Convert<int32_t>(data.deleteOffset), expectedOffset);
        auto willDeleteDirection = Converter::OptConvert<TextDeleteDirection>(data.direction);
        auto result = willDeleteDirection == TextDeleteDirection::FORWARD;
        CallbackHelper(cbReturn).Invoke(Converter::ArkValue<Ark_Boolean>(result));
    };
    auto arkCallback = Converter::ArkValue<Callback_DeleteValue_Boolean>(nullptr, callbackSyncFunc, expectedResId);
    modifier_->setOnWillDelete(node_, &arkCallback);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    DeleteValueInfo checkValueDefault;

    {
        DeleteValueInfo checkValue = {
            .deleteOffset = expectedOffset, .deleteValue = CHECK_TEXT, .direction = TextDeleteDirection::FORWARD
        };
        auto checkVal = eventHub->FireOnWillDeleteEvent(checkValue);
        EXPECT_TRUE(checkVal);
    }
    {
        DeleteValueInfo checkValue = {
            .deleteOffset = expectedOffset, .deleteValue = CHECK_TEXT, .direction = TextDeleteDirection::BACKWARD
        };
        auto checkVal = eventHub->FireOnWillDeleteEvent(checkValue);
        EXPECT_FALSE(checkVal);
    }
}
} // namespace OHOS::Ace::NG
