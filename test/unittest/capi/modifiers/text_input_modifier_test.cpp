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

} // namespace OHOS::Ace::NG
