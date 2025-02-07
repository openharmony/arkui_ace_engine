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
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_WIDTH_NAME = "width";
const auto ATTRIBUTE_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_HEIGHT_NAME = "height";
const auto ATTRIBUTE_HEIGHT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_POINTS_NAME = "points";
const auto ATTRIBUTE_POINTS_DEFAULT_VALUE = "!NOT-DEFINED!";
} // namespace

class PolylineModifierTest : public ModifierTestBase<GENERATED_ArkUIPolylineModifier,
                                 &GENERATED_ArkUINodeModifiers::getPolylineModifier, GENERATED_ARKUI_POLYLINE> {
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
 * @tc.name: setPolylineOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolylineModifierTest, setPolylineOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WIDTH_DEFAULT_VALUE) << "Default value for attribute 'options.width'";

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_HEIGHT_DEFAULT_VALUE) << "Default value for attribute 'options.height'";
}

/*
 * @tc.name: setPolylineOptionsTestOptionsWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolylineModifierTest, setPolylineOptionsTestOptionsWidthValidValues, TestSize.Level1)
{
    Opt_PolylineOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).width = ArkUnion<Opt_Union_String_Number, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueOptions).height = ArkUnion<Opt_Union_String_Number, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Number& value) {
        Opt_PolylineOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).width = value;
        modifier_->setPolylineOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WIDTH_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPolylineOptions, attribute: options.width";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Number, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Number, Ark_String>(value));
    }
}

/*
 * @tc.name: setPolylineOptionsTestOptionsWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolylineModifierTest, setPolylineOptionsTestOptionsWidthInvalidValues, TestSize.Level1)
{
    Opt_PolylineOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).width = ArkUnion<Opt_Union_String_Number, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueOptions).height = ArkUnion<Opt_Union_String_Number, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Union_String_Number& value) {
        Opt_PolylineOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).width = value;
        modifier_->setPolylineOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WIDTH_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPolylineOptions, attribute: options.width";
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

/*
 * @tc.name: setPolylineOptionsTestOptionsHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolylineModifierTest, setPolylineOptionsTestOptionsHeightValidValues, TestSize.Level1)
{
    Opt_PolylineOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).width = ArkUnion<Opt_Union_String_Number, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueOptions).height = ArkUnion<Opt_Union_String_Number, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Number& value) {
        Opt_PolylineOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).height = value;
        modifier_->setPolylineOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPolylineOptions, attribute: options.height";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Number, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Number, Ark_String>(value));
    }
}

/*
 * @tc.name: setPolylineOptionsTestOptionsHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolylineModifierTest, setPolylineOptionsTestOptionsHeightInvalidValues, TestSize.Level1)
{
    Opt_PolylineOptions initValueOptions;

    // Initial setup
    WriteTo(initValueOptions).width = ArkUnion<Opt_Union_String_Number, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(initValueOptions).height = ArkUnion<Opt_Union_String_Number, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueOptions](const std::string& input, const Opt_Union_String_Number& value) {
        Opt_PolylineOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueOptions).height = value;
        modifier_->setPolylineOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_HEIGHT_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_HEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPolylineOptions, attribute: options.height";
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

/*
 * @tc.name: setPointsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolylineModifierTest, DISABLED_setPointsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_POINTS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINTS_DEFAULT_VALUE) << "Default value for attribute 'points'";
}

/*
 * @tc.name: setPointsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PolylineModifierTest, DISABLED_setPointsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}
} // namespace OHOS::Ace::NG
