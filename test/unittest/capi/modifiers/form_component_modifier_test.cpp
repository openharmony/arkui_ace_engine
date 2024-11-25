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

#include "core/interfaces/arkoala/utility/reverse_converter.h"

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

std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureFormSizeDimensionValidValues = {
    { "100.00vp", Converter::ArkValue<Ark_Number>(100), "100.00vp" },
    { "0.00vp", Converter::ArkValue<Ark_Number>(0), "0.00vp" },
    { "-100.00vp", Converter::ArkValue<Ark_Number>(-100), "-100.00vp" },
    { "12.34vp", Converter::ArkValue<Ark_Number>(12.34), "12.34vp" },
    { "-56.78vp", Converter::ArkValue<Ark_Number>(-56.78), "-56.78vp" },
};



// test!!!
std::ofstream out2("test_json_output.txt");    



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

    // test!!!
        std::unique_ptr<JsonValue> jsonValue2 = GetJsonValue(node_);
        auto resultConstructor2 =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue2, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultSize2 = GetAttrValue<std::unique_ptr<JsonValue>>(resultConstructor2, ATTRIBUTE_SIZE_NAME);
        out2 << "\ntest_json_set_size_default.txt === \n";
        auto resultStr2 = GetAttrValue<std::string>(resultSize2, ATTRIBUTE_SIZE_I_WIDTH_NAME);
        auto resultStr3 = GetAttrValue<std::string>(resultSize2, ATTRIBUTE_SIZE_I_HEIGHT_NAME);
        out2 << "size.width: " << resultStr2.c_str() << " " << ATTRIBUTE_SIZE_I_WIDTH_DEFAULT_VALUE << " ";
        out2 << "size.height: " << resultStr3.c_str() << " " << ATTRIBUTE_SIZE_I_HEIGHT_DEFAULT_VALUE << std::endl;

        std::printf("\ntest: constructor: resultConstructor2: %s", resultConstructor2->ToString().c_str());
        std::printf("\ntest: size: resultSize2: %s", resultSize2->ToString().c_str());
        std::printf("\ntest: size width: resultStr2: %s", resultStr2.c_str());
        std::printf("\ntest: size height: resultStr3: %s", resultStr3.c_str());
        out2 << "   " << jsonValue2->ToString().c_str();
    // test!!!

    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto resultConstructor =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
    auto resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(resultConstructor, ATTRIBUTE_SIZE_NAME);
    std::string resultStr;

    std::printf("\ntest: constructor: resultConstructor: %s", resultConstructor->ToString().c_str());
    std::printf("\ntest: size: resultSize: %s", resultSize->ToString().c_str());
    resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_WIDTH_NAME);
    std::printf("\ntest: size width: resultStr: %s", resultStr.c_str());
    EXPECT_EQ(resultStr, ATTRIBUTE_SIZE_I_WIDTH_DEFAULT_VALUE) << "Default value for attribute 'size.width'" << " resultStr: " << resultStr.c_str();


    resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_HEIGHT_NAME);
    std::printf("\ntest: size height: resultStr: %s", resultStr.c_str());
    EXPECT_EQ(resultStr, ATTRIBUTE_SIZE_I_HEIGHT_DEFAULT_VALUE) << "Default value for attribute 'size.height'" << " resultStr: " << resultStr.c_str();
}

