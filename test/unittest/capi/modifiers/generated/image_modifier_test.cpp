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
const auto ATTRIBUTE_IMAGE_AIOPTIONS_NAME = "imageAIOptions";
const auto ATTRIBUTE_POINT_LIGHT_NAME = "pointLight";
const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME = "lightSource";
const auto ATTRIBUTE_SRC_NAME = "src";
const auto ATTRIBUTE_SRC_DEFAULT_VALUE = "";
const auto ATTRIBUTE_IMAGE_AIOPTIONS_I_TYPES_NAME = "types";
const auto ATTRIBUTE_IMAGE_AIOPTIONS_I_TYPES_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ALT_NAME = "alt";
const auto ATTRIBUTE_ALT_DEFAULT_VALUE = "";
const auto ATTRIBUTE_MATCH_TEXT_DIRECTION_NAME = "matchTextDirection";
const auto ATTRIBUTE_MATCH_TEXT_DIRECTION_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_FIT_ORIGINAL_SIZE_NAME = "fitOriginalSize";
const auto ATTRIBUTE_FIT_ORIGINAL_SIZE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_FILL_COLOR_NAME = "fillColor";
const auto ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE = "#FF000000";
const auto ATTRIBUTE_OBJECT_FIT_NAME = "objectFit";
const auto ATTRIBUTE_OBJECT_FIT_DEFAULT_VALUE = "ImageFit.Cover";
const auto ATTRIBUTE_OBJECT_REPEAT_NAME = "objectRepeat";
const auto ATTRIBUTE_OBJECT_REPEAT_DEFAULT_VALUE = "ImageRepeat.NoRepeat";
const auto ATTRIBUTE_AUTO_RESIZE_NAME = "autoResize";
const auto ATTRIBUTE_AUTO_RESIZE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_RENDER_MODE_NAME = "renderMode";
const auto ATTRIBUTE_RENDER_MODE_DEFAULT_VALUE = "ImageRenderMode.Original";
const auto ATTRIBUTE_DYNAMIC_RANGE_MODE_NAME = "dynamicRangeMode";
const auto ATTRIBUTE_DYNAMIC_RANGE_MODE_DEFAULT_VALUE = "dynamicRangeMode.Standard";
const auto ATTRIBUTE_INTERPOLATION_NAME = "interpolation";
const auto ATTRIBUTE_INTERPOLATION_DEFAULT_VALUE = "ImageInterpolation.None";
const auto ATTRIBUTE_SYNC_LOAD_NAME = "syncLoad";
const auto ATTRIBUTE_SYNC_LOAD_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_COPY_OPTION_NAME = "copyOption";
const auto ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE = "CopyOptions.None";
const auto ATTRIBUTE_DRAGGABLE_NAME = "draggable";
const auto ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_X_NAME = "positionX";
const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_X_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Y_NAME = "positionY";
const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Y_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Z_NAME = "positionZ";
const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Z_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_INTENSITY_NAME = "intensity";
const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_INTENSITY_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_COLOR_NAME = "color";
const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_COLOR_DEFAULT_VALUE = "#FFFFFFFF";
const auto ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_NAME = "illuminated";
const auto ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_DEFAULT_VALUE = "IlluminatedType.NONE";
const auto ATTRIBUTE_POINT_LIGHT_I_BLOOM_NAME = "bloom";
const auto ATTRIBUTE_POINT_LIGHT_I_BLOOM_DEFAULT_VALUE = "0.000000";
const auto ATTRIBUTE_ENABLE_ANALYZER_NAME = "enableAnalyzer";
const auto ATTRIBUTE_ENABLE_ANALYZER_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_PRIVACY_SENSITIVE_NAME = "privacySensitive";
const auto ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ORIENTATION_NAME = "orientation";
const auto ATTRIBUTE_ORIENTATION_DEFAULT_VALUE = "1";
} // namespace

class ImageModifierTest : public ModifierTestBase<GENERATED_ArkUIImageModifier,
                              &GENERATED_ArkUINodeModifiers::getImageModifier, GENERATED_ARKUI_IMAGE> {
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
 * @tc.name: setImageOptions0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setImageOptions0TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SRC_DEFAULT_VALUE) << "Default value for attribute 'src'";
}

