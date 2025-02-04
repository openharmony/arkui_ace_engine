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

#include "test/unittest/capi/modifiers/generated/text_input_modifier_test.h"

#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/interfaces/native/implementation/text_input_controller_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace Converter;
using namespace TypeHelper;
using namespace TestConst::TextInput;

namespace GeneratedModifier {
const GENERATED_ArkUITextInputControllerAccessor* GetTextInputControllerAccessor();
}

namespace {
    const auto CHECK_TEXT(u"test_text");

    PreviewText g_PreviewText = { .offset = 1234, .value = u"test_offset" };
    std::u16string g_EventTestString(u"");
    int32_t g_EventTestOffset(0);

    struct EventsTracker {
        static inline GENERATED_ArkUITextInputEventsReceiver eventsReceiver {};

        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getTextInputEventsReceiver = [] () -> const GENERATED_ArkUITextInputEventsReceiver* {
                return &eventsReceiver;
            }
        };
    }; // EventsTracker
} // namespace

namespace Converter {
    template<>
    PreviewText Convert(const Ark_PreviewText& src)
    {
        PreviewText previewText = {.value = Convert<std::u16string>(src.value),
                                   .offset = Convert<int32_t>(src.offset)};
        return previewText;
    }
} // namespace Converter

class TextInputModifierTest2 : public ModifierTestBase<GENERATED_ArkUITextInputModifier,
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
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
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

    g_EventTestString.clear();
    g_EventTestOffset = 0;

    auto arkCallback = [](Ark_Int32 nodeId,
        const Ark_String value,
        const Opt_PreviewText previewText) {
        auto value2 = Converter::OptConvert<std::u16string>(value).value_or(u"");
        auto previewText2 = Converter::OptConvert<PreviewText>(previewText).value_or(PreviewText{});
        g_EventTestOffset = previewText2.offset;
        g_EventTestString.append(value2).append(previewText2.value);
    };

    auto onChange = Converter::ArkValue<EditableTextOnChangeCallback>(arkCallback, frameNode->GetId());

    modifier_->setOnChange(node_, &onChange);
    textFieldEventHub->FireOnChange(CHECK_TEXT, g_PreviewText);
    std::u16string checkString = CHECK_TEXT;
    checkString.append(g_PreviewText.value);
    EXPECT_EQ(g_EventTestString, checkString);
    EXPECT_EQ(g_EventTestOffset, g_PreviewText.offset);
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

    g_EventTestString.clear();
    g_EventTestOffset = 0;

    auto arkCallback = [](const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event) {
        g_EventTestString = Converter::OptConvert<std::u16string>(content).value_or(u"");
    };

    auto onPaste = Converter::ArkValue<OnPasteCallback>(arkCallback, frameNode->GetId());
    modifier_->setOnPaste(node_, &onPaste);
    textFieldEventHub->FireOnPaste(CHECK_TEXT);
    std::u16string checkString = CHECK_TEXT;
    EXPECT_EQ(g_EventTestString, checkString);
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

} // namespace OHOS::Ace::NG
