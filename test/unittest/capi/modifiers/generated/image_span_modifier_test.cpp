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
const auto ATTRIBUTE_VALUE_NAME = "value";
const auto ATTRIBUTE_VALUE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_VERTICAL_ALIGN_NAME = "verticalAlign";
const auto ATTRIBUTE_VERTICAL_ALIGN_DEFAULT_VALUE = "VerticalAlign.BOTTOM";
const auto ATTRIBUTE_OBJECT_FIT_NAME = "objectFit";
const auto ATTRIBUTE_OBJECT_FIT_DEFAULT_VALUE = "ImageFit.Cover";
} // namespace

class ImageSpanModifierTest : public ModifierTestBase<GENERATED_ArkUIImageSpanModifier,
                                  &GENERATED_ArkUINodeModifiers::getImageSpanModifier, GENERATED_ARKUI_IMAGE_SPAN> {
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
 * @tc.name: setImageSpanOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, DISABLED_setImageSpanOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) << "Default value for attribute 'value'";
}

/*
 * @tc.name: setImageSpanOptionsTestValueValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, DISABLED_setImageSpanOptionsTestValueValidValues, TestSize.Level1)
{
    Ark_Union_ResourceStr_image_PixelMap initValueValue;

    // Initial setup
    initValueValue = ArkUnion<Ark_Union_ResourceStr_image_PixelMap, Ark_ResourceStr>(
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0])));

    auto checkValue = [this, &initValueValue](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_ResourceStr_image_PixelMap& value) {
        Ark_Union_ResourceStr_image_PixelMap inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue = value;
        modifier_->setImageSpanOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setImageSpanOptions, attribute: value";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected,
            ArkUnion<Ark_Union_ResourceStr_image_PixelMap, Ark_ResourceStr>(
                ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected,
            ArkUnion<Ark_Union_ResourceStr_image_PixelMap, Ark_ResourceStr>(
                ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
}

/*
 * @tc.name: setImageSpanOptionsTestValueInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, DISABLED_setImageSpanOptionsTestValueInvalidValues, TestSize.Level1)
{
    Ark_Union_ResourceStr_image_PixelMap initValueValue;

    // Initial setup
    initValueValue = ArkUnion<Ark_Union_ResourceStr_image_PixelMap, Ark_ResourceStr>(
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0])));

    auto checkValue = [this, &initValueValue](const std::string& input,
        const Ark_Union_ResourceStr_image_PixelMap& value) {
        Ark_Union_ResourceStr_image_PixelMap inputValueValue = initValueValue;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueValue = value;
        modifier_->setImageSpanOptions(node, &inputValueValue);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VALUE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setImageSpanOptions, attribute: value";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_ResourceStr_image_PixelMap, Ark_Empty>(nullptr));
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_ResourceStr_image_PixelMap, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setVerticalAlignTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, setVerticalAlignTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VERTICAL_ALIGN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VERTICAL_ALIGN_DEFAULT_VALUE) << "Default value for attribute 'verticalAlign'";
}

/*
 * @tc.name: setVerticalAlignTestVerticalAlignValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, setVerticalAlignTestVerticalAlignValidValues, TestSize.Level1)
{
    Opt_ImageSpanAlignment initValueVerticalAlign;

    // Initial setup
    initValueVerticalAlign =
        ArkValue<Opt_ImageSpanAlignment>(std::get<1>(Fixtures::testFixtureImageSpanVerticalAlignValidValues[0]));

    auto checkValue = [this, &initValueVerticalAlign](const std::string& input, const std::string& expectedStr,
                          const Opt_ImageSpanAlignment& value) {
        Opt_ImageSpanAlignment inputValueVerticalAlign = initValueVerticalAlign;

        inputValueVerticalAlign = value;
        modifier_->setVerticalAlign(node_, &inputValueVerticalAlign);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VERTICAL_ALIGN_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setVerticalAlign, attribute: verticalAlign";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureImageSpanVerticalAlignValidValues) {
        checkValue(input, expected, ArkValue<Opt_ImageSpanAlignment>(value));
    }
}

/*
 * @tc.name: setVerticalAlignTestVerticalAlignInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, setVerticalAlignTestVerticalAlignInvalidValues, TestSize.Level1)
{
    Opt_ImageSpanAlignment initValueVerticalAlign;

    // Initial setup
    initValueVerticalAlign =
        ArkValue<Opt_ImageSpanAlignment>(std::get<1>(Fixtures::testFixtureImageSpanVerticalAlignValidValues[0]));

    auto checkValue = [this, &initValueVerticalAlign](const std::string& input, const Opt_ImageSpanAlignment& value) {
        Opt_ImageSpanAlignment inputValueVerticalAlign = initValueVerticalAlign;

        modifier_->setVerticalAlign(node_, &inputValueVerticalAlign);
        inputValueVerticalAlign = value;
        modifier_->setVerticalAlign(node_, &inputValueVerticalAlign);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_VERTICAL_ALIGN_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_VERTICAL_ALIGN_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setVerticalAlign, attribute: verticalAlign";
    };

    for (auto& [input, value] : Fixtures::testFixtureImageSpanVerticalAlignInvalidValues) {
        checkValue(input, ArkValue<Opt_ImageSpanAlignment>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ImageSpanAlignment>());
}

/*
 * @tc.name: setObjectFitTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, setObjectFitTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_FIT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OBJECT_FIT_DEFAULT_VALUE) << "Default value for attribute 'objectFit'";
}

/*
 * @tc.name: setObjectFitTestObjectFitInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, setObjectFitTestObjectFitInvalidValues, TestSize.Level1)
{
    Opt_ImageFit initValueObjectFit;

    // Initial setup
    initValueObjectFit = ArkValue<Opt_ImageFit>(std::get<1>(Fixtures::testFixtureEnumImageFitValidValues[0]));

    auto checkValue = [this, &initValueObjectFit](const std::string& input, const Opt_ImageFit& value) {
        Opt_ImageFit inputValueObjectFit = initValueObjectFit;

        modifier_->setObjectFit(node_, &inputValueObjectFit);
        inputValueObjectFit = value;
        modifier_->setObjectFit(node_, &inputValueObjectFit);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_FIT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OBJECT_FIT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setObjectFit, attribute: objectFit";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumImageFitInvalidValues) {
        checkValue(input, ArkValue<Opt_ImageFit>(value));
    }
}
} // namespace OHOS::Ace::NG