/*
 * @tc.name: setImageOptions0TestSrcValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setImageOptions0TestSrcValidValues, TestSize.Level1)
{
    Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent initValueSrc;

    // Initial setup
    initValueSrc = ArkUnion<Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_ImageContent>(
        std::get<1>(Fixtures::testFixtureImageContentValidValues[0]));

    auto checkValue = [this, &initValueSrc](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent& value) {
        Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent inputValueSrc = initValueSrc;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueSrc = value;
        modifier_->setImageOptions0(node, &inputValueSrc);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setImageOptions0, attribute: src";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureImageContentValidValues) {
        checkValue(input, expected,
            ArkUnion<Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_ImageContent>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected,
            ArkUnion<Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_ResourceStr>(
                ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected,
            ArkUnion<Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_ResourceStr>(
                ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
}

/*
 * @tc.name: setImageOptions0TestSrcInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setImageOptions0TestSrcInvalidValues, TestSize.Level1)
{
    Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent initValueSrc;

    // Initial setup
    initValueSrc = ArkUnion<Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_ImageContent>(
        std::get<1>(Fixtures::testFixtureImageContentValidValues[0]));

    auto checkValue = [this, &initValueSrc](const std::string& input,
                          const Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent& value) {
        Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent inputValueSrc = initValueSrc;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueSrc = value;
        modifier_->setImageOptions0(node, &inputValueSrc);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_SRC_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setImageOptions0, attribute: src";
    };

    // Check invalid union
    checkValue(
        "invalid union", ArkUnion<Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_Empty>(nullptr));
    // Check invalid union
    checkValue(
        "invalid union", ArkUnion<Ark_Union_image_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setImageOptions1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setImageOptions1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultImageAIOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_IMAGE_AIOPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SRC_DEFAULT_VALUE) << "Default value for attribute 'src'";

    resultStr = GetAttrValue<std::string>(resultImageAIOptions, ATTRIBUTE_IMAGE_AIOPTIONS_I_TYPES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IMAGE_AIOPTIONS_I_TYPES_DEFAULT_VALUE) <<
        "Default value for attribute 'imageAIOptions.types'";
}

/*
 * @tc.name: setImageOptions1TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setImageOptions1TestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setAltTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setAltTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALT_DEFAULT_VALUE) << "Default value for attribute 'alt'";
}

/*
 * @tc.name: setAltTestAltValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setAltTestAltValidValues, TestSize.Level1)
{
    Opt_Union_String_Resource_image_PixelMap initValueAlt;

    // Initial setup
    initValueAlt = ArkUnion<Opt_Union_String_Resource_image_PixelMap, Ark_String>(
        std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueAlt](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_String_Resource_image_PixelMap& value) {
        Opt_Union_String_Resource_image_PixelMap inputValueAlt = initValueAlt;

        inputValueAlt = value;
        modifier_->setAlt(node_, &inputValueAlt);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setAlt, attribute: alt";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource_image_PixelMap, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Union_String_Resource_image_PixelMap, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setAltTestAltInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setAltTestAltInvalidValues, TestSize.Level1)
{
    Opt_Union_String_Resource_image_PixelMap initValueAlt;

    // Initial setup
    initValueAlt = ArkUnion<Opt_Union_String_Resource_image_PixelMap, Ark_String>(
        std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueAlt](const std::string& input, const Opt_Union_String_Resource_image_PixelMap& value) {
        Opt_Union_String_Resource_image_PixelMap inputValueAlt = initValueAlt;

        modifier_->setAlt(node_, &inputValueAlt);
        inputValueAlt = value;
        modifier_->setAlt(node_, &inputValueAlt);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlt, attribute: alt";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_String_Resource_image_PixelMap, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_String_Resource_image_PixelMap>());
}

/*
 * @tc.name: setMatchTextDirectionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setMatchTextDirectionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MATCH_TEXT_DIRECTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MATCH_TEXT_DIRECTION_DEFAULT_VALUE) <<
        "Default value for attribute 'matchTextDirection'";
}

/*
 * @tc.name: setMatchTextDirectionTestMatchTextDirectionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setMatchTextDirectionTestMatchTextDirectionValidValues, TestSize.Level1)
{
    Opt_Boolean initValueMatchTextDirection;

    // Initial setup
    initValueMatchTextDirection = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueMatchTextDirection](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueMatchTextDirection = initValueMatchTextDirection;

        inputValueMatchTextDirection = value;
        modifier_->setMatchTextDirection(node_, &inputValueMatchTextDirection);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MATCH_TEXT_DIRECTION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMatchTextDirection, attribute: matchTextDirection";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setMatchTextDirectionTestMatchTextDirectionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setMatchTextDirectionTestMatchTextDirectionInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueMatchTextDirection;

    // Initial setup
    initValueMatchTextDirection = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueMatchTextDirection](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueMatchTextDirection = initValueMatchTextDirection;

        modifier_->setMatchTextDirection(node_, &inputValueMatchTextDirection);
        inputValueMatchTextDirection = value;
        modifier_->setMatchTextDirection(node_, &inputValueMatchTextDirection);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MATCH_TEXT_DIRECTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_MATCH_TEXT_DIRECTION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setMatchTextDirection, attribute: matchTextDirection";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setFitOriginalSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setFitOriginalSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FIT_ORIGINAL_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FIT_ORIGINAL_SIZE_DEFAULT_VALUE) << "Default value for attribute 'fitOriginalSize'";
}

/*
 * @tc.name: setFitOriginalSizeTestFitOriginalSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setFitOriginalSizeTestFitOriginalSizeValidValues, TestSize.Level1)
{
    Opt_Boolean initValueFitOriginalSize;

    // Initial setup
    initValueFitOriginalSize = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFitOriginalSize](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueFitOriginalSize = initValueFitOriginalSize;

        inputValueFitOriginalSize = value;
        modifier_->setFitOriginalSize(node_, &inputValueFitOriginalSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FIT_ORIGINAL_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFitOriginalSize, attribute: fitOriginalSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setFitOriginalSizeTestFitOriginalSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setFitOriginalSizeTestFitOriginalSizeInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueFitOriginalSize;

    // Initial setup
    initValueFitOriginalSize = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueFitOriginalSize](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueFitOriginalSize = initValueFitOriginalSize;

        modifier_->setFitOriginalSize(node_, &inputValueFitOriginalSize);
        inputValueFitOriginalSize = value;
        modifier_->setFitOriginalSize(node_, &inputValueFitOriginalSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FIT_ORIGINAL_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FIT_ORIGINAL_SIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFitOriginalSize, attribute: fitOriginalSize";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setFillColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setFillColorTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE) << "Default value for attribute 'fillColor'";
}

/*
 * @tc.name: setFillColorTestFillColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setFillColorTestFillColorValidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_ColorContent_ColorMetrics initValueFillColor;

    // Initial setup
    initValueFillColor = ArkUnion<Opt_Union_ResourceColor_ColorContent_ColorMetrics, Ark_ResourceColor>(
        ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueFillColor](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_ResourceColor_ColorContent_ColorMetrics& value) {
        Opt_Union_ResourceColor_ColorContent_ColorMetrics inputValueFillColor = initValueFillColor;

        inputValueFillColor = value;
        modifier_->setFillColor(node_, &inputValueFillColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFillColor, attribute: fillColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_ColorContent_ColorMetrics, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_ColorContent_ColorMetrics, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Int32>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_ColorContent_ColorMetrics, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_Resource>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceColor_ColorContent_ColorMetrics, Ark_ResourceColor>(
                ArkUnion<Ark_ResourceColor, Ark_String>(value)));
    }
}

/*
 * @tc.name: setFillColorTestFillColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setFillColorTestFillColorInvalidValues, TestSize.Level1)
{
    Opt_Union_ResourceColor_ColorContent_ColorMetrics initValueFillColor;

    // Initial setup
    initValueFillColor = ArkUnion<Opt_Union_ResourceColor_ColorContent_ColorMetrics, Ark_ResourceColor>(
        ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0])));

    auto checkValue = [this, &initValueFillColor](
                          const std::string& input, const Opt_Union_ResourceColor_ColorContent_ColorMetrics& value) {
        Opt_Union_ResourceColor_ColorContent_ColorMetrics inputValueFillColor = initValueFillColor;

        modifier_->setFillColor(node_, &inputValueFillColor);
        inputValueFillColor = value;
        modifier_->setFillColor(node_, &inputValueFillColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFillColor, attribute: fillColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_ColorContent_ColorMetrics, Ark_ResourceColor>(
                              ArkUnion<Ark_ResourceColor, Ark_String>(value)));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_Union_ResourceColor_ColorContent_ColorMetrics, Ark_ResourceColor>(
                              ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(value)));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_ResourceColor_ColorContent_ColorMetrics, Ark_Empty>(nullptr));
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_ResourceColor_ColorContent_ColorMetrics, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_ResourceColor_ColorContent_ColorMetrics>());
}

/*
 * @tc.name: setObjectFitTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setObjectFitTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_FIT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OBJECT_FIT_DEFAULT_VALUE) << "Default value for attribute 'objectFit'";
}

/*
 * @tc.name: setObjectFitTestObjectFitValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setObjectFitTestObjectFitValidValues, TestSize.Level1)
{
    Opt_ImageFit initValueObjectFit;

    // Initial setup
    initValueObjectFit = ArkValue<Opt_ImageFit>(std::get<1>(Fixtures::testFixtureEnumImageFitValidValues[0]));

    auto checkValue = [this, &initValueObjectFit](
                          const std::string& input, const std::string& expectedStr, const Opt_ImageFit& value) {
        Opt_ImageFit inputValueObjectFit = initValueObjectFit;

        inputValueObjectFit = value;
        modifier_->setObjectFit(node_, &inputValueObjectFit);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_FIT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setObjectFit, attribute: objectFit";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumImageFitValidValues) {
        checkValue(input, expected, ArkValue<Opt_ImageFit>(value));
    }
}

/*
 * @tc.name: setObjectFitTestObjectFitInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setObjectFitTestObjectFitInvalidValues, TestSize.Level1)
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

/*
 * @tc.name: setObjectRepeatTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setObjectRepeatTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_REPEAT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OBJECT_REPEAT_DEFAULT_VALUE) << "Default value for attribute 'objectRepeat'";
}

/*
 * @tc.name: setObjectRepeatTestObjectRepeatValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setObjectRepeatTestObjectRepeatValidValues, TestSize.Level1)
{
    Opt_ImageRepeat initValueObjectRepeat;

    // Initial setup
    initValueObjectRepeat = ArkValue<Opt_ImageRepeat>(std::get<1>(Fixtures::testFixtureEnumImageRepeatValidValues[0]));

    auto checkValue = [this, &initValueObjectRepeat](
                          const std::string& input, const std::string& expectedStr, const Opt_ImageRepeat& value) {
        Opt_ImageRepeat inputValueObjectRepeat = initValueObjectRepeat;

        inputValueObjectRepeat = value;
        modifier_->setObjectRepeat(node_, &inputValueObjectRepeat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_REPEAT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setObjectRepeat, attribute: objectRepeat";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumImageRepeatValidValues) {
        checkValue(input, expected, ArkValue<Opt_ImageRepeat>(value));
    }
}

/*
 * @tc.name: setObjectRepeatTestObjectRepeatInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setObjectRepeatTestObjectRepeatInvalidValues, TestSize.Level1)
{
    Opt_ImageRepeat initValueObjectRepeat;

    // Initial setup
    initValueObjectRepeat = ArkValue<Opt_ImageRepeat>(std::get<1>(Fixtures::testFixtureEnumImageRepeatValidValues[0]));

    auto checkValue = [this, &initValueObjectRepeat](const std::string& input, const Opt_ImageRepeat& value) {
        Opt_ImageRepeat inputValueObjectRepeat = initValueObjectRepeat;

        modifier_->setObjectRepeat(node_, &inputValueObjectRepeat);
        inputValueObjectRepeat = value;
        modifier_->setObjectRepeat(node_, &inputValueObjectRepeat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_REPEAT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OBJECT_REPEAT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setObjectRepeat, attribute: objectRepeat";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumImageRepeatInvalidValues) {
        checkValue(input, ArkValue<Opt_ImageRepeat>(value));
    }
}

/*
 * @tc.name: setAutoResizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setAutoResizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_RESIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_AUTO_RESIZE_DEFAULT_VALUE) << "Default value for attribute 'autoResize'";
}

/*
 * @tc.name: setAutoResizeTestAutoResizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setAutoResizeTestAutoResizeValidValues, TestSize.Level1)
{
    Opt_Boolean initValueAutoResize;

    // Initial setup
    initValueAutoResize = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueAutoResize](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueAutoResize = initValueAutoResize;

        inputValueAutoResize = value;
        modifier_->setAutoResize(node_, &inputValueAutoResize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_RESIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAutoResize, attribute: autoResize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setAutoResizeTestAutoResizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setAutoResizeTestAutoResizeInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueAutoResize;

    // Initial setup
    initValueAutoResize = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueAutoResize](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueAutoResize = initValueAutoResize;

        modifier_->setAutoResize(node_, &inputValueAutoResize);
        inputValueAutoResize = value;
        modifier_->setAutoResize(node_, &inputValueAutoResize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_RESIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_AUTO_RESIZE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAutoResize, attribute: autoResize";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setRenderModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setRenderModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RENDER_MODE_DEFAULT_VALUE) << "Default value for attribute 'renderMode'";
}

/*
 * @tc.name: setRenderModeTestRenderModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setRenderModeTestRenderModeValidValues, TestSize.Level1)
{
    Opt_ImageRenderMode initValueRenderMode;

    // Initial setup
    initValueRenderMode =
        ArkValue<Opt_ImageRenderMode>(std::get<1>(Fixtures::testFixtureEnumImageRenderModeValidValues[0]));

    auto checkValue = [this, &initValueRenderMode](
                          const std::string& input, const std::string& expectedStr, const Opt_ImageRenderMode& value) {
        Opt_ImageRenderMode inputValueRenderMode = initValueRenderMode;

        inputValueRenderMode = value;
        modifier_->setRenderMode(node_, &inputValueRenderMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRenderMode, attribute: renderMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumImageRenderModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ImageRenderMode>(value));
    }
}

/*
 * @tc.name: setRenderModeTestRenderModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setRenderModeTestRenderModeInvalidValues, TestSize.Level1)
{
    Opt_ImageRenderMode initValueRenderMode;

    // Initial setup
    initValueRenderMode =
        ArkValue<Opt_ImageRenderMode>(std::get<1>(Fixtures::testFixtureEnumImageRenderModeValidValues[0]));

    auto checkValue = [this, &initValueRenderMode](const std::string& input, const Opt_ImageRenderMode& value) {
        Opt_ImageRenderMode inputValueRenderMode = initValueRenderMode;

        modifier_->setRenderMode(node_, &inputValueRenderMode);
        inputValueRenderMode = value;
        modifier_->setRenderMode(node_, &inputValueRenderMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RENDER_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRenderMode, attribute: renderMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumImageRenderModeInvalidValues) {
        checkValue(input, ArkValue<Opt_ImageRenderMode>(value));
    }
}

/*
 * @tc.name: setDynamicRangeModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setDynamicRangeModeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DYNAMIC_RANGE_MODE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DYNAMIC_RANGE_MODE_DEFAULT_VALUE) <<
        "Default value for attribute 'dynamicRangeMode'";
}

/*
 * @tc.name: setDynamicRangeModeTestDynamicRangeModeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setDynamicRangeModeTestDynamicRangeModeValidValues, TestSize.Level1)
{
    Opt_DynamicRangeMode initValueDynamicRangeMode;

    // Initial setup
    initValueDynamicRangeMode =
        ArkValue<Opt_DynamicRangeMode>(std::get<1>(Fixtures::testFixtureEnumDynamicRangeModeValidValues[0]));

    auto checkValue = [this, &initValueDynamicRangeMode](
                          const std::string& input, const std::string& expectedStr, const Opt_DynamicRangeMode& value) {
        Opt_DynamicRangeMode inputValueDynamicRangeMode = initValueDynamicRangeMode;

        inputValueDynamicRangeMode = value;
        modifier_->setDynamicRangeMode(node_, &inputValueDynamicRangeMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DYNAMIC_RANGE_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDynamicRangeMode, attribute: dynamicRangeMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumDynamicRangeModeValidValues) {
        checkValue(input, expected, ArkValue<Opt_DynamicRangeMode>(value));
    }
}

/*
 * @tc.name: setDynamicRangeModeTestDynamicRangeModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setDynamicRangeModeTestDynamicRangeModeInvalidValues, TestSize.Level1)
{
    Opt_DynamicRangeMode initValueDynamicRangeMode;

    // Initial setup
    initValueDynamicRangeMode =
        ArkValue<Opt_DynamicRangeMode>(std::get<1>(Fixtures::testFixtureEnumDynamicRangeModeValidValues[0]));

    auto checkValue = [this, &initValueDynamicRangeMode](const std::string& input, const Opt_DynamicRangeMode& value) {
        Opt_DynamicRangeMode inputValueDynamicRangeMode = initValueDynamicRangeMode;

        modifier_->setDynamicRangeMode(node_, &inputValueDynamicRangeMode);
        inputValueDynamicRangeMode = value;
        modifier_->setDynamicRangeMode(node_, &inputValueDynamicRangeMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DYNAMIC_RANGE_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DYNAMIC_RANGE_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDynamicRangeMode, attribute: dynamicRangeMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumDynamicRangeModeInvalidValues) {
        checkValue(input, ArkValue<Opt_DynamicRangeMode>(value));
    }
}

/*
 * @tc.name: setInterpolationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setInterpolationTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INTERPOLATION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_INTERPOLATION_DEFAULT_VALUE) << "Default value for attribute 'interpolation'";
}

/*
 * @tc.name: setInterpolationTestInterpolationValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setInterpolationTestInterpolationValidValues, TestSize.Level1)
{
    Opt_ImageInterpolation initValueInterpolation;

    // Initial setup
    initValueInterpolation =
        ArkValue<Opt_ImageInterpolation>(std::get<1>(Fixtures::testFixtureEnumImageInterpolationValidValues[0]));

    auto checkValue = [this, &initValueInterpolation](const std::string& input, const std::string& expectedStr,
                          const Opt_ImageInterpolation& value) {
        Opt_ImageInterpolation inputValueInterpolation = initValueInterpolation;

        inputValueInterpolation = value;
        modifier_->setInterpolation(node_, &inputValueInterpolation);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INTERPOLATION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setInterpolation, attribute: interpolation";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumImageInterpolationValidValues) {
        checkValue(input, expected, ArkValue<Opt_ImageInterpolation>(value));
    }
}

/*
 * @tc.name: setInterpolationTestInterpolationInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setInterpolationTestInterpolationInvalidValues, TestSize.Level1)
{
    Opt_ImageInterpolation initValueInterpolation;

    // Initial setup
    initValueInterpolation =
        ArkValue<Opt_ImageInterpolation>(std::get<1>(Fixtures::testFixtureEnumImageInterpolationValidValues[0]));

    auto checkValue = [this, &initValueInterpolation](const std::string& input, const Opt_ImageInterpolation& value) {
        Opt_ImageInterpolation inputValueInterpolation = initValueInterpolation;

        modifier_->setInterpolation(node_, &inputValueInterpolation);
        inputValueInterpolation = value;
        modifier_->setInterpolation(node_, &inputValueInterpolation);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INTERPOLATION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_INTERPOLATION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setInterpolation, attribute: interpolation";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumImageInterpolationInvalidValues) {
        checkValue(input, ArkValue<Opt_ImageInterpolation>(value));
    }
}

/*
 * @tc.name: setSourceSizeTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setSourceSizeTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setSyncLoadTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setSyncLoadTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SYNC_LOAD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SYNC_LOAD_DEFAULT_VALUE) << "Default value for attribute 'syncLoad'";
}

/*
 * @tc.name: setSyncLoadTestSyncLoadValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setSyncLoadTestSyncLoadValidValues, TestSize.Level1)
{
    Opt_Boolean initValueSyncLoad;

    // Initial setup
    initValueSyncLoad = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueSyncLoad](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueSyncLoad = initValueSyncLoad;

        inputValueSyncLoad = value;
        modifier_->setSyncLoad(node_, &inputValueSyncLoad);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SYNC_LOAD_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSyncLoad, attribute: syncLoad";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setSyncLoadTestSyncLoadInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setSyncLoadTestSyncLoadInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueSyncLoad;

    // Initial setup
    initValueSyncLoad = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueSyncLoad](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueSyncLoad = initValueSyncLoad;

        modifier_->setSyncLoad(node_, &inputValueSyncLoad);
        inputValueSyncLoad = value;
        modifier_->setSyncLoad(node_, &inputValueSyncLoad);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SYNC_LOAD_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SYNC_LOAD_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setSyncLoad, attribute: syncLoad";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setColorFilterTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setColorFilterTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setCopyOptionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setCopyOptionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE) << "Default value for attribute 'copyOption'";
}

/*
 * @tc.name: setCopyOptionTestCopyOptionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setCopyOptionTestCopyOptionValidValues, TestSize.Level1)
{
    Opt_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = ArkValue<Opt_CopyOptions>(std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]));

    auto checkValue = [this, &initValueCopyOption](
                          const std::string& input, const std::string& expectedStr, const Opt_CopyOptions& value) {
        Opt_CopyOptions inputValueCopyOption = initValueCopyOption;

        inputValueCopyOption = value;
        modifier_->setCopyOption(node_, &inputValueCopyOption);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCopyOption, attribute: copyOption";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumCopyOptionsValidValues) {
        checkValue(input, expected, ArkValue<Opt_CopyOptions>(value));
    }
}

/*
 * @tc.name: setCopyOptionTestCopyOptionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setCopyOptionTestCopyOptionInvalidValues, TestSize.Level1)
{
    Opt_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = ArkValue<Opt_CopyOptions>(std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]));

    auto checkValue = [this, &initValueCopyOption](const std::string& input, const Opt_CopyOptions& value) {
        Opt_CopyOptions inputValueCopyOption = initValueCopyOption;

        modifier_->setCopyOption(node_, &inputValueCopyOption);
        inputValueCopyOption = value;
        modifier_->setCopyOption(node_, &inputValueCopyOption);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCopyOption, attribute: copyOption";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumCopyOptionsInvalidValues) {
        checkValue(input, ArkValue<Opt_CopyOptions>(value));
    }
}

/*
 * @tc.name: setDraggableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setDraggableTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DRAGGABLE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE) << "Default value for attribute 'draggable'";
}

/*
 * @tc.name: setDraggableTestDraggableValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setDraggableTestDraggableValidValues, TestSize.Level1)
{
    Opt_Boolean initValueDraggable;

    // Initial setup
    initValueDraggable = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueDraggable](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueDraggable = initValueDraggable;

        inputValueDraggable = value;
        modifier_->setDraggable(node_, &inputValueDraggable);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DRAGGABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDraggable, attribute: draggable";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setDraggableTestDraggableInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setDraggableTestDraggableInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueDraggable;

    // Initial setup
    initValueDraggable = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueDraggable](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueDraggable = initValueDraggable;

        modifier_->setDraggable(node_, &inputValueDraggable);
        inputValueDraggable = value;
        modifier_->setDraggable(node_, &inputValueDraggable);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DRAGGABLE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDraggable, attribute: draggable";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setPointLightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultPointLight =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
    std::unique_ptr<JsonValue> resultLightSource =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_X_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_X_DEFAULT_VALUE) <<
        "Default value for attribute 'pointLight.lightSource.positionX'";

    resultStr = GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Y_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Y_DEFAULT_VALUE) <<
        "Default value for attribute 'pointLight.lightSource.positionY'";

    resultStr = GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Z_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Z_DEFAULT_VALUE) <<
        "Default value for attribute 'pointLight.lightSource.positionZ'";

    resultStr = GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_INTENSITY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_INTENSITY_DEFAULT_VALUE) <<
        "Default value for attribute 'pointLight.lightSource.intensity'";

    resultStr = GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_COLOR_DEFAULT_VALUE) <<
        "Default value for attribute 'pointLight.lightSource.color'";

    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_DEFAULT_VALUE) <<
        "Default value for attribute 'pointLight.illuminated'";

    resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_BLOOM_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_BLOOM_DEFAULT_VALUE) <<
        "Default value for attribute 'pointLight.bloom'";
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionXValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionXValidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Dimension& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(WriteTo(inputValuePointLight).lightSource).positionX = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_X_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.positionX";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Dimension, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Dimension, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Dimension, Ark_String>(value));
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionXInvalidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Ark_Dimension& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        WriteTo(WriteTo(inputValuePointLight).lightSource).positionX = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_X_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_X_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.positionX";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Dimension, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Dimension, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Ark_Dimension, Ark_Number>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Dimension, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionYValidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Dimension& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(WriteTo(inputValuePointLight).lightSource).positionY = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Y_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.positionY";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Dimension, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Dimension, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Dimension, Ark_String>(value));
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionYInvalidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Ark_Dimension& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        WriteTo(WriteTo(inputValuePointLight).lightSource).positionY = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Y_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Y_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.positionY";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Dimension, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Dimension, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Ark_Dimension, Ark_Number>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Dimension, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionZValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionZValidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Dimension& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(WriteTo(inputValuePointLight).lightSource).positionZ = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Z_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.positionZ";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Dimension, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Dimension, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Dimension, Ark_String>(value));
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionZInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionZInvalidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Ark_Dimension& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        WriteTo(WriteTo(inputValuePointLight).lightSource).positionZ = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Z_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_POSITION_Z_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.positionZ";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Dimension, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Dimension, Ark_Resource>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Ark_Dimension, Ark_Number>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Dimension, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setPointLightTestPointLightLightSourceIntensityValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourceIntensityValidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(WriteTo(inputValuePointLight).lightSource).intensity = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_INTENSITY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.intensity";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourceColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourceColorValidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(WriteTo(inputValuePointLight).lightSource).color = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.color";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Int32>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourceColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourceColorInvalidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Opt_ResourceColor& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        WriteTo(WriteTo(inputValuePointLight).lightSource).color = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultLightSource =
            GetAttrValue<std::unique_ptr<JsonValue>>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultLightSource, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_I_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.lightSource.color";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setPointLightTestPointLightIlluminatedValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setPointLightTestPointLightIlluminatedValidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_IlluminatedType& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight).illuminated = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.illuminated";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumIlluminatedTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_IlluminatedType>(value));
    }
}

/*
 * @tc.name: setPointLightTestPointLightIlluminatedInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setPointLightTestPointLightIlluminatedInvalidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Opt_IlluminatedType& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        WriteTo(inputValuePointLight).illuminated = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_ILLUMINATED_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.illuminated";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumIlluminatedTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_IlluminatedType>(value));
    }
}

/*
 * @tc.name: setPointLightTestPointLightBloomValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightBloomValidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight).bloom = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_BLOOM_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.bloom";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, ArkValue<Opt_Number>(value));
    }
}

/*
 * @tc.name: setPointLightTestPointLightBloomInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightBloomInvalidValues, TestSize.Level1)
{
    Opt_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(WriteTo(initValuePointLight).lightSource).positionX =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionY =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).positionZ =
        ArkUnion<Ark_Dimension, Ark_Number>(std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));
    WriteTo(WriteTo(initValuePointLight).lightSource).intensity =
        std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(WriteTo(initValuePointLight).lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    WriteTo(initValuePointLight).illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    WriteTo(initValuePointLight).bloom =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Opt_Number& value) {
        Opt_PointLightStyle inputValuePointLight = initValuePointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        WriteTo(inputValuePointLight).bloom = value;
        modifier_->setPointLight(node_, &inputValuePointLight);
        auto jsonValue = GetJsonValue(node_);
        auto resultPointLight = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_POINT_LIGHT_NAME);
        auto resultStr = GetAttrValue<std::string>(resultPointLight, ATTRIBUTE_POINT_LIGHT_I_BLOOM_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_POINT_LIGHT_I_BLOOM_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPointLight, attribute: pointLight.bloom";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setEdgeAntialiasingTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setEdgeAntialiasingTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setEnableAnalyzerTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setEnableAnalyzerTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_ANALYZER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_ANALYZER_DEFAULT_VALUE) << "Default value for attribute 'enableAnalyzer'";
}

/*
 * @tc.name: setEnableAnalyzerTestEnableAnalyzerValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setEnableAnalyzerTestEnableAnalyzerValidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableAnalyzer;

    // Initial setup
    initValueEnableAnalyzer = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableAnalyzer](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableAnalyzer = initValueEnableAnalyzer;

        inputValueEnableAnalyzer = value;
        modifier_->setEnableAnalyzer(node_, &inputValueEnableAnalyzer);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_ANALYZER_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableAnalyzer, attribute: enableAnalyzer";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setEnableAnalyzerTestEnableAnalyzerInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setEnableAnalyzerTestEnableAnalyzerInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValueEnableAnalyzer;

    // Initial setup
    initValueEnableAnalyzer = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValueEnableAnalyzer](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValueEnableAnalyzer = initValueEnableAnalyzer;

        modifier_->setEnableAnalyzer(node_, &inputValueEnableAnalyzer);
        inputValueEnableAnalyzer = value;
        modifier_->setEnableAnalyzer(node_, &inputValueEnableAnalyzer);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_ANALYZER_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_ANALYZER_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnableAnalyzer, attribute: enableAnalyzer";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setAnalyzerConfigTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setAnalyzerConfigTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setResizableTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setResizableTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setPrivacySensitiveTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setPrivacySensitiveTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PRIVACY_SENSITIVE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE) << "Default value for attribute 'privacySensitive'";
}

/*
 * @tc.name: setPrivacySensitiveTestPrivacySensitiveValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setPrivacySensitiveTestPrivacySensitiveValidValues, TestSize.Level1)
{
    Opt_Boolean initValuePrivacySensitive;

    // Initial setup
    initValuePrivacySensitive = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValuePrivacySensitive](
                          const std::string& input, const std::string& expectedStr, const Opt_Boolean& value) {
        Opt_Boolean inputValuePrivacySensitive = initValuePrivacySensitive;

        inputValuePrivacySensitive = value;
        modifier_->setPrivacySensitive(node_, &inputValuePrivacySensitive);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PRIVACY_SENSITIVE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPrivacySensitive, attribute: privacySensitive";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, ArkValue<Opt_Boolean>(value));
    }
}

/*
 * @tc.name: setPrivacySensitiveTestPrivacySensitiveInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setPrivacySensitiveTestPrivacySensitiveInvalidValues, TestSize.Level1)
{
    Opt_Boolean initValuePrivacySensitive;

    // Initial setup
    initValuePrivacySensitive = ArkValue<Opt_Boolean>(std::get<1>(Fixtures::testFixtureBooleanValidValues[0]));

    auto checkValue = [this, &initValuePrivacySensitive](const std::string& input, const Opt_Boolean& value) {
        Opt_Boolean inputValuePrivacySensitive = initValuePrivacySensitive;

        modifier_->setPrivacySensitive(node_, &inputValuePrivacySensitive);
        inputValuePrivacySensitive = value;
        modifier_->setPrivacySensitive(node_, &inputValuePrivacySensitive);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PRIVACY_SENSITIVE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setPrivacySensitive, attribute: privacySensitive";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Boolean>());
}

/*
 * @tc.name: setEnhancedImageQualityTestPlaceholder
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setEnhancedImageQualityTestPlaceholder, TestSize.Level1)
{
    // This is placeholder to have disabled test
}

/*
 * @tc.name: setOrientationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setOrientationTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ORIENTATION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ORIENTATION_DEFAULT_VALUE) << "Default value for attribute 'orientation'";
}

/*
 * @tc.name: setOrientationTestOrientationValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setOrientationTestOrientationValidValues, TestSize.Level1)
{
    Opt_ImageRotateOrientation initValueOrientation;

    // Initial setup
    initValueOrientation =
        ArkValue<Opt_ImageRotateOrientation>(std::get<1>(Fixtures::testFixtureImageRotateOrientationValidValues[0]));

    auto checkValue = [this, &initValueOrientation](const std::string& input, const std::string& expectedStr,
                          const Opt_ImageRotateOrientation& value) {
        Opt_ImageRotateOrientation inputValueOrientation = initValueOrientation;

        inputValueOrientation = value;
        modifier_->setOrientation(node_, &inputValueOrientation);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ORIENTATION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setOrientation, attribute: orientation";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureImageRotateOrientationValidValues) {
        checkValue(input, expected, ArkValue<Opt_ImageRotateOrientation>(value));
    }
}

/*
 * @tc.name: setOrientationTestOrientationInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setOrientationTestOrientationInvalidValues, TestSize.Level1)
{
    Opt_ImageRotateOrientation initValueOrientation;

    // Initial setup
    initValueOrientation =
        ArkValue<Opt_ImageRotateOrientation>(std::get<1>(Fixtures::testFixtureImageRotateOrientationValidValues[0]));

    auto checkValue = [this, &initValueOrientation](const std::string& input, const Opt_ImageRotateOrientation& value) {
        Opt_ImageRotateOrientation inputValueOrientation = initValueOrientation;

        modifier_->setOrientation(node_, &inputValueOrientation);
        inputValueOrientation = value;
        modifier_->setOrientation(node_, &inputValueOrientation);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ORIENTATION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ORIENTATION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setOrientation, attribute: orientation";
    };

    for (auto& [input, value] : Fixtures::testFixtureImageRotateOrientationInvalidValues) {
        checkValue(input, ArkValue<Opt_ImageRotateOrientation>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ImageRotateOrientation>());
}
} // namespace OHOS::Ace::NG
