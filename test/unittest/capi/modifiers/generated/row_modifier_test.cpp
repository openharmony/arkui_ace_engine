/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_SPACE_NAME = "space";
const auto ATTRIBUTE_SPACE_DEFAULT_VALUE = "0.00px";
} // namespace

class RowModifierTest : public ModifierTestBase<GENERATED_ArkUIRowModifier,
                            &GENERATED_ArkUINodeModifiers::getRowModifier, GENERATED_ARKUI_ROW> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setRowOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setRowOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SPACE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SPACE_DEFAULT_VALUE) << "Default value for attribute 'options.RowOptions.space'";
}

/*
 * @tc.name: setRowOptionsTestOptionsRowOptionsSpaceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setRowOptionsTestOptionsRowOptionsSpaceValidValues, TestSize.Level1)
{
    Opt_Union_RowOptions_RowOptionsV2 initValueOptions;

    // Initial setup
    WriteToUnion<Ark_RowOptions>(WriteTo(initValueOptions)).space = ArkUnion<Opt_Union_String_Number, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Number& value) {
        Opt_Union_RowOptions_RowOptionsV2 inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteToUnion<Ark_RowOptions>(WriteTo(inputValueOptions)).space = value;
        modifier_->setRowOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SPACE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRowOptions, attribute: options.RowOptions.space";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Number, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Number, Ark_String>(value));
    }
}

/*
 * @tc.name: setRowOptionsTestOptionsRowOptionsSpaceInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RowModifierTest, setRowOptionsTestOptionsRowOptionsSpaceInvalidValues, TestSize.Level1)
{
    Opt_Union_RowOptions_RowOptionsV2 initValueOptions;

    // Initial setup
    WriteToUnion<Ark_RowOptions>(WriteTo(initValueOptions)).space = ArkUnion<Opt_Union_String_Number, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Union_String_Number& value) {
        Opt_Union_RowOptions_RowOptionsV2 inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteToUnion<Ark_RowOptions>(WriteTo(inputValueOptions)).space = value;
        modifier_->setRowOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SPACE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_SPACE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRowOptions, attribute: options.RowOptions.space";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Number, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_String_Number, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Number, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Number>());
}
} // namespace OHOS::Ace::NG
