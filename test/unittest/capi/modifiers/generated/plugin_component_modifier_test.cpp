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
const auto ATTRIBUTE_TEMPLATE_NAME = "template";
const auto ATTRIBUTE_TEMPLATE_I_SOURCE_NAME = "source";
const auto ATTRIBUTE_TEMPLATE_I_SOURCE_DEFAULT_VALUE = "";
const auto ATTRIBUTE_TEMPLATE_I_BUNDLE_NAME_NAME = "bundleName";
const auto ATTRIBUTE_TEMPLATE_I_BUNDLE_NAME_DEFAULT_VALUE = "";
} // namespace

class PluginComponentModifierTest
    : public ModifierTestBase<GENERATED_ArkUIPluginComponentModifier,
          &GENERATED_ArkUINodeModifiers::getPluginComponentModifier, GENERATED_ARKUI_PLUGIN_COMPONENT> {
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
 * @tc.name: setPluginComponentOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PluginComponentModifierTest, setPluginComponentOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTemplate =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEMPLATE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultTemplate, ATTRIBUTE_TEMPLATE_I_SOURCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEMPLATE_I_SOURCE_DEFAULT_VALUE) <<
        "Default value for attribute 'options.template.source'";

    resultStr = GetAttrValue<std::string>(resultTemplate, ATTRIBUTE_TEMPLATE_I_BUNDLE_NAME_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TEMPLATE_I_BUNDLE_NAME_DEFAULT_VALUE) <<
        "Default value for attribute 'options.template.bundleName'";
}

/*
 * @tc.name: setPluginComponentOptionsTestOptionsTemplateSourceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(PluginComponentModifierTest, setPluginComponentOptionsTestOptionsTemplateSourceValidValues, TestSize.Level1)
{
    Ark_PluginComponentOptions initValueOptions;

    // Initial setup
    initValueOptions.template_.source = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueOptions.template_.bundleName = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_PluginComponentOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.template_.source = value;
        modifier_->setPluginComponentOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultTemplate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEMPLATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTemplate, ATTRIBUTE_TEMPLATE_I_SOURCE_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setPluginComponentOptions, attribute: options.template.source";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setPluginComponentOptionsTestOptionsTemplateBundleNameValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    PluginComponentModifierTest, setPluginComponentOptionsTestOptionsTemplateBundleNameValidValues, TestSize.Level1)
{
    Ark_PluginComponentOptions initValueOptions;

    // Initial setup
    initValueOptions.template_.source = std::get<1>(Fixtures::testFixtureStringValidValues[0]);
    initValueOptions.template_.bundleName = std::get<1>(Fixtures::testFixtureStringValidValues[0]);

    auto checkValue = [this, &initValueOptions](
                          const std::string& input, const std::string& expectedStr, const Ark_String& value) {
        Ark_PluginComponentOptions inputValueOptions = initValueOptions;

        // Re-create node for 'options' attribute
        auto node = CreateNode();
        inputValueOptions.template_.bundleName = value;
        modifier_->setPluginComponentOptions(node, &inputValueOptions);
        auto jsonValue = GetJsonValue(node);
        auto resultTemplate = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TEMPLATE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTemplate, ATTRIBUTE_TEMPLATE_I_BUNDLE_NAME_NAME);
        DisposeNode(node);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input
            << ", method: setPluginComponentOptions, attribute: options.template.bundleName";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureStringValidValues) {
        checkValue(input, expected, value);
    }
}
} // namespace OHOS::Ace::NG
