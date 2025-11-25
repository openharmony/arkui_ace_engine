/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "gauge_modifier_test.h"
#include <gtest/gtest.h>
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components/search/search_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"

#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

const auto ATTRIBUTE_KEYBOARD_APPEARANCE_NAME = "keyboardAppearance";
const auto ATTRIBUTE_KEYBOARD_APPEARANCE_DEFAULT_VALUE = "0";

namespace Converter {
    template<>
    PreviewText Convert(const Ark_PreviewText& src)
    {
        PreviewText previewText = {.value = Convert<std::u16string>(src.value),
                                   .offset = Convert<int32_t>(src.offset)};
        return previewText;
    }
} // namespace Converter

class SearchModifierTest2 : public ModifierTestBase<GENERATED_ArkUISearchModifier,
                               &GENERATED_ArkUINodeModifiers::getSearchModifier, GENERATED_ARKUI_SEARCH> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<SearchTheme>();
        SetupTheme<TextFieldTheme>();
        SetupTheme<IconTheme>();
    }
};

/*
 * @tc.name: setCustomKeyboard_CustomNodeBuilder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest2, setCustomKeyboard_CustomNodeBuilder, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCustomKeyboard, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    int callsCount = 0;
    CustomNodeBuilderTestHelper<SearchModifierTest2> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    modifier_->setCustomKeyboard(frameNode, &builder, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    EXPECT_TRUE(textFieldPattern->HasCustomKeyboard());
    EXPECT_TRUE(textFieldPattern->RequestCustomKeyboard());
    EXPECT_EQ(builderHelper.GetCallsCountAsync(), ++callsCount);
}

/*
 * @tc.name: setCustomKeyboard_CustomNodeBuilder_KeyboardOptions
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest2, setCustomKeyboard_CustomNodeBuilder_KeyboardOptions, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCustomKeyboard, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    KeyboardOptions keyboardOptions = {.supportAvoidance = true};
    auto optKeyboardOptions = Converter::ArkValue<Opt_KeyboardOptions>(keyboardOptions);

    int callsCount = 0;
    CustomNodeBuilderTestHelper<SearchModifierTest2> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    modifier_->setCustomKeyboard(node_, &builder, &optKeyboardOptions);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    EXPECT_TRUE(textFieldPattern->HasCustomKeyboard());
    EXPECT_TRUE(textFieldPattern->RequestCustomKeyboard());
    EXPECT_EQ(builderHelper.GetCallsCountAsync(), ++callsCount);
}

/*
 * @tc.name: setKeyboardAppearanceDefaultValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest2, setKeyboardAppearanceDefaultValuesTest, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_APPEARANCE_NAME);
    EXPECT_EQ(resultStr,  ATTRIBUTE_KEYBOARD_APPEARANCE_DEFAULT_VALUE) <<
        "Default value for attribute 'keyboardAppearance'";
}

std::vector<std::tuple<std::string, Opt_KeyboardAppearance, std::string>> testFixtureEnumKeyboardAppearanceTestPlan = {
    { "KeyboardAppearance.NONE_IMMERSIVE",
        Converter::ArkValue<Opt_KeyboardAppearance>(ARK_KEYBOARD_APPEARANCE_NONE_IMMERSIVE), "0" },
    { "KeyboardAppearance.IMMERSIVE",
        Converter::ArkValue<Opt_KeyboardAppearance>(ARK_KEYBOARD_APPEARANCE_IMMERSIVE), "1" },
    { "KeyboardAppearance.LIGHT_IMMERSIVE",
        Converter::ArkValue<Opt_KeyboardAppearance>(ARK_KEYBOARD_APPEARANCE_LIGHT_IMMERSIVE), "2" },
    { "-1", Converter::ArkValue<Opt_KeyboardAppearance>(static_cast<Ark_KeyboardAppearance>(-1)),
        ATTRIBUTE_KEYBOARD_APPEARANCE_DEFAULT_VALUE },
    { "INT_MAX", Converter::ArkValue<Opt_KeyboardAppearance>(static_cast<Ark_KeyboardAppearance>(INT_MAX)),
        ATTRIBUTE_KEYBOARD_APPEARANCE_DEFAULT_VALUE },
};

/*
 * @tc.name: setKeyboardAppearanceValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SearchModifierTest2, setKeyboardAppearanceValuesTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setKeyboardAppearance, nullptr);
    auto checkValue = [this](
                        const std::string& input, const std::string& expectedStr, const Opt_KeyboardAppearance& value) {
        Opt_KeyboardAppearance inputValueKeyboardAppearance = value;
        modifier_->setKeyboardAppearance(node_, &inputValueKeyboardAppearance);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_KEYBOARD_APPEARANCE_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input <<
                                        ", method: setKeyboardAppearance, attribute: keyboardAppearance";
    };
    for (auto& [input, value, expected] : testFixtureEnumKeyboardAppearanceTestPlan) {
        checkValue(input, expected, value);
    }
}

/*
+ * @tc.name: setOnWillChangeTest
+ * @tc.desc:
+ * @tc.type: FUNC
+ */
HWTEST_F(SearchModifierTest2, setOnWillChangeTest, TestSize.Level1)
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
        ChangeValueInfo info;
        info.value = Converter::Convert<std::u16string>(parameter.content);
        info.previewText = Converter::Convert<PreviewText>(parameter.previewText.value);
        info.rangeBefore = Converter::Convert<TextRange>(parameter.options.value.rangeBefore);
        info.rangeAfter = Converter::Convert<TextRange>(parameter.options.value.rangeAfter);
        info.oldContent = Converter::Convert<std::u16string>(parameter.options.value.oldContent);
        info.oldPreviewText =  Converter::Convert<PreviewText>(parameter.options.value.oldPreviewText);
        checkEvent = CheckEvent {resourceId, info};
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Ark_Boolean>(true));
    };
    auto func = Converter::ArkValue<Callback_EditableTextChangeValue_Boolean>(nullptr,
        inputCallback, expectedResourceId);
    auto optCallback = Converter::ArkValue<Opt_Callback_EditableTextChangeValue_Boolean>(func);
    modifier_->setOnWillChange(node_, &optCallback);

    auto searchTextField = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(searchTextField);
    auto eventHub = searchTextField->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
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
} // namespace OHOS::Ace::NG