/*
 * @tc.name: setSizeTestSizeWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setSizeTestSizeWidthValidValues, TestSize.Level1)
{
    Ark_Literal_Number_height_width initValueSize;

    // Initial setup
    initValueSize.width = std::get<1>( testFixtureFormSizeDimensionValidValues[0]);
    initValueSize.height = std::get<1>(testFixtureFormSizeDimensionValidValues[0]);

    auto checkValue = [this, &initValueSize](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Literal_Number_height_width inputValueSize = initValueSize;

        inputValueSize.width = value;
        modifier_->setSize(node_, &inputValueSize);
    // test!!!
        auto jsonValue2 = GetJsonValue(node_);
        auto resultConstructor2 =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue2, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultSize2 = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue2, ATTRIBUTE_SIZE_NAME);
        auto resultStr2 = GetAttrValue<std::string>(resultSize2, ATTRIBUTE_SIZE_I_WIDTH_NAME);
        out2 << "\nsize.width: " << input.c_str() << " read: " << resultStr2.c_str()  <<  " expected: " << expectedStr.c_str() << std::endl;
        out2 << "   " << jsonValue2->ToString().c_str();
    // test!!!
        
       
        auto jsonValue = GetJsonValue(node_);
        auto resultConstructor =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(resultConstructor, ATTRIBUTE_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setSize, attribute: size.width";
    };

    // test!!!
        out2 << "\n\ntest_json_set_size_width_valid.txt";    
    // test!!!

    for (auto& [input, value, expected] : testFixtureFormSizeDimensionValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setSizeTestSizeHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FormComponentModifierTest, setSizeTestSizeHeightValidValues, TestSize.Level1)
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


    // test!!!
        auto resultConstructor2 =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultSize2 = GetAttrValue<std::unique_ptr<JsonValue>>(resultConstructor2, ATTRIBUTE_SIZE_NAME);
        auto resultStr2 = GetAttrValue<std::string>(resultSize2, ATTRIBUTE_SIZE_I_HEIGHT_NAME);
        out2 << "\nsize.height: " << input.c_str() << " read: " << resultStr2.c_str()  <<  " expected: " << expectedStr.c_str() << std::endl;
        out2 << "   " << jsonValue->ToString().c_str();
    // test!!!


        auto resultConstructor =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultSize = GetAttrValue<std::unique_ptr<JsonValue>>(resultConstructor, ATTRIBUTE_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSize, ATTRIBUTE_SIZE_I_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setSize, attribute: size.height";
    };

    // test!!!
        out2 << "\n\ntest_json_set_size_height_valid.txt";    
    // test!!!
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

    // test!!!
    out2 << "\n\ntest_json_module_name_default.txt";
    auto resultConstructor2 =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
    auto resultStr2 = GetAttrValue<std::string>(resultConstructor2, ATTRIBUTE_MODULE_NAME_NAME);
    out2 << "\nmoduleName: " << resultStr2.c_str() << " expected: " << ATTRIBUTE_MODULE_NAME_DEFAULT_VALUE << std::endl;
    out2 << jsonValue->ToString().c_str();
    // test!!!

    auto resultConstructor =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
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

        std::printf("test: %s\n", input.c_str());
        modifier_->setModuleName(node_, &inputValueModuleName);
        auto jsonValue = GetJsonValue(node_);

        // test!!!
        auto resultConstructor2 =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr2 = GetAttrValue<std::string>(resultConstructor2, ATTRIBUTE_MODULE_NAME_NAME);
        out2 << "\nmoduleName: " << input.c_str() << " read: " << resultStr2.c_str()  <<  " expected: " << expectedStr.c_str() << std::endl;
        out2 << jsonValue->ToString().c_str();
        // test!!!

        auto resultConstructor =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultConstructor, ATTRIBUTE_MODULE_NAME_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setModuleName, attribute: moduleName";
    };


    // test!!!
        out2 << "\n\ntest_json_module_name_valid.txt";
    // test!!!

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


    // test!!!
    out2 << "\n\ntest_json_allow_update_default.txt"; 
    auto resultConstructor2 =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
    auto resultStr2 = GetAttrValue<std::string>(resultConstructor2, ATTRIBUTE_ALLOW_UPDATE_NAME);
    out2 << "\nallowUpdate: " << resultStr2.c_str() << " expected: " << ATTRIBUTE_ALLOW_UPDATE_DEFAULT_VALUE << std::endl;
    out2 << jsonValue->ToString().c_str();
    // test!!!


    auto resultConstructor =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
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


        // test!!!
        auto resultConstructor2 =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr2 = GetAttrValue<std::string>(resultConstructor2, ATTRIBUTE_ALLOW_UPDATE_NAME);
        out2 << "\nallowUpdate: " << input.c_str() << " read: " << resultStr2.c_str()  <<  " expected: " << expectedStr.c_str() << std::endl;
        out2 << jsonValue->ToString().c_str();
        // test!!!


        auto resultConstructor =  GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CONSTRUCTOR_NAME);
        auto resultStr = GetAttrValue<std::string>(resultConstructor, ATTRIBUTE_ALLOW_UPDATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAllowUpdate, attribute: allowUpdate";
    };


        // test!!!
        out2 << "\n\ntest_json_allow_update_valid.txt";
        // test!!!



    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}
} // namespace OHOS::Ace::NG
