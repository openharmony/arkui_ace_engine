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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "generated/test_fixtures.h"
#include "generated/type_helpers.h"
#include "core/components_ng/pattern/form/form_event_hub.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;

namespace  {
const auto ATTRIBUTE_CONSTRUCTOR_NAME = "constructor";
const auto ATTRIBUTE_SIZE_NAME = "size";
const auto ATTRIBUTE_SIZE_I_WIDTH_NAME = "width";
const auto ATTRIBUTE_SIZE_I_WIDTH_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_SIZE_I_HEIGHT_NAME = "height";
const auto ATTRIBUTE_SIZE_I_HEIGHT_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_MODULE_NAME_NAME = "moduleName";
const auto ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALLOW_UPDATE_NAME = "allowUpdate";
const auto ATTRIBUTE_ALLOW_UPDATE_DEFAULT_VALUE = "true";
const auto ATTRIBUTE_DIMENSION_NAME = "dimension";
const auto ATTRIBUTE_DIMENSION_DEFAULT_VALUE = "-1";
const auto ATTRIBUTE_VISIBILITY_NAME = "visibility";
const auto ATTRIBUTE_VISIBILITY_DEFAULT_VALUE = "Visibility.Visible";
const auto FORM_ON_ACQUIRED_ID_KEY = "id";
const auto FORM_ON_ACQUIRED_ID_STRING_KEY = "idString";
const auto FORM_ON_ERROR_CODE_KEY = "errcode";
const auto FORM_ON_ERROR_MSG_KEY = "msg";
const auto FORM_EMPTY_STRING = "";

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureFormSizeDimensionValidValues = {
    { "100", Converter::ArkValue<Ark_Float64>(100), "100.00vp" },
    { "0", Converter::ArkValue<Ark_Float64>(0), "0.00vp" },
    { "-100", Converter::ArkValue<Ark_Float64>(-100), "-100.00vp" },
    { "12.34", Converter::ArkValue<Ark_Float64>(12.34), "12.34vp" },
    { "-56.78", Converter::ArkValue<Ark_Float64>(-56.78), "-56.78vp" },
};

std::vector<std::tuple<std::string, Ark_FormDimension, std::string>> testFixtureEnumFormDimensionValidValues = {
    { "ARK_FORM_DIMENSION_DIMENSION_1_2", ARK_FORM_DIMENSION_DIMENSION_1_2, "0" },
    { "ARK_FORM_DIMENSION_DIMENSION_2_2", ARK_FORM_DIMENSION_DIMENSION_2_2, "1" },
    { "ARK_FORM_DIMENSION_DIMENSION_2_4", ARK_FORM_DIMENSION_DIMENSION_2_4, "2" },
    { "ARK_FORM_DIMENSION_DIMENSION_4_4", ARK_FORM_DIMENSION_DIMENSION_4_4, "3" },
    { "ARK_FORM_DIMENSION_DIMENSION_1_1", ARK_FORM_DIMENSION_DIMENSION_1_1, "6" },
    { "ARK_FORM_DIMENSION_DIMENSION_6_4", ARK_FORM_DIMENSION_DIMENSION_6_4, "7" },
    { "ARK_FORM_DIMENSION_DIMENSION_2_3", ARK_FORM_DIMENSION_DIMENSION_2_3, "8" },
    { "ARK_FORM_DIMENSION_DIMENSION_3_3", ARK_FORM_DIMENSION_DIMENSION_3_3, "9" },
};

std::vector<std::tuple<std::string, Ark_FormDimension>> testFixtureEnumFormDimensionInvalidValues = {
    { "-1", static_cast<Ark_FormDimension>(-1) },
    { "INT_MAX", static_cast<Ark_FormDimension>(INT_MAX) },
};

std::vector<std::tuple<std::string, Ark_Visibility, std::string>> testFixtureEnumFormVisibilityValidValues = {
    { "ARK_VISIBILITY_VISIBLE", Ark_Visibility::ARK_VISIBILITY_VISIBLE, "Visibility.Hidden" },
    { "ARK_VISIBILITY_HIDDEN", Ark_Visibility::ARK_VISIBILITY_HIDDEN, "Visibility.Hidden" },
    { "ARK_VISIBILITY_NONE", Ark_Visibility::ARK_VISIBILITY_NONE, "Visibility.None" },
};

std::vector<std::tuple<std::string, Ark_Visibility>> testFixtureEnumFormVisibilityInvalidValues = {
    { "-1", static_cast<Ark_Visibility>(-1) },
    { "INT_MAX", static_cast<Ark_Visibility>(INT_MAX) },
};

std::vector<std::tuple<int64_t, int64_t, std::string>> testFixtureFormOnAcquiredCallbackTestValues = {
    { 1, 1, "1" },
    { -1, -1, "-1" },
    { 151, 151, "151" },
    { -1050, -1050, "-1050" },
    { 2147483647, 2147483647, "2147483647" },
    { -2147483647, -2147483647, "-2147483647" },
    { 4294967295, 4294967295, "4294967295" },
    { -4294967295, -4294967295, "-4294967295" },
    { 141733920767, 141733920767, "141733920767" },
    { -141733920767, -141733920767, "-141733920767" },
    { 9007199254740992, 9007199254740992, "9007199254740992" },
    { -9007199254740992, -9007199254740992, "-9007199254740992" },
    { 19007199254740992, 19007199254740992, "19007199254740992" },
    { -19007199254740992, -19007199254740992, "-19007199254740992" },
    { 9223372036854775807, 9223372036854775807, "9223372036854775807" },
    { -9223372036854775807, -9223372036854775807, "-9223372036854775807" },
};

std::vector<std::tuple<std::int32_t, std::string, std::int32_t>> testFixtureFormOnErrorCallbackTestValues = {
    { 1, "error message 1", 1 },
    { -1, "error another -1", -1 },
    { 151, "error message 151", 151 },
    { -1050, "error invalid code -1050", -1050 },
    { 2147483647, "error message 2147483647", 2147483647 },
    { -2147483648, "error message -2147483647", -2147483648 },
};

std::vector<std::tuple<std::string, Ark_String, std::string>> testFixtureFormNameValidValues = {
    { "valid_name", Converter::ArkValue<Ark_String>("valid_name"), "valid_name" },
    { "number_name", Converter::ArkValue<Ark_String>("12345"), "12345" },
    { "empty_name", Converter::ArkValue<Ark_String>(""), "" },
};

std::string ToJson(const int64_t& id)
{
    auto json = JsonUtil::Create(true);
    json->Put(FORM_ON_ACQUIRED_ID_KEY, std::to_string(id).c_str());
    json->Put(FORM_ON_ACQUIRED_ID_STRING_KEY, std::to_string(id).c_str());
    return json->ToString();
}

std::string ToJson(const int64_t& code, const std::string& msg)
{
    auto json = JsonUtil::Create(true);
    json->Put(FORM_ON_ERROR_CODE_KEY, std::to_string(code).c_str());
    json->Put(FORM_ON_ERROR_MSG_KEY, msg.c_str());
    return json->ToString();
}
} // namespace
class FormComponentModifierTest : public ModifierTestBase<GENERATED_ArkUIFormComponentModifier,
    &GENERATED_ArkUINodeModifiers::getFormComponentModifier, GENERATED_ARKUI_FORM_COMPONENT> {
    void SetUp(void) override
    {
        ModifierTestBase::SetUp();
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        frameNode->MarkModifyDone();
    }
};

