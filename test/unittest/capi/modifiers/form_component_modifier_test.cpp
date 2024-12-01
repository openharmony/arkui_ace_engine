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
const auto FORM_COMPONENT_ID_KEY = "id";
const auto FORM_COMPONENT_ID_STRING_KEY = "idString";

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureFormSizeDimensionValidValues = {
    { "100.00vp", Converter::ArkValue<Ark_Number>(100), "100.00vp" },
    { "0.00vp", Converter::ArkValue<Ark_Number>(0), "0.00vp" },
    { "-100.00vp", Converter::ArkValue<Ark_Number>(-100), "-100.00vp" },
    { "12.34vp", Converter::ArkValue<Ark_Number>(12.34), "12.34vp" },
    { "-56.78vp", Converter::ArkValue<Ark_Number>(-56.78), "-56.78vp" },
};

std::vector<std::tuple<std::string, Ark_FormDimension, std::string>> testFixtureEnumFormDimensionValidValues = {
    { "ARK_FORM_DIMENSION_DIMENSION_1_2", ARK_FORM_DIMENSION_DIMENSION_1_2, "1" },
    { "ARK_FORM_DIMENSION_DIMENSION_2_2", ARK_FORM_DIMENSION_DIMENSION_2_2, "2" },
    { "ARK_FORM_DIMENSION_DIMENSION_2_4", ARK_FORM_DIMENSION_DIMENSION_2_4, "3" },
    { "ARK_FORM_DIMENSION_DIMENSION_4_4", ARK_FORM_DIMENSION_DIMENSION_4_4, "4" },
    { "ARK_FORM_DIMENSION_DIMENSION_2_1", ARK_FORM_DIMENSION_DIMENSION_2_1, "5" },
    { "ARK_FORM_DIMENSION_DIMENSION_1_1", ARK_FORM_DIMENSION_DIMENSION_1_1, "6" },
    { "ARK_FORM_DIMENSION_DIMENSION_6_4", ARK_FORM_DIMENSION_DIMENSION_6_4, "7" },
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

std::vector<std::tuple<int64_t, uint32_t, std::string>> testFixtureFormIngoCallbackTestValues = {
    { 1, 1, "1" },
    { -1, -1, "-1" },
    { 151, 151, "151" },
    { -1050, -1, "-1050" },
    { 2147483647, 2147483647, "2147483647" },
    { 4294967295, -1, "4294967295" },
    { 141733920767, -1, "141733920767" },
    { 9007199254740992, -1, "9007199254740992" },
    { 19007199254740992, -1, "19007199254740992" },
    { 9223372036854775807, -1, "9223372036854775807" },
};

std::string ToJson(const int64_t& id)
{
    auto json = JsonUtil::Create(true);
    json->Put(FORM_COMPONENT_ID_KEY, std::to_string(id).c_str());
    json->Put(FORM_COMPONENT_ID_STRING_KEY, std::to_string(id).c_str());
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
    Ark_Literal_Number_height_width initValueSize;

    // Initial setup
    initValueSize.width = std::get<1>(testFixtureFormSizeDimensionValidValues[0]);
    initValueSize.height = std::get<1>(testFixtureFormSizeDimensionValidValues[0]);

    auto checkValue = [this, &initValueSize](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Literal_Number_height_width inputValueSize = initValueSize;
        inputValueSize.width = value;
        modifier_->setSize(node_, &inputValueSize);
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
    Ark_Literal_Number_height_width initValueSize;
    // Initial setup
    initValueSize.width = std::get<1>(testFixtureFormSizeDimensionValidValues[0]);
    initValueSize.height = std::get<1>(testFixtureFormSizeDimensionValidValues[0]);
    auto checkValue = [this, &initValueSize](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Literal_Number_height_width inputValueSize = initValueSize;
        inputValueSize.height = value;
        modifier_->setSize(node_, &inputValueSize);
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
HWTEST_F(FormComponentModifierTest, setModuleNameTestModuleNameValidValues, TestSize.Level1)
{
    Ark_String initValueModuleName;

    // Initial setup
    initValueModuleName = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    auto checkValue = [this, &initValueModuleName](
                          const std::string& input, const Ark_String& value, const std::string& expectedStr) {
        Ark_String inputValueModuleName = initValueModuleName;
        inputValueModuleName = value;
        modifier_->setModuleName(node_, &inputValueModuleName);
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
HWTEST_F(FormComponentModifierTest, setAllowUpdateTestAllowUpdateValidValues, TestSize.Level1)
{
    Ark_Boolean initValueAllowUpdate;

    // Initial setup
    initValueAllowUpdate = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);
    auto checkValue = [this, &initValueAllowUpdate](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueAllowUpdate = initValueAllowUpdate;
        inputValueAllowUpdate = value;
        modifier_->setAllowUpdate(node_, inputValueAllowUpdate);
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
HWTEST_F(FormComponentModifierTest, setDimensionTestDimensionValidValues, TestSize.Level1)
{
    Ark_FormDimension initValueDimension;

    // Initial setup
    initValueDimension = std::get<1>(testFixtureEnumFormDimensionValidValues[0]);

    auto checkValue = [this, &initValueDimension](
                          const std::string& input, const Ark_FormDimension& value, const std::string& expectedStr) {
        Ark_FormDimension inputValueDimension = initValueDimension;
        inputValueDimension = value;

        modifier_->setDimension(node_, inputValueDimension);
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
        modifier_->setDimension(node_, inputValueDimension);
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
HWTEST_F(FormComponentModifierTest, setVisibilityTestVisibilityValidValues, TestSize.Level1)
{
    Ark_Visibility initValueVisibility;

    // Initial setup
    initValueVisibility = std::get<1>(testFixtureEnumFormVisibilityValidValues[0]);

    auto checkValue = [this, &initValueVisibility](
                          const std::string& input, const Ark_Visibility& value, const std::string& expectedStr) {
        Ark_Visibility inputValueVisibility = initValueVisibility;
        inputValueVisibility = value;

        modifier_->setVisibility(node_, inputValueVisibility);
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
        modifier_->setVisibility(node_, inputValueVisibility);
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
HWTEST_F(FormComponentModifierTest, setOnAcquiredTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnAcquired, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<FormEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static std::optional<std::pair<uint32_t, std::string>> formInfo = std::nullopt;
    auto onAcquired = [](const Ark_Int32 resourceId, const Ark_FormCallbackInfo parameter) {

       std::pair<uint32_t, std::string> info; 
       
       
       // test!!!
       std::printf("callback: opt: %d\n", formInfo.has_value());
       // test!!!

       
       info.first =  Converter::Convert<uint32_t>(parameter.id);
       info.second = Converter::Convert<std::string>(parameter.idString);
       formInfo = info;


       // test!!!
       std::printf("callback: 2 first: %d second: %s opt %d\n", formInfo->first, formInfo->second.c_str(), formInfo.has_value());
       // test!!!


    
    };
    Callback_FormCallbackInfo_Void func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onAcquired
    };


    // test!!!
    std::printf("test: \n");
    // test!!!


    modifier_->setOnAcquired(node_, &func);
    
    // test!!!
    std::printf("test: 2\n");
    // test!!!

    for (const auto& [actual, expectedNum, expectedStr] : testFixtureFormIngoCallbackTestValues) {
        formInfo = std::nullopt;

        auto testValue = ToJson(actual);

        // test!!!
        std::printf("test: 3 testValue: %s\n", testValue.c_str());
        // test!!!

        eventHub->FireOnAcquired(testValue);

       // test!!!
       std::printf("test: 4 first: %d second: %s opt %d\n", formInfo->first, formInfo->second.c_str(), formInfo.has_value());
       // test!!!

        EXPECT_TRUE(formInfo.has_value());
        EXPECT_EQ(formInfo->first, expectedNum);
        EXPECT_EQ(formInfo->second, expectedStr);

    }
// for (const auto& testValue : CHANGE_EVENT_TEST_PLAN) {
//         DatePickerChangeEvent event(testValue.first.ToString(true));
//         eventHub->FireChangeEvent(&event);

//         EXPECT_TRUE(selectedDate.has_value());
//         EXPECT_EQ(selectedDate->GetYear(), testValue.second.GetYear());
//         EXPECT_EQ(selectedDate->GetMonth(), testValue.second.GetMonth());
//         EXPECT_EQ(selectedDate->GetDay(), testValue.second.GetDay());
//     };

// //========================
// void (*call)(const Ark_Int32 resourceId, const Ark_FormCallbackInfo parameter);
// void FireOnAcquired(const std::string& param) const
// //========================
//     static std::optional<PickerDate> selectedDate = std::nullopt;
//     auto onDateChange = [](const Ark_Int32 resourceId, const Ark_Date parameter) {
//         selectedDate = Converter::OptConvert<PickerDate>(parameter);
//     };
//     Callback_Date_Void func = {
//         .resource = Ark_CallbackResource {
//             .resourceId = frameNode->GetId(),
//             .hold = nullptr,
//             .release = nullptr,
//         },
//         .call = onDateChange
//     };

//     modifier_->setOnDateChange(node_, &func);

//     for (const auto& testValue : CHANGE_EVENT_TEST_PLAN) {
//         DatePickerChangeEvent event(testValue.first.ToString(true));
//         eventHub->FireChangeEvent(&event);

//         EXPECT_TRUE(selectedDate.has_value());
//         EXPECT_EQ(selectedDate->GetYear(), testValue.second.GetYear());
//         EXPECT_EQ(selectedDate->GetMonth(), testValue.second.GetMonth());
//         EXPECT_EQ(selectedDate->GetDay(), testValue.second.GetDay());
//     };
}

/*
 * @tc.name: emptyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, emptyTest, TestSize.Level1)
{
    std::printf("\n\n\n\n\n");
    char *p = nullptr;
    char s = p[2];
    p[20] = s;
    
}
} // namespace OHOS::Ace::NG
