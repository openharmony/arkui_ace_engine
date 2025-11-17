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
const auto ATTRIBUTE_SCENE_OPTIONS_NAME = "sceneOptions";
const auto ATTRIBUTE_CUSTOM_RENDER_NAME = "customRender";
const auto ATTRIBUTE_SCENE_OPTIONS_I_SCENE_NAME = "scene";
const auto ATTRIBUTE_SCENE_OPTIONS_I_SCENE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_SCENE_OPTIONS_I_MODEL_TYPE_NAME = "modelType";
const auto ATTRIBUTE_SCENE_OPTIONS_I_MODEL_TYPE_DEFAULT_VALUE = "!NOT-DEFINED!";
const auto ATTRIBUTE_ENVIRONMENT_NAME = "environment";
const auto ATTRIBUTE_ENVIRONMENT_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SHADER_NAME = "shader";
const auto ATTRIBUTE_SHADER_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SHADER_IMAGE_TEXTURE_NAME = "shaderImageTexture";
const auto ATTRIBUTE_SHADER_IMAGE_TEXTURE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_SHADER_INPUT_BUFFER_NAME = "shaderInputBuffer";
const auto ATTRIBUTE_SHADER_INPUT_BUFFER_DEFAULT_VALUE = "";
const auto ATTRIBUTE_RENDER_WIDTH_NAME = "renderWidth";
const auto ATTRIBUTE_RENDER_WIDTH_DEFAULT_VALUE = "1.000000";
const auto ATTRIBUTE_RENDER_HEIGHT_NAME = "renderHeight";
const auto ATTRIBUTE_RENDER_HEIGHT_DEFAULT_VALUE = "1.000000";
const auto ATTRIBUTE_CUSTOM_RENDER_I_URI_NAME = "uri";
const auto ATTRIBUTE_CUSTOM_RENDER_I_URI_DEFAULT_VALUE = "";
const auto ATTRIBUTE_CUSTOM_RENDER_I_SELF_RENDER_UPDATE_NAME = "selfRenderUpdate";
const auto ATTRIBUTE_CUSTOM_RENDER_I_SELF_RENDER_UPDATE_DEFAULT_VALUE = "";
} // namespace

class Component3DModifierTest
    : public ModifierTestBase<GENERATED_ArkUIComponent3DModifier, &GENERATED_ArkUINodeModifiers::getComponent3DModifier,
          GENERATED_ARKUI_COMPONENT_3D> {
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
 * @tc.name: setComponent3DOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setComponent3DOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultSceneOptions =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SCENE_OPTIONS_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultSceneOptions, ATTRIBUTE_SCENE_OPTIONS_I_SCENE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SCENE_OPTIONS_I_SCENE_DEFAULT_VALUE) <<
        "Default value for attribute 'sceneOptions.scene'";

    resultStr = GetAttrValue<std::string>(resultSceneOptions, ATTRIBUTE_SCENE_OPTIONS_I_MODEL_TYPE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SCENE_OPTIONS_I_MODEL_TYPE_DEFAULT_VALUE) <<
        "Default value for attribute 'sceneOptions.modelType'";
}