/*
 * @tc.name: setSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto resultConstructor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
    auto resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(resultConstructor, ATTRIBUTE_SIZE_NAME);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SIZE_I_WIDTH_DEFAULT_VALUE) <<
        "Default value for attribute 'size.width'" << " resultStr: " << resultStr.c_str();
    resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SIZE_I_HEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'size.height'" << " resultStr: " << resultStr.c_str();
}

/*
 * @tc.name: setSizeTestSizeWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setSizeTestSizeWidthValidValues, TestSize.Level1)
{
    Ark_FormSize initValueSize;

    // Initial setup
    initValueSize.width = std::get<1>(testFixtureFormSizeDimensionValidValues[0]);
    initValueSize.height = std::get<1>(testFixtureFormSizeDimensionValidValues[0]);

    auto checkValue = [this, &initValueSize](
                          const std::string& input, const Ark_Float64& value, const std::string& expectedStr) {
        Ark_FormSize inputValueSize = initValueSize;
        inputValueSize.width = value;
        auto optValue = Converter::ArkValue<Opt_FormSize>(inputValueSize);
        modifier_->setSize(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultConstructor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(resultConstructor, ATTRIBUTE_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSize, attribute: size.width";
    };
    for (auto& [input, value, expected] : testFixtureFormSizeDimensionValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setSizeTestSizeHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setSizeTestSizeHeightValidValues, TestSize.Level1)
{
    Ark_FormSize initValueSize;
    // Initial setup
    initValueSize.width = std::get<1>(testFixtureFormSizeDimensionValidValues[0]);
    initValueSize.height = std::get<1>(testFixtureFormSizeDimensionValidValues[0]);
    auto checkValue = [this, &initValueSize](
                          const std::string& input, const Ark_Float64& value, const std::string& expectedStr) {
        Ark_FormSize inputValueSize = initValueSize;
        inputValueSize.height = value;
        auto optValue = Converter::ArkValue<Opt_FormSize>(inputValueSize);
        modifier_->setSize(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultConstructor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(resultConstructor, ATTRIBUTE_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSize, attribute: size.height";
    };

    for (auto& [input, value, expected] : testFixtureFormSizeDimensionValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setModuleNameTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setModuleNameTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    auto resultConstructor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
    resultStr = GetAttrValue<std::string>(resultConstructor, ATTRIBUTE_MODULE_NAME_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE) << "Default value for attribute 'moduleName'";
}

/*
 * @tc.name: setModuleNameTestModuleNameValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setModuleNameTestModuleNameValidValues, TestSize.Level1)
{
    Ark_String initValueModuleName;

    // Initial setup
    initValueModuleName = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    auto checkValue = [this, &initValueModuleName](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueModuleName = initValueModuleName;
        inputValueModuleName = value;
        auto optValue = Converter::ArkValue<Opt_String>(inputValueModuleName);
        modifier_->setModuleName(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultConstructor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultConstructor, ATTRIBUTE_MODULE_NAME_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setModuleName, attribute: moduleName";
    };
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setAllowUpdateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setAllowUpdateTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    auto resultConstructor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
    resultStr = GetAttrValue<std::string>(resultConstructor, ATTRIBUTE_ALLOW_UPDATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALLOW_UPDATE_DEFAULT_VALUE) << "Default value for attribute 'allowUpdate'";
}

/*
 * @tc.name: setAllowUpdateTestAllowUpdateValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setAllowUpdateTestAllowUpdateValidValues, TestSize.Level1)
{
    Ark_Boolean initValueAllowUpdate;

    // Initial setup
    initValueAllowUpdate = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    auto checkValue = [this, &initValueAllowUpdate](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueAllowUpdate = initValueAllowUpdate;
        inputValueAllowUpdate = value;
        auto optValue = Converter::ArkValue<Opt_Boolean>(inputValueAllowUpdate);
        modifier_->setAllowUpdate(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultConstructor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultConstructor, ATTRIBUTE_ALLOW_UPDATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAllowUpdate, attribute: allowUpdate";
    };
    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}
/*
 * @tc.name: setDimensionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setDimensionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    auto resultConstructor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
    resultStr = GetAttrValue<std::string>(resultConstructor, ATTRIBUTE_DIMENSION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIMENSION_DEFAULT_VALUE) << "Default value for attribute 'dimension'";
}

/*
 * @tc.name: setDimensionTestDimensionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setDimensionTestDimensionValidValues, TestSize.Level1)
{
    Ark_FormDimension initValueDimension;

    // Initial setup
    initValueDimension = std::get<1>(testFixtureEnumFormDimensionValidValues[0]);

    auto checkValue = [this, &initValueDimension](
                          const std::string& input, const Ark_FormDimension& value, const std::string& expectedStr) {
        Ark_FormDimension inputValueDimension = initValueDimension;
        inputValueDimension = value;
        auto optValue = Converter::ArkValue<Opt_FormDimension>(inputValueDimension);
        modifier_->setDimension(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultConstructor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultConstructor, ATTRIBUTE_DIMENSION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDimension, attribute: dimension";
    };
    for (auto& [input, value, expected] : testFixtureEnumFormDimensionValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDimensionTestDimensionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setDimensionTestDimensionInvalidValues, TestSize.Level1)
{
    Ark_FormDimension initValueDimension;

    // Initial setup
    initValueDimension = std::get<1>(testFixtureEnumFormDimensionValidValues[0]);

    auto checkValue = [this, &initValueDimension](const std::string& input, const Ark_FormDimension& value) {
        Ark_FormDimension inputValueDimension = initValueDimension;

        inputValueDimension = value;
        auto optValue = Converter::ArkValue<Opt_FormDimension>(inputValueDimension);
        modifier_->setDimension(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultConstructor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultConstructor, ATTRIBUTE_DIMENSION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DIMENSION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDimension, attribute: dimension";
    };
    for (auto& [input, value] : testFixtureEnumFormDimensionInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setVisibilityTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setVisibilityTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VISIBILITY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VISIBILITY_DEFAULT_VALUE) << "Default value for attribute 'visibility'";
}

/*
 * @tc.name: setVisibilityTestVisibilityValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setVisibilityTestVisibilityValidValues, TestSize.Level1)
{
    Ark_Visibility initValueVisibility;

    // Initial setup
    initValueVisibility = std::get<1>(testFixtureEnumFormVisibilityValidValues[0]);

    auto checkValue = [this, &initValueVisibility](
                          const std::string& input, const Ark_Visibility& value, const std::string& expectedStr) {
        Ark_Visibility inputValueVisibility = initValueVisibility;
        inputValueVisibility = value;
        auto optValue = Converter::ArkValue<Opt_Visibility>(inputValueVisibility);
        modifier_->setVisibility(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VISIBILITY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setVisibility, attribute: visibility";
    };
    for (auto& [input, value, expected] : testFixtureEnumFormVisibilityValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setVisibilityTestVisibilityInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setVisibilityTestVisibilityInvalidValues, TestSize.Level1)
{
    Ark_Visibility initValueVisibility;

    // Initial setup
    initValueVisibility = std::get<1>(testFixtureEnumFormVisibilityValidValues[0]);

    auto checkValue = [this, &initValueVisibility](const std::string& input, const Ark_Visibility& value) {
        Ark_Visibility inputValueVisibility = initValueVisibility;

        inputValueVisibility = value;
        auto optValue = Converter::ArkValue<Opt_Visibility>(inputValueVisibility);
        modifier_->setVisibility(node_, &optValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VISIBILITY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_VISIBILITY_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setVisibility, attribute: visibility";
    };
    for (auto& [input, value] : testFixtureEnumFormVisibilityInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setOnAcquiredTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setOnAcquiredTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnAcquired, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<FormEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::optional<std::pair<int64_t, std::string>> formInfo = std::nullopt;
    auto onAcquired = [](const Ark_Int32 resourceId, const Ark_FormCallbackInfo parameter) {
        std::pair<int64_t, std::string> info;
        info.first = Converter::Convert<int64_t>(parameter.id);
        info.second = Converter::Convert<std::string>(parameter.idString);
        formInfo = info;
    };
    Callback_FormCallbackInfo_Void func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onAcquired
    };
    auto optFunc = Converter::ArkValue<Opt_Callback_FormCallbackInfo_Void>(func);
    modifier_->setOnAcquired(node_, &optFunc);
    for (const auto& [actual, expectedNum, expectedStr] : testFixtureFormOnAcquiredCallbackTestValues) {
        formInfo = std::nullopt;
        auto testValue = ToJson(actual);
        eventHub->FireOnAcquired(testValue);
        EXPECT_TRUE(formInfo.has_value());
        EXPECT_EQ(formInfo->first, expectedNum);
        EXPECT_EQ(formInfo->second, expectedStr);
    }
}

/*
 * @tc.name: setOnErrorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setOnErrorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnError, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<FormEventHub>();
    ASSERT_NE(eventHub, nullptr);
    static std::optional<std::pair<int32_t, std::string>> formInfo = std::nullopt;
    auto onError = [](const Ark_Int32 resourceId, const Ark_ErrorInformation parameter) {
        std::pair<int32_t, std::string> info;
        info.first = Converter::Convert<int32_t>(parameter.errcode);
        info.second = Converter::Convert<std::string>(parameter.msg);
        formInfo = info;
    };
    Callback_ErrorInformation_Void func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onError
    };
    auto optFunc = Converter::ArkValue<Opt_Callback_ErrorInformation_Void>(func);
    modifier_->setOnError(node_, &optFunc);
    for (const auto& [code, msg, expected] : testFixtureFormOnErrorCallbackTestValues) {
        formInfo = std::nullopt;
        auto testValue = ToJson(code, msg);
        eventHub->FireOnError(testValue);

        EXPECT_TRUE(formInfo.has_value());
        EXPECT_EQ(formInfo->first, expected);
        EXPECT_EQ(formInfo->second, msg);
    }
}

/*
 * @tc.name: setOnUninstallTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setOnUninstallTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnUninstall, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<FormEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::optional<std::pair<int64_t, std::string>> formInfo = std::nullopt;
    auto onUninstall = [](const Ark_Int32 resourceId, const Ark_FormCallbackInfo parameter) {
        std::pair<int64_t, std::string> info;
        info.first = Converter::Convert<int64_t>(parameter.id);
        info.second = Converter::Convert<std::string>(parameter.idString);
        formInfo = info;
    };
    Callback_FormCallbackInfo_Void func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onUninstall
    };
    auto optFunc = Converter::ArkValue<Opt_Callback_FormCallbackInfo_Void>(func);
    modifier_->setOnUninstall(node_, &optFunc);
    for (const auto& [actual, expectedNum, expectedStr] : testFixtureFormOnAcquiredCallbackTestValues) {
        formInfo = std::nullopt;
        auto testValue = ToJson(actual);
        eventHub->FireOnUninstall(testValue);
        EXPECT_TRUE(formInfo.has_value());
        EXPECT_EQ(formInfo->first, expectedNum);
        EXPECT_EQ(formInfo->second, expectedStr);
    }
}

/*
 * @tc.name: setOnLoadTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setOnLoadTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnLoad, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<FormEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static constexpr int32_t contextId = 123;
    static std::optional<bool> formInfo = std::nullopt;
    auto onLoad = [](const Ark_Int32 resourceId) {
        formInfo = true;
        EXPECT_EQ(resourceId, contextId);
    };
    VoidCallback func = {
        .resource = Ark_CallbackResource {
            .resourceId = contextId,
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onLoad
    };
    const auto optFunc = Converter::ArkValue<Opt_VoidCallback>(func);
    modifier_->setOnLoad(node_, &optFunc);
    formInfo = std::nullopt;
    eventHub->FireOnLoad(FORM_EMPTY_STRING);
    EXPECT_TRUE(formInfo.has_value());
    EXPECT_TRUE(*formInfo);
}

/*
 * @tc.name: setOnRouterTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setOnRouterTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnRouter, nullptr);
}

/*
 * @tc.name: setFormComponentOptionsModuleNameValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsModuleNameValues, TestSize.Level1)
{
    Ark_FormInfo initValue;
    // Initial setup
    int64_t id = -1;
    initValue.id = Converter::ArkUnion<Ark_Union_I64_String, Ark_Int64>(id);
    initValue.name = Converter::ArkValue<Ark_String>(FORM_EMPTY_STRING);
    initValue.bundle = Converter::ArkValue<Ark_String>(FORM_EMPTY_STRING);
    initValue.ability = Converter::ArkValue<Ark_String>(FORM_EMPTY_STRING);
    initValue.module = Converter::ArkValue<Ark_String>(FORM_EMPTY_STRING);
    initValue.dimension = Converter::ArkValue<Opt_FormDimension>(Ark_Empty());
    initValue.temporary = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    initValue.want = Converter::ArkValue<Opt_Want>(Ark_Empty());
    initValue.renderingMode = Converter::ArkValue<Opt_FormRenderingMode>(Ark_Empty());
    initValue.shape = Converter::ArkValue<Opt_FormShape>(Ark_Empty());
    auto checkValue = [this, &initValue](
                          const std::string& input, const Ark_String& value, const std::string& expected) {
        Ark_FormInfo inputValue = initValue;
        inputValue.module = value;
        modifier_->setFormComponentOptions(node_, &inputValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultConstructor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto result = GetAttrValue<std::string>(resultConstructor, ATTRIBUTE_MODULE_NAME_NAME);
        EXPECT_EQ(result, expected) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: module";
    };
    for (auto& [input, value, expected] : testFixtureFormNameValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setFormComponentOptionsDimensionValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, DISABLED_setFormComponentOptionsDimensionValues, TestSize.Level1)
{
    Ark_FormInfo initValue;
    // Initial setup
    int64_t id = -1;
    initValue.id = Converter::ArkUnion<Ark_Union_I64_String, Ark_Int64>(id);
    initValue.name = Converter::ArkValue<Ark_String>(FORM_EMPTY_STRING);
    initValue.bundle = Converter::ArkValue<Ark_String>(FORM_EMPTY_STRING);
    initValue.ability = Converter::ArkValue<Ark_String>(FORM_EMPTY_STRING);
    initValue.module = Converter::ArkValue<Ark_String>(FORM_EMPTY_STRING);
    initValue.dimension = Converter::ArkValue<Opt_FormDimension>(Ark_Empty());
    initValue.temporary = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    initValue.want = Converter::ArkValue<Opt_Want>(Ark_Empty());
    initValue.renderingMode = Converter::ArkValue<Opt_FormRenderingMode>(Ark_Empty());
    initValue.shape = Converter::ArkValue<Opt_FormShape>(Ark_Empty());
    auto checkValue = [this, &initValue](
                          const std::string& input, const Ark_FormDimension& value, const std::string& expected) {
        Ark_FormInfo inputValue = initValue;
        inputValue.dimension = Converter::ArkValue<Opt_FormDimension>(value);
        modifier_->setFormComponentOptions(node_, &inputValue);
        auto jsonValue = GetJsonValue(node_);
        auto resultConstructor = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto result = GetAttrValue<std::string>(resultConstructor, ATTRIBUTE_DIMENSION_NAME);
        EXPECT_EQ(result, expected) <<
            "Input value is: " << input << ", method: setFormComponentOptions, attribute: dimension";
    };
    for (auto& [input, value, expected] : testFixtureEnumFormDimensionValidValues) {
        checkValue(input, value, expected);
    }
    auto presetValue = initValue;
    auto input = std::get<1>(testFixtureEnumFormDimensionValidValues[0]);
    auto expected = std::get<2>(testFixtureEnumFormDimensionValidValues[0]);
    presetValue.dimension = Converter::ArkValue<Opt_FormDimension>(input);
    modifier_->setFormComponentOptions(node_, &presetValue);
    for (auto& [input, value] : testFixtureEnumFormDimensionInvalidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setOnUpdateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setOnUpdateTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnUpdate, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<FormEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::optional<std::pair<int64_t, std::string>> formInfo = std::nullopt;
    auto onUpdate = [](const Ark_Int32 resourceId, const Ark_FormCallbackInfo parameter) {
        std::pair<int64_t, std::string> info;
        info.first = Converter::Convert<int64_t>(parameter.id);
        info.second = Converter::Convert<std::string>(parameter.idString);
        formInfo = info;
    };
    auto optFunc = Converter::ArkValue<Opt_Callback_FormCallbackInfo_Void>(
        Converter::ArkValue<Callback_FormCallbackInfo_Void>(onUpdate, frameNode->GetId()));

    modifier_->setOnUpdate(node_, &optFunc);
    for (const auto& [actual, expectedNum, expectedStr] : testFixtureFormOnAcquiredCallbackTestValues) {
        formInfo = std::nullopt;
        auto testValue = ToJson(actual);
        eventHub->FireOnUpdate(testValue);
        EXPECT_TRUE(formInfo.has_value());
        EXPECT_EQ(formInfo->first, expectedNum);
        EXPECT_EQ(formInfo->second, expectedStr);
    }
}
} // namespace OHOS::Ace::NG
