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
const auto ATTRIBUTE_IMAGE_AIOPTIONS_NAME = "imageAIOptions";
const auto ATTRIBUTE_SOURCE_SIZE_NAME = "sourceSize";
const auto ATTRIBUTE_POINT_LIGHT_NAME = "pointLight";
const auto ATTRIBUTE_POINT_LIGHT_I_LIGHT_SOURCE_NAME = "lightSource";
const auto ATTRIBUTE_ANALYZER_CONFIG_NAME = "analyzerConfig";
const auto ATTRIBUTE_RESIZABLE_NAME = "resizable";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_NAME = "slice";
const auto ATTRIBUTE_SRC_NAME = "src";
const auto ATTRIBUTE_SRC_DEFAULT_VALUE = "";
const auto ATTRIBUTE_IMAGE_AIOPTIONS_I_TYPES_NAME = "types";
const auto ATTRIBUTE_IMAGE_AIOPTIONS_I_TYPES_DEFAULT_VALUE = "";
const auto ATTRIBUTE_IMAGE_AIOPTIONS_I_AI_CONTROLLER_NAME = "aiController";
const auto ATTRIBUTE_IMAGE_AIOPTIONS_I_AI_CONTROLLER_DEFAULT_VALUE = "";
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
const auto ATTRIBUTE_SOURCE_SIZE_I_WIDTH_NAME = "width";
const auto ATTRIBUTE_SOURCE_SIZE_I_WIDTH_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_SOURCE_SIZE_I_HEIGHT_NAME = "height";
const auto ATTRIBUTE_SOURCE_SIZE_I_HEIGHT_DEFAULT_VALUE = "0.00vp";
const auto ATTRIBUTE_SYNC_LOAD_NAME = "syncLoad";
const auto ATTRIBUTE_SYNC_LOAD_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_COLOR_FILTER_NAME = "colorFilter";
const auto ATTRIBUTE_COLOR_FILTER_DEFAULT_VALUE = "";
const auto ATTRIBUTE_COPY_OPTION_NAME = "copyOption";
const auto ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE = "CopyOptions.None";
const auto ATTRIBUTE_DRAGGABLE_NAME = "draggable";
const auto ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE = "true";
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
const auto ATTRIBUTE_POINT_LIGHT_I_BLOOM_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_EDGE_ANTIALIASING_NAME = "edgeAntialiasing";
const auto ATTRIBUTE_EDGE_ANTIALIASING_DEFAULT_VALUE = "";
const auto ATTRIBUTE_ENABLE_ANALYZER_NAME = "enableAnalyzer";
const auto ATTRIBUTE_ENABLE_ANALYZER_DEFAULT_VALUE = "false";
const auto ATTRIBUTE_ANALYZER_CONFIG_I_TYPES_NAME = "types";
const auto ATTRIBUTE_ANALYZER_CONFIG_I_TYPES_DEFAULT_VALUE = "";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_TOP_NAME = "top";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_TOP_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_RIGHT_NAME = "right";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_RIGHT_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_BOTTOM_NAME = "bottom";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_BOTTOM_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_LEFT_NAME = "left";
const auto ATTRIBUTE_RESIZABLE_I_SLICE_I_LEFT_DEFAULT_VALUE = "0";
const auto ATTRIBUTE_PRIVACY_SENSITIVE_NAME = "privacySensitive";
const auto ATTRIBUTE_PRIVACY_SENSITIVE_DEFAULT_VALUE = "false";
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
HWTEST_F(ImageModifierTest, DISABLED_setImageOptions0TestSrcValidValues, TestSize.Level1)
{
    Ark_Union_PixelMap_ResourceStr_DrawableDescriptor initValueSrc;

    // Initial setup
    initValueSrc = ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor, Ark_ResourceStr>(
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0])));

    auto checkValue = [this, &initValueSrc](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor& value) {
        Ark_Union_PixelMap_ResourceStr_DrawableDescriptor inputValueSrc = initValueSrc;

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

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected,
            ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor, Ark_ResourceStr>(
                ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected,
            ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor, Ark_ResourceStr>(
                ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
}

/*
 * @tc.name: setImageOptions0TestSrcInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setImageOptions0TestSrcInvalidValues, TestSize.Level1)
{
    Ark_Union_PixelMap_ResourceStr_DrawableDescriptor initValueSrc;

    // Initial setup
    initValueSrc = ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor, Ark_ResourceStr>(
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0])));

    auto checkValue = [this, &initValueSrc](
                          const std::string& input, const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor& value) {
        Ark_Union_PixelMap_ResourceStr_DrawableDescriptor inputValueSrc = initValueSrc;

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
    checkValue("invalid union", ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor, Ark_Empty>(nullptr));
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setImageOptions1TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setImageOptions1TestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SRC_DEFAULT_VALUE) << "Default value for attribute 'src'";
}

/*
 * @tc.name: setImageOptions1TestSrcValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setImageOptions1TestSrcValidValues, TestSize.Level1)
{
    Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent initValueSrc;

    // Initial setup
    initValueSrc = ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_ImageContent>(
        std::get<1>(Fixtures::testFixtureEnumImageContentValidValues[0]));

    auto checkValue = [this, &initValueSrc](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent& value) {
        Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent inputValueSrc = initValueSrc;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueSrc = value;
        modifier_->setImageOptions1(node, &inputValueSrc);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setImageOptions1, attribute: src";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumImageContentValidValues) {
        checkValue(input, expected,
            ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_ImageContent>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected,
            ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_ResourceStr>(
                ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected,
            ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_ResourceStr>(
                ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
}

/*
 * @tc.name: setImageOptions1TestSrcInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setImageOptions1TestSrcInvalidValues, TestSize.Level1)
{
    Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent initValueSrc;

    // Initial setup
    initValueSrc = ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_ImageContent>(
        std::get<1>(Fixtures::testFixtureEnumImageContentValidValues[0]));

    auto checkValue = [this, &initValueSrc](const std::string& input,
                          const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent& value) {
        Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent inputValueSrc = initValueSrc;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueSrc = value;
        modifier_->setImageOptions1(node, &inputValueSrc);
        auto jsonValue = GetJsonValue(node);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SRC_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_SRC_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setImageOptions1, attribute: src";
    };

    // Check invalid union
    checkValue(
        "invalid union", ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_Empty>(nullptr));
    for (auto& [input, value] : Fixtures::testFixtureEnumImageContentInvalidValues) {
        checkValue(
            input, ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_ImageContent>(value));
    }
    // Check invalid union
    checkValue(
        "invalid union", ArkUnion<Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setImageOptions2TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setImageOptions2TestDefaultValues, TestSize.Level1)
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

    resultStr = GetAttrValue<std::string>(resultImageAIOptions, ATTRIBUTE_IMAGE_AIOPTIONS_I_AI_CONTROLLER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_IMAGE_AIOPTIONS_I_AI_CONTROLLER_DEFAULT_VALUE) <<
        "Default value for attribute 'imageAIOptions.aiController'";
}

/*
 * @tc.name: setImageOptions2TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setImageOptions2TestValidValues, TestSize.Level1)
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
HWTEST_F(ImageModifierTest, DISABLED_setAltTestAltValidValues, TestSize.Level1)
{
    Ark_Union_String_Resource_PixelMap initValueAlt;

    // Initial setup
    initValueAlt = ArkUnion<Ark_Union_String_Resource_PixelMap, Ark_String>(
        std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueAlt](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_String_Resource_PixelMap& value) {
        Ark_Union_String_Resource_PixelMap inputValueAlt = initValueAlt;

        inputValueAlt = value;
        modifier_->setAlt(node_, &inputValueAlt);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALT_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setAlt, attribute: alt";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_String_Resource_PixelMap, Ark_String>(value));
    }
    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
}

/*
 * @tc.name: setAltTestAltInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setAltTestAltInvalidValues, TestSize.Level1)
{
    Ark_Union_String_Resource_PixelMap initValueAlt;

    // Initial setup
    initValueAlt = ArkUnion<Ark_Union_String_Resource_PixelMap, Ark_String>(
        std::get<1>(Fixtures::testFixtureStringValidValues[0]));

    auto checkValue = [this, &initValueAlt](const std::string& input, const Ark_Union_String_Resource_PixelMap& value) {
        Ark_Union_String_Resource_PixelMap inputValueAlt = initValueAlt;

        modifier_->setAlt(node_, &inputValueAlt);
        inputValueAlt = value;
        modifier_->setAlt(node_, &inputValueAlt);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ALT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setAlt, attribute: alt";
    };

    ADD_FAILURE() << "No fixture is defined for type Ark_Resource";
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_String_Resource_PixelMap, Ark_Empty>(nullptr));
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
    Ark_Boolean initValueMatchTextDirection;

    // Initial setup
    initValueMatchTextDirection = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueMatchTextDirection](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueMatchTextDirection = initValueMatchTextDirection;

        inputValueMatchTextDirection = value;
        modifier_->setMatchTextDirection(node_, inputValueMatchTextDirection);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MATCH_TEXT_DIRECTION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMatchTextDirection, attribute: matchTextDirection";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
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
    Ark_Boolean initValueFitOriginalSize;

    // Initial setup
    initValueFitOriginalSize = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueFitOriginalSize](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueFitOriginalSize = initValueFitOriginalSize;

        inputValueFitOriginalSize = value;
        modifier_->setFitOriginalSize(node_, inputValueFitOriginalSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FIT_ORIGINAL_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFitOriginalSize, attribute: fitOriginalSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
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
    Ark_ResourceColor initValueFillColor;

    // Initial setup
    initValueFillColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueFillColor](
                          const std::string& input, const std::string& expectedStr, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueFillColor = initValueFillColor;

        inputValueFillColor = value;
        modifier_->setFillColor(node_, &inputValueFillColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setFillColor, attribute: fillColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
}

/*
 * @tc.name: setFillColorTestFillColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setFillColorTestFillColorInvalidValues, TestSize.Level1)
{
    Ark_ResourceColor initValueFillColor;

    // Initial setup
    initValueFillColor =
        ArkUnion<Ark_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueFillColor](const std::string& input, const Ark_ResourceColor& value) {
        Ark_ResourceColor inputValueFillColor = initValueFillColor;

        modifier_->setFillColor(node_, &inputValueFillColor);
        inputValueFillColor = value;
        modifier_->setFillColor(node_, &inputValueFillColor);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FILL_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_FILL_COLOR_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setFillColor, attribute: fillColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceColor, Ark_Empty>(nullptr));
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
HWTEST_F(ImageModifierTest, setObjectFitTestObjectFitValidValues, TestSize.Level1)
{
    Ark_ImageFit initValueObjectFit;

    // Initial setup
    initValueObjectFit = std::get<1>(Fixtures::testFixtureEnumImageFitValidValues[0]);

    auto checkValue = [this, &initValueObjectFit](
                          const std::string& input, const std::string& expectedStr, const Ark_ImageFit& value) {
        Ark_ImageFit inputValueObjectFit = initValueObjectFit;

        inputValueObjectFit = value;
        modifier_->setObjectFit(node_, inputValueObjectFit);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_FIT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setObjectFit, attribute: objectFit";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumImageFitValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setObjectFitTestObjectFitInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setObjectFitTestObjectFitInvalidValues, TestSize.Level1)
{
    Ark_ImageFit initValueObjectFit;

    // Initial setup
    initValueObjectFit = std::get<1>(Fixtures::testFixtureEnumImageFitValidValues[0]);

    auto checkValue = [this, &initValueObjectFit](const std::string& input, const Ark_ImageFit& value) {
        Ark_ImageFit inputValueObjectFit = initValueObjectFit;

        modifier_->setObjectFit(node_, inputValueObjectFit);
        inputValueObjectFit = value;
        modifier_->setObjectFit(node_, inputValueObjectFit);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_FIT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OBJECT_FIT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setObjectFit, attribute: objectFit";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumImageFitInvalidValues) {
        checkValue(input, value);
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
    Ark_ImageRepeat initValueObjectRepeat;

    // Initial setup
    initValueObjectRepeat = std::get<1>(Fixtures::testFixtureEnumImageRepeatValidValues[0]);

    auto checkValue = [this, &initValueObjectRepeat](
                          const std::string& input, const std::string& expectedStr, const Ark_ImageRepeat& value) {
        Ark_ImageRepeat inputValueObjectRepeat = initValueObjectRepeat;

        inputValueObjectRepeat = value;
        modifier_->setObjectRepeat(node_, inputValueObjectRepeat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_REPEAT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setObjectRepeat, attribute: objectRepeat";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumImageRepeatValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setObjectRepeatTestObjectRepeatInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setObjectRepeatTestObjectRepeatInvalidValues, TestSize.Level1)
{
    Ark_ImageRepeat initValueObjectRepeat;

    // Initial setup
    initValueObjectRepeat = std::get<1>(Fixtures::testFixtureEnumImageRepeatValidValues[0]);

    auto checkValue = [this, &initValueObjectRepeat](const std::string& input, const Ark_ImageRepeat& value) {
        Ark_ImageRepeat inputValueObjectRepeat = initValueObjectRepeat;

        modifier_->setObjectRepeat(node_, inputValueObjectRepeat);
        inputValueObjectRepeat = value;
        modifier_->setObjectRepeat(node_, inputValueObjectRepeat);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OBJECT_REPEAT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OBJECT_REPEAT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setObjectRepeat, attribute: objectRepeat";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumImageRepeatInvalidValues) {
        checkValue(input, value);
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
    Ark_Boolean initValueAutoResize;

    // Initial setup
    initValueAutoResize = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueAutoResize](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueAutoResize = initValueAutoResize;

        inputValueAutoResize = value;
        modifier_->setAutoResize(node_, inputValueAutoResize);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_RESIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setAutoResize, attribute: autoResize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
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
    Ark_ImageRenderMode initValueRenderMode;

    // Initial setup
    initValueRenderMode = std::get<1>(Fixtures::testFixtureEnumImageRenderModeValidValues[0]);

    auto checkValue = [this, &initValueRenderMode](
                          const std::string& input, const std::string& expectedStr, const Ark_ImageRenderMode& value) {
        Ark_ImageRenderMode inputValueRenderMode = initValueRenderMode;

        inputValueRenderMode = value;
        modifier_->setRenderMode(node_, inputValueRenderMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRenderMode, attribute: renderMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumImageRenderModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setRenderModeTestRenderModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setRenderModeTestRenderModeInvalidValues, TestSize.Level1)
{
    Ark_ImageRenderMode initValueRenderMode;

    // Initial setup
    initValueRenderMode = std::get<1>(Fixtures::testFixtureEnumImageRenderModeValidValues[0]);

    auto checkValue = [this, &initValueRenderMode](const std::string& input, const Ark_ImageRenderMode& value) {
        Ark_ImageRenderMode inputValueRenderMode = initValueRenderMode;

        modifier_->setRenderMode(node_, inputValueRenderMode);
        inputValueRenderMode = value;
        modifier_->setRenderMode(node_, inputValueRenderMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RENDER_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRenderMode, attribute: renderMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumImageRenderModeInvalidValues) {
        checkValue(input, value);
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
    Ark_DynamicRangeMode initValueDynamicRangeMode;

    // Initial setup
    initValueDynamicRangeMode = std::get<1>(Fixtures::testFixtureEnumDynamicRangeModeValidValues[0]);

    auto checkValue = [this, &initValueDynamicRangeMode](
                          const std::string& input, const std::string& expectedStr, const Ark_DynamicRangeMode& value) {
        Ark_DynamicRangeMode inputValueDynamicRangeMode = initValueDynamicRangeMode;

        inputValueDynamicRangeMode = value;
        modifier_->setDynamicRangeMode(node_, inputValueDynamicRangeMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DYNAMIC_RANGE_MODE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDynamicRangeMode, attribute: dynamicRangeMode";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumDynamicRangeModeValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setDynamicRangeModeTestDynamicRangeModeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setDynamicRangeModeTestDynamicRangeModeInvalidValues, TestSize.Level1)
{
    Ark_DynamicRangeMode initValueDynamicRangeMode;

    // Initial setup
    initValueDynamicRangeMode = std::get<1>(Fixtures::testFixtureEnumDynamicRangeModeValidValues[0]);

    auto checkValue = [this, &initValueDynamicRangeMode](const std::string& input, const Ark_DynamicRangeMode& value) {
        Ark_DynamicRangeMode inputValueDynamicRangeMode = initValueDynamicRangeMode;

        modifier_->setDynamicRangeMode(node_, inputValueDynamicRangeMode);
        inputValueDynamicRangeMode = value;
        modifier_->setDynamicRangeMode(node_, inputValueDynamicRangeMode);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DYNAMIC_RANGE_MODE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DYNAMIC_RANGE_MODE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setDynamicRangeMode, attribute: dynamicRangeMode";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumDynamicRangeModeInvalidValues) {
        checkValue(input, value);
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
    Ark_ImageInterpolation initValueInterpolation;

    // Initial setup
    initValueInterpolation = std::get<1>(Fixtures::testFixtureEnumImageInterpolationValidValues[0]);

    auto checkValue = [this, &initValueInterpolation](const std::string& input, const std::string& expectedStr,
                          const Ark_ImageInterpolation& value) {
        Ark_ImageInterpolation inputValueInterpolation = initValueInterpolation;

        inputValueInterpolation = value;
        modifier_->setInterpolation(node_, inputValueInterpolation);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INTERPOLATION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setInterpolation, attribute: interpolation";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumImageInterpolationValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setInterpolationTestInterpolationInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setInterpolationTestInterpolationInvalidValues, TestSize.Level1)
{
    Ark_ImageInterpolation initValueInterpolation;

    // Initial setup
    initValueInterpolation = std::get<1>(Fixtures::testFixtureEnumImageInterpolationValidValues[0]);

    auto checkValue = [this, &initValueInterpolation](const std::string& input, const Ark_ImageInterpolation& value) {
        Ark_ImageInterpolation inputValueInterpolation = initValueInterpolation;

        modifier_->setInterpolation(node_, inputValueInterpolation);
        inputValueInterpolation = value;
        modifier_->setInterpolation(node_, inputValueInterpolation);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_INTERPOLATION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_INTERPOLATION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setInterpolation, attribute: interpolation";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumImageInterpolationInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setSourceSizeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setSourceSizeTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultSourceSize =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SOURCE_SIZE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultSourceSize, ATTRIBUTE_SOURCE_SIZE_I_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SOURCE_SIZE_I_WIDTH_DEFAULT_VALUE) <<
        "Default value for attribute 'sourceSize.width'";

    resultStr = GetAttrValue<std::string>(resultSourceSize, ATTRIBUTE_SOURCE_SIZE_I_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SOURCE_SIZE_I_HEIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'sourceSize.height'";
}

/*
 * @tc.name: setSourceSizeTestSourceSizeWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setSourceSizeTestSourceSizeWidthValidValues, TestSize.Level1)
{
    Ark_ImageSourceSize initValueSourceSize;

    // Initial setup
    initValueSourceSize.width = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    initValueSourceSize.height = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueSourceSize](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_ImageSourceSize inputValueSourceSize = initValueSourceSize;

        inputValueSourceSize.width = value;
        modifier_->setSourceSize(node_, &inputValueSourceSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultSourceSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SOURCE_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSourceSize, ATTRIBUTE_SOURCE_SIZE_I_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSourceSize, attribute: sourceSize.width";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setSourceSizeTestSourceSizeHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setSourceSizeTestSourceSizeHeightValidValues, TestSize.Level1)
{
    Ark_ImageSourceSize initValueSourceSize;

    // Initial setup
    initValueSourceSize.width = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    initValueSourceSize.height = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueSourceSize](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_ImageSourceSize inputValueSourceSize = initValueSourceSize;

        inputValueSourceSize.height = value;
        modifier_->setSourceSize(node_, &inputValueSourceSize);
        auto jsonValue = GetJsonValue(node_);
        auto resultSourceSize = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SOURCE_SIZE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSourceSize, ATTRIBUTE_SOURCE_SIZE_I_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSourceSize, attribute: sourceSize.height";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, value);
    }
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
    Ark_Boolean initValueSyncLoad;

    // Initial setup
    initValueSyncLoad = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueSyncLoad](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueSyncLoad = initValueSyncLoad;

        inputValueSyncLoad = value;
        modifier_->setSyncLoad(node_, inputValueSyncLoad);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SYNC_LOAD_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setSyncLoad, attribute: syncLoad";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setColorFilterTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setColorFilterTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COLOR_FILTER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_COLOR_FILTER_DEFAULT_VALUE) << "Default value for attribute 'colorFilter'";
}

/*
 * @tc.name: setColorFilterTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setColorFilterTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
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
    Ark_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]);

    auto checkValue = [this, &initValueCopyOption](
                          const std::string& input, const std::string& expectedStr, const Ark_CopyOptions& value) {
        Ark_CopyOptions inputValueCopyOption = initValueCopyOption;

        inputValueCopyOption = value;
        modifier_->setCopyOption(node_, inputValueCopyOption);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCopyOption, attribute: copyOption";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumCopyOptionsValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setCopyOptionTestCopyOptionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setCopyOptionTestCopyOptionInvalidValues, TestSize.Level1)
{
    Ark_CopyOptions initValueCopyOption;

    // Initial setup
    initValueCopyOption = std::get<1>(Fixtures::testFixtureEnumCopyOptionsValidValues[0]);

    auto checkValue = [this, &initValueCopyOption](const std::string& input, const Ark_CopyOptions& value) {
        Ark_CopyOptions inputValueCopyOption = initValueCopyOption;

        modifier_->setCopyOption(node_, inputValueCopyOption);
        inputValueCopyOption = value;
        modifier_->setCopyOption(node_, inputValueCopyOption);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COPY_OPTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_COPY_OPTION_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCopyOption, attribute: copyOption";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumCopyOptionsInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setDraggableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setDraggableTestDefaultValues, TestSize.Level1)
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
    Ark_Boolean initValueDraggable;

    // Initial setup
    initValueDraggable = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueDraggable](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueDraggable = initValueDraggable;

        inputValueDraggable = value;
        modifier_->setDraggable(node_, inputValueDraggable);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DRAGGABLE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setDraggable, attribute: draggable";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
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
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).positionX = value;
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

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionXInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionXInvalidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Ark_Length& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        WriteTo(inputValuePointLight.lightSource).positionX = value;
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
        checkValue(input, value);
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionYValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionYValidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).positionY = value;
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

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionYInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionYInvalidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Ark_Length& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        WriteTo(inputValuePointLight.lightSource).positionY = value;
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
        checkValue(input, value);
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionZValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionZValidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).positionZ = value;
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

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourcePositionZInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourcePositionZInvalidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Ark_Length& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        WriteTo(inputValuePointLight.lightSource).positionZ = value;
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
        checkValue(input, value);
    }
}

/*
 * @tc.name: setPointLightTestPointLightLightSourceIntensityValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightLightSourceIntensityValidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).intensity = value;
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
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_ResourceColor& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        WriteTo(inputValuePointLight.lightSource).color = value;
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
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, expected, ArkUnion<Opt_ResourceColor, Ark_Number>(value));
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
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Opt_ResourceColor& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        WriteTo(inputValuePointLight.lightSource).color = value;
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
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
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
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightIlluminatedValidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_IlluminatedType& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        inputValuePointLight.illuminated = value;
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
HWTEST_F(ImageModifierTest, DISABLED_setPointLightTestPointLightIlluminatedInvalidValues, TestSize.Level1)
{
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Opt_IlluminatedType& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        inputValuePointLight.illuminated = value;
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
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](
                          const std::string& input, const std::string& expectedStr, const Opt_Number& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        inputValuePointLight.bloom = value;
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
    Ark_PointLightStyle initValuePointLight;

    // Initial setup
    WriteTo(initValuePointLight.lightSource).positionX =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionY =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).positionZ =
        std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]);
    WriteTo(initValuePointLight.lightSource).intensity = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);
    WriteTo(initValuePointLight.lightSource).color =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValuePointLight.illuminated =
        ArkValue<Opt_IlluminatedType>(std::get<1>(Fixtures::testFixtureEnumIlluminatedTypeValidValues[0]));
    initValuePointLight.bloom = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValuePointLight](const std::string& input, const Opt_Number& value) {
        Ark_PointLightStyle inputValuePointLight = initValuePointLight;

        modifier_->setPointLight(node_, &inputValuePointLight);
        inputValuePointLight.bloom = value;
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
 * @tc.name: setEdgeAntialiasingTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setEdgeAntialiasingTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EDGE_ANTIALIASING_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_EDGE_ANTIALIASING_DEFAULT_VALUE) << "Default value for attribute 'edgeAntialiasing'";
}

/*
 * @tc.name: setEdgeAntialiasingTestEdgeAntialiasingValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setEdgeAntialiasingTestEdgeAntialiasingValidValues, TestSize.Level1)
{
    Ark_Number initValueEdgeAntialiasing;

    // Initial setup
    initValueEdgeAntialiasing = std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]);

    auto checkValue = [this, &initValueEdgeAntialiasing](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueEdgeAntialiasing = initValueEdgeAntialiasing;

        inputValueEdgeAntialiasing = value;
        modifier_->setEdgeAntialiasing(node_, &inputValueEdgeAntialiasing);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_EDGE_ANTIALIASING_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEdgeAntialiasing, attribute: edgeAntialiasing";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, expected, value);
    }
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
    Ark_Boolean initValueEnableAnalyzer;

    // Initial setup
    initValueEnableAnalyzer = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueEnableAnalyzer](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueEnableAnalyzer = initValueEnableAnalyzer;

        inputValueEnableAnalyzer = value;
        modifier_->setEnableAnalyzer(node_, inputValueEnableAnalyzer);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_ANALYZER_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnableAnalyzer, attribute: enableAnalyzer";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setAnalyzerConfigTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, setAnalyzerConfigTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultAnalyzerConfig =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_ANALYZER_CONFIG_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultAnalyzerConfig, ATTRIBUTE_ANALYZER_CONFIG_I_TYPES_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ANALYZER_CONFIG_I_TYPES_DEFAULT_VALUE) <<
        "Default value for attribute 'analyzerConfig.types'";
}

/*
 * @tc.name: setAnalyzerConfigTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setAnalyzerConfigTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setResizableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setResizableTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultResizable =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RESIZABLE_NAME);
    std::unique_ptr<JsonValue> resultSlice =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultResizable, ATTRIBUTE_RESIZABLE_I_SLICE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultSlice, ATTRIBUTE_RESIZABLE_I_SLICE_I_TOP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RESIZABLE_I_SLICE_I_TOP_DEFAULT_VALUE) <<
        "Default value for attribute 'resizable.slice.top'";

    resultStr = GetAttrValue<std::string>(resultSlice, ATTRIBUTE_RESIZABLE_I_SLICE_I_RIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RESIZABLE_I_SLICE_I_RIGHT_DEFAULT_VALUE) <<
        "Default value for attribute 'resizable.slice.right'";

    resultStr = GetAttrValue<std::string>(resultSlice, ATTRIBUTE_RESIZABLE_I_SLICE_I_BOTTOM_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RESIZABLE_I_SLICE_I_BOTTOM_DEFAULT_VALUE) <<
        "Default value for attribute 'resizable.slice.bottom'";

    resultStr = GetAttrValue<std::string>(resultSlice, ATTRIBUTE_RESIZABLE_I_SLICE_I_LEFT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RESIZABLE_I_SLICE_I_LEFT_DEFAULT_VALUE) <<
        "Default value for attribute 'resizable.slice.left'";
}

/*
 * @tc.name: setResizableTestResizableSliceTopValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setResizableTestResizableSliceTopValidValues, TestSize.Level1)
{
    Ark_ResizableOptions initValueResizable;

    // Initial setup
    WriteTo(initValueResizable.slice).top =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).right =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).bottom =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).left =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueResizable](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_ResizableOptions inputValueResizable = initValueResizable;

        WriteTo(inputValueResizable.slice).top = value;
        modifier_->setResizable(node_, &inputValueResizable);
        auto jsonValue = GetJsonValue(node_);
        auto resultResizable = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RESIZABLE_NAME);
        auto resultSlice = GetAttrValue<std::unique_ptr<JsonValue>>(resultResizable, ATTRIBUTE_RESIZABLE_I_SLICE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlice, ATTRIBUTE_RESIZABLE_I_SLICE_I_TOP_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setResizable, attribute: resizable.slice.top";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setResizableTestResizableSliceTopInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setResizableTestResizableSliceTopInvalidValues, TestSize.Level1)
{
    Ark_ResizableOptions initValueResizable;

    // Initial setup
    WriteTo(initValueResizable.slice).top =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).right =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).bottom =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).left =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueResizable](const std::string& input, const Opt_Length& value) {
        Ark_ResizableOptions inputValueResizable = initValueResizable;

        modifier_->setResizable(node_, &inputValueResizable);
        WriteTo(inputValueResizable.slice).top = value;
        modifier_->setResizable(node_, &inputValueResizable);
        auto jsonValue = GetJsonValue(node_);
        auto resultResizable = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RESIZABLE_NAME);
        auto resultSlice = GetAttrValue<std::unique_ptr<JsonValue>>(resultResizable, ATTRIBUTE_RESIZABLE_I_SLICE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlice, ATTRIBUTE_RESIZABLE_I_SLICE_I_TOP_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RESIZABLE_I_SLICE_I_TOP_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setResizable, attribute: resizable.slice.top";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setResizableTestResizableSliceRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setResizableTestResizableSliceRightValidValues, TestSize.Level1)
{
    Ark_ResizableOptions initValueResizable;

    // Initial setup
    WriteTo(initValueResizable.slice).top =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).right =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).bottom =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).left =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueResizable](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_ResizableOptions inputValueResizable = initValueResizable;

        WriteTo(inputValueResizable.slice).right = value;
        modifier_->setResizable(node_, &inputValueResizable);
        auto jsonValue = GetJsonValue(node_);
        auto resultResizable = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RESIZABLE_NAME);
        auto resultSlice = GetAttrValue<std::unique_ptr<JsonValue>>(resultResizable, ATTRIBUTE_RESIZABLE_I_SLICE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlice, ATTRIBUTE_RESIZABLE_I_SLICE_I_RIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setResizable, attribute: resizable.slice.right";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setResizableTestResizableSliceRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setResizableTestResizableSliceRightInvalidValues, TestSize.Level1)
{
    Ark_ResizableOptions initValueResizable;

    // Initial setup
    WriteTo(initValueResizable.slice).top =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).right =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).bottom =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).left =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueResizable](const std::string& input, const Opt_Length& value) {
        Ark_ResizableOptions inputValueResizable = initValueResizable;

        modifier_->setResizable(node_, &inputValueResizable);
        WriteTo(inputValueResizable.slice).right = value;
        modifier_->setResizable(node_, &inputValueResizable);
        auto jsonValue = GetJsonValue(node_);
        auto resultResizable = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RESIZABLE_NAME);
        auto resultSlice = GetAttrValue<std::unique_ptr<JsonValue>>(resultResizable, ATTRIBUTE_RESIZABLE_I_SLICE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlice, ATTRIBUTE_RESIZABLE_I_SLICE_I_RIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RESIZABLE_I_SLICE_I_RIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setResizable, attribute: resizable.slice.right";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setResizableTestResizableSliceBottomValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setResizableTestResizableSliceBottomValidValues, TestSize.Level1)
{
    Ark_ResizableOptions initValueResizable;

    // Initial setup
    WriteTo(initValueResizable.slice).top =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).right =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).bottom =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).left =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueResizable](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_ResizableOptions inputValueResizable = initValueResizable;

        WriteTo(inputValueResizable.slice).bottom = value;
        modifier_->setResizable(node_, &inputValueResizable);
        auto jsonValue = GetJsonValue(node_);
        auto resultResizable = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RESIZABLE_NAME);
        auto resultSlice = GetAttrValue<std::unique_ptr<JsonValue>>(resultResizable, ATTRIBUTE_RESIZABLE_I_SLICE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlice, ATTRIBUTE_RESIZABLE_I_SLICE_I_BOTTOM_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setResizable, attribute: resizable.slice.bottom";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setResizableTestResizableSliceBottomInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setResizableTestResizableSliceBottomInvalidValues, TestSize.Level1)
{
    Ark_ResizableOptions initValueResizable;

    // Initial setup
    WriteTo(initValueResizable.slice).top =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).right =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).bottom =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).left =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueResizable](const std::string& input, const Opt_Length& value) {
        Ark_ResizableOptions inputValueResizable = initValueResizable;

        modifier_->setResizable(node_, &inputValueResizable);
        WriteTo(inputValueResizable.slice).bottom = value;
        modifier_->setResizable(node_, &inputValueResizable);
        auto jsonValue = GetJsonValue(node_);
        auto resultResizable = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RESIZABLE_NAME);
        auto resultSlice = GetAttrValue<std::unique_ptr<JsonValue>>(resultResizable, ATTRIBUTE_RESIZABLE_I_SLICE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlice, ATTRIBUTE_RESIZABLE_I_SLICE_I_BOTTOM_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RESIZABLE_I_SLICE_I_BOTTOM_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setResizable, attribute: resizable.slice.bottom";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setResizableTestResizableSliceLeftValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setResizableTestResizableSliceLeftValidValues, TestSize.Level1)
{
    Ark_ResizableOptions initValueResizable;

    // Initial setup
    WriteTo(initValueResizable.slice).top =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).right =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).bottom =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).left =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueResizable](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_ResizableOptions inputValueResizable = initValueResizable;

        WriteTo(inputValueResizable.slice).left = value;
        modifier_->setResizable(node_, &inputValueResizable);
        auto jsonValue = GetJsonValue(node_);
        auto resultResizable = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RESIZABLE_NAME);
        auto resultSlice = GetAttrValue<std::unique_ptr<JsonValue>>(resultResizable, ATTRIBUTE_RESIZABLE_I_SLICE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlice, ATTRIBUTE_RESIZABLE_I_SLICE_I_LEFT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setResizable, attribute: resizable.slice.left";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegNonPctValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setResizableTestResizableSliceLeftInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, DISABLED_setResizableTestResizableSliceLeftInvalidValues, TestSize.Level1)
{
    Ark_ResizableOptions initValueResizable;

    // Initial setup
    WriteTo(initValueResizable.slice).top =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).right =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).bottom =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));
    WriteTo(initValueResizable.slice).left =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegNonPctValidValues[0]));

    auto checkValue = [this, &initValueResizable](const std::string& input, const Opt_Length& value) {
        Ark_ResizableOptions inputValueResizable = initValueResizable;

        modifier_->setResizable(node_, &inputValueResizable);
        WriteTo(inputValueResizable.slice).left = value;
        modifier_->setResizable(node_, &inputValueResizable);
        auto jsonValue = GetJsonValue(node_);
        auto resultResizable = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_RESIZABLE_NAME);
        auto resultSlice = GetAttrValue<std::unique_ptr<JsonValue>>(resultResizable, ATTRIBUTE_RESIZABLE_I_SLICE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSlice, ATTRIBUTE_RESIZABLE_I_SLICE_I_LEFT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RESIZABLE_I_SLICE_I_LEFT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setResizable, attribute: resizable.slice.left";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegNonPctInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
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
    Ark_Boolean initValuePrivacySensitive;

    // Initial setup
    initValuePrivacySensitive = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValuePrivacySensitive](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValuePrivacySensitive = initValuePrivacySensitive;

        inputValuePrivacySensitive = value;
        modifier_->setPrivacySensitive(node_, inputValuePrivacySensitive);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_PRIVACY_SENSITIVE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPrivacySensitive, attribute: privacySensitive";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}
} // namespace OHOS::Ace::NG