/*
 * @tc.name: setComponent3DOptionsTestSceneOptionsSceneValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setComponent3DOptionsTestSceneOptionsSceneValidValues, TestSize.Level1)
{
    Opt_SceneOptions initValueSceneOptions;

    // Initial setup
    WriteTo(initValueSceneOptions).scene = ArkUnion<Opt_Union_ResourceStr_Scene, Ark_ResourceStr>(
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0])));
    WriteTo(initValueSceneOptions).modelType =
        ArkValue<Opt_ModelType>(std::get<1>(Fixtures::testFixtureEnumModelTypeValidValues[0]));

    auto checkValue = [this, &initValueSceneOptions](const std::string& input, const std::string& expectedStr,
                          const Opt_Union_ResourceStr_Scene& value) {
        Opt_SceneOptions inputValueSceneOptions = initValueSceneOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueSceneOptions).scene = value;
        modifier_->setComponent3DOptions(node, &inputValueSceneOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultSceneOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SCENE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSceneOptions, ATTRIBUTE_SCENE_OPTIONS_I_SCENE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setComponent3DOptions, attribute: sceneOptions.scene";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceStr_Scene, Ark_ResourceStr>(ArkUnion<Ark_ResourceStr, Ark_String>(value)));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureStringResValidValues) {
        checkValue(input, expected,
            ArkUnion<Opt_Union_ResourceStr_Scene, Ark_ResourceStr>(ArkUnion<Ark_ResourceStr, Ark_Resource>(value)));
    }
}

/*
 * @tc.name: setComponent3DOptionsTestSceneOptionsSceneInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setComponent3DOptionsTestSceneOptionsSceneInvalidValues, TestSize.Level1)
{
    Opt_SceneOptions initValueSceneOptions;

    // Initial setup
    WriteTo(initValueSceneOptions).scene = ArkUnion<Opt_Union_ResourceStr_Scene, Ark_ResourceStr>(
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0])));
    WriteTo(initValueSceneOptions).modelType =
        ArkValue<Opt_ModelType>(std::get<1>(Fixtures::testFixtureEnumModelTypeValidValues[0]));

    auto checkValue = [this, &initValueSceneOptions](
                          const std::string& input, const Opt_Union_ResourceStr_Scene& value) {
        Opt_SceneOptions inputValueSceneOptions = initValueSceneOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueSceneOptions).scene = value;
        modifier_->setComponent3DOptions(node, &inputValueSceneOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultSceneOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SCENE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSceneOptions, ATTRIBUTE_SCENE_OPTIONS_I_SCENE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_SCENE_OPTIONS_I_SCENE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setComponent3DOptions, attribute: sceneOptions.scene";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_ResourceStr_Scene, Ark_Empty>(nullptr));
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_Union_ResourceStr_Scene, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Union_ResourceStr_Scene>());
}

/*
 * @tc.name: setComponent3DOptionsTestSceneOptionsModelTypeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setComponent3DOptionsTestSceneOptionsModelTypeValidValues, TestSize.Level1)
{
    Opt_SceneOptions initValueSceneOptions;

    // Initial setup
    WriteTo(initValueSceneOptions).scene = ArkUnion<Opt_Union_ResourceStr_Scene, Ark_ResourceStr>(
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0])));
    WriteTo(initValueSceneOptions).modelType =
        ArkValue<Opt_ModelType>(std::get<1>(Fixtures::testFixtureEnumModelTypeValidValues[0]));

    auto checkValue = [this, &initValueSceneOptions](
                          const std::string& input, const std::string& expectedStr, const Opt_ModelType& value) {
        Opt_SceneOptions inputValueSceneOptions = initValueSceneOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueSceneOptions).modelType = value;
        modifier_->setComponent3DOptions(node, &inputValueSceneOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultSceneOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SCENE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSceneOptions, ATTRIBUTE_SCENE_OPTIONS_I_MODEL_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setComponent3DOptions, attribute: sceneOptions.modelType";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumModelTypeValidValues) {
        checkValue(input, expected, ArkValue<Opt_ModelType>(value));
    }
}

/*
 * @tc.name: setComponent3DOptionsTestSceneOptionsModelTypeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setComponent3DOptionsTestSceneOptionsModelTypeInvalidValues, TestSize.Level1)
{
    Opt_SceneOptions initValueSceneOptions;

    // Initial setup
    WriteTo(initValueSceneOptions).scene = ArkUnion<Opt_Union_ResourceStr_Scene, Ark_ResourceStr>(
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureStringValidValues[0])));
    WriteTo(initValueSceneOptions).modelType =
        ArkValue<Opt_ModelType>(std::get<1>(Fixtures::testFixtureEnumModelTypeValidValues[0]));

    auto checkValue = [this, &initValueSceneOptions](const std::string& input, const Opt_ModelType& value) {
        Opt_SceneOptions inputValueSceneOptions = initValueSceneOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        WriteTo(inputValueSceneOptions).modelType = value;
        modifier_->setComponent3DOptions(node, &inputValueSceneOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultSceneOptions = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_SCENE_OPTIONS_NAME);
        auto resultStr = GetAttrValue<std::string>(resultSceneOptions, ATTRIBUTE_SCENE_OPTIONS_I_MODEL_TYPE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, ATTRIBUTE_SCENE_OPTIONS_I_MODEL_TYPE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setComponent3DOptions, attribute: sceneOptions.modelType";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumModelTypeInvalidValues) {
        checkValue(input, ArkValue<Opt_ModelType>(value));
    }
}

/*
 * @tc.name: setEnvironmentTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setEnvironmentTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENVIRONMENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENVIRONMENT_DEFAULT_VALUE) << "Default value for attribute 'environment'";
}

/*
 * @tc.name: setEnvironmentTestEnvironmentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setEnvironmentTestEnvironmentValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueEnvironment;

    // Initial setup
    initValueEnvironment =
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureUriStringValidValues[0]));

    auto checkValue = [this, &initValueEnvironment](
                          const std::string& input, const std::string& expectedStr, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueEnvironment = initValueEnvironment;

        inputValueEnvironment = value;
        modifier_->setEnvironment(node_, &inputValueEnvironment);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENVIRONMENT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setEnvironment, attribute: environment";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureUriStringValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureUriStringResNoEmptyValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setEnvironmentTestEnvironmentInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setEnvironmentTestEnvironmentInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueEnvironment;

    // Initial setup
    initValueEnvironment =
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureUriStringValidValues[0]));

    auto checkValue = [this, &initValueEnvironment](const std::string& input, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueEnvironment = initValueEnvironment;

        modifier_->setEnvironment(node_, &inputValueEnvironment);
        inputValueEnvironment = value;
        modifier_->setEnvironment(node_, &inputValueEnvironment);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENVIRONMENT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_ENVIRONMENT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setEnvironment, attribute: environment";
    };

    for (auto& [input, value] : Fixtures::testFixtureUriStringInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceStr, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceStr, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setShaderTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setShaderTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHADER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHADER_DEFAULT_VALUE) << "Default value for attribute 'shader'";
}

/*
 * @tc.name: setShaderTestShaderValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setShaderTestShaderValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueShader;

    // Initial setup
    initValueShader = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureUriStringValidValues[0]));

    auto checkValue = [this, &initValueShader](
                          const std::string& input, const std::string& expectedStr, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueShader = initValueShader;

        inputValueShader = value;
        modifier_->setShader(node_, &inputValueShader);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHADER_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setShader, attribute: shader";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureUriStringValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureUriStringResNoEmptyValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setShaderTestShaderInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setShaderTestShaderInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueShader;

    // Initial setup
    initValueShader = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureUriStringValidValues[0]));

    auto checkValue = [this, &initValueShader](const std::string& input, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueShader = initValueShader;

        modifier_->setShader(node_, &inputValueShader);
        inputValueShader = value;
        modifier_->setShader(node_, &inputValueShader);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHADER_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHADER_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setShader, attribute: shader";
    };

    for (auto& [input, value] : Fixtures::testFixtureUriStringInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceStr, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceStr, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setShaderImageTextureTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setShaderImageTextureTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHADER_IMAGE_TEXTURE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHADER_IMAGE_TEXTURE_DEFAULT_VALUE) <<
        "Default value for attribute 'shaderImageTexture'";
}

/*
 * @tc.name: setShaderImageTextureTestShaderImageTextureValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setShaderImageTextureTestShaderImageTextureValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueShaderImageTexture;

    // Initial setup
    initValueShaderImageTexture =
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureImageUriStringValidValues[0]));

    auto checkValue = [this, &initValueShaderImageTexture](
                          const std::string& input, const std::string& expectedStr, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueShaderImageTexture = initValueShaderImageTexture;

        inputValueShaderImageTexture = value;
        modifier_->setShaderImageTexture(node_, &inputValueShaderImageTexture);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHADER_IMAGE_TEXTURE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setShaderImageTexture, attribute: shaderImageTexture";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureImageUriStringValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureImageUriStringResNoEmptyValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setShaderImageTextureTestShaderImageTextureInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setShaderImageTextureTestShaderImageTextureInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueShaderImageTexture;

    // Initial setup
    initValueShaderImageTexture =
        ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureImageUriStringValidValues[0]));

    auto checkValue = [this, &initValueShaderImageTexture](const std::string& input, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueShaderImageTexture = initValueShaderImageTexture;

        modifier_->setShaderImageTexture(node_, &inputValueShaderImageTexture);
        inputValueShaderImageTexture = value;
        modifier_->setShaderImageTexture(node_, &inputValueShaderImageTexture);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHADER_IMAGE_TEXTURE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHADER_IMAGE_TEXTURE_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setShaderImageTexture, attribute: shaderImageTexture";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceStr, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setShaderInputBufferTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setShaderInputBufferTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHADER_INPUT_BUFFER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHADER_INPUT_BUFFER_DEFAULT_VALUE) <<
        "Default value for attribute 'shaderInputBuffer'";
}

/*
 * @tc.name: setShaderInputBufferTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setShaderInputBufferTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setRenderWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setRenderWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RENDER_WIDTH_DEFAULT_VALUE) << "Default value for attribute 'renderWidth'";
}

/*
 * @tc.name: setRenderWidthTestRenderWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setRenderWidthTestRenderWidthValidValues, TestSize.Level1)
{
    Ark_Length initValueRenderWidth;

    // Initial setup
    initValueRenderWidth = std::get<1>(Fixtures::testFixtureLengthPositivelValidValues[0]);

    auto checkValue = [this, &initValueRenderWidth](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_Length inputValueRenderWidth = initValueRenderWidth;

        inputValueRenderWidth = value;
        modifier_->setRenderWidth(node_, &inputValueRenderWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRenderWidth, attribute: renderWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthPositivelValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setRenderWidthTestRenderWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setRenderWidthTestRenderWidthInvalidValues, TestSize.Level1)
{
    Ark_Length initValueRenderWidth;

    // Initial setup
    initValueRenderWidth = std::get<1>(Fixtures::testFixtureLengthPositivelValidValues[0]);

    auto checkValue = [this, &initValueRenderWidth](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueRenderWidth = initValueRenderWidth;

        modifier_->setRenderWidth(node_, &inputValueRenderWidth);
        inputValueRenderWidth = value;
        modifier_->setRenderWidth(node_, &inputValueRenderWidth);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RENDER_WIDTH_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRenderWidth, attribute: renderWidth";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthPositivelInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setRenderHeightTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setRenderHeightTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_RENDER_HEIGHT_DEFAULT_VALUE) << "Default value for attribute 'renderHeight'";
}

/*
 * @tc.name: setRenderHeightTestRenderHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setRenderHeightTestRenderHeightValidValues, TestSize.Level1)
{
    Ark_Length initValueRenderHeight;

    // Initial setup
    initValueRenderHeight = std::get<1>(Fixtures::testFixtureLengthPositivelValidValues[0]);

    auto checkValue = [this, &initValueRenderHeight](
                          const std::string& input, const std::string& expectedStr, const Ark_Length& value) {
        Ark_Length inputValueRenderHeight = initValueRenderHeight;

        inputValueRenderHeight = value;
        modifier_->setRenderHeight(node_, &inputValueRenderHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setRenderHeight, attribute: renderHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthPositivelValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setRenderHeightTestRenderHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setRenderHeightTestRenderHeightInvalidValues, TestSize.Level1)
{
    Ark_Length initValueRenderHeight;

    // Initial setup
    initValueRenderHeight = std::get<1>(Fixtures::testFixtureLengthPositivelValidValues[0]);

    auto checkValue = [this, &initValueRenderHeight](const std::string& input, const Ark_Length& value) {
        Ark_Length inputValueRenderHeight = initValueRenderHeight;

        modifier_->setRenderHeight(node_, &inputValueRenderHeight);
        inputValueRenderHeight = value;
        modifier_->setRenderHeight(node_, &inputValueRenderHeight);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_RENDER_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_RENDER_HEIGHT_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setRenderHeight, attribute: renderHeight";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthPositivelInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setCustomRenderTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, setCustomRenderTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultCustomRender =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CUSTOM_RENDER_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultCustomRender, ATTRIBUTE_CUSTOM_RENDER_I_URI_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CUSTOM_RENDER_I_URI_DEFAULT_VALUE) <<
        "Default value for attribute 'customRender.uri'";

    resultStr = GetAttrValue<std::string>(resultCustomRender, ATTRIBUTE_CUSTOM_RENDER_I_SELF_RENDER_UPDATE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CUSTOM_RENDER_I_SELF_RENDER_UPDATE_DEFAULT_VALUE) <<
        "Default value for attribute 'customRender.selfRenderUpdate'";
}

/*
 * @tc.name: setCustomRenderTestCustomRenderUriValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setCustomRenderTestCustomRenderUriValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueUri;
    Ark_Boolean initValueSelfRenderUpdate;

    // Initial setup
    initValueUri = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureUriStringValidValues[0]));
    initValueSelfRenderUpdate = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueUri, &initValueSelfRenderUpdate](
                          const std::string& input, const std::string& expectedStr, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueUri = initValueUri;
        Ark_Boolean inputValueSelfRenderUpdate = initValueSelfRenderUpdate;

        inputValueUri = value;
        modifier_->setCustomRender(node_, &inputValueUri, inputValueSelfRenderUpdate);
        auto jsonValue = GetJsonValue(node_);
        auto resultCustomRender = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CUSTOM_RENDER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCustomRender, ATTRIBUTE_CUSTOM_RENDER_I_URI_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCustomRender, attribute: customRender.uri";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureUriStringValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceStr, Ark_String>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureUriStringResNoEmptyValidValues) {
        checkValue(input, expected, ArkUnion<Ark_ResourceStr, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setCustomRenderTestCustomRenderUriInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setCustomRenderTestCustomRenderUriInvalidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueUri;
    Ark_Boolean initValueSelfRenderUpdate;

    // Initial setup
    initValueUri = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureUriStringValidValues[0]));
    initValueSelfRenderUpdate = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueUri, &initValueSelfRenderUpdate](
                          const std::string& input, const Ark_ResourceStr& value) {
        Ark_ResourceStr inputValueUri = initValueUri;
        Ark_Boolean inputValueSelfRenderUpdate = initValueSelfRenderUpdate;

        modifier_->setCustomRender(node_, &inputValueUri, inputValueSelfRenderUpdate);
        inputValueUri = value;
        modifier_->setCustomRender(node_, &inputValueUri, inputValueSelfRenderUpdate);
        auto jsonValue = GetJsonValue(node_);
        auto resultCustomRender = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CUSTOM_RENDER_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCustomRender, ATTRIBUTE_CUSTOM_RENDER_I_URI_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CUSTOM_RENDER_I_URI_DEFAULT_VALUE) <<
            "Input value is: " << input << ", method: setCustomRender, attribute: customRender.uri";
    };

    for (auto& [input, value] : Fixtures::testFixtureUriStringInvalidValues) {
        checkValue(input, ArkUnion<Ark_ResourceStr, Ark_String>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_ResourceStr, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setCustomRenderTestCustomRenderSelfRenderUpdateValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(Component3DModifierTest, DISABLED_setCustomRenderTestCustomRenderSelfRenderUpdateValidValues, TestSize.Level1)
{
    Ark_ResourceStr initValueUri;
    Ark_Boolean initValueSelfRenderUpdate;

    // Initial setup
    initValueUri = ArkUnion<Ark_ResourceStr, Ark_String>(std::get<1>(Fixtures::testFixtureUriStringValidValues[0]));
    initValueSelfRenderUpdate = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueUri, &initValueSelfRenderUpdate](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_ResourceStr inputValueUri = initValueUri;
        Ark_Boolean inputValueSelfRenderUpdate = initValueSelfRenderUpdate;

        inputValueSelfRenderUpdate = value;
        modifier_->setCustomRender(node_, &inputValueUri, inputValueSelfRenderUpdate);
        auto jsonValue = GetJsonValue(node_);
        auto resultCustomRender = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CUSTOM_RENDER_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCustomRender, ATTRIBUTE_CUSTOM_RENDER_I_SELF_RENDER_UPDATE_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setCustomRender, attribute: customRender.selfRenderUpdate";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}
} // namespace OHOS::Ace::NG
