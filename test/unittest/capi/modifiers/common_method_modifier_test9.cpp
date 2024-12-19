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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/implementation/draw_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto ATTRIBUTE_GROUP_NAME_TEST = "accessibilityGroup";
    const auto ATTRIBUTE_GROUP_DEFAULT_VALUE_TEST = "false";
    const auto ATTRIBUTE_TEXT_NAME_TEST = "accessibilityText";
    const auto ATTRIBUTE_TEXT_DEFAULT_VALUE_TEST = "";
    const auto ATTRIBUTE_TEXT_HINT_NAME_TEST = "accessibilityTextHint";
    const auto ATTRIBUTE_TEXT_HINT_DEFAULT_VALUE_TEST = "";
    const auto ATTRIBUTE_DESCRIPTION_NAME_TEST = "accessibilityDescription";
    const auto ATTRIBUTE_DESCRIPTION_DEFAULT_VALUE_TEST = "";
    const auto ATTRIBUTE_LEVEL_NAME_TEST = "accessibilityLevel";
    const auto ATTRIBUTE_LEVEL_DEFAULT_VALUE_TEST = "auto";
    const auto ATTRIBUTE_CHECKED_NAME_TEST = "accessibilityChecked";
    const auto ATTRIBUTE_CHECKED_DEFAULT_VALUE_TEST = "";
    const auto ATTRIBUTE_SELECTED_NAME_TEST = "accessibilitySelected";
    const auto ATTRIBUTE_SELECTED_DEFAULT_VALUE_TEST = "";
}

namespace Converter {
    template<>
    void AssignArkValue(Ark_Resource& dst, const std::string& src, ConvContext *ctx)
    {
        dst.type = Converter::ArkValue<Opt_Number>(static_cast<uint32_t>(ResourceType::STRING));
        dst.bundleName = Converter::ArkValue<Ark_String>(src);
        LOGE("this converter is disabled");
    }
}

class CommonMethodModifierTest9 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }

    RefPtr<GestureEventHub> GetGestureEventHub()
    {
        if (auto fnode = reinterpret_cast<FrameNode *>(node_); fnode) {
            if (auto eventHub = fnode->GetEventHub<NG::EventHub>(); eventHub) {
                return eventHub->GetOrCreateGestureEventHub();
            }
        }
        return nullptr;
    }
};

//////// AccessibilityGroup
/*
 * @tc.name: setAccessibilityGroupTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityGroupTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_GROUP_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_GROUP_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilityGroupTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityGroupTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityGroup0, nullptr);
    using OneTestStep = std::tuple<Ark_Boolean, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Boolean>(true), "true"},
        {Converter::ArkValue<Ark_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityGroup0(node_, inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_GROUP_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////// AccessibilityText
/*
 * @tc.name: setAccessibilityTextTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityTextTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_TEXT_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_TEXT_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilityTextTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityText0TestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityText0, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("test string 1"), "test string 1"},
        {Converter::ArkValue<Ark_String>("test string 2"), "test string 2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityText0(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_TEXT_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setAccessibilityTextTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityText1TestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityText1, nullptr);
    using OneTestStep = std::tuple<Ark_Resource, std::string>;
    std::string inputVal1 {"test string 1"}, inputVal2 {"test string 2"};
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Resource>(inputVal1, nullptr), inputVal1},
        {Converter::ArkValue<Ark_Resource>(inputVal2, nullptr), inputVal2},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityText1(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_TEXT_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
        // Освобождаем выделенную память
        delete[] inputValue.params.value.array;
    }
}

//////// AccessibilityTextHint
/*
 * @tc.name: setAccessibilityTextHintTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityTextHintTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_TEXT_HINT_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_TEXT_HINT_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilityTextHintTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityTextHintTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityTextHint, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("test string 1"), "test string 1"},
        {Converter::ArkValue<Ark_String>("test string 2"), "test string 2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityTextHint(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_TEXT_HINT_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////// AccessibilityDescription
/*
 * @tc.name: setAccessibilityDescriptionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityDescriptionTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_DESCRIPTION_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_DESCRIPTION_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilityDescriptionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityDescription0TestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityDescription0, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("test string 1"), "test string 1"},
        {Converter::ArkValue<Ark_String>("test string 2"), "test string 2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityDescription0(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_DESCRIPTION_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setAccessibilityDescriptionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityDescription1TestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityDescription1, nullptr);
    using OneTestStep = std::tuple<Ark_Resource, std::string>;
    std::string inputVal1 {"test string 1"}, inputVal2 {"test string 2"};
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Resource>(inputVal1, nullptr), inputVal1},
        {Converter::ArkValue<Ark_Resource>(inputVal2, nullptr), inputVal2},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityDescription1(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_DESCRIPTION_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////// AccessibilityLevel
/*
 * @tc.name: setAccessibilityLevelTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityLevelTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_LEVEL_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_LEVEL_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilityLevelTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityLevelTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityLevel, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("test string 1"), "test string 1"},
        {Converter::ArkValue<Ark_String>("test string 2"), "test string 2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityLevel(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_LEVEL_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////// AccessibilityChecked
/*
 * @tc.name: setAccessibilityCheckedTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilityCheckedTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_CHECKED_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_CHECKED_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilityCheckedTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilityCheckedTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityChecked, nullptr);
    using OneTestStep = std::tuple<Ark_Boolean, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Boolean>(true), "true"},
        {Converter::ArkValue<Ark_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilityChecked(node_, inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_CHECKED_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////// AccessibilitySelected
/*
 * @tc.name: setAccessibilitySelectedTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, setAccessibilitySelectedTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_SELECTED_NAME_TEST);
    EXPECT_EQ(strResult, ATTRIBUTE_SELECTED_DEFAULT_VALUE_TEST);
}

/*
 * @tc.name: setAccessibilitySelectedTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest9, DISABLED_setAccessibilitySelectedTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilitySelected, nullptr);
    using OneTestStep = std::tuple<Ark_Boolean, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Boolean>(true), "true"},
        {Converter::ArkValue<Ark_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setAccessibilitySelected(node_, inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_SELECTED_NAME_TEST);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}
}
